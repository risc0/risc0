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

// Wherever an AliasLayoutOp occurs, the implied layout constraint must be
// unconditionally satisfied. Therefore, we should replace any IfOp with its
// contents when collecting our layout constraints.
struct DeconditionalizeIfOp : public OpRewritePattern<Zll::IfOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(Zll::IfOp op, PatternRewriter& rewriter) const final {
    // For some reason, this inlining method puts the terminator in the middle
    // of the destination block, so preemptively erase it.
    rewriter.eraseOp(op.getInner().front().getTerminator());
    rewriter.inlineBlockBefore(&op.getInner().front(), op);
    rewriter.eraseOp(op);
    return success();
  }
};

} // namespace

// Transform ComponentOps into constraint-checking functions.
struct GenerateCheckLayoutPass : public GenerateCheckLayoutBase<GenerateCheckLayoutPass> {
  void runOnOperation() override {
    auto* ctx = &getContext();

    RewritePatternSet patterns(ctx);
    patterns.insert<EraseOp<ZStruct::LoadOp>>(ctx);
    patterns.insert<EraseOp<ZStruct::StoreOp>>(ctx);
    patterns.insert<EraseOp<Zll::ExternOp>>(ctx);
    patterns.insert<EraseOp<Zll::EqualZeroOp>>(ctx);
    patterns.insert<InlineCalls>(ctx);
    patterns.insert<ZStruct::SplitSwitchArms>(ctx);
    patterns.insert<DeconditionalizeIfOp>(ctx);
    ZStruct::getUnrollPatterns(patterns, ctx);

    FrozenRewritePatternSet frozenPatterns(std::move(patterns));

    OpBuilder builder(ctx);
    mlir::ModuleOp mod = getOperation();

    mod.walk([&](Zhlt::ComponentOp component) {
      if (!Zhlt::isBufferComponent(component))
        return;

      StringRef name = component.getName();
      Location loc = component.getLoc();
      builder.setInsertionPoint(component);
      Type layoutType = component.getLayoutType();
      auto func = builder.create<Zhlt::CheckLayoutFuncOp>(loc, name, layoutType);

      Block* block = func.addEntryBlock();
      builder.setInsertionPointToEnd(block);
      if (layoutType) {
        // Synthesize other params out of nothing; since these cannot be
        // involved in layout expressions, they will fold away in a moment.
        SmallVector<Value> constructArgs;
        for (Type paramType : component.getConstructParamTypes()) {
          Value param = builder.create<Zhlt::MagicOp>(loc, paramType);
          constructArgs.push_back(param);
        }
        Value layout = block->getArgument(0);
        builder.create<Zhlt::ConstructOp>(loc, component, constructArgs, layout);
      }
      builder.create<Zhlt::ReturnOp>(loc);

      // Now, inline everything and get rid of everything that's not a constraint.
      GreedyRewriteConfig config;
      config.maxIterations = 100;
      if (applyPatternsAndFoldGreedily(func, frozenPatterns, config).failed()) {
        func->emitError("Could not generate check function");
        signalPassFailure();
      }
    });
  }
};

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateCheckLayoutPass() {
  return std::make_unique<GenerateCheckLayoutPass>();
}

} // namespace dsl
} // namespace zirgen
