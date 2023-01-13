// Copyright 2022 RISC Zero, Inc.
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

use alloc::vec::Vec;

use anyhow::Result;
use risc0_zkp::core::sha::{Digest, DIGEST_WORDS, DIGEST_WORD_SIZE};

/// The default digest count when generating a MethodId.
pub const DEFAULT_METHOD_ID_LIMIT: usize = 21; // 2M

/// The MethodId serves as a cryptographic identifier for the ELF file that the
/// zkVM is executing. Intuitively, the MethodId can be considered as a hash of
/// the ELF file.
#[derive(Clone, Eq, PartialEq)]
pub struct MethodId {
    /// In practice, the "code columns" determine the operation of the zkVM, and
    /// the merkle commitment for the "code merkle tree" serves as the
    /// cryptographic identifier for the zkVM behavior. Since the MethodId
    /// is generated before zkVM operation and the "code merkle tree" depends on
    /// the length-of-zkVM-execution, the MethodId consists of a table with one
    /// row per possible execution length. The receipt verification process
    /// checks that the merkle commitment for the "code merkle tree" is
    /// contained in the table.
    pub table: Vec<Digest>,
}

impl From<&MethodId> for MethodId {
    fn from(method_id: &MethodId) -> Self {
        method_id.clone()
    }
}

impl From<&[u8]> for MethodId {
    fn from(bytes: &[u8]) -> Self {
        MethodId::from_slice(bytes).unwrap()
    }
}

impl From<&[u32]> for MethodId {
    fn from(words: &[u32]) -> Self {
        let mut table = Vec::new();
        for digest in words.chunks_exact(DIGEST_WORDS) {
            table.push(digest.try_into().unwrap());
        }
        MethodId { table }
    }
}

impl MethodId {
    /// The current version of the MethodID.
    ///
    /// Bump this whenever the way that a MethodID is created or represented
    /// changes.
    pub const VERSION: usize = 2;

    pub fn as_slice(&self) -> &[u8] {
        bytemuck::cast_slice(self.table.as_slice())
    }

    pub fn from_slice(bytes: &[u8]) -> Result<Self> {
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
            // Unwrap here since chunks_exact already would ensure no errors.
            table.push(words.try_into().unwrap());
        }
        Ok(MethodId { table })
    }

    #[cfg(feature = "prove")]
    pub fn compute(elf_contents: &[u8]) -> Result<Self> {
        MethodId::compute_with_limit(elf_contents, DEFAULT_METHOD_ID_LIMIT)
    }

    #[cfg(feature = "prove")]
    pub fn compute_with_limit(elf_contents: &[u8], limit: usize) -> Result<Self> {
        prove::compute_with_limit(elf_contents, limit)
    }
}

#[cfg(feature = "prove")]
mod prove {
    use anyhow::Result;
    use risc0_zkp::{
        adapter::TapsProvider, core::sha::Digest, field::baby_bear::BabyBearElem, hal::Hal,
        prove::poly_group::PolyGroup, MAX_CYCLES_PO2, MIN_CYCLES_PO2, ZK_CYCLES,
    };
    use risc0_zkvm_platform::memory::MEM_SIZE;

    use super::MethodId;
    use crate::{
        prove::{elf::Program, loader::Loader},
        CIRCUIT,
    };

    pub fn compute_with_limit(elf_contents: &[u8], limit: usize) -> Result<MethodId> {
        let code_size = CIRCUIT.code_size();
        cfg_if::cfg_if! {
            if #[cfg(target_os = "macos")] {
                let hal = risc0_zkp::hal::metal::MetalHal::new();
            } else {
                let hal = risc0_zkp::hal::cpu::BabyBearCpuHal::new();
            }
        }
        let program = Program::load_elf(elf_contents, MEM_SIZE as u32)?;
        let loader = Loader::new(&program.image);
        let min_cycles = loader.compute_min_cycles();

        // Start with an empty table
        let mut table = Vec::new();

        // Make the digest for each level
        let count = std::cmp::min(limit, MAX_CYCLES_PO2);
        for i in MIN_CYCLES_PO2..count {
            let cycles = 1 << i;
            if cycles <= min_cycles {
                // Can't even fit the program in this cycle size, just set to zero
                table.push(Digest::default());
                continue;
            }

            // Make a vector & set it up with the elf data
            let mut code = vec![BabyBearElem::default(); cycles * code_size];
            load_code(&loader, &mut code, &program, cycles)?;

            // Copy into accel buffer
            let coeffs = hal.copy_from_elem("coeffs", &code);
            // Do interpolate & shift
            hal.batch_interpolate_ntt(&coeffs, code_size);
            hal.zk_shift(&coeffs, code_size);
            // Make the poly-group & extract the root
            let code_group = PolyGroup::new(&hal, &coeffs, code_size, cycles, "code");
            table.push(code_group.merkle.root().clone());
        }

        Ok(MethodId { table })
    }

    fn load_code(
        loader: &Loader,
        code: &mut [BabyBearElem],
        elf: &Program,
        max_cycles: usize,
    ) -> Result<usize> {
        let code_size = CIRCUIT.code_size();
        let mut cycle = 0;
        loader.load(elf.entry, |chunk, fini| {
            for i in 0..code_size {
                code[max_cycles * i + cycle] = chunk[i];
            }
            let total = cycle + fini + ZK_CYCLES;
            if total < max_cycles {
                cycle += 1;
                Ok(true)
            } else {
                log::debug!("Halting. {cycle} + {fini} + ZK_CYCLES ({total}) < {max_cycles}");
                Ok(false)
            }
        })
    }
}
