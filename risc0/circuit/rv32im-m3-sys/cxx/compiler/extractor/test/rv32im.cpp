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

#include "compiler/extractor/base.h"
#include "rv32im/circuit/circuit.ipp"
#include "zirgen/compiler/picus/picus.h"

#include "mlir/IR/Verifier.h"

int main() {
  using C = RecordingContext;
  mlir::MLIRContext mlirCtx;
  RecordingContext ctx(&mlirCtx);
  RecordingReg::setContext(&ctx);
  BuilderSingleton::set(&ctx.builder);

  extract1<IsZero>(ctx);

  // EXTRACT(IsZero);
  // EXTRACT(UnitAddSubBlock);
  // EXTRACT(UnitBitBlock);
  // EXTRACT(UnitMulBlock);
  EXTRACT(UnitDivBlock);

// #define BLOCK_TYPE(name, count) EXTRACT(name##Block)
//   BLOCK_TYPES
// #undef BLOCK_TYPE

  if (failed(mlir::verify(ctx.getModuleOp()))) {
    llvm::errs() << "Module verification error\n";
    return 1;
  }

  llvm::outs() << ctx.getModuleOp() << "\n\n";
  printPicus(ctx.getModuleOp(), llvm::outs());

  // llvm::outs() << "(begin-module UnitArgument)\n"
  //                 "(input a_low)\n"
  //                 "(input a_high)\n"
  //                 "(input b_low)\n"
  //                 "(input b_high)\n"
  //                 "(output out_low)\n"
  //                 "(output out_high)\n"
  //                 "(end-module)\n";
  return 0;
}
