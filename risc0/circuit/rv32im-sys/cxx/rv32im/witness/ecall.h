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

#include "rv32im/base/poseidon2.h"
#include "rv32im/witness/decode.h"

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct EcallTerminateWitness {
  uint32_t cycle;
  FetchWitness fetch;
  RegMemReadWitness a7;
  RegMemReadWitness a0;
  RegMemReadWitness a1;
  PhysMemReadWitness output[8];
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct EcallReadWitness {
  uint32_t cycle;
  uint32_t finalCycle;
  FetchWitness fetch;
  RegMemReadWitness a7;
  RegMemReadWitness a1;
  RegMemReadWitness a2;
  RegMemWriteWitness a0;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct EcallWriteWitness {
  uint32_t cycle;
  FetchWitness fetch;
  RegMemReadWitness a7;
  RegMemReadWitness a2;
  RegMemWriteWitness a0;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct P2State {
  uint32_t cycle;
  uint8_t isElem;
  uint8_t isCheck;
  uint16_t count;
  uint32_t inWordAddr;
  uint32_t outWordAddr;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct P2StepWitness {
  P2State state;
  Fp stateIn[CELLS_DIGEST];
  Fp stateOut[CELLS_DIGEST];
  PhysMemReadWitness dataIn[CELLS_RATE];
  PhysMemWriteWitness dataOut[CELLS_DIGEST];
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct EcallP2Witness {
  uint32_t cycle;
  FetchWitness fetch;
  RegMemReadWitness a0;
  RegMemReadWitness a1;
  RegMemReadWitness a2;
  RegMemReadWitness a3;
  RegMemReadWitness a7;
  PhysMemReadWitness stateIn[CELLS_DIGEST];
  PhysMemWriteWitness stateOut[CELLS_DIGEST];
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct EcallBigIntWitness {
  uint32_t cycle;
  FetchWitness fetch;
  RegMemReadWitness a7;
  RegMemReadWitness t0;
  RegMemReadWitness t2;
  uint32_t count;
};
