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

#include "compiler/extractor/PopulateComponentVisitor.h"

namespace populate_component {

Populator::Populator(RecordingContext& ctx) : builder(ctx.mlirCtx), zero(ctx.zero) {
  builder.setInsertionPointAfterValue(ctx.zero);
  path.push_back(ctx.componentBody->getArguments().back());
}

mlir::Value Populator::lookup(const char* memberName) {
  llvm::outs() << "lookup " << memberName << "\n";
  mlir::Value layout = path.back();
  mlir::StringAttr name = builder.getStringAttr(memberName);
  mlir::Value sublayout =
      builder.create<zirgen::ZStruct::LookupOp>(builder.getUnknownLoc(), layout, name);
  path.push_back(sublayout);
  return sublayout;
}

mlir::Value Populator::subscript(size_t index) {
  mlir::Value layout = path.back();
  auto i = builder.create<mlir::arith::ConstantIndexOp>(builder.getUnknownLoc(), index);
  mlir::Value sublayout =
      builder.create<zirgen::ZStruct::SubscriptOp>(builder.getUnknownLoc(), layout, i);
  path.push_back(sublayout);
  return sublayout;
}

mlir::Value Populator::load() {
  mlir::Value layout = path.back();
  return builder.create<zirgen::ZStruct::LoadOp>(builder.getUnknownLoc(), layout, zero);
}

Populator* PopulatorSingleton::populator;

} // end namespace populate_component
