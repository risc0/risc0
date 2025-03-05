// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

extern crate alloc;

use alloc::{collections::BTreeMap, vec, vec::Vec};

use anyhow::{anyhow, bail, ensure, Context, Result};
use elf::{endian::LittleEndian, file::Class, ElfBytes};
use risc0_zkp::core::{digest::Digest, hash::sha::Impl};
use risc0_zkvm_platform::WORD_SIZE;

use crate::{Digestible as _, MemoryImage2, SystemState, KERNEL_START_ADDR};

/// A RISC Zero program
pub struct Program {
    /// The entrypoint of the program
    pub entry: u32,

    /// The initial memory image
    pub image: BTreeMap<u32, u32>,
}

impl Program {
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
            let vaddr: u32 = segment
                .p_vaddr
                .try_into()
                .map_err(|err| anyhow!("vaddr is larger than 32 bits. {err}"))?;
            if vaddr % WORD_SIZE as u32 != 0 {
                bail!("vaddr {vaddr:08x} is unaligned");
            }
            let offset: u32 = segment
                .p_offset
                .try_into()
                .map_err(|err| anyhow!("offset is larger than 32 bits. {err}"))?;
            for i in (0..mem_size).step_by(WORD_SIZE) {
                let addr = vaddr.checked_add(i).context("Invalid segment vaddr")?;
                if addr >= max_mem {
                    bail!("Address [0x{addr:08x}] exceeds maximum address for guest programs [0x{max_mem:08x}]");
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
        Ok(Program { entry, image })
    }
}

/// A pair to hold a user ELF and a kernel ELF together.
pub struct ProgramPair<'a> {
    /// The user ELF.
    pub user_elf: &'a [u8],

    /// The kernel ELF.
    pub kernel_elf: &'a [u8],
}

impl<'a> ProgramPair<'a> {
    /// Construct from a pair of ELFs.
    pub fn new(user_elf: &'a [u8], kernel_elf: &'a [u8]) -> Self {
        Self {
            user_elf,
            kernel_elf,
        }
    }

    /// Parse a blob into a ProgramPair.
    pub fn decode(blob: &'a [u8]) -> Result<Self> {
        ensure!(blob.len() > WORD_SIZE);

        let user_len_bytes = &blob[..WORD_SIZE];
        let user_len = u32::from_le_bytes(user_len_bytes.try_into().unwrap()) as usize;
        ensure!(user_len > 0);

        let kernel_offset = WORD_SIZE + user_len;
        let user_elf = &blob[WORD_SIZE..kernel_offset];
        let kernel_elf = &blob[kernel_offset..];

        Ok(Self {
            user_elf,
            kernel_elf,
        })
    }

    /// Convert this pair into a blob.
    pub fn encode(&self) -> Vec<u8> {
        let user_len = self.user_elf.len();
        let kernel_offset = WORD_SIZE + user_len;
        let user_len = user_len as u32;

        let mut ret = vec![0; size_of_val(&user_len) + self.user_elf.len() + self.kernel_elf.len()];
        ret[..WORD_SIZE].copy_from_slice(&user_len.to_le_bytes());
        ret[WORD_SIZE..kernel_offset].copy_from_slice(self.user_elf);
        ret[kernel_offset..].copy_from_slice(self.kernel_elf);
        ret
    }

    /// Convert this pair into a MemoryImage2.
    pub fn to_image(&self) -> Result<MemoryImage2> {
        let user_program =
            Program::load_elf(self.user_elf, KERNEL_START_ADDR.0).context("Loading user ELF")?;
        let kernel_program =
            Program::load_elf(self.kernel_elf, u32::MAX).context("Loading kernel ELF")?;
        Ok(MemoryImage2::with_kernel(user_program, kernel_program))
    }

    /// Compute and return the ImageID of this ProgramPair.
    pub fn compute_image_id(&self) -> Result<Digest> {
        let merkle_root = self.to_image()?.image_id();
        Ok(SystemState { pc: 0, merkle_root }.digest::<Impl>())
    }
}
