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

#include "rv32im/emu/expand.h"

#include <assert.h>

namespace risc0::rv32im {

namespace {
// Setup some heavy syntactic sugar to make implementing spec not horrible to read

// Bit range
class B {
public:
  // Single bit constructor
  B(uint32_t bit) : bits(bit), size(1) {}
  // Multi bit constructor
  B(uint32_t bits, uint32_t size) : bits(bits), size(size) {}
  // Single bit extraction
  B operator()(uint32_t pos) const {
    assert(pos < size);
    return B((bits >> pos) & 1, 1);
  }
  // Extract range of bits, inclusive, upper first (like spec docs)
  B operator()(uint32_t upper, uint32_t lower) const {
    assert(upper < size);
    assert(lower < size);
    assert(upper > lower);
    uint32_t newSize = upper - lower + 1;
    uint32_t mask = (uint32_t(1) << newSize) - 1;
    return B((bits >> lower) & mask, newSize);
  }
  // Concatenate two bit ranges
  B  operator|(const B& rhs) const {
    return B(bits << rhs.size | rhs.bits, size + rhs.size);
  }

  uint32_t bits;
  uint32_t size;
};

// Map compressed register to uncompressed register
B UR(B in) {
  assert(in.size == 3);
  return B(in.bits + 8, 5);
}

// Get sign + optionally expand it to multiple bits
B SE(B in, uint32_t size = 1) {
  uint32_t signBit = in.bits >> (in.size - 1);
  uint32_t mask = (uint32_t(1) << size) - 1;
  return B(mask * signBit, size);
}

// Make loops look nice
class BIter {
public:
  BIter(uint32_t bits, uint32_t size, uint32_t step) : bits(bits), size(size), step(step) {}
  B operator*() { return B(bits, size); }
  void operator++() { bits += step; }
  bool operator!=(BIter rhs) { return bits != rhs.bits; }

  uint32_t bits;
  uint32_t size;
  uint32_t step;
};

class Loop {
public:
  Loop(uint32_t size, uint32_t step=1) : size(size), step(step) {}
  BIter begin() const { return BIter(0, size, step); }
  BIter end() const { return BIter((uint32_t(1) << size), size, step); }

  uint32_t size;
  uint32_t step;
};

uint32_t EXPANSION_TABLE[] = {
#include "expand.inc"
};


} // namespace

std::vector<uint32_t> generateExpandTable() {
  std::vector<uint32_t> table(1 << 16);
  auto addEntry = [&](B compressed, B uncompressed) {
    assert(compressed.size == 16);
    assert(uncompressed.size == 32);
    table[compressed.bits] = uncompressed.bits;
  };
  // TODO: Replace precomputed table with full translation
  // Load in initial table for now until we fully implement spec
  for (size_t i = 0; i < 65536; i++) {
    table[i] = EXPANSION_TABLE[i];
  }
  // Jumps
  for (auto imm : Loop(12, 2)) {
    // c.JL -> JAL rd = 1
    addEntry(
        // 001 | imm[11|4|9:8|10|6|7|3:1|5] | 01
        B(0b001, 3) | imm(11) | imm(4) | imm(9,8) | imm(10) | imm(6) | imm(7) | imm(3, 1) | imm(5) | B(0b01, 2),
        // imm[20|10:1|11|19:12] | rd = 1 | 1101111
        SE(imm) | imm(10, 1) | imm(11) | SE(imm, 8) | B(1, 5) | B(0b1101111, 7)
    );
    // c.J -> JAL rd = 0
    addEntry(
        // 101 | imm[11|4|9:8|10|6|7|3:1|5] | 01
        B(0b101, 3) | imm(11) | imm(4) | imm(9,8) | imm(10) | imm(6) | imm(7) | imm(3, 1) | imm(5) | B(0b01, 2),
        // imm[20|10:1|11|19:12] | rd = 0 | 1101111
        SE(imm) | imm(10, 1) | imm(11) | SE(imm, 8) | B(0, 5) | B(0b1101111, 7)
    );
  }
  // Branches
  for (auto imm : Loop(9, 2)) {
    for (auto rs1 : Loop(3)) {
      // c.BEQZ -> BEQ rs2 = 0
      addEntry(
          // 110 | imm[8|4:3] | rs1' | imm[7:6|2:1|5] | 01
          B(0b110, 3) | imm(8) | imm(4, 3) | rs1 | imm(7, 6) | imm(2, 1) | imm(5) | B(0b01, 2),
          // imm[12|10:5] | rs2 = 0 | rs1 | func3 = 000 | imm[4:1|11] | 1100011
          SE(imm, 3) | imm(8, 5) | B(0, 5) | UR(rs1) | B(0, 3) | imm(4, 1) | SE(imm) | B(0b1100011, 7)
      );
      // c.BNEZ -> BNE rs2 = 0
      addEntry(
          // 111 | imm[8|4:3] | rs1' | imm[7:6|2:1|5] | 01
          B(0b111, 3) | imm(8) | imm(4, 3) | rs1 | imm(7, 6) | imm(2, 1) | imm(5) | B(0b01, 2),
          // imm[12|10:5] | rs2 = 0 | rs1 | func3 = 001 | imm[4:1|11] | 1100011
          SE(imm, 3) | imm(8, 5) | B(0, 5) | UR(rs1) | B(1, 3) | imm(4, 1) | SE(imm) | B(0b1100011, 7)
      );
    }
  }
  return table;
}

}  // namespace risc0::rv32im
