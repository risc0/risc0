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

use anyhow::Result;
use risc0_zkp::{
    core::{
        fp::Fp,
        log2_ceil,
        sha::{Digest, DIGEST_WORDS, DIGEST_WORD_SIZE},
    },
    MAX_CYCLES, MIN_CYCLES, ZK_CYCLES,
};

const MAX_CODE_DIGEST_COUNT: usize = log2_ceil(MAX_CYCLES / MIN_CYCLES) + 1;

#[derive(Clone)]
pub struct MethodId {
    pub table: Vec<Digest>,
}

impl MethodId {
    pub fn load(bytes: &[u8]) -> Result<Self> {
        let mut table = Vec::new();
        for digest in bytes.chunks_exact(DIGEST_WORDS * DIGEST_WORD_SIZE) {
            let words: Vec<u32> = digest
                .chunks_exact(DIGEST_WORD_SIZE)
                .map(|x| {
                    let mut word = 0;
                    for i in 0..4 {
                        word |= (x[i] as u32) << (i * 8);
                    }
                    word
                })
                .collect();
            table.push(Digest::try_from_slice(&words)?);
        }
        Ok(MethodId { table })
    }

    #[cfg(feature = "prove")]
    pub fn compute(elf_contents: &[u8]) -> Result<Self> {
        use crate::host::DEFAULT_METHOD_ID_LIMIT;
        MethodId::compute_with_limit(elf_contents, DEFAULT_METHOD_ID_LIMIT as usize)
    }

    #[cfg(feature = "prove")]
    pub fn compute_with_limit(elf_contents: &[u8], limit: usize) -> Result<Self> {
        use crate::{elf::Program, platform::memory::MEM_SIZE, CODE_SIZE};
        use risc0_zkp::{
            hal::{cpu::CpuHal, Hal},
            prove::poly_group::PolyGroup,
        };

        let hal = CpuHal {};
        let program = Program::load_elf(elf_contents, MEM_SIZE as u32)?;

        // Start with an empty table
        let mut table = Vec::new();

        // Make the digest for each level
        let count = std::cmp::min(limit, MAX_CODE_DIGEST_COUNT);
        for i in 0..count {
            let cycles = MIN_CYCLES * (1 << i);
            if cycles < program.image.len() + 3 + ZK_CYCLES {
                // Can't even fit the program in this cycle size, just set to zero
                table.push(Digest::default());
                continue;
            }

            // Make a vector & set it up with the elf data
            let mut code = vec![Fp::default(); cycles * CODE_SIZE];
            load_code(&mut code, &program, cycles)?;

            // Copy into accel buffer
            let coeffs = hal.copy_from(&code);
            // Do interpolate & shift
            hal.batch_interpolate_ntt(&coeffs, CODE_SIZE);
            hal.zk_shift(&coeffs, CODE_SIZE);
            // Make the poly-group & extract the root
            let code_group = PolyGroup::new(&hal, &coeffs, CODE_SIZE, cycles);
            table.push(code_group.merkle.root().clone());
        }

        Ok(MethodId { table })
    }
}

#[cfg(feature = "prove")]
fn load_code(code: &mut [Fp], elf: &crate::elf::Program, cycles: usize) -> Result<()> {
    use crate::{prove::exec, CODE_SIZE};

    let mut cycle = 0;
    exec::load_code(elf.entry, &elf.image, |chunk, fini| {
        for i in 0..CODE_SIZE {
            code[cycles * i + cycle] = chunk[i];
        }
        if cycle + fini + ZK_CYCLES < cycles {
            cycle += 1;
            Ok(true)
        } else {
            Ok(false)
        }
    })
}
