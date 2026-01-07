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

#include "RecordingVal.h"
#include "compiler/extractor/RecordingContext.h"

class PicusDeclareInputVisitor {
public:
  template <typename T, typename... Args>
  static void apply(RecordingContext& ctx, const char* memberName, T& t, Args... args) {
    PicusDeclareInputVisitor::apply(ctx, t, args...);
  }

  template <typename T, typename... Args>
  static void apply(RecordingContext& ctx, T& t, Args... args) {
    t.template applyInner<PicusDeclareInputVisitor>(ctx, args...);
  }

  template <typename T, size_t N> static void apply(RecordingContext& ctx, T (&t)[N]) {
    for (size_t i = 0; i < N; i++) {
      PicusDeclareInputVisitor::apply(ctx, t[i]);
    }
  }

  static void apply(RecordingContext& ctx, RecordingReg& x) {
    PicusDeclareInputVisitor::apply(ctx, x.val);
  }

  static void apply(RecordingContext& ctx, RecordingVal& x);
};

template <typename Component> void picusInput(RecordingContext& ctx, Component component) {
  PicusDeclareInputVisitor::apply(ctx, component);
}

// Emit an `AssumeRange` directive into the IR. This will result in assuptions
// in the generated picus code that the value is in the given range, which means
// that Picus will assume that condition for its proof. It will then check any
// callers of this component to make sure that the condition is met before
// concluding that the output is deterministic. This should primarily be used
// as a hint to Picus that a value is range checked by the caller.
void rangePrecondition(RecordingContext& ctx, uint32_t low, RecordingVal x, uint32_t high);

// Emit an `AssertRange` directive into the IR. This constrains the given value
// to be in the indicated range, the same as an assertion from a polynomial
// constraint. This should primarily be used on registers that are range checked.
void rangePostcondition(RecordingContext& ctx, uint32_t low, RecordingVal x, uint32_t high);

// Emit a constructor call to the indicated component constructor with the given
// (flattened) list of inputs, which constrains the given componentLayout.
//
// Example:
// PICUS_CALL(ctx, "IsZero", {x}, xIsZero);
//
// Zirgen IR:
// %trivial = zhlt.construct @IsZero(%x, %layout) : (!zll.val<BabyBear>, !zlayout$IsZero) ->
// !zstruct$Component
//
// Picus constraint language:
// (call [layout_denomZero_invReg, layout_denomZero_isZero_inner] IsZero [x])
void picusCall(RecordingContext& ctx,
               const char* name,
               llvm::ArrayRef<RecordingVal> inputs,
               mlir::Value layout);

// Emit a `DeterministicIf` directive into the IR. This indicates to Picus that
// if all of the input signals are deterministic, then all of the output signals
// are also deterministic. This is primarily used for arguments where some other
// block force the outputs to be determined by the inputs, but that fact is
// otherwise unclear from only considering the current block.
void picusArgument(RecordingContext& ctx,
                   llvm::ArrayRef<mlir::Value> inputs,
                   llvm::ArrayRef<mlir::Value> outputs);
