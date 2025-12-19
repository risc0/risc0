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
#include "compiler/extractor/base.h"

#include "mlir/Transforms/Passes.h"
#include "zirgen/compiler/codegen/codegen.h"
#include "zirgen/compiler/edsl/edsl.h"
#include "llvm/Support/InitLLVM.h"

#include "rv32im/circuit/circuit.ipp"

using namespace zirgen;
namespace cl = llvm::cl;

enum Action {
  RUST,
  ZHLT,
  CHECK,
};

static cl::opt<enum Action>
    emitAction("emit",
               cl::desc("Output of the binary"),
               cl::values(clEnumValN(RUST, "rust", "Emit Rust code for the verifier"),
                          clEnumValN(ZHLT, "zhlt", "Emit basic ZHLT components"),
                          clEnumValN(CHECK, "check", "Emit check function")));

int main(int argc, char** argv) {
  llvm::InitLLVM y(argc, argv);
  registerEdslCLOptions();
  registerCodegenCLOptions();
  llvm::cl::ParseCommandLineOptions(argc, argv, "RISC Zero code emitter");

  // Build a module with the circuit
  Module module;
  using C = RecordingContext;
  RecordingContext ctx(module.getCtx());
  RecordingReg::setContext(&ctx);
  BuilderSingleton::set(&ctx.builder);

#define BLOCK_TYPE(name, count) EXTRACT(name##Block);
  BLOCK_TYPES
#undef BLOCK_TYPE

  // Mark all blocks as entry points
  ctx.getModuleOp().walk([&](zirgen::Zhlt::ComponentOp component) {
    component->setAttr("entry", mlir::UnitAttr::get(ctx.mlirCtx));
  });

  // Clean up the cruft from the initial IR lowering
  mlir::PassManager pm(ctx.mlirCtx);
  pm.addPass(mlir::createCanonicalizerPass());
  if (failed(pm.run(ctx.getModuleOp()))) {
    llvm::errs() << "Failed to run canonicalizer pass\n";
    return 1;
  }

  if (emitAction == ZHLT) {
    ctx.getModuleOp().print(llvm::outs());
    return 0;
  }

  if (failed(translateToCheckFunc(ctx.getModuleOp()))) {
    return 1;
  }

  if (emitAction == CHECK) {
    ctx.getModuleOp().print(llvm::outs());
    return 0;
  }

  if (emitAction == RUST) {
    // Emit code artifacts
    std::string protocolInfo = "ZIRGEN_TEST_____";
    std::string circuitName = "rv32im_v3";
    auto circuitNameAttr = zirgen::Zll::CircuitNameAttr::get(ctx.mlirCtx, circuitName);
    setModuleAttr(ctx.getModuleOp(), circuitNameAttr);
    emitRustVerifierCode(ctx.getModuleOp(), circuitName, protocolInfo);
  }

  return 0;
}
