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

#pragma once

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/Pass.h"

namespace zirgen {
namespace dsl {

// Pass constructors
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>>
createEraseUnusedAspectsPass(bool forTests = false);
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateBackPass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateExecPass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateLayoutPass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateCheckLayoutPass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateCheckPass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateTapsPass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateValidityRegsPass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateValidityTapsPass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateAccumPass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateGlobalsPass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createElideTrivialStructsPass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createInlinePurePass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createFieldDCEPass();
std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createHoistInvariantsPass();
std::unique_ptr<mlir::Pass> createTopologicalShufflePass();

// Generate the code for registering passes.
#define GEN_PASS_REGISTRATION
#include "zirgen/dsl/passes/Passes.h.inc"

} // namespace dsl
} // namespace zirgen
