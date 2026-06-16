// Copyright 2026 RISC Zero, Inc.
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

use risc0_core::{
    field::{Elem, ExtElem, RootsOfUnity},
    scope, scope_with,
};

#[cfg(all(feature = "low_vram", feature = "cuda"))]
use crate::{
    adapter::{REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA},
    hal::{release_buffer, release_buffer_ext, ZK_SHIFT_POST_BITREV, ZK_SHIFT_PRE_BITREV},
    LARGE_SEGMENT_PO2,
};
use crate::{
    core::{digest::Digest, poly::poly_interpolate},
    hal::{Buffer, CircuitHal, Hal},
    prove::{fri::fri_prove, poly_group::PolyGroup, write_iop::WriteIOP},
    taps::TapSet,
    INV_RATE,
};

/// Tag value used to detect that the active circuit is rv32im (and not
/// recursion/keccak). It mirrors `risc0_circuit_rv32im::zirgen::REGCOUNT_ACCUM`
/// (set by `define_tap_buffer!{accum, 103, 0}` in
/// `risc0/circuit/rv32im/src/zirgen/defs.rs.inc`). `risc0-zkp` cannot import
/// that constant directly because `risc0-circuit-rv32im` depends on
/// `risc0-zkp` — taking the reverse path would form a circular dep. Only used
/// under `low_vram + cuda` to release rv32im's accum evaluated buffer at
/// po2 > 21, where memory pressure is real; recursion/keccak's accum groups
/// have different sizes and don't need the release.
#[cfg(all(feature = "low_vram", feature = "cuda"))]
const RV32IM_ACCUM_REGCOUNT: usize = 103;

/// Object to generate a zero-knowledge proof of the execution of some circuit.
pub struct Prover<'a, H: Hal> {
    hal: &'a H,
    taps: &'a TapSet<'a>,
    iop: WriteIOP<H::Field>,
    pub groups: Vec<Option<PolyGroup<H>>>,
    cycles: usize,
    po2: usize,
}

#[cfg(all(feature = "low_vram", feature = "cuda"))]
fn make_coeffs<H: Hal>(
    hal: &H,
    witness: &H::Buffer<H::Elem>,
    count: usize,
    grp_id: usize,
) -> H::Buffer<H::Elem> {
    scope!("make_coeffs");

    let coeffs = if grp_id != REGISTER_GROUP_ACCUM {
        let coeffs = hal.alloc_elem("coeffs", witness.size());
        hal.eltwise_copy_elem(&coeffs, witness);
        coeffs
    } else {
        witness.clone()
    };

    // Do interpolate
    hal.batch_interpolate_ntt(&coeffs, count);
    // Convert f(x) -> f(3x), which effective multiplies coefficients c_i by 3^i.
    #[cfg(not(feature = "circuit_debug"))]
    {
        let beta = Elem::from_u64(3);
        hal.zk_shift(&coeffs, count, beta, 1);
    }

    coeffs
}

#[cfg(not(all(feature = "low_vram", feature = "cuda")))]
fn make_coeffs<H: Hal>(
    hal: &H,
    witness: &H::Buffer<H::Elem>,
    count: usize,
    _grp_id: usize,
) -> H::Buffer<H::Elem> {
    scope!("make_coeffs");
    let coeffs = hal.alloc_elem("coeffs", witness.size());
    hal.eltwise_copy_elem(&coeffs, witness);
    // Do interpolate
    hal.batch_interpolate_ntt(&coeffs, count);
    // Convert f(x) -> f(3x), which effective multiplies coefficients c_i by 3^i.
    #[cfg(not(feature = "circuit_debug"))]
    {
        let beta = Elem::from_u64(3);
        hal.zk_shift(&coeffs, count, beta, 1);
    }

    coeffs
}

impl<'a, H: Hal> Prover<'a, H> {
    #[cfg(all(feature = "low_vram", feature = "cuda"))]
    fn eval_check<C>(
        &mut self,
        check_poly: &H::Buffer<H::Elem>,
        globals: &[&H::Buffer<H::Elem>],
        poly_mix: H::ExtElem,
        circuit_hal: &C,
    ) -> Result<&str, &str>
    where
        C: CircuitHal<H>,
    {
        let data_id = REGISTER_GROUP_DATA;
        let accum_id = REGISTER_GROUP_ACCUM;
        let code_id = REGISTER_GROUP_CODE;

        // Collect evaluated buffers into owned vector first, then create references
        if self.groups[accum_id].as_ref().unwrap().evaluated.is_some()
            || self.po2 < LARGE_SEGMENT_PO2
        {
            let buffers: Vec<_> = self
                .groups
                .iter()
                .map(|pg| pg.as_ref().unwrap().evaluated.as_ref().unwrap().clone())
                .collect();
            let groups: Vec<&_> = buffers.iter().collect();

            circuit_hal.eval_check(
                check_poly,
                groups.as_slice(),
                globals,
                poly_mix,
                self.po2,
                self.cycles,
            );

            {
                let pg = self.groups[accum_id].as_mut().unwrap();
                if pg.count == RV32IM_ACCUM_REGCOUNT && self.po2 >= LARGE_SEGMENT_PO2 {
                    release_buffer(
                        "accum poly evalueated",
                        self.hal,
                        &mut pg.evaluated.as_mut().unwrap(),
                    );
                }
            }
        } else {
            {
                let dgp = &self.groups[data_id].as_ref().unwrap();
                let agp = &self.groups[accum_id].as_ref().unwrap();
                let cgp = &self.groups[code_id].as_ref().unwrap();
                let dcode2 = dgp.codewords[2].as_ref().unwrap();
                let acode2 = agp.codewords[2].as_ref().unwrap();

                let groups: Vec<&_> = vec![acode2, cgp.evaluated.as_ref().unwrap(), dcode2];

                circuit_hal.eval_check_interleave(
                    check_poly,
                    groups.as_slice(),
                    globals,
                    poly_mix,
                    self.po2,
                    self.cycles,
                    2,
                );
            }
            {
                let pg = self.groups[REGISTER_GROUP_ACCUM].as_mut().unwrap();
                release_buffer(
                    "accum codeword 2",
                    self.hal,
                    &mut pg.codewords[2].as_mut().unwrap(),
                );
                pg.codewords[2] = None;
            }

            {
                let dgp = &self.groups[data_id].as_ref().unwrap();
                let agp = &self.groups[accum_id].as_ref().unwrap();
                let cgp = &self.groups[code_id].as_ref().unwrap();
                let dcode3 = dgp.codewords[3].as_ref().unwrap();
                let acode3 = agp.codewords[3].as_ref().unwrap();

                let groups: Vec<&_> = vec![acode3, cgp.evaluated.as_ref().unwrap(), dcode3];

                circuit_hal.eval_check_interleave(
                    check_poly,
                    groups.as_slice(),
                    globals,
                    poly_mix,
                    self.po2,
                    self.cycles,
                    3,
                );
            }

            {
                let dgp = self.groups[data_id].as_mut().unwrap();
                let dcode0 = self.hal.alloc_elem("dcodeword0", dgp.count * self.cycles);
                dgp.codewords[0] = Some(dcode0);
            }
            {
                let dgp = &self.groups[data_id].as_ref().unwrap();
                let agp = &self.groups[accum_id].as_ref().unwrap();
                let cgp = &self.groups[code_id].as_ref().unwrap();
                let dcode0 = dgp.codewords[0].as_ref().unwrap();
                let acode0 = agp.codewords[3].as_ref().unwrap();

                self.hal.eltwise_copy_elem(&dcode0, &dgp.coeffs);
                self.hal.batch_evaluate_ntt(&dcode0, dgp.count);
                self.hal.eltwise_copy_elem(acode0, &agp.coeffs);
                self.hal.batch_evaluate_ntt(acode0, agp.count);

                let groups: Vec<&_> = vec![acode0, cgp.evaluated.as_ref().unwrap(), &dcode0];
                circuit_hal.eval_check_interleave(
                    check_poly,
                    groups.as_slice(),
                    globals,
                    poly_mix,
                    self.po2,
                    self.cycles,
                    0,
                );
            }

            {
                let pg = self.groups[data_id].as_mut().unwrap();
                pg.codewords[1] = pg.codewords[3].clone();
                pg.codewords[3] = None;
            }
            {
                let beta = H::Elem::ROU_FWD[self.po2 + 2];
                let dgp = &self.groups[data_id].as_ref().unwrap();
                let agp = &self.groups[accum_id].as_ref().unwrap();
                let cgp = &self.groups[code_id].as_ref().unwrap();
                let dcode1 = dgp.codewords[1].as_ref().unwrap();
                let acode1 = agp.codewords[3].as_ref().unwrap();

                self.hal.zk_shift_outplace(
                    &dgp.coeffs,
                    dcode1,
                    dgp.count,
                    beta,
                    1 | ZK_SHIFT_POST_BITREV,
                ); // codeword_id=1, post-NTT bit-reverse
                self.hal.batch_evaluate_ntt(&dcode1, dgp.count);
                self.hal.zk_shift_outplace(
                    &agp.coeffs,
                    acode1,
                    agp.count,
                    beta,
                    1 | ZK_SHIFT_POST_BITREV,
                ); // codeword_id=1, post-NTT bit-reverse
                self.hal.batch_evaluate_ntt(&acode1, agp.count);

                let groups: Vec<&_> = vec![acode1, cgp.evaluated.as_ref().unwrap(), &dcode1];
                circuit_hal.eval_check_interleave(
                    check_poly,
                    groups.as_slice(),
                    globals,
                    poly_mix,
                    self.po2,
                    self.cycles,
                    1,
                );
            }
        }

        {
            let pg = self.groups[accum_id].as_mut().unwrap();
            if pg.codewords[2].is_some() {
                release_buffer(
                    "accum codeword 2",
                    self.hal,
                    &mut pg.codewords[2].as_mut().unwrap(),
                )
            };
            if pg.codewords[3].is_some() {
                release_buffer(
                    "accum codeword 3",
                    self.hal,
                    &mut pg.codewords[3].as_mut().unwrap(),
                )
            };
        }

        Ok("Eval Check.")
    }

    #[cfg(all(feature = "low_vram", feature = "cuda"))]
    fn prove_group_with_idxs(
        hal: &'a H,
        pg: &PolyGroup<H>,
        iop: &mut WriteIOP<H::Field>,
        idxs: Vec<usize>,
        rou: H::Elem,
    ) -> (Vec<Vec<H::Elem>>, Vec<Vec<Digest>>) {
        pg.merkle.prove_with_idxs(
            hal,
            iop,
            idxs,
            &pg.coeffs,
            rou,
            pg.evaluated.clone(),
            pg.codewords.clone(),
        )
    }

    #[cfg(not(all(feature = "low_vram", feature = "cuda")))]
    fn prove_group_with_idxs(
        hal: &'a H,
        pg: &PolyGroup<H>,
        iop: &mut WriteIOP<H::Field>,
        idxs: Vec<usize>,
        _rou: H::Elem,
    ) -> (Vec<Vec<H::Elem>>, Vec<Vec<Digest>>) {
        pg.merkle.prove_with_idxs(hal, iop, idxs)
    }

    #[allow(dead_code)]
    #[cfg(all(feature = "low_vram", feature = "cuda"))]
    fn fri_prepare(&mut self, _check: &mut PolyGroup<H>) {
        let beta = H::Elem::ROU_FWD[self.po2 + 2];

        {
            let pg = self.groups[REGISTER_GROUP_DATA].as_mut().unwrap();
            if self.po2 >= LARGE_SEGMENT_PO2 && pg.codewords[0].is_some() {
                let codeword3 = pg.coeffs.clone();

                self.hal.zk_shift_outplace(
                    &pg.coeffs,
                    &codeword3,
                    pg.count,
                    beta,
                    3 | ZK_SHIFT_PRE_BITREV,
                ); // codeword_id=3, pre-NTT bit-reverse
                self.hal.batch_evaluate_ntt(&codeword3, pg.count);
                pg.codewords[3] = Some(codeword3);
            } else {
                release_buffer("data coeffs", self.hal, &mut pg.coeffs);
            }
        }
    }

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

    /// Sets the number of cycles to 2^po2.  This must be called
    /// once after new() before any commit_group() calls.
    pub fn set_po2(&mut self, po2: usize) {
        assert_eq!(self.po2, usize::MAX);
        assert_eq!(self.cycles, 0);
        self.po2 = po2;
        self.cycles = 1 << po2;
    }

    /// Commits a given buffer to the IOP; the values must not subsequently
    /// change.
    pub fn commit_group(&mut self, tap_group_index: usize, witness: &H::Buffer<H::Elem>) {
        scope_with!("commit_group({})", witness.name());
        let group_size = self.taps.group_size(tap_group_index);
        assert_eq!(witness.size() % group_size, 0);
        assert_eq!(witness.size() / group_size, self.cycles);
        assert!(
            self.groups[tap_group_index].is_none(),
            "Attempted to commit group {} more than once",
            self.taps.group_name(tap_group_index)
        );

        let coeffs = make_coeffs(self.hal, witness, group_size, tap_group_index);
        let group_ref = self.groups[tap_group_index].insert(PolyGroup::new(
            self.hal,
            coeffs,
            group_size,
            self.cycles,
            witness.name(),
        ));

        group_ref.merkle.commit(&mut self.iop);

        tracing::debug!(
            "{} group root: {}",
            self.taps.group_name(tap_group_index),
            group_ref.merkle.root()
        );
    }

    /// Generates the proof and returns the seal.
    pub fn finalize<C>(mut self, globals: &[&H::Buffer<H::Elem>], circuit_hal: &C) -> Vec<u32>
    where
        C: CircuitHal<H>,
    {
        scope!("finalize");

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

        cfg_if::cfg_if! {
            if #[cfg(all(feature = "low_vram", feature = "cuda"))] {
                let _ = self.eval_check(&check_poly, globals, poly_mix, circuit_hal);
            } else {
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
            }
        }

        #[cfg(feature = "circuit_debug")]
        let mut bad_z = None;

        #[cfg(feature = "circuit_debug")]
        check_poly.view(|check_out| {
            for i in (0..domain).step_by(4) {
                if check_out[i] != H::Elem::ZERO {
                    tracing::debug!("check[{i}] = 0x{:08x?}", check_out[i].to_u32_words()[0]);
                    bad_z.get_or_insert(H::ExtElem::from_subfield(
                        &H::Elem::ROU_FWD[self.po2].pow(i / 4),
                    ));
                }
            }
            // assert!(bad_z.is_none());
        });

        // Convert to coefficients.  Some tricky business here with the fact that
        // checkPoly is really an FpExt polynomial.  Nicely for us, since all the
        // roots of unity (which are the only thing that and values get multiplied
        // by) are in Fp, FpExt values act like simple vectors of Fp for the
        // purposes of interpolate/evaluate.
        self.hal.batch_interpolate_ntt(&check_poly, ext_size);

        // The next step is to convert the degree 4*n check polynomial into 4 degree n
        // polynomials so that f(x) = g0(x^4) + g1(x^4) x + g2(x^4) x^2 + g3(x^4)
        // x^3.  To do this, we normally would grab all the coefficients of f(x) =
        // sum_i c_i x^i where i % 4 == 0 and put them into a new polynomial g0(x) =
        // sum_i d0_i*x^i, where d0_i = c_(i*4).
        //
        // Amazingly, since the coefficients are bit reversed, the coefficients of g0
        // are all already next to each other and in bit-reversed for g0, as are
        // the coefficients of g1, etc. So really, we can just reinterpret 4 polys of
        // invRate*size to 16 polys of size, without actually doing anything.

        // Make the PolyGroup + add it to the IOP;
        cfg_if::cfg_if! {
            if #[cfg(all(feature = "low_vram", feature = "cuda"))] {
                let mut check_group = PolyGroup::new(self.hal, check_poly, H::CHECK_SIZE, self.cycles, "check");
            } else {
                let check_group = PolyGroup::new(self.hal, check_poly, H::CHECK_SIZE, self.cycles, "check");
            }
        }

        check_group.merkle.commit(&mut self.iop);
        tracing::debug!("checkGroup: {}", check_group.merkle.root());

        // Now pick a value for Z, which is used as the DEEP-ALI query point.
        cfg_if::cfg_if! {
            if #[cfg(feature = "circuit_debug")] {
                let z = if let Some(bad_z) = bad_z {
                    self.iop.write_field_elem_slice(bad_z.subelems());
                    bad_z
                } else {
                    self.iop.random_ext_elem()
                };
            } else {
                let z = self.iop.random_ext_elem();
            }
        }
        tracing::debug!("Z = {z:?}");

        // Get rev rou for size
        let back_one = H::ExtElem::from_subfield(&H::Elem::ROU_REV[self.po2]);
        let mut all_xs = Vec::new();

        // Now, we evaluate each group at the appropriate points (relative to Z).
        // From here on out, we always process groups in accum, code, data order,
        // since this is the order used by the codegen system (alphabetical).
        // Sometimes it's a requirement for matching generated code, but even when
        // it's not we keep the order for consistency.

        let mut eval_u: Vec<H::ExtElem> = Vec::new();
        scope!("eval_u", {
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
        scope!("poly_interpolate", {
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
        scope!("misc", {
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

            // Set the mix value, which is used for FRI batching.
        });

        let mix = self.iop.random_ext_elem();
        tracing::debug!("Mix = {mix:?}");

        // Do the coefficient mixing
        // Begin by making a zeroed output buffer
        let combo_count = self.taps.combos_size();

        cfg_if::cfg_if! {
            if #[cfg(all(feature = "low_vram", feature = "cuda"))] {
                let mut combos = scope!(
                    "alloc(combos)",
                    self.hal
                        .alloc_extelem_zeroed("combos", self.cycles * (combo_count + 1))
                );
            } else {
                let combos = scope!(
                    "alloc(combos)",
                    self.hal
                        .alloc_extelem_zeroed("combos", self.cycles * (combo_count + 1))
                );
            }
        }

        scope!("mix_poly_coeffs", {
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

        scope!("load_combos", {
            let reg_sizes: Vec<_> = self.taps.regs().map(|x| x.size() as u32).collect();
            let reg_combo_ids: Vec<_> = self.taps.regs().map(|x| x.combo_id() as u32).collect();

            scope!("prepare", {
                self.hal.combos_prepare(
                    &combos,
                    &coeff_u,
                    combo_count,
                    self.cycles,
                    &reg_sizes,
                    &reg_combo_ids,
                    &mix,
                );
            });

            scope!("divide", {
                let mut chunks = vec![];

                // Divide each element by (x - Z * back1^back) for each back
                for i in 0..combo_count {
                    let mut pows = vec![];
                    for &back in self.taps.get_combo(i).slice() {
                        pows.push(z * back_one.pow(back.into()));
                    }
                    chunks.push((i, pows));
                }

                // Divide check polys by z^EXT_SIZE
                chunks.push((combo_count, vec![z_pow]));

                self.hal.combos_divide(&combos, chunks, self.cycles);
            });
        });

        // Sum the combos up into one final polynomial + make it into 4 Fp polys.
        // Additionally, it needs to be bit reversed to make everyone happy
        let final_poly_coeffs = scope!("sum", {
            let final_poly_coeffs = self
                .hal
                .alloc_elem("final_poly_coeffs", self.cycles * ext_size);
            self.hal.eltwise_sum_extelem(&final_poly_coeffs, &combos);
            final_poly_coeffs
        });

        cfg_if::cfg_if! {
            if #[cfg(all(feature = "low_vram", feature = "cuda"))] {
                release_buffer_ext("combos", self.hal, &mut combos);
            }
        }

        // Finally do the FRI protocol to prove the degree of the polynomial
        scope!(
            "bit_rev",
            self.hal.batch_bit_reverse(&final_poly_coeffs, ext_size)
        );
        tracing::debug!("FRI-proof, size = {}", final_poly_coeffs.size() / ext_size);

        cfg_if::cfg_if! {
            if #[cfg(all(feature = "low_vram", feature = "cuda"))] {
                self.fri_prepare(&mut check_group);
            }
        }

        let rou = H::Elem::ROU_FWD[self.po2 + 2];
        fri_prove(self.hal, &mut self.iop, &final_poly_coeffs, |iop, idx| {
            let mut querys = Vec::new();
            for pg in self.groups.iter() {
                let pg = pg.as_ref().unwrap();
                querys.push(Self::prove_group_with_idxs(
                    self.hal,
                    pg,
                    iop,
                    idx.clone(),
                    rou,
                ));
            }
            querys.push(Self::prove_group_with_idxs(
                self.hal,
                &check_group,
                iop,
                idx.clone(),
                rou,
            ));
            querys
        });

        let proven_soundness_error =
            super::soundness::proven::<H>(self.taps, final_poly_coeffs.size());
        tracing::debug!("proven_soundness_error: {proven_soundness_error:?}");

        let conjectured_security =
            super::soundness::toy_model_security::<H>(self.taps, final_poly_coeffs.size());
        tracing::debug!("conjectured_security: {conjectured_security:?}");

        // Return final proof
        let proof = self.iop.proof;
        tracing::debug!("Proof size = {}", proof.len());
        proof
    }
}
