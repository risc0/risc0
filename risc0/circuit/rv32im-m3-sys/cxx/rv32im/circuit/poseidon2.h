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

#include "rv32im/circuit/one_hot.h"
#include "rv32im/witness/poseidon2.h"

template <typename C> using RegCells = Reg<C>[CELLS];

template <typename C> using RegDigest = Reg<C>[CELLS_DIGEST];

template <typename C> struct P2ExtRoundBlock {
  CONSTANT static char NAME[] = "P2ExtRoundBlock";

  Reg<C> id;
  OneHot<C, 8> round;
  RegCells<C> inputs;
  RegCells<C> sBoxTmp;
  RegCells<C> outputs;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, id);
    T::apply(ctx, round);
    T::apply(ctx, inputs);
    T::apply(ctx, sBoxTmp);
    T::apply(ctx, outputs);
  }

  FDEV void set(CTX, P2ExtRoundWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct P2IntRoundsBlock {
  CONSTANT static char NAME[] = "P2IntRoundsBlock";

  Reg<C> id;
  RegCells<C> inputs;
  Reg<C> sBoxT1[ROUNDS_PARTIAL];
  Reg<C> sBoxT2[ROUNDS_PARTIAL];
  RegCells<C> outputs;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, id);
    T::apply(ctx, inputs);
    T::apply(ctx, sBoxT1);
    T::apply(ctx, sBoxT2);
    T::apply(ctx, outputs);
  }

  FDEV void set(CTX, P2IntRoundsWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct P2BlockBlock {
  CONSTANT static char NAME[] = "P2BlockBlock";

  Reg<C> id;
  ArgCountReg<C> outUseCount;
  ArgCountReg<C> contUseCount;
  RegCells<C> inputs;
  RegCells<C> outputs;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, id);
    T::apply(ctx, outUseCount);
    T::apply(ctx, contUseCount);
    T::apply(ctx, inputs);
    T::apply(ctx, outputs);
  }

  FDEV void set(CTX, P2BlockWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV;
};
