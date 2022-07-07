// Copyright 2022 Risc0, Inc.
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

use alloc::collections::BTreeMap;

use anyhow::{anyhow, bail, Result};
use xmas_elf::{
    header::{Class, Data, Machine, Version},
    program::ProgramHeader,
    ElfFile,
};

pub struct Program {
    pub entry: u32,
    pub image: BTreeMap<u32, u32>,
}

impl Program {
    pub fn load_elf(input: &[u8], max_mem: u32) -> Result<Program> {
        let mut image: BTreeMap<u32, u32> = BTreeMap::new();
        let elf = ElfFile::new(input).map_err(|err| anyhow!(err))?;
        xmas_elf::header::sanity_check(&elf).map_err(|err| anyhow!(err))?;
        if elf.header.pt1.class() != Class::ThirtyTwo {
            bail!("Not a 32-bit ELF");
        }
        if elf.header.pt1.data() != Data::LittleEndian {
            bail!("Not little endian");
        }
        if elf.header.pt1.version() != Version::Current || elf.header.pt2.version() != 1 {
            bail!("Invalid ELF version");
        }
        if elf.header.pt2.machine().as_machine() != Machine::RISC_V {
            bail!("Invalid machine type, must be RISC-V");
        }
        if elf.header.pt2.type_().as_type() != xmas_elf::header::Type::Executable {
            bail!("Invalid ELF type, must be executable");
        }
        let entry: u32 = elf.header.pt2.entry_point().try_into()?;
        if entry >= max_mem || entry % 4 != 0 {
            bail!("Invalid entry point");
        }
        if elf.header.pt2.ph_count() > 256 {
            bail!("Too many program headers");
        }
        for phdr in elf.program_iter() {
            let type_ = phdr.get_type().map_err(|err| anyhow!(err))?;
            if type_ != xmas_elf::program::Type::Load {
                continue;
            }

            let phdr = match phdr {
                ProgramHeader::Ph32(phdr) => phdr,
                ProgramHeader::Ph64(_) => bail!("Not a 32-bit ELF"),
            };
            for i in (0..phdr.mem_size).step_by(4) {
                let addr = phdr.virtual_addr + i;
                if i >= phdr.file_size {
                    // Past the file size, all zeros.
                    image.insert(addr, 0);
                } else {
                    let mut word = 0;
                    // Don't read past the end of the file.
                    let len = std::cmp::min(phdr.file_size - i, 4);
                    for j in 0..len {
                        let offset = (phdr.offset + i + j) as usize;
                        let byte = input[offset] as u32;
                        word |= byte << j * 8;
                    }
                    image.insert(addr, word);
                }
            }
        }
        Ok(Program { entry, image })
    }
}
