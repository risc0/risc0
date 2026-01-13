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

#include "compiler/extractor/PicusDirectives.h"
#include "compiler/extractor/RecordingVal.h"
#include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"

using namespace mlir;

void PicusDeclareInputVisitor::apply(RecordingContext& ctx, RecordingVal& x) {
  OpBuilder& builder = *BuilderSingleton::get();
  SmallVector<Value> args = {x.value};
  builder.create<zirgen::Zhlt::DirectiveOp>(builder.getUnknownLoc(), "PicusInput", args);
}

void rangePrecondition(RecordingContext& ctx, uint32_t low, RecordingVal x, uint32_t high) {
  OpBuilder& builder = *BuilderSingleton::get();
  Value lowConst = builder.create<zirgen::Zll::ConstOp>(builder.getUnknownLoc(), low);
  Value highConst = builder.create<zirgen::Zll::ConstOp>(builder.getUnknownLoc(), high);
  SmallVector<Value> args = {lowConst, x.value, highConst};
  builder.create<zirgen::Zhlt::DirectiveOp>(builder.getUnknownLoc(), "AssumeRange", args);
}

void rangePostcondition(RecordingContext& ctx, uint32_t low, RecordingVal x, uint32_t high) {
  OpBuilder& builder = *BuilderSingleton::get();
  Value lowConst = builder.create<zirgen::Zll::ConstOp>(builder.getUnknownLoc(), low);
  Value highConst = builder.create<zirgen::Zll::ConstOp>(builder.getUnknownLoc(), high);
  SmallVector<Value> args = {lowConst, x.value, highConst};
  builder.create<zirgen::Zhlt::DirectiveOp>(builder.getUnknownLoc(), "AssertRange", args);
}

void picusCall(RecordingContext& ctx,
               const char* name,
               llvm::ArrayRef<RecordingVal> inputs,
               mlir::Value layout) {
  mlir::OpBuilder& builder = *BuilderSingleton::get();
  auto compType = zirgen::Zhlt::getComponentType(ctx.mlirCtx);
  llvm::SmallVector<mlir::Value> arguments;
  for (auto val : inputs) {
    arguments.push_back(val.value);
  }
  builder.create<zirgen::Zhlt::ConstructOp>(
      builder.getUnknownLoc(), name, compType, arguments, layout);
}

void picusArgument(RecordingContext& ctx,
                   llvm::ArrayRef<Value> inputs,
                   llvm::ArrayRef<Value> outputs) {
  OpBuilder& builder = *BuilderSingleton::get();
  Location loc = builder.getUnknownLoc();

  llvm::SmallVector<mlir::Value> operands;
  operands.append(inputs.begin(), inputs.end());
  operands.append(outputs.begin(), outputs.end());
  auto dir = builder.create<zirgen::Zhlt::DirectiveOp>(loc, "PicusDeterministicIf", operands);
  dir->setAttr("input_count", builder.getUI32IntegerAttr(inputs.size()));
}
