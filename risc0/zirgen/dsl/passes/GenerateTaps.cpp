// Copyright 2024 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "mlir/Transforms/DialectConversion.h"
#include "llvm/ADT/TypeSwitch.h"

#include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"
#include "zirgen/Dialect/ZHLT/IR/ZHLT.h"
#include "zirgen/Dialect/ZStruct/IR/ZStruct.h"
#include "zirgen/Dialect/Zll/IR/Interpreter.h"
#include "zirgen/dsl/passes/PassDetail.h"

using namespace mlir;
using namespace zirgen::ZStruct;

namespace zirgen {
namespace dsl {

// The requirements for GenerateTapsPass are:
//  * Layouts must be generated
//
//  * The circuit-wide CheckFuncOp completely unrolled, in that both the "ref" and
//  "back" arguments to any ZStruct::Load must be evaluatable as constants.
struct GenerateTapsPass : public GenerateTapsBase<GenerateTapsPass> {
  void runOnOperation() override {
    auto module = getOperation();
    auto ctx = module.getContext();
    OpBuilder builder(ctx);
    Location loc = builder.getUnknownLoc();
    auto bufs = Zll::lookupModuleAttr<Zll::BuffersAttr>(module);

    DenseMap<std::pair</*buffer=*/StringAttr, /*offset=*/size_t>, /*backs=*/DenseSet<size_t>>
        namedTaps;
    DenseMap<std::tuple</*buffer=*/StringAttr, /*offset=*/size_t, /*back=*/size_t>,
             SmallVector<Zll::GetOp>>
        getOps;

    auto walkResult = module.walk([&](Zhlt::CheckFuncOp check) {
      Zll::Interpreter interp(ctx);

      auto res = check->walk([&](LoadOp op) {
        auto ref = interp.evaluateConstantOfType<BoundLayoutAttr>(op.getRef());
        if (!ref) {
          op->emitError() << "Ref must be a constant";
          return WalkResult::interrupt();
        }
        auto distanceAttr = interp.evaluateConstantOfType<IntegerAttr>(op.getDistance());
        if (!distanceAttr) {
          op->emitError() << "distance must be a constant";
          return WalkResult::interrupt();
        }
        size_t distance = getIndexVal(distanceAttr);
        namedTaps[std::make_pair(ref.getBuffer(), llvm::cast<RefAttr>(ref.getLayout()).getIndex())]
            .insert(distance);
        return WalkResult::advance();
      });
      if (res.wasInterrupted())
        return WalkResult::interrupt();

      res = check->walk([&](Zll::GetOp op) {
        auto bufOp = op.getBuf().getDefiningOp<GetBufferOp>();
        if (!bufOp) {
          op->emitError() << "unable to determine buffer";
          return WalkResult::interrupt();
        }

        namedTaps[std::make_pair(bufOp.getNameAttr(), op.getOffset())].insert(op.getBack());
        getOps[std::make_tuple(bufOp.getNameAttr(), op.getOffset(), op.getBack())].push_back(op);
        return WalkResult::advance();
      });
      if (res.wasInterrupted())
        return WalkResult::interrupt();
      return WalkResult::advance();
    });

    if (walkResult.wasInterrupted()) {
      signalPassFailure();
    }

    SmallVector<Zll::TapAttr> taps;
    for (auto tapBuf : bufs.getTapBuffers()) {
      for (size_t offset = 0; offset != tapBuf.getRegCount(); ++offset) {
        SmallVector<size_t> backs =
            llvm::to_vector(namedTaps.lookup(std::make_pair(tapBuf.getName(), offset)));
        if (backs.empty()) {
          // Fill in any holes so that the register list is contiguous
          // TODO: We shouldn't have to do this, either by verifying there aren't any holes,
          // or by not depending on there being no holes.
          backs.push_back(0);
        }
        llvm::sort(backs);
        for (size_t back : backs) {
          taps.push_back(builder.getAttr<Zll::TapAttr>(*tapBuf.getRegGroupId(), offset, back));
        }
      }
    }

    builder.setInsertionPointToStart(module.getBody());

    Type tapArrayType = builder.getType<ArrayType>(builder.getType<TapType>(), taps.size());

    builder.create<GlobalConstOp>(loc,
                                  Zhlt::getTapsConstName(),
                                  tapArrayType,
                                  builder.getArrayAttr(llvm::to_vector_of<Attribute>(taps)));

    Zll::setModuleAttr(module, builder.getAttr<Zll::TapsAttr>(taps));
  }
};

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateTapsPass() {
  return std::make_unique<GenerateTapsPass>();
}

} // namespace dsl
} // namespace zirgen
