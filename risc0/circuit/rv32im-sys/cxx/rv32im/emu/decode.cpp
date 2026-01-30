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

#include "rv32im/emu/decode.h"

#include <vector>

namespace risc0::rv32im {

namespace {

class FastDecodeTable {
public:
  FastDecodeTable() {
    table.resize(1 << 10, Opcode::INVALID);
    addRV32IM();
  }

  Opcode lookup(const DecodedInst inst) const {
    if ((inst.opcode & 0x3) != 3) {
      return Opcode::INVALID;
    }
    // Annoyingly MRET doesn't fit in the 10 bit table
    if (inst.inst == 0x30200073) {
      return Opcode::MRET;
    }
    // ECALL technically fits, but f7 being 0 isn't sufficient
    if (inst.inst == 0x00000073) {
      return Opcode::ECALL;
    }
    return table[map10(inst.opcode, inst.func3, inst.func7)];
  }

private:
  std::vector<Opcode> table;

  // Map to 10 bit format
  static inline uint32_t map10(uint32_t opcode, uint32_t func3, uint32_t func7) {
    uint32_t opHigh = opcode >> 2;
    // Map 0 -> 0, 1 -> 1, 0x20 -> 2, everything else to 3
    uint32_t func72bits = (func7 <= 1 ? func7 : (func7 == 0x20 ? 2 : 3));
    return (opHigh << 5) | (func72bits << 3) | func3;
  }

  void addInst(uint32_t opcode, int32_t func3, int32_t func7, Opcode inst) {
    // Annoyingly MRET doesn't fit in the 10 bit table
    if (inst == Opcode::MRET) {
      return;
    }
    // ECall is also special cased
    if (inst == Opcode::ECALL) {
      return;
    }
    uint32_t opHigh = opcode >> 2;
    if (func3 < 0) {
      for (uint32_t f3 = 0; f3 < 8; f3++) {
        for (uint32_t f7b = 0; f7b < 4; f7b++) {
          table[(opHigh << 5) | (f7b << 3) | f3] = inst;
        }
      }
      return;
    }
    if (func7 < 0) {
      for (uint32_t f7b = 0; f7b < 4; f7b++) {
        table[(opHigh << 5) | (f7b << 3) | func3] = inst;
      }
      return;
    }
    table[map10(opcode, func3, func7)] = inst;
  }

  void addRV32IM() {
#define XF7 -1
#define XF3 -1
#define ENTRY(name, idx, opcode, immType, func3, func7, ...)                                       \
  addInst(opcode, func3, func7, Opcode::name);
#include "rv32im/base/rv32im.inc"
#undef ENTRY
#undef XF3
#undef XF7
  }
};

FastDecodeTable gDecode;

} // namespace

Opcode getOpcode(const DecodedInst& inst) {
  return gDecode.lookup(inst);
}

} // namespace risc0::rv32im
