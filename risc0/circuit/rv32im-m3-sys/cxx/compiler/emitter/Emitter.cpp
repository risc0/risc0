// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include "compiler/emitter/Emitter.h"
#include "zirgen/Main/Utils.h"

#include "zirgen/circuit/verify/wrap_zirgen.h"
#include "zirgen/compiler/codegen/codegen.h"
#include "zirgen/dsl/passes/Passes.h"
#include "zirgen/Dialect/ZHLT/Transforms/Passes.h"
#include "zirgen/Dialect/ZStruct/Transforms/Passes.h"

using namespace mlir;
using namespace zirgen;

LogicalResult translateToCheckFunc(ModuleOp mod) {
  PassManager pm(mod.getContext());
  // Generate layout
  // TODO: does this give the right field ordering guarantees in the layout? It works in this case!
  pm.addPass(dsl::createGenerateCheckLayoutPass());
  pm.addPass(dsl::createGenerateLayoutPass());

  // Generate check function
  pm.addPass(dsl::createGenerateExecPass()); // Weirdly, the step func needs this
  pm.addPass(Zhlt::createAnalyzeBuffersPass());
  pm.addPass(Zhlt::createGenerateStepsPass());
  pm.addPass(dsl::createGenerateCheckPass());
  auto& checkPasses = pm.nest<Zhlt::CheckFuncOp>();
  checkPasses.addPass(ZStruct::createInlineLayoutPass());
  if (failed(pm.run(mod))) {
    llvm::errs() << "Failed to generate check function\n";
    return failure();
  }

  // Clean up unnecessary intermediates for the check function
  mod.walk([&](Zhlt::ComponentOp x) { x->erase(); });
  mod.walk([&](Zhlt::StepFuncOp x) { x->erase(); });
  mod.walk([&](Zhlt::ExecFuncOp x) { x->erase(); });
  mod.walk([&](Zhlt::CheckLayoutFuncOp x) { x->erase(); });
  mod.walk([&](ZStruct::GlobalConstOp x) { x->erase(); });

  return success();
}

void emitRustVerifierCode(ModuleOp mod, std::string circuitName, std::string protocolInfo) {
  auto circuitNameAttr = Zll::lookupModuleAttr<Zll::CircuitNameAttr>(mod);
  emitPoly(mod, circuitName, protocolInfo);
  emitTarget(
      RustCodegenTarget(circuitNameAttr), mod, mod, codegen::getRustCodegenOpts());
  }
