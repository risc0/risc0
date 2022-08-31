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
use core::{fmt, iter::zip};
// use log::debug;

use crate::{
    adapter::{CircuitInfo, TapsProvider},
    core::{
        fp::Fp,
        fp4::Fp4,
        log2_ceil,
        poly::poly_eval,
        rou::{ROU_FWD, ROU_REV},
        sha::{Digest, Sha},
    },
    field::{baby_bear::BabyBear, Elem},
    taps::RegisterGroup,
    verify::{fri::fri_verify, merkle::MerkleTreeVerifier, read_iop::ReadIOP},
    CHECK_SIZE, INV_RATE, MAX_CYCLES_PO2, QUERIES,
};

use self::adapter::VerifyAdapter;

#[cfg(feature = "host")]
pub use host::VerifyImpl;

#[derive(Debug)]
pub enum VerificationError {
    ReceiptFormatError,
    MethodVerificationError,
    MerkleQueryOutOfRange { idx: usize, rows: usize },
    InvalidProof,
}

impl fmt::Display for VerificationError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            VerificationError::ReceiptFormatError => write!(f, "invalid receipt format"),
            VerificationError::MethodVerificationError => write!(f, "method verification failed"),
            VerificationError::MerkleQueryOutOfRange { idx, rows } => write!(
                f,
                "Requested Merkle validation on row {}, but only {} rows exist",
                idx, rows
            ),
            VerificationError::InvalidProof => write!(f, "Verification indicates proof is invalid"),
        }
    }
}

pub trait VerifyHal {
    type Sha: Sha;

    fn sha(&self) -> &Self::Sha;

    fn debug(&self, msg: &str);

    fn compute_polynomial(&self, u: &[Fp4], poly_mix: Fp4, out: &[Fp], mix: &[Fp]) -> Fp4;
}

#[cfg(feature = "host")]
mod host {
    use crate::adapter::{PolyExt, PolyExtContext};

    use super::*;

    pub struct VerifyImpl<'a, S: Sha, C: PolyExt> {
        sha: &'a S,
        circuit: &'a C,
    }

    impl<'a, S: Sha, C: PolyExt> VerifyImpl<'a, S, C> {
        pub fn new(sha: &'a S, circuit: &'a C) -> Self {
            Self { sha, circuit }
        }
    }

    impl<'a, S: Sha, C: PolyExt> VerifyHal for VerifyImpl<'a, S, C> {
        type Sha = S;

        fn sha(&self) -> &Self::Sha {
            self.sha
        }

        fn debug(&self, msg: &str) {
            log::debug!("{}", msg);
        }

        fn compute_polynomial(&self, u: &[Fp4], poly_mix: Fp4, out: &[Fp], mix: &[Fp]) -> Fp4 {
            let ctx = PolyExtContext { mix: poly_mix };
            let args: &[&[Fp]] = &[out, mix];
            let result = self.circuit.poly_ext(&ctx, u, args);
            result.tot
        }
    }
}

pub fn verify<'a, H, C, F>(
    hal: &'a H,
    circuit: &C,
    seal: &'a [u32],
    check_code: F,
) -> Result<(), VerificationError>
where
    H: VerifyHal,
    C: CircuitInfo + TapsProvider,
    F: Fn(u32, &Digest) -> bool,
{
    if seal.len() == 0 {
        return Err(VerificationError::ReceiptFormatError);
    }

    let mut adapter = VerifyAdapter::new(circuit);
    let taps = adapter.taps();

    // Make IOP
    let mut iop = ReadIOP::new(hal.sha(), seal);

    // Read any execution state
    hal.debug("> execute");
    adapter.execute(&mut iop);
    hal.debug("< execute");

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
    let combo_count = taps.combos_size();

    // Get code and data merkle roots
    hal.debug("code_merkle");
    let code_merkle = MerkleTreeVerifier::new(&mut iop, domain, code_size, QUERIES);
    // debug!("codeRoot = {}", code_merkle.root());
    hal.debug("data_merkle");
    let data_merkle = MerkleTreeVerifier::new(&mut iop, domain, data_size, QUERIES);
    // debug!("dataRoot = {}", data_merkle.root());

    // Verify code is valid
    if !check_code(po2, code_merkle.root()) {
        return Err(VerificationError::MethodVerificationError);
    }

    // Prep accumulation
    hal.debug("accumulate");
    adapter.accumulate(&mut iop);

    hal.debug("accum_merkle");
    let accum_merkle = MerkleTreeVerifier::new(&mut iop, domain, accum_size, QUERIES);
    // debug!("accumRoot = {}", accum_merkle.root());

    // Set the poly mix value
    let poly_mix = Fp4::random(&mut iop);

    hal.debug("check_merkle");
    let check_merkle = MerkleTreeVerifier::new(&mut iop, domain, CHECK_SIZE, QUERIES);
    // debug!("checkRoot = {}", check_merkle.root());

    let z = Fp4::random(&mut iop);
    // debug!("Z = {z:?}");
    let back_one = Fp::from(ROU_REV[po2 as usize]);

    // Read the U coeffs + commit their hash
    let num_taps = taps.tap_size();
    let coeff_u = iop.read_pod_slice(num_taps + CHECK_SIZE);
    let hash_u = *hal.sha().hash_raw_pod_slice(coeff_u);
    iop.commit(&hash_u);

    // Now, convert to evaluated values
    hal.debug("> poly_eval");
    let mut cur_pos = 0;
    let mut eval_u = Vec::with_capacity(num_taps);
    for reg in taps.regs() {
        for i in 0..reg.size() {
            let x = back_one.pow(reg.back(i)) * z;
            let fx = poly_eval(&coeff_u[cur_pos..(cur_pos + reg.size())], x);
            eval_u.push(fx);
        }
        cur_pos += reg.size();
    }
    assert_eq!(eval_u.len(), num_taps, "Miscalculated capacity for eval_us");
    hal.debug("< poly_eval");

    // Compute the core polynomial
    hal.debug("> compute_polynomial");
    let result = hal.compute_polynomial(&eval_u, poly_mix, &adapter.out.unwrap(), &adapter.mix);
    hal.debug("< compute_polynomial");
    // debug!("Result = {result:?}");

    // Now generate the check polynomial
    let mut check = Fp4::ZERO;
    let remap = [0, 2, 1, 3];
    let fp0 = Fp::from(0 as u32);
    let fp1 = Fp::from(1 as u32);
    for i in 0..4 {
        let rmi = remap[i];
        check += coeff_u[num_taps + rmi + 0] * z.pow(i) * Fp4::new(fp1, fp0, fp0, fp0);
        check += coeff_u[num_taps + rmi + 4] * z.pow(i) * Fp4::new(fp0, fp1, fp0, fp0);
        check += coeff_u[num_taps + rmi + 8] * z.pow(i) * Fp4::new(fp0, fp0, fp1, fp0);
        check += coeff_u[num_taps + rmi + 12] * z.pow(i) * Fp4::new(fp0, fp0, fp0, fp1);
    }
    check *= (Fp4::from_u32(3) * z).pow(size) - Fp4::ONE;
    // debug!("Check = {check:?}");
    if check != result {
        return Err(VerificationError::InvalidProof);
    }

    // Set the mix mix value
    let mix = Fp4::random(&mut iop);
    // debug!("mix = {mix:?}");

    // Make the mixed U polynomials
    let mut combo_u: Vec<Vec<Fp4>> = Vec::with_capacity(combo_count + 1);
    combo_u.extend(
        (0..combo_count)
            .into_iter()
            .map(|i| vec![Fp4::ZERO; taps.get_combo(i).size()]),
    );
    let mut cur_mix = Fp4::ONE;
    cur_pos = 0;
    let mut tap_mix_pows = Vec::with_capacity(taps.reg_count());
    for reg in taps.regs() {
        for i in 0..reg.size() {
            combo_u[reg.combo_id()][i] += cur_mix * coeff_u[cur_pos + i];
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
    combo_u.push(vec![Fp4::ZERO]);
    assert_eq!(
        combo_u.len(),
        combo_count + 1,
        "Miscalculated capacity for combo_u"
    );
    let mut check_mix_pows = Vec::with_capacity(CHECK_SIZE);
    for _ in 0..CHECK_SIZE {
        combo_u[combo_count][0] += cur_mix * coeff_u[cur_pos];
        cur_pos += 1;
        check_mix_pows.push(cur_mix);
        cur_mix *= mix;
    }
    assert_eq!(
        check_mix_pows.len(),
        CHECK_SIZE,
        "Miscalculated capacity for check_mix_pows"
    );
    // debug!("cur_mix: {cur_mix:?}");

    let gen = Fp::new(ROU_FWD[log2_ceil(domain)]);
    // debug!("FRI-verify, size = {size}");
    fri_verify(
        &mut iop,
        size,
        |iop: &mut ReadIOP<_>, idx: usize| -> Result<Fp4, VerificationError> {
            hal.debug("fri_verify");
            let x = Fp4::from_fp(gen.pow(idx));
            let rows = [
                accum_merkle.verify::<BabyBear>(iop, idx)?,
                code_merkle.verify::<BabyBear>(iop, idx)?,
                data_merkle.verify::<BabyBear>(iop, idx)?,
            ];
            let check_row = check_merkle.verify::<BabyBear>(iop, idx)?;
            let mut tot = vec![Fp4::ZERO; combo_count + 1];
            for (reg, cur) in zip(taps.regs(), tap_mix_pows.iter()) {
                tot[reg.combo_id()] += *cur * rows[reg.group() as usize][reg.offset()];
            }
            for (i, cur) in zip(0..CHECK_SIZE, check_mix_pows.iter()) {
                tot[combo_count] += *cur * check_row[i];
            }
            let mut ret = Fp4::ZERO;
            for i in 0..combo_count {
                let num = tot[i] - poly_eval(&combo_u[i], x);
                let mut divisor = Fp4::ONE;
                for back in taps.get_combo(i).slice() {
                    divisor *= x - z * back_one.pow(*back as usize);
                }
                ret += num * divisor.inv();
            }
            let check_num = tot[combo_count] - combo_u[combo_count][0];
            let check_div = x - z.pow(INV_RATE);
            ret += check_num * check_div.inv();
            Ok(ret)
        },
    )?;
    iop.verify_complete();
    Ok(())
}
