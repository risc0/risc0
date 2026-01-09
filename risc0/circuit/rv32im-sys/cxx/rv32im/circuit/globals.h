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

#include "rv32im/circuit/poseidon2.h"
#include "rv32im/witness/globals.h"

template <typename C> struct GlobalsBlock {
  CONSTANT static char NAME[] = "GlobalsBlock";

  RegDigest<C> rootIn;
  RegDigest<C> rootOut;
  Reg<C> p2Count;
  Reg<C> finalCycle;
  Reg<C> finalCycleCeilDiv;
  RegU16<C> ceilDivLow;
  RegU8<C> ceilDivHigh;
  RegU8<C> delta;
  RegU8<C> deltaTimes32;
  RegU32<C> povwNonce[8];

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, "rootIn", rootIn);
    T::apply(ctx, "rootOut", rootOut);
    T::apply(ctx, "p2Count", p2Count);
    T::apply(ctx, "finalCycle", finalCycle);
    T::apply(ctx, "finalCycleCeilDiv", finalCycleCeilDiv);
    T::apply(ctx, "ceilDivLow", ceilDivLow);
    T::apply(ctx, "ceilDivHigh", ceilDivHigh);
    T::apply(ctx, "delta", delta);
    T::apply(ctx, "deltaTimes32", deltaTimes32);
    T::apply(ctx, "povwNonce", povwNonce);
  }

  FDEV void set(CTX, GlobalsWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};
