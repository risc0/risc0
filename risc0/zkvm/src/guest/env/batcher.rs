// Copyright 2024 RISC Zero, Inc.
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

use core::ptr::addr_of;

use alloc::vec;

use risc0_circuit_keccak::{KeccakState, KECCAK_CONTROL_ROOT, KECCAK_DEFAULT_PO2};
use risc0_zkp::core::{digest::Digest, hash::sha::SHA256_INIT};
use risc0_zkvm_platform::syscall::{sys_keccak, sys_prove_keccak, sys_sha_compress, DIGEST_WORDS};

const KECCAK_PERMUTE_CYCLES: usize = 200;
const MAX_KECCAK_CYCLES: usize = 1 << KECCAK_DEFAULT_PO2;
const MAX_KECCAK_INPUTS: usize = MAX_KECCAK_CYCLES / KECCAK_PERMUTE_CYCLES;

/// This struct implements the batching of calls to the keccak accelerator.
pub struct Keccak2Batcher {
    claim_state: Digest,
    inputs: Vec<KeccakState>,
}

impl Keccak2Batcher {
    pub const fn init() -> Self {
        Self {
            claim_state: SHA256_INIT,
            inputs: vec![],
        }
    }

    pub fn update(&mut self, keccak_state: &mut KeccakState) {
        sha_single_keccak(&mut self.claim_state, keccak_state);
        unsafe { sys_keccak(keccak_state, keccak_state) };
        sha_single_keccak(&mut self.claim_state, keccak_state);
        self.inputs.push(*keccak_state);
        if self.inputs.len() == MAX_KECCAK_INPUTS {
            // we've reached the limit. Create a proof request.
            self.finalize();
        }
    }

    pub fn finalize(&mut self) {
        if self.inputs.is_empty() {
            // no input so there's nothing to do
            self.reset();
            return;
        }

        let input: &[u32] = bytemuck::cast_slice(self.inputs.as_flattened());
        let claim_digest = self.claim_digest();

        unsafe {
            sys_prove_keccak(
                claim_digest.as_ref(),
                KECCAK_DEFAULT_PO2,
                KECCAK_CONTROL_ROOT.as_ref(),
                input.as_ptr(),
                input.len(),
            );
        }
        crate::guest::env::verify_assumption(claim_digest, KECCAK_CONTROL_ROOT).unwrap();

        self.reset();
    }

    fn claim_digest(&self) -> Digest {
        let mut claim_digest = self.claim_state;
        for word in claim_digest.as_mut_words().iter_mut() {
            *word = word.to_be();
        }
        claim_digest
    }

    fn reset(&mut self) {
        self.claim_state = SHA256_INIT;
        self.inputs.clear();
    }
}

pub(crate) fn sha_single_keccak(claim_state: &mut Digest, keccak_state: &KeccakState) {
    const ZEROES: [u32; DIGEST_WORDS] = [0u32; DIGEST_WORDS];

    let keccak_state_u32: *const u32 = keccak_state.as_ptr() as *const u32;
    for i in 0..3 {
        unsafe {
            sys_sha_compress(
                claim_state.as_mut(),
                claim_state.as_ref(),
                keccak_state_u32.add(i * 16) as *const [u32; DIGEST_WORDS],
                keccak_state_u32.add(i * 16 + 8) as *const [u32; DIGEST_WORDS],
            )
        };
    }

    // any last words?
    static mut LAST_WORDS: [u32; DIGEST_WORDS] = [0u32; DIGEST_WORDS];
    unsafe {
        LAST_WORDS[0] = *keccak_state_u32.add(48);
        LAST_WORDS[1] = *keccak_state_u32.add(49);
    }

    unsafe {
        sys_sha_compress(
            claim_state.as_mut(),
            claim_state.as_ref(),
            addr_of!(LAST_WORDS),
            &ZEROES as *const [u32; DIGEST_WORDS],
        )
    };
}
