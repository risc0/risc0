// Copyright 2025 RISC Zero, Inc.
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

#include "compiler/extractor/base.h"

#include "rv32im/base/base.h"

#include "mlir/IR/Verifier.h"

template<typename C>
struct Top {
  CONSTANT static char NAME[] = "TestTop";

  Reg<C> array[4];

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, array);
  }

  FDEV void set(CTX, Fp val) DEV {}
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX, Val<C> val) DEV {}
};

int main() {
    using C = RecordingContext;
    mlir::MLIRContext mlirCtx;
    RecordingContext ctx(&mlirCtx);
    RecordingVal::setContext(&ctx);

    ctx.enterComponent("Top");
    Top<C> component;
    mlir::Type layoutType = getLayoutType(ctx, component);
    llvm::outs() << "Layout type: " << layoutType << "\n";
    component.verify(ctx);
    ctx.materializeLayout(layoutType);
    ctx.exitComponent();

    ctx.getModuleOp().print(llvm::outs());
    return failed(mlir::verify(ctx.getModuleOp()));
}
