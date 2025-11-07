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

#include "rv32im/witness/decode.h"

struct InstResumeWitness {
  PhysMemReadWitness v2Compat;
  PhysMemReadWitness pc;
  PhysMemReadWitness mode;
  PhysMemWriteWitness version;
  PhysMemWriteWitness writeCycle;
};

struct InstSuspendWitness {
  uint32_t cycle;
  uint32_t iCacheCycle;
  PhysMemWriteWitness pc;
  PhysMemWriteWitness mode;
  PhysMemReadWitness readCycle;
  PhysMemWriteWitness updateTime;
  PhysMemWriteWitness updateTimeH;
};

#define TRAP_ECALL 0
#define TRAP_INST 1
#define TRAP_FETCH 2
#define TRAP_INTER 3

struct InstTrapWitness {
  uint32_t cycle;
  uint32_t trapType;
  FetchWitness fetch;
  PhysMemWriteWitness writePc;
  PhysMemWriteWitness writeMode;
  PhysMemWriteWitness writeVal;
  PhysMemReadWitness readDispatch;
  PhysMemReadWitness readCycle;
  PhysMemWriteWitness updateTime;
  PhysMemWriteWitness updateTimeH;
};

struct InstMretWitness {
  uint32_t cycle;
  FetchWitness fetch;
  PhysMemReadWitness readPc;
  PhysMemReadWitness readMode;
  PhysMemWriteWitness updateClearCache;
  PhysMemWriteWitness writeCycle;
};
