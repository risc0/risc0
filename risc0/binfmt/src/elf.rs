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

extern crate alloc;

use alloc::{collections::BTreeMap, vec, vec::Vec};

use anyhow::{Context, Result, anyhow, bail, ensure};
use elf::{ElfBytes, endian::LittleEndian, file::Class};
use risc0_zkp::core::{digest::Digest, hash::sha::Impl};
use risc0_zkvm_platform::WORD_SIZE;
use serde::{Deserialize, Serialize};

use crate::{ByteAddr, Digestible as _, KERNEL_START_ADDR, MemoryImage, SystemState};

/// The starting address for user programs in the RISC Zero zkVM.
const USER_START_ADDR: ByteAddr = ByteAddr(0x0001_0000);

const SUSPEND_PC_ADDR: ByteAddr = ByteAddr(0xffff_0210);
const SUSPEND_MODE_ADDR: ByteAddr = ByteAddr(0xffff_0214);

/// A RISC Zero program
pub struct Program {
    /// The entrypoint of the program
    pub(crate) entry: u32,

    /// The initial memory image
    pub(crate) image: BTreeMap<u32, u32>,

    /// Program header table address (where phdrs are loaded in memory)
    pub(crate) phdr_addr: u32,

    /// Number of program headers
    pub(crate) phnum: u32,

    /// Base address of the interpreter
    pub(crate) interp_base_addr: u32,

    /// Address of the interpreter
    pub(crate) interp_addr: u32,

    /// The base address of the brk
    pub(crate) brk: u32,
}

impl Program {
    /// Loads an ELF file for a dynamic program, including the interpreter.
    pub fn load_elf_dyn(input: &[u8], max_mem: u32, interp: &[u8]) -> Result<Program> {
        let mut brk = 0u32;
        let mut image: BTreeMap<u32, u32> = BTreeMap::new();
        let elf = ElfBytes::<LittleEndian>::minimal_parse(input)
            .map_err(|err| anyhow!("Elf parse error: {err}"))?;
        if elf.ehdr.class != Class::ELF32 {
            bail!("Not a 32-bit ELF");
        }
        if elf.ehdr.e_machine != elf::abi::EM_RISCV {
            bail!("Invalid machine type, must be RISC-V");
        }
        if elf.ehdr.e_type != elf::abi::ET_DYN {
            bail!("Invalid ELF type, must be dynamic");
        }
        // ELF_ET_DYN_BASE = (2/3) * TASK_SIZE = (2/3) * 0x9c800000 ≈ 0x68555555
        // → page-align → 0x68555000
        let load_base = 0x68555000u32;

        // Linux page size (4096 bytes), not zkVM PAGE_SIZE (1024 bytes)
        const LINUX_PAGE_SIZE: u32 = 0x1000;
        let entry: u32 = elf
            .ehdr
            .e_entry
            .try_into()
            .map_err(|err| anyhow!("e_entry was larger than 32 bits. {err}"))?;
        if entry >= max_mem || entry % WORD_SIZE as u32 != 0 {
            bail!("Invalid entrypoint");
        }
        let segments = elf
            .segments()
            .ok_or_else(|| anyhow!("Missing segment table"))?;
        if segments.len() > 256 {
            bail!("Too many program headers");
        }
        for segment in segments.iter().filter(|x| x.p_type == elf::abi::PT_LOAD) {
            let file_size: u32 = segment
                .p_filesz
                .try_into()
                .map_err(|err| anyhow!("filesize was larger than 32 bits. {err}"))?;
            if file_size >= max_mem {
                bail!("Invalid segment file_size");
            }
            let mem_size: u32 = segment
                .p_memsz
                .try_into()
                .map_err(|err| anyhow!("mem_size was larger than 32 bits {err}"))?;
            if mem_size >= max_mem {
                bail!("Invalid segment mem_size");
            }
            let p_vaddr: u32 = segment
                .p_vaddr
                .try_into()
                .map_err(|err| anyhow!("vaddr is larger than 32 bits. {err}"))?;

            // Get segment alignment
            let p_align: u32 = segment
                .p_align
                .try_into()
                .map_err(|err| anyhow!("p_align is larger than 32 bits. {err}"))?;
            let p_align = u32::max(p_align, LINUX_PAGE_SIZE);

            // Calculate page offset (where data starts within the page)
            let page_offset = p_vaddr & (p_align - 1);

            // Align segment start down to page boundary, then add load_bias
            let segment_start = (p_vaddr & !(p_align - 1)) + load_base;

            // Actual data starts at segment_start + page_offset
            let vaddr = segment_start + page_offset;

            println!(
                "Segment p_vaddr={:08x}, load_base={:08x}",
                p_vaddr, load_base
            );
            println!(
                "  segment_start={:08x}, data_vaddr={:08x}",
                segment_start, vaddr
            );
            // Note: vaddr may not be word-aligned; we handle this by iterating from segment_start

            let p_offset: u32 = segment
                .p_offset
                .try_into()
                .map_err(|err| anyhow!("offset is larger than 32 bits. {err}"))?;

            // Calculate file offset for the page-aligned segment start
            // The file is also offset by the same page_offset from its page boundary
            let file_segment_start = p_offset - page_offset;

            // Fill entire page-aligned segment region
            let segment_end = segment_start + page_offset + mem_size;
            let total_size = segment_end - segment_start;

            for i in (0..total_size).step_by(WORD_SIZE) {
                let addr = segment_start
                    .checked_add(i)
                    .context("Invalid segment vaddr")?;
                if addr >= max_mem {
                    bail!(
                        "Address [0x{addr:08x}] exceeds maximum address for guest programs [0x{max_mem:08x}]"
                    );
                }

                // Calculate file offset for this address relative to segment_start
                let offset_from_seg_start = (addr - segment_start) as usize;
                let file_offset = (file_segment_start as usize) + offset_from_seg_start;

                // Check if within file data range (page_offset + file_size from segment_start)
                if offset_from_seg_start < (page_offset + file_size) as usize {
                    // Load from file
                    let mut word = 0;
                    let bytes_available =
                        ((page_offset + file_size) as usize) - offset_from_seg_start;
                    let len = core::cmp::min(bytes_available as u32, WORD_SIZE as u32);
                    for j in 0..len {
                        let file_byte_offset = file_offset + (j as usize);
                        let byte = input
                            .get(file_byte_offset)
                            .context("Invalid segment offset")?;
                        word |= (*byte as u32) << (j * 8);
                    }
                    image.insert(addr, word);
                } else {
                    // Zero-fill BSS (beyond page_offset + filesz)
                    image.insert(addr, 0);
                }
            }
            // Compute segment end for brk calculation (data end aligned up)
            let data_end = vaddr + mem_size;
            let segment_end_aligned = (data_end + p_align - 1) & !(p_align - 1);

            println!(
                "Main LOAD: vaddr={:08x}, p_align={:08x}, memsz={:08x}, data_end={:08x}, aligned_end={:08x}",
                vaddr, p_align, mem_size, data_end, segment_end_aligned
            );
            if segment_end_aligned > brk {
                println!(
                    "  -> updating brk from {:08x} to {:08x}",
                    brk, segment_end_aligned
                );
                brk = segment_end_aligned;
            }
        }
        // brk is now already page-aligned from per-segment calculations
        println!("Final main executable brk: {:08x}", brk);

        // Calculate Program Header table address (where phdrs are loaded in memory)
        let mut phdr_addr = 0;
        let phnum = segments.len() as u32;

        // Find which segment contains the Program Header table and calculate its virtual address
        for segment in segments.iter().filter(|x| x.p_type == elf::abi::PT_LOAD) {
            let segment_offset: u32 = segment
                .p_offset
                .try_into()
                .map_err(|err| anyhow!("segment offset is larger than 32 bits. {err}"))?;
            let segment_vaddr: u32 = segment
                .p_vaddr
                .try_into()
                .map_err(|err| anyhow!("segment vaddr is larger than 32 bits. {err}"))?;
            let segment_filesz: u32 = segment
                .p_filesz
                .try_into()
                .map_err(|err| anyhow!("segment filesz is larger than 32 bits. {err}"))?;

            // Check if this segment contains the Program Header table
            let phoff: u32 = elf
                .ehdr
                .e_phoff
                .try_into()
                .map_err(|err| anyhow!("e_phoff is larger than 32 bits. {err}"))?;
            if segment_offset <= phoff && phoff < segment_offset + segment_filesz {
                phdr_addr = phoff - segment_offset + segment_vaddr + load_base;
                break;
            }
        }

        let executable = (load_base + entry, phdr_addr, phnum);

        // Compute top-down DSO arena base (matching Linux's memory layout)
        const TASK_SIZE: u32 = 0x9C80_0000; // User VA ceiling (STACK_TOP / FIXADDR_START)
        const STACK_GAP: u32 = 0x0800_0000; // Stack gap (128 MiB)
        const BIG_ALIGN: u32 = 0x0080_0000; // 8 MiB alignment for mmap_base
        const PAGE: u32 = 0x1000;

        let mmap_base: u32 = (TASK_SIZE - STACK_GAP) & !(BIG_ALIGN - 1); // → 0x94800000

        let elf = ElfBytes::<LittleEndian>::minimal_parse(interp)
            .map_err(|err| anyhow!("Elf parse error: {err}"))?;
        if elf.ehdr.class != Class::ELF32 {
            bail!("Not a 32-bit ELF");
        }
        if elf.ehdr.e_machine != elf::abi::EM_RISCV {
            bail!("Invalid machine type, must be RISC-V");
        }
        if elf.ehdr.e_type != elf::abi::ET_DYN {
            bail!("Invalid ELF type, must be dynamic");
        }

        let entry: u32 = elf
            .ehdr
            .e_entry
            .try_into()
            .map_err(|err| anyhow!("e_entry was larger than 32 bits. {err}"))?;
        if entry >= max_mem || entry % WORD_SIZE as u32 != 0 {
            bail!("Invalid entrypoint");
        }
        let segments = elf
            .segments()
            .ok_or_else(|| anyhow!("Missing segment table"))?;
        if segments.len() > 256 {
            bail!("Too many program headers");
        }

        // Compute interpreter's max virtual extent across all PT_LOAD segments
        println!("\n=== Interpreter Extent Calculation ===");
        let mut interp_max_end = 0u32;
        for segment in segments.iter().filter(|x| x.p_type == elf::abi::PT_LOAD) {
            let p_align: u32 = segment
                .p_align
                .try_into()
                .map_err(|err| anyhow!("p_align is larger than 32 bits. {err}"))?;
            let p_align = u32::max(p_align, PAGE);
            let p_vaddr: u32 = segment
                .p_vaddr
                .try_into()
                .map_err(|err| anyhow!("p_vaddr is larger than 32 bits. {err}"))?;
            let vstart = p_vaddr & !(p_align - 1); // align down
            let mem_size: u32 = segment
                .p_memsz
                .try_into()
                .map_err(|err| anyhow!("p_memsz is larger than 32 bits. {err}"))?;
            let vend = (vstart
                .checked_add(mem_size)
                .context("Invalid segment size")?
                .checked_add(p_align - 1)
                .context("Invalid segment size")?)
                & !(p_align - 1); // align up
            println!(
                "Interp LOAD: p_vaddr={:08x}, p_align={:08x}, vstart={:08x}, memsz={:08x}, vend={:08x}",
                p_vaddr, p_align, vstart, mem_size, vend
            );
            if vend > interp_max_end {
                println!(
                    "  -> updating max_end from {:08x} to {:08x}",
                    interp_max_end, vend
                );
                interp_max_end = vend;
            }
        }
        println!("Interp max extent: {:08x}", interp_max_end);

        // Place interpreter so its top ends exactly at mmap_base (top-down placement)
        let load_bias = mmap_base
            .checked_sub(interp_max_end)
            .context("Not enough VA space for interpreter")?;
        println!(
            "Placing interpreter: mmap_base={:08x} - max_extent={:08x} = load_bias={:08x}",
            mmap_base, interp_max_end, load_bias
        );
        println!(
            "Interpreter will occupy: {:08x} - {:08x}\n",
            load_bias,
            load_bias + interp_max_end
        );

        println!("=== Loading Interpreter Segments ===");
        for segment in segments.iter().filter(|x| x.p_type == elf::abi::PT_LOAD) {
            let file_size: u32 = segment
                .p_filesz
                .try_into()
                .map_err(|err| anyhow!("filesize was larger than 32 bits. {err}"))?;
            if file_size >= max_mem {
                bail!("Invalid segment file_size");
            }
            let mem_size: u32 = segment
                .p_memsz
                .try_into()
                .map_err(|err| anyhow!("mem_size was larger than 32 bits {err}"))?;
            if mem_size >= max_mem {
                bail!("Invalid segment mem_size");
            }
            let p_vaddr: u32 = segment
                .p_vaddr
                .try_into()
                .map_err(|err| anyhow!("vaddr is larger than 32 bits. {err}"))?;

            // Get segment alignment
            let p_align: u32 = segment
                .p_align
                .try_into()
                .map_err(|err| anyhow!("p_align is larger than 32 bits. {err}"))?;
            let p_align = u32::max(p_align, LINUX_PAGE_SIZE);

            // Calculate page offset (where data starts within the page)
            let page_offset = p_vaddr & (p_align - 1);

            // Align segment start down to page boundary, then add load_bias
            let segment_start = (p_vaddr & !(p_align - 1)) + load_bias;

            // Actual data starts at segment_start + page_offset
            let vaddr = segment_start + page_offset;

            println!(
                "Interp segment: p_vaddr={:08x}, p_align={:08x}, page_offset={:08x}",
                p_vaddr, p_align, page_offset
            );
            println!(
                "  segment_start={:08x}, data_vaddr={:08x}, filesz={:08x}, memsz={:08x}",
                segment_start, vaddr, file_size, mem_size
            );
            // Note: vaddr may not be word-aligned; we handle this by iterating from segment_start

            let p_offset: u32 = segment
                .p_offset
                .try_into()
                .map_err(|err| anyhow!("offset is larger than 32 bits. {err}"))?;

            // Calculate file offset for the page-aligned segment start
            let file_segment_start = p_offset - page_offset;

            // Fill entire page-aligned segment region
            let segment_end = segment_start + page_offset + mem_size;
            let total_size = segment_end - segment_start;

            for i in (0..total_size).step_by(WORD_SIZE) {
                let addr = segment_start
                    .checked_add(i)
                    .context("Invalid segment vaddr")?;
                if addr >= max_mem {
                    bail!(
                        "Address [0x{addr:08x}] exceeds maximum address for guest programs [0x{max_mem:08x}]"
                    );
                }

                // Calculate file offset for this address relative to segment_start
                let offset_from_seg_start = (addr - segment_start) as usize;
                let file_offset = (file_segment_start as usize) + offset_from_seg_start;

                // Check if within file data range
                if offset_from_seg_start < (page_offset + file_size) as usize {
                    // Load from file
                    let mut word = 0;
                    let bytes_available =
                        ((page_offset + file_size) as usize) - offset_from_seg_start;
                    let len = core::cmp::min(bytes_available as u32, WORD_SIZE as u32);
                    for j in 0..len {
                        let file_byte_offset = file_offset + (j as usize);
                        let byte = interp
                            .get(file_byte_offset)
                            .context("Invalid segment offset")?;
                        word |= (*byte as u32) << (j * 8);
                    }
                    // Debug output for specific addresses
                    if (0x947fe000..0x947fe010).contains(&addr) {
                        println!(
                            "  DEBUG .data: addr={:08x}, file_offset={:08x}, word={:08x}",
                            addr, file_offset, word
                        );
                    }
                    // Also check DYNAMIC section (0x947fdecc to 0x947fdf84)
                    if (0x947fdecc..0x947fdf84).contains(&addr) {
                        println!(
                            "  DEBUG DYNAMIC: addr={:08x}, file_offset={:08x}, word={:08x}",
                            addr, file_offset, word
                        );
                    }
                    image.insert(addr, word);
                } else {
                    // Zero-fill BSS (beyond page_offset + filesz)
                    if (0x947fdd84..0x947fe010).contains(&addr) {
                        println!("  DEBUG: addr={:08x}, zero-fill BSS", addr);
                    }
                    image.insert(addr, 0);
                }
            }
            // Note: brk is NOT updated for interpreter segments - it tracks only the main executable
        }

        println!("=== Memory Layout ===");
        println!("Main entry:           {:08x}", executable.0);
        println!("Main phdr_addr:       {:08x}", executable.1);
        println!("Main phnum:           {}", executable.2);
        println!("Main brk (heap):      {:08x}", brk);
        println!("DSO mmap_base:        {:08x}", mmap_base);
        println!("Interp max extent:    {:08x}", interp_max_end);
        println!("Interp load_bias:     {:08x}", load_bias);
        println!("Interp entry:         {:08x}", load_bias + entry);
        println!("Interp top:           {:08x}", load_bias + interp_max_end);
        Ok(Program::new_from_entry_and_image(
            executable.0,
            image,
            executable.1,
            executable.2,
            load_bias,
            load_bias + entry,
            brk,
        ))
    }

    /// Initialize a RISC Zero Program from an appropriate ELF file
    pub fn load_elf(input: &[u8], max_mem: u32) -> Result<Program> {
        let mut image: BTreeMap<u32, u32> = BTreeMap::new();
        let elf = ElfBytes::<LittleEndian>::minimal_parse(input)
            .map_err(|err| anyhow!("Elf parse error: {err}"))?;
        if elf.ehdr.class != Class::ELF32 {
            bail!("Not a 32-bit ELF");
        }
        if elf.ehdr.e_machine != elf::abi::EM_RISCV {
            bail!("Invalid machine type, must be RISC-V");
        }
        if elf.ehdr.e_type != elf::abi::ET_EXEC {
            bail!("Invalid ELF type, must be executable");
        }
        let entry: u32 = elf
            .ehdr
            .e_entry
            .try_into()
            .map_err(|err| anyhow!("e_entry was larger than 32 bits. {err}"))?;
        if entry >= max_mem || !entry.is_multiple_of(WORD_SIZE as u32) {
            bail!("Invalid entrypoint");
        }
        let segments = elf
            .segments()
            .ok_or_else(|| anyhow!("Missing segment table"))?;
        if segments.len() > 256 {
            bail!("Too many program headers");
        }
        for segment in segments.iter().filter(|x| x.p_type == elf::abi::PT_LOAD) {
            let file_size: u32 = segment
                .p_filesz
                .try_into()
                .map_err(|err| anyhow!("filesize was larger than 32 bits. {err}"))?;
            if file_size >= max_mem {
                bail!("Invalid segment file_size");
            }
            let mem_size: u32 = segment
                .p_memsz
                .try_into()
                .map_err(|err| anyhow!("mem_size was larger than 32 bits {err}"))?;
            if mem_size >= max_mem {
                bail!("Invalid segment mem_size");
            }
            let vaddr: u32 = segment
                .p_vaddr
                .try_into()
                .map_err(|err| anyhow!("vaddr is larger than 32 bits. {err}"))?;
            if !vaddr.is_multiple_of(WORD_SIZE as u32) {
                bail!("vaddr {vaddr:08x} is unaligned");
            }
            let offset: u32 = segment
                .p_offset
                .try_into()
                .map_err(|err| anyhow!("offset is larger than 32 bits. {err}"))?;
            for i in (0..mem_size).step_by(WORD_SIZE) {
                let addr = vaddr.checked_add(i).context("Invalid segment vaddr")?;
                if addr >= max_mem {
                    bail!(
                        "Address [0x{addr:08x}] exceeds maximum address for guest programs [0x{max_mem:08x}]"
                    );
                }
                if i >= file_size {
                    // Past the file size, all zeros.
                    image.insert(addr, 0);
                } else {
                    let mut word = 0;
                    // Don't read past the end of the file.
                    let len = core::cmp::min(file_size - i, WORD_SIZE as u32);
                    for j in 0..len {
                        let offset = (offset + i + j) as usize;
                        let byte = input.get(offset).context("Invalid segment offset")?;
                        word |= (*byte as u32) << (j * 8);
                    }

                    image.insert(addr, word);
                }
            }
        }

        // Calculate Program Header table address (where phdrs are loaded in memory)
        let mut phdr_addr = 0;
        let phnum = segments.len() as u32;

        // Find which segment contains the Program Header table and calculate its virtual address
        for segment in segments.iter().filter(|x| x.p_type == elf::abi::PT_LOAD) {
            let segment_offset: u32 = segment
                .p_offset
                .try_into()
                .map_err(|err| anyhow!("segment offset is larger than 32 bits. {err}"))?;
            let segment_vaddr: u32 = segment
                .p_vaddr
                .try_into()
                .map_err(|err| anyhow!("segment vaddr is larger than 32 bits. {err}"))?;
            let segment_filesz: u32 = segment
                .p_filesz
                .try_into()
                .map_err(|err| anyhow!("segment filesz is larger than 32 bits. {err}"))?;

            // Check if this segment contains the Program Header table
            let phoff: u32 = elf
                .ehdr
                .e_phoff
                .try_into()
                .map_err(|err| anyhow!("e_phoff is larger than 32 bits. {err}"))?;
            if segment_offset <= phoff && phoff < segment_offset + segment_filesz {
                phdr_addr = phoff - segment_offset + segment_vaddr;
                break;
            }
        }

        Ok(Program::new_from_entry_and_image(
            entry, image, phdr_addr, phnum, 0, 0, 0,
        ))
    }

    /// Create `Program` from given entry-point and image map
    pub fn new_from_entry_and_image(
        entry: u32,
        image: BTreeMap<u32, u32>,
        phdr_addr: u32,
        phnum: u32,
        interp_base_addr: u32,
        interp_addr: u32,
        brk: u32,
    ) -> Self {
        Self {
            entry,
            image,
            phdr_addr,
            phnum,
            interp_base_addr,
            interp_addr,
            brk,
        }
    }

    /// The size of the image in a count of words
    pub fn size_in_words(&self) -> usize {
        self.image.len()
    }

    /// Read a word from the image
    pub fn read_u32(&self, address: &u32) -> Option<u32> {
        self.image.get(address).copied()
    }

    pub(crate) fn prepare_user(&mut self) {
        self.image.insert(USER_START_ADDR.0, self.entry);
    }

    pub(crate) fn prepare_kernel(&mut self, user: Option<&mut Program>) {
        if let Some(user) = user {
            self.image.append(&mut user.image);
        }
        self.image.insert(SUSPEND_PC_ADDR.0, self.entry);
        self.image.insert(SUSPEND_MODE_ADDR.0, 1);
    }
    /// Write a word to the image
    pub fn write_u32(&mut self, address: u32, value: u32) {
        self.image.insert(address, value);
    }
}

const MAGIC: &[u8] = b"R0BF"; // RISC Zero Binary Format
const BINARY_FORMAT_VERSION: u32 = 1; // RISC Zero Binary Format Version Number

#[derive(Serialize, Deserialize)]
enum ProgramBinaryHeaderValueOnDisk {
    AbiVersion(AbiKind, semver::Version),
}

trait ReadBytesExt<'a> {
    fn read_u32(&mut self) -> Result<u32>;
    fn read_slice(&mut self, len: usize) -> Result<&'a [u8]>;
}

impl<'a> ReadBytesExt<'a> for &'a [u8] {
    fn read_u32(&mut self) -> Result<u32> {
        const U32_SIZE: usize = core::mem::size_of::<u32>();

        if self.len() < U32_SIZE {
            bail!("unexpected end of file");
        }

        let value = u32::from_le_bytes(self[..U32_SIZE].try_into().unwrap());
        *self = &self[U32_SIZE..];
        Ok(value)
    }

    fn read_slice(&mut self, len: usize) -> Result<&'a [u8]> {
        if self.len() < len {
            bail!("unexpected end of file");
        }
        let mut other: &[u8] = &[][..];
        core::mem::swap(self, &mut other);
        let (first, rest) = other.split_at(len);
        *self = rest;
        Ok(first)
    }
}

trait WriteBytesExt {
    fn write_u32(&mut self, value: u32);
}

impl WriteBytesExt for Vec<u8> {
    fn write_u32(&mut self, value: u32) {
        self.extend_from_slice(&value.to_le_bytes());
    }
}

/// What kind of ABI is the program using
#[non_exhaustive]
#[derive(Copy, Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub enum AbiKind {
    /// The v1 version of the ABI
    V1Compat,
    /// The Linux ABI
    Linux, // unused for now
}

/// A list of key-value pairs that contains information about the program.
#[non_exhaustive]
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct ProgramBinaryHeader {
    /// The ABI the program uses
    pub abi_kind: AbiKind,

    /// The version of the ABI that the program uses
    pub abi_version: semver::Version,
}

impl Default for ProgramBinaryHeader {
    fn default() -> Self {
        Self {
            abi_version: semver::Version::new(1, 0, 0),
            abi_kind: AbiKind::V1Compat,
        }
    }
}

impl ProgramBinaryHeader {
    fn decode(mut bytes: &[u8]) -> Result<Self> {
        let num_kv_pairs = bytes.read_u32().context("Malformed ProgramBinaryHeader")?;

        // Decode the key-value pairs
        let mut kv_pairs = vec![];
        for _ in 0..num_kv_pairs {
            let kv_pair_len = bytes.read_u32().context("Malformed ProgramBinaryHeader")?;
            let kv_bytes = bytes
                .read_slice(kv_pair_len as usize)
                .context("Malformed ProgramBinaryHeader")?;

            // Skip any entries we can't decode
            if let Ok(kv_pair) = postcard::from_bytes(kv_bytes) {
                kv_pairs.push(kv_pair);
            }
        }

        if !bytes.is_empty() {
            bail!("Malformed ProgramBinaryHeader: trailing bytes");
        }

        // Find the individual key-value pairs we need
        if kv_pairs.len() != 1 {
            bail!("Malformed ProgramBinaryHeader: duplicate attributes");
        }
        let (abi_kind, abi_version) = kv_pairs
            .into_iter()
            .map(|pair| {
                let ProgramBinaryHeaderValueOnDisk::AbiVersion(abi_kind, abi_version) = pair;
                (abi_kind, abi_version)
            })
            .next()
            .ok_or_else(|| anyhow!("ProgramBinary header missing AbiVersion"))?;

        Ok(Self {
            abi_kind,
            abi_version,
        })
    }

    fn encode(&self) -> Vec<u8> {
        let kv_pairs = vec![ProgramBinaryHeaderValueOnDisk::AbiVersion(
            self.abi_kind,
            self.abi_version.clone(),
        )];

        let mut ret = vec![];

        ret.write_u32(kv_pairs.len() as u32);
        for p in &kv_pairs {
            let kv_bytes = postcard::to_allocvec(p).unwrap();
            ret.write_u32(kv_bytes.len() as u32);
            ret.extend_from_slice(&kv_bytes[..]);
        }

        ret
    }
}

#[test]
fn header_encode_decode() {
    let header = ProgramBinaryHeader::default();
    let header_roundtripped = ProgramBinaryHeader::decode(&header.encode()[..]).unwrap();

    assert_eq!(header, header_roundtripped);
}

#[test]
fn header_decode_errors_on_too_short() {
    ProgramBinaryHeader::decode(&[1, 2, 3, 4][..]).unwrap_err();
    ProgramBinaryHeader::decode(&[1, 2, 3, 4, 5, 6][..]).unwrap_err();
}

#[test]
fn header_decode_errors_on_trailing_bytes() {
    let mut encoded = ProgramBinaryHeader::default().encode();
    encoded.extend_from_slice(&[1, 2, 3, 4][..]);
    ProgramBinaryHeader::decode(&encoded).unwrap_err();
}

#[test]
fn header_decode_ignores_unknown_attributes() {
    let mut encoded = ProgramBinaryHeader::default().encode();

    encoded[0] += 1;
    encoded.extend_from_slice(&[2, 0, 0, 0, 0xFF, 0xFF][..]);
    let header = ProgramBinaryHeader::decode(&encoded).unwrap();
    assert_eq!(header, ProgramBinaryHeader::default());
}

/// A container to hold a user ELF and a kernel ELF together.
#[non_exhaustive]
#[derive(Debug, PartialEq, Eq)]
pub struct ProgramBinary<'a> {
    /// The header.
    pub header: ProgramBinaryHeader,

    /// The user ELF.
    pub user_elf: &'a [u8],

    /// The kernel ELF.
    pub kernel_elf: &'a [u8],
}

impl<'a> ProgramBinary<'a> {
    /// Construct from a pair of ELFs.
    pub fn new(user_elf: &'a [u8], kernel_elf: &'a [u8]) -> Self {
        Self {
            header: ProgramBinaryHeader::default(),
            user_elf,
            kernel_elf,
        }
    }

    /// Parse a blob into a `ProgramBinary`.
    pub fn decode(mut blob: &'a [u8]) -> Result<Self> {
        // Read MAGIC bytes. These signal the file format.
        let magic = blob
            .read_slice(MAGIC.len())
            .context("Malformed ProgramBinary")?;
        ensure!(magic == MAGIC, "Malformed ProgramBinary");

        // Read the format version number.
        let binary_format_version = blob.read_u32().context("Malformed ProgramBinary")?;
        ensure!(
            binary_format_version == BINARY_FORMAT_VERSION,
            "ProgramBinary binary format version mismatch"
        );

        // Read the header.
        let header_len = blob.read_u32().context("Malformed ProgramBinary")? as usize;
        let header = ProgramBinaryHeader::decode(
            blob.read_slice(header_len)
                .context("Malformed ProgramBinary")?,
        )?;

        // Read user length, and calculate kernel offset / length
        let user_len = blob.read_u32().context("Malformed ProgramBinary")? as usize;
        let user_elf = blob
            .read_slice(user_len)
            .context("Malformed ProgramBinary")?;
        ensure!(!user_elf.is_empty(), "Malformed ProgramBinary");

        let kernel_elf = blob;
        ensure!(!kernel_elf.is_empty(), "Malformed ProgramBinary");

        Ok(Self {
            header,
            user_elf,
            kernel_elf,
        })
    }

    /// Convert this binary into a blob.
    pub fn encode(&self) -> Vec<u8> {
        let mut ret = vec![];

        // Write magic and format version
        ret.extend_from_slice(MAGIC);
        ret.write_u32(BINARY_FORMAT_VERSION);

        // Write the header
        let header_bytes = ProgramBinaryHeader::encode(&self.header);
        ret.write_u32(header_bytes.len() as u32);
        ret.extend_from_slice(&header_bytes[..]);

        // Write the user and kernel elfs
        ret.write_u32(self.user_elf.len() as u32);
        ret.extend_from_slice(self.user_elf);
        ret.extend_from_slice(self.kernel_elf);

        ret
    }

    fn user_program(&self) -> Result<Program> {
        Program::load_elf(self.user_elf, KERNEL_START_ADDR.0).context("Loading user ELF")
    }

    fn kernel_program(&self) -> Result<Program> {
        Program::load_elf(self.kernel_elf, u32::MAX).context("Loading kernel ELF")
    }

    /// Convert this binary into a `MemoryImage`.
    pub fn to_image(&self) -> Result<MemoryImage> {
        Ok(MemoryImage::with_kernel(
            self.user_program()?,
            self.kernel_program()?,
        ))
    }

    /// Compute and return the ImageID of this binary.
    pub fn compute_image_id(&self) -> Result<Digest> {
        let merkle_root = self.to_image()?.image_id();
        Ok(SystemState { pc: 0, merkle_root }.digest::<Impl>())
    }

    /// Compute the memory merkle root of the kernel.
    pub fn kernel_id(&self) -> Result<Digest> {
        Ok(MemoryImage::new_kernel(self.kernel_program()?).image_id())
    }
}

#[test]
fn encode_decode() {
    let p1 = ProgramBinary::new(&[1, 2, 3, 4], &[5, 6, 7, 8]);
    let v = p1.encode();
    let p2 = ProgramBinary::decode(&v).unwrap();

    assert_eq!(p1, p2);
}

#[test]
fn bad_magic() {
    let p1 = ProgramBinary::new(&[1, 2, 3, 4], &[5, 6, 7, 8]);
    let mut v = p1.encode();
    v[0] = 0xbe;
    ProgramBinary::decode(&v).unwrap_err();
}

#[test]
fn bad_version() {
    let p1 = ProgramBinary::new(&[1, 2, 3, 4], &[5, 6, 7, 8]);
    let mut v = p1.encode();
    v[MAGIC.len()] = 0xbe;
    ProgramBinary::decode(&v).unwrap_err();
}
