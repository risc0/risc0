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

#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/Transforms/TopologicalSortUtils.h"
#include "zirgen/dsl/passes/PassDetail.h"
#include "llvm/ADT/TypeSwitch.h"

#include "zirgen/Dialect/Zll/IR/IR.h"

using namespace mlir;

namespace zirgen::dsl {

namespace {

struct TopologicalShufflePass : public TopologicalShuffleBase<TopologicalShufflePass> {
  void moveUsesBefore(Operation* op, Operation* beforeOp, Block* origBlock) {
    while (op->getBlock() != origBlock) {
      op = op->getParentOp();
      if (!op)
        return;
    }
    op->moveBefore(beforeOp);

    op->walk([&](Operation* subOp) {
      for (Operation* userOp : subOp->getUsers()) {
        moveUsesBefore(userOp, beforeOp, origBlock);
      }
    });
  }
  void runOnOperation() override {
    getOperation()->walk([&](Block* block) {
      Block* newBlock = new Block;
      auto termOp = block->getTerminator();
      termOp->moveBefore(newBlock, newBlock->end());
      while (!block->empty()) {
        Operation* op = &block->front();

        moveUsesBefore(op, termOp, block);
      }
      newBlock->insertBefore(block);
      block->erase();

      sortTopologically(newBlock);
    });
  }
};

} // End namespace

std::unique_ptr<Pass> createTopologicalShufflePass() {
  return std::make_unique<TopologicalShufflePass>();
}

} // namespace zirgen::dsl
