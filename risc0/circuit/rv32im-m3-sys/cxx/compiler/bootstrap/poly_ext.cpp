#include "core/log.h"
#include "compiler/extractor/RecordingVal.h"
#include "rv32im/circuit/verify.h"
#include "rv32im/emu/blocks.h"
#include "verify/rv32im.h"
#include "zkp/taps.h"

#include "llvm/ADT/TypeSwitch.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/Passes.h"

static std::string prefix = R"***(// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkp::adapter::{PolyExtStep, PolyExtStepDef};

pub const POLY_EXT_DEF: PolyExtStepDef = PolyExtStepDef {
    block: &[
)***";

using namespace risc0;
using namespace mlir;
using namespace zirgen::Zll;

struct TrivialRecordingReg {
  Value val;
  TrivialRecordingReg(Value val) : val(val) {}
  template<typename T, typename C> void applyInner(C& ctx) {}
  template<typename C> void applyInner(C& ctx) {}
  template<typename C> void verify(C& ctx) {}
  template<typename C> void addArguments(C& ctx) {}
  RecordingVal get() { return RecordingVal(val); }
};

static Type getBufType(MLIRContext& ctx, uint32_t deg, uint32_t size, BufferKind kind) {
  return BufferType::get(&ctx, ValType::get(&ctx, kFieldPrimeDefault, deg), size, kind); 
}

using TapMap = std::map<Tap, size_t>;

static std::vector<TrivialRecordingReg> makeRegs(Value uBuf, const Group& group, const TapMap& tapMap, size_t back) {
  OpBuilder& builder = *BuilderSingleton::get();
  Value zero = RecordingVal(0).value;
  auto loc = builder.getUnknownLoc();
  std::vector<TrivialRecordingReg> ret;
  for (const Column& col : group.getColumns()) {
    Value cur = zero;
    for (const Tap& tap : col.getTaps()) {
      if (tap.back == back && tapMap.count(tap)) {
        size_t id = tapMap.at(tap);
        cur = builder.create<GetOp>(loc, uBuf, id, 0, IntegerAttr());
      }
    }
    ret.emplace_back(cur);
  }
  return ret;
}

static std::vector<RecordingVal> makeGlobals(Value buffer, size_t size) {
  std::vector<RecordingVal> ret;
  OpBuilder& builder = *BuilderSingleton::get();
  auto loc = builder.getUnknownLoc();
  for (size_t i = 0; i < size; i++) {
    Value val = builder.create<GetGlobalOp>(loc, buffer, i);
    ret.emplace_back(val);
  }
  return ret;
}

static std::vector<RecordingValExt> makeMix(Value buffer, size_t size) {
  std::vector<RecordingValExt> ret;
  OpBuilder& builder = *BuilderSingleton::get();
  auto loc = builder.getUnknownLoc();
  for (size_t i = 0; i < size; i++) {
    auto v0 = RecordingVal(builder.create<GetGlobalOp>(loc, buffer, 4*i + 0));
    auto v1 = RecordingVal(builder.create<GetGlobalOp>(loc, buffer, 4*i + 1));
    auto v2 = RecordingVal(builder.create<GetGlobalOp>(loc, buffer, 4*i + 2));
    auto v3 = RecordingVal(builder.create<GetGlobalOp>(loc, buffer, 4*i + 3));
    ret.emplace_back(v0, v1, v2, v3);
  }
  return ret;
}

struct ZllEqzContext {
  using MixStateT = Value;
  Value getTrue() {
    OpBuilder& builder = *BuilderSingleton::get();
    return builder.create<TrueOp>(builder.getUnknownLoc());
  }
  Value andEqz(Value chain, RecordingVal v) {
    OpBuilder& builder = *BuilderSingleton::get();
    return builder.create<AndEqzOp>(builder.getUnknownLoc(), chain, v.value);
  }
  Value andEqz(Value chain, RecordingValExt v) {
    OpBuilder& builder = *BuilderSingleton::get();
    return builder.create<AndEqzOp>(builder.getUnknownLoc(), chain, v.value);
  }
  Value andCond(Value chain, RecordingVal v, Value inner) {
    OpBuilder& builder = *BuilderSingleton::get();
    return builder.create<AndCondOp>(builder.getUnknownLoc(), chain, v.value, inner);
  }
};

void emitPolyExt(const std::string path) {
  // Basic MLIR setup
  MLIRContext mlirCtx;
  mlirCtx.getOrLoadDialect<zirgen::Zll::ZllDialect>();
  OpBuilder builder(&mlirCtx);
  auto loc = builder.getUnknownLoc();
  auto moduleOp = mlir::ModuleOp::create(loc);
  builder.setInsertionPointToEnd(moduleOp.getBody());
  BuilderSingleton::set(&builder);

  // Get taps
  VerifyCircuitInfo ci;
  setupVerifyInfo(ci);
  auto& taps = ci.taps;

  // Make tap map
  TapMap tapMap;
  for (const Tap& tap : taps.getTaps()) {
    size_t id = tapMap.size();
    tapMap[tap] = id;
  }

  // Setup entry function: receive a buffer of U + x, globals, mix (as Fp)
  std::vector<Type> inTypes;
  size_t totTaps = taps.getTaps().size();
  inTypes.push_back(getBufType(mlirCtx, 1, totTaps + 1, BufferKind::Constant));
  inTypes.push_back(getBufType(mlirCtx, 1, NUM_GLOBALS, BufferKind::Global));
  inTypes.push_back(getBufType(mlirCtx, 1, 4*ACCUM_MIX_SIZE, BufferKind::Global));

  // Return a 'truthy' value
  std::vector<Type> outTypes;
  outTypes.push_back(ConstraintType::get(&mlirCtx));

  // Make function entry point and set builder inside
  auto funcType = FunctionType::get(&mlirCtx, inTypes, outTypes);
  auto func = builder.create<func::FuncOp>(loc, "verify", funcType);
  builder.setInsertionPointToStart(func.addEntryBlock());

  // Get the relevant arguments + name them
  Value uBuf = func.getArgument(0);
  Value gBuf = func.getArgument(1);
  Value mBuf = func.getArgument(2);

  // Convert to 'registers'
  auto data = makeRegs(uBuf, taps.getGroups()[0], tapMap,  0);
  auto accum = makeRegs(uBuf, taps.getGroups()[1], tapMap, 0);
  auto prevAccum = makeRegs(uBuf, taps.getGroups()[1], tapMap, 1);

  // Make globals, mix and x
  auto globals = makeGlobals(gBuf, NUM_GLOBALS);
  auto accumMix = makeMix(mBuf, ACCUM_MIX_SIZE);
  Value xVal = builder.create<GetOp>(loc, uBuf, totTaps, 0, IntegerAttr());
  auto x  = RecordingVal(xVal);

  // Apply circuit + finalize function
  ZllEqzContext eqzCtx;
  auto ret = verifyCircuitCtx<TrivialRecordingReg, RecordingVal, RecordingValExt, ZllEqzContext>(
      eqzCtx,
      data.data(),
      accum.data(),
      prevAccum.data(),
      globals.data(),
      accumMix.data(),
      x);
  builder.create<func::ReturnOp>(loc, ret);

  // Simplify
  mlir::PassManager pm(&mlirCtx);
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());
  if (failed(pm.run(moduleOp))) {
    throw std::runtime_error("Unable to optimize polyext");
  }

  // Open output 
  std::error_code EC;
  llvm::raw_fd_ostream outs(path, EC);
  if (EC) {
    throw std::runtime_error("Unable to open polyext output file");
  }
  outs << prefix;

  mlir::DenseMap<Value, size_t> valMap;
  mlir::DenseMap<Value, size_t> condMap;
  // Add an early zero in to handle 'neg'
  outs << "        PolyExtStep::Const(0),\n";
  for (Operation& origOp : func.front().without_terminator()) {
    TypeSwitch<Operation*>(&origOp)
      .Case<ConstOp>([&](auto op) {
          auto co= op.getCoefficients();
          if (co.size() == 1) {
            outs << "        PolyExtStep::Const(" << co[0] << "),\n";
          } else {
            outs << "        PolyExtStep::ConstExt(" << co[0] << ", " << co[1] << ", " << co[2] << ", " << co[3] << "),\n";
          }
      })
      .Case<GetOp>([&](auto op) {
          outs << "        PolyExtStep::Get(" << op.getOffset() << "),\n";
      })
      .Case<GetGlobalOp>([&](auto op) {
          size_t idx = (op.getBuf() == gBuf ? 0 : 1); 
          outs << "        PolyExtStep::GetGlobal(" << idx << ", " << op.getOffset() << "),\n";
      })
      .Case<AddOp>([&](auto op) {
          outs << "        PolyExtStep::Add(" << valMap.at(op.getLhs()) << ", " << valMap.at(op.getRhs()) << "),\n";
      })
      .Case<SubOp>([&](auto op) {
          outs << "        PolyExtStep::Sub(" << valMap.at(op.getLhs()) << ", " << valMap.at(op.getRhs()) << "),\n";
      })
      .Case<MulOp>([&](auto op) {
          outs << "        PolyExtStep::Mul(" << valMap.at(op.getLhs()) << ", " << valMap.at(op.getRhs()) << "),\n";
      })
      .Case<NegOp>([&](auto op) {
          outs << "        PolyExtStep::Sub(0, " << valMap.at(op.getIn()) << "),\n";
      })
      .Case<TrueOp>([&](auto op) {
          outs << "        PolyExtStep::True,\n";
      })
      .Case<AndEqzOp>([&](auto op) {
          outs << "        PolyExtStep::AndEqz(" << condMap.at(op.getIn()) << ", " << valMap.at(op.getVal()) << "),\n";
      })
      .Case<AndCondOp>([&](auto op) {
          outs << "        PolyExtStep::AndCond(" << condMap.at(op.getIn()) << ", " << 
          valMap.at(op.getCond()) << ", " << condMap.at(op.getInner()) << "),\n";
      })
      .Default([&](Operation* op) {
          llvm::errs() << *op;
          throw std::runtime_error("Invalid op");
      });
    TypeSwitch<Type>(origOp.getResult(0).getType())
      .Case<ConstraintType>([&](auto t) {
          size_t id = condMap.size();
          condMap[origOp.getResult(0)] = id;
      })
      .Case<ValType>([&](auto t) {
          size_t id = valMap.size() + 1;  // +1 due to fake 0 const
          valMap[origOp.getResult(0)] = id;
      })
      .Default([&](Type t) {
          throw std::runtime_error("Invalid type");
      });
  }
  outs << "    ],\n";
  auto returnOp = func.front().getTerminator();
  outs << "    ret: " << condMap.at(returnOp->getOperand(0)) << ",\n";
  outs << "};\n";
}
