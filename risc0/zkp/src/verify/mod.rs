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

pub mod adapter;
mod fri;
pub(crate) mod merkle;
pub mod read_iop;

use alloc::{vec, vec::Vec};
use core::fmt;

#[cfg(not(target_os = "zkvm"))]
pub use host::CpuVerifyHal;
use risc0_zeroio::WORD_SIZE;

use self::adapter::VerifyAdapter;
use crate::{
    adapter::{CircuitInfo, TapsProvider},
    core::{
        log2_ceil,
        sha::{Digest, Sha, DIGEST_WORDS},
    },
    field::{Elem, ExtElem, RootsOfUnity},
    taps::{RegisterGroup, TapSet},
    verify::{fri::fri_verify, merkle::MerkleTreeVerifier, read_iop::ReadIOP},
    FRI_FOLD, INV_RATE, MAX_CYCLES_PO2, QUERIES,
};

#[derive(Debug)]
pub enum VerificationError {
    ReceiptFormatError,
    MethodCycleError { required: usize },
    MethodVerificationError,
    MerkleQueryOutOfRange { idx: usize, rows: usize },
    InvalidProof,
    JournalSealRootMismatch,
    SealJournalLengthMismatch { seal_len: usize, journal_len: usize },
}

impl fmt::Display for VerificationError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            VerificationError::ReceiptFormatError => write!(f, "invalid receipt format"),
            VerificationError::MethodCycleError { required } => {
                write!(f, "Method execution cycle exceeded code limit. Increase code limit to at least {required}.")
            }
            VerificationError::MethodVerificationError => write!(f, "method verification failed"),
            VerificationError::MerkleQueryOutOfRange { idx, rows } => write!(
                f,
                "Requested Merkle validation on row {idx}, but only {rows} rows exist",
            ),
            VerificationError::InvalidProof => write!(f, "Verification indicates proof is invalid"),
            VerificationError::JournalSealRootMismatch => {
                write!(f, "Journal and seal root mismatch detected")
            }
            VerificationError::SealJournalLengthMismatch {
                seal_len,
                journal_len,
            } => write!(
                f,
                "Seal's output length ({seal_len}) does not match journal length ({journal_len})"
            ),
        }
    }
}

pub trait VerifyHal {
    type Sha: Sha;
    type Elem: Elem + RootsOfUnity;
    type ExtElem: ExtElem<SubElem = Self::Elem>;

    const CHECK_SIZE: usize = INV_RATE * Self::ExtElem::EXT_SIZE;

    fn sha(&self) -> &Self::Sha;

    fn debug(&self, msg: &str);

    fn compute_polynomial(
        &self,
        u: &[Self::ExtElem],
        poly_mix: Self::ExtElem,
        out: &[Self::Elem],
        mix: &[Self::Elem],
    ) -> Self::ExtElem;

    fn fold_eval(&self, io: &mut [Self::ExtElem; FRI_FOLD], x: Self::ExtElem) -> Self::ExtElem;

    /// Evaluate a polynomial whose coefficients are in the extension field at a
    /// point.
    fn poly_eval(&self, coeffs: &[Self::ExtElem], x: Self::ExtElem) -> Self::ExtElem;

    // Compute the FRI verify taps sum.
    fn fri_eval_taps(
        &self,
        taps: &TapSet<'static>,
        mix: Self::ExtElem,
        combo_u: &[Self::ExtElem],
        check_row: &[Self::Elem],
        back_one: Self::Elem,
        x: Self::Elem,
        z: Self::ExtElem,
        rows: [&[Self::Elem]; 3],
    ) -> Self::ExtElem;
}

#[cfg(not(target_os = "zkvm"))]
mod host {
    use alloc::collections::BTreeMap;
    use core::{cell::RefCell, iter::zip};

    use super::*;
    use crate::{
        adapter::PolyExt,
        core::ntt::{bit_reverse, interpolate_ntt},
        field::Field,
        FRI_FOLD,
    };

    struct TapCache<F: Field> {
        tap_mix_pows: Vec<F::ExtElem>,
        check_mix_pows: Vec<F::ExtElem>,
    }

    pub struct CpuVerifyHal<'a, S: Sha, F: Field, C: PolyExt<F>> {
        sha: &'a S,
        circuit: &'a C,
        tap_cache: RefCell<BTreeMap<*const TapSet<'static>, TapCache<F>>>,
    }

    impl<'a, S: Sha, F: Field, C: PolyExt<F>> CpuVerifyHal<'a, S, F, C> {
        pub fn new(sha: &'a S, circuit: &'a C) -> Self {
            Self {
                sha,
                circuit,
                tap_cache: RefCell::new(BTreeMap::new()),
            }
        }
    }

    impl<'a, S: Sha, F: Field, C: PolyExt<F>> VerifyHal for CpuVerifyHal<'a, S, F, C> {
        type Sha = S;
        type Elem = F::Elem;
        type ExtElem = F::ExtElem;

        fn sha(&self) -> &Self::Sha {
            self.sha
        }

        fn debug(&self, msg: &str) {
            log::debug!("{}", msg);
        }

        fn fold_eval(&self, io: &mut [Self::ExtElem; FRI_FOLD], x: Self::ExtElem) -> Self::ExtElem {
            interpolate_ntt::<Self::Elem, Self::ExtElem>(io);
            bit_reverse(io);
            self.poly_eval(io, x)
        }

        fn poly_eval(&self, coeffs: &[Self::ExtElem], x: Self::ExtElem) -> Self::ExtElem {
            let mut mul_x = Self::ExtElem::ONE;
            let mut tot = Self::ExtElem::ZERO;
            for i in 0..coeffs.len() {
                tot += coeffs[i] * mul_x;
                mul_x *= x;
            }
            tot
        }

        fn compute_polynomial(
            &self,
            u: &[Self::ExtElem],
            poly_mix: Self::ExtElem,
            out: &[Self::Elem],
            mix: &[Self::Elem],
        ) -> Self::ExtElem {
            self.circuit.poly_ext(&poly_mix, u, &[out, mix]).tot
        }

        fn fri_eval_taps(
            &self,
            taps: &TapSet<'static>,
            mix: Self::ExtElem,
            combo_u: &[Self::ExtElem],
            check_row: &[Self::Elem],
            back_one: Self::Elem,
            x: Self::Elem,
            z: Self::ExtElem,
            rows: [&[Self::Elem]; 3],
        ) -> Self::ExtElem {
            let mut tot = vec![Self::ExtElem::ZERO; taps.combos_size() + 1];
            let combo_count = taps.combos_size();
            let x = Self::ExtElem::from_subfield(&x);

            let mut tap_cache_lock = self.tap_cache.borrow_mut();
            let tap_cache = tap_cache_lock.entry(taps).or_insert_with(|| {
                let mut cur_mix = Self::ExtElem::ONE;
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

                TapCache {
                    tap_mix_pows,
                    check_mix_pows,
                }
            });
            for (reg, cur) in zip(taps.regs(), tap_cache.tap_mix_pows.iter()) {
                tot[reg.combo_id()] += *cur * rows[reg.group() as usize][reg.offset()];
            }
            for (i, cur) in zip(0..Self::CHECK_SIZE, tap_cache.check_mix_pows.iter()) {
                tot[combo_count] += *cur * check_row[i];
            }
            let mut ret = Self::ExtElem::ZERO;
            for i in 0..combo_count {
                let num = tot[i]
                    - self.poly_eval(
                        &combo_u[taps.combo_begin[i] as usize..taps.combo_begin[i + 1] as usize],
                        x,
                    );
                let mut divisor = Self::ExtElem::ONE;
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
    }
}

#[tracing::instrument(skip_all)]
pub fn verify<'a, H, C, F>(
    hal: &'a H,
    circuit: &C,
    seal: &'a [u32],
    journal: &'a [u32],
    check_code: F,
) -> Result<(), VerificationError>
where
    H: VerifyHal,
    C: CircuitInfo + TapsProvider,
    F: Fn(u32, &Digest) -> Result<(), VerificationError>,
{
    if seal.len() == 0 {
        return Err(VerificationError::ReceiptFormatError);
    }

    let mut adapter = VerifyAdapter::new(circuit);
    let taps = adapter.taps();

    // Make IOP
    let mut iop = ReadIOP::new(hal.sha(), seal);

    // Read any execution state
    adapter.execute(&mut iop);

    if let Some(outputs) = adapter.out {
        let result_length_index = 16;
        // Each element outputs are generated by the output ecall. The handler for the
        // output ecall splits the 32-bit value supplied to the ecall into two
        // 16-bit chunks. Since each index of the journal contains all 32 bits
        // of the output ecall value, we must shift and combine the two 16-bit
        // values before comparing them to the journal.
        let output_len = u32::from(outputs[result_length_index])
            + u32::from(outputs[result_length_index + 1])
                .checked_shl(16)
                .unwrap();
        if journal.len() * WORD_SIZE != output_len.try_into().unwrap() {
            return Err(VerificationError::SealJournalLengthMismatch {
                seal_len: output_len.try_into().unwrap(),
                journal_len: journal.len() * WORD_SIZE,
            });
        }
        if journal.len() <= DIGEST_WORDS {
            for i in 0..journal.len() {
                if journal[i]
                    != u32::from(outputs[i * 2])
                        + u32::from(outputs[i * 2 + 1]).checked_shl(16).unwrap()
                {
                    return Err(VerificationError::JournalSealRootMismatch);
                }
            }
        } else {
            let journal_digest = hal.sha().hash_raw_pod_slice(journal);
            let journal_hash = journal_digest.as_slice();
            for i in 0..journal_hash.len() {
                if journal_hash[i]
                    != (u32::from(outputs[i * 2]))
                        + u32::from(outputs[i * 2 + 1]).checked_shl(16).unwrap()
                {
                    return Err(VerificationError::JournalSealRootMismatch);
                }
            }
        }
    }

    // Get the size
    let po2 = adapter.po2();
    assert!(po2 as usize <= MAX_CYCLES_PO2);
    let size = 1 << po2;
    let domain = INV_RATE * size;
    // debug!("size = {size}, po2 = {po2}");

    // Get taps and compute sizes
    let code_size = taps.group_size(RegisterGroup::Code);
    let data_size = taps.group_size(RegisterGroup::Data);
    let accum_size = taps.group_size(RegisterGroup::Accum);

    // Get code and data merkle roots
    hal.debug("code_merkle");
    let code_merkle = MerkleTreeVerifier::new(hal, &mut iop, domain, code_size, QUERIES);
    // debug!("codeRoot = {}", code_merkle.root());

    // Verify code is valid
    check_code(po2, code_merkle.root())?;

    hal.debug("data_merkle");
    let data_merkle = MerkleTreeVerifier::new(hal, &mut iop, domain, data_size, QUERIES);
    // debug!("dataRoot = {}", data_merkle.root());

    // Prep accumulation
    hal.debug("accumulate");
    adapter.accumulate(&mut iop);

    hal.debug("accum_merkle");
    let accum_merkle = MerkleTreeVerifier::new(hal, &mut iop, domain, accum_size, QUERIES);
    // debug!("accumRoot = {}", accum_merkle.root());

    // Set the poly mix value
    let poly_mix = H::ExtElem::random(&mut iop);

    hal.debug("check_merkle");
    let check_merkle = MerkleTreeVerifier::new(hal, &mut iop, domain, H::CHECK_SIZE, QUERIES);
    // debug!("checkRoot = {}", check_merkle.root());

    let z = H::ExtElem::random(&mut iop);
    // debug!("Z = {z:?}");
    let back_one = <H::Elem as RootsOfUnity>::ROU_REV[po2 as usize];

    // Read the U coeffs + commit their hash
    let num_taps = taps.tap_size();
    let coeff_u = iop.read_field_elem_slice(num_taps + H::CHECK_SIZE);
    let hash_u = *hal.sha().hash_raw_pod_slice(coeff_u);
    iop.commit(&hash_u);

    // Now, convert to evaluated values
    let mut cur_pos = 0;
    let mut eval_u = Vec::with_capacity(num_taps);
    for reg in taps.regs() {
        for i in 0..reg.size() {
            let x = z * back_one.pow(reg.back(i));
            let fx = hal.poly_eval(&coeff_u[cur_pos..(cur_pos + reg.size())], x);
            eval_u.push(fx);
        }
        cur_pos += reg.size();
    }
    assert_eq!(eval_u.len(), num_taps, "Miscalculated capacity for eval_us");

    // Compute the core polynomial
    hal.debug("> compute_polynomial");
    let result = hal.compute_polynomial(
        &eval_u,
        poly_mix,
        bytemuck::cast_slice(&adapter.out.unwrap()),
        bytemuck::cast_slice(&adapter.mix),
    );
    hal.debug("< compute_polynomial");
    // debug!("Result = {result:?}");

    // Now generate the check polynomial
    // TODO: This currently treats the extension degree as hardcoded at 4, with
    // the structure of the code and the value of `remap` (and how it is
    // accessed) only working in the extension degree = 4 case.
    // However, for generic fields the extension degree may be different
    // TODO: Therefore just using the to/from baby bear shims for now
    let mut check = H::ExtElem::default();
    let remap = [0, 2, 1, 3];
    let fp0 = H::Elem::ZERO;
    let fp1 = H::Elem::ONE;
    for i in 0..4 {
        let rmi = remap[i];
        check += coeff_u[num_taps + rmi + 0]
            * z.pow(i)
            * H::ExtElem::from_subelems([fp1, fp0, fp0, fp0]);
        check += coeff_u[num_taps + rmi + 4]
            * z.pow(i)
            * H::ExtElem::from_subelems([fp0, fp1, fp0, fp0]);
        check += coeff_u[num_taps + rmi + 8]
            * z.pow(i)
            * H::ExtElem::from_subelems([fp0, fp0, fp1, fp0]);
        check += coeff_u[num_taps + rmi + 12]
            * z.pow(i)
            * H::ExtElem::from_subelems([fp0, fp0, fp0, fp1]);
    }
    let three = H::Elem::from_u64(3);
    check *= (H::ExtElem::from_subfield(&three) * z).pow(size) - H::ExtElem::ONE;
    // debug!("Check = {check:?}");
    if check != result {
        return Err(VerificationError::InvalidProof);
    }

    // Set the mix mix value
    let mix = H::ExtElem::random(&mut iop);
    // debug!("mix = {mix:?}");

    // Make the mixed U polynomials.  combo_u has one element for each
    // back for each combo, plus 1 for the check.
    let mut combo_u: Vec<H::ExtElem> = vec![H::ExtElem::ZERO; taps.tot_combo_backs + 1];
    let mut cur_mix = H::ExtElem::ONE;
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
    // debug!("cur_mix: {cur_mix:?}, cur_pos: {cur_pos}");
    // Handle check group
    let mut check_mix_pows = Vec::with_capacity(H::CHECK_SIZE);
    for _ in 0..H::CHECK_SIZE {
        combo_u[taps.tot_combo_backs] += cur_mix * coeff_u[cur_pos];
        cur_pos += 1;
        check_mix_pows.push(cur_mix);
        cur_mix *= mix;
    }
    assert_eq!(
        check_mix_pows.len(),
        H::CHECK_SIZE,
        "Miscalculated capacity for check_mix_pows"
    );
    // debug!("cur_mix: {cur_mix:?}");

    let gen = <H::Elem as RootsOfUnity>::ROU_FWD[log2_ceil(domain)];
    // debug!("FRI-verify, size = {size}");
    fri_verify(
        hal,
        &mut iop,
        size,
        |iop: &mut ReadIOP<_>, idx: usize| -> Result<H::ExtElem, VerificationError> {
            hal.debug("fri_verify");
            let x = gen.pow(idx);
            let rows = [
                accum_merkle.verify(iop, idx)?,
                code_merkle.verify(iop, idx)?,
                data_merkle.verify(iop, idx)?,
            ];
            let check_row = check_merkle.verify(iop, idx)?;
            let ret = hal.fri_eval_taps(taps, mix, &combo_u, check_row, back_one, x, z, rows);
            Ok(ret)
        },
    )?;
    iop.verify_complete();
    Ok(())
}
