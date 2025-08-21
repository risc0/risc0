// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! Cryptographic algorithms for verifying a ZK proof of compute

mod fri;
mod merkle;
mod read_iop;

use alloc::{vec, vec::Vec};
use core::{
    cell::{RefCell, RefMut},
    fmt,
    iter::zip,
    ops::DerefMut,
};

pub(crate) use merkle::MerkleTreeVerifier;
pub use read_iop::ReadIOP;
use risc0_core::field::{Elem, ExtElem, Field, RootsOfUnity};

use crate::{
    INV_RATE, MAX_CYCLES_PO2, QUERIES,
    adapter::{
        CircuitCoreDef, CircuitCoreDefV3, PROOF_SYSTEM_INFO, ProtocolInfo, REGISTER_GROUP_ACCUM,
        REGISTER_GROUP_CODE, REGISTER_GROUP_DATA,
    },
    core::{digest::Digest, hash::HashSuite, log2_ceil},
    taps::TapSet,
};

// If true, enable tracing of verifier internals.
const VERIFY_TRACE_ENABLED: bool = false;

macro_rules! trace_if_enabled {
    ($($args:tt)*) => {
        if VERIFY_TRACE_ENABLED {
            #[cfg(not(target_os = "zkvm"))]
            tracing::debug!($($args)*);
        }
    }
}

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
                write!(
                    f,
                    "claim digest does not match the expected digest {received}; expected {expected}"
                )
            }
            VerificationError::UnexpectedExitCode => write!(f, "unexpected exit_code"),
            VerificationError::InvalidHashSuite => write!(f, "invalid hash suite"),
            VerificationError::VerifierParametersMissing => {
                write!(
                    f,
                    "verifier parameters were not found in verifier context for the given receipt type"
                )
            }
            VerificationError::VerifierParametersMismatch { expected, received } => {
                write!(
                    f,
                    "receipt was produced for a version of the verifier with parameters digest {received}; expected {expected}"
                )
            }
            VerificationError::ProofSystemInfoMismatch { expected, received } => {
                write!(
                    f,
                    "receipt was produced for a version of the verifier with proof system info {received}; expected {expected}"
                )
            }
            VerificationError::CircuitInfoMismatch { expected, received } => {
                write!(
                    f,
                    "receipt was produced for a version of the verifier with circuit info {received}; expected {expected}"
                )
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

#[stability::unstable]
pub struct Verifier<'a, F>
where
    F: Field,
{
    taps: &'a TapSet<'a>,
    suite: &'a HashSuite<F>,
    iop: RefCell<ReadIOP<'a, F>>,
    po2: usize,
    tot_cycles: usize,
    // Merkle tree verifiers, indexed by register group id
    merkle_verifiers: Vec<Option<MerkleTreeVerifier<'a>>>,
}

impl<F: Field> VerifyParams<F> for Verifier<'_, F> {}

impl<'a, F: Field> Verifier<'a, F> {
    /// Start a new verification session.
    #[stability::unstable]
    pub fn new(taps: &'a TapSet<'a>, suite: &'a HashSuite<F>, seal: &'a [u32]) -> Self {
        trace_if_enabled!("Starting verify");
        Self {
            taps,
            suite,
            po2: 0,
            tot_cycles: 0,
            iop: RefCell::new(ReadIOP::new(seal, suite.rng.as_ref())),
            // TODO: change this to core::iter::repeat_n once it's stabilized.
            merkle_verifiers: core::iter::repeat_with(|| None)
                .take(taps.num_groups())
                .collect(),
        }
    }

    #[stability::unstable]
    pub fn iop(&self) -> RefMut<'_, ReadIOP<'a, F>> {
        self.iop.borrow_mut()
    }

    #[stability::unstable]
    pub fn commit_circuit_info(&mut self, circuit_info: &ProtocolInfo) {
        trace_if_enabled!("Verifying protocol={PROOF_SYSTEM_INFO} circuit {circuit_info}");
        // At the start of the protocol, seed the Fiat-Shamir transcript with context information
        // about the proof system and circuit.
        let hashfn = self.suite.hashfn.as_ref();
        self.iop()
            .commit(&hashfn.hash_elem_slice(&PROOF_SYSTEM_INFO.encode()));
        self.iop()
            .commit(&hashfn.hash_elem_slice(&circuit_info.encode()));
    }

    /// Read in the next merkle group in the seal.  `reg_group_id` should be the group ID
    /// as specified in the taps.
    #[stability::unstable]
    pub fn verify_group(&mut self, reg_group_id: usize) -> Result<&Digest, VerificationError> {
        assert!(
            self.merkle_verifiers[reg_group_id].is_none(),
            "Reg group id {reg_group_id} ({}) may only occur once",
            self.taps.group_name(reg_group_id)
        );
        let group_size = self.taps.group_size(reg_group_id);
        let domain = INV_RATE * self.tot_cycles;
        let hashfn = self.suite.hashfn.as_ref();

        let merkle =
            MerkleTreeVerifier::new(self.iop().deref_mut(), hashfn, domain, group_size, QUERIES);
        self.merkle_verifiers[reg_group_id] = Some(merkle);
        let root = self.merkle_verifiers[reg_group_id].as_ref().unwrap().root();
        trace_if_enabled!(
            "{} (group id={reg_group_id}) root: {root:?}",
            self.taps.group_name(reg_group_id)
        );
        Ok(root)
    }

    /// Reads `elems` field elements of randomness from the IOP
    #[stability::unstable]
    pub fn read_rng(&mut self, elems: usize) -> Vec<F::Elem> {
        let mix = (0..elems).map(|_| self.iop().random_elem()).collect();
        trace_if_enabled!("Got mix values from IOP: {mix:?}");
        mix
    }

    #[allow(clippy::too_many_arguments)]
    // Compute the FRI verify taps sum.
    fn fri_eval_taps(
        &self,
        combo_u: &[F::ExtElem],
        check_row: &[F::Elem],
        back_one: F::Elem,
        x: F::Elem,
        z: F::ExtElem,
        rows: &[&[F::Elem]],
        tap_mix_pows: &[F::ExtElem],
        check_mix_pows: &[F::ExtElem],
    ) -> F::ExtElem {
        let mut tot = vec![F::ExtElem::ZERO; self.taps.combos_size() + 1];
        let combo_count = self.taps.combos_size();
        let x = F::ExtElem::from_subfield(&x);

        for (reg, cur) in zip(self.taps.regs(), tap_mix_pows.iter()) {
            tot[reg.combo_id()] += *cur * rows[reg.group()][reg.offset()];
        }
        for (i, cur) in zip(0..Self::CHECK_SIZE, check_mix_pows.iter()) {
            tot[combo_count] += *cur * check_row[i];
        }
        let mut ret = F::ExtElem::ZERO;
        for i in 0..combo_count {
            let num = tot[i]
                - self.poly_eval(
                    &combo_u
                        [self.taps.combo_begin[i] as usize..self.taps.combo_begin[i + 1] as usize],
                    x,
                );
            let mut divisor = F::ExtElem::ONE;
            for back in self.taps.get_combo(i).slice() {
                divisor *= x - z * back_one.pow(*back as usize);
            }
            ret += num * divisor.inv();
        }
        let check_num = tot[combo_count] - combo_u[self.taps.tot_combo_backs];
        let check_div = x - z.pow(INV_RATE);
        ret += check_num * check_div.inv();
        ret
    }

    /// Execute the IOP protocol to verify the validity polynomial
    /// such that all the constraints are satisfied.  This is
    /// currently only supported when called exactly once at the end
    /// of the verification.
    #[stability::unstable]
    pub fn verify_validity(
        &mut self,
        validity_fn: impl Fn(&F::ExtElem, &[F::ExtElem]) -> F::ExtElem,
    ) -> Result<(), VerificationError> {
        // Ensure that we were given verifiers for all tap groups
        for (reg_group_id, verifier) in self.merkle_verifiers.iter().enumerate() {
            if !verifier.is_some() {
                panic!(
                    "Missing merkle verifier for reg group {reg_group_id} ({})",
                    self.taps.group_name(reg_group_id)
                );
            }
        }

        // Get a pseudorandom value with which to mix the constraint polynomials.
        // See DEEP-ALI protocol from DEEP-FRI paper for details on constraint mixing.
        let poly_mix = self.iop().random_ext_elem();
        trace_if_enabled!("Poly mix: {poly_mix:?}");

        let hashfn = self.suite.hashfn.as_ref();
        let domain = INV_RATE * self.tot_cycles;
        let check_merkle = MerkleTreeVerifier::new(
            self.iop().deref_mut(),
            hashfn,
            domain,
            Self::CHECK_SIZE,
            QUERIES,
        );
        trace_if_enabled!("Check merkle root: {}", check_merkle.root());

        // Get a pseudorandom DEEP query point
        // See DEEP-ALI protocol from DEEP-FRI paper for details on DEEP query.
        cfg_if::cfg_if! {
            if #[cfg(feature = "circuit_debug")] {
                let z_slice = self.iop().read_field_elem_slice(F::ExtElem::EXT_SIZE);
                let z = F::ExtElem::from_subelems(z_slice.iter().cloned());
            } else {
                let z = self.iop().random_ext_elem();
            }
        }

        trace_if_enabled!("Z = {z:?}");
        let back_one = F::Elem::ROU_REV[self.po2];

        // Read the U coeffs (the interpolations of the taps) + commit their hash.
        let num_taps = self.taps.tap_size();
        let coeff_u = self
            .iop()
            .read_field_elem_slice(num_taps + Self::CHECK_SIZE);
        let hash_u = hashfn.hash_ext_elem_slice(coeff_u);
        self.iop().commit(&hash_u);

        // Now, convert U polynomials from coefficient form to evaluation form
        let mut cur_pos = 0;
        let mut eval_u = Vec::with_capacity(num_taps);
        for reg in self.taps.regs() {
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

        let result = validity_fn(&poly_mix, &eval_u);
        trace_if_enabled!("Computed polynomial: {result:?}");

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
        check *= (F::ExtElem::from_subfield(&three) * z).pow(self.tot_cycles) - F::ExtElem::ONE;
        trace_if_enabled!("Check = {check:?}");
        if check != result {
            tracing::debug!("check != result");
            return Err(VerificationError::InvalidProof);
        }

        // Set the mix value, pseudorandom value used for FRI batching
        let mix = self.iop().random_ext_elem();
        trace_if_enabled!("FRI mix = {mix:?}");

        // Fill in

        // Make the mixed U polynomials.
        // combo_u has one element for each column with the same set of taps.
        // These columns share a denominator in the DEEP-ALI equation.
        // We group these terms together to reduce the number of inverses we
        // need to compute.
        let mut combo_u: Vec<F::ExtElem> = vec![F::ExtElem::ZERO; self.taps.tot_combo_backs + 1];
        let mut cur_mix = F::ExtElem::ONE;
        cur_pos = 0;
        let mut tap_mix_pows = Vec::with_capacity(self.taps.reg_count());
        for reg in self.taps.regs() {
            for i in 0..reg.size() {
                combo_u[self.taps.combo_begin[reg.combo_id()] as usize + i] +=
                    cur_mix * coeff_u[cur_pos + i];
            }
            tap_mix_pows.push(cur_mix);
            cur_mix *= mix;
            cur_pos += reg.size();
        }
        assert_eq!(
            tap_mix_pows.len(),
            self.taps.reg_count(),
            "Miscalculated capacity for tap_mix_pows"
        );
        trace_if_enabled!("cur_mix: {cur_mix:?}, cur_pos: {cur_pos}");
        // Handle check group
        let mut check_mix_pows = Vec::with_capacity(Self::CHECK_SIZE);
        for _ in 0..Self::CHECK_SIZE {
            combo_u[self.taps.tot_combo_backs] += cur_mix * coeff_u[cur_pos];
            cur_pos += 1;
            check_mix_pows.push(cur_mix);
            cur_mix *= mix;
        }
        assert_eq!(
            check_mix_pows.len(),
            Self::CHECK_SIZE,
            "Miscalculated capacity for check_mix_pows"
        );
        let gen_ = <F::Elem as RootsOfUnity>::ROU_FWD[log2_ceil(domain)];
        let hashfn = self.suite.hashfn.as_ref();
        self.fri_verify(|idx| {
            let x = gen_.pow(idx);
            let rows= self
                .merkle_verifiers
                .iter()
                .map(|merkle: &Option<MerkleTreeVerifier>| -> Result<&'a [F::Elem], VerificationError> {
                    merkle.as_ref()
                        .unwrap()
                        .verify(self.iop().deref_mut(), hashfn, idx)
                })
                .collect::<Result<Vec<_>,_>>()?;
            let check_row = check_merkle.verify(self.iop().deref_mut(),hashfn, idx)?;
            let ret = self.fri_eval_taps(&combo_u, check_row, back_one, x, z, &rows, &tap_mix_pows, &check_mix_pows);
            Ok(ret)
        })?;
        Ok(())
    }

    /// Reads a slice of `size` field elements from the IOP along with
    /// the po2 of the number of cycles the circuit ran for, and
    /// commits to them.  This is typically used at the beginning of
    /// the seal to encode the globals of the circuit.
    #[stability::unstable]
    pub fn read_slice_with_po2(&mut self, size: usize) -> (&'a [F::Elem], usize) {
        let slice = self.iop().read_field_elem_slice(size + 1);
        self.iop().commit(&self.suite.hashfn.hash_elem_slice(slice));

        // Extract the out buffer and po2 from slice while checking sizes.
        let (out, &[po2_elem]) = slice.split_at(size) else {
            unreachable!()
        };
        let (&[po2], &[]) = po2_elem.to_u32_words().split_at(1) else {
            panic!("po2 elem is larger than u32");
        };
        self.po2 = po2 as usize;
        assert!(self.po2 <= MAX_CYCLES_PO2);
        self.tot_cycles = 1usize.checked_shl(po2).unwrap();
        (out, self.po2)
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
///
/// This version of `verify` has a fixed IOP protocol that's used by
/// multiple circuits.
// Circuits that don't share this protocol may use [Verifier] directly once it's stabilized.
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
    if seal.is_empty() {
        return Err(VerificationError::ReceiptFormatError);
    }

    let mut verifier = Verifier::<F>::new(circuit.get_taps(), suite, seal);
    verifier.commit_circuit_info(&C::CIRCUIT_INFO);

    // Read the globals (i.e. outputs) from the IOP, and mix them into the Fiat-Shamir state.
    //
    // NOTE: The globals are the only values known to the verifier, and constitute the public
    // statement of the prover. In many scenarios, they are the first values sent to the
    // verifier by the prover, and therefore should be committed at the start of verification.
    let (out, po2) = verifier.read_slice_with_po2(C::OUTPUT_SIZE);

    // Get merkle root for the code merkle tree.
    // The code merkle tree contains the control instructions for the zkVM.
    let code_root = verifier.verify_group(REGISTER_GROUP_CODE)?;

    // Invoke the user-supplied verification function to ensure that
    // the code root of the merkle tree is as expected.
    check_code(po2 as u32, code_root)?;

    // Get merkle root for the data merkle tree.
    // The data merkle tree contains the execution trace of the program being run,
    // including memory accesses as well as the permutation of those memory
    // accesses sorted by location used by PLONK.
    verifier.verify_group(REGISTER_GROUP_DATA)?;

    // Fill in accum mix
    let mix = verifier.read_rng(C::MIX_SIZE);

    // Get merkle root for the accum merkle tree.
    // The accum merkle tree contains the accumulations for two permutation check
    // arguments: Each permutation check consists of a pre-permutation
    // accumulation and a post-permutation accumulation.
    // The first permutation check uses memory-based values (see PLONK paper for
    // details). This permutation is used to re-order memory accesses for
    // quicker verification. The second permutation check uses bytes-based
    // values (see PLOOKUP paper for details). This permutation is used to
    // implement a look-up table.
    verifier.verify_group(REGISTER_GROUP_ACCUM)?;

    // Verify the evaluation of the validity polynomial to make sure
    // the constraints were not violated.
    verifier
        .verify_validity(|poly_mix, eval_u| circuit.poly_ext(poly_mix, eval_u, &[out, &mix]).tot)?;

    // There should be nothing else in the IOP, so verify that's the case.
    verifier.iop().verify_complete();
    Ok(())
}

/// Verify a seal is valid for the given circuit. This implements a different IOP
/// protocol than the other `verify` function above, and is used for circuits in
/// the architecture of the v3 circuit.
pub fn verify_v3<F, C>(
    circuit: &C,
    suite: &HashSuite<F>,
    seal: &[u32],
    po2: usize,
) -> Result<(), VerificationError>
where
    F: Field,
    C: CircuitCoreDefV3<F>,
{
    if seal.is_empty() {
        return Err(VerificationError::ReceiptFormatError);
    }

    let mut mix: Vec<F::Elem> = vec![];
    let mut globals: Vec<F::Elem> = vec![];
    let mut verifier = Verifier::<F>::new(circuit.get_taps(), suite, seal);
    verifier.po2 = po2;
    verifier.tot_cycles = 1 << po2;

    for (i, group) in circuit.get_groups().iter().enumerate() {
        // Draw Fiat-Shamir randomness for the group.
        mix.extend(verifier.read_rng(group.mix_count));

        // Commit to the globals for the group.
        if group.global_count > 0 {
            let group_globals = verifier.iop().read_field_elem_slice(group.global_count);
            globals.extend(group_globals);
            verifier
                .iop()
                .commit(&suite.hashfn.hash_elem_slice(group_globals));
        }

        // Verify merkle root for the group.
        verifier.verify_group(i)?;
    }

    // Verify the evaluation of the validity polynomial to make sure
    // the constraints were not violated.
    verifier.verify_validity(|poly_mix, eval_u| {
        circuit.poly_ext(poly_mix, eval_u, &[&globals, &mix]).tot
    })?;

    // There should be nothing else in the IOP, so verify that's the case.
    verifier.iop().verify_complete();
    Ok(())
}

#[cfg(test)]
mod test {
    use risc0_core::field::{
        Elem,
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
    };

    use crate::{
        adapter::{CircuitCoreDefV3, CircuitInfoV3, GroupInfo, MixState, PolyExt, TapsProvider},
        core::hash::poseidon2::Poseidon2HashSuite,
        taps::{TapData, TapSet},
        verify::verify_v3,
    };

    pub const TAPSET: &TapSet = &TapSet::<'static> {
        taps: &[
            TapData {
                offset: 0,
                back: 0,
                group: 0,
                combo: 0,
                skip: 1,
            },
            TapData {
                offset: 0,
                back: 0,
                group: 1,
                combo: 0,
                skip: 1,
            },
            TapData {
                offset: 0,
                back: 0,
                group: 2,
                combo: 0,
                skip: 1,
            },
        ],
        combo_taps: &[0],
        combo_begin: &[0, 1],
        group_begin: &[0, 1, 2, 3],
        combos_count: 1,
        reg_count: 3,
        tot_combo_backs: 1,
        group_names: &["accum", "code", "data"],
    };

    struct HelloCircuit {}
    impl CircuitInfoV3 for HelloCircuit {
        fn get_groups(&self) -> &'static [GroupInfo] {
            &[
                GroupInfo {
                    global_count: 0,
                    mix_count: 0,
                },
                GroupInfo {
                    global_count: 0,
                    mix_count: 0,
                },
                GroupInfo {
                    global_count: 0,
                    mix_count: 0,
                },
            ]
        }
    }
    impl PolyExt<BabyBear> for HelloCircuit {
        fn poly_ext(
            &self,
            mix: &BabyBearExtElem,
            u: &[BabyBearExtElem],
            _args: &[&[BabyBearElem]],
        ) -> MixState<BabyBearExtElem> {
            let mut state = MixState::<BabyBearExtElem> {
                tot: BabyBearExtElem::ZERO,
                mul: BabyBearExtElem::ONE,
            };
            let mut eqz = |inner: BabyBearExtElem| {
                state = MixState {
                    tot: state.tot + state.mul * inner,
                    mul: state.mul * *mix,
                };
            };

            eqz(u[0]);
            eqz(u[1]);
            eqz(u[2] * (u[2] - BabyBearExtElem::from_u32(1)));
            state
        }
    }
    impl TapsProvider for HelloCircuit {
        fn get_taps(&self) -> &'static TapSet<'static> {
            TAPSET
        }
    }
    impl CircuitCoreDefV3<BabyBear> for HelloCircuit {}

    #[test]
    fn verify_v3_stark_proof() {
        let transcript: Vec<u32> = include_bytes!("proof.bin")
            .chunks_exact(4)
            .map(|chunk| u32::from_le_bytes(chunk.try_into().unwrap()))
            // .map(|x| BabyBearElem::new(x).as_u32_montgomery())
            .collect();

        let circuit = HelloCircuit {};
        let suite = Poseidon2HashSuite::new_suite();
        let x = verify_v3(&circuit, &suite, &transcript, 12);
        match x {
            Ok(_) => {}
            Err(e) => panic!("Failed to verify: {e}"),
        }
    }
}
