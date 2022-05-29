use alloc::vec::Vec;

use risc0_zkp_core::{
    fp::Fp,
    fp4::Fp4,
    sha::{Digest, Sha},
    sha_rng::ShaRng,
};

pub struct WriteIOP<S: Sha> {
    pub proof: Vec<u32>,
    pub rng: ShaRng<S>,
}

impl<S: Sha> WriteIOP<S> {
    /// Create a new empty proof
    pub fn new(sha: &S) -> Self {
        WriteIOP {
            proof: Vec::new(),
            rng: ShaRng::new(sha),
        }
    }

    /// Called by the prover to write some data.
    ///
    /// This data is not cryptographically verifiable on its own,
    /// but is typically committed by a later hash which includes it.
    pub fn write_u32_slice(&mut self, slice: &[u32]) {
        self.proof.extend_from_slice(slice);
    }

    /// Called by the prover to write some data.
    pub fn write_fp_slice(&mut self, slice: &[Fp]) {
        self.proof.extend(slice.iter().map(|x| {
            let x: u32 = x.into();
            x
        }));
    }

    /// Called by the prover to write some data.
    pub fn write_fp4_slice(&mut self, slice: &[Fp4]) {
        for x in slice {
            self.write_fp_slice(x.elems());
        }
    }

    /// Called by the prover to write some data.
    pub fn write_digest_slice(&mut self, digest: &[Digest]) {
        for x in digest {
            self.write_u32_slice(x.as_slice());
        }
    }

    /// Called by the prover to commit to some hash (usually data written earlier or a Merkle root).
    pub fn commit(&mut self, message: &Digest) {
        self.rng.mix(message);
    }
}
