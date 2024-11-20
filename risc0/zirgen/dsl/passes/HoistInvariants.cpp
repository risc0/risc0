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

#include "mlir/Transforms/LoopInvariantCodeMotionUtils.h"
#include "zirgen/Dialect/ZStruct/Transforms/RewritePatterns.h"
#include "zirgen/dsl/passes/CommonRewrites.h"
#include "zirgen/dsl/passes/PassDetail.h"

using namespace zirgen::ZStruct;

namespace zirgen {
namespace dsl {

namespace {

size_t moveInvariantCode(Operation* parentOp) {
  SmallVector<Region*> regions;
  for (auto& reg : parentOp->getRegions()) {
    regions.push_back(&reg);
  }
  return moveLoopInvariantCode(
      regions,
      [&](Value value, Region*) {
        return !parentOp->isAncestor(value.getParentRegion()->getParentOp());
      },
      [&](Operation* op, Region*) { return isMemoryEffectFree(op) && isSpeculatable(op); },
      [&](Operation* op, Region*) { op->moveBefore(parentOp); });
}

} // namespace

struct HoistInvariantsPass : public HoistInvariantsBase<HoistInvariantsPass> {
  void runOnOperation() override {
    getOperation()->walk([&](Operation* op) {
      if (llvm::isa<SwitchOp, Zll::IfOp, MapOp, ReduceOp>(op))
        moveInvariantCode(op);
    });
  }
};

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createHoistInvariantsPass() {
  return std::make_unique<HoistInvariantsPass>();
}

} // namespace dsl
} // namespace zirgen
