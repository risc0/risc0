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

use core::{cell::UnsafeCell, mem::MaybeUninit, slice};

use risc0_zkp::core::sha::Digest;
use risc0_zkvm::serde::{Deserializer, Serializer, Slice};
// Re-export for easy use by user programs.
#[cfg(target_os = "zkvm")]
pub use risc0_zkvm_platform::rt::host_io::host_sendrecv;
use risc0_zkvm_platform::{
    io::{
        IoDescriptor, GPIO_COMMIT, GPIO_CYCLECOUNT, SENDRECV_CHANNEL_INITIAL_INPUT,
        SENDRECV_CHANNEL_STDOUT,
    },
    memory,
    rt::host_io::host_recv,
    WORD_SIZE,
};
use serde::{Deserialize, Serialize};

use crate::{align_up, memory_barrier, sha};

#[cfg(not(target_os = "zkvm"))]
// Bazel really wants to compile this file for the host too, so provide a stub.
/// Stub version of risc0_zkvm_platform::rt::host_sendrecv, re-exported for
/// easy access through the SDK.
pub fn host_sendrecv(_channel: u32, _buf: &[u8]) -> (&'static [u32], usize) {
    unimplemented!()
}

struct Env {
    output: Serializer<Slice<'static>>,
    commit: Serializer<Slice<'static>>,
    commit_len: usize,
    initial_input_reader: Option<Reader>,
}

struct Once<T> {
    data: UnsafeCell<MaybeUninit<T>>,
}

unsafe impl<T: Send + Sync> Sync for Once<T> {}

/// Reads and deserializes objects from a section of memory.
pub struct Reader(Deserializer<'static>);

impl Reader {
    /// Read private data from the host.
    pub fn read<T: Deserialize<'static>>(&mut self) -> T {
        T::deserialize(&mut self.0).unwrap()
    }
}

impl<T> Once<T> {
    const fn new() -> Self {
        Once {
            data: UnsafeCell::new(MaybeUninit::uninit()),
        }
    }

    fn init(&self, value: T) {
        unsafe { &mut *(self.data.get()) }.write(value);
    }

    fn get(&self) -> &mut T {
        unsafe {
            self.data
                .get()
                .as_mut()
                .unwrap_unchecked()
                .assume_init_mut()
        }
    }
}

static ENV: Once<Env> = Once::new();

pub(crate) fn init() {
    ENV.init(Env::new());
}

pub(crate) fn finalize(result: *mut usize) {
    ENV.get().finalize(result);
}

/// Exchanges data with the host, returning the data from the host
/// as a slice of bytes.
pub fn send_recv(channel: u32, buf: &[u8]) -> &'static [u8] {
    ENV.get().send_recv(channel, buf)
}

/// Exchanges data with the host, returning the data from the host as
/// a slice of words and the length in bytes.
pub fn send_recv_as_u32(channel: u32, buf: &[u8]) -> (&'static [u32], usize) {
    ENV.get().send_recv_as_u32(channel, buf)
}

/// Read private data from the host.
pub fn read<T: Deserialize<'static>>() -> T {
    ENV.get().read()
}

/// Write private data to the host.
pub fn write<T: Serialize>(data: &T) {
    ENV.get().write(data);
}

/// Commit public data to the journal.
pub fn commit<T: Serialize>(data: &T) {
    ENV.get().commit(data);
}

/// Returns the number of processor cycles that have occured since the guest
/// began.
pub fn get_cycle_count() -> usize {
    ENV.get().get_cycle_count()
}

impl Env {
    fn new() -> Self {
        Env {
            commit: Serializer::new(Slice::new(unsafe {
                slice::from_raw_parts_mut(memory::COMMIT.start() as _, memory::COMMIT.len_words())
            })),
            output: Serializer::new(Slice::new(unsafe {
                slice::from_raw_parts_mut(memory::OUTPUT.start() as _, memory::OUTPUT.len_words())
            })),

            commit_len: 0,
            initial_input_reader: None,
        }
    }

    pub fn send_recv_as_u32(&mut self, channel: u32, buf: &[u8]) -> (&'static [u32], usize) {
        host_sendrecv(channel, buf)
    }

    pub fn send_recv(&mut self, channel: u32, buf: &[u8]) -> &'static [u8] {
        let (data, bytes) = self.send_recv_as_u32(channel, buf);
        &bytemuck::cast_slice(data)[..bytes]
    }

    fn initial_input(&mut self) -> &mut Reader {
        if !self.initial_input_reader.is_some() {
            let (words, _) = self.send_recv_as_u32(SENDRECV_CHANNEL_INITIAL_INPUT, &[]);
            self.initial_input_reader = Some(Reader(Deserializer::new(words)))
        }
        self.initial_input_reader.as_mut().unwrap()
    }

    pub fn read<T: Deserialize<'static>>(&mut self) -> T {
        self.initial_input().read()
    }

    fn write<T: Serialize>(&mut self, data: &T) {
        data.serialize(&mut self.output).unwrap();
        let buf = self.output.release().unwrap();
        self.send_recv(SENDRECV_CHANNEL_STDOUT, bytemuck::cast_slice(buf));
    }

    fn commit<T: Serialize>(&mut self, data: &T) {
        data.serialize(&mut self.commit).unwrap();
        let buf = self.commit.release().unwrap();
        self.commit_len += buf.len();
        // Copy to stdout
        self.send_recv(SENDRECV_CHANNEL_STDOUT, bytemuck::cast_slice(buf));
    }

    fn finalize(&mut self, result: *mut usize) {
        let len_words = self.commit_len;
        let len_bytes = len_words * WORD_SIZE;
        let slice: &mut [u32] = unsafe {
            slice::from_raw_parts_mut(memory::COMMIT.start() as _, memory::COMMIT.len_words())
        };

        // Write the full data out to the host
        unsafe {
            let desc = IoDescriptor {
                size: len_bytes as u32,
                addr: slice.as_ptr() as u32,
            };
            let ptr: *const IoDescriptor = &desc;
            memory_barrier(ptr);
            GPIO_COMMIT.as_ptr().write_volatile(&desc);
        }

        // If the total proof message is small (<= 32 bytes), return it directly
        // from the proof, otherwise SHA it and return the hash.
        if len_words <= 8 {
            for i in 0..len_words {
                unsafe {
                    result
                        .add(i)
                        .write_volatile(*slice.get_unchecked(i) as usize)
                };
            }
            for i in len_words..8 {
                unsafe { result.add(i).write_volatile(0) };
            }
        } else {
            let cap = sha::compute_capacity_needed(len_bytes);
            let mut slice = &mut slice[..cap];
            sha::add_trailer(&mut slice, len_bytes, sha::MemoryType::WOM);

            let digest = result as *mut Digest;
            // SAFETY: result is a pointer to the output digest.
            unsafe {
                sha::raw_digest_to(&slice, digest);
            }
        }
        unsafe {
            result.add(8).write_volatile(len_bytes);
            memory_barrier(result);
        };
        sha::finalize();
    }

    fn get_cycle_count(&self) -> usize {
        unsafe { GPIO_CYCLECOUNT.as_ptr().write_volatile(0) }
        match host_recv(1) {
            &[nbytes] => nbytes as usize,
            _ => unreachable!(),
        }
    }
}
