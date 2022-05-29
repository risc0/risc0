use alloc::boxed::Box;

use risc0_zkp_core::{fp::Fp, fp4::Fp4};

pub type BoxedSlice<T> = Box<dyn Slice<T>>;

pub trait Slice<T> {
    fn size(&self) -> usize;

    // fn offset(&self) -> usize;

    // fn slice(&self, offset: usize, size: usize) -> BoxedSlice<T>;

    fn view(&self) -> &[T];

    fn view_mut(&mut self) -> &mut [T];
}

pub fn alloc<T>(size: usize) -> BoxedSlice<T> {
    todo!()
}

pub fn copy_from<T>(from: &[T]) -> BoxedSlice<T> {
    todo!()
}

pub fn batch_expand(output: &mut dyn Slice<Fp>, input: &dyn Slice<Fp>, count: usize) {
    todo!()
}

pub fn batch_evaluate_ntt(io: &dyn Slice<Fp>, count: usize, expand_bits: usize) {
    todo!()
}

pub fn batch_interpolate_ntt(io: &dyn Slice<Fp>, count: usize) {
    todo!()
}

pub fn batch_bit_reverse(io: &dyn Slice<Fp>, count: usize) {
    todo!()
}

pub fn batch_evaluate_any(
    coeffs: &dyn Slice<Fp>,
    poly_count: usize,
    which: &dyn Slice<u32>,
    xs: &dyn Slice<Fp4>,
    out: &dyn Slice<Fp4>,
) {
    todo!()
}

pub fn zk_shift(io: &dyn Slice<Fp>, count: usize) {
    todo!()
}

pub fn mix_poly_coeffs(
    out: &dyn Slice<Fp4>,
    mix_start: &dyn Slice<Fp4>,
    mix: &dyn Slice<Fp4>,
    input: &dyn Slice<Fp>,
    combos: &dyn Slice<u32>,
    input_size: usize,
    count: usize,
) {
    todo!()
}

pub fn eltwise_sum_fp4(output: &dyn Slice<Fp>, input: &dyn Slice<Fp4>) {
    todo!()
}

pub fn fri_fold(output: &dyn Slice<Fp>, input: &dyn Slice<Fp>, mix: &dyn Slice<Fp4>) {
    todo!()
}
