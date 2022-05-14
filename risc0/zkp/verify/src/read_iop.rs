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

use risc0_zkp_core::{
    fp::Fp,
    fp4::Fp4,
    sha::{Digest, Sha, DIGEST_WORDS},
    sha_rng::ShaRng,
};

use rand::{Error, RngCore};

#[derive(Debug)]
pub struct ReadIOP<'a, S: Sha> {
    sha: S,
    proof: &'a [u32],
    rng: ShaRng<S>,
}

impl<'a, S: Sha> ReadIOP<'a, S> {
    pub fn new(sha: &'a S, proof: &'a [u32]) -> Self {
        ReadIOP {
            sha: sha.clone(),
            proof,
            rng: ShaRng::new(sha),
        }
    }

    pub fn get_sha(&self) -> &S {
        &self.sha
    }

    pub fn read_u32s(&mut self, x: &mut [u32]) {
        x.clone_from_slice(&self.proof[0..x.len()]);
        self.proof = &self.proof[x.len()..];
    }

    pub fn read_fps(&mut self, x: &mut [Fp]) {
        for i in 0..x.len() {
            x[i] = Fp::from(self.proof[i]);
        }
        self.proof = &self.proof[x.len()..];
    }

    pub fn read_fp4s(&mut self, x: &mut [Fp4]) {
        for i in 0..x.len() {
            x[i] = Fp4::new(
                Fp::from(self.proof[4 * i + 0]),
                Fp::from(self.proof[4 * i + 1]),
                Fp::from(self.proof[4 * i + 2]),
                Fp::from(self.proof[4 * i + 3]),
            )
        }
        self.proof = &self.proof[4 * x.len()..];
    }

    pub fn read_digests(&mut self, x: &mut [Digest]) {
        for i in 0..x.len() {
            x[i] = Digest::from_slice(&self.proof[DIGEST_WORDS * i..DIGEST_WORDS * (i + 1)]);
        }
        self.proof = &self.proof[DIGEST_WORDS * x.len()..];
    }

    pub fn commit(&mut self, digest: &Digest) {
        self.rng.mix(digest);
    }

    pub fn verify_complete(&self) {
        assert!(self.proof.len() == 0);
    }
}

impl<'a, S: Sha> RngCore for ReadIOP<'a, S> {
    fn next_u32(&mut self) -> u32 {
        self.rng.next_u32()
    }

    fn next_u64(&mut self) -> u64 {
        self.rng.next_u64()
    }

    fn fill_bytes(&mut self, dest: &mut [u8]) {
        self.rng.fill_bytes(dest)
    }

    fn try_fill_bytes(&mut self, dest: &mut [u8]) -> Result<(), Error> {
        self.rng.try_fill_bytes(dest)
    }
}
