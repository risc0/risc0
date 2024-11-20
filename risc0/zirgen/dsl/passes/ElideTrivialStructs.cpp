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

#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "llvm/ADT/TypeSwitch.h"

#include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"
#include "zirgen/Dialect/ZHLT/IR/ZHLT.h"
#include "zirgen/Dialect/ZStruct/IR/ZStruct.h"
#include "zirgen/dsl/passes/PassDetail.h"

using namespace mlir;
using namespace zirgen::ZStruct;

namespace zirgen {
namespace dsl {

namespace {

bool isTrivial(Type t) {
  return TypeSwitch<Type, bool>(t)
      .Case<StructType, LayoutType>([&](auto type) {
        const auto& fields = type.getFields();
        if (fields.size() != 1)
          return false;
        if (fields[0].name != "@super")
          return false;
        Type superType = fields[0].type;
        if (!llvm::isa<StructType, LayoutType>(superType))
          return false;
        return true;
      })
      .Default([&](auto) { return false; });
}

template <typename T>
AttrTypeReplacer::ReplaceFnResult<Type> typeReplacer(AttrTypeReplacer& replacer, T type) {
  const auto& fields = type.getFields();
  if (fields.size() != 1)
    return std::nullopt;
  if (fields[0].name != "@super")
    return std::nullopt;
  Type superType = fields[0].type;
  if (!llvm::isa<StructType, LayoutType>(superType))
    return std::nullopt;
  superType = replacer.replace(superType);
  return std::make_pair(superType, WalkResult::advance());
}

AttrTypeReplacer::ReplaceFnResult<StructAttr> attrReplacer(StructAttr attr) {
  for (;;) {
    if (attr.getFields().size() != 1)
      break;
    if (!llvm::isa<StructType, LayoutType>(attr.getType()))
      break;
    if (attr.getFields().size() != 1)
      break;

    Attribute superAttr = attr.getFields().get("@super");
    if (!superAttr || !llvm::isa<StructAttr>(superAttr))
      break;
    attr = llvm::cast<StructAttr>(superAttr);
  }

  return std::make_pair(attr, WalkResult::advance());
}

struct ElideTrivialStructsPass : public ElideTrivialStructsBase<ElideTrivialStructsPass> {
  void runOnOperation() override {
    DenseSet<Operation*> elideList;
    getOperation().walk([&](ZStruct::LookupOp lookupOp) {
      if (lookupOp.getMember() != "@super")
        return;
      if (!isTrivial(lookupOp.getBase().getType()))
        return;

      elideList.insert(lookupOp);
    });
    getOperation().walk([&](ZStruct::PackOp packOp) {
      if (packOp.getMembers().size() != 1)
        return;
      if (!isTrivial(packOp.getType()))
        return;

      elideList.insert(packOp);
    });

    AttrTypeReplacer replacer;
    DenseSet<Type> elided;
    replacer.addReplacement([&](StructType t) { return typeReplacer(replacer, t); });
    replacer.addReplacement([&](LayoutType t) { return typeReplacer(replacer, t); });
    replacer.addReplacement(attrReplacer);
    replacer.recursivelyReplaceElementsIn(getOperation(),
                                          /*replaceAttrs=*/true,
                                          /*replaceLocs=*/false,
                                          /*replaceTypes=*/true);

    for (auto op : elideList) {
      Value value = TypeSwitch<Operation*, Value>(op)
                        .Case<ZStruct::LookupOp>([&](auto lookupOp) { return lookupOp.getBase(); })
                        .Case<ZStruct::PackOp>([&](auto packOp) { return packOp.getMembers()[0]; });
      assert(value.getType() == op->getResult(0).getType());
      op->getResult(0).replaceAllUsesWith(value);
      op->erase();
    }
  }
};

} // namespace

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createElideTrivialStructsPass() {
  return std::make_unique<ElideTrivialStructsPass>();
}

} // namespace dsl
} // namespace zirgen
