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

#include <cstdint>

namespace risc0::rv32im {

enum class Opcode : uint8_t {
#define ENTRY(name, ...) name,
#include "rv32im/base/rv32im.inc"
#undef ENTRY
  INVALID,
};

inline const char* getOpcodeName(Opcode opcode) {
  switch (opcode) {
#define ENTRY(name, ...)                                                                           \
  case Opcode::name:                                                                               \
    return #name;
#include "rv32im/base/rv32im.inc"
#undef ENTRY
  default:
    return "***UNKNOWN***";
  }
}

// Decomposed instruction
struct DecodedInst {
  DecodedInst() = default;
  DecodedInst(uint32_t inst)
      : inst(inst)
      , topBit((inst & 0x80000000) >> 31)
      , func7((inst & 0xfe000000) >> 25)
      , rs2((inst & 0x01f00000) >> 20)
      , rs1((inst & 0x000f8000) >> 15)
      , func3((inst & 0x00007000) >> 12)
      , rd((inst & 0x00000f80) >> 7)
      , opcode((inst & 0x0000007f)) {}

  uint32_t inst;
  uint32_t topBit;
  uint32_t func7;
  uint32_t rs2;
  uint32_t rs1;
  uint32_t func3;
  uint32_t rd;
  uint32_t opcode;
  uint32_t immB() const {
    return (topBit * 0xfffff000) | ((rd & 1) << 11) | ((func7 & 0x3f) << 5) | (rd & 0x1e);
  }
  uint32_t immI() const { return (topBit * 0xfffff000) | (func7 << 5) | rs2; }
  uint32_t immIL() const { return rs2; }
  uint32_t immS() const { return (topBit * 0xfffff000) | (func7 << 5) | rd; }
  uint32_t immJ() const {
    return (topBit * 0xfff00000) | (rs1 << 15) | (func3 << 12) | ((rs2 & 1) << 11) |
           ((func7 & 0x3f) << 5) | (rs2 & 0x1e);
  }
  uint32_t immU() const { return inst & 0xfffff000; }
  uint32_t immR() const { return 0; }
};

Opcode getOpcode(const DecodedInst& inst);

} // namespace risc0::rv32im
