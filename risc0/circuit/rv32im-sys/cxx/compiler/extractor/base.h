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

#pragma once

#include "compiler/extractor/LayoutBuilderVisitor.h"
#include "compiler/extractor/PicusDirectives.h"
#include "compiler/extractor/PopulateComponentVisitor.h"
#include "compiler/extractor/RecordingContext.h"
#include "compiler/extractor/RecordingVal.h"
#include "zkp/fp.h"
#include "zkp/fpext.h"

#include <type_traits>

using namespace risc0;

#define PICUS
#define PICUS_INPUT(ctx, x) picusInput(ctx, x)
#define RANGE_PRECONDITION(ctx, low, x, high) rangePrecondition(ctx, low, x, high)
#define RANGE_POSTCONDITION(ctx, low, x, high) rangePostcondition(ctx, low, x, high)
#define PICUS_ARGUMENT(ctx, inputs, outputs)                                                       \
  {                                                                                                \
    llvm::SmallVector<mlir::Value> inputsVec inputs;                                               \
    llvm::SmallVector<mlir::Value> outputsVec outputs;                                             \
    picusArgument(ctx, inputsVec, outputsVec);                                                     \
  }
#define PICUS_CALL(ctx, name, inputs, layout)                                                      \
  {                                                                                                \
    llvm::SmallVector<RecordingVal> inputsVec{inputs};                                             \
    picusCall(ctx, name, inputsVec, layout);                                                       \
  }

#define PICUS_BEGIN_OUTLINE(...)                                                                   \
  if (NAME != ctx.componentName) {                                                                 \
    llvm::SmallVector<RecordingVal> inputsVec{__VA_ARGS__};                                        \
    picusCall(ctx, NAME, inputsVec, ctx.get(*this));                                               \
  } else {
#define PICUS_END_OUTLINE }
