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

use alloc::{vec, vec::Vec};
use core::fmt;

use risc0_zkp_core::{
    fp::Fp,
    fp4::{Fp4, EXT_SIZE},
    poly::poly_eval,
    rou::{ROU_FWD, ROU_REV},
    sha::{Digest, Sha},
    to_po2,
};

use crate::{
    fri::{fri_verify, INV_RATE, QUERIES},
    merkle::MerkleTreeVerifier,
    read_iop::ReadIOP,
    taps::{RegisterGroup, Taps},
};

const MAX_CYCLES_PO2: usize = 20;
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
    fn taps(&self) -> &'static Taps<'static>;
    fn execute<S: Sha>(&mut self, iop: &mut ReadIOP<S>);
    fn accumulate<S: Sha>(&mut self, iop: &mut ReadIOP<S>);
    fn po2(&self) -> u32;
    fn check_code(&self, root: &Digest) -> Result<(), VerificationError>;
    fn compute_polynomial(&self, u: &[Fp4], mix: Fp4) -> Fp4;
}

pub fn verify<S: Sha, C: Circuit>(
    sha: &S,
    circuit: &mut C,
    proof: &[u32],
) -> Result<(), VerificationError> {
    // Make IOP
    let mut iop = ReadIOP::new(sha, proof);

    // Do 'execute' phase and get size
    circuit.execute(&mut iop);
    let po2 = circuit.po2();
    assert!(po2 as usize <= MAX_CYCLES_PO2);
    let size = 1 << po2;
    let domain = INV_RATE * size;

    // Get taps and compute sizes
    let taps = circuit.taps();
    // TODO: This is a very silly way to do this
    let mut accum_size = 0;
    let mut code_size = 0;
    let mut data_size = 0;
    let mut num_taps = 0;
    for reg in taps.registers.iter() {
        match reg.group {
            RegisterGroup::Accum => {
                accum_size += 1;
            }
            RegisterGroup::Code => {
                code_size += 1;
            }
            RegisterGroup::Data => {
                data_size += 1;
            }
        }
        num_taps += reg.back.len();
    }

    // Get code and data merkle roots
    let code_merkle = MerkleTreeVerifier::new(&mut iop, domain, code_size, QUERIES);
    let data_merkle = MerkleTreeVerifier::new(&mut iop, domain, data_size, QUERIES);

    // Verify code is valid
    circuit.check_code(code_merkle.root())?;

    // Prep accumulation
    circuit.accumulate(&mut iop);

    let accum_merkle = MerkleTreeVerifier::new(&mut iop, domain, accum_size, QUERIES);

    // Set the poly mix value
    let poly_mix = Fp4::random(&mut iop);

    let check_merkle = MerkleTreeVerifier::new(&mut iop, domain, CHECK_SIZE, QUERIES);

    let z = Fp4::random(&mut iop);

    // Read the U coeffs + commit their hash
    let mut coeff_u: Vec<Fp4> = vec![Fp4::default(); num_taps + CHECK_SIZE];
    iop.read_fp4s(&mut coeff_u);
    let hash_u = *sha.hash_fp4s(&coeff_u);
    iop.commit(&hash_u);

    // Now, convert to evaluated values
    let back_one: Fp = Fp::from(ROU_REV[po2 as usize]);
    let mut cur_pos: usize = 0;
    let mut eval_u: Vec<Fp4> = vec![];
    for reg in taps.registers {
        let blen = reg.back.len();
        for b in reg.back {
            let x = back_one.pow(*b) * z;
            let fx = poly_eval(&coeff_u[cur_pos..(cur_pos + blen)], x);
            eval_u.push(fx);
        }
        cur_pos += blen;
    }

    // Compute the core polynomial
    let result = circuit.compute_polynomial(&eval_u, poly_mix);

    // Now generate the check polynomial
    let mut check = Fp4::zero();
    let remap: [usize; 4] = [0, 2, 1, 3];
    let fp0 = Fp::from(0 as u32);
    let fp1 = Fp::from(1 as u32);
    for i in 0..4 {
        let rmi = remap[i];
        check += coeff_u[num_taps + rmi + 0] * z.pow(i) * Fp4::new(fp1, fp0, fp0, fp0);
        check += coeff_u[num_taps + rmi + 4] * z.pow(i) * Fp4::new(fp0, fp1, fp0, fp0);
        check += coeff_u[num_taps + rmi + 8] * z.pow(i) * Fp4::new(fp0, fp0, fp1, fp0);
        check += coeff_u[num_taps + rmi + 12] * z.pow(i) * Fp4::new(fp0, fp0, fp0, fp1);
    }
    check *= (Fp4::from(3 as u32) * z).pow(size) - Fp4::one();
    assert!(check == result);

    // Set the mix mix value
    let mix = Fp4::random(&mut iop);

    // Make the mixed U polynomials
    let combos_size = taps.combos.len();
    let mut combo_u: Vec<Vec<Fp4>> = vec![];
    for i in 0..combos_size {
        combo_u.push(vec![Fp4::zero(); taps.combos[i].back.len()]);
    }
    let mut cur_mix = Fp4::one();
    cur_pos = 0;
    for reg in taps.registers {
        let blen = reg.back.len();
        for i in 0..blen {
            combo_u[reg.combo_id][i] += cur_mix * coeff_u[cur_pos + i];
        }
        cur_mix *= mix;
        cur_pos += blen;
    }
    // Handle check group
    combo_u.push(vec![Fp4::zero()]);
    for _ in 0..CHECK_SIZE {
        combo_u[combos_size][0] += cur_mix * coeff_u[cur_pos];
        cur_pos += 1;
        cur_mix *= mix;
    }

    let domain_po2 = to_po2(domain);
    let gen: Fp = Fp::new(ROU_FWD[domain_po2]);
    fri_verify(
        &mut iop,
        size,
        |inner_iop: &mut ReadIOP<S>, idx: usize| -> Fp4 {
            let x = Fp4::from_fp(gen.pow(idx));
            let mut rows: Vec<Vec<Fp>> = vec![];
            rows.push(accum_merkle.verify(inner_iop, idx));
            rows.push(code_merkle.verify(inner_iop, idx));
            rows.push(data_merkle.verify(inner_iop, idx));
            let check_row = check_merkle.verify(inner_iop, idx);
            let mut cur = Fp4::one();
            let mut tot = vec![Fp4::zero(); combos_size + 1];
            for reg in taps.registers {
                tot[reg.combo_id] += cur * rows[reg.group as usize][reg.offset];
                cur *= mix;
            }
            for i in 0..CHECK_SIZE {
                tot[combos_size] += cur * check_row[i];
                cur *= mix;
            }
            let mut ret = Fp4::zero();
            for i in 0..combos_size {
                let num = tot[i] - poly_eval(&combo_u[i], x);
                let mut divisor = Fp4::one();
                for b in taps.combos[i].back {
                    divisor *= x - z * back_one.pow(*b);
                }
                ret += num * divisor.inv();
            }
            let check_num = tot[combos_size] - combo_u[combos_size][0];
            let check_div = x - z.pow(INV_RATE);
            ret += check_num * check_div.inv();
            return ret;
        },
    );
    iop.verify_complete();
    Ok(())
}
