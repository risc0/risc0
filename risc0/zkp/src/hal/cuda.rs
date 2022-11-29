// Copyright 2022 Risc0, Inc.

use std::{cell::RefCell, ffi::CString, marker::PhantomData, rc::Rc};

use bytemuck::Pod;
use fil_rustacuda as rustacuda;
use rustacuda::{
    device::DeviceAttribute,
    function::{BlockSize, GridSize},
    launch,
    prelude::*,
};
use rustacuda_core::UnifiedPointer;

use crate::{
    core::{log2_ceil, sha::Digest},
    field::{
        baby_bear::{BabyBearElem, BabyBearExtElem},
        Elem, ExtElem, RootsOfUnity,
    },
    hal::{Buffer, Hal},
    FRI_FOLD,
};

const KERNELS_FATBIN: &[u8] = include_bytes!(concat!(env!("OUT_DIR"), "/kernels.fatbin"));

pub struct CudaHal {
    pub max_threads: u32,
    pub module: Module,
    // This is marked ManuallyDrop because otherwise we get errors like
    // 'Failed to unload CUDA module: ContextIsDestroyed'
    _context: core::mem::ManuallyDrop<Context>,
}

struct RawBuffer {
    name: &'static str,
    buf: UnifiedBuffer<u8>,
}

impl RawBuffer {
    pub fn new(name: &'static str, size: usize) -> Self {
        log::debug!("alloc: {size} bytes, {name}");
        Self {
            name,
            buf: unsafe { UnifiedBuffer::uninitialized(size).unwrap() },
        }
    }
}

impl Drop for RawBuffer {
    fn drop(&mut self) {
        log::debug!("free: {} bytes, {}", self.buf.len(), self.name);
    }
}

#[derive(Clone)]
pub struct BufferImpl<T> {
    buffer: Rc<RefCell<RawBuffer>>,
    size: usize,
    offset: usize,
    marker: PhantomData<T>,
}

impl<T: Pod> BufferImpl<T> {
    fn new(name: &'static str, size: usize) -> Self {
        let bytes_len = std::mem::size_of::<T>() * size;
        assert!(bytes_len > 0);
        BufferImpl {
            buffer: Rc::new(RefCell::new(RawBuffer::new(name, bytes_len))),
            size,
            offset: 0,
            marker: PhantomData,
        }
    }

    pub fn copy_from(name: &'static str, slice: &[T]) -> Self {
        let bytes_len = std::mem::size_of::<T>() * slice.len();
        assert!(bytes_len > 0);
        let mut buffer = RawBuffer::new(name, bytes_len);
        let bytes = bytemuck::cast_slice(slice);
        buffer.buf.copy_from_slice(bytes);
        BufferImpl {
            buffer: Rc::new(RefCell::new(buffer)),
            size: slice.len(),
            offset: 0,
            marker: PhantomData,
        }
    }

    pub fn as_device_ptr(&self) -> UnifiedPointer<u8> {
        let ptr = self.buffer.borrow_mut().buf.as_unified_ptr();
        let offset = self.offset * std::mem::size_of::<T>();
        unsafe { ptr.offset(offset.try_into().unwrap()) }
    }

    pub fn as_device_ptr_with_offset(&self, offset: usize) -> UnifiedPointer<u8> {
        let ptr = self.buffer.borrow_mut().buf.as_unified_ptr();
        let offset = (self.offset + offset) * std::mem::size_of::<T>();
        unsafe { ptr.offset(offset.try_into().unwrap()) }
    }
}

impl<T: Pod> Buffer<T> for BufferImpl<T> {
    fn size(&self) -> usize {
        self.size
    }

    fn slice(&self, offset: usize, size: usize) -> BufferImpl<T> {
        assert!(offset + size <= self.size());
        BufferImpl {
            buffer: self.buffer.clone(),
            size,
            offset: self.offset + offset,
            marker: PhantomData,
        }
    }

    fn view<F: FnOnce(&[T])>(&self, f: F) {
        let buf = self.buffer.borrow_mut();
        let slice = bytemuck::cast_slice(&buf.buf);
        f(&slice[self.offset..]);
    }

    fn view_mut<F: FnOnce(&mut [T])>(&self, f: F) {
        let mut buf = self.buffer.borrow_mut();
        let slice = bytemuck::cast_slice_mut(&mut buf.buf);
        f(&mut slice[self.offset..]);
    }
}

impl CudaHal {
    #[tracing::instrument(name = "CudaHal::new", skip_all)]
    pub fn new() -> Self {
        rustacuda::init(CudaFlags::empty()).unwrap();
        let device = Device::get_device(0).unwrap();
        let max_threads = device
            .get_attribute(DeviceAttribute::MaxThreadsPerBlock)
            .unwrap();
        let context = Context::create_and_push(ContextFlags::SCHED_AUTO, device).unwrap();
        let module = Module::load_from_bytes(KERNELS_FATBIN).unwrap();
        Self {
            max_threads: max_threads as u32,
            module,
            _context: core::mem::ManuallyDrop::new(context),
        }
    }

    pub fn compute_simple_params(&self, count: usize) -> (GridSize, BlockSize) {
        let count: u32 = count.try_into().unwrap();
        let block = self.max_threads / 4;
        let grid = div_ceil(count, block);
        (GridSize::x(grid), BlockSize::x(block))
    }

    pub fn compute_launch_params(
        &self,
        n_bits: u32,
        s_bits: u32,
        c_size: u32,
    ) -> (GridSize, BlockSize) {
        let s_size = 1 << (s_bits - 1);
        let g_size = 1 << (n_bits - s_bits);

        let mut grid = GridSize::xyz(1, 1, 1);
        let mut block = BlockSize::xyz(1, 1, 1);

        let mut threads = 128;
        // First thread over S
        block.x = threads.min(s_size);
        threads /= block.x;
        // Next thread over G
        block.y = threads.min(g_size);
        // Don't bother threading over C
        let mut grids = 32;
        // First grid over S
        grid.x = grids.min(s_size / block.x);
        grids /= grid.x;
        // Next grid over G
        grid.y = grids.min(g_size / block.y);
        grids /= grid.y;
        // Next grid over C
        grid.z = grids.min(c_size);
        (grid, block)
    }
}

#[allow(unused_variables)]
impl Hal for CudaHal {
    type Elem = BabyBearElem;
    type ExtElem = BabyBearExtElem;

    type BufferDigest = BufferImpl<Digest>;
    type BufferElem = BufferImpl<Self::Elem>;
    type BufferExtElem = BufferImpl<Self::ExtElem>;
    type BufferU32 = BufferImpl<u32>;

    fn alloc_elem(&self, name: &'static str, size: usize) -> Self::BufferElem {
        BufferImpl::new(name, size)
    }

    fn copy_from_elem(&self, name: &'static str, slice: &[Self::Elem]) -> Self::BufferElem {
        BufferImpl::copy_from(name, slice)
    }

    fn alloc_extelem(&self, name: &'static str, size: usize) -> Self::BufferExtElem {
        BufferImpl::new(name, size)
    }

    fn copy_from_extelem(
        &self,
        name: &'static str,
        slice: &[Self::ExtElem],
    ) -> Self::BufferExtElem {
        BufferImpl::copy_from(name, slice)
    }

    fn alloc_digest(&self, name: &'static str, size: usize) -> Self::BufferDigest {
        BufferImpl::new(name, size)
    }

    fn copy_from_digest(&self, name: &'static str, slice: &[Digest]) -> Self::BufferDigest {
        BufferImpl::copy_from(name, slice)
    }

    fn alloc_u32(&self, name: &'static str, size: usize) -> Self::BufferU32 {
        BufferImpl::new(name, size)
    }

    fn copy_from_u32(&self, name: &'static str, slice: &[u32]) -> Self::BufferU32 {
        BufferImpl::copy_from(name, slice)
    }

    #[tracing::instrument(skip_all)]
    fn batch_expand(&self, output: &Self::BufferElem, input: &Self::BufferElem, poly_count: usize) {
        let out_size = output.size() / poly_count;
        let in_size = input.size() / poly_count;
        let expand_bits = log2_ceil(out_size / in_size);
        assert_eq!(output.size(), out_size * poly_count);
        assert_eq!(input.size(), in_size * poly_count);
        assert_eq!(out_size, in_size * (1 << expand_bits));

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();
        let kernel_name = CString::new("batch_expand").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        let params = self.compute_simple_params(out_size.try_into().unwrap());
        unsafe {
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                output.as_device_ptr(),
                input.as_device_ptr(),
                poly_count as u32,
                out_size as u32,
                in_size as u32,
                expand_bits as u32
            ))
            .unwrap();
        }
        stream.synchronize().unwrap();
    }

    #[tracing::instrument(skip_all)]
    fn batch_evaluate_ntt(&self, io: &Self::BufferElem, count: usize, expand_bits: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        let n_bits = log2_ceil(row_size);
        assert_eq!(row_size, 1 << n_bits);
        assert!(n_bits >= expand_bits);
        assert!(n_bits < Self::Elem::MAX_ROU_PO2);
        let rou = self.copy_from_elem("rou", Self::Elem::ROU_FWD);

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();
        let kernel_name = CString::new("multi_ntt_fwd_step").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        for s_bits in 1 + expand_bits..=n_bits {
            let params = self.compute_launch_params(n_bits as u32, s_bits as u32, count as u32);
            unsafe {
                launch!(kernel<<<params.0, params.1, 0, stream>>>(
                    io.as_device_ptr(),
                    rou.as_device_ptr(),
                    n_bits as u32,
                    s_bits as u32,
                    count as u32
                ))
                .unwrap();
            }
            stream.synchronize().unwrap();
        }
    }

    #[tracing::instrument(skip_all)]
    fn batch_interpolate_ntt(&self, io: &Self::BufferElem, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        let n_bits = log2_ceil(row_size);
        assert_eq!(row_size, 1 << n_bits);
        assert!(n_bits < Self::Elem::MAX_ROU_PO2);
        let rou = self.copy_from_elem("rou", Self::Elem::ROU_REV);

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();
        let kernel_name = CString::new("multi_ntt_rev_step").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        for s_bits in (1..=n_bits).rev() {
            let params = self.compute_launch_params(n_bits as u32, s_bits as u32, count as u32);
            unsafe {
                launch!(kernel<<<params.0, params.1, 0, stream>>>(
                    io.as_device_ptr(),
                    rou.as_device_ptr(),
                    n_bits as u32,
                    s_bits as u32,
                    count as u32
                ))
                .unwrap();
            }
            stream.synchronize().unwrap();
        }

        let io_size = io.size().try_into().unwrap();
        let params = self.compute_simple_params(io_size);
        let kernel_name = CString::new("eltwise_mul_factor_fp").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        let norm = self.copy_from_elem("norm", &[Self::Elem::new(row_size as u32).inv()]);
        unsafe {
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                io.as_device_ptr(),
                norm.as_device_ptr(),
                io_size
            ))
            .unwrap();
        }
        stream.synchronize().unwrap();
    }

    #[tracing::instrument(skip_all)]
    fn batch_bit_reverse(&self, io: &Self::BufferElem, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        let bits = log2_ceil(row_size);
        assert_eq!(row_size, 1 << bits);
        let io_size = io.size();

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();
        let kernel_name = CString::new("multi_bit_reverse").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        let params = self.compute_simple_params(io_size);
        unsafe {
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                io.as_device_ptr(),
                bits,
                io_size
            ))
            .unwrap();
        }
        stream.synchronize().unwrap();
    }

    #[tracing::instrument(skip_all)]
    fn batch_evaluate_any(
        &self,
        coeffs: &Self::BufferElem,
        poly_count: usize,
        which: &Self::BufferU32,
        xs: &Self::BufferExtElem,
        out: &Self::BufferExtElem,
    ) {
        let po2 = log2_ceil(coeffs.size() / poly_count);
        assert_eq!(poly_count * (1 << po2), coeffs.size());
        let eval_count = which.size();
        assert_eq!(xs.size(), eval_count);
        assert_eq!(out.size(), eval_count);
        let count = 1 << po2;

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();
        let kernel_name = CString::new("batch_evaluate_any").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        let params = self.compute_simple_params(eval_count);
        unsafe {
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                out.as_device_ptr(),
                coeffs.as_device_ptr(),
                which.as_device_ptr(),
                xs.as_device_ptr(),
                count,
                eval_count
            ))
            .unwrap();
        }
        stream.synchronize().unwrap();
    }

    #[tracing::instrument(skip_all)]
    fn zk_shift(&self, io: &Self::BufferElem, poly_count: usize) {
        let bits = log2_ceil(io.size() / poly_count);
        let count = io.size();
        assert_eq!(io.size(), poly_count * (1 << bits));

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();
        let kernel_name = CString::new("zk_shift").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        let params = self.compute_simple_params(count);
        unsafe {
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                io.as_device_ptr(),
                bits,
                count
            ))
            .unwrap();
        }
        stream.synchronize().unwrap();
    }

    #[tracing::instrument(skip_all)]
    fn mix_poly_coeffs(
        &self,
        output: &Self::BufferExtElem,
        mix_start: &Self::ExtElem,
        mix: &Self::ExtElem,
        input: &Self::BufferElem,
        combos: &Self::BufferU32,
        input_size: usize,
        count: usize,
    ) {
        let mix_start = self.copy_from_extelem("mix_start", &[*mix_start]);
        let mix = self.copy_from_extelem("mix", &[*mix]);

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();
        let kernel_name = CString::new("mix_poly_coeffs").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        let params = self.compute_simple_params(count);
        unsafe {
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                output.as_device_ptr(),
                input.as_device_ptr(),
                combos.as_device_ptr(),
                mix_start.as_device_ptr(),
                mix.as_device_ptr(),
                input_size,
                count
            ))
            .unwrap();
        }
        stream.synchronize().unwrap();
    }

    #[tracing::instrument(skip_all)]
    fn eltwise_add_elem(
        &self,
        output: &Self::BufferElem,
        input1: &Self::BufferElem,
        input2: &Self::BufferElem,
    ) {
        assert_eq!(output.size(), input1.size());
        assert_eq!(output.size(), input2.size());
        let count = output.size();

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();
        let kernel_name = CString::new("eltwise_add_fp").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        let params = self.compute_simple_params(count);
        unsafe {
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                output.as_device_ptr(),
                input1.as_device_ptr(),
                input2.as_device_ptr(),
                count
            ))
            .unwrap();
        }
        stream.synchronize().unwrap();
    }

    #[tracing::instrument(skip_all)]
    fn eltwise_sum_extelem(&self, output: &Self::BufferElem, input: &Self::BufferExtElem) {
        let count = output.size() / Self::ExtElem::EXT_SIZE;
        let to_add = input.size() / count;
        assert_eq!(output.size(), count * Self::ExtElem::EXT_SIZE);
        assert_eq!(input.size(), count * to_add);

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();
        let kernel_name = CString::new("eltwise_sum_fp4").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        let params = self.compute_simple_params(output.size());
        unsafe {
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                output.as_device_ptr(),
                input.as_device_ptr(),
                to_add,
                count
            ))
            .unwrap();
        }
        stream.synchronize().unwrap();
    }

    #[tracing::instrument(skip_all)]
    fn eltwise_copy_elem(&self, output: &Self::BufferElem, input: &Self::BufferElem) {
        let count = output.size();
        assert_eq!(count, input.size());

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();
        let kernel_name = CString::new("eltwise_copy_fp").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        let params = self.compute_simple_params(count);
        unsafe {
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                output.as_device_ptr(),
                input.as_device_ptr(),
                count
            ))
            .unwrap();
        }
        stream.synchronize().unwrap();
    }

    #[tracing::instrument(skip_all)]
    fn fri_fold(&self, output: &Self::BufferElem, input: &Self::BufferElem, mix: &Self::ExtElem) {
        let count = output.size() / Self::ExtElem::EXT_SIZE;
        assert_eq!(output.size(), count * Self::ExtElem::EXT_SIZE);
        assert_eq!(input.size(), output.size() * FRI_FOLD);
        let mix = self.copy_from_extelem("mix", &[*mix]);

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();
        let kernel_name = CString::new("fri_fold").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        let params = self.compute_simple_params(count);
        unsafe {
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                output.as_device_ptr(),
                input.as_device_ptr(),
                mix.as_device_ptr(),
                count
            ))
            .unwrap();
        }
        stream.synchronize().unwrap();
    }

    #[tracing::instrument(skip_all)]
    fn sha_rows(&self, output: &Self::BufferDigest, matrix: &Self::BufferElem) {
        let row_size = output.size();
        let col_size = matrix.size() / output.size();
        assert_eq!(matrix.size(), col_size * row_size);

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();
        let kernel_name = CString::new("sha_rows").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        let params = self.compute_simple_params(row_size);
        unsafe {
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                output.as_device_ptr(),
                matrix.as_device_ptr(),
                row_size,
                col_size
            ))
            .unwrap();
        }
        stream.synchronize().unwrap();
    }

    fn sha_fold(&self, io: &Self::BufferDigest, input_size: usize, output_size: usize) {
        assert_eq!(input_size, 2 * output_size);

        let stream = Stream::new(StreamFlags::DEFAULT, None).unwrap();
        let kernel_name = CString::new("sha_fold").unwrap();
        let kernel = self.module.get_function(&kernel_name).unwrap();
        let params = self.compute_simple_params(input_size);
        unsafe {
            // DevicePointers require that the underlying type of the pointer implements the
            // DeviceCopy trait. core::Digest does not implement this trait.
            // TODO: refactor data types to allow safer copying.
            // Here, we perform pointer arithmetic on the underlying device_pointer of type
            // u8.
            // TODO: modify type hierarchy to fit Rustacuda's memory model
            // to allow for more type safe pointer arithmetic
            let input = io.as_device_ptr_with_offset(input_size);
            let output = io.as_device_ptr_with_offset(output_size);
            launch!(kernel<<<params.0, params.1, 0, stream>>>(
                output,
                input,
                output_size
            ))
            .unwrap();
        }
        stream.synchronize().unwrap();
    }
}

fn div_ceil(a: u32, b: u32) -> u32 {
    (a.checked_add(b).unwrap() - 1) / b
}

#[cfg(test)]
mod tests {
    use serial_test::serial;
    use test_log::test;

    use super::CudaHal;
    use crate::hal::testutil;

    #[test]
    #[should_panic]
    fn check_req() {
        testutil::check_req(CudaHal::new());
    }

    #[test]
    #[serial]
    fn eltwise_add_elem() {
        testutil::eltwise_add_elem(CudaHal::new());
    }

    #[test]
    #[serial]
    fn eltwise_copy_elem() {
        testutil::eltwise_copy_elem(CudaHal::new());
    }

    #[test]
    #[serial]
    fn eltwise_sum_extelem() {
        testutil::eltwise_sum_extelem(CudaHal::new());
    }

    #[test]
    #[serial]
    fn sha_rows() {
        testutil::sha_rows(CudaHal::new());
    }

    #[test]
    #[serial]
    fn sha_fold() {
        testutil::sha_fold(CudaHal::new());
    }

    #[test]
    #[serial]
    fn fri_fold() {
        testutil::fri_fold(CudaHal::new());
    }

    #[test]
    #[serial]
    fn batch_expand() {
        testutil::batch_expand(CudaHal::new());
    }

    #[test]
    #[serial]
    fn batch_evaluate_ntt() {
        testutil::batch_evaluate_ntt(CudaHal::new());
    }

    #[test]
    #[serial]
    fn batch_interpolate_ntt() {
        testutil::batch_interpolate_ntt(CudaHal::new());
    }

    #[test]
    #[serial]
    fn batch_bit_reverse() {
        testutil::batch_bit_reverse(CudaHal::new());
    }

    #[test]
    #[serial]
    fn batch_evaluate_any() {
        testutil::batch_evaluate_any(CudaHal::new());
    }

    #[test]
    #[serial]
    fn zk_shift() {
        testutil::zk_shift(CudaHal::new());
    }

    #[test]
    #[serial]
    fn mix_poly_coeffs() {
        testutil::mix_poly_coeffs(CudaHal::new());
    }
}
