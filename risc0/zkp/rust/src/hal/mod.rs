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

//! Hardware Abstraction Layer (HAL) for accelerating the ZKP system.

pub mod cpu;
#[cfg(any(feature = "opencl", feature = "cuda"))]
pub mod gpu;

use crate::{
    core::sha::Digest,
    field::{self, baby_bear::BabyBear},
};

pub trait Buffer<T>: Clone {
    fn size(&self) -> usize;

    fn slice(&self, offset: usize, size: usize) -> Self;

    fn view<F: FnOnce(&[T])>(&self, f: F);

    fn view_mut<F: FnOnce(&mut [T])>(&self, f: F);
}

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

pub trait Hal {
    type Field: field::Field;
    type BufferDigest: Buffer<Digest>;
    type BufferFp: Buffer<<Self::Field as field::Field>::Elem>;
    type BufferFp4: Buffer<<Self::Field as field::Field>::ExtElem>;
    type BufferU32: Buffer<u32>;

    fn alloc_digest(&self, size: usize) -> Self::BufferDigest;
    fn alloc_fp(&self, size: usize) -> Self::BufferFp;
    fn alloc_fp4(&self, size: usize) -> Self::BufferFp4;
    fn alloc_u32(&self, size: usize) -> Self::BufferU32;

    fn copy_digest_from(&self, slice: &[Digest]) -> Self::BufferDigest;
    fn copy_fp_from(&self, slice: &[<Self::Field as field::Field>::Elem]) -> Self::BufferFp;
    fn copy_fp4_from(&self, slice: &[<Self::Field as field::Field>::ExtElem]) -> Self::BufferFp4;
    fn copy_u32_from(&self, slice: &[u32]) -> Self::BufferU32;

    fn batch_expand(&self, output: &Self::BufferFp, input: &Self::BufferFp, count: usize);

    fn batch_evaluate_ntt(&self, io: &Self::BufferFp, count: usize, expand_bits: usize);

    fn batch_interpolate_ntt(&self, io: &Self::BufferFp, count: usize);

    fn batch_bit_reverse(&self, io: &Self::BufferFp, count: usize);

    fn batch_evaluate_any(
        &self,
        coeffs: &Self::BufferFp,
        poly_count: usize,
        which: &Self::BufferU32,
        xs: &Self::BufferFp4,
        out: &Self::BufferFp4,
    );

    fn zk_shift(&self, io: &Self::BufferFp, count: usize);

    fn mix_poly_coeffs(
        &self,
        out: &Self::BufferFp4,
        mix_start: &<Self::Field as field::Field>::ExtElem,
        mix: &<Self::Field as field::Field>::ExtElem,
        input: &Self::BufferFp,
        combos: &Self::BufferU32,
        input_size: usize,
        count: usize,
    );

    fn eltwise_add_fp(
        &self,
        output: &Self::BufferFp,
        input1: &Self::BufferFp,
        input2: &Self::BufferFp,
    );

    fn eltwise_sum_fp4(&self, output: &Self::BufferFp, input: &Self::BufferFp4);

    fn eltwise_copy_fp(&self, output: &Self::BufferFp, input: &Self::BufferFp);

    fn eltwise_copy_digest(&self, output: &Self::BufferDigest, input: &Self::BufferDigest);

    fn fri_fold(
        &self,
        output: &Self::BufferFp,
        input: &Self::BufferFp,
        mix: &<Self::Field as field::Field>::ExtElem,
    );

    fn sha_rows(&self, output: &Self::BufferDigest, matrix: &Self::BufferFp);

    fn sha_fold(&self, io: &Self::BufferDigest, input_size: usize, output_size: usize);

    // fn fri_fold_new(&self, input: &Self::BufferFp, mix: &<Self::Field as
    // field::Field>::ExtElem) -> Self::BufferFp {     let output =
    // self.alloc_fp() }

    fn fri_finalize(
        &self,
        input: &Self::BufferFp,
        input_size: usize,
        ext_size: usize,
    ) -> Self::BufferFp {
        let coeffs = self.alloc_fp(input_size);
        self.eltwise_copy_fp(&coeffs, &input);
        self.batch_bit_reverse(&coeffs, ext_size);
        coeffs
    }

    // Adapters to convert to/from baby bear field until all code is migrated.
    baby_bear_adapter!(
        to_baby_bear_fp,
        to_baby_bear_fp_slice,
        to_baby_bear_fp_slice_mut,
        <Self::Field as field::Field>::Elem,
        <BabyBear as field::Field>::Elem,
    );
    baby_bear_adapter!(
        to_baby_bear_fp4,
        to_baby_bear_fp4_slice,
        to_baby_bear_fp4_slice_mut,
        <Self::Field as field::Field>::ExtElem,
        <BabyBear as field::Field>::ExtElem,
    );
    baby_bear_adapter!(
        from_baby_bear_fp,
        from_baby_bear_fp_slice,
        from_baby_bear_fp_slice_mut,
        <BabyBear as field::Field>::Elem,
        <Self::Field as field::Field>::Elem,
    );
    baby_bear_adapter!(
        from_baby_bear_fp4,
        from_baby_bear_fp4_slice,
        from_baby_bear_fp4_slice_mut,
        <BabyBear as field::Field>::ExtElem,
        <Self::Field as field::Field>::ExtElem,
    );
}

pub trait EvalCheck<H: Hal> {
    /// Compute check polynomial.
    fn eval_check(
        &self,
        check: &H::BufferFp,
        code: &H::BufferFp,
        data: &H::BufferFp,
        accum: &H::BufferFp,
        mix: &H::BufferFp,
        out: &H::BufferFp,
        poly_mix: <H::Field as field::Field>::ExtElem,
        po2: usize,
        steps: usize,
    );
}
