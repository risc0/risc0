// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! GPU buffer implementation for cubecl HAL backend.

use std::{cell::RefCell, marker::PhantomData, rc::Rc};

use cubecl::{cuda::CudaRuntime, prelude::*, server::Handle};

use crate::hal::{Buffer, tracker};

/// Internal allocation tracking for shared GPU memory.
struct Alloc {
    name: &'static str,
    handle: Handle,
    total_bytes: usize,
}

impl Drop for Alloc {
    fn drop(&mut self) {
        tracing::trace!("free: {} bytes, {}", self.total_bytes, self.name);
        tracker().lock().unwrap().free(self.total_bytes);
    }
}

/// GPU buffer wrapping a cubecl memory handle.
///
/// Multiple `CubeClBuffer`s can share the same underlying allocation via `Rc`,
/// supporting zero-copy slicing (like CudaHal's BufferImpl pattern).
pub struct CubeClBuffer<T> {
    alloc: Rc<RefCell<Alloc>>,
    client: ComputeClient<CudaRuntime>,
    size: usize,
    offset: usize,
    marker: PhantomData<T>,
}

impl<T> CubeClBuffer<T> {
    /// Create a new uninitialized buffer of `size` elements.
    pub fn new(
        name: &'static str,
        size: usize,
        client: ComputeClient<CudaRuntime>,
    ) -> Self {
        let total_bytes = size * std::mem::size_of::<T>();
        assert!(total_bytes > 0, "cannot allocate zero-size buffer: {name}");
        tracing::trace!("alloc: {total_bytes} bytes, {name}");
        tracker().lock().unwrap().alloc(total_bytes);
        let handle = client.empty(total_bytes);
        CubeClBuffer {
            alloc: Rc::new(RefCell::new(Alloc {
                name,
                handle,
                total_bytes,
            })),
            client,
            size,
            offset: 0,
            marker: PhantomData,
        }
    }

    /// Create a buffer initialized from a host slice.
    pub fn from_slice(
        name: &'static str,
        slice: &[T],
        client: ComputeClient<CudaRuntime>,
    ) -> Self {
        let total_bytes = std::mem::size_of_val(slice);
        assert!(total_bytes > 0, "cannot allocate zero-size buffer: {name}");
        tracing::trace!("alloc: {total_bytes} bytes, {name}");
        tracker().lock().unwrap().alloc(total_bytes);
        let bytes = unsafe {
            std::slice::from_raw_parts(slice.as_ptr() as *const u8, total_bytes)
        };
        let handle = client.create_from_slice(bytes);
        CubeClBuffer {
            alloc: Rc::new(RefCell::new(Alloc {
                name,
                handle,
                total_bytes,
            })),
            client,
            size: slice.len(),
            offset: 0,
            marker: PhantomData,
        }
    }

    /// Get a handle suitable for kernel launch, with offset applied.
    pub fn handle(&self) -> Handle {
        let alloc = self.alloc.borrow();
        let byte_offset = self.offset * std::mem::size_of::<T>();
        let handle = alloc.handle.clone();
        if byte_offset > 0 {
            handle.offset_start(byte_offset as u64)
        } else {
            handle
        }
    }

    /// Get the element count.
    pub fn len(&self) -> usize {
        self.size
    }
}

impl<T: Clone> Clone for CubeClBuffer<T> {
    fn clone(&self) -> Self {
        CubeClBuffer {
            alloc: self.alloc.clone(),
            client: self.client.clone(),
            size: self.size,
            offset: self.offset,
            marker: PhantomData,
        }
    }
}

impl<T: Clone> Buffer<T> for CubeClBuffer<T> {
    fn name(&self) -> &'static str {
        self.alloc.borrow().name
    }

    fn size(&self) -> usize {
        self.size
    }

    fn slice(&self, offset: usize, size: usize) -> Self {
        assert!(
            offset + size <= self.size,
            "slice out of bounds: offset={offset} size={size} buf_size={}",
            self.size
        );
        CubeClBuffer {
            alloc: self.alloc.clone(),
            client: self.client.clone(),
            size,
            offset: self.offset + offset,
            marker: PhantomData,
        }
    }

    fn get_at(&self, idx: usize) -> T {
        assert!(idx < self.size, "get_at out of bounds: idx={idx} size={}", self.size);
        let mut result = None;
        self.view(|slice| {
            result = Some(slice[idx].clone());
        });
        result.unwrap()
    }

    fn view<F: FnOnce(&[T])>(&self, f: F) {
        // Read the full allocation from device
        let alloc = self.alloc.borrow();
        let bytes = self.client.read_one(alloc.handle.clone());
        drop(alloc);

        // Reinterpret as T slice and apply offset
        let all_elems = unsafe {
            let ptr = bytes.as_ptr() as *const T;
            let len = bytes.len() / std::mem::size_of::<T>();
            std::slice::from_raw_parts(ptr, len)
        };
        f(&all_elems[self.offset..self.offset + self.size]);
    }

    fn view_mut<F: FnOnce(&mut [T])>(&self, f: F) {
        // Read the full allocation from device
        let alloc = self.alloc.borrow();
        let bytes = self.client.read_one(alloc.handle.clone());
        drop(alloc);

        // Reinterpret as mutable T slice
        let mut host_buf = bytes;
        let all_elems = unsafe {
            let ptr = host_buf.as_mut_ptr() as *mut T;
            let len = host_buf.len() / std::mem::size_of::<T>();
            std::slice::from_raw_parts_mut(ptr, len)
        };

        // Apply user function to the relevant portion
        f(&mut all_elems[self.offset..self.offset + self.size]);

        // Write back the full buffer by creating a new handle
        let new_handle = self.client.create_from_slice(&host_buf);
        let mut alloc = self.alloc.borrow_mut();
        // Note: the old handle gets dropped, freeing old GPU memory.
        // We don't update the memory tracker since the size is the same.
        alloc.handle = new_handle;
    }

    fn to_vec(&self) -> Vec<T> {
        let mut result = Vec::new();
        self.view(|slice| {
            result = slice.to_vec();
        });
        result
    }
}
