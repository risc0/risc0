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

#include "rv32im/circuit/decode.h"
#include "rv32im/circuit/is_zero.h"
#include "rv32im/witness/sys.h"

// A 'resume' instruction reads the PC and the machine mode
// and initiates normal executions, always occurs on cycle 1
template <typename C> struct InstResumeBlock {
  CONSTANT static char NAME[] = "InstResumeBlock";

  PhysMemReadBlock<C> readV2Compat;
  PhysMemReadBlock<C> readPc;
  PhysMemReadBlock<C> readMode;
  PhysMemWriteBlock<C> writeVersion;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, readV2Compat, 1);
    T::apply(ctx, readPc, 1);
    T::apply(ctx, readMode, 1);
    T::apply(ctx, writeVersion, 1);
  }

  FDEV void set(CTX, InstResumeWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

// A 'suspend' instruction writes the PC and machine mode and
// terminates execution.
template <typename C> struct InstSuspendBlock {
  CONSTANT static char NAME[] = "InstSuspendBlock";

  Reg<C> cycle;
  Reg<C> iCacheCycle;
  PhysMemWriteBlock<C> writePc;
  PhysMemWriteBlock<C> writeMode;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, writePc, cycle.get());
    T::apply(ctx, writeMode, cycle.get());
  }

  FDEV void set(CTX, InstSuspendWitness) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct InstTrapBlock {
  CONSTANT static char NAME[] = "InstTrapBlock";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  OneHot<C, 4> trapType;
  Reg<C> rs1;
  Reg<C> rs2;
  Reg<C> rd;
  PhysMemWriteBlock<C> writePc;
  PhysMemWriteBlock<C> writeMode;
  PhysMemWriteBlock<C> writeVal;
  PhysMemReadBlock<C> readDispatch;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, fetch, cycle.get());
    T::apply(ctx, writePc, cycle.get());
    T::apply(ctx, writeMode, cycle.get());
    T::apply(ctx, writeVal, cycle.get());
    T::apply(ctx, readDispatch, cycle.get());
  }

  FDEV void set(CTX, InstTrapWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};

template <typename C> struct InstMretBlock {
  CONSTANT static char NAME[] = "InstMretBlock";

  Reg<C> cycle;
  FetchBlock<C> fetch;
  PhysMemReadBlock<C> readPc;
  PhysMemReadBlock<C> readMode;
  Reg<C> toAdd;
  AddU32<C> sumPc;
  PhysMemWriteBlock<C> updateClearCache;
  Reg<C> iCacheCycleOut;

  template <typename T> FDEV void applyInner(CTX) DEV {
    T::apply(ctx, cycle);
    T::apply(ctx, fetch, cycle.get());
    T::apply(ctx, readPc, cycle.get());
    T::apply(ctx, readMode, cycle.get());
    T::apply(ctx, toAdd);
    T::apply(ctx, sumPc, readPc.data.get(), ValU32<C>(toAdd.get(), 0));
    T::apply(ctx, updateClearCache, cycle.get());
    T::apply(ctx, iCacheCycleOut);
  }

  FDEV void set(CTX, InstMretWitness wit) DEV;
  FDEV inline void finalize(CTX) DEV {}

  FDEV void verify(CTX) DEV;
  FDEV void addArguments(CTX) DEV;
};
