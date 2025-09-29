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

#include "mlir/IR/Verifier.h"

int main() {
    using C = RecordingContext;
    mlir::MLIRContext mlirCtx;
    RecordingContext ctx(&mlirCtx);
    RecordingVal::setContext(&ctx);

    ctx.enterComponent("IsZero");
    Val<C> x = ctx.addValParameter();
    IsZero<C> component;
    mlir::Type layoutType = getLayoutType(ctx, component, x);
    component.verify(ctx, x);
    ctx.materializeLayout(layoutType);
    ctx.exitComponent();

    ctx.getModuleOp().print(llvm::outs());
    return failed(mlir::verify(ctx.getModuleOp()));
}
