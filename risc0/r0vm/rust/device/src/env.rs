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

use _alloc::boxed::Box;
use core::{mem, ptr::null_mut};

use crate::{
    gpio::{IoDescriptor, GPIO_COMMIT, GPIO_DESC_IO, GPIO_LOG, GPIO_WRITE},
    sha::{self, Digest, SHA256},
    REGION_INPUT_START,
};

struct Env {
    message: SHA256,
    read_ptr: *const u8,
}

static mut ENV: *mut Env = null_mut();

fn env() -> &'static Env {
    unsafe { &*ENV }
}

fn env_mut() -> &'static mut Env {
    unsafe { &mut *ENV }
}

pub(crate) fn init() {
    let mut env = Env::new();
    unsafe { ENV = &mut env };
}

pub(crate) fn finalize(result: *mut usize) {
    env_mut().finalize(result);
}

pub fn read<T>() -> T {
    env_mut().read()
}

pub fn write<T>(data: &T) {
    env().write(data);
}

pub fn commit<T>(data: &T) {
    env_mut().commit(data);
}

pub fn commit_digest(data: &Box<Digest>) {
    env_mut().commit_digest(data);
}

pub fn read_slice<T>() -> &'static [T] {
    env_mut().read_slice()
}

pub fn write_slice<T>(slice: &[T]) {
    env().write_slice(slice);
}

pub fn print(msg: &str) {
    unsafe {
        GPIO_DESC_IO.write_volatile(IoDescriptor {
            size: msg.len(),
            addr: msg.as_ptr() as usize,
        });
        GPIO_LOG.write_volatile(GPIO_DESC_IO);
    }
}

impl Env {
    fn new() -> Self {
        Env {
            message: SHA256::with_capacity(256 * 1024),
            read_ptr: REGION_INPUT_START as _,
        }
    }

    fn read<T>(&mut self) -> T {
        let ptr: *const T = self.read_ptr.cast();
        let obj = unsafe {
            self.read_ptr = self.read_ptr.add(mem::size_of::<T>());
            ptr.read_volatile()
        };
        obj
    }

    fn write<T>(&self, data: &T) {
        let ptr: *const T = data;
        unsafe {
            GPIO_DESC_IO.write_volatile(IoDescriptor {
                size: mem::size_of::<T>(),
                addr: ptr as usize,
            });
            GPIO_WRITE.write_volatile(GPIO_DESC_IO);
        }
    }

    fn commit<T>(&mut self, data: &T) {
        self.write(data);
        self.message.update(data);
    }

    fn read_slice<T>(&mut self) -> &[T] {
        let size: usize = self.read();
        let ptr: *const T = self.read_ptr.cast();
        unsafe {
            self.read_ptr = self.read_ptr.add(size);
            core::slice::from_raw_parts(ptr, size / mem::size_of::<T>())
        }
    }

    fn write_slice<T>(&self, slice: &[T]) {
        unsafe {
            GPIO_DESC_IO.write_volatile(IoDescriptor {
                size: slice.len() * mem::size_of::<T>(),
                addr: slice.as_ptr() as usize,
            });
            GPIO_WRITE.write_volatile(GPIO_DESC_IO);
        }
    }

    fn commit_digest(&mut self, digest: &Box<Digest>) {
        self.write_slice(&digest.words);
        self.message.update_slice(&digest.words);
    }

    fn finalize(&mut self, result: *mut usize) {
        let (slice_ptr, len_bytes) = {
            let slice = self.message.storage.as_slice();
            // Write the full data out to the host
            unsafe {
                GPIO_DESC_IO.write_volatile(IoDescriptor {
                    size: slice.len(),
                    addr: slice.as_ptr() as usize,
                });
                GPIO_COMMIT.write_volatile(GPIO_DESC_IO);
            }

            (slice.as_ptr(), slice.len())
        };

        // If the total proof message is small (<= 32 bytes), return it directly
        // from the proof, otherwise SHA it and return the hash.
        if len_bytes <= 32 {
            let ptr = result as *mut u8;
            unsafe { ptr.copy_from_nonoverlapping(slice_ptr, len_bytes) };
        } else {
            let digest = self.message.finalize();
            let src = digest.words.as_ptr();
            let len = digest.words.len();
            unsafe { result.copy_from_nonoverlapping(src, len) };
        }
        unsafe { result.add(8).write_volatile(len_bytes) };
        sha::finalize();
    }
}
