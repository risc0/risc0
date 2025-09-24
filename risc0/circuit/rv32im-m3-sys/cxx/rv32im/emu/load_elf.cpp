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

#include "rv32im/emu/load_elf.h"
#include "core/log.h"
#include "rv32im/emu/expand.h"

#define CONSTANT constexpr
#include "rv32im/base/constants.h"

namespace risc0::rv32im {

void fillExpandTable(std::map<uint32_t, uint32_t>& words) {
  auto table = generateExpandTable();
  // Load table into ELF
  for (size_t i = 0; i < 65536; i++) {
    words[COMPRESSED_INST_LOOKUP_WORD + i] = table[i];
  }
}

void loadWithKernel(std::map<uint32_t, uint32_t>& words,
                    const std::string& kernelElf,
                    const std::string& userElf) {
  auto kernelElfBytes = risc0::loadFile(kernelElf);
  auto userElfBytes = risc0::loadFile(userElf);
  // Set MEPC so MRET jumpts to start of user mode code
  uint32_t userEntry = risc0::loadElf(ArrayRef(userElfBytes.data(), userElfBytes.size()),
                                      words,
                                      ZERO_PAGE_END_WORD,
                                      KERNEL_START_WORD);
  words[MEPC_WORD] = userEntry - 4;
  // Put start info into the memory image
  uint32_t kernelEntry = risc0::loadElf(ArrayRef(kernelElfBytes.data(), kernelElfBytes.size()),
                                        words,
                                        KERNEL_START_WORD,
                                        KERNEL_END_WORD);
  words[SUSPEND_PC_WORD] = kernelEntry;
  words[SUSPEND_MODE_WORD] = 1;
  // Load expansion table
  fillExpandTable(words);
}

void loadRaw(std::map<uint32_t, uint32_t>& words, const std::string& elf) {
  auto elfBytes = risc0::loadFile(elf);

  loadRawBytes(words, ArrayRef(elfBytes.data(), elfBytes.size()));
}

void loadRawBytes(std::map<uint32_t, uint32_t>& words, const ArrayRef<uint8_t>& elfBytes) {
  uint32_t entry = risc0::loadElf(elfBytes, words, ZERO_PAGE_END_WORD, KERNEL_END_WORD);
  words[SUSPEND_PC_WORD] = entry;
  words[SUSPEND_MODE_WORD] = 1;
  // Load expansion table
  fillExpandTable(words);
}

} // namespace risc0::rv32im
