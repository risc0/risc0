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

#[cfg(feature = "host")]
pub use host::CpuVerifyHal;

use self::adapter::VerifyAdapter;
// use log::debug;
use crate::{
    adapter::{CircuitInfo, TapsProvider},
    core::{
        // TODO: Cleanup imports
        fp::Fp,
        fp4::Fp4,
        log2_ceil,
        sha::{Digest, Sha},
    },
    field::{baby_bear::BabyBear, Elem, ExtElem, Field, RootsOfUnity},
    taps::RegisterGroup,
    verify::{fri::fri_verify, merkle::MerkleTreeVerifier, read_iop::ReadIOP},
    CHECK_SIZE, INV_RATE, MAX_CYCLES_PO2, QUERIES,
};

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

// [borrowed from the main HAL]
//
// Baby bear adapters to facilitate migration to generics.  They
// convert between a genericizied baby bear type and a concreate baby
// bear type.  Once everything uses genericized types, we can get rid
// of these.
//
// If called with a non-baby-bear field, they will produce an error at
// runtime.
//
// TODO: Make it so these aren't necessary anymore.
macro_rules! baby_bear_adapter {
    ($fn_name:ident, $slice_fn_name:ident, $mut_slice_fn_name:ident, $from_ty:ty, $to_ty: ty $(,)?) => {
        fn $fn_name(val: $from_ty) -> $to_ty {
            let val_any = &val as &dyn core::any::Any;
            if let Some(val) = val_any.downcast_ref::<$to_ty>() {
                *val
            } else {
                panic!("Unable to convert between baby bear types {} and {}; other fields not supported yet.",
                       core::any::type_name::<$from_ty>(),
                       core::any::type_name::<$to_ty>());
            }
        }

        // Rust doesn't let us put a reference in an any, so we have
        // to resort to unsafe.  Specify lifetimes explicitly here
        // to avoid any confusion.
        fn $slice_fn_name<'a>(val: &'a [$from_ty]) -> &'a [$to_ty] {
            let len = val.len();
            if core::any::TypeId::of::<$from_ty>() == core::any::TypeId::of::<$to_ty>() {
                let ptr: *const $from_ty = val.as_ptr();
                let out: *const $to_ty = ptr.cast();
                unsafe { core::slice::from_raw_parts(out, len) }
            } else {
                panic!("Unable to convert between baby bear types &[{}] and &[{}]; other fields not supported yet.",
                       core::any::type_name::<$from_ty>(),
                       core::any::type_name::<$to_ty>());
            }
        }

        fn $mut_slice_fn_name<'a>(val: &'a mut [$from_ty]) -> &'a mut [$to_ty] {
            let len = val.len();
            if core::any::TypeId::of::<$from_ty>() == core::any::TypeId::of::<$to_ty>() {
                let ptr: *mut $from_ty = val.as_mut_ptr();
                let out: *mut $to_ty = ptr.cast();
                unsafe { core::slice::from_raw_parts_mut(out, len) }
            } else {
                panic!("Unable to convert between baby bear types &mut [{}] and &mut [{}]; other fields not supported yet.",
                       core::any::type_name::<$from_ty>(),
                       core::any::type_name::<$to_ty>());
            }
        }
    };
}

pub trait VerifyHal {
    type Sha: Sha;
    type Field: Field;

    fn sha(&self) -> &Self::Sha;

    fn debug(&self, msg: &str);

    fn compute_polynomial(
        &self,
        u: &[<Self::Field as Field>::ExtElem],
        poly_mix: <Self::Field as Field>::ExtElem,
        out: &[<Self::Field as Field>::Elem],
        mix: &[<Self::Field as Field>::Elem],
    ) -> <Self::Field as Field>::ExtElem;

    /// Evaluate a polynomial whose coefficients are in the extension field at a
    /// point.
    fn poly_eval(
        &self,
        coeffs: &[<Self::Field as Field>::ExtElem],
        x: <Self::Field as Field>::ExtElem,
        y: <Self::Field as Field>::Elem,
    ) -> <Self::Field as Field>::ExtElem {
        let mut mul_fp = <Self::Field as Field>::Elem::ONE;
        let mut mul_fp4 = <Self::Field as Field>::ExtElem::ONE;
        let mut tot = <Self::Field as Field>::ExtElem::ZERO;
        for i in 0..coeffs.len() {
            tot += coeffs[i] * mul_fp * mul_fp4;
            mul_fp *= y;
            mul_fp4 *= x;
        }
        tot
    }

    // Adapters to convert to/from baby bear field until all code is migrated.
    // TODO: Remove once migration complete
    baby_bear_adapter!(
        to_baby_bear_fp,
        to_baby_bear_fp_slice,
        to_baby_bear_fp_slice_mut,
        <Self::Field as Field>::Elem,
        <BabyBear as Field>::Elem,
    );
    baby_bear_adapter!(
        to_baby_bear_fp4,
        to_baby_bear_fp4_slice,
        to_baby_bear_fp4_slice_mut,
        <Self::Field as Field>::ExtElem,
        <BabyBear as Field>::ExtElem,
    );
    baby_bear_adapter!(
        from_baby_bear_fp,
        from_baby_bear_fp_slice,
        from_baby_bear_fp_slice_mut,
        <BabyBear as Field>::Elem,
        <Self::Field as Field>::Elem,
    );
    baby_bear_adapter!(
        from_baby_bear_fp4,
        from_baby_bear_fp4_slice,
        from_baby_bear_fp4_slice_mut,
        <BabyBear as Field>::ExtElem,
        <Self::Field as Field>::ExtElem,
    );
}

#[cfg(feature = "host")]
mod host {
    use super::*;
    use crate::adapter::{PolyExt, PolyExtContext};

    // TODO: Not certain how best to handle the unused Field that's needed to
    // indicate which sorts of elements to use for calculations...
    pub struct CpuVerifyHal<'a, S: Sha, C: PolyExt, F: Field> {
        sha: &'a S,
        circuit: &'a C,
        field: &'a F,
    }

    impl<'a, S: Sha, C: PolyExt, F: Field> CpuVerifyHal<'a, S, C, F> {
        pub fn new(sha: &'a S, circuit: &'a C, field: &'a F) -> Self {
            Self {
                sha,
                circuit,
                field,
            }
        }
    }

    impl<'a, S: Sha, C: PolyExt, F: Field> VerifyHal for CpuVerifyHal<'a, S, C, F> {
        type Sha = S;
        type Field = F;

        fn sha(&self) -> &Self::Sha {
            self.sha
        }

        fn debug(&self, msg: &str) {
            log::debug!("{}", msg);
        }

        fn compute_polynomial(
            &self,
            u: &[<F as Field>::ExtElem],
            poly_mix: <F as Field>::ExtElem,
            out: &[<F as Field>::Elem],
            mix: &[<F as Field>::Elem],
        ) -> <F as Field>::ExtElem {
            let ctx = PolyExtContext {
                mix: <Self as VerifyHal>::to_baby_bear_fp4(poly_mix),
            };
            let args: &[&[Fp]] = &[
                <Self as VerifyHal>::to_baby_bear_fp_slice(out),
                <Self as VerifyHal>::to_baby_bear_fp_slice(mix),
            ];
            let result =
                self.circuit
                    .poly_ext(&ctx, <Self as VerifyHal>::to_baby_bear_fp4_slice(u), args);
            <Self as VerifyHal>::from_baby_bear_fp4(result.tot)
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
    let poly_mix = <H::Field as Field>::ExtElem::random(&mut iop);

    hal.debug("check_merkle");
    let check_merkle = MerkleTreeVerifier::new(&mut iop, domain, CHECK_SIZE, QUERIES);
    // debug!("checkRoot = {}", check_merkle.root());

    let z = <H::Field as Field>::ExtElem::random(&mut iop);
    // debug!("Z = {z:?}");
    let back_one = <<H::Field as Field>::Elem as RootsOfUnity>::ROU_REV[po2 as usize];

    // Read the U coeffs + commit their hash
    let num_taps = taps.tap_size();
    let coeff_u = iop.read_pod_slice(num_taps + CHECK_SIZE);
    let hash_u = *hal.sha().hash_raw_pod_slice(coeff_u);
    iop.commit(&hash_u);

    // Now, convert to evaluated values
    let mut cur_pos = 0;
    let mut eval_u = Vec::with_capacity(num_taps);
    for reg in taps.regs() {
        for i in 0..reg.size() {
            let x = z * back_one.pow(reg.back(i));
            let fx = hal.poly_eval(
                &coeff_u[cur_pos..(cur_pos + reg.size())],
                x,
                <H::Field as Field>::Elem::ONE,
            );
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
        <H as VerifyHal>::from_baby_bear_fp_slice(&adapter.out.unwrap()),
        <H as VerifyHal>::from_baby_bear_fp_slice(&adapter.mix),
    );
    hal.debug("< compute_polynomial");
    // debug!("Result = {result:?}");

    // Now generate the check polynomial
    // TODO: This currently treats the extension degree as hardcoded at 4, with
    // the structure of the code and the value of `remap` (and how it is
    // accessed) only working in the extension degree = 4 case.
    // However, for generic fields the extension degree may be different
    // TODO: Therefore just using the to/from baby bear shims for now
    let mut check = Fp4::ZERO;
    let remap = [0, 2, 1, 3];
    let fp0 = Fp::from(0 as u32);
    let fp1 = Fp::from(1 as u32);
    for i in 0..4 {
        let rmi = remap[i];
        check += <H as VerifyHal>::to_baby_bear_fp4(coeff_u[num_taps + rmi + 0] * z.pow(i))
            * Fp4::new(fp1, fp0, fp0, fp0);
        check += <H as VerifyHal>::to_baby_bear_fp4(coeff_u[num_taps + rmi + 4] * z.pow(i))
            * Fp4::new(fp0, fp1, fp0, fp0);
        check += <H as VerifyHal>::to_baby_bear_fp4(coeff_u[num_taps + rmi + 8] * z.pow(i))
            * Fp4::new(fp0, fp0, fp1, fp0);
        check += <H as VerifyHal>::to_baby_bear_fp4(coeff_u[num_taps + rmi + 12] * z.pow(i))
            * Fp4::new(fp0, fp0, fp0, fp1);
    }
    check *= (Fp4::from_u32(3) * <H as VerifyHal>::to_baby_bear_fp4(z)).pow(size) - Fp4::ONE;
    // debug!("Check = {check:?}");
    if <H as VerifyHal>::from_baby_bear_fp4(check) != result {
        return Err(VerificationError::InvalidProof);
    }

    // Set the mix mix value
    let mix = <H::Field as Field>::ExtElem::random(&mut iop);
    // debug!("mix = {mix:?}");

    // Make the mixed U polynomials
    let mut combo_u: Vec<Vec<<H::Field as Field>::ExtElem>> = Vec::with_capacity(combo_count + 1);
    combo_u.extend(
        (0..combo_count)
            .into_iter()
            .map(|i| vec![<H::Field as Field>::ExtElem::ZERO; taps.get_combo(i).size()]),
    );
    let mut cur_mix = <H::Field as Field>::ExtElem::ONE;
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
    combo_u.push(vec![<H::Field as Field>::ExtElem::ZERO]);
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

    let gen = <<H::Field as Field>::Elem as RootsOfUnity>::ROU_FWD[log2_ceil(domain)];
    // debug!("FRI-verify, size = {size}");
    fri_verify(
        hal,
        &mut iop,
        size,
        |iop: &mut ReadIOP<_>, idx: usize| -> Result<Fp4, VerificationError> {
            hal.debug("fri_verify");
            let x = <H::Field as Field>::ExtElem::from_subfield(&gen.pow(idx));
            let rows = [
                accum_merkle.verify::<H::Field>(iop, idx)?,
                code_merkle.verify::<H::Field>(iop, idx)?,
                data_merkle.verify::<H::Field>(iop, idx)?,
            ];
            let check_row = check_merkle.verify::<H::Field>(iop, idx)?;
            let mut tot = vec![<H::Field as Field>::ExtElem::ZERO; combo_count + 1];
            for (reg, cur) in zip(taps.regs(), tap_mix_pows.iter()) {
                tot[reg.combo_id()] += *cur * rows[reg.group() as usize][reg.offset()];
            }
            for (i, cur) in zip(0..CHECK_SIZE, check_mix_pows.iter()) {
                tot[combo_count] += *cur * check_row[i];
            }
            let mut ret = <H::Field as Field>::ExtElem::ZERO;
            for i in 0..combo_count {
                let num = tot[i] - hal.poly_eval(&combo_u[i], x, <H::Field as Field>::Elem::ONE);
                let mut divisor = <H::Field as Field>::ExtElem::ONE;
                for back in taps.get_combo(i).slice() {
                    divisor *= x - z * back_one.pow(*back as usize);
                }
                ret += num * divisor.inv();
            }
            let check_num = tot[combo_count] - combo_u[combo_count][0];
            let check_div = x - z.pow(INV_RATE);
            ret += check_num * check_div.inv();
            Ok(H::to_baby_bear_fp4(ret))
        },
    )?;
    iop.verify_complete();
    Ok(())
}
