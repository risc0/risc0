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

use std::{
    cell::RefCell,
    fmt::Debug,
    marker::PhantomData,
    rc::Rc,
    sync::{
        atomic::{AtomicUsize, Ordering},
        OnceLock,
    },
};

use anyhow::{bail, Context as _, Result};
use cust::{
    device::DeviceAttribute,
    memory::{DeviceCopy, DevicePointer, GpuBuffer},
    prelude::*,
};
use parking_lot::{ReentrantMutex, ReentrantMutexGuard};
use risc0_core::{
    field::{
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
        Elem, ExtElem, RootsOfUnity,
    },
    scope,
};
use risc0_sys::{cuda::*, ffi_wrap};

use super::{tracker, Buffer, Hal};
use crate::{
    core::{
        digest::Digest,
        hash::{
            poseidon2::Poseidon2HashSuite, poseidon_254::Poseidon254HashSuite,
            sha::Sha256HashSuite, HashSuite,
        },
        log2_ceil,
    },
    FRI_FOLD,
};

// The GPU becomes unstable as the number of concurrent provers grow.
pub fn singleton() -> &'static ReentrantMutex<()> {
    static ONCE: OnceLock<ReentrantMutex<()>> = OnceLock::new();
    ONCE.get_or_init(|| ReentrantMutex::new(()))
}

pub struct PinnedArena {
    pub(crate) base_ptr: *mut u8,
    pub(crate) total_size: usize,
    current_offset: AtomicUsize,
    // Fixed 1GB region reserved for code.merkle.nodes
    code_merkle_nodes_ptr: *mut u8,
    code_merkle_nodes_size: usize,
}

unsafe impl Send for PinnedArena {}
unsafe impl Sync for PinnedArena {}

impl PinnedArena {
    unsafe fn new(size_bytes: usize) -> Result<Self> {
        extern "C" {
            fn cudaMallocHost(ptr: *mut *mut std::ffi::c_void, size: usize) -> i32;
        }

        let mut ptr: *mut std::ffi::c_void = std::ptr::null_mut();
        let result = cudaMallocHost(&mut ptr, size_bytes);
        if result != 0 {
            panic!(
                "FATAL: Failed to allocate {:.2} GB pinned memory arena: CUDA error code {}. Cannot continue execution.",
                size_bytes as f64 / (1024.0 * 1024.0 * 1024.0),
                result
            );
        }

        // Reserve 1GB at the beginning for code.merkle.nodes
        const CODE_MERKLE_NODES_SIZE: usize = 1024 * 1024 * 1024; // 1GB
        let code_merkle_nodes_ptr = ptr as *mut u8;
        let reserved_offset = CODE_MERKLE_NODES_SIZE;

        // Ensure we have enough space for the reserved region
        if size_bytes < reserved_offset {
            bail!("Pinned arena size ({:.2} GB) is too small. Need at least 1GB for code.merkle.nodes reservation.",
                  size_bytes as f64 / (1024.0 * 1024.0 * 1024.0));
        }

        tracing::info!(
            "Pinned memory arena initialized: {:.2} GB at {:p} (1GB reserved for code.merkle.nodes)",
            size_bytes as f64 / (1024.0 * 1024.0 * 1024.0),
            ptr
        );

        Ok(Self {
            base_ptr: ptr as *mut u8,
            total_size: size_bytes,
            current_offset: AtomicUsize::new(reserved_offset), // Start after reserved region
            code_merkle_nodes_ptr,
            code_merkle_nodes_size: CODE_MERKLE_NODES_SIZE,
        })
    }

    /// This method is thread-safe. Multiple threads can call `alloc` concurrently
    /// without memory corruption. However, when the arena wraps around, previous
    /// allocations may be overwritten, so callers must ensure their buffers are
    /// no longer in use before wrap-around occurs.
    fn alloc(&self, size: usize) -> Option<*mut u8> {
        // Align to 256 bytes for optimal PCIe transfer performance
        let aligned_size = (size + 255) & !255;

        // Use a compare-and-swap loop to handle wrap-around atomically
        loop {
            let current = self.current_offset.load(Ordering::SeqCst);
            let new_offset = current + aligned_size;

            if new_offset > self.total_size {
                // Arena is full, try to wrap around atomically
                // Wrap around to after the reserved region (code.merkle.nodes)
                let wrap_around_offset = self.code_merkle_nodes_size;
                match self.current_offset.compare_exchange(
                    current,
                    wrap_around_offset + aligned_size,
                    Ordering::SeqCst,
                    Ordering::SeqCst,
                ) {
                    Ok(_) => {
                        // This thread won the race to wrap around
                        tracing::warn!(
                            "Pinned arena full ({}%), wrapping around. Previous allocations may be overwritten.",
                            (current * 100) / self.total_size
                        );
                        // Return pointer after reserved region
                        return unsafe { Some(self.base_ptr.add(wrap_around_offset)) };
                    }
                    Err(_) => {
                        // Another thread already wrapped around, retry with new offset
                        continue;
                    }
                }
            } else {
                // Try to atomically update the offset
                match self.current_offset.compare_exchange(
                    current,
                    new_offset,
                    Ordering::SeqCst,
                    Ordering::SeqCst,
                ) {
                    Ok(_) => {
                        // Successfully allocated at offset 'current'
                        return unsafe { Some(self.base_ptr.add(current)) };
                    }
                    Err(_) => {
                        // Another thread modified current_offset, retry
                        continue;
                    }
                }
            }
        }
    }

    /// Get the fixed memory address for code.merkle.nodes
    /// This always returns the same 1GB region reserved at arena initialization.
    fn alloc_fixed_for_code_merkle_nodes(&self, size: usize) -> Option<*mut u8> {
        if size > self.code_merkle_nodes_size {
            tracing::warn!(
                "Requested size {} bytes exceeds reserved 1GB for code.merkle.nodes",
                size
            );
            return None;
        }
        Some(self.code_merkle_nodes_ptr)
    }

    /// Get current usage statistics
    fn usage(&self) -> (usize, usize, f64) {
        let used = self.current_offset.load(Ordering::SeqCst);
        let percent = (used as f64 / self.total_size as f64) * 100.0;
        (used, self.total_size, percent)
    }
}

impl Drop for PinnedArena {
    fn drop(&mut self) {
        unsafe {
            extern "C" {
                fn cudaFreeHost(ptr: *mut std::ffi::c_void) -> i32;
            }
            let result = cudaFreeHost(self.base_ptr as *mut std::ffi::c_void);
            if result != 0 {
                tracing::error!("Failed to free pinned arena: CUDA error code {}", result);
            } else {
                tracing::info!("Pinned memory arena freed");
            }
        }
    }
}

// Global pinned memory arena singleton
static PINNED_ARENA: OnceLock<PinnedArena> = OnceLock::new();

/// Get or initialize the global pinned memory arena.
pub fn pinned_arena() -> &'static PinnedArena {
    PINNED_ARENA
        .get()
        .expect("Pinned arena not initialized! Call init_pinned_arena() first.")
}

pub fn init_pinned_arena(size_gb: Option<usize>) -> Result<()> {
    let size_gb = size_gb.unwrap_or_else(|| {
        std::env::var("PINNED_ARENA_SIZE_GB")
            .ok()
            .and_then(|s| s.parse().ok())
            .unwrap_or(10) // Default: 10GB
    });

    let size_bytes = size_gb * 1024 * 1024 * 1024;

    tracing::info!(
        "Initializing pinned memory arena: {} GB (this may take 2-3 seconds)...",
        size_gb
    );
    let t_start = std::time::Instant::now();

    let arena = unsafe { PinnedArena::new(size_bytes)? };

    PINNED_ARENA
        .set(arena)
        .map_err(|_| anyhow::anyhow!("Pinned arena already initialized"))?;

    tracing::info!(
        "Pinned arena ready in {:.2}s - subsequent allocations will be <1μs!",
        t_start.elapsed().as_secs_f64()
    );

    Ok(())
}

#[derive(Clone, Copy)]
#[repr(transparent)]
pub struct DeviceElem(pub BabyBearElem);

#[derive(Clone, Copy)]
#[repr(transparent)]
pub struct DeviceExtElem(pub BabyBearExtElem);

unsafe impl DeviceCopy for DeviceExtElem {}

pub trait CudaHash {
    /// Create a hash implementation
    fn new() -> Self
    where
        Self: Sized;

    /// Run the hash_fold function
    fn hash_fold(&self, io: &BufferImpl<Digest>, output_size: usize);

    /// Run the hash_rows function
    fn hash_rows(&self, output: &BufferImpl<Digest>, matrix: &BufferImpl<BabyBearElem>);

    /// Run the hash_rows_interleave function
    #[cfg(all(feature = "low_vram", feature = "cuda"))]
    fn hash_rows_interleave(
        &self,
        output: &BufferImpl<Digest>,
        matrix: &BufferImpl<BabyBearElem>,
        codeword_id: u32,
    );

    /// Return the HashSuite
    fn get_hash_suite(&self) -> &HashSuite<BabyBear>;
}

pub struct CudaHashSha256 {
    suite: HashSuite<BabyBear>,
}

impl CudaHash for CudaHashSha256 {
    fn new() -> Self {
        CudaHashSha256 {
            suite: Sha256HashSuite::new_suite(),
        }
    }

    fn hash_fold(&self, io: &BufferImpl<Digest>, output_size: usize) {
        let input = io.as_device_ptr_with_offset(2 * output_size);
        let output = io.as_device_ptr_with_offset(output_size);

        extern "C" {
            fn risc0_zkp_cuda_sha_fold(
                output: DevicePointer<u8>,
                input: DevicePointer<u8>,
                count: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe { risc0_zkp_cuda_sha_fold(output, input, output_size as u32) }).unwrap();
    }

    fn hash_rows(&self, output: &BufferImpl<Digest>, matrix: &BufferImpl<BabyBearElem>) {
        let row_size = output.size();
        let col_size = matrix.size() / output.size();
        assert_eq!(matrix.size(), col_size * row_size);

        extern "C" {
            fn risc0_zkp_cuda_sha_rows(
                output: DevicePointer<u8>,
                matrix: DevicePointer<u8>,
                row_size: u32,
                col_size: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_sha_rows(
                output.as_device_ptr(),
                matrix.as_device_ptr(),
                row_size as u32,
                col_size as u32,
            )
        })
        .unwrap();
    }

    #[cfg(all(feature = "low_vram", feature = "cuda"))]
    fn hash_rows_interleave(
        &self,
        _output: &BufferImpl<Digest>,
        _matrix: &BufferImpl<BabyBearElem>,
        _codeword_id: u32,
    ) {
        panic!("hash_rows_interleave is not supported for CudaHashSha256");
    }

    fn get_hash_suite(&self) -> &HashSuite<BabyBear> {
        &self.suite
    }
}

pub struct CudaHashPoseidon2 {
    suite: HashSuite<BabyBear>,
}

impl CudaHash for CudaHashPoseidon2 {
    fn new() -> Self {
        CudaHashPoseidon2 {
            suite: Poseidon2HashSuite::new_suite(),
        }
    }

    fn hash_fold(&self, io: &BufferImpl<Digest>, output_size: usize) {
        let err = unsafe {
            let input = io.as_device_ptr_with_offset(2 * output_size);
            let output = io.as_device_ptr_with_offset(output_size);
            sppark_poseidon2_fold(output, input, output_size)
        };
        if err.code != 0 {
            panic!("Failure during hash_fold: {err}");
        }
    }

    fn hash_rows(&self, output: &BufferImpl<Digest>, matrix: &BufferImpl<BabyBearElem>) {
        let row_size = output.size();
        let col_size = matrix.size() / output.size();
        assert_eq!(matrix.size(), col_size * row_size);

        let err = unsafe {
            sppark_poseidon2_rows(
                output.as_device_ptr(),
                matrix.as_device_ptr(),
                row_size.try_into().unwrap(),
                col_size.try_into().unwrap(),
            )
        };
        if err.code != 0 {
            panic!("Failure during hash_rows: {err}");
        }
    }

    #[cfg(all(feature = "low_vram", feature = "cuda"))]
    fn hash_rows_interleave(
        &self,
        output: &BufferImpl<Digest>,
        matrix: &BufferImpl<BabyBearElem>,
        codeword_id: u32,
    ) {
        let row_size = output.size() / 4;
        let col_size = matrix.size() / row_size;
        assert_eq!(matrix.size(), col_size * row_size);

        let err = unsafe {
            sppark_poseidon2_rows_interleave(
                output.as_device_ptr(),
                matrix.as_device_ptr(),
                row_size.try_into().unwrap(),
                col_size.try_into().unwrap(),
                codeword_id,
            )
        };
        if err.code != 0 {
            panic!("Failure during hash_rows: {err}");
        }
    }

    fn get_hash_suite(&self) -> &HashSuite<BabyBear> {
        &self.suite
    }
}

pub struct CudaHashPoseidon254 {
    suite: HashSuite<BabyBear>,
}

impl CudaHash for CudaHashPoseidon254 {
    fn new() -> Self {
        CudaHashPoseidon254 {
            suite: Poseidon254HashSuite::new_suite(),
        }
    }

    fn hash_fold(&self, io: &BufferImpl<Digest>, output_size: usize) {
        let err = unsafe {
            let input = io.as_device_ptr_with_offset(2 * output_size);
            let output = io.as_device_ptr_with_offset(output_size);
            sppark_poseidon254_fold(output, input, output_size)
        };
        if err.code != 0 {
            panic!("Failure during hash_fold: {err}");
        }
    }

    fn hash_rows(&self, output: &BufferImpl<Digest>, matrix: &BufferImpl<BabyBearElem>) {
        let row_size = output.size();
        let col_size = matrix.size() / output.size();
        assert_eq!(matrix.size(), col_size * row_size);

        let err = unsafe {
            sppark_poseidon254_rows(
                output.as_device_ptr(),
                matrix.as_device_ptr(),
                row_size,
                col_size.try_into().unwrap(),
            )
        };
        if err.code != 0 {
            panic!("Failure during hash_rows 254: {err}");
        }
    }

    #[cfg(all(feature = "low_vram", feature = "cuda"))]
    fn hash_rows_interleave(
        &self,
        _output: &BufferImpl<Digest>,
        _matrix: &BufferImpl<BabyBearElem>,
        _codeword_id: u32,
    ) {
        panic!("hash_rows_interleave is not supported for CudaHashPoseidon254");
    }

    fn get_hash_suite(&self) -> &HashSuite<BabyBear> {
        &self.suite
    }
}

pub struct CudaHal<Hash: CudaHash + ?Sized> {
    pub max_threads: u32,
    hash: Option<Box<Hash>>,
    _context: Context,
    _lock: ReentrantMutexGuard<'static, ()>,
}

pub type CudaHalSha256 = CudaHal<CudaHashSha256>;
pub type CudaHalPoseidon2 = CudaHal<CudaHashPoseidon2>;
pub type CudaHalPoseidon254 = CudaHal<CudaHashPoseidon254>;

enum BufferStorage {
    Device(DeviceBuffer<u8>),
    Host(TrackedLockedBuffer),
}

struct RawBuffer {
    name: &'static str,
    storage: BufferStorage,
}

/// A wrapper for page-locked (pinned) host memory allocated via `cudaMallocHost`.
/// The memory is uninitialized and suitable for asynchronous device-to-host transfers.
pub struct TrackedLockedBuffer {
    name: &'static str,
    ptr: *mut u8,
    size: usize,
}

impl RawBuffer {
    pub fn new(name: &'static str, size: usize) -> Self {
        tracing::trace!("alloc: {size} bytes, {name}");
        tracker().lock().unwrap().alloc(size);
        let buf = unsafe { DeviceBuffer::uninitialized(size) }
            .context(format!("allocation failed on {name}: {size} bytes"))
            .unwrap();
        Self {
            name,
            storage: BufferStorage::Device(buf),
        }
    }

    pub fn from_tracked_locked_buffer(name: &'static str, host_buf: TrackedLockedBuffer) -> Self {
        Self {
            name,
            storage: BufferStorage::Host(host_buf),
        }
    }

    pub fn set_u32(&mut self, value: u32) {
        match &mut self.storage {
            BufferStorage::Device(buf) => {
                buf.set_32(value).unwrap();
            }
            BufferStorage::Host(_) => {
                panic!("set_u32 not supported for host storage");
            }
        }
    }

    pub fn as_device_ptr(&self) -> DevicePointer<u8> {
        match &self.storage {
            BufferStorage::Device(buf) => buf.as_device_ptr(),
            BufferStorage::Host(_) => {
                panic!("as_device_ptr() not supported for host storage");
            }
        }
    }

    pub fn as_host_ptr(&self) -> Option<*mut u8> {
        match &self.storage {
            BufferStorage::Device(_) => None,
            BufferStorage::Host(host_buf) => Some(host_buf.as_raw_ptr()),
        }
    }

    pub fn len(&self) -> usize {
        match &self.storage {
            BufferStorage::Device(buf) => buf.len(),
            BufferStorage::Host(host_buf) => host_buf.len(),
        }
    }

    pub fn as_host_vec(&mut self) -> Result<Vec<u8>> {
        match &mut self.storage {
            BufferStorage::Device(buf) => buf.as_host_vec().map_err(|e| anyhow::anyhow!("{}", e)),
            BufferStorage::Host(host_buf) => {
                // For host storage, directly read from pinned memory
                let size = host_buf.len();
                let ptr = host_buf.as_raw_ptr();
                let slice = unsafe { std::slice::from_raw_parts(ptr, size) };
                Ok(slice.to_vec())
            }
        }
    }

    pub fn copy_from(&mut self, src: &[u8]) -> Result<()> {
        match &mut self.storage {
            BufferStorage::Device(buf) => buf.copy_from(src).map_err(|e| anyhow::anyhow!("{}", e)),
            BufferStorage::Host(_) => {
                bail!("copy_from() not supported for host storage");
            }
        }
    }
}

impl Drop for RawBuffer {
    fn drop(&mut self) {
        let size = self.len();
        tracing::trace!("free: {} bytes, {}", size, self.name);
        tracker().lock().unwrap().free(size);
        // TrackedLockedBuffer will handle its own cleanup
    }
}

impl TrackedLockedBuffer {
    pub fn new(name: &'static str, size: usize) -> Result<Self> {
        tracing::trace!("alloc_locked_host_from_arena: {size} bytes, {name}");
        tracker().lock().unwrap().alloc(size);

        // Allocate from global pinned arena (fast: <1μs instead of 90-130ms!)
        let arena = pinned_arena();

        // Use fixed 1GB region for code.merkle.nodes
        let ptr = if name == "code.merkle.nodes" {
            arena.alloc_fixed_for_code_merkle_nodes(size).ok_or_else(|| {
                anyhow::anyhow!("Failed to allocate fixed memory for code.merkle.nodes: requested {} bytes exceeds 1GB limit", size)
            })?
        } else {
            arena.alloc(size).ok_or_else(|| {
                anyhow::anyhow!(
                    "Pinned arena exhausted! Requested {} bytes, arena usage: {:.1}%",
                    size,
                    arena.usage().2
                )
            })?
        };

        if name == "code.merkle.nodes" {
            tracing::trace!(
                "Allocated {} bytes from fixed code.merkle.nodes region at offset {} (always same address)",
                size,
                (ptr as usize) - (arena.base_ptr as usize)
            );
        } else {
            tracing::trace!(
                "Allocated {} bytes from arena at offset {} ({:.1}% used)",
                size,
                (ptr as usize) - (arena.base_ptr as usize),
                arena.usage().2
            );
        }

        // Memory is uninitialized - perfect for async memcpy from device
        Ok(Self { name, ptr, size })
    }

    pub fn as_raw_ptr(&self) -> *mut u8 {
        self.ptr
    }

    /// Get the size in bytes
    pub fn len(&self) -> usize {
        self.size
    }

    pub fn is_empty(&self) -> bool {
        self.size == 0
    }
}

impl Drop for TrackedLockedBuffer {
    fn drop(&mut self) {
        tracing::trace!(
            "release_locked_host_to_arena: {} bytes, {}",
            self.size,
            self.name
        );

        // Memory belongs to the global arena, no need to call cudaFreeHost.
        // The arena will reuse this memory when it wraps around.
        // Just update the tracker for accounting purposes.
        tracker().lock().unwrap().free(self.size);
    }
}

#[derive(Clone)]
pub struct BufferImpl<T> {
    buffer: Rc<RefCell<RawBuffer>>,
    size: usize,
    offset: usize,
    marker: PhantomData<T>,
}

#[inline]
fn unchecked_cast<A, B>(a: &[A]) -> &[B] {
    let new_len = std::mem::size_of_val(a) / std::mem::size_of::<B>();
    unsafe { std::slice::from_raw_parts(a.as_ptr() as *const B, new_len) }
}

#[inline]
fn unchecked_cast_mut<A, B>(a: &mut [A]) -> &mut [B] {
    let new_len = std::mem::size_of_val(a) / std::mem::size_of::<B>();
    unsafe { std::slice::from_raw_parts_mut(a.as_mut_ptr() as *mut B, new_len) }
}

impl<T> BufferImpl<T> {
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
        // scope!("copy_from");
        let bytes_len = std::mem::size_of_val(slice);
        assert!(bytes_len > 0);
        let mut buffer = RawBuffer::new(name, bytes_len);
        let bytes = unchecked_cast(slice);
        buffer.copy_from(bytes).unwrap();

        BufferImpl {
            buffer: Rc::new(RefCell::new(buffer)),
            size: slice.len(),
            offset: 0,
            marker: PhantomData,
        }
    }

    pub fn from_tracked_locked_buffer(
        name: &'static str,
        host_buf: TrackedLockedBuffer,
        size: usize,
    ) -> Self {
        let buffer = RawBuffer::from_tracked_locked_buffer(name, host_buf);
        BufferImpl {
            buffer: Rc::new(RefCell::new(buffer)),
            size,
            offset: 0,
            marker: PhantomData,
        }
    }

    pub fn as_device_ptr(&self) -> DevicePointer<u8> {
        let ptr = self.buffer.borrow().as_device_ptr();
        let offset = self.offset * std::mem::size_of::<T>();
        unsafe { ptr.offset(offset.try_into().unwrap()) }
    }

    pub fn as_device_ptr_with_offset(&self, offset: usize) -> DevicePointer<u8> {
        let ptr = self.buffer.borrow().as_device_ptr();
        let offset = (self.offset + offset) * std::mem::size_of::<T>();
        unsafe { ptr.offset(offset.try_into().unwrap()) }
    }
}

impl<T: Clone> Buffer<T> for BufferImpl<T> {
    fn name(&self) -> &'static str {
        self.buffer.borrow().name
    }

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

    fn get_at(&self, idx: usize) -> T {
        let item_size = std::mem::size_of::<T>();

        // Check if this is host storage (in a separate scope to release borrow)
        let is_host_storage = {
            let buf = self.buffer.borrow();
            buf.as_host_ptr().is_some()
        };

        if is_host_storage {
            // Host storage: directly read from host memory
            let buf = self.buffer.borrow();
            if let Some(host_ptr) = buf.as_host_ptr() {
                let offset = (self.offset + idx) * item_size;
                let ptr = unsafe { host_ptr.add(offset) as *const T };
                return unsafe { ptr.read() };
            }
        }

        // Device storage: use existing logic
        let buf = self.buffer.borrow_mut();
        let offset = (self.offset + idx) * item_size;
        let ptr = unsafe { buf.as_device_ptr().offset(offset as isize) };
        let device_slice = unsafe { DeviceSlice::from_raw_parts(ptr, item_size) };
        let host_buf = device_slice.as_host_vec().unwrap();
        let slice: &[T] = unchecked_cast(&host_buf);
        slice[0].clone()
    }

    fn view<F: FnOnce(&[T])>(&self, f: F) {
        scope!("view");
        let item_size = std::mem::size_of::<T>();

        // Check if this is host storage (in a separate scope to release borrow)
        let is_host_storage = {
            let buf = self.buffer.borrow();
            buf.as_host_ptr().is_some()
        };

        if is_host_storage {
            // Host storage: directly read from host memory
            let buf = self.buffer.borrow();
            if let Some(host_ptr) = buf.as_host_ptr() {
                let offset = self.offset * item_size;
                let ptr = unsafe { host_ptr.add(offset) as *const T };
                let slice = unsafe { std::slice::from_raw_parts(ptr, self.size) };
                f(slice);
                return;
            }
        }

        // Device storage: use existing logic
        let buf = self.buffer.borrow_mut();
        let offset = self.offset * item_size;
        let len = self.size * item_size;
        let ptr = unsafe { buf.as_device_ptr().offset(offset as isize) };
        let device_slice = unsafe { DeviceSlice::from_raw_parts(ptr, len) };
        let host_buf = device_slice.as_host_vec().unwrap();
        let slice = unchecked_cast(&host_buf);
        f(slice);
    }

    fn view_mut<F: FnOnce(&mut [T])>(&self, f: F) {
        scope!("view_mut");
        let item_size = std::mem::size_of::<T>();

        // Check if this is host storage (in a separate scope to release borrow)
        let is_host_storage = {
            let buf = self.buffer.borrow();
            buf.as_host_ptr().is_some()
        };

        if is_host_storage {
            // Host storage: directly write to host memory
            let buf = self.buffer.borrow();
            if let Some(host_ptr) = buf.as_host_ptr() {
                let offset = self.offset * item_size;
                let ptr = unsafe { host_ptr.add(offset) as *mut T };
                let slice = unsafe { std::slice::from_raw_parts_mut(ptr, self.size) };
                f(slice);
                // No need to copy back for host storage
            }
        } else {
            // Device storage: use existing logic
            let mut buf = self.buffer.borrow_mut();
            let mut host_buf = buf.as_host_vec().unwrap();
            let slice = unchecked_cast_mut(&mut host_buf);
            f(&mut slice[self.offset..]);
            buf.copy_from(&host_buf).unwrap();
        }
    }

    fn to_vec(&self) -> Vec<T> {
        // Check if this is host storage (in a separate scope to release borrow)
        let is_host_storage = {
            let buf = self.buffer.borrow();
            buf.as_host_ptr().is_some()
        };

        if is_host_storage {
            // Host storage: directly read from host memory
            let buf = self.buffer.borrow();
            if let Some(host_ptr) = buf.as_host_ptr() {
                let item_size = std::mem::size_of::<T>();
                let offset = self.offset * item_size;
                let ptr = unsafe { host_ptr.add(offset) as *const T };
                let slice = unsafe { std::slice::from_raw_parts(ptr, self.size) };
                return slice.to_vec();
            }
        }

        // Device storage: use existing logic
        let mut buf = self.buffer.borrow_mut();
        let host_buf = buf.as_host_vec().unwrap();
        let slice = unchecked_cast(&host_buf);
        slice.to_vec()
    }
}

impl<CH: CudaHash> Default for CudaHal<CH> {
    fn default() -> Self {
        Self::new()
    }
}

impl<CH: CudaHash + ?Sized> CudaHal<CH> {
    pub fn new() -> Self
    where
        CH: Sized,
    {
        Self::new_from_hash(Box::new(CH::new()))
    }

    fn new_from_hash(hash: Box<CH>) -> Self {
        let _lock = singleton().lock();

        let err = unsafe { sppark_init() };
        if err.code != 0 {
            panic!("Failure during sppark_init: {err}");
        }

        cust::init(CudaFlags::empty()).unwrap();
        let device = Device::get_device(0).unwrap();
        let max_threads = device
            .get_attribute(DeviceAttribute::MaxThreadsPerBlock)
            .unwrap();
        let context = Context::new(device).unwrap();
        context.set_flags(ContextFlags::SCHED_AUTO).unwrap();

        let mut hal = Self {
            max_threads: max_threads as u32,
            _context: context,
            hash: None,
            _lock,
        };
        hal.hash = Some(hash);
        hal
    }

    pub fn alloc_locked_host_buffer(
        &self,
        name: &'static str,
        size: usize,
    ) -> Result<TrackedLockedBuffer> {
        TrackedLockedBuffer::new(name, size)
    }

    fn poly_divide(
        &self,
        polynomial: &BufferImpl<BabyBearExtElem>,
        pow: BabyBearExtElem,
    ) -> BabyBearExtElem {
        let mut remainder = BabyBearExtElem::ZERO;
        let poly_size = polynomial.size();
        let pow = pow.to_u32_words();

        let err = unsafe {
            supra_poly_divide(
                polynomial.as_device_ptr(),
                poly_size,
                &mut remainder as *mut _ as *mut u32,
                pow.as_ptr(),
            )
        };

        if err.code != 0 {
            panic!("Failure during supra_poly_divide: {err}");
        }

        remainder
    }
}

impl CudaHal<dyn CudaHash> {
    pub fn new_from_hash_suite(hash_suite: HashSuite<BabyBear>) -> Result<Self> {
        let hash_suite_box = match &hash_suite.name[..] {
            "poseidon2" => Box::new(CudaHashPoseidon2::new()) as Box<dyn CudaHash>,
            "poseidon254" => Box::new(CudaHashPoseidon254::new()) as Box<dyn CudaHash>,
            "sha-256" => Box::new(CudaHashSha256::new()) as Box<dyn CudaHash>,
            other => bail!("unsupported hash_fn {other}"),
        };
        Ok(Self::new_from_hash(hash_suite_box))
    }
}

impl<CH: CudaHash + ?Sized> Hal for CudaHal<CH> {
    type Field = BabyBear;
    type Elem = BabyBearElem;
    type ExtElem = BabyBearExtElem;
    type Buffer<T: Clone + Debug + PartialEq> = BufferImpl<T>;

    fn alloc_elem(&self, name: &'static str, size: usize) -> Self::Buffer<Self::Elem> {
        BufferImpl::new(name, size)
    }

    fn alloc_elem_init(
        &self,
        name: &'static str,
        size: usize,
        value: Self::Elem,
    ) -> Self::Buffer<Self::Elem> {
        let buffer = self.alloc_elem(name, size);
        buffer
            .buffer
            .borrow_mut()
            .set_u32(value.as_u32_montgomery());
        buffer
    }

    fn copy_from_elem(&self, name: &'static str, slice: &[Self::Elem]) -> Self::Buffer<Self::Elem> {
        BufferImpl::copy_from(name, slice)
    }

    fn alloc_extelem(&self, name: &'static str, size: usize) -> Self::Buffer<Self::ExtElem> {
        BufferImpl::new(name, size)
    }

    fn alloc_extelem_zeroed(&self, name: &'static str, size: usize) -> Self::Buffer<Self::ExtElem> {
        let buffer = self.alloc_extelem(name, size);
        buffer.buffer.borrow_mut().set_u32(0);
        buffer
    }

    fn copy_from_extelem(
        &self,
        name: &'static str,
        slice: &[Self::ExtElem],
    ) -> Self::Buffer<Self::ExtElem> {
        BufferImpl::copy_from(name, slice)
    }

    fn alloc_digest(&self, name: &'static str, size: usize) -> Self::Buffer<Digest> {
        BufferImpl::new(name, size)
    }

    fn copy_from_digest(&self, name: &'static str, slice: &[Digest]) -> Self::Buffer<Digest> {
        BufferImpl::copy_from(name, slice)
    }

    fn alloc_u32(&self, name: &'static str, size: usize) -> Self::Buffer<u32> {
        BufferImpl::new(name, size)
    }

    fn copy_from_u32(&self, name: &'static str, slice: &[u32]) -> Self::Buffer<u32> {
        BufferImpl::copy_from(name, slice)
    }

    fn batch_expand_into_evaluate_ntt(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
        poly_count: usize,
        expand_bits: usize,
    ) {
        // batch_expand
        {
            let out_size = output.size() / poly_count;
            let in_size = input.size() / poly_count;
            let expand_bits = log2_ceil(out_size / in_size);
            assert_eq!(output.size(), out_size * poly_count);
            assert_eq!(input.size(), in_size * poly_count);
            assert_eq!(out_size, in_size * (1 << expand_bits));
            let in_bits = log2_ceil(in_size);
            let err = unsafe {
                sppark_batch_expand(
                    output.as_device_ptr(),
                    input.as_device_ptr(),
                    in_bits.try_into().unwrap(),
                    expand_bits.try_into().unwrap(),
                    poly_count.try_into().unwrap(),
                )
            };
            if err.code != 0 {
                panic!("Failure during batch_expand: {err}");
            }
        }

        // batch_evaluate_ntt
        {
            let row_size = output.size() / poly_count;
            assert_eq!(row_size * poly_count, output.size());
            let n_bits = log2_ceil(row_size);
            assert_eq!(row_size, 1 << n_bits);
            assert!(n_bits >= expand_bits);
            assert!(n_bits < Self::Elem::MAX_ROU_PO2);

            let err = unsafe {
                sppark_batch_NTT(
                    output.as_device_ptr(),
                    n_bits.try_into().unwrap(),
                    poly_count.try_into().unwrap(),
                )
            };
            if err.code != 0 {
                panic!("Failure during batch_evaluate_ntt: {err}");
            }
        }
    }

    fn batch_interpolate_ntt(&self, io: &Self::Buffer<Self::Elem>, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        let n_bits = log2_ceil(row_size);
        assert_eq!(row_size, 1 << n_bits);
        assert!(n_bits < Self::Elem::MAX_ROU_PO2);

        let err = unsafe {
            sppark_batch_iNTT(
                io.as_device_ptr(),
                n_bits.try_into().unwrap(),
                count.try_into().unwrap(),
            )
        };
        if err.code != 0 {
            panic!("Failure during batch_interpolate_ntt: {err}");
        }
    }

    fn batch_evaluate_ntt(&self, io: &Self::Buffer<Self::Elem>, count: usize) {
        let pcount = if count >= (1 << 15) {
            count - (1 << 15)
        } else {
            count
        };
        let row_size = io.size() / pcount;
        assert_eq!(row_size * pcount, io.size());
        let n_bits = log2_ceil(row_size);
        assert_eq!(row_size, 1 << n_bits);
        assert!(n_bits < Self::Elem::MAX_ROU_PO2);

        let err = unsafe {
            sppark_batch_NTT(
                io.as_device_ptr(),
                n_bits.try_into().unwrap(),
                count.try_into().unwrap(),
            )
        };
        if err.code != 0 {
            panic!("Failure during batch_interpolate_ntt: {err}");
        }
    }

    fn batch_bit_reverse(&self, io: &Self::Buffer<Self::Elem>, count: usize) {
        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        let bits = log2_ceil(row_size);
        assert_eq!(row_size, 1 << bits);
        let io_size = io.size();

        extern "C" {
            fn risc0_zkp_cuda_batch_bit_reverse(
                io: DevicePointer<u8>,
                bits: u32,
                count: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_batch_bit_reverse(io.as_device_ptr(), bits as u32, io_size as u32)
        })
        .unwrap();
    }

    fn batch_evaluate_any(
        &self,
        coeffs: &Self::Buffer<Self::Elem>,
        poly_n: usize,
        which: &Self::Buffer<u32>,
        xs: &Self::Buffer<Self::ExtElem>,
        out: &Self::Buffer<Self::ExtElem>,
    ) {
        let po2 = log2_ceil(coeffs.size() / poly_n);
        let deg = 1 << po2;
        assert_eq!(poly_n * deg, coeffs.size());

        let eval_n = which.size();
        assert_eq!(xs.size(), eval_n);
        assert_eq!(out.size(), eval_n);

        // Determine chunk_n based on poly_n (similar to batch_evaluate_same_x_bk)
        let chunk_n: usize = if poly_n > 100 { 8 } else { 32 };

        // Allocate temporary device buffer for chunk results
        let chunk_out = self.alloc_extelem("chunk_out", eval_n * chunk_n);

        extern "C" {
            fn risc0_zkp_cuda_batch_evaluate_any(
                output: DevicePointer<u8>,
                chunk_output: DevicePointer<u8>,
                coeffs: DevicePointer<u8>,
                which: DevicePointer<u8>,
                xs: DevicePointer<u8>,
                eval_n: u32,
                deg: u32,
                chunk_n: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_batch_evaluate_any(
                out.as_device_ptr(),
                chunk_out.as_device_ptr(),
                coeffs.as_device_ptr(),
                which.as_device_ptr(),
                xs.as_device_ptr(),
                eval_n as u32,
                deg as u32,
                chunk_n as u32,
            )
        })
        .unwrap();

        // chunk_out will be automatically freed when it goes out of scope
    }

    fn batch_evaluate_same_x(
        &self,
        coeffs: &Self::Buffer<Self::Elem>,
        poly_n: usize,
        which: &Self::Buffer<u32>,
        xs: Vec<Self::Elem>,
    ) -> Vec<Self::Elem> {
        let po2 = log2_ceil(coeffs.size() / poly_n);
        let deg = 1 << po2;
        let x_n = xs.len();

        assert_eq!(poly_n, which.size());
        assert_eq!(poly_n * deg, coeffs.size());

        let chunk_n: usize = if poly_n > 100 { 4 } else { 32 };

        extern "C" {
            fn risc0_zkp_cuda_batch_evaluate_same_x(
                output: *mut u8,
                coeffs: DevicePointer<u8>,
                which: DevicePointer<u8>,
                xs: *const u8,
                chunk_n: u32,
                poly_n: u32,
                deg: u32,
                x_n: u32,
            ) -> *const std::os::raw::c_char;
        }

        // The underlying CUDA kernel hardcodes Fp sum[25] / powx[25] for
        // register-pressure reasons; loop in chunks of X_BATCH internally so
        // callers can pass an arbitrary number of x's.
        const X_BATCH: usize = 25;
        let mut ys = Vec::with_capacity(poly_n * x_n);

        for xs_chunk in xs.chunks(X_BATCH) {
            let chunk_x_n = xs_chunk.len();
            let mut out_host = vec![Self::Elem::ZERO; poly_n * chunk_n * chunk_x_n];

            ffi_wrap(|| unsafe {
                risc0_zkp_cuda_batch_evaluate_same_x(
                    out_host.as_mut_ptr() as *mut u8,
                    coeffs.as_device_ptr(),
                    which.as_device_ptr(),
                    xs_chunk.as_ptr() as *const u8,
                    chunk_n as u32,
                    poly_n as u32,
                    deg as u32,
                    chunk_x_n as u32,
                )
            })
            .unwrap();

            // Compute per-x chunk-folding powers
            let mut xpows = Vec::with_capacity(chunk_n * chunk_x_n);
            for x in xs_chunk.iter().take(chunk_x_n) {
                let xp = x.pow(deg / chunk_n);
                let mut xpow = Self::Elem::ONE;
                for _ in 0..chunk_n {
                    xpows.push(xpow);
                    xpow *= xp;
                }
            }

            // Fold chunk outputs into final ys[xid][poly] entries
            for xid in 0..chunk_x_n {
                for i in 0..poly_n {
                    let c0id = i + xid * poly_n * chunk_n;
                    let mut y = out_host[c0id];
                    for c in 1..chunk_n {
                        y += out_host[c0id + poly_n * c] * xpows[c + chunk_n * xid];
                    }
                    ys.push(y);
                }
            }
        }

        ys
    }

    fn gather_sample(
        &self,
        dst: &Self::Buffer<Self::Elem>,
        src: &Self::Buffer<Self::Elem>,
        idx: usize,
        size: usize,
        stride: usize,
    ) {
        extern "C" {
            fn risc0_zkp_cuda_gather_sample(
                dst: DevicePointer<u8>,
                src: DevicePointer<u8>,
                idx: u32,
                size: u32,
                stride: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_gather_sample(
                dst.as_device_ptr(),
                src.as_device_ptr(),
                idx as u32,
                size as u32,
                stride as u32,
            )
        })
        .unwrap();
    }

    fn gather_samples_batch(
        &self,
        dst: &Self::Buffer<Self::Elem>,
        src: &Self::Buffer<Self::Elem>,
        idxs: &[u32],
        col_size: usize,
        stride: usize,
    ) {
        // Upload idxs to a GPU buffer, then launch one batched kernel.
        let idxs_buf = self.copy_from_u32("gather_idxs", idxs);

        extern "C" {
            fn risc0_zkp_cuda_gather_samples_batch(
                dst: DevicePointer<u8>,
                src: DevicePointer<u8>,
                idxs: DevicePointer<u8>,
                n_idxs: u32,
                col_size: u32,
                stride: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_gather_samples_batch(
                dst.as_device_ptr(),
                src.as_device_ptr(),
                idxs_buf.as_device_ptr(),
                idxs.len() as u32,
                col_size as u32,
                stride as u32,
            )
        })
        .unwrap();
    }

    fn gather_digests_batch(&self, nodes: &Self::Buffer<Digest>, indices: &[u32]) -> Vec<Digest> {
        let n = indices.len();
        if n == 0 {
            return Vec::new();
        }

        // host pinned (e.g. rv32im code group merkle.nodes after copy_merkle2host):
        // walk the host slice directly, no kernel + no D2H.
        let is_host = nodes.buffer.borrow().as_host_ptr().is_some();
        if is_host {
            let buf = nodes.buffer.borrow();
            let host_ptr = buf.as_host_ptr().unwrap();
            let base = nodes.offset;
            let mut out = Vec::with_capacity(n);
            for &i in indices {
                let p = unsafe { (host_ptr as *const Digest).add(base + i as usize) };
                out.push(unsafe { p.read() });
            }
            return out;
        }

        // device storage: gather kernel + single D2H of n digests.
        let dst: BufferImpl<Digest> = BufferImpl::new("gather_digests_dst", n);
        let idxs_buf = self.copy_from_u32("gather_digests_idxs", indices);

        extern "C" {
            fn risc0_zkp_cuda_gather_digests_batch(
                dst: DevicePointer<u8>,
                src: DevicePointer<u8>,
                idxs: DevicePointer<u8>,
                n: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_gather_digests_batch(
                dst.as_device_ptr(),
                nodes.as_device_ptr(),
                idxs_buf.as_device_ptr(),
                n as u32,
            )
        })
        .unwrap();

        let mut out = Vec::with_capacity(n);
        dst.view(|view| out.extend_from_slice(view));
        out
    }

    fn has_unified_memory(&self) -> bool {
        false
    }

    fn zk_shift(
        &self,
        io: &Self::Buffer<Self::Elem>,
        poly_count: usize,
        beta: Self::Elem,
        factor: u32,
    ) {
        let bits = log2_ceil(io.size() / poly_count);
        assert_eq!(io.size(), poly_count * (1 << bits));

        let err = unsafe {
            sppark_batch_zk_shift(
                io.as_device_ptr(),
                bits.try_into().unwrap(),
                poly_count.try_into().unwrap(),
                beta.as_u32_montgomery(),
                factor,
            )
        };
        if err.code != 0 {
            panic!("Failure during zk_shift: {err}");
        }
    }

    fn zk_shift_outplace(
        &self,
        d_in: &Self::Buffer<Self::Elem>,
        d_out: &Self::Buffer<Self::Elem>,
        poly_count: usize,
        beta: Self::Elem,
        factor: u32,
    ) {
        let bits = log2_ceil(d_in.size() / poly_count);
        assert_eq!(d_in.size(), poly_count * (1 << bits));

        let err = unsafe {
            sppark_batch_zk_shift_outplace(
                d_in.as_device_ptr(),
                d_out.as_device_ptr(),
                bits.try_into().unwrap(),
                poly_count.try_into().unwrap(),
                beta.as_u32_montgomery(),
                factor,
            )
        };
        if err.code != 0 {
            panic!("Failure during zk_shift_outplace: {err}");
        }
    }

    fn batch_coeffs_bitrev(&self, d_inout: &Self::Buffer<Self::Elem>, poly_count: usize) {
        let bits = log2_ceil(d_inout.size() / poly_count);
        assert_eq!(d_inout.size(), poly_count * (1 << bits));

        let err = unsafe {
            sppark_batch_coeffs_bitrev(
                d_inout.as_device_ptr(),
                bits.try_into().unwrap(),
                poly_count.try_into().unwrap(),
            )
        };
        if err.code != 0 {
            panic!("Failure during sppark_batch_coeffs_bitrev: {err}");
        }
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
        let mix_start = self.copy_from_extelem("mix_start", &[*mix_start]);
        let mix = self.copy_from_extelem("mix", &[*mix]);

        extern "C" {
            fn risc0_zkp_cuda_mix_poly_coeffs(
                output: DevicePointer<u8>,
                input: DevicePointer<u8>,
                combos: DevicePointer<u8>,
                mix_start: DevicePointer<u8>,
                mix: DevicePointer<u8>,
                input_size: u32,
                count: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_mix_poly_coeffs(
                output.as_device_ptr(),
                input.as_device_ptr(),
                combos.as_device_ptr(),
                mix_start.as_device_ptr(),
                mix.as_device_ptr(),
                input_size as u32,
                count as u32,
            )
        })
        .unwrap();
    }

    fn eltwise_add_elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input1: &Self::Buffer<Self::Elem>,
        input2: &Self::Buffer<Self::Elem>,
    ) {
        assert_eq!(output.size(), input1.size());
        assert_eq!(output.size(), input2.size());
        let count = output.size();

        extern "C" {
            fn risc0_zkp_cuda_eltwise_add_fp(
                out: DevicePointer<u8>,
                x: DevicePointer<u8>,
                y: DevicePointer<u8>,
                count: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_eltwise_add_fp(
                output.as_device_ptr(),
                input1.as_device_ptr(),
                input2.as_device_ptr(),
                count as u32,
            )
        })
        .unwrap();
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

        extern "C" {
            fn risc0_zkp_cuda_eltwise_sum_fpext(
                output: DevicePointer<u8>,
                input: DevicePointer<u8>,
                to_add: u32,
                count: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_eltwise_sum_fpext(
                output.as_device_ptr(),
                input.as_device_ptr(),
                to_add as u32,
                count as u32,
            )
        })
        .unwrap();
    }

    fn eltwise_copy_elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
    ) {
        let count = output.size();
        assert_eq!(count, input.size());

        extern "C" {
            fn risc0_zkp_cuda_eltwise_copy_fp(
                output: DevicePointer<u8>,
                input: DevicePointer<u8>,
                count: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_eltwise_copy_fp(
                output.as_device_ptr(),
                input.as_device_ptr(),
                count as u32,
            )
        })
        .unwrap();
    }

    fn copy_digest2elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Digest>,
        offset_bytes: usize,
    ) {
        use std::mem::size_of;

        unsafe {
            extern "C" {
                fn cudaMemcpy(
                    dst: *mut std::ffi::c_void,
                    src: *const std::ffi::c_void,
                    count: usize,
                    kind: u32,
                ) -> i32;
            }

            // Calculate input size in bytes
            let input_size_bytes = input.size() * size_of::<Digest>();

            // Get device pointers
            let src_ptr = input.as_device_ptr();
            let output_base_ptr = output.as_device_ptr();
            let dst_ptr = output_base_ptr.offset(offset_bytes as isize);

            // Perform device-to-device copy (kind = 1 for cudaMemcpyDeviceToDevice)
            let result = cudaMemcpy(
                dst_ptr.as_raw() as *mut std::ffi::c_void,
                src_ptr.as_raw() as *const std::ffi::c_void,
                input_size_bytes,
                1, // cudaMemcpyDeviceToDevice
            );

            if result != 0 {
                panic!("cudaMemcpy failed: error code {}", result);
            }
        }
    }

    fn elem2dig_buffer_transmute(
        &self,
        buffer: &Self::Buffer<Self::Elem>,
        offset_bytes: usize,
        count: usize,
    ) -> Self::Buffer<Digest> {
        use std::mem::size_of;

        // SAFETY: BufferImpl<Digest> and Self::Buffer<Digest> resolve to the
        // same concrete type when monomorphized on the CUDA backend; the
        // transmute is a no-op cast through the trait's associated type.
        #[allow(clippy::useless_transmute)]
        let buffer_as_digest: BufferImpl<Digest> = unsafe { std::mem::transmute(buffer.clone()) };
        let digest_elem_offset = offset_bytes / size_of::<Digest>();

        let nodes_slice = buffer_as_digest.slice(digest_elem_offset, count);
        #[allow(clippy::useless_transmute)]
        unsafe {
            std::mem::transmute(nodes_slice)
        }
    }

    fn eltwise_zeroize_elem(&self, elems: &Self::Buffer<Self::Elem>) {
        extern "C" {
            fn risc0_zkp_cuda_eltwise_zeroize_fp(
                elems: DevicePointer<u8>,
                count: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_eltwise_zeroize_fp(elems.as_device_ptr(), elems.size() as u32)
        })
        .unwrap();
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

        let count = index.len() - 1;
        if count == 0 {
            return;
        }

        let index = self.copy_from_u32("index", index);
        let offsets = self.copy_from_u32("offsets", offsets);
        let values = self.copy_from_elem("values", values);

        extern "C" {
            fn risc0_zkp_cuda_scatter(
                into: DevicePointer<u8>,
                index: DevicePointer<u8>,
                offsets: DevicePointer<u8>,
                values: DevicePointer<u8>,
                count: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_scatter(
                into.as_device_ptr(),
                index.as_device_ptr(),
                offsets.as_device_ptr(),
                values.as_device_ptr(),
                count as u32,
            )
        })
        .unwrap();
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
        let from = self.copy_from_elem("from", from);

        extern "C" {
            fn risc0_zkp_cuda_eltwise_copy_fp_region(
                into: DevicePointer<u8>,
                from: DevicePointer<u8>,
                from_rows: u32,
                from_cols: u32,
                from_offset: u32,
                from_stride: u32,
                into_offset: u32,
                into_stride: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_eltwise_copy_fp_region(
                into.as_device_ptr(),
                from.as_device_ptr(),
                from_rows as u32,
                from_cols as u32,
                from_offset as u32,
                from_stride as u32,
                into_offset as u32,
                into_stride as u32,
            )
        })
        .unwrap();
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
        let mix = self.copy_from_extelem("mix", &[*mix]);

        extern "C" {
            fn risc0_zkp_cuda_fri_fold(
                output: DevicePointer<u8>,
                input: DevicePointer<u8>,
                mix: DevicePointer<u8>,
                count: u32,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_fri_fold(
                output.as_device_ptr(),
                input.as_device_ptr(),
                mix.as_device_ptr(),
                count as u32,
            )
        })
        .unwrap();
    }

    fn hash_fold(&self, io: &Self::Buffer<Digest>, input_size: usize, output_size: usize) {
        assert_eq!(input_size, 2 * output_size);
        self.hash.as_ref().unwrap().hash_fold(io, output_size);
    }

    fn hash_rows(&self, output: &Self::Buffer<Digest>, matrix: &Self::Buffer<Self::Elem>) {
        self.hash.as_ref().unwrap().hash_rows(output, matrix);
    }

    #[cfg(all(feature = "low_vram", feature = "cuda"))]
    fn hash_rows_interleave(
        &self,
        output: &Self::Buffer<Digest>,
        matrix: &Self::Buffer<Self::Elem>,
        codeword_id: u32,
    ) {
        self.hash
            .as_ref()
            .unwrap()
            .hash_rows_interleave(output, matrix, codeword_id);
    }

    fn get_hash_suite(&self) -> &HashSuite<Self::Field> {
        self.hash.as_ref().unwrap().get_hash_suite()
    }

    fn prefix_products(&self, io: &Self::Buffer<Self::ExtElem>) {
        io.view_mut(|io| {
            for i in 1..io.len() {
                io[i] *= io[i - 1];
            }
        });
    }

    fn combos_prepare(
        &self,
        combos: &Self::Buffer<Self::ExtElem>,
        coeff_u: &[Self::ExtElem],
        combo_count: usize,
        cycles: usize,
        reg_sizes: &[u32],
        reg_combo_ids: &[u32],
        mix: &Self::ExtElem,
    ) {
        let coeff_u = self.copy_from_extelem("coeff_u", coeff_u);
        let combo_count = combo_count as u32;
        let cycles = cycles as u32;
        let regs_count = reg_sizes.len() as u32;
        let reg_sizes = self.copy_from_u32("reg_sizes", reg_sizes);
        let reg_combo_ids = self.copy_from_u32("reg_combo_ids", reg_combo_ids);
        let mix = self.copy_from_extelem("mix", &[*mix]);

        extern "C" {
            fn risc0_zkp_cuda_combos_prepare(
                combos: DevicePointer<u8>,
                coeff_u: DevicePointer<u8>,
                combo_count: u32,
                cycles: u32,
                regs_count: u32,
                reg_sizes: DevicePointer<u8>,
                reg_combo_ids: DevicePointer<u8>,
                checkSize: u32,
                mix: DevicePointer<u8>,
            ) -> *const std::os::raw::c_char;
        }

        ffi_wrap(|| unsafe {
            risc0_zkp_cuda_combos_prepare(
                combos.as_device_ptr(),
                coeff_u.as_device_ptr(),
                combo_count,
                cycles,
                regs_count,
                reg_sizes.as_device_ptr(),
                reg_combo_ids.as_device_ptr(),
                Self::CHECK_SIZE as u32,
                mix.as_device_ptr(),
            )
        })
        .unwrap();
    }

    fn combos_divide(
        &self,
        combos: &Self::Buffer<Self::ExtElem>,
        chunks: Vec<(usize, Vec<Self::ExtElem>)>,
        cycles: usize,
    ) {
        scope!("combos_divide");
        for (i, pows) in chunks {
            let combo_slice = combos.slice(i * cycles, cycles);
            for pow in pows {
                let remainder = self.poly_divide(&combo_slice, pow);
                assert_eq!(remainder, Self::ExtElem::ZERO, "i: {i}");
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use test_log::test;

    use super::{CudaHalPoseidon2, CudaHalSha256};
    use crate::hal::testutil;

    #[test]
    #[should_panic]
    fn check_req() {
        testutil::check_req(CudaHalSha256::new());
    }

    #[test]
    fn eltwise_add_elem() {
        testutil::eltwise_add_elem(CudaHalSha256::new());
    }

    #[test]
    fn eltwise_copy_elem() {
        testutil::eltwise_copy_elem(CudaHalSha256::new());
    }

    #[test]
    fn eltwise_sum_extelem() {
        testutil::eltwise_sum_extelem(CudaHalSha256::new());
    }

    #[test]
    fn hash_rows_sha256() {
        testutil::hash_rows(CudaHalSha256::new());
    }

    #[test]
    fn hash_fold_sha256() {
        testutil::hash_fold(CudaHalSha256::new());
    }

    #[test]
    fn hash_rows_poseidon2() {
        testutil::hash_rows(CudaHalPoseidon2::new());
    }

    #[test]
    fn hash_fold_poseidon2() {
        testutil::hash_fold(CudaHalPoseidon2::new());
    }

    #[test]
    fn fri_fold() {
        testutil::fri_fold(CudaHalSha256::new());
    }

    #[test]
    fn batch_expand_into_evaluate_ntt() {
        testutil::batch_expand_into_evaluate_ntt(CudaHalSha256::new());
    }

    #[test]
    fn batch_interpolate_ntt() {
        testutil::batch_interpolate_ntt(CudaHalSha256::new());
    }

    #[test]
    fn batch_bit_reverse() {
        testutil::batch_bit_reverse(CudaHalSha256::new());
    }

    #[test]
    fn batch_evaluate_any() {
        testutil::batch_evaluate_any(CudaHalSha256::new());
    }

    #[test]
    fn gather_sample() {
        testutil::gather_sample(CudaHalSha256::new());
    }

    #[test]
    fn zk_shift() {
        testutil::zk_shift(CudaHalSha256::new());
    }

    #[test]
    fn mix_poly_coeffs() {
        testutil::mix_poly_coeffs(CudaHalSha256::new());
    }
}
