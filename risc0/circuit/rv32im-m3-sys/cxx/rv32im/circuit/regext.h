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

#include "rv32im/base/base.h"

template <typename C> struct RegExt {
  CONSTANT static char NAME[] = "RegExt";

  Reg<C> elems[4];

  template <typename T> FDEV void applyInner(CTX) DEV { T::apply(ctx, "elems", elems); }

  FDEV void set(CTX, ValExt<C> val) DEV {
    for (size_t i = 0; i < 4; i++) {
      elems[i].set(ctx, val.elem(i));
    }
  }
  FDEV ValExt<C> get() DEV {
    return ValExt<C>(elems[0].get(), elems[1].get(), elems[2].get(), elems[3].get());
  }
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV {}
};
