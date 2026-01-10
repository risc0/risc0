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

// Memory address ranges (really only used for ELF loading?)
pub const USER_START_ADDR: u32 = 0;
pub const USER_START_WORD: u32 = USER_START_ADDR / BYTES_PER_WORD;
pub const USER_END_ADDR: u32 = 0xc0000000;
pub const USER_END_WORD: u32 = USER_END_ADDR / BYTES_PER_WORD;
pub const KERNEL_START_ADDR: u32 = 0xc0000000;
pub const KERNEL_START_WORD: u32 = KERNEL_START_ADDR / BYTES_PER_WORD;
pub const KERNEL_END_ADDR: u32 = 0xff000000;
pub const KERNEL_END_WORD: u32 = KERNEL_END_ADDR / BYTES_PER_WORD;

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

// Functions to get CSR as a word address
pub const fn csr_addr(csr: u32) -> u32 {
    CSR_BASE_ADDR + BYTES_PER_WORD * csr
}
pub const fn csr_word(csr: u32) -> u32 {
    CSR_BASE_WORD + csr
}

// User mode CSRs
pub const CSR_CYCLE: u32 = 0xc00;
pub const CSR_TIME: u32 = 0xc01;
pub const CSR_INSTRET: u32 = 0xc02;
pub const CSR_CYCLEH: u32 = 0xc80;
pub const CSR_TIMEH: u32 = 0xc81;
pub const CSR_INSTRETH: u32 = 0xc82;

// Required supervisory CSRs
pub const CSR_SSTATUS: u32 = 0x100;
pub const CSR_SIE: u32 = 0x104;
pub const CSR_STVEC: u32 = 0x105;
pub const CSR_SCOUNTEREN: u32 = 0x106;
pub const CSR_SENVCFG: u32 = 0x10a;
pub const CSR_SSCRATCH: u32 = 0x140;
pub const CSR_SEPC: u32 = 0x141;
pub const CSR_SCAUSE: u32 = 0x142;
pub const CSR_STVAL: u32 = 0x143;
pub const CSR_SIP: u32 = 0x144;
pub const CSR_SATP: u32 = 0x180;

// Standard machine CSRs we actually use
pub const CSR_MEPC: u32 = 0x341;

// Custom machine CSRs
pub const CSR_MVERSION: u32 = 0x7c0; // Set in V3 (but not V2)
pub const CSR_MSPC: u32 = 0x7c1; // Suspend/Resume PC
pub const CSR_MSMODE: u32 = 0x7c2; // Suspend/Resume Mode
pub const CSR_MTECALL: u32 = 0x7d0; // Trap vector for ecall
pub const CSR_MTEXCEPT: u32 = 0x7d1; // Trap vector for other expections
pub const CSR_MNOV2COMPAT: u32 = 0x7FF; // Turn off V2 compat in global
//
// V2 Compatibility constants
pub const V2_COMPAT_MEPC: u32 = 0xffff0200 / 4;
pub const V2_COMPAT_ECALL_DISPATCH: u32 = 0xffff1000 / 4;
pub const V2_COMPAT_TRAP_DISPATCH: u32 = 0xffff2000 / 4;
pub const V2_COMPAT_SPC: u32 = 0xffff0210 / 4;
pub const V2_COMPAT_SMODE: u32 = 0xffff0214 / 4;
pub const V2_COMPAT_VERSION: u32 = 0xffff0300 / 4;

// Poseidon flags
pub const PFLAG_IS_ELEM: u32 = 0x80000000;
pub const PFLAG_CHECK_OUT: u32 = 0x40000000;
