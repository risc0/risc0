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

use rand::{Error, RngCore};

use crate::core::{
    fp::Fp,
    fp4::Fp4,
    sha::{Digest, Sha, DIGEST_WORDS},
    sha_rng::ShaRng,
};
use crate::field::{Elem, ExtElem};

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
        for i in 0..x.len() {
            x[i] = self.proof[i];
        }
        self.proof = &self.proof[x.len()..];
    }

    pub fn read_fps(&mut self, x: &mut [Fp]) {
        let words = <Fp as Elem>::WORDS;
        for i in 0..x.len() {
            x[i] = <Fp as Elem>::from_u32_words(&self.proof[words * i..words * (i + 1)]);
            // Ignore the odd-numbered values, which will be 0 for baby-bear
        }
        self.proof = &self.proof[<Fp as Elem>::WORDS * x.len()..];
    }

    pub fn read_fp4s(&mut self, x: &mut [Fp4]) {
        let elem_words = <Fp4 as ExtElem>::SubElem::WORDS;
        let ext_size = <Fp4 as ExtElem>::EXT_SIZE;
        for i in 0..x.len() {
            let mut subelems = Vec::<<Fp4 as ExtElem>::SubElem>::new();
            for j in 0..<Fp4 as ExtElem>::EXT_SIZE {
                let offset: usize = ext_size * i + j;
                subelems.push(<Fp4 as ExtElem>::SubElem::from_u32_words(
                    &self.proof[elem_words * offset..elem_words * (offset + 1)],
                ));
            }
            x[i] = <Fp4 as ExtElem>::from_subelems(subelems);
        }
        self.proof = &self.proof[<Fp4 as Elem>::WORDS * x.len()..];
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
        assert_eq!(self.proof.len(), 0);
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
