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

struct EcallTerminateWitness {
  uint32_t cycle;
  FetchWitness fetch;
  RegMemReadWitness a7;
  RegMemReadWitness a0;
  RegMemReadWitness a1;
  PhysMemReadWitness output[8];
};

struct EcallReadWitness {
  uint32_t cycle;
  uint32_t finalCycle;
  FetchWitness fetch;
  RegMemReadWitness a7;
  RegMemReadWitness a1;
  RegMemReadWitness a2;
  RegMemWriteWitness a0;
};

struct EcallWriteWitness {
  uint32_t cycle;
  FetchWitness fetch;
  RegMemReadWitness a7;
  RegMemReadWitness a2;
  RegMemWriteWitness a0;
};

struct EcallBigIntWitness {
  uint32_t cycle;
  FetchWitness fetch;
  RegMemReadWitness a7;
  RegMemReadWitness t0;
  RegMemReadWitness t2;
  uint32_t count;
};
