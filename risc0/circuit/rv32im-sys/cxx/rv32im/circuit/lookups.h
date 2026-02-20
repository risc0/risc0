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

#include "rv32im/base/base.h"
#include "rv32im/witness/lookups.h"

// A register that is constrained to be [0, 255]
template <typename C> struct RegU8 {
  CONSTANT static char NAME[] = "RegU8";

  Reg<C> inner;

  template <typename T> FDEV void applyInner(CTX) DEV { T::apply(ctx, "inner", inner); }

  FDEV void set(CTX, Val<C> in) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV Val<C> get() DEV;
  FDEV void verify(CTX) DEV { RANGE_POSTCONDITION(ctx, 0, inner.get(), (1 << 8)); }
  FDEV void addArguments(CTX) DEV;
};

template <typename C> FDEV void assertU16(CTX, Val<C> val);

// A register that is constrained to be [0, 65535]
template <typename C> struct RegU16 {
  CONSTANT static char NAME[] = "RegU16";

  Reg<C> inner;

  template <typename T> FDEV void applyInner(CTX) DEV { T::apply(ctx, "inner", inner); }

  FDEV void set(CTX, Val<C> in) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV Val<C> get() DEV;
  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};

// A thing that generates table entries
template <typename C> struct MakeTableBlock {
  CONSTANT static char NAME[] = "MakeTableBlock";

  Reg<C> table;
  Reg<C> start;
  ArgCountReg<C> useCount[16];

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "table", table);
    T::apply(ctx, "start", start);
    T::apply(ctx, "useCount", useCount);
  }

  FDEV void set(CTX, MakeTableWitness wit) DEV;
  FDEV void finalize(CTX) DEV;
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};
