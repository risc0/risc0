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

#include <functional>

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/Dominance.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/Verifier.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/CSE.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/Transforms/TopologicalSortUtils.h"
#include "llvm/ADT/TypeSwitch.h"

#include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"
#include "zirgen/Dialect/ZHLT/IR/ZHLT.h"
#include "zirgen/Dialect/ZStruct/IR/ZStruct.h"
#include "zirgen/Dialect/ZStruct/Transforms/RewritePatterns.h"
#include "zirgen/Dialect/Zll/IR/Interpreter.h"
#include "zirgen/dsl/passes/CommonRewrites.h"
#include "zirgen/dsl/passes/PassDetail.h"

using namespace mlir;
using namespace zirgen::Zll;
using namespace zirgen::ZStruct;

namespace cl = llvm::cl;

static cl::opt<size_t> circuitNdebug(
    "circuit-ndebug",
    cl::desc("Don't check constraints when generating proofs.  This can make debugging more "
             "difficult, since problems won't be detected until verification."),
    cl::init(false));

namespace zirgen {
namespace dsl {

// Convert zhlt.construct to func.call on the component's "exec" function.
struct ConstructToCall : public OpRewritePattern<Zhlt::ConstructOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(Zhlt::ConstructOp op, PatternRewriter& rewriter) const final {
    auto callOp = rewriter.create<Zhlt::ExecCallOp>(op->getLoc(),
                                                    op.getCallee(),
                                                    op.getType(),
                                                    op.getConstructParam(),
                                                    /*layout=*/op.getLayout());
    rewriter.replaceOp(op, callOp.getResult());
    return success();
  }
};

// Inline zhlt.constructs for use in "check" functions.
struct InlineCheckConstruct : public OpRewritePattern<Zhlt::ConstructOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(Zhlt::ConstructOp op, PatternRewriter& rewriter) const final {
    Zhlt::ComponentOp callable =
        op->getParentOfType<ModuleOp>().lookupSymbol<Zhlt::ComponentOp>(op.getCallee());
    if (!callable)
      return rewriter.notifyMatchFailure(op, "failed to resolve symbol " + op.getCallee());

    IRMapping mapping;
    Region clonedBody;
    callable.getBody().cloneInto(&clonedBody, mapping);
    remapInlinedLocations(clonedBody.getBlocks(), op.getLoc());
    Block* block = &clonedBody.front();
    auto returnOp = cast<Zhlt::ReturnOp>(block->getTerminator());

    rewriter.inlineBlockBefore(block, op, op.getOperands());
    rewriter.replaceOp(op, returnOp->getOperands());
    rewriter.eraseOp(returnOp);
    return success();
  }
};

// Convert maps over argument arrays to maps over a range
struct ArrayMapToRangeMap : public OpRewritePattern<MapOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(MapOp op, PatternRewriter& rewriter) const final {
    TypedValue<ArrayLikeTypeInterface> array = op.getArray();

    if (!isa<Zhlt::MagicOp>(array.getDefiningOp()))
      return rewriter.notifyMatchFailure(op, "array is not an argument");

    // Create a range to replace the argument array with
    SmallVector<Value> content;
    for (uint64_t i = 0; i < array.getType().getSize(); i++) {
      content.push_back(rewriter.create<Zll::ConstOp>(op.getLoc(), i));
    }
    Value range = rewriter.create<ZStruct::ArrayOp>(op.getLoc(), content);

    // before: for elem : arr { ... }
    //  after: for i : 0..N { elem := arr[i]; ... }
    auto mapOp = rewriter.create<ZStruct::MapOp>(op.getLoc(), op.getType(), range, op.getLayout());
    mapOp.getBody().takeBody(op.getBody());
    rewriter.setInsertionPointToStart(&mapOp.getBody().front());
    BlockArgument idx = mapOp.getBody().getArgument(0);
    idx.setType(getValType(op.getContext()));
    Value replacementArg = rewriter.create<SubscriptOp>(op.getLoc(), array, idx);
    rewriter.replaceAllUsesWith(idx, replacementArg);

    rewriter.replaceOp(op, mapOp);
    return success();
  }
};

static bool isIdempotent(Operation* op) {
  return op->hasTrait<OpTrait::ConstantLike>() || isPure(op) ||
         llvm::isa<PolyOp, EqualZeroOp, YieldOp, IfOp, TerminateOp, LoadOp>(op);
}

// Attempts to to unravel the use of the result of a switch operation
// returning a StructType.  We generate an additional switch operation
// with the same condition for each member of the structure, having
// the switch operation only return that member.  Then, we add a pack
// operation to reconstruct the structure from the individual switch
// operations.
//
// Constraints are left in the original switch operation for
// processing by SplitSwitchArms, but all uses of the result value are
// changed to use the repacked value.
//
// This requires all operations inside are at the least idempotent if
// not completely pure, since they may be duplicated between struct
// members.  As such, we verify that all the operations are ones are
// allow before we attempt unravelling.

struct UnravelSwitchPackResult : public OpRewritePattern<SwitchOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(SwitchOp op, PatternRewriter& rewriter) const final {
    // Don't bother unravelling if we don't need these results
    if (op->use_empty())
      return failure();

    StructType ty = dyn_cast<StructType>(op.getType());
    if (!ty)
      return failure();

    // Make sure all operations are ones we expect
    for (auto& region : op->getRegions()) {
      for (auto& nestedOp : region.getOps()) {
        if (!isIdempotent(&nestedOp))
          return failure();
      }
    }

    rewriter.setInsertionPointAfter(op);
    SmallVector<Value> splitFields;
    for (auto field : ty.getFields()) {
      auto fieldSplitOp =
          rewriter.create<SwitchOp>(op.getLoc(), field.type, op.getSelector(), op.getArms().size());
      for (size_t i = 0; i != op.getArms().size(); ++i) {
        auto& origArm = op.getArms()[i];
        OpBuilder::InsertionGuard insertionGuard(rewriter);
        rewriter.createBlock(&fieldSplitOp.getArms()[i]);

        IRMapping mapper;
        for (auto& origOp : origArm.front()) {
          TypeSwitch<Operation*>(&origOp)
              .Case<EqualZeroOp>([&](auto origOp) {
                // Don't add constraints to any of the copies.
              })
              .Case<IfOp>([&](auto origOp) {
                // If ops can't contribute to the result, so skip them.
              })
              .Case<YieldOp>([&](auto origOp) {
                auto lookupOp = rewriter.createOrFold<LookupOp>(
                    origOp.getLoc(), mapper.lookupOrDefault(origOp.getOperand()), field.name);
                rewriter.create<YieldOp>(origOp.getLoc(), lookupOp);
              })
              .Default([&](auto origOp) { rewriter.clone(*origOp, mapper); });
        }
      }
      fieldSplitOp->getOpResult(0).setType(field.type);
      splitFields.push_back(fieldSplitOp);
    }

    auto packOp = rewriter.create<PackOp>(op.getLoc(), op.getType(), splitFields);
    rewriter.replaceAllUsesWith(op, packOp);
    return success();
  }
};

// Attempts to to unravel the use of the result of a switch operation returning
// an ArrayType. We generate an additional switch operation with the same
// condition for each element of the array, having the switch operation only
// return that member. Then, we add an array operation to reconstruct the array
// from the individual switch operations.
//
// Constraints are left in the original switch operation for processing by
// SplitSwitchArms, but all uses of the result value are changed to use the
// repacked value.
//
// This requires all operations inside are idempotent, since they may be
// duplicated between array elements.  As such, we verify that all the
// operations are ones are allow before we attempt unravelling.
struct UnravelSwitchArrayResult : public OpRewritePattern<SwitchOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(SwitchOp op, PatternRewriter& rewriter) const final {
    // Don't bother unravelling if we don't need these results
    if (op->use_empty())
      return failure();

    ArrayType ty = dyn_cast<ArrayType>(op.getType());
    if (!ty)
      return failure();

    // Make sure all operations are ones we expect
    for (auto& region : op->getRegions()) {
      for (auto& nestedOp : region.getOps()) {
        if (!isIdempotent(&nestedOp))
          return failure();
      }
    }

    rewriter.setInsertionPointAfter(op);
    SmallVector<Value> splitElements;
    for (size_t i = 0; i < ty.getSize(); i++) {
      Value index = rewriter.create<arith::ConstantOp>(op->getLoc(), rewriter.getIndexAttr(i));
      auto elementSplitOp = rewriter.create<SwitchOp>(
          op.getLoc(), ty.getElement(), op.getSelector(), op.getArms().size());
      for (size_t j = 0; j < op.getArms().size(); j++) {
        OpBuilder::InsertionGuard insertionGuard(rewriter);
        rewriter.createBlock(&elementSplitOp.getArms()[j]);

        IRMapping mapper;
        for (auto& origOp : op.getArms()[j].front()) {
          TypeSwitch<Operation*>(&origOp)
              .Case<EqualZeroOp>([&](auto origOp) {
                // Don't add constraints to any of the copies.
              })
              .Case<IfOp>([&](auto origOp) {
                // If ops can't contribute to the result, so skip them.
              })
              .Case<YieldOp>([&](auto origOp) {
                auto subscriptOp = rewriter.createOrFold<SubscriptOp>(
                    origOp.getLoc(), mapper.lookupOrDefault(origOp.getOperand()), index);
                rewriter.create<YieldOp>(origOp.getLoc(), subscriptOp);
              })
              .Default([&](auto origOp) { rewriter.clone(*origOp, mapper); });
        }
      }
      splitElements.push_back(elementSplitOp);
    }

    auto arrayOp = rewriter.create<ArrayOp>(op.getLoc(), op.getType(), splitElements);
    rewriter.replaceAllUsesWith(op, arrayOp);
    return success();
  }
};

// Attempts to unravel a use of the result of a switch operations returning a val
// by multiplying by each of the selectors and summing the result.
//
// This assumes there's exactly one selector that has a value of 1 and the
// rest are zero.
struct UnravelSwitchValResult : public OpRewritePattern<SwitchOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(SwitchOp op, PatternRewriter& rewriter) const final {
    // Don't bother if we don't need these results
    if (op->use_empty())
      return failure();

    ValType ty = dyn_cast<ValType>(op.getType());
    if (!ty)
      return failure();

    // If there's anything better ot be done like inlining or inner switch operations, deal with
    // those first.
    for (auto& region : op->getRegions()) {
      for (auto& block : region) {
        for (auto& blockOp : block) {
          if (!llvm::isa<PolyOp, EqualZeroOp, YieldOp, IfOp, TerminateOp, LoadOp>(blockOp) &&
              !blockOp.hasTrait<OpTrait::ConstantLike>() && !isPure(&blockOp))
            return failure();
        }
      }
    }

    rewriter.setInsertionPointAfter(op);
    SmallVector<Value> elems;
    for (auto [arm, sel] : llvm::zip_equal(op.getArms(), op.getSelector())) {
      Value selValue = sel;
      IRMapping mapper;
      Value mulOp;
      for (auto& origOp : arm.front()) {
        TypeSwitch<Operation*>(&origOp)
            .Case<EqualZeroOp>([&](auto origOp) {
              // Don't copy constraints; they will stay in the original switch operation.
            })
            .Case<IfOp>([&](auto origOp) {
              // "If" operations don't return anything, so they can't contribute to the result.
            })
            .Case<YieldOp>([&](auto origOp) {
              mulOp = rewriter.createOrFold<Zll::MulOp>(
                  op.getLoc(), mapper.lookupOrDefault(origOp.getOperand()), selValue);
            })
            .Case<LoadOp>([&](auto origOp) {
              auto loadOp = rewriter.clone(*origOp, mapper);
              rewriter.modifyOpInPlace(
                  loadOp, [&]() { loadOp->setAttr("unchecked", rewriter.getAttr<UnitAttr>()); });
            })
            .Default([&](auto origOp) { rewriter.clone(*origOp, mapper); });
      }
      assert(mulOp && "Undable to find yield op in arm");
      elems.push_back(mulOp);
    }
    Value sum;
    for (auto elem : elems) {
      if (sum)
        sum = rewriter.createOrFold<Zll::AddOp>(op.getLoc(), sum, elem);
      else
        sum = elem;
    }
    assert(sum && "Unable to find any arms to sum up");
    rewriter.replaceAllUsesWith(op, sum);
    return success();
  }
};

struct ReplaceYieldWithTerminator : public OpRewritePattern<YieldOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(YieldOp op, PatternRewriter& rewriter) const final {
    if (llvm::isa<IfOp>(op->getParentOp())) {
      rewriter.replaceOpWithNewOp<TerminateOp>(op);
      return success();
    }

    return failure();
  }
};

// Convert zhlt.construct to func.call on the component's "back"
// function.  Assumes it's within a "back" fnuction.
struct ConstructToBack : public OpRewritePattern<Zhlt::ConstructOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(Zhlt::ConstructOp op, PatternRewriter& rewriter) const final {
    auto parent = op->getParentOfType<Zhlt::BackFuncOp>();
    if (!parent) {
      return failure();
    }

    if (op.use_empty()) {
      // TODO: Find a better way to indicate that back functions have no effects.
      op.erase();
      return success();
    }

    auto distance = parent.getDistance();
    auto callee = SymbolTable::lookupNearestSymbolFrom<Zhlt::ComponentOp>(op, op.getCalleeAttr());
    auto callOp = rewriter.create<Zhlt::BackCallOp>(
        op->getLoc(), callee.getSymName(), callee.getOutType(), distance, op.getLayout());
    rewriter.replaceOp(op, callOp);
    return success();
  }
};

// Replace a "Back" inside an execution function to call the back
// function.  Assumes it's within an "exec" or "check" function.
struct BackToCall : public OpRewritePattern<Zhlt::BackOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(Zhlt::BackOp op, PatternRewriter& rewriter) const final {
    // TODO: unify distance types and just call op.getDistanceAttr().
    auto distance = rewriter.create<arith::ConstantOp>(
        op->getLoc(), rewriter.getIndexAttr(op.getDistance().getZExtValue()));
    auto callee = SymbolTable::lookupNearestSymbolFrom<Zhlt::ComponentOp>(op, op.getCalleeAttr());
    auto callOp = rewriter.create<Zhlt::BackCallOp>(
        op->getLoc(), callee.getSymName(), callee.getOutType(), distance, op.getLayout());
    rewriter.replaceOp(op, callOp);
    return success();
  }
};

// Replace a "back" inside a back function to add its distance to the
// parent's.  Assumes it's within a "back$" function.
struct BackBackToCall : public OpRewritePattern<Zhlt::BackOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(Zhlt::BackOp op, PatternRewriter& rewriter) const final {
    auto parent = op->getParentOfType<Zhlt::BackFuncOp>();
    if (!parent) {
      return failure();
    }

    auto oldDistance = parent.getDistance();
    // TODO: unify distance types and just call op.getDistanceAttr().
    auto backOpDistance = rewriter.create<arith::ConstantOp>(
        op->getLoc(), rewriter.getIndexAttr(op.getDistance().getZExtValue()));
    auto callee = SymbolTable::lookupNearestSymbolFrom<Zhlt::ComponentOp>(op, op.getCalleeAttr());
    auto distance = rewriter.create<arith::AddIOp>(op->getLoc(), oldDistance, backOpDistance);
    auto callOp = rewriter.create<Zhlt::BackCallOp>(
        op->getLoc(), callee.getSymName(), callee.getOutType(), distance, op.getLayout());
    rewriter.replaceOp(op, callOp);
    return success();
  }
};

// Replace a "load" inside a back function to get the distance from the enclosing function.
// Assumes it's within a "back$" function.
struct AddLoadDistance : public OpRewritePattern<LoadOp> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(LoadOp op, PatternRewriter& rewriter) const final {
    if (llvm::isa<BlockArgument>(op.getDistance())) {
      // Already attached to parent BackFuncOp.
      return failure();
    }
    auto parent = op->getParentOfType<Zhlt::BackFuncOp>();
    if (!parent) {
      return failure();
    }
    assert(parent.getSymName().starts_with("back$"));
    auto distanceArg = parent.getDistance();
    rewriter.startOpModification(op);
    op.getDistanceMutable().assign(distanceArg);
    rewriter.finalizeOpModification(op);
    return success();
  }
};

/// Analyse all components to see which ones are accessed using
/// zhlt.back, both directly and transitively.
class BacksNeededAnalysis {
public:
  BacksNeededAnalysis(ModuleOp module) {
    SmallVector<Zhlt::ComponentOp> added;

    // Find which components call zhlt.back directly
    module.walk([&](Zhlt::BackOp backOp) {
      auto symName = backOp.getCalleeAttr().getAttr();
      auto [it, didInsert] = backsNeeded.try_emplace(symName);
      it->second.insert(backOp);
      if (didInsert) {
        added.push_back(module.lookupSymbol<Zhlt::ComponentOp>(symName));
      }
    });

    // Any components which were called by zhlt.back also need to have
    // back functions generated for all their subcomponents.
    while (!added.empty()) {
      SmallVector<Zhlt::ComponentOp> newAdded;

      for (auto component : added) {
        component.walk([&](Zhlt::ConstructOp construct) {
          auto symName = construct.getCalleeAttr().getAttr();
          auto [it, didInsert] = backsNeeded.try_emplace(symName);
          it->second.insert(construct);
          if (didInsert) {
            newAdded.push_back(module.lookupSymbol<Zhlt::ComponentOp>(symName));
          }
        });
      }

      added = std::move(newAdded);
    }
  }

  bool backNeeded(Zhlt::ComponentOp component) {
    if (!component.getLayoutType() && !component.getConstructParamTypes().empty()) {
      // No need to generate back functions for components without registers.
      return false;
    }
    return backsNeeded.contains(component.getSymNameAttr());
  }

  const DenseSet<Operation*>& getUses(Zhlt::ComponentOp component) {
    return backsNeeded[component.getSymNameAttr()];
  }

private:
  DenseMap<StringAttr, DenseSet<Operation*>> backsNeeded;
};

struct GenerateBackPass : public GenerateBackBase<GenerateBackPass> {
  void runOnOperation() override {
    auto* ctx = &getContext();
    auto& backsNeeded = getAnalysis<BacksNeededAnalysis>();

    RewritePatternSet patterns(ctx);
    patterns.insert<EraseOp<StoreOp>>(ctx);
    patterns.insert<EraseOp<ExternOp>>(ctx);
    patterns.insert<EraseOp<Zhlt::MagicOp>>(ctx);
    patterns.insert<EraseOp<EqualZeroOp>>(ctx);
    patterns.insert<ConstructToBack>(ctx);
    patterns.insert<BackBackToCall>(ctx);
    patterns.insert<AddLoadDistance>(ctx);
    patterns.insert<ArrayMapToRangeMap>(ctx);
    FrozenRewritePatternSet frozenPatterns(std::move(patterns));

    OpBuilder builder(ctx);
    // Generate "back" functions
    getOperation()->walk([&](Zhlt::ComponentOp op) {
      if (!backsNeeded.backNeeded(op)) {
        return;
      }

      builder.setInsertionPoint(op);

      auto layoutType = op.getLayoutType();
      auto valType = op.getResultType();
      auto distanceType = builder.getIndexType();

      // Start out with the old function signature and copy in the block
      auto func =
          builder.create<Zhlt::BackFuncOp>(op->getLoc(), op.getSymName(), valType, layoutType);

      IRMapping mapping;
      op.getBody().cloneInto(&func.getBody(), mapping);

      // Now strip it down to just the distance and layout arguments.
      // Replace other arguments with MagicOps, which should go away
      // at the end of the lowering.
      Block* block = &func.getBody().front();
      // arg0 = exec context, arg1 = back distance, arg2 = optional layout
      size_t numValArgs = op.getConstructParam().size();
      builder.setInsertionPointToStart(block);
      for (auto constructArg : op.getConstructParam()) {
        auto valArg = mapping.lookup(constructArg);
        auto magic = builder.create<Zhlt::MagicOp>(op.getLoc(), valArg.getType());
        valArg.replaceAllUsesWith(magic);
      }
      block->eraseArguments(0u, numValArgs);
      block->insertArgument(0u, distanceType, op->getLoc());
      // arg1 = back distance, arg2 = optional layout
      assert(block->getNumArguments() == 1 || block->getNumArguments() == 2);

      if (applyPatternsAndFoldGreedily(func, frozenPatterns).failed()) {
        auto diag = func->emitError()
                    << "Unable to generate `back' function; required by the following locations:";
        for (auto usedBy : backsNeeded.getUses(op)) {
          diag.attachNote(usedBy->getLoc()) << "here";
        }

        signalPassFailure();
      }
    });
  }
};

struct GenerateExecPass : public GenerateExecBase<GenerateExecPass> {
  void runOnOperation() override {
    auto* ctx = &getContext();

    RewritePatternSet patterns(ctx);
    patterns.insert<ConstructToCall>(ctx);
    patterns.insert<BackToCall>(ctx);
    if (circuitNdebug)
      patterns.insert<EraseOp<EqualZeroOp>>(ctx);
    FrozenRewritePatternSet frozenPatterns(std::move(patterns));

    OpBuilder builder(ctx);
    // Transform ComponentOps into exec functions.
    getOperation().walk([&](Zhlt::ComponentOp op) {
      builder.setInsertionPoint(op);

      auto func = builder.create<Zhlt::ExecFuncOp>(op->getLoc(),
                                                   op.getName(),
                                                   op.getOutType(),
                                                   op.getConstructParamTypes(),
                                                   op.getLayoutType());
      IRMapping mapping;
      op.getBody().cloneInto(&func.getBody(), mapping);

      if (applyPatternsAndFoldGreedily(func, frozenPatterns).failed()) {
        func->emitError("Could not generate back function");
        signalPassFailure();
      }
    });
  }
};

// Transform ComponentOps into constraint-checking functions.
struct GenerateCheckPass : public GenerateCheckBase<GenerateCheckPass> {
  void
  generateCheckFunc(OpBuilder& builder, StringRef checkFuncName, ArrayRef<StringAttr> callees) {
    MLIRContext* ctx = builder.getContext();
    RewritePatternSet patterns(ctx);
    patterns.insert<InlineCheckConstruct>(ctx);
    patterns.insert<BackToCall>(ctx);
    patterns.insert<EraseOp<StoreOp>>(ctx);
    patterns.insert<EraseOp<VariadicPackOp>>(ctx);
    patterns.insert<EraseOp<ExternOp>>(ctx);
    patterns.insert<EraseOp<AliasLayoutOp>>(ctx);
    patterns.insert<EraseOp<Zhlt::MagicOp>>(ctx);
    patterns.insert<InlineCalls>(ctx);
    patterns.insert<SplitSwitchArms>(ctx);
    patterns.insert<ReplaceYieldWithTerminator>(ctx);
    ZStruct::SwitchOp::getCanonicalizationPatterns(patterns, ctx);
    ZStruct::getUnrollPatterns(patterns, ctx);
    Zll::EqualZeroOp::getCanonicalizationPatterns(patterns, ctx);

    // Only try these if nothing else work, since they cause a lot of duplication.
    patterns.insert<UnravelSwitchPackResult>(ctx, /*benefit=*/0);
    patterns.insert<UnravelSwitchArrayResult>(ctx, /*benefit=*/0);
    patterns.insert<UnravelSwitchValResult>(ctx, /*benefit=*/0);

    FrozenRewritePatternSet frozenPatterns(std::move(patterns));

    OpBuilder::InsertionGuard guard(builder);
    auto checkFuncOp = builder.create<Zhlt::CheckFuncOp>(builder.getUnknownLoc(), checkFuncName);
    builder.setInsertionPointToStart(checkFuncOp.addEntryBlock());

    for (auto callee : callees) {
      builder.create<func::CallOp>(builder.getUnknownLoc(), callee, /*results=*/TypeRange{});
    }

    // Now, inline everything and get rid of everything that's not a constraint.
    builder.create<Zhlt::ReturnOp>(builder.getUnknownLoc());
    GreedyRewriteConfig config;
    config.maxIterations = 100;
    if (applyPatternsAndFoldGreedily(checkFuncOp, frozenPatterns, config).failed()) {
      checkFuncOp->emitError("Could not generate check function");
      signalPassFailure();
    }
  }

  void runOnOperation() override {
    auto* ctx = &getContext();

    OpBuilder builder(ctx);
    mlir::ModuleOp mod = getOperation();
    builder.setInsertionPointToEnd(mod.getBody());

    std::map</*checkFuncName=*/std::string, /*callees=*/SmallVector<StringAttr>> checkFuncs;

    mod.walk([&](Zhlt::StepFuncOp op) {
      // Generate a circuit-wide constraint checker, plus one for teach t3est.
      StringRef stepName = op.getName();
      std::string checkName;
      if (stepName.consume_front("step$test$")) {
        stepName.consume_back("$accum");
        checkName = ("test$" + stepName).str();
      }

      checkFuncs[checkName].push_back(op.getSymNameAttr());
    });

    for (const auto& [name, callees] : checkFuncs) {
      generateCheckFunc(builder, name, callees);
    }
  }
};

struct GenerateValidityRegsPass : public GenerateValidityRegsBase<GenerateValidityRegsPass> {
  Value runOnBlock(Location loc,
                   Block& block,
                   OpBuilder& builder,
                   IRMapping& mapper,
                   Value state,
                   Value polyMixArg) {
    for (Operation& origOp : block.without_terminator()) {
      Location opLoc = origOp.getLoc();
      if (opLoc != loc)
        opLoc = CallSiteLoc::get(loc, origOp.getLoc());

      TypeSwitch<Operation*>(&origOp)
          .Case<EqualZeroOp>([&](EqualZeroOp op) {
            auto oldIn = op.getIn();
            if (!mapper.contains(oldIn)) {
              // A previous error may have resulted in this invalid state
              op.emitError("Invalid state for MakePolynomial");
              signalPassFailure();
              return;
            }
            auto newIn = mapper.lookup(oldIn);
            state = builder.create<AndEqzOp>(opLoc, state, newIn);
          })
          .Case<IfOp>([&](IfOp op) {
            Value innerState = builder.create<TrueOp>(opLoc);
            innerState =
                runOnBlock(opLoc, op.getInner().front(), builder, mapper, innerState, polyMixArg);
            state = builder.create<AndCondOp>(opLoc, state, mapper.lookup(op.getCond()), innerState)
                        .getResult();
          })
          // Polynomial and structural ops just get passed through
          .Case<Zhlt::BackOp,
                GetBufferOp,
                SwitchOp,
                PolyOp,
                LookupOp,
                SubscriptOp,
                LoadOp,
                PackOp,
                ArrayOp,
                BindLayoutOp,
                arith::ConstantOp,
                arith::AddIOp>([&](auto op) {
            OpBuilder::InsertionGuard guard(builder);
            if (llvm::isa<LoadOp, LookupOp, SubscriptOp>(op.getOperation()))
              builder.setInsertionPointToStart(builder.getBlock());
            builder.clone(origOp, mapper);
          })
          .Default([&](Operation* op) {
            llvm::errs() << *op;
            op->emitError("Invalid op for MakePolynomial");
            signalPassFailure();
          });
    }
    return state;
  }

  void runOnOperation() override {
    auto module = getOperation();

    module.walk([&](Zhlt::CheckFuncOp checkFunc) {
      OpBuilder builder(checkFunc);
      if (checkFunc.getSymName() != "check$")
        return;
      auto func = builder.create<Zhlt::ValidityRegsFuncOp>(
          checkFunc.getLoc(),
          "validity_regs",
          builder.getFunctionType({builder.getType<PolyMixType>()},
                                  {builder.getType<ConstraintType>()}),
          /*argNames=*/ArrayRef<StringRef>({"polyMix"}));
      Block* block = func.addEntryBlock();
      Value polyMix = block->getArgument(0);
      IRMapping mapper;
      builder.setInsertionPointToStart(block);
      Value mixState = builder.create<TrueOp>(func.getLoc());
      mixState = runOnBlock(
          checkFunc.getLoc(), checkFunc.getBody().front(), builder, mapper, mixState, polyMix);
      builder.create<Zhlt::ReturnOp>(func.getLoc(), mixState);
      sortTopologically(builder.getBlock());
    });
  }
};

using NamedTap = std::tuple</*bufferName=*/StringRef, /*offset=*/size_t, /*back=*/size_t>;

struct TapifyLoadOp : public OpRewritePattern<LoadOp> {
  TapifyLoadOp(MLIRContext* ctx, Interpreter& interp, DenseMap<NamedTap, Value>& tapIndex)
      : OpRewritePattern(ctx), interp(interp), tapIndex(tapIndex) {}

  LogicalResult matchAndRewrite(LoadOp op, PatternRewriter& rewriter) const final {
    BoundLayoutAttr ref = interp.evaluateConstantOfType<BoundLayoutAttr>(op.getRef());
    if (!ref) {
      op->emitError("couldn't evaluate reference");
      return failure();
    }

    auto distAttr = interp.evaluateConstantOfType<IntegerAttr>(op.getDistance());
    if (!distAttr) {
      op->emitError("couldn't evaluate distance");
      return failure();
    }
    size_t distance = getIndexVal(distAttr);

    auto namedTap =
        NamedTap{ref.getBuffer(), llvm::cast<RefAttr>(ref.getLayout()).getIndex(), distance};
    if (tapIndex.contains(namedTap)) {
      rewriter.replaceOp(op, tapIndex.lookup(namedTap));
      return success();
    } else {
      return failure();
    }
  }

private:
  Interpreter& interp;
  DenseMap<NamedTap, Value>& tapIndex;
};

struct GenerateValidityTapsPass : public GenerateValidityTapsBase<GenerateValidityTapsPass> {
  void runOnOperation() override {
    auto module = getOperation();
    auto ctx = module.getContext();
    OpBuilder builder(ctx);
    auto bufs = Zll::lookupModuleAttr<Zll::BuffersAttr>(module);
    auto tapsOp = module.lookupSymbol<GlobalConstOp>(Zhlt::getTapsConstName());
    if (!tapsOp) {
      return;
    }
    ArrayAttr taps = cast<ArrayAttr>(tapsOp.getConstant());
    auto groupNames =
        llvm::map_to_vector(bufs.getTapBuffers(), [&](auto bufDesc) { return bufDesc.getName(); });

    module.walk([&](Zhlt::ValidityRegsFuncOp regsFunc) {
      builder.setInsertionPoint(regsFunc);
      auto func = builder.create<Zhlt::ValidityTapsFuncOp>(
          regsFunc.getLoc(),
          "validity_taps",
          builder.getFunctionType({/*taps=*/builder.getType<BufferType>(Zhlt::getValExtType(ctx),
                                                                        taps.size(),
                                                                        Zll::BufferKind::Constant),
                                   builder.getType<PolyMixType>()},
                                  {builder.getType<ConstraintType>()}),
          ArrayRef<StringRef>({"taps", "polyMix"}));
      builder.setInsertionPointToStart(func.addEntryBlock());
      auto tapsArg = func.getArgument(0);
      auto polyMixArg = func.getArgument(1);

      // This AttrTypeReplacer extends all field elements to extension
      // field elements, whether they be in types or attributes.
      size_t extSize = Zhlt::getValExtType(ctx).getFieldK();
      AttrTypeReplacer extendFieldTypes;
      // Leave layout types alone; they will be discarded in the final
      // output after all the tap locations have been evaluated.
      extendFieldTypes.addReplacement(
          [&](LayoutType t) { return std::make_pair(t, WalkResult::skip()); });
      extendFieldTypes.addReplacement(
          [&](RefType t) { return std::make_pair(t, WalkResult::skip()); });
      extendFieldTypes.addReplacement(
          [&](BufferType t) { return std::make_pair(t, WalkResult::skip()); });
      extendFieldTypes.addReplacement([&](ValType t) { return Zhlt::getValExtType(ctx); });
      extendFieldTypes.addReplacement([&](PolynomialAttr attr) {
        SmallVector<uint64_t> elems = llvm::to_vector(attr.asArrayRef());
        elems.resize(extSize, 0);
        return PolynomialAttr::get(ctx, elems);
      });

      // Store which refs are in which tap indexes.
      DenseMap<NamedTap, Value> tapIndex;
      size_t ntaps = 0;
      for (auto tap : taps) {
        auto tapRef = cast<TapAttr>(tap);
        auto namedTap =
            NamedTap{groupNames[tapRef.getRegGroupId()], tapRef.getOffset(), tapRef.getBack()};
        assert(!tapIndex.contains(namedTap));
        tapIndex[namedTap] = builder.create<Zll::GetOp>(regsFunc.getLoc(),
                                                        tapsArg,
                                                        /*offset=*/ntaps++,
                                                        /*back=*/0,
                                                        /*tap=*/mlir::IntegerAttr{});
      }
      assert(ntaps == taps.size());

      IRMapping mapper;
      mapper.map(/*polyMix=*/regsFunc.getArgument(0), polyMixArg);
      for (auto& op : regsFunc.getBody().front())
        builder.clone(op, mapper);

      Interpreter interp(ctx);
      RewritePatternSet patterns(ctx);
      patterns.insert<TapifyLoadOp>(ctx, interp, tapIndex);
      FrozenRewritePatternSet frozenPatterns(std::move(patterns));
      if (applyPatternsAndFoldGreedily(func, frozenPatterns).failed()) {
        auto diag = func->emitError("Unable to generate `verify taps' function");
        signalPassFailure();
        return;
      }

      // Convert field elements and NondetRegs to extension field elements in all types.
      extendFieldTypes.recursivelyReplaceElementsIn(
          func, /*replaceAttrs=*/true, /*replaceLocs=*/false, /*replaceTypes=*/true);

      // Re-infer types on any load-ops, since we may have changed their return types
      func.walk([&](ZStruct::LoadOp loadOp) { reinferReturnType(loadOp); });

      // Elminate dead code referring to old layout.
      IRRewriter rewriter(builder);
      DominanceInfo domInfo;
      bool changed = true;
      while (changed) {
        eliminateCommonSubExpressions(rewriter, domInfo, func, &changed);
      }
    });
  }
};

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateBackPass() {
  return std::make_unique<GenerateBackPass>();
}

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateExecPass() {
  return std::make_unique<GenerateExecPass>();
}

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateCheckPass() {
  return std::make_unique<GenerateCheckPass>();
}

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateValidityRegsPass() {
  return std::make_unique<GenerateValidityRegsPass>();
}

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateValidityTapsPass() {
  return std::make_unique<GenerateValidityTapsPass>();
}

} // namespace dsl
} // namespace zirgen
