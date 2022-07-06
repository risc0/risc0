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

mod fri;
mod merkle;
pub mod read_iop;

use alloc::vec;
use core::fmt;
// use log::debug;

use crate::{
    core::{
        fp::Fp,
        fp4::{Fp4, EXT_SIZE},
        log2_ceil,
        poly::poly_eval,
        rou::{ROU_FWD, ROU_REV},
        sha::{Digest, Sha},
        Random,
    },
    taps::{RegisterGroup, TapSet},
    verify::{fri::fri_verify, merkle::MerkleTreeVerifier, read_iop::ReadIOP},
    INV_RATE, MAX_CYCLES_PO2, QUERIES,
};

const CHECK_SIZE: usize = INV_RATE * EXT_SIZE;

#[derive(Debug)]
pub enum VerificationError {
    ReceiptFormatError,
    MethodVerificationError,
}

impl fmt::Display for VerificationError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            VerificationError::ReceiptFormatError => write!(f, "invalid receipt format"),
            VerificationError::MethodVerificationError => write!(f, "method verification failed"),
        }
    }
}

pub trait Circuit {
    fn taps(&self) -> &TapSet;
    fn execute<S: Sha>(&mut self, iop: &mut ReadIOP<S>);
    fn accumulate<S: Sha>(&mut self, iop: &mut ReadIOP<S>);
    fn po2(&self) -> u32;
    fn check_code(&self, root: &Digest) -> Result<(), VerificationError>;
    fn compute_polynomial(&self, u: &[Fp4], mix: Fp4) -> Fp4;
}

pub fn verify<S, C>(sha: &S, circuit: &mut C, seal: &[u32]) -> Result<(), VerificationError>
where
    S: Sha,
    C: Circuit,
{
    let taps = circuit.taps().clone();

    // Make IOP
    let mut iop = ReadIOP::new(sha, seal);

    // Read any execution state
    circuit.execute(&mut iop);

    // Get the size
    let po2 = circuit.po2();
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
    let code_merkle = MerkleTreeVerifier::new(&mut iop, domain, code_size, QUERIES);
    // debug!("codeRoot = {}", code_merkle.root());
    let data_merkle = MerkleTreeVerifier::new(&mut iop, domain, data_size, QUERIES);
    // debug!("dataRoot = {}", data_merkle.root());

    // Verify code is valid
    circuit.check_code(code_merkle.root())?;

    // Prep accumulation
    circuit.accumulate(&mut iop);

    let accum_merkle = MerkleTreeVerifier::new(&mut iop, domain, accum_size, QUERIES);
    // debug!("accumRoot = {}", accum_merkle.root());

    // Set the poly mix value
    let poly_mix = Fp4::random(&mut iop);

    let check_merkle = MerkleTreeVerifier::new(&mut iop, domain, CHECK_SIZE, QUERIES);
    // debug!("checkRoot = {}", check_merkle.root());

    let z = Fp4::random(&mut iop);
    // debug!("Z = {z:?}");
    let back_one = Fp::from(ROU_REV[po2 as usize]);

    // Read the U coeffs + commit their hash
    let num_taps = taps.tap_size();
    let mut coeff_u = vec![Fp4::default(); num_taps + CHECK_SIZE];
    iop.read_fp4s(&mut coeff_u);
    let hash_u = *sha.hash_fp4s(&coeff_u);
    iop.commit(&hash_u);

    // Now, convert to evaluated values
    let mut cur_pos = 0;
    let mut eval_u = vec![];
    for reg in taps.regs() {
        for i in 0..reg.size() {
            let x = back_one.pow(reg.back(i)) * z;
            let fx = poly_eval(&coeff_u[cur_pos..(cur_pos + reg.size())], x);
            eval_u.push(fx);
        }
        cur_pos += reg.size();
    }

    // Compute the core polynomial
    let result = circuit.compute_polynomial(&eval_u, poly_mix);
    // debug!("Result = {result:?}");

    // Now generate the check polynomial
    let mut check = Fp4::zero();
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
    check *= (Fp4::from_u32(3) * z).pow(size) - Fp4::one();
    // debug!("Check = {check:?}");
    assert_eq!(check, result);

    // Set the mix mix value
    let mix = Fp4::random(&mut iop);
    // debug!("mix = {mix:?}");

    // Make the mixed U polynomials
    let mut combo_u = vec![];
    for i in 0..combo_count {
        combo_u.push(vec![Fp4::zero(); taps.get_combo(i).size()]);
    }
    let mut cur_mix = Fp4::one();
    cur_pos = 0;
    for reg in taps.regs() {
        for i in 0..reg.size() {
            combo_u[reg.combo_id()][i] += cur_mix * coeff_u[cur_pos + i];
        }
        cur_mix *= mix;
        cur_pos += reg.size();
    }
    // debug!("cur_mix: {cur_mix:?}, cur_pos: {cur_pos}");
    // Handle check group
    combo_u.push(vec![Fp4::zero()]);
    for _ in 0..CHECK_SIZE {
        combo_u[combo_count][0] += cur_mix * coeff_u[cur_pos];
        cur_pos += 1;
        cur_mix *= mix;
    }
    // debug!("cur_mix: {cur_mix:?}");

    let gen = Fp::new(ROU_FWD[log2_ceil(domain)]);
    // debug!("FRI-verify, size = {size}");
    fri_verify(&mut iop, size, |iop: &mut ReadIOP<S>, idx: usize| -> Fp4 {
        let x = Fp4::from_fp(gen.pow(idx));
        let mut rows = vec![];
        rows.push(accum_merkle.verify(iop, idx));
        rows.push(code_merkle.verify(iop, idx));
        rows.push(data_merkle.verify(iop, idx));
        let check_row = check_merkle.verify(iop, idx);
        let mut cur = Fp4::one();
        let mut tot = vec![Fp4::zero(); combo_count + 1];
        for reg in taps.regs() {
            tot[reg.combo_id()] += cur * rows[reg.group() as usize][reg.offset()];
            cur *= mix;
        }
        for i in 0..CHECK_SIZE {
            tot[combo_count] += cur * check_row[i];
            cur *= mix;
        }
        let mut ret = Fp4::zero();
        for i in 0..combo_count {
            let num = tot[i] - poly_eval(&combo_u[i], x);
            let mut divisor = Fp4::one();
            for back in taps.get_combo(i).slice() {
                divisor *= x - z * back_one.pow(*back as usize);
            }
            ret += num * divisor.inv();
        }
        let check_num = tot[combo_count] - combo_u[combo_count][0];
        let check_div = x - z.pow(INV_RATE);
        ret += check_num * check_div.inv();
        ret
    });
    iop.verify_complete();
    Ok(())
}
