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

namespace zirgen {
namespace dsl {

namespace {

template <typename OpT, typename Wrapped> struct NonLayout : public Wrapped {
  using Wrapped::Wrapped;

  mlir::LogicalResult matchAndRewrite(OpT op, mlir::PatternRewriter& rewriter) const override {
    // Skip anything with a layout
    if (llvm::any_of(op->getOperands().getTypes(),
                     [&](auto ty) { return llvm::isa<LayoutType, LayoutArrayType>(ty); }))
      return failure();

    return Wrapped::matchAndRewrite(op, rewriter);
  }
};

} // namespace

struct InlinePurePass : public InlinePureBase<InlinePurePass> {
  void runOnOperation() override {
    auto* ctx = &getContext();

    RewritePatternSet patterns(ctx);
    patterns.insert<NonLayout<ZStruct::MapOp, ZStruct::UnrollMaps>>(ctx);
    patterns.insert<NonLayout<ZStruct::ReduceOp, ZStruct::UnrollReduces>>(ctx);
    patterns.insert<NonLayout<CallOpInterface, InlineCalls>>(ctx);
    //    patterns.insert<NonLayout<ZStruct::SwitchOp, ZStruct::SplitSwitchArms>>(ctx);

    for (auto* dialect : ctx->getLoadedDialects())
      dialect->getCanonicalizationPatterns(patterns);
    for (RegisteredOperationName op : ctx->getRegisteredOperations())
      op.getCanonicalizationPatterns(patterns, ctx);

    FrozenRewritePatternSet frozenPatterns(std::move(patterns));
    GreedyRewriteConfig config;
    config.maxIterations = 100;
    if (applyPatternsAndFoldGreedily(getOperation(), frozenPatterns, config).failed()) {
      getOperation()->emitError("Couldn't apply optimization patterns");
      signalPassFailure();
    }
  }
};

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createInlinePurePass() {
  return std::make_unique<InlinePurePass>();
}

} // namespace dsl
} // namespace zirgen
