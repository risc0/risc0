// Copyright 2026 RISC Zero, Inc.
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

#include "rv32im/base/base.h"

#include "mlir/IR/Verifier.h"

template <typename C> struct Top {
  CONSTANT static char NAME[] = "TestTop";

  Reg<C> array[4];

  template <typename T> FDEV void applyInner(CTX) DEV { T::apply(ctx, "array", array); }

  FDEV void set(CTX, Fp val) DEV {}
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX, Val<C> val) DEV {}
};

int main() {
  using C = RecordingContext;
  mlir::MLIRContext mlirCtx;
  RecordingContext ctx(&mlirCtx);
  RecordingReg::setContext(&ctx);
  BuilderSingleton::set(&ctx.builder);

  extract<Top>(ctx);

  ctx.getModuleOp().print(llvm::outs());
  return failed(mlir::verify(ctx.getModuleOp()));
}
