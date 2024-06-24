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

//! Cryptographic algorithms for verifying a ZK proof of compute

mod fri;
mod merkle;
mod read_iop;

use alloc::{vec, vec::Vec};
use core::{cell::RefCell, fmt, iter::zip};

pub(crate) use merkle::MerkleTreeVerifier;
pub use read_iop::ReadIOP;
use risc0_core::field::{Elem, ExtElem, Field, RootsOfUnity};

use crate::{
    adapter::{
        CircuitCoreDef, ProtocolInfo, PROOF_SYSTEM_INFO, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE,
        REGISTER_GROUP_DATA,
    },
    core::{digest::Digest, hash::HashSuite, log2_ceil},
    taps::TapSet,
    INV_RATE, MAX_CYCLES_PO2, QUERIES,
};

#[derive(PartialEq)]
#[non_exhaustive]
pub enum VerificationError {
    ReceiptFormatError,
    ControlVerificationError {
        control_id: Digest,
    },
    ImageVerificationError,
    MerkleQueryOutOfRange {
        idx: usize,
        rows: usize,
    },
    InvalidProof,
    JournalDigestMismatch,
    ClaimDigestMismatch {
        expected: Digest,
        received: Digest,
    },
    UnexpectedExitCode,
    InvalidHashSuite,
    VerifierParametersMissing,
    VerifierParametersMismatch {
        expected: Digest,
        received: Digest,
    },
    ProofSystemInfoMismatch {
        expected: ProtocolInfo,
        received: ProtocolInfo,
    },
    CircuitInfoMismatch {
        expected: ProtocolInfo,
        received: ProtocolInfo,
    },
    UnresolvedAssumption {
        digest: Digest,
    },
}

impl fmt::Debug for VerificationError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        fmt::Display::fmt(&self, f)
    }
}

impl fmt::Display for VerificationError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            VerificationError::ReceiptFormatError => write!(f, "invalid receipt format"),
            VerificationError::ControlVerificationError { control_id } => {
                write!(f, "control_id mismatch: {control_id}")
            }
            VerificationError::ImageVerificationError => write!(f, "image_id mismatch"),
            VerificationError::MerkleQueryOutOfRange { idx, rows } => write!(
                f,
                "requested Merkle validation on row {idx}, but only {rows} rows exist",
            ),
            VerificationError::InvalidProof => write!(f, "verification indicates proof is invalid"),
            VerificationError::JournalDigestMismatch => {
                write!(f, "journal digest mismatch detected")
            }
            VerificationError::ClaimDigestMismatch { expected, received } => {
                write!(f, "claim digest does not match the expected digest {received}; expected {expected}")
            }
            VerificationError::UnexpectedExitCode => write!(f, "unexpected exit_code"),
            VerificationError::InvalidHashSuite => write!(f, "invalid hash suite"),
            VerificationError::VerifierParametersMissing => {
                write!(f, "verifier parameters were not found in verifier context for the given receipt type")
            }
            VerificationError::VerifierParametersMismatch { expected, received } => {
                write!(f, "receipt was produced for a version of the verifier with parameters digest {received}; expected {expected}")
            }
            VerificationError::ProofSystemInfoMismatch { expected, received } => {
                write!(f, "receipt was produced for a version of the verifier with proof system info {received}; expected {expected}")
            }
            VerificationError::CircuitInfoMismatch { expected, received } => {
                write!(f, "receipt was produced for a version of the verifier with circuit info {received}; expected {expected}")
            }
            VerificationError::UnresolvedAssumption { digest } => {
                write!(f, "receipt contains an unresolved assumption: {digest}")
            }
        }
    }
}

#[cfg(feature = "std")]
impl std::error::Error for VerificationError {}

trait VerifyParams<F: Field> {
    const CHECK_SIZE: usize = INV_RATE * F::ExtElem::EXT_SIZE;
}

struct TapCache<F: Field> {
    taps: *const TapSet<'static>,
    mix: F::ExtElem,
    tap_mix_pows: Vec<F::ExtElem>,
    check_mix_pows: Vec<F::ExtElem>,
}

pub(crate) struct Verifier<'a, F, C>
where
    F: Field,
{
    circuit: &'a C,
    suite: &'a HashSuite<F>,
    po2: u32,
    steps: usize,
    out: Option<&'a [F::Elem]>,
    mix: Vec<F::Elem>,
    tap_cache: RefCell<Option<TapCache<F>>>,
}

impl<'a, F: Field, C> VerifyParams<F> for Verifier<'a, F, C> {}

impl<'a, F, C> Verifier<'a, F, C>
where
    F: Field,
    C: CircuitCoreDef<F>,
{
    fn new(circuit: &'a C, suite: &'a HashSuite<F>) -> Self {
        Self {
            circuit,
            suite,
            po2: 0,
            steps: 0,
            out: None,
            mix: Vec::new(),
            tap_cache: RefCell::new(None),
        }
    }

    // Compute the FRI verify taps sum.
    #[allow(clippy::too_many_arguments)]
    fn fri_eval_taps(
        &self,
        taps: &TapSet<'static>,
        mix: F::ExtElem,
        combo_u: &[F::ExtElem],
        check_row: &[F::Elem],
        back_one: F::Elem,
        x: F::Elem,
        z: F::ExtElem,
        rows: [&[F::Elem]; 3],
    ) -> F::ExtElem {
        let mut tot = vec![F::ExtElem::ZERO; taps.combos_size() + 1];
        let combo_count = taps.combos_size();
        let x = F::ExtElem::from_subfield(&x);

        let mut tap_cache = self.tap_cache.borrow_mut();
        if let Some(ref c) = &mut *tap_cache {
            if c.taps != taps || c.mix != mix {
                // tracing::debug!("Resetting tap cache");
                tap_cache.take();
            }
        }
        if tap_cache.is_none() {
            let mut cur_mix = F::ExtElem::ONE;
            let mut tap_mix_pows = Vec::with_capacity(taps.reg_count());
            for _reg in taps.regs() {
                tap_mix_pows.push(cur_mix);
                cur_mix *= mix;
            }
            assert_eq!(
                tap_mix_pows.len(),
                taps.reg_count(),
                "Miscalculated capacity for tap_mix_pows"
            );
            let mut check_mix_pows = Vec::with_capacity(Self::CHECK_SIZE);
            for _ in 0..Self::CHECK_SIZE {
                check_mix_pows.push(cur_mix);
                cur_mix *= mix;
            }

            tap_cache.replace(TapCache {
                taps,
                mix,
                tap_mix_pows,
                check_mix_pows,
            });
        }
        let tap_cache = tap_cache.as_ref().unwrap();

        for (reg, cur) in zip(taps.regs(), tap_cache.tap_mix_pows.iter()) {
            tot[reg.combo_id()] += *cur * rows[reg.group()][reg.offset()];
        }
        for (i, cur) in zip(0..Self::CHECK_SIZE, tap_cache.check_mix_pows.iter()) {
            tot[combo_count] += *cur * check_row[i];
        }
        let mut ret = F::ExtElem::ZERO;
        for i in 0..combo_count {
            let num = tot[i]
                - self.poly_eval(
                    &combo_u[taps.combo_begin[i] as usize..taps.combo_begin[i + 1] as usize],
                    x,
                );
            let mut divisor = F::ExtElem::ONE;
            for back in taps.get_combo(i).slice() {
                divisor *= x - z * back_one.pow(*back as usize);
            }
            ret += num * divisor.inv();
        }
        let check_num = tot[combo_count] - combo_u[taps.tot_combo_backs];
        let check_div = x - z.pow(INV_RATE);
        ret += check_num * check_div.inv();
        ret
    }

    fn verify<CheckCodeFn>(
        &mut self,
        seal: &'a [u32],
        check_code: CheckCodeFn,
    ) -> Result<(), VerificationError>
    where
        CheckCodeFn: Fn(u32, &Digest) -> Result<(), VerificationError>,
    {
        if seal.is_empty() {
            return Err(VerificationError::ReceiptFormatError);
        }

        let taps = self.circuit.get_taps();
        let hashfn = self.suite.hashfn.as_ref();

        // Make IOP
        let mut iop = ReadIOP::new(seal, self.suite.rng.as_ref());

        // At the start of the protocol, seed the Fiat-Shamir transcript with context information
        // about the proof system and circuit.
        iop.commit(&hashfn.hash_elem_slice(&PROOF_SYSTEM_INFO.encode()));
        iop.commit(&hashfn.hash_elem_slice(&C::CIRCUIT_INFO.encode()));

        // Read any execution state
        self.execute(&mut iop);

        // Get the size
        assert!(self.po2 as usize <= MAX_CYCLES_PO2);
        let size = 1 << self.po2;
        let domain = INV_RATE * size;
        // tracing::debug!("size = {size}, po2 = {po2}");

        // Get taps and compute sizes
        let code_size = taps.group_size(REGISTER_GROUP_CODE);
        let data_size = taps.group_size(REGISTER_GROUP_DATA);
        let accum_size = taps.group_size(REGISTER_GROUP_ACCUM);

        // Get merkle root for the code merkle tree.
        // The code merkle tree contains the control instructions for the zkVM.
        #[cfg(not(target_os = "zkvm"))]
        tracing::debug!("code_merkle");
        let code_merkle = MerkleTreeVerifier::new(&mut iop, hashfn, domain, code_size, QUERIES);
        // tracing::debug!("codeRoot = {}", code_merkle.root());
        check_code(self.po2, code_merkle.root())?;

        // Get merkle root for the data merkle tree.
        // The data merkle tree contains the execution trace of the program being run,
        // including memory accesses as well as the permutation of those memory
        // accesses sorted by location used by PLONK.
        #[cfg(not(target_os = "zkvm"))]
        tracing::debug!("data_merkle");
        let data_merkle = MerkleTreeVerifier::new(&mut iop, hashfn, domain, data_size, QUERIES);
        // tracing::debug!("dataRoot = {}", data_merkle.root());

        // Prep accumulation
        #[cfg(not(target_os = "zkvm"))]
        tracing::debug!("accumulate");
        // Fill in accum mix
        self.mix = (0..C::MIX_SIZE).map(|_| iop.random_elem()).collect();

        // Get merkle root for the accum merkle tree.
        // The accum merkle tree contains the accumulations for two permutation check
        // arguments: Each permutation check consists of a pre-permutation
        // accumulation and a post-permutation accumulation.
        // The first permutation check uses memory-based values (see PLONK paper for
        // details). This permutation is used to re-order memory accesses for
        // quicker verification. The second permutation check uses bytes-based
        // values (see PLOOKUP paper for details). This permutation is used to
        // implement a look-up table.
        #[cfg(not(target_os = "zkvm"))]
        tracing::debug!("accum_merkle");
        let accum_merkle = MerkleTreeVerifier::new(&mut iop, hashfn, domain, accum_size, QUERIES);
        // tracing::debug!("accumRoot = {}", accum_merkle.root());

        // Get a pseudorandom value with which to mix the constraint polynomials.
        // See DEEP-ALI protocol from DEEP-FRI paper for details on constraint mixing.
        let poly_mix = iop.random_ext_elem();

        #[cfg(not(target_os = "zkvm"))]
        tracing::debug!("check_merkle");
        let check_merkle =
            MerkleTreeVerifier::new(&mut iop, hashfn, domain, Self::CHECK_SIZE, QUERIES);
        // tracing::debug!("checkRoot = {}", check_merkle.root());

        // Get a pseudorandom DEEP query point
        // See DEEP-ALI protocol from DEEP-FRI paper for details on DEEP query.
        let z = iop.random_ext_elem();
        // tracing::debug!("Z = {z:?}");
        let back_one = F::Elem::ROU_REV[self.po2 as usize];

        // Read the U coeffs (the interpolations of the taps) + commit their hash.
        let num_taps = taps.tap_size();
        let coeff_u = iop.read_field_elem_slice(num_taps + Self::CHECK_SIZE);
        let hash_u = self.suite.hashfn.hash_ext_elem_slice(coeff_u);
        iop.commit(&hash_u);

        // Now, convert U polynomials from coefficient form to evaluation form
        let mut cur_pos = 0;
        let mut eval_u = Vec::with_capacity(num_taps);
        for reg in taps.regs() {
            for i in 0..reg.size() {
                let x = z * back_one.pow(reg.back(i));
                let fx = self.poly_eval(&coeff_u[cur_pos..(cur_pos + reg.size())], x);
                eval_u.push(fx);
            }
            cur_pos += reg.size();
        }
        assert_eq!(eval_u.len(), num_taps, "Miscalculated capacity for eval_us");

        // Compute the core constraint polynomial.
        // I.e. the set of all constraints mixed by poly_mix
        #[cfg(not(target_os = "zkvm"))]
        tracing::debug!("> compute_polynomial");
        // let result = self.compute_polynomial(&eval_u, poly_mix);
        let result = self
            .circuit
            .poly_ext(&poly_mix, &eval_u, &[self.out.unwrap(), &self.mix])
            .tot;

        #[cfg(not(target_os = "zkvm"))]
        tracing::debug!("< compute_polynomial");
        // tracing::debug!("Result = {result:?}");

        // Now generate the check polynomial
        // TODO: This currently treats the extension degree as hardcoded at 4, with
        // the structure of the code and the value of `remap` (and how it is
        // accessed) only working in the extension degree = 4 case.
        // However, for generic fields the extension degree may be different
        // TODO: Therefore just using the to/from baby bear shims for now
        let mut check = F::ExtElem::default();
        let remap = [0, 2, 1, 3];
        let fp0 = F::Elem::ZERO;
        let fp1 = F::Elem::ONE;
        for (i, rmi) in remap.iter().enumerate() {
            check += coeff_u[num_taps + rmi]
                * z.pow(i)
                * F::ExtElem::from_subelems([fp1, fp0, fp0, fp0]);
            check += coeff_u[num_taps + rmi + 4]
                * z.pow(i)
                * F::ExtElem::from_subelems([fp0, fp1, fp0, fp0]);
            check += coeff_u[num_taps + rmi + 8]
                * z.pow(i)
                * F::ExtElem::from_subelems([fp0, fp0, fp1, fp0]);
            check += coeff_u[num_taps + rmi + 12]
                * z.pow(i)
                * F::ExtElem::from_subelems([fp0, fp0, fp0, fp1]);
        }
        let three = F::Elem::from_u64(3);
        check *= (F::ExtElem::from_subfield(&three) * z).pow(size) - F::ExtElem::ONE;
        // tracing::debug!("Check = {check:?}");
        if check != result {
            return Err(VerificationError::InvalidProof);
        }

        // Set the mix value, pseudorandom value used for FRI batching
        let mix = iop.random_ext_elem();
        // tracing::debug!("mix = {mix:?}");

        // Make the mixed U polynomials.
        // combo_u has one element for each column with the same set of taps.
        // These columns share a denominator in the DEEP-ALI equation.
        // We group these terms together to reduce the number of inverses we
        // need to compute.
        let mut combo_u: Vec<F::ExtElem> = vec![F::ExtElem::ZERO; taps.tot_combo_backs + 1];
        let mut cur_mix = F::ExtElem::ONE;
        cur_pos = 0;
        let mut tap_mix_pows = Vec::with_capacity(taps.reg_count());
        for reg in taps.regs() {
            for i in 0..reg.size() {
                combo_u[taps.combo_begin[reg.combo_id()] as usize + i] +=
                    cur_mix * coeff_u[cur_pos + i];
            }
            tap_mix_pows.push(cur_mix);
            cur_mix *= mix;
            cur_pos += reg.size();
        }
        assert_eq!(
            tap_mix_pows.len(),
            taps.reg_count(),
            "Miscalculated capacity for tap_mix_pows"
        );
        // tracing::debug!("cur_mix: {cur_mix:?}, cur_pos: {cur_pos}");
        // Handle check group
        let mut check_mix_pows = Vec::with_capacity(Self::CHECK_SIZE);
        for _ in 0..Self::CHECK_SIZE {
            combo_u[taps.tot_combo_backs] += cur_mix * coeff_u[cur_pos];
            cur_pos += 1;
            check_mix_pows.push(cur_mix);
            cur_mix *= mix;
        }
        assert_eq!(
            check_mix_pows.len(),
            Self::CHECK_SIZE,
            "Miscalculated capacity for check_mix_pows"
        );
        // tracing::debug!("cur_mix: {cur_mix:?}");

        let gen = <F::Elem as RootsOfUnity>::ROU_FWD[log2_ceil(domain)];
        // tracing::debug!("FRI-verify, size = {size}");
        self.fri_verify(&mut iop, size, |iop, idx| {
            // tracing::debug!("fri_verify");
            let x = gen.pow(idx);
            let rows = [
                accum_merkle.verify(iop, hashfn, idx)?,
                code_merkle.verify(iop, hashfn, idx)?,
                data_merkle.verify(iop, hashfn, idx)?,
            ];
            let check_row = check_merkle.verify(iop, hashfn, idx)?;
            let ret = self.fri_eval_taps(taps, mix, &combo_u, check_row, back_one, x, z, rows);
            Ok(ret)
        })?;
        iop.verify_complete();
        Ok(())
    }

    /// Read the globals (i.e. outputs) from the IOP, and mix them into the Fiat-Shamir state.
    ///
    /// NOTE: The globals are the only values known to the verifier, and constitute the public
    /// statement of the prover. In many scenarios, they are the first values sent to the
    /// verifier by the prover, and therefore should be committed at the start of verification.
    fn execute(&mut self, iop: &mut ReadIOP<'a, F>) {
        let slice = iop.read_field_elem_slice(C::OUTPUT_SIZE + 1);
        iop.commit(&self.suite.hashfn.hash_elem_slice(slice));

        // Extract the out buffer and po2 from slice while checking sizes.
        let (out, &[po2_elem]) = slice.split_at(C::OUTPUT_SIZE) else {
            unreachable!()
        };
        self.out = Some(out);
        let (&[po2], &[]) = po2_elem.to_u32_words().split_at(1) else {
            panic!("po2 elem is larger than u32");
        };
        self.po2 = po2;
        self.steps = 1usize.checked_shl(po2).unwrap();
    }

    /// Evaluate a polynomial whose coefficients are in the extension field at a
    /// point.
    fn poly_eval(&self, coeffs: &[F::ExtElem], x: F::ExtElem) -> F::ExtElem {
        let mut mul_x = F::ExtElem::ONE;
        let mut tot = F::ExtElem::ZERO;
        for coeff in coeffs {
            tot += *coeff * mul_x;
            mul_x *= x;
        }
        tot
    }
}

/// Verify a seal is valid for the given circuit, and code checking function.
#[must_use]
#[tracing::instrument(skip_all)]
pub fn verify<F, C, CheckCode>(
    circuit: &C,
    suite: &HashSuite<F>,
    seal: &[u32],
    check_code: CheckCode,
) -> Result<(), VerificationError>
where
    F: Field,
    C: CircuitCoreDef<F>,
    CheckCode: Fn(u32, &Digest) -> Result<(), VerificationError>,
{
    Verifier::<F, C>::new(circuit, suite).verify(seal, check_code)
}
