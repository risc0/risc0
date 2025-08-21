// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! CPU implementation of the HAL.

use std::{fmt::Debug, ops::Range, sync::Arc};

use ndarray::{ArrayView, ArrayViewMut, Axis};
use parking_lot::{
    MappedRwLockReadGuard, MappedRwLockWriteGuard, RwLock, RwLockReadGuard, RwLockWriteGuard,
};
use rayon::prelude::*;
use risc0_core::field::{Elem, ExtElem, Field};

use super::{Buffer, Hal, tracker};
use crate::{
    FRI_FOLD,
    core::{
        digest::Digest,
        hash::HashSuite,
        log2_ceil,
        ntt::{bit_rev_32, bit_reverse, evaluate_ntt, expand, interpolate_ntt},
    },
};

pub struct CpuHal<F: Field> {
    suite: HashSuite<F>,
}

impl<F: Field> CpuHal<F> {
    pub fn new(suite: HashSuite<F>) -> Self {
        Self { suite }
    }
}

#[derive(Debug, Clone)]
struct Region(usize, usize);

impl Region {
    fn offset(&self) -> usize {
        self.0
    }

    fn size(&self) -> usize {
        self.1
    }

    fn range(&self) -> Range<usize> {
        Range {
            start: self.offset(),
            end: self.offset() + self.size(),
        }
    }
}

struct TrackedVec<T>(Vec<T>);

impl<T> TrackedVec<T> {
    pub fn new(vec: Vec<T>) -> Self {
        tracker()
            .lock()
            .unwrap()
            .alloc(vec.capacity() * std::mem::size_of::<T>());
        Self(vec)
    }
}

impl<T> Drop for TrackedVec<T> {
    fn drop(&mut self) {
        tracker()
            .lock()
            .unwrap()
            .free(self.0.capacity() * std::mem::size_of::<T>());
    }
}

#[derive(Clone)]
pub struct CpuBuffer<T> {
    name: &'static str,
    buf: Arc<RwLock<TrackedVec<T>>>,
    region: Region,
}

enum SyncSliceRef<'a, T: Default + Clone> {
    FromBuf {
        _inner: MappedRwLockWriteGuard<'a, [T]>,
    },
    FromSlice {
        _inner: &'a SyncSlice<'a, T>,
    },
}

/// A buffer which can be used across multiple threads.  Users are
/// responsible for ensuring that no two threads access the same
/// element at the same time.
pub(crate) struct SyncSlice<'a, T: Default + Clone> {
    _buf: SyncSliceRef<'a, T>,
    ptr: *mut T,
    size: usize,
}

// SAFETY: SyncSlice keeps a MappedRwLockWriteGuard to the original CpuBuffer, so
// no other as_slice or as_slice_muts can be active at the same time.
//
// The user of the SyncSlice is responsible for ensuring that no
// two threads access the same elements at the same time.
unsafe impl<T: Default + Clone> Sync for SyncSlice<'_, T> {}

impl<'a, T: Default + Clone> SyncSlice<'a, T> {
    pub fn new(mut buf: MappedRwLockWriteGuard<'a, [T]>) -> Self {
        let ptr = buf.as_mut_ptr();
        let size = buf.len();
        SyncSlice {
            ptr,
            size,
            _buf: SyncSliceRef::FromBuf { _inner: buf },
        }
    }

    pub fn get_ptr(&self) -> *mut T {
        self.ptr
    }

    pub fn get(&self, offset: usize) -> T {
        assert!(offset < self.size);
        unsafe { self.ptr.add(offset).read() }
    }

    pub fn set(&self, offset: usize, val: T) {
        assert!(offset < self.size);
        unsafe { self.ptr.add(offset).write(val) }
    }

    pub fn slice(&self, offset: usize, size: usize) -> SyncSlice<'_, T> {
        assert!(
            offset + size <= self.size,
            "Attempting to slice [{offset}, {offset} + {size} = {}) from a slice of length {}",
            offset + size,
            self.size
        );
        SyncSlice {
            _buf: SyncSliceRef::FromSlice { _inner: self },
            ptr: unsafe { self.ptr.add(offset) },
            size,
        }
    }

    pub fn size(&self) -> usize {
        self.size
    }
}

impl<T: Default + Clone> CpuBuffer<T> {
    fn new(name: &'static str, size: usize) -> Self {
        let buf = vec![T::default(); size];
        CpuBuffer {
            name,
            buf: Arc::new(RwLock::new(TrackedVec::new(buf))),
            region: Region(0, size),
        }
    }

    pub fn get_ptr(&self) -> *mut T {
        self.as_slice_sync().get_ptr()
    }

    fn copy_from(name: &'static str, slice: &[T]) -> Self {
        CpuBuffer {
            name,
            buf: Arc::new(RwLock::new(TrackedVec::new(slice.to_vec()))),
            region: Region(0, slice.len()),
        }
    }

    pub fn from_fn<F>(name: &'static str, size: usize, f: F) -> Self
    where
        F: FnMut(usize) -> T,
    {
        let vec = (0..size).map(f).collect();
        CpuBuffer {
            name,
            buf: Arc::new(RwLock::new(TrackedVec::new(vec))),
            region: Region(0, size),
        }
    }

    pub fn as_slice(&self) -> MappedRwLockReadGuard<'_, [T]> {
        let vec = self.buf.read();
        RwLockReadGuard::map(vec, |vec| &vec.0[self.region.range()])
    }

    pub fn as_slice_mut(&self) -> MappedRwLockWriteGuard<'_, [T]> {
        let vec = self.buf.write();
        RwLockWriteGuard::map(vec, |vec| &mut vec.0[self.region.range()])
    }

    pub(crate) fn as_slice_sync(&self) -> SyncSlice<'_, T> {
        SyncSlice::new(self.as_slice_mut())
    }
}

impl<T: Default + Clone> From<Vec<T>> for CpuBuffer<T> {
    fn from(vec: Vec<T>) -> CpuBuffer<T> {
        let size = vec.len();
        CpuBuffer {
            name: "vec",
            buf: Arc::new(RwLock::new(TrackedVec::new(vec))),
            region: Region(0, size),
        }
    }
}

impl<T: Clone> Buffer<T> for CpuBuffer<T> {
    fn name(&self) -> &'static str {
        self.name
    }

    fn size(&self) -> usize {
        self.region.size()
    }

    fn slice(&self, offset: usize, size: usize) -> CpuBuffer<T> {
        assert!(offset + size <= self.size());
        let region = Region(self.region.offset() + offset, size);
        CpuBuffer {
            name: self.name,
            buf: Arc::clone(&self.buf),
            region,
        }
    }

    fn get_at(&self, idx: usize) -> T {
        let buf = self.buf.read();
        buf.0[idx].clone()
    }

    fn view<F: FnOnce(&[T])>(&self, f: F) {
        let buf = self.buf.read();
        f(&buf.0[self.region.range()]);
    }

    fn view_mut<F: FnOnce(&mut [T])>(&self, f: F) {
        let mut buf = self.buf.write();
        f(&mut buf.0[self.region.range()]);
    }

    fn to_vec(&self) -> Vec<T> {
        self.buf.read().0.clone()
    }
}

impl<F: Field> Hal for CpuHal<F> {
    type Field = F;
    type Elem = F::Elem;
    type ExtElem = F::ExtElem;
    type Buffer<T: Clone + Debug + PartialEq> = CpuBuffer<T>;

    fn alloc_elem(&self, name: &'static str, size: usize) -> Self::Buffer<Self::Elem> {
        CpuBuffer::new(name, size)
    }

    fn copy_from_elem(&self, name: &'static str, slice: &[Self::Elem]) -> Self::Buffer<Self::Elem> {
        CpuBuffer::copy_from(name, slice)
    }

    fn alloc_extelem(&self, name: &'static str, size: usize) -> Self::Buffer<Self::ExtElem> {
        CpuBuffer::new(name, size)
    }

    fn copy_from_extelem(
        &self,
        name: &'static str,
        slice: &[Self::ExtElem],
    ) -> Self::Buffer<Self::ExtElem> {
        CpuBuffer::copy_from(name, slice)
    }

    fn alloc_digest(&self, name: &'static str, size: usize) -> Self::Buffer<Digest> {
        CpuBuffer::new(name, size)
    }

    fn copy_from_digest(&self, name: &'static str, slice: &[Digest]) -> Self::Buffer<Digest> {
        CpuBuffer::copy_from(name, slice)
    }

    fn alloc_u32(&self, name: &'static str, size: usize) -> Self::Buffer<u32> {
        CpuBuffer::new(name, size)
    }

    fn copy_from_u32(&self, name: &'static str, slice: &[u32]) -> Self::Buffer<u32> {
        CpuBuffer::copy_from(name, slice)
    }

    fn batch_expand_into_evaluate_ntt(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
        count: usize,
        expand_bits: usize,
    ) {
        // batch_expand
        {
            let out_size = output.size() / count;
            let in_size = input.size() / count;
            let expand_bits = log2_ceil(out_size / in_size);
            assert_eq!(out_size, in_size * (1 << expand_bits));
            assert_eq!(out_size * count, output.size());
            assert_eq!(in_size * count, input.size());
            output
                .as_slice_mut()
                .par_chunks_exact_mut(out_size)
                .zip(input.as_slice().par_chunks_exact(in_size))
                .for_each(|(output, input)| {
                    expand(output, input, expand_bits);
                });
        }

        // batch_evaluate_ntt
        {
            let row_size = output.size() / count;
            assert_eq!(row_size * count, output.size());
            output
                .as_slice_mut()
                .par_chunks_exact_mut(row_size)
                .for_each(|row| {
                    evaluate_ntt::<Self::Elem, Self::Elem>(row, expand_bits);
                });
        }
    }

    fn batch_interpolate_ntt(&self, io: &Self::Buffer<Self::Elem>, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        io.as_slice_mut()
            .par_chunks_exact_mut(row_size)
            .for_each(|row| {
                interpolate_ntt::<Self::Elem, Self::Elem>(row);
            });
    }

    fn batch_bit_reverse(&self, io: &Self::Buffer<Self::Elem>, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        io.as_slice_mut()
            .par_chunks_exact_mut(row_size)
            .for_each(|row| {
                bit_reverse(row);
            });
    }

    fn batch_evaluate_any(
        &self,
        coeffs: &Self::Buffer<Self::Elem>,
        poly_count: usize,
        which: &Self::Buffer<u32>,
        xs: &Self::Buffer<Self::ExtElem>,
        out: &Self::Buffer<Self::ExtElem>,
    ) {
        let po2 = log2_ceil(coeffs.size() / poly_count);
        assert_eq!(poly_count * (1 << po2), coeffs.size());
        let eval_count = which.size();
        assert_eq!(xs.size(), eval_count);
        assert_eq!(out.size(), eval_count);
        let coeffs = &*coeffs.as_slice();
        let which = which.as_slice();
        let xs = xs.as_slice();
        let mut out = out.as_slice_mut();
        (&which[..], &xs[..], &mut out[..])
            .into_par_iter()
            .for_each(|(id, x, out)| {
                let mut tot = Self::ExtElem::ZERO;
                let mut cur = Self::ExtElem::ONE;
                let id = *id as usize;
                let count = 1 << po2;
                let local = &coeffs[count * id..count * id + count];
                for coeff in local {
                    tot += cur * *coeff;
                    cur *= *x;
                }
                *out = tot;
            });
    }

    fn zk_shift(&self, io: &Self::Buffer<Self::Elem>, poly_count: usize) {
        let bits = log2_ceil(io.size() / poly_count);
        let count = io.size();
        assert_eq!(io.size(), poly_count * (1 << bits));
        let mut io = io.as_slice_mut();
        (&mut io[..], 0..count)
            .into_par_iter()
            .for_each(|(io, idx)| {
                let pos = idx & ((1 << bits) - 1);
                let rev = bit_rev_32(pos as u32) >> (32 - bits);
                let pow3 = Self::Elem::from_u64(3).pow(rev as usize);
                *io *= pow3;
            });
    }

    fn mix_poly_coeffs(
        &self,
        output: &Self::Buffer<Self::ExtElem>,
        mix_start: &Self::ExtElem,
        mix: &Self::ExtElem,
        input: &Self::Buffer<Self::Elem>,
        combos: &Self::Buffer<u32>,
        input_size: usize,
        count: usize,
    ) {
        tracing::debug!(
            "output: {}, input: {}, combos: {}, input_size: {input_size}, count: {count}",
            output.size(),
            input.size(),
            combos.size()
        );

        let mut mix_cur = *mix_start;
        let mix_pows: Vec<_> = (0..input_size)
            .map(|_| {
                let val = mix_cur;
                mix_cur *= *mix;
                val
            })
            .collect();

        // Make everything into plain slices so we can pass them between threads.
        let combos: &[u32] = &combos.as_slice();
        let mix_pows: &[Self::ExtElem] = mix_pows.as_slice();
        let input: &[Self::Elem] = &input.as_slice();

        output
            .as_slice_mut()
            .par_chunks_exact_mut(count)
            .enumerate()
            .for_each(|(id, out_chunk): (usize, &mut [Self::ExtElem])| {
                for i in 0..input_size {
                    if combos[i] != id as u32 {
                        continue;
                    }
                    for idx in 0..count {
                        out_chunk[idx] += mix_pows[i] * input[count * i + idx];
                    }
                }
            });
    }

    fn eltwise_add_elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input1: &Self::Buffer<Self::Elem>,
        input2: &Self::Buffer<Self::Elem>,
    ) {
        assert_eq!(output.size(), input1.size());
        assert_eq!(output.size(), input2.size());
        let mut output = output.as_slice_mut();
        let input1 = input1.as_slice();
        let input2 = input2.as_slice();
        (&mut output[..], &input1[..], &input2[..])
            .into_par_iter()
            .for_each(|(o, a, b)| {
                *o = *a + *b;
            });
    }

    fn eltwise_sum_extelem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::ExtElem>,
    ) {
        let count = output.size() / Self::ExtElem::EXT_SIZE;
        let to_add = input.size() / count;
        assert_eq!(output.size(), count * Self::ExtElem::EXT_SIZE);
        assert_eq!(input.size(), count * to_add);
        let mut output = output.as_slice_mut();
        let mut output =
            ArrayViewMut::from_shape((Self::ExtElem::EXT_SIZE, count), &mut output).unwrap();
        let output = output.axis_iter_mut(Axis(1)).into_par_iter();
        let input = input.as_slice();
        let input = ArrayView::from_shape((to_add, count), &input).unwrap();
        let input = input.axis_iter(Axis(1)).into_par_iter();
        output.zip(input).for_each(|(mut output, input)| {
            let mut sum = Self::ExtElem::ZERO;
            for i in input {
                sum += *i;
            }
            for i in 0..Self::ExtElem::EXT_SIZE {
                output[i] = sum.subelems()[i]
            }
        });
    }

    fn eltwise_copy_elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
    ) {
        let count = output.size();
        assert_eq!(count, input.size());
        let mut output = output.as_slice_mut();
        let input = input.as_slice();
        (&mut output[..], &input[..])
            .into_par_iter()
            .for_each(|(output, input)| {
                *output = *input;
            });
    }

    fn eltwise_zeroize_elem(&self, elems: &Self::Buffer<Self::Elem>) {
        elems.as_slice_mut().par_iter_mut().for_each(|elem| {
            *elem = elem.valid_or_zero();
        });
    }

    fn fri_fold(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
        mix: &Self::ExtElem,
    ) {
        let count = output.size() / Self::ExtElem::EXT_SIZE;
        assert_eq!(output.size(), count * Self::ExtElem::EXT_SIZE);
        assert_eq!(input.size(), output.size() * FRI_FOLD);
        let mut output = output.as_slice_mut();
        let input = input.as_slice();

        // TODO(flaub): parallelize
        for idx in 0..count {
            let mut tot = Self::ExtElem::ZERO;
            let mut cur_mix = Self::ExtElem::ONE;
            for i in 0..FRI_FOLD {
                let rev_i = bit_rev_32(i as u32) >> (32 - log2_ceil(FRI_FOLD));
                let rev_idx = rev_i as usize * count + idx;
                let factor = Self::ExtElem::from_subelems(
                    (0..Self::ExtElem::EXT_SIZE).map(|i| input[i * count * FRI_FOLD + rev_idx]),
                );
                tot += cur_mix * factor;
                cur_mix *= *mix;
            }
            for i in 0..Self::ExtElem::EXT_SIZE {
                output[count * i + idx] = tot.subelems()[i];
            }
        }
    }

    fn hash_rows(&self, output: &Self::Buffer<Digest>, matrix: &Self::Buffer<Self::Elem>) {
        let row_size = output.size();
        let col_size = matrix.size() / output.size();
        assert_eq!(matrix.size(), col_size * row_size);
        let mut output = output.as_slice_mut();
        let matrix = &*matrix.as_slice();
        let hashfn = self.suite.hashfn.as_ref();
        output.par_iter_mut().enumerate().for_each(|(idx, output)| {
            let column: Vec<Self::Elem> =
                (0..col_size).map(|i| matrix[i * row_size + idx]).collect();
            *output = *hashfn.hash_elem_slice(column.as_slice());
        });
    }

    fn hash_fold(&self, io: &Self::Buffer<Digest>, input_size: usize, output_size: usize) {
        assert!(io.size() >= 2 * input_size);
        assert_eq!(input_size, 2 * output_size);
        let io = io.as_slice_sync();
        let output = io.slice(output_size, output_size);
        let input = io.slice(input_size, input_size);
        let hashfn = self.suite.hashfn.as_ref();
        (0..output.size()).into_par_iter().for_each(|idx| {
            let in1 = input.get(2 * idx);
            let in2 = input.get(2 * idx + 1);
            output.set(idx, *hashfn.hash_pair(&in1, &in2));
        });
    }

    fn gather_sample(
        &self,
        dst: &Self::Buffer<Self::Elem>,
        src: &Self::Buffer<Self::Elem>,
        idx: usize,
        size: usize,
        stride: usize,
    ) {
        let src = src.as_slice();
        let mut dst = dst.as_slice_mut();
        for gid in 0..size {
            dst[gid] = src[gid * stride + idx];
        }
    }

    fn scatter(
        &self,
        into: &Self::Buffer<Self::Elem>,
        index: &[u32],
        offsets: &[u32],
        values: &[Self::Elem],
    ) {
        if index.is_empty() {
            return;
        }

        let mut into = into.as_slice_mut();
        for cycle in 0..index.len() - 1 {
            for idx in index[cycle]..index[cycle + 1] {
                into[offsets[idx as usize] as usize] = values[idx as usize];
            }
        }
    }

    fn eltwise_copy_elem_slice(
        &self,
        into: &Self::Buffer<Self::Elem>,
        from: &[Self::Elem],
        from_rows: usize,
        from_cols: usize,
        from_offset: usize,
        from_stride: usize,
        into_offset: usize,
        into_stride: usize,
    ) {
        let mut into = into.as_slice_mut();
        for row in 0..from_rows {
            for col in 0..from_cols {
                into[into_offset + row * into_stride + col] =
                    from[from_offset + row * from_stride + col];
            }
        }
    }

    fn prefix_products(&self, io: &Self::Buffer<Self::ExtElem>) {
        let mut io = io.as_slice_mut();
        for i in 1..io.len() {
            io[i] = io[i] * io[i - 1];
        }
    }

    fn has_unified_memory(&self) -> bool {
        true
    }

    fn get_hash_suite(&self) -> &HashSuite<Self::Field> {
        &self.suite
    }
}

#[cfg(test)]
mod tests {
    use hex::FromHex;
    use risc0_core::field::baby_bear::{BabyBear, BabyBearExtElem};

    use super::*;
    use crate::core::hash::sha::Sha256HashSuite;

    #[test]
    #[should_panic]
    fn check_req() {
        let hal: CpuHal<BabyBear> = CpuHal::new(Sha256HashSuite::new_suite());
        let a = hal.alloc_elem("a", 10);
        let b = hal.alloc_elem("b", 20);
        hal.eltwise_add_elem(&a, &b, &b);
    }

    #[test]
    fn fp() {
        let hal: CpuHal<BabyBear> = CpuHal::new(Sha256HashSuite::new_suite());
        const COUNT: usize = 1024 * 1024;
        test_binary(
            &hal,
            |o, a, b| {
                hal.eltwise_add_elem(o, a, b);
            },
            |a, b| *a + *b,
            COUNT,
        );
    }

    fn test_binary<H, HF, CF>(hal: &H, hal_fn: HF, cpu_fn: CF, count: usize)
    where
        H: Hal,
        HF: Fn(&H::Buffer<H::Elem>, &H::Buffer<H::Elem>, &H::Buffer<H::Elem>),
        CF: Fn(&H::Elem, &H::Elem) -> H::Elem,
    {
        let a = hal.alloc_elem("a", count);
        let b = hal.alloc_elem("b", count);
        let o = hal.alloc_elem("o", count);
        let mut golden = Vec::with_capacity(count);
        let mut rng = rand::rng();
        a.view_mut(|a| {
            b.view_mut(|b| {
                for i in 0..count {
                    a[i] = H::Elem::random(&mut rng);
                    b[i] = H::Elem::random(&mut rng);
                }
                for i in 0..count {
                    golden.push(cpu_fn(&a[i], &b[i]));
                }
            });
        });
        hal_fn(&o, &a, &b);
        o.view(|o| {
            assert_eq!(o, &golden[..]);
        });
    }

    fn do_hash_rows(rows: usize, cols: usize, expected: &[&str]) {
        let hal: CpuHal<BabyBear> = CpuHal::new(Sha256HashSuite::new_suite());
        let matrix_size = rows * cols;
        let matrix = hal.alloc_elem("matrix", matrix_size);
        let output = hal.alloc_digest("output", rows);
        hal.hash_rows(&output, &matrix);
        output.view(|view| {
            assert_eq!(expected.len(), view.len());
            for (expected, actual) in expected.iter().zip(view) {
                assert_eq!(Digest::from_hex(expected).unwrap(), *actual);
            }
        });
    }

    #[test]
    fn hash_rows() {
        do_hash_rows(
            1,
            16,
            &["da5698be17b9b46962335799779fbeca8ce5d491c0d26243bafef9ea1837a9d8"],
        );
    }

    #[test]
    fn prefix_products() {
        let hal: CpuHal<BabyBear> = CpuHal::new(Sha256HashSuite::new_suite());
        let io = vec![BabyBearExtElem::from_u32(2); 4];
        let io = hal.copy_from_extelem("io", &io);
        hal.prefix_products(&io);

        let io: Vec<_> = io.as_slice().iter().cloned().collect();

        assert_eq!(
            &io,
            &[
                BabyBearExtElem::from_u32(2),
                BabyBearExtElem::from_u32(4),
                BabyBearExtElem::from_u32(8),
                BabyBearExtElem::from_u32(16),
            ]
        );
    }
}
