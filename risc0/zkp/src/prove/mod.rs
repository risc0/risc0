// Copyright 2023 RISC Zero, Inc.
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

//! Cryptographic algorithms for producing a ZK proof of compute
//!
//! This module is not typically used directly. Instead, we recommend the
//! higher-level tools offered in [`risc0_zkvm::prove`].
//!
//! [`risc0_zkvm::prove`]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/prove/index.html

mod accum;
pub mod adapter;
pub mod executor;
mod fri;
mod merkle;
pub mod poly_group;
pub mod write_iop;

use alloc::{vec, vec::Vec};

use log::debug;
use risc0_core::field::{Elem, ExtElem, Field, RootsOfUnity};

use self::adapter::ProveAdapter;
use crate::{
    adapter::{CircuitDef, CircuitStepHandler},
    core::{
        poly::{poly_divide, poly_interpolate},
        sha::Sha,
    },
    hal::{Buffer, EvalCheck, Hal},
    prove::{fri::fri_prove, poly_group::PolyGroup, write_iop::WriteIOP},
    taps::RegisterGroup,
    INV_RATE, MAX_CYCLES_PO2,
};

/// INSECURELY execute a circuit without producing a seal that proves execution
pub fn prove_without_seal<'a, F, S, C, CS>(sha: &S, circuit: &mut ProveAdapter<'a, F, C, CS>)
where
    F: Field,
    S: Sha,
    C: CircuitDef<F>,
    CS: CircuitStepHandler<F::Elem>,
{
    let mut iop = WriteIOP::new(sha);
    circuit.execute(&mut iop);
}

/// Construct a seal proving execution
#[tracing::instrument(skip_all)]
pub fn prove<'a, F, H, S, E, C, CS>(
    hal: &H,
    sha: &S,
    circuit: &mut ProveAdapter<'a, F, C, CS>,
    eval: &E,
) -> Vec<u32>
where
    F: Field,
    H: Hal<Elem = F::Elem, ExtElem = F::ExtElem>,
    S: Sha,
    E: EvalCheck<H>,
    C: CircuitDef<F>,
    CS: CircuitStepHandler<F::Elem>,
{
    // The taps are the entries of the trace used in evaluating the constraints.
    let taps = circuit.get_taps();

    // The number of columns used for encoding zkvm control instructions.
    let code_size = taps.group_size(RegisterGroup::Code);
    // The number of columns used for encoding the execution trace.
    let data_size = taps.group_size(RegisterGroup::Data);
    // The number of columns used for the PLOOKUP argument.
    let accum_size = taps.group_size(RegisterGroup::Accum);
    debug!(
        "code: {code_size}/{}, data: {data_size}/{}, accum: {accum_size}/{}",
        circuit.get_code().len(),
        circuit.get_data().len(),
        circuit.get_accum().len()
    );

    let mut iop = WriteIOP::new(sha);

    circuit.execute(&mut iop);

    // The log of the number of steps in the execution trace.
    let po2 = circuit.po2();
    assert!(po2 as usize <= MAX_CYCLES_PO2);
    let size = 1 << po2;

    // Make code + data PolyGroups + commit them
    let code_coeffs = make_coeffs(hal, circuit.get_code(), code_size);
    let code_group = PolyGroup::new(hal, &code_coeffs, code_size, size, "code");
    code_group.merkle.commit(&mut iop);
    debug!("codeGroup: {}", code_group.merkle.root());

    let data_coeffs = make_coeffs(hal, circuit.get_data(), data_size);
    let data_group = PolyGroup::new(hal, &data_coeffs, data_size, size, "data");
    data_group.merkle.commit(&mut iop);
    debug!("dataGroup: {}", data_group.merkle.root());

    // Generates grand product accumulations for PLONK-style permutation arguments
    circuit.accumulate(&mut iop);

    // Make the accum group + commit
    debug!("size = {size}, accumSize = {accum_size}");
    debug!("getAccum.size() = {}", circuit.get_accum().len());
    let accum_coeffs = make_coeffs(hal, circuit.get_accum(), accum_size);
    let accum_group = PolyGroup::new(hal, &accum_coeffs, accum_size, size, "accum");
    accum_group.merkle.commit(&mut iop);
    debug!("accumGroup: {}", accum_group.merkle.root());

    // Set the poly mix value, which is used for constraint compression in the
    // DEEP-ALI protocol.
    let poly_mix = H::ExtElem::random(&mut iop.rng);
    let domain = size * INV_RATE;

    // Now generate the check polynomial.
    // The check polynomial is the core of the STARK: if the constraints are
    // satisfied, the check polynomial will be a low-degree polynomial. See
    // DEEP-ALI paper for details on the construction of the check_poly.
    let check_poly = hal.alloc_elem("check_poly", H::ExtElem::EXT_SIZE * domain);
    let mix = hal.copy_from_elem("mix", circuit.get_mix());
    let out = hal.copy_from_elem("out", circuit.get_io());
    eval.eval_check(
        &check_poly,
        &code_group.evaluated,
        &data_group.evaluated,
        &accum_group.evaluated,
        &mix,
        &out,
        poly_mix,
        po2 as usize,
        circuit.get_steps(),
    );

    #[cfg(feature = "circuit_debug")]
    check_poly.view(|check_out| {
        for i in (0..domain).step_by(4) {
            if check_out[i] != H::Elem::ZERO {
                debug!("check[{}] =  {:?}", i, check_out[i]);
            }
        }
    });

    // Convert to coefficients.  Some tricky bizness here with the fact that
    // checkPoly is really an Fp4 polynomial.  Nicely for us, since all the
    // roots of unity (which are the only thing that and values get multiplied
    // by) are in Fp, Fp4 values act like simple vectors of Fp for the
    // purposes of interpolate/evaluate.
    hal.batch_interpolate_ntt(&check_poly, H::ExtElem::EXT_SIZE);

    // The next step is to convert the degree 4*n check polynomial into 4 degreen n
    // polynomials so that f(x) = g0(x^4) + g1(x^4) x + g2(x^4) x^2 + g3(x^4)
    // x^3.  To do this, we normally would grab all the coeffients of f(x) =
    // sum_i c_i x^i where i % 4 == 0 and put them into a new polynomial g0(x) =
    // sum_i d0_i*x^i, where d0_i = c_(i*4).
    //
    // Amazingingly, since the coefficients are bit reversed, the coefficients of g0
    // are all aleady next to each other and in bit-reversed for for g0, as are
    // the coeffients of g1, etc. So really, we can just reinterpret 4 polys of
    // invRate*size to 16 polys of size, without actually doing anything.

    // Make the PolyGroup + add it to the IOP;
    let check_group = PolyGroup::new(hal, &check_poly, H::CHECK_SIZE, size, "check");
    check_group.merkle.commit(&mut iop);
    debug!("checkGroup: {}", check_group.merkle.root());

    // Now pick a value for Z, which is used as the DEEP-ALI query point.
    let z = H::ExtElem::random(&mut iop.rng);
    // #ifdef CIRCUIT_DEBUG
    //   if (badZ != Fp4(0)) {
    //     Z = badZ;
    //   }
    //   iop.write(&Z, 1);
    // #endif
    //   LOG(1, "Z = " << Z);

    // Get rev rou for size
    let back_one = H::ExtElem::from_subfield(&H::Elem::ROU_REV[po2 as usize]);
    let mut all_xs = Vec::new();

    // Do evaluations of all of the various polynomials at the appropriate points.
    let mut eval_u: Vec<H::ExtElem> = Vec::new();
    let mut eval_group = |id: RegisterGroup, pg: &PolyGroup<H>| {
        let mut which = Vec::new();
        let mut xs = Vec::new();
        for tap in taps.group_taps(id) {
            which.push(tap.offset() as u32);
            let x = back_one.pow(tap.back()) * z;
            xs.push(x);
            all_xs.push(x);
        }
        let which = hal.copy_from_u32("which", which.as_slice());
        let xs = hal.copy_from_extelem("xs", xs.as_slice());
        let out = hal.alloc_extelem("out", which.size());
        hal.batch_evaluate_any(&pg.coeffs, pg.count, &which, &xs, &out);
        out.view(|view| {
            eval_u.extend(view);
        });
    };

    // Now, we evaluate each group at the approriate points (relative to Z).
    // From here on out, we always process groups in accum, code, data order,
    // since this is the order used by the codegen system (alphabetical).
    // Sometimes it's a requirement for matching generated code, but even when
    // it's not we keep the order for consistency.
    eval_group(RegisterGroup::Accum, &accum_group);
    eval_group(RegisterGroup::Code, &code_group);
    eval_group(RegisterGroup::Data, &data_group);

    // Now, convert the values to coefficients via interpolation
    let mut pos = 0;
    let mut coeff_u = vec![H::ExtElem::ZERO; eval_u.len()];
    for reg in taps.regs() {
        poly_interpolate(
            &mut coeff_u[pos..],
            &all_xs[pos..],
            &eval_u[pos..],
            reg.size(),
        );
        pos += reg.size();
    }

    // Add in the coeffs of the check polynomials.
    let z_pow = z.pow(H::ExtElem::EXT_SIZE);
    let which = Vec::from_iter(0u32..H::CHECK_SIZE as u32);
    let xs = vec![z_pow; H::CHECK_SIZE];
    let out = hal.alloc_extelem("out", H::CHECK_SIZE);
    let which = hal.copy_from_u32("which", which.as_slice());
    let xs = hal.copy_from_extelem("xs", xs.as_slice());
    hal.batch_evaluate_any(&check_group.coeffs, H::CHECK_SIZE, &which, &xs, &out);
    out.view(|view| {
        coeff_u.extend(view);
    });

    debug!("Size of U = {}", coeff_u.len());
    iop.write_field_elem_slice(&coeff_u);
    let hash_u = sha.hash_raw_pod_slice(coeff_u.as_slice());
    iop.commit(&hash_u);

    // Set the mix mix value, which is used for FRI batching.
    let mix = H::ExtElem::random(&mut iop.rng);
    debug!("Mix = {mix:?}");

    // Do the coefficent mixing
    // Begin by making a zeroed output buffer
    let combo_count = taps.combos_size();
    let combos = vec![H::ExtElem::ZERO; size * (combo_count + 1)];
    let combos = hal.copy_from_extelem("combos", combos.as_slice());
    let mut cur_mix = H::ExtElem::ONE;

    let mut mix_group = |id: RegisterGroup, pg: &PolyGroup<H>| {
        let mut which = Vec::new();
        for reg in taps.group_regs(id) {
            which.push(reg.combo_id() as u32);
        }
        let which_buf = hal.copy_from_u32("which", which.as_slice());
        let group_size = taps.group_size(id);
        hal.mix_poly_coeffs(
            &combos, &cur_mix, &mix, &pg.coeffs, &which_buf, group_size, size,
        );
        cur_mix *= mix.pow(group_size);
    };

    mix_group(RegisterGroup::Accum, &accum_group);
    mix_group(RegisterGroup::Code, &code_group);
    mix_group(RegisterGroup::Data, &data_group);

    let which = vec![combo_count as u32; H::CHECK_SIZE];
    let which_buf = hal.copy_from_u32("which", which.as_slice());
    hal.mix_poly_coeffs(
        &combos,
        &cur_mix,
        &mix,
        &check_group.coeffs,
        &which_buf,
        H::CHECK_SIZE,
        size,
    );

    // Load the near final coefficients back to the CPU
    combos.view_mut(|combos| {
        // Subtract the U coeffs from the combos
        let mut cur_pos = 0;
        let mut cur = H::ExtElem::ONE;
        for reg in taps.regs() {
            for i in 0..reg.size() {
                combos[size * reg.combo_id() + i] -= cur * coeff_u[cur_pos + i];
            }
            cur *= mix;
            cur_pos += reg.size();
        }
        // Subtract the final 'check' coefficents
        for _ in 0..H::CHECK_SIZE {
            combos[size * combo_count] -= cur * coeff_u[cur_pos];
            cur_pos += 1;
            cur *= mix;
        }
        // Divide each element by (x - Z * back1^back) for each back
        for combo in 0..combo_count {
            for back in taps.get_combo(combo).slice() {
                assert_eq!(
                    poly_divide(
                        &mut combos[combo * size..combo * size + size],
                        z * back_one.pow((*back).into())
                    ),
                    H::ExtElem::ZERO
                );
            }
        }
        // Divide check polys by z^EXT_SIZE
        assert_eq!(
            poly_divide(
                &mut combos[combo_count * size..combo_count * size + size],
                z_pow
            ),
            H::ExtElem::ZERO
        );
    });

    // Sum the combos up into one final polynomial + make it into 4 Fp polys.
    // Additionally, it needs to be bit reversed to make everyone happy
    let final_poly_coeffs = hal.alloc_elem("final_poly_coeffs", size * H::ExtElem::EXT_SIZE);
    hal.eltwise_sum_extelem(&final_poly_coeffs, &combos);

    // Finally do the FRI protocol to prove the degree of the polynomial
    hal.batch_bit_reverse(&final_poly_coeffs, H::ExtElem::EXT_SIZE);
    debug!(
        "FRI-proof, size = {}",
        final_poly_coeffs.size() / H::ExtElem::EXT_SIZE
    );

    fri_prove(hal, &mut iop, &final_poly_coeffs, |iop, idx| {
        accum_group.merkle.prove(iop, idx);
        code_group.merkle.prove(iop, idx);
        data_group.merkle.prove(iop, idx);
        check_group.merkle.prove(iop, idx);
    });

    // Return final proof
    let proof = iop.proof;
    debug!("Proof size = {}", proof.len());
    proof
}

fn make_coeffs<H: Hal>(hal: &H, input: &[H::Elem], count: usize) -> H::BufferElem {
    // Copy into accel buffer
    let buf = hal.copy_from_elem("input", input);
    // Do interpolate
    hal.batch_interpolate_ntt(&buf, count);
    // Convert f(x) -> f(3x), which effective multiplies cofficent c_i by 3^i.
    #[cfg(not(feature = "circuit_debug"))]
    hal.zk_shift(&buf, count);
    buf
}
