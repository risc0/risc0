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

use core::ptr::addr_of;

use risc0_circuit_keccak::{KeccakState, KECCAK_CONTROL_ROOT};
use risc0_circuit_recursion::control_id::ALLOWED_CONTROL_ROOT;
use risc0_zkp::core::{digest::Digest, hash::sha::SHA256_INIT};
use risc0_zkvm_platform::syscall::{sys_keccak, sys_prove_keccak, sys_poseidon2_compress, DIGEST_WORDS};

use crate::{
    mmr::{GuestPeak, MerkleMountainAccumulator},
    Assumption,
};

/// This struct implements the batching of calls to the keccak accelerator.
#[derive(Debug)]
pub(crate) struct KeccakBatcher {
    claim_state: Digest,
    mmr: MerkleMountainAccumulator<GuestPeak>,
    proof_count: u32,
}

impl KeccakBatcher {
    fn input_exists(&self) -> bool {
        self.claim_state != SHA256_INIT
    }

    pub fn new() -> Self {
        Self {
            claim_state: SHA256_INIT,
            mmr: MerkleMountainAccumulator::<GuestPeak>::new(),
            proof_count: 0,
        }
    }

    #[allow(dead_code)]
    pub(crate) fn update(&mut self, keccak_state: &mut KeccakState) {
        sha_single_keccak(&mut self.claim_state, keccak_state);
        let status = unsafe { sys_keccak(keccak_state, keccak_state) };
        // at this point the keccak_state is output state resulting from keccak permutation.
        sha_single_keccak(&mut self.claim_state, keccak_state);
        if status == 1 {
            // we've reached the limit. Create a proof request.
            self.flush();
        }
    }

    pub(crate) fn flush(&mut self) {
        if !self.input_exists() {
            // no input so there's nothing to do
            return;
        }

        let claim_digest = self.claim_digest();
        unsafe {
            sys_prove_keccak(claim_digest.as_ref(), KECCAK_CONTROL_ROOT.as_ref());
        }
        self.proof_count += 1;
        self.mmr
            .insert(Assumption {
                claim: claim_digest,
                control_root: KECCAK_CONTROL_ROOT,
            })
            .unwrap(); // this is infallible for GuestPeak
        self.reset();
    }

    pub(crate) fn finalize(mut self) {
        self.flush();
        if let Ok(root_assumption) = self.mmr.root() {
            // if proof_count == 0, self.mmr.root() will return an error.
            let control_root = if self.proof_count == 1 {
                KECCAK_CONTROL_ROOT
            } else {
                ALLOWED_CONTROL_ROOT
            };
            crate::guest::env::verify_assumption2(root_assumption.claim, control_root).unwrap();
        }
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
    }
}

pub(crate) fn sha_single_keccak(claim_state: &mut Digest, keccak_state: &KeccakState) {
    let keccak_state_u32 = keccak_state.as_ptr() as *const u32;
        unsafe {
            sys_poseidon2_compress(
                claim_state.as_ref(),
                keccak_state.as_ptr() as *const u8,
                claim_state.as_mut(),
                0x2000_0000 | 3
            )
        };

    // any last words?
    static mut LAST_WORDS: [u32; DIGEST_WORDS] = [0u32; DIGEST_WORDS];
    unsafe {
        LAST_WORDS[0] = *keccak_state_u32.add(48);
        LAST_WORDS[1] = *keccak_state_u32.add(49);
    }

    unsafe {
        sys_poseidon2_compress(
            claim_state.as_ref(),
            addr_of!(LAST_WORDS) as *const u8,
            claim_state.as_mut(),
            0x2000_0000 | 1
        )
    };
}
