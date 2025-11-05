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

// Verify a value is binary, i.e. in { 0, 1 }
template <typename C> FDEV void AssertBit(CTX, Val<C> val);

// A register which is also constrained to be a bit
template <typename C> struct BitReg {
  CONSTANT static char NAME[] = "BitReg";

  Reg<C> inner;

  template <typename T> FDEV void applyInner(CTX) DEV { T::apply(ctx, "inner", inner); }

  FDEV void set(CTX, Val<C> v) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV Val<C> get() DEV;
  FDEV void verify(CTX) DEV;
  FDEV inline void addArguments(CTX) DEV {}
};

// Choose a or b based on the value of c
template <typename C> inline FDEV Val<C> cond(Val<C> c, Val<C> a, Val<C> b) {
  return c * a + (Val<C>(1) - c) * b;
};
