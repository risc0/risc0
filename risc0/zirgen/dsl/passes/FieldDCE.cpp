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

#include "zirgen/Dialect/ZStruct/Transforms/RewritePatterns.h"
#include "zirgen/dsl/passes/CommonRewrites.h"
#include "zirgen/dsl/passes/PassDetail.h"

using namespace zirgen::ZStruct;

namespace zirgen {
namespace dsl {

namespace {

struct FieldDCEPass : public FieldDCEBase<FieldDCEPass> {
  void runOnOperation() override {
    auto* ctx = &getContext();

    DenseMap<StructType, /*used=*/DenseSet</*fieldName=*/StringAttr>> used;

    // Make sure pack operations at least exist, so we can remove all the fields if none of them are
    // there.
    getOperation()->walk([&](ZStruct::PackOp packOp) {
      if (auto structType = llvm::dyn_cast<StructType>(packOp.getType()))
        used.insert(std::make_pair(structType, DenseSet<StringAttr>{}));
    });
    // Now, see what's used by lookup operations
    getOperation()->walk([&](ZStruct::LookupOp lookupOp) {
      if (auto structType = llvm::dyn_cast<StructType>(lookupOp.getBase().getType())) {
        used[structType].insert(lookupOp.getMemberAttr());
      }
    });

    DenseMap</*old=*/StructType, /*pack args to erase=*/BitVector> erasePackArgs;

    for (auto [ty, usedFields] : used) {
      BitVector eraseSet(ty.getFields().size());
      for (auto [idx, field] : llvm::enumerate(ty.getFields())) {
        if (!usedFields.contains(field.name)) {
          eraseSet.set(idx);
        }
      }
      erasePackArgs[ty] = eraseSet;
    }

    getOperation()->walk([&](ZStruct::PackOp packOp) {
      if (auto structType = llvm::dyn_cast<StructType>(packOp.getType())) {
        packOp->eraseOperands(erasePackArgs.at(structType));
      }
    });

    AttrTypeReplacer rewriteTypes;
    // replace types even if they're behind a TypeAttr
    rewriteTypes.addReplacement([&](TypeAttr typeAttr) -> Attribute {
      return TypeAttr::get(rewriteTypes.replace(typeAttr.getValue()));
    });
    rewriteTypes.addReplacement([&](StructType ty) -> std::optional<Type> {
      if (!used.contains(ty))
        return std::nullopt;
      DenseSet<StringAttr> usedFields = used.at(ty);

      SmallVector<FieldInfo> newFields;
      for (auto field : ty.getFields()) {
        if (usedFields.contains(field.name))
          newFields.push_back(
              FieldInfo{.name = field.name, .type = rewriteTypes.replace(field.type)});
      }

      auto newType = StructType::get(ctx, ty.getId(), newFields);
      return newType;
    });

    rewriteTypes.recursivelyReplaceElementsIn(getOperation(),
                                              /*replaceAttrs=*/true,
                                              /*replaceLocs=*/false,
                                              /*replaceTypes=*/true);
  }
};

} // namespace

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createFieldDCEPass() {
  return std::make_unique<FieldDCEPass>();
}

} // namespace dsl
} // namespace zirgen
