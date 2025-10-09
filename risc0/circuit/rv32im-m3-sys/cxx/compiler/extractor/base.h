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

#pragma once

#include "compiler/extractor/LayoutBuilderVisitor.h"
#include "compiler/extractor/RecordingContext.h"
#include "compiler/extractor/RecordingVal.h"
#include "zkp/fp.h"
#include "zkp/fpext.h"

using namespace risc0;

struct VerifyFwd {
  template <typename T, typename... Args>
  static void apply(RecordingContext& ctx, T& obj, Args... args) {
    obj.template applyInner<VerifyFwd>(ctx, args...);
    obj.verify(ctx, args...);
  }

  template <typename T, size_t N> static void apply(RecordingContext& ctx, T (&t)[N]) {
    for (size_t i = 0; i < N; i++) {
      VerifyFwd::apply(ctx, t[i]);
    }
  }
};

#define EXTRACT(Comp)                                                                              \
  {                                                                                                \
    ctx.enterComponent(Comp<C>::NAME);                                                             \
    Comp<C> component;                                                                             \
    mlir::Type layoutType = getLayoutType(ctx, component);                                         \
    VerifyFwd::apply(ctx, component);                                                              \
    ctx.materializeLayout(layoutType);                                                             \
    ctx.exitComponent();                                                                           \
  }
