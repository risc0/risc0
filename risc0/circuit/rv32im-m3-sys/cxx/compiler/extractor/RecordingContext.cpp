// Copyright 2025 RISC Zero, Inc.
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

#include "compiler/extractor/RecordingContext.h"
#include "compiler/extractor/RecordingVal.h"
#include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"
#include <mlir/Dialect/Arith/IR/Arith.h>

using namespace mlir;

RecordingContext::RecordingContext(MLIRContext* mlirCtx) : mlirCtx(mlirCtx), builder(mlirCtx) {
    mlirCtx->getOrLoadDialect<zirgen::Zhlt::ZhltDialect>();
    mlirCtx->getOrLoadDialect<zirgen::ZStruct::ZStructDialect>();
    mlirCtx->getOrLoadDialect<zirgen::Zll::ZllDialect>();
    moduleOp = mlir::ModuleOp::create(builder.getUnknownLoc());
    builder.setInsertionPointToEnd(moduleOp.getBody());
}

void RecordingContext::enterComponent(std::string name) {
    assert(!componentBody && "starting a new component without ending the previous one");

    // Create a temporary region in the module where the component will be built
    componentName = builder.getStringAttr(name);
    componentBody = new Region(moduleOp);
    builder.setInsertionPointToStart(builder.createBlock(componentBody));
    zero = builder.create<arith::ConstantOp>(builder.getUnknownLoc(), builder.getIndexAttr(0));
}

void RecordingContext::exitComponent() {
    assert(componentBody && "ending a component without starting one");

    // Add a trivial return
    auto compType = zirgen::Zhlt::getComponentType(mlirCtx);
    auto ret = builder.create<zirgen::ZStruct::PackOp>(builder.getUnknownLoc(), compType, ValueRange());
    builder.create<zirgen::Zhlt::ReturnOp>(builder.getUnknownLoc(), ret);

    // Now move the temporary body into a function with the right signature
    builder.setInsertionPointToEnd(moduleOp.getBody());
    auto funcType = FunctionType::get(mlirCtx, componentBody->getArgumentTypes(), {compType});
    auto component = builder.create<zirgen::Zhlt::ComponentOp>(
        builder.getUnknownLoc(), componentName, funcType, nullptr, nullptr, nullptr);
    component.getBody().takeBody(*componentBody);
    component->setAttr("picus_analyze", builder.getUnitAttr());
    componentBody = nullptr;
    zero = nullptr;
}

RecordingVal RecordingContext::addValParameter() {
    assert(componentBody && "adding parameter without a component");
    mlir::Type val = zirgen::Zhlt::getValType(mlirCtx);
    mlir::Value param = componentBody->addArgument(val, builder.getUnknownLoc());
    return RecordingVal(param);
}

RecordingVal RecordingContext::getNextRef() {
    assert(componentBody && "adding parameter without a component");
    mlir::Value ref = builder.create<mlir::UnrealizedConversionCastOp>(
        builder.getUnknownLoc(), zirgen::Zll::ValType::get(mlirCtx), ValueRange {}).getResult(0);
    refs.push_back(ref);
    return ref;
}

void RecordingContext::unifyRefsIntoLayout(mlir::Value layout, size_t& i) {
  assert(i < refs.size() && "there should be the same number of refs in the context and layout");

  if (isa<zirgen::ZStruct::RefType>(layout.getType())) {
    mlir::Value val = builder.create<zirgen::ZStruct::LoadOp>(builder.getUnknownLoc(), layout, zero);
    refs[i].replaceAllUsesWith(val);
    refs[i].getDefiningOp()->erase();
    i++;
  } else if (auto str = dyn_cast<zirgen::ZStruct::LayoutType>(layout.getType())) {
    for (auto field : str.getFields()) {
      mlir::Value sublayout = builder.create<zirgen::ZStruct::LookupOp>(builder.getUnknownLoc(), layout, field.name);
      unifyRefsIntoLayout(sublayout, i);
    }
  } else if (auto arr = dyn_cast<zirgen::ZStruct::LayoutArrayType>(layout.getType())) {
    for (size_t j = 0; j < arr.getSize(); j++) {
      auto index = builder.create<arith::ConstantIndexOp>(builder.getUnknownLoc(), j);
      mlir::Value sublayout = builder.create<zirgen::ZStruct::SubscriptOp>(
          builder.getUnknownLoc(), layout, index);
      unifyRefsIntoLayout(sublayout, i);
    }
  } else {
    assert(false && "unrecognized layout type");
  }
}

void RecordingContext::materializeLayout(mlir::Type layoutType) {
    assert(componentBody && "materializing layout of a component that doesn't exist");

    mlir::Value layout = componentBody->addArgument(layoutType, builder.getUnknownLoc());
    builder.setInsertionPointAfter(refs.back().getDefiningOp());
    size_t i = 0;
    unifyRefsIntoLayout(layout, i);
    builder.setInsertionPointToEnd(&componentBody->back());
    refs.clear();
}
