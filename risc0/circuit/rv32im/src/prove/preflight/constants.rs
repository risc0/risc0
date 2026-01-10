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

// Very basic numbers
pub const WORD_SIZE: u32 = 4;
pub const BITS_PER_BYTE: u32 = 8;
pub const BYTES_PER_WORD_PO2: u32 = 2;
pub const BYTES_PER_WORD: u32 = 1 << BYTES_PER_WORD_PO2;

// Physical Merkle Paging constants
pub const MPAGE_SIZE_BYTES_PO2: u32 = 10;
pub const MPAGE_SIZE_BYTES: u64 = 1 << MPAGE_SIZE_BYTES_PO2;
pub const MPAGE_MASK_BYTES: u64 = MPAGE_SIZE_BYTES - 1;
pub const MPAGE_SIZE_WORDS_PO2: u32 = MPAGE_SIZE_BYTES_PO2 - BYTES_PER_WORD_PO2;
pub const MPAGE_SIZE_WORDS: u64 = MPAGE_SIZE_BYTES / BYTES_PER_WORD as u64;
pub const MPAGE_MASK_WORDS: u64 = MPAGE_SIZE_WORDS - 1;
pub const MPAGE_PART_SIZE: u32 = 8;

// Logical MMU Paging constants
pub const VPAGE_SIZE_BYTES_PO2: u32 = 12;
pub const VPAGE_SIZE_BYTES: u64 = 1 << VPAGE_SIZE_BYTES_PO2;
pub const VPAGE_MASK_BYTES: u64 = VPAGE_SIZE_BYTES - 1;
pub const VPAGE_SIZE_WORDS_PO2: u32 = VPAGE_SIZE_BYTES_PO2 - BYTES_PER_WORD_PO2;
pub const VPAGE_SIZE_WORDS: u64 = VPAGE_SIZE_BYTES / BYTES_PER_WORD as u64;
pub const VPAGE_MASK_WORDS: u64 = VPAGE_SIZE_WORDS - 1;

// Versioning constants
pub const RV32IM_SEAL_VERSION: u32 = 3;
pub const RV32IM_CIRCUIT_VERSION: u32 = 3;

// Memory constants
pub const PAGE_SIZE_BYTES: u64 = 1024;
pub const MEMORY_SIZE_BYTES: u64 = 1u64 << 32;
pub const MEMORY_SIZE_WORDS: u64 = MEMORY_SIZE_BYTES / BYTES_PER_WORD as u64;
pub const MEMORY_SIZE_MPAGES: u64 = MEMORY_SIZE_BYTES / MPAGE_SIZE_BYTES;

// Mode constants
pub const MODE_USER: u32 = 0;
pub const MODE_SUPERVISOR: u32 = 1;
pub const MODE_MACHINE: u32 = 3;

// Various memory mapped things
pub const MACHINE_REGS_ADDR: u32 = 0xffff0000;
pub const MACHINE_REGS_WORD: u32 = MACHINE_REGS_ADDR / BYTES_PER_WORD;
pub const USER_REGS_ADDR: u32 = 0xffff0080;
pub const USER_REGS_WORD: u32 = USER_REGS_ADDR / BYTES_PER_WORD;
pub const CSR_BASE_ADDR: u32 = 0xffff4000;
pub const CSR_BASE_WORD: u32 = CSR_BASE_ADDR / BYTES_PER_WORD;
pub const OUTPUT_ADDR: u32 = 0xffff0240;
pub const OUTPUT_WORD: u32 = OUTPUT_ADDR / 4;
pub const INPUT_ADDR: u32 = 0xffff0260;
pub const INPUT_WORD: u32 = INPUT_ADDR / 4;
pub const P2_ZEROS_ADDR: u32 = 0xffff0280;
pub const P2_ZEROS_WORD: u32 = P2_ZEROS_ADDR / 4;
pub const P2_TRASH_ADDR: u32 = 0xffff02a0;
pub const P2_TRASH_WORD: u32 = P2_TRASH_ADDR / 4;
pub const TRAP_DISPATCH_ADDR: u32 = 0xffff2000;
pub const TRAP_DISPATCH_WORD: u32 = TRAP_DISPATCH_ADDR / 4;
pub const COMPRESSED_INST_LOOKUP_ADDR: u32 = 0xfff80000;
pub const COMPRESSED_INST_LOOKUP_WORD: u32 = COMPRESSED_INST_LOOKUP_ADDR / BYTES_PER_WORD;
