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

#include "rv32im/circuit/bits.h"

// A widget holds a value from [0..N-1] as N bits, exactly one
// of which is set
template <typename C, size_t N> struct OneHot {
#define _NAME(N) "OneHot<" #N ">"
  CONSTANT static char NAME[] = _NAME(N);
#undef _NAME

  BitReg<C> bits[N];

  template <typename T> FDEV void applyInner(CTX) DEV { T::apply(ctx, bits); }

  FDEV void set(CTX, uint32_t val) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV Val<C> get() DEV;
  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV {}
};

template <typename C, size_t N, size_t M> struct TwoHot {
#define _NAME(N, M) "OneHot<" #N ", " #M ">"
  CONSTANT static char NAME[] = _NAME(N, M);
#undef _NAME

  OneHot<C, N> major;
  OneHot<C, M> minor;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, major);
    T::apply(ctx, minor);
  }

  FDEV void set(CTX, uint32_t val) DEV;
  FDEV inline void finalize(CTX) DEV {}
  FDEV Val<C> get() DEV;
  FDEV Val<C> at(uint32_t offset) DEV;
  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV {}
};
