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

use risc0_circuit_keccak::{
    KeccakState, KECCAK_CONTROL_ROOT, KECCAK_DEFAULT_PO2, KECCAK_PO2_RANGE,
};
use risc0_zkp::core::{digest::Digest, hash::sha::SHA256_INIT};
use risc0_zkvm_platform::syscall::{sys_keccak, sys_prove_keccak, sys_sha_compress, DIGEST_WORDS};

const KECCAK_PERMUTE_CYCLES: usize = 200;

/// This struct implements the batching of calls to the keccak accelerator.
#[derive(Debug)]
pub struct Keccak2Batcher {
    claim_state: Digest,
    inputs: Vec<KeccakState>,
    po2: u32,
}

impl Keccak2Batcher {
    fn max_keccak_inputs(&self) -> usize {
        let max_keccak_cycles: usize = 1 << self.po2;
        max_keccak_cycles / KECCAK_PERMUTE_CYCLES
    }

    pub fn new() -> Self {
        #[cfg(feature = "std")]
        let po2 = match std::env::var("RISC0_KECCAK_PO2") {
            Err(_) => KECCAK_DEFAULT_PO2 as u32,
            Ok(po2) => {
                let po2 = po2.parse::<u32>().unwrap();
                if !KECCAK_PO2_RANGE.contains(&(po2 as usize)) {
                    panic!(
                        "invalid keccak po2 {po2}. Expected range: {:?}",
                        KECCAK_PO2_RANGE
                    );
                }
                po2
            }
        };
        #[cfg(not(feature = "std"))]
        let po2 = KECCAK_DEFAULT_PO2;
        Self {
            claim_state: SHA256_INIT,
            inputs: vec![],
            po2,
        }
    }

    pub fn update(&mut self, keccak_state: &mut KeccakState) {
        self.inputs.push(*keccak_state);
        sha_single_keccak(&mut self.claim_state, keccak_state);
        unsafe { sys_keccak(keccak_state, keccak_state) };
        // at this point the keccak_state is output state resulting from keccak permutation.
        sha_single_keccak(&mut self.claim_state, keccak_state);
        if self.inputs.len() == self.max_keccak_inputs() {
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
                self.po2,
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

    let keccak_state_u32 = keccak_state.as_ptr() as *const u32;
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
            &ZEROES,
        )
    };
}
