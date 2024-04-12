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

use rayon::prelude::*;
use risc0_core::field::{Elem, ExtElem, RootsOfUnity};

use crate::{
    core::poly::{poly_divide, poly_interpolate},
    hal::{Buffer, CircuitHal, Hal},
    prove::{fri::fri_prove, poly_group::PolyGroup, write_iop::WriteIOP},
    taps::TapSet,
    INV_RATE,
};

/// Object to generate a zero-knowledge proof of the execution of some circuit.
pub struct Prover<'a, H: Hal> {
    hal: &'a H,
    taps: &'a TapSet<'a>,
    iop: WriteIOP<H::Field>,
    groups: Vec<Option<PolyGroup<H>>>,
    cycles: usize,
    po2: usize,
}

fn make_coeffs<H: Hal>(hal: &H, buf: H::Buffer<H::Elem>, count: usize) -> H::Buffer<H::Elem> {
    // Do interpolate
    hal.batch_interpolate_ntt(&buf, count);
    // Convert f(x) -> f(3x), which effective multiplies cofficent c_i by 3^i.
    #[cfg(not(feature = "circuit_debug"))]
    hal.zk_shift(&buf, count);
    buf
}

impl<'a, H: Hal> Prover<'a, H> {
    /// Creates a new prover.
    pub fn new(hal: &'a H, taps: &'a TapSet) -> Self {
        Self {
            hal,
            taps,
            iop: WriteIOP::new(hal.get_hash_suite().rng.as_ref()),
            groups: std::iter::repeat_with(|| None)
                .take(taps.num_groups())
                .collect(),
            cycles: 0,
            po2: usize::MAX,
        }
    }

    /// Accesses the prover's IOP to commit or read random data.
    pub fn iop(&mut self) -> &mut WriteIOP<H::Field> {
        &mut self.iop
    }

    /// Sets the number of cycles to to 2^po2.  This must be called
    /// once after new() before any commit_group() calls.
    pub fn set_po2(&mut self, po2: usize) {
        assert_eq!(self.po2, usize::MAX);
        assert_eq!(self.cycles, 0);
        self.po2 = po2;
        self.cycles = 1 << po2;
    }

    /// Commits a given buffer to the IOP; the values must not subsequently
    /// change.
    #[tracing::instrument(skip_all)]
    pub fn commit_group(&mut self, tap_group_index: usize, buf: H::Buffer<H::Elem>) {
        let group_size = self.taps.group_size(tap_group_index);
        assert_eq!(buf.size() % group_size, 0);
        assert_eq!(buf.size() / group_size, self.cycles);
        assert!(
            self.groups[tap_group_index].is_none(),
            "Attempted to commit group {} more than once",
            self.taps.group_name(tap_group_index)
        );

        let coeffs = make_coeffs(self.hal, buf, group_size);
        let group_ref = self.groups[tap_group_index].insert(PolyGroup::new(
            self.hal,
            coeffs,
            group_size,
            self.cycles,
            "data",
        ));

        group_ref.merkle.commit(&mut self.iop);

        tracing::debug!(
            "{} group root: {}",
            self.taps.group_name(tap_group_index),
            group_ref.merkle.root()
        );
    }

    /// Generates the proof and returns the seal.
    #[tracing::instrument(skip_all)]
    pub fn finalize<C>(mut self, globals: &[&H::Buffer<H::Elem>], circuit_hal: &C) -> Vec<u32>
    where
        C: CircuitHal<H>,
    {
        // Set the poly mix value, which is used for constraint compression in the
        // DEEP-ALI protocol.
        let poly_mix = self.iop.random_ext_elem();
        let domain = self.cycles * INV_RATE;
        let ext_size = H::ExtElem::EXT_SIZE;

        // Now generate the check polynomial.
        // The check polynomial is the core of the STARK: if the constraints are
        // satisfied, the check polynomial will be a low-degree polynomial. See
        // DEEP-ALI paper for details on the construction of the check_poly.
        let check_poly = self.hal.alloc_elem("check_poly", ext_size * domain);

        let groups: Vec<&_> = self
            .groups
            .iter()
            .map(|pg| &pg.as_ref().unwrap().evaluated)
            .collect();
        circuit_hal.eval_check(
            &check_poly,
            groups.as_slice(),
            globals,
            poly_mix,
            self.po2,
            self.cycles,
        );

        #[cfg(feature = "circuit_debug")]
        check_poly.view(|check_out| {
            for i in (0..domain).step_by(4) {
                if check_out[i] != H::Elem::ZERO {
                    tracing::debug!("check[{}] =  {:?}", i, check_out[i]);
                }
            }
        });

        // Convert to coefficients.  Some tricky bizness here with the fact that
        // checkPoly is really an FpExt polynomial.  Nicely for us, since all the
        // roots of unity (which are the only thing that and values get multiplied
        // by) are in Fp, FpExt values act like simple vectors of Fp for the
        // purposes of interpolate/evaluate.
        self.hal.batch_interpolate_ntt(&check_poly, ext_size);

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
        let check_group = PolyGroup::new(self.hal, check_poly, H::CHECK_SIZE, self.cycles, "check");
        check_group.merkle.commit(&mut self.iop);
        tracing::debug!("checkGroup: {}", check_group.merkle.root());

        // Now pick a value for Z, which is used as the DEEP-ALI query point.
        let z = self.iop.random_ext_elem();
        // #ifdef CIRCUIT_DEBUG
        //   if (badZ != FpExt(0)) {
        //     Z = badZ;
        //   }
        //   iop.write(&Z, 1);
        // #endif
        //   LOG(1, "Z = " << Z);

        // Get rev rou for size
        let back_one = H::ExtElem::from_subfield(&H::Elem::ROU_REV[self.po2]);
        let mut all_xs = Vec::new();

        // Now, we evaluate each group at the approriate points (relative to Z).
        // From here on out, we always process groups in accum, code, data order,
        // since this is the order used by the codegen system (alphabetical).
        // Sometimes it's a requirement for matching generated code, but even when
        // it's not we keep the order for consistency.

        let mut eval_u: Vec<H::ExtElem> = Vec::new();
        tracing::info_span!("eval_u").in_scope(|| {
            for (id, pg) in self.groups.iter().enumerate() {
                let pg = pg.as_ref().unwrap();

                let mut which = Vec::new();
                let mut xs = Vec::new();
                for tap in self.taps.group_taps(id) {
                    which.push(tap.offset() as u32);
                    let x = back_one.pow(tap.back()) * z;
                    xs.push(x);
                    all_xs.push(x);
                }
                let which = self.hal.copy_from_u32("which", which.as_slice());
                let xs = self.hal.copy_from_extelem("xs", xs.as_slice());
                let out = self.hal.alloc_extelem("out", which.size());
                self.hal
                    .batch_evaluate_any(&pg.coeffs, pg.count, &which, &xs, &out);
                out.view(|view| {
                    eval_u.extend(view);
                });
            }
        });

        // Now, convert the values to coefficients via interpolation
        let mut coeff_u = vec![H::ExtElem::ZERO; eval_u.len()];
        tracing::info_span!("poly_interpolate").in_scope(|| {
            let mut pos = 0;
            for reg in self.taps.regs() {
                poly_interpolate(
                    &mut coeff_u[pos..],
                    &all_xs[pos..],
                    &eval_u[pos..],
                    reg.size(),
                );
                pos += reg.size();
            }
        });

        // Add in the coeffs of the check polynomials.
        let z_pow = z.pow(ext_size);
        let which = Vec::from_iter(0u32..H::CHECK_SIZE as u32);
        let xs = vec![z_pow; H::CHECK_SIZE];
        let out = self.hal.alloc_extelem("out", H::CHECK_SIZE);
        let which = self.hal.copy_from_u32("which", which.as_slice());
        let xs = self.hal.copy_from_extelem("xs", xs.as_slice());
        self.hal
            .batch_evaluate_any(&check_group.coeffs, H::CHECK_SIZE, &which, &xs, &out);
        out.view(|view| {
            coeff_u.extend(view);
        });

        tracing::debug!("Size of U = {}", coeff_u.len());
        self.iop.write_field_elem_slice(&coeff_u);
        let hash_u = self
            .hal
            .get_hash_suite()
            .hashfn
            .hash_ext_elem_slice(coeff_u.as_slice());
        self.iop.commit(&hash_u);

        // Set the mix mix value, which is used for FRI batching.
        let mix = self.iop.random_ext_elem();
        tracing::debug!("Mix = {mix:?}");

        // Do the coefficent mixing
        // Begin by making a zeroed output buffer
        let combo_count = self.taps.combos_size();
        let combos = vec![H::ExtElem::ZERO; self.cycles * (combo_count + 1)];
        let combos = self.hal.copy_from_extelem("combos", combos.as_slice());
        tracing::info_span!("mix_poly_coeffs").in_scope(|| {
            let mut cur_mix = H::ExtElem::ONE;

            for (id, pg) in self.groups.iter().enumerate() {
                let pg = pg.as_ref().unwrap();

                let group_size = self.taps.group_size(id);
                let mut which = Vec::with_capacity(group_size);
                for reg in self.taps.group_regs(id) {
                    which.push(reg.combo_id() as u32);
                }
                let which = self.hal.copy_from_u32("which", which.as_slice());
                self.hal.mix_poly_coeffs(
                    &combos,
                    &cur_mix,
                    &mix,
                    &pg.coeffs,
                    &which,
                    group_size,
                    self.cycles,
                );
                cur_mix *= mix.pow(group_size);
            }

            let which = vec![combo_count as u32; H::CHECK_SIZE];
            let which_buf = self.hal.copy_from_u32("which", which.as_slice());
            self.hal.mix_poly_coeffs(
                &combos,
                &cur_mix,
                &mix,
                &check_group.coeffs,
                &which_buf,
                H::CHECK_SIZE,
                self.cycles,
            );
        });

        // Load the near final coefficients back to the CPU
        tracing::info_span!("load_combos").in_scope(|| {
            combos.view_mut(|combos| {
                tracing::info_span!("part1").in_scope(|| {
                    let mut cur_pos = 0;
                    let mut cur = H::ExtElem::ONE;
                    // Subtract the U coeffs from the combos
                    for reg in self.taps.regs() {
                        for i in 0..reg.size() {
                            combos[self.cycles * reg.combo_id() + i] -= cur * coeff_u[cur_pos + i];
                        }
                        cur *= mix;
                        cur_pos += reg.size();
                    }
                    // Subtract the final 'check' coefficents
                    for _ in 0..H::CHECK_SIZE {
                        combos[self.cycles * combo_count] -= cur * coeff_u[cur_pos];
                        cur_pos += 1;
                        cur *= mix;
                    }
                });
                // Divide each element by (x - Z * back1^back) for each back
                tracing::info_span!("part2").in_scope(|| {
                    combos
                        .par_chunks_exact_mut(self.cycles)
                        .zip(0..combo_count)
                        .for_each(|(combo, i)| {
                            for back in self.taps.get_combo(i).slice() {
                                assert_eq!(
                                    poly_divide(combo, z * back_one.pow((*back).into())),
                                    H::ExtElem::ZERO
                                );
                            }
                        });
                });
                tracing::info_span!("part3").in_scope(|| {
                    // Divide check polys by z^EXT_SIZE
                    let slice = &mut combos
                        [combo_count * self.cycles..combo_count * self.cycles + self.cycles];
                    assert_eq!(poly_divide(slice, z_pow), H::ExtElem::ZERO);
                });
            });
        });
        // Sum the combos up into one final polynomial + make it into 4 Fp polys.
        // Additionally, it needs to be bit reversed to make everyone happy
        let final_poly_coeffs = self
            .hal
            .alloc_elem("final_poly_coeffs", self.cycles * ext_size);
        self.hal.eltwise_sum_extelem(&final_poly_coeffs, &combos);

        // Finally do the FRI protocol to prove the degree of the polynomial
        self.hal.batch_bit_reverse(&final_poly_coeffs, ext_size);
        tracing::debug!("FRI-proof, size = {}", final_poly_coeffs.size() / ext_size);

        fri_prove(self.hal, &mut self.iop, &final_poly_coeffs, |iop, idx| {
            for pg in self.groups.iter() {
                let pg = pg.as_ref().unwrap();
                pg.merkle.prove(self.hal, iop, idx);
            }
            check_group.merkle.prove(self.hal, iop, idx);
        });

        let proven_soundness_error =
            super::soundness::proven::<H>(self.taps, final_poly_coeffs.size());
        tracing::info!("proven_soundness_error: {proven_soundness_error:?}");

        let conjectured_security =
            super::soundness::toy_model_security::<H>(self.taps, final_poly_coeffs.size());
        tracing::info!("conjectured_security: {conjectured_security:?}");

        // Return final proof
        let proof = self.iop.proof;
        tracing::debug!("Proof size = {}", proof.len());
        proof
    }
}
