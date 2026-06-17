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

//! `PinnedVec<T>`: a `Vec`-like container backed by CUDA pinned (page-locked)
//! host memory via `cudaMallocHost`/`cudaFreeHost`.
//!
//! Used by `PreflightTrace` for the three large H2D buffers (`cycles`, `txns`,
//! `bigint_bytes`). Putting the source memory in pinned arena lets
//! `cudaMemcpy` skip the driver's pageable→pinned bounce buffer and DMA at
//! full PCIe gen4 bandwidth (~22 GB/s instead of ~6 GB/s).
//!
//! When the `cuda` feature is disabled (CPU build), `PinnedVec<T>` falls back
//! to wrapping a plain `Vec<T>` so all callers compile unchanged.
//!
//! API surface is the minimum needed by `preflight.rs`: `with_capacity`,
//! `push`, `extend_from_slice` (T: Copy), `truncate`, `len`/`is_empty`, plus
//! `Deref<Target=[T]>` / `DerefMut<Target=[T]>` so indexing, `iter()`,
//! `iter_mut()`, `last()`, etc. just work via the standard slice methods.

#[cfg(all(feature = "cuda", feature = "pinned_witgen"))]
mod imp {
    use std::fmt;
    use std::ops::{Deref, DerefMut};
    use std::ptr::NonNull;

    extern "C" {
        fn cudaMallocHost(ptr: *mut *mut std::ffi::c_void, size: usize) -> i32;
        fn cudaFreeHost(ptr: *mut std::ffi::c_void) -> i32;
    }

    // Global reuse pool: PinnedVec drops return their buffer here instead
    // of calling cudaFreeHost. Subsequent with_capacity() calls scan this
    // pool for a big-enough buffer first. Persistent for process lifetime.
    struct PoolEntry {
        ptr: *mut u8,
        cap_bytes: usize,
    }
    unsafe impl Send for PoolEntry {}

    static PINNED_POOL: std::sync::Mutex<Vec<PoolEntry>> = std::sync::Mutex::new(Vec::new());

    fn pool_take(bytes_needed: usize) -> Option<PoolEntry> {
        let mut pool = PINNED_POOL.lock().unwrap();
        // Find the smallest buffer that fits — minimizes wasted capacity.
        let mut best: Option<usize> = None;
        for (i, e) in pool.iter().enumerate() {
            if e.cap_bytes >= bytes_needed
                && best
                    .map(|b| pool[b].cap_bytes > e.cap_bytes)
                    .unwrap_or(true)
            {
                best = Some(i);
            }
        }
        best.map(|i| pool.swap_remove(i))
    }

    fn pool_return(entry: PoolEntry) {
        PINNED_POOL.lock().unwrap().push(entry);
    }

    pub struct PinnedVec<T> {
        ptr: NonNull<T>,
        len: usize,
        cap: usize,
    }

    // Pinned host memory is plain bytes; sharing across threads is no different
    // from sharing a Vec across threads (still subject to T's own Send/Sync).
    unsafe impl<T: Send> Send for PinnedVec<T> {}
    unsafe impl<T: Sync> Sync for PinnedVec<T> {}

    impl<T> PinnedVec<T> {
        pub fn new() -> Self {
            Self {
                ptr: NonNull::dangling(),
                len: 0,
                cap: 0,
            }
        }

        pub fn with_capacity(cap: usize) -> Self {
            if cap == 0 {
                return Self::new();
            }
            let bytes = cap
                .checked_mul(std::mem::size_of::<T>())
                .expect("PinnedVec capacity overflow");
            // Try to satisfy from the global pool first: pick the smallest
            // pooled buffer that's big enough. If none fits, fall back to
            // cudaMallocHost.
            if let Some(entry) = pool_take(bytes) {
                let pooled_cap = entry.cap_bytes / std::mem::size_of::<T>();
                return Self {
                    ptr: unsafe { NonNull::new_unchecked(entry.ptr as *mut T) },
                    len: 0,
                    cap: pooled_cap,
                };
            }
            let mut v = Self::new();
            unsafe { v.alloc_to(cap) };
            v
        }

        #[inline]
        pub fn len(&self) -> usize {
            self.len
        }

        #[inline]
        #[allow(dead_code)]
        pub fn push(&mut self, value: T) {
            if self.len == self.cap {
                let new_cap = if self.cap == 0 { 64 } else { self.cap * 2 };
                unsafe { self.grow_to(new_cap) };
            }
            unsafe {
                self.ptr.as_ptr().add(self.len).write(value);
            }
            self.len += 1;
        }

        pub fn extend_from_slice(&mut self, src: &[T])
        where
            T: Copy,
        {
            let need = self.len + src.len();
            if need > self.cap {
                let mut new_cap = if self.cap == 0 { 64 } else { self.cap };
                while new_cap < need {
                    new_cap *= 2;
                }
                unsafe { self.grow_to(new_cap) };
            }
            unsafe {
                std::ptr::copy_nonoverlapping(
                    src.as_ptr(),
                    self.ptr.as_ptr().add(self.len),
                    src.len(),
                );
            }
            self.len += src.len();
        }

        pub fn truncate(&mut self, new_len: usize) {
            if new_len >= self.len {
                return;
            }
            let drop_count = self.len - new_len;
            unsafe {
                let drop_start = self.ptr.as_ptr().add(new_len);
                std::ptr::drop_in_place(std::slice::from_raw_parts_mut(drop_start, drop_count));
            }
            self.len = new_len;
        }

        // Allocate a fresh pinned buffer of `new_cap` slots; assumes cap == 0.
        unsafe fn alloc_to(&mut self, new_cap: usize) {
            debug_assert_eq!(self.cap, 0);
            let bytes = new_cap
                .checked_mul(std::mem::size_of::<T>())
                .expect("PinnedVec capacity overflow");
            let mut new_ptr: *mut std::ffi::c_void = std::ptr::null_mut();
            let res = cudaMallocHost(&mut new_ptr, bytes);
            if res != 0 {
                panic!("cudaMallocHost({} bytes) failed: code {}", bytes, res);
            }
            self.ptr = NonNull::new_unchecked(new_ptr as *mut T);
            self.cap = new_cap;
        }

        // Grow capacity to `new_cap`; allocates a new buffer, copies existing
        // initialized prefix, frees the old one.
        unsafe fn grow_to(&mut self, new_cap: usize) {
            debug_assert!(new_cap >= self.len);
            let bytes = new_cap
                .checked_mul(std::mem::size_of::<T>())
                .expect("PinnedVec capacity overflow");
            let mut new_ptr: *mut std::ffi::c_void = std::ptr::null_mut();
            let res = cudaMallocHost(&mut new_ptr, bytes);
            if res != 0 {
                panic!("cudaMallocHost({} bytes) failed: code {}", bytes, res);
            }
            let new_ptr = new_ptr as *mut T;
            if self.len > 0 {
                std::ptr::copy_nonoverlapping(self.ptr.as_ptr(), new_ptr, self.len);
            }
            if self.cap > 0 {
                cudaFreeHost(self.ptr.as_ptr() as *mut std::ffi::c_void);
            }
            self.ptr = NonNull::new_unchecked(new_ptr);
            self.cap = new_cap;
        }
    }

    impl<T> Drop for PinnedVec<T> {
        fn drop(&mut self) {
            // Drop initialized elements; T may have non-trivial destructors.
            self.truncate(0);
            if self.cap > 0 {
                // Return the underlying pinned buffer to the global pool
                // instead of cudaFreeHost, so next allocation can reuse.
                let cap_bytes = self.cap * std::mem::size_of::<T>();
                pool_return(PoolEntry {
                    ptr: self.ptr.as_ptr() as *mut u8,
                    cap_bytes,
                });
                self.cap = 0;
            }
        }
    }

    impl<T> Default for PinnedVec<T> {
        fn default() -> Self {
            Self::new()
        }
    }

    impl<T> Deref for PinnedVec<T> {
        type Target = [T];
        fn deref(&self) -> &[T] {
            if self.len == 0 {
                &[]
            } else {
                unsafe { std::slice::from_raw_parts(self.ptr.as_ptr(), self.len) }
            }
        }
    }

    impl<T> DerefMut for PinnedVec<T> {
        fn deref_mut(&mut self) -> &mut [T] {
            if self.len == 0 {
                &mut []
            } else {
                unsafe { std::slice::from_raw_parts_mut(self.ptr.as_ptr(), self.len) }
            }
        }
    }

    impl<T: Clone> Clone for PinnedVec<T> {
        fn clone(&self) -> Self {
            let mut new = Self::with_capacity(self.len);
            for item in self.iter() {
                new.push(item.clone());
            }
            new
        }
    }

    impl<T: fmt::Debug> fmt::Debug for PinnedVec<T> {
        fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
            self.deref().fmt(f)
        }
    }
}

#[cfg(not(all(feature = "cuda", feature = "pinned_witgen")))]
mod imp {
    use std::fmt;
    use std::ops::{Deref, DerefMut};

    /// Fallback for non-CUDA builds: just wraps a plain `Vec<T>`.
    /// Same API as the pinned variant so callers compile unchanged.
    pub struct PinnedVec<T> {
        inner: Vec<T>,
    }

    impl<T> Default for PinnedVec<T> {
        fn default() -> Self {
            Self::new()
        }
    }

    impl<T: Clone> Clone for PinnedVec<T> {
        fn clone(&self) -> Self {
            Self {
                inner: self.inner.clone(),
            }
        }
    }

    impl<T> PinnedVec<T> {
        pub fn new() -> Self {
            Self { inner: Vec::new() }
        }

        pub fn with_capacity(cap: usize) -> Self {
            Self {
                inner: Vec::with_capacity(cap),
            }
        }

        #[inline]
        pub fn len(&self) -> usize {
            self.inner.len()
        }

        pub fn push(&mut self, value: T) {
            self.inner.push(value)
        }

        pub fn extend_from_slice(&mut self, src: &[T])
        where
            T: Copy,
        {
            self.inner.extend_from_slice(src)
        }

        pub fn truncate(&mut self, new_len: usize) {
            self.inner.truncate(new_len)
        }
    }

    impl<T> Deref for PinnedVec<T> {
        type Target = [T];
        fn deref(&self) -> &[T] {
            &self.inner
        }
    }

    impl<T> DerefMut for PinnedVec<T> {
        fn deref_mut(&mut self) -> &mut [T] {
            &mut self.inner
        }
    }

    impl<T: fmt::Debug> fmt::Debug for PinnedVec<T> {
        fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
            self.inner.fmt(f)
        }
    }
}

pub use imp::PinnedVec;
