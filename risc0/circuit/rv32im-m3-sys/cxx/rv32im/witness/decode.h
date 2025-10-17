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

#include "rv32im/witness/mem.h"

struct FetchWitness {
  uint32_t mode;
  uint32_t iCacheCycle;
  uint32_t pc;
  uint32_t nextPc;
};

struct DecodeWitness {
  uint32_t opcode;
  FetchWitness fetch;
  uint32_t loadCycle;
  VirtMemReadWitness load0;
  VirtMemReadWitness load1;
  uint32_t inst;
  uint32_t count;
};
