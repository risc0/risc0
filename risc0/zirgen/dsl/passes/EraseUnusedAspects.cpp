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

#include "zirgen/dsl/passes/PassDetail.h"

using namespace mlir;

namespace zirgen::dsl {

namespace {

struct EraseUnusedAspectsPass : public EraseUnusedAspectsBase<EraseUnusedAspectsPass> {
  EraseUnusedAspectsPass(bool forTests) : forTests(forTests) {}

  void runOnOperation() override {
    if (forTests) {
      getOperation().walk([&](Operation* op) {
        // keep steps and execs, except for Top
        if (isa<Zhlt::ComponentOp>(op) || isa<Zhlt::CheckLayoutFuncOp>(op) ||
            isa<Zhlt::ValidityRegsFuncOp>(op) || isa<Zhlt::ValidityTapsFuncOp>(op)) {
          op->erase();
          return;
        }
        auto step = dyn_cast<Zhlt::StepFuncOp>(op);
        if (step && step.getName() == "step$Top") {
          step->erase();
          return;
        }
      });
    }
  }

  bool forTests;
};

} // namespace

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createEraseUnusedAspectsPass(bool forTests) {
  return std::make_unique<EraseUnusedAspectsPass>(forTests);
}

} // namespace zirgen::dsl
