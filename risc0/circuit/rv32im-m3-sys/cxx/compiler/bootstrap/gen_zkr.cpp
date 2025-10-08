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

#include "compiler/bootstrap/extract_zkr.h"
#include "zirgen/compiler/codegen/codegen.h"

namespace cl = llvm::cl;

static cl::opt<std::string>
    outputDir("output-dir", cl::desc("Output directory"), cl::value_desc("dir"), cl::Required);


int main(int argc, char* argv[]) {
  llvm::InitLLVM y(argc, argv);
  zirgen::registerEdslCLOptions();
  llvm::cl::ParseCommandLineOptions(argc, argv, "rv32im-m3 predicates");

  zirgen::Module module;
  size_t po2 = 12;
  risc0::addLift(module, po2);  // TODO: Loop here
  module.optimize();
  // module.dump(true);
  module.getModule().walk([&](mlir::func::FuncOp func) { zirgen::emitRecursion(outputDir, func); });
}
