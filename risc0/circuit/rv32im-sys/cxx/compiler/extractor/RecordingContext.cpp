// Copyright 2026 RISC Zero, Inc.
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

#include "compiler/extractor/RecordingContext.h"
#include "compiler/extractor/RecordingVal.h"
#include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"
#include <mlir/Dialect/Arith/IR/Arith.h>

using namespace mlir;

RecordingContext* RecordingReg::ctx = nullptr;

RecordingContext::RecordingContext(MLIRContext* mlirCtx) : mlirCtx(mlirCtx), builder(mlirCtx) {
  mlirCtx->getOrLoadDialect<zirgen::Zhlt::ZhltDialect>();
  mlirCtx->getOrLoadDialect<zirgen::ZStruct::ZStructDialect>();
  mlirCtx->getOrLoadDialect<zirgen::Zll::ZllDialect>();
  moduleOp = mlir::ModuleOp::create(builder.getUnknownLoc());
  builder.setInsertionPointToEnd(moduleOp.getBody());
}

RecordingVal RecordingContext::globalGet(uint32_t entry) {
  if (globalsCache.find(entry) != globalsCache.end()) {
    // Cache values of globals within a component so that accesses of the same
    // global are the same MLIR value.
    return globalsCache.at(entry);
  } else {
    auto loc = builder.getUnknownLoc();
    auto ref = zirgen::ZStruct::getRefType(builder.getContext());
    auto global = builder.create<zirgen::Zhlt::GetGlobalLayoutOp>(loc, ref, std::to_string(entry));
    auto val = builder.create<zirgen::ZStruct::LoadOp>(loc, global.getResult(), zero);
    RecordingVal result(val.getResult());
    globalsCache.insert({entry, result});
    return result;
  }
}

RecordingVal RecordingContext::getX() {
  // Cache the value of `x` within a component so that different accesses give
  // the same MLIR value.
  if (!x.value) {
    x = addValParameter();
  }
  return x;
}

void RecordingContext::enterComponent(const char* name, mlir::Type layoutType) {
  assert(!componentBody && "starting a new component without ending the previous one");

  // Create a temporary region in the module where the component will be built
  componentName = name;
  componentBody = new Region(moduleOp);
  builder.setInsertionPointToStart(builder.createBlock(componentBody));
  componentBody->addArgument(layoutType, builder.getUnknownLoc());
  zero = builder.create<arith::ConstantOp>(builder.getUnknownLoc(), builder.getIndexAttr(0));
}

void RecordingContext::exitComponent() {
  assert(componentBody && "ending a component without starting one");

  // Add a trivial return
  auto compType = zirgen::Zhlt::getComponentType(mlirCtx);
  auto ret =
      builder.create<zirgen::ZStruct::PackOp>(builder.getUnknownLoc(), compType, ValueRange());
  builder.create<zirgen::Zhlt::ReturnOp>(builder.getUnknownLoc(), ret);

  // Now move the temporary body into a function with the right signature
  builder.setInsertionPointToEnd(moduleOp.getBody());
  auto funcType = FunctionType::get(mlirCtx, componentBody->getArgumentTypes(), {compType});
  auto component = builder.create<zirgen::Zhlt::ComponentOp>(builder.getUnknownLoc(),
                                                             builder.getStringAttr(componentName),
                                                             funcType,
                                                             nullptr,
                                                             nullptr,
                                                             nullptr);
  component.getBody().takeBody(*componentBody);
  component->setAttr("picus_analyze", builder.getUnitAttr());
  componentBody = nullptr;
  zero = nullptr;
  globalsCache.clear();
  x.value = nullptr;
}

RecordingVal RecordingContext::addValParameter() {
  assert(componentBody && "adding parameter without a component");
  mlir::Type val = zirgen::Zhlt::getValType(mlirCtx);
  auto pos = componentBody->getNumArguments() - 1;
  mlir::Value param = componentBody->insertArgument(pos, val, builder.getUnknownLoc());
  return RecordingVal(param);
}
