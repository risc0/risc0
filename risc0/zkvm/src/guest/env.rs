// Copyright 2023 RISC Zero, Inc.
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

//! Functions for interacting with the host environment.

use core::{cell::UnsafeCell, mem::MaybeUninit, ptr, slice};

use risc0_zkp::core::sha::{Digest, DIGEST_WORDS, SHA256_INIT};
use risc0_zkvm_platform::{
    io::{SENDRECV_CHANNEL_INITIAL_INPUT, SENDRECV_CHANNEL_STDOUT},
    memory,
    syscall::{sys_commit, sys_cycle_count, sys_halt, sys_io, sys_log, sys_output},
    WORD_SIZE,
};
use serde::{Deserialize, Serialize};

use crate::{
    guest::{memory_barrier, sha},
    serde::{Deserializer, Serializer, Slice},
};

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

pub(crate) fn finalize() {
    ENV.get().finalize();
}

/// Exchanges data with the host, returning the data from the host
/// as a slice of bytes.
pub fn send_recv(channel: u32, buf: &[u8]) -> &'static [u8] {
    unsafe { sys_io(channel, buf.as_ptr(), buf.len()) }
}

/// Exchanges data with the host, returning the data from the host as
/// a slice of words and the length in bytes.
pub fn send_recv_as_u32(channel: u32, buf: &[u8]) -> &'static [u32] {
    bytemuck::cast_slice(send_recv(channel, buf))
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
    unsafe { sys_cycle_count() }
}

/// Print a message to the debug console.
pub fn log(msg: &str) {
    unsafe { sys_log(msg.as_ptr(), msg.len()) };
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

    fn initial_input(&mut self) -> &mut Reader {
        if !self.initial_input_reader.is_some() {
            let bytes = send_recv(SENDRECV_CHANNEL_INITIAL_INPUT, &[]);
            let words = bytemuck::cast_slice(bytes);
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
        send_recv(SENDRECV_CHANNEL_STDOUT, bytemuck::cast_slice(buf));
    }

    fn commit<T: Serialize>(&mut self, data: &T) {
        data.serialize(&mut self.commit).unwrap();
        let buf = self.commit.release().unwrap();
        self.commit_len += buf.len();
        // Copy to stdout
        send_recv(SENDRECV_CHANNEL_STDOUT, bytemuck::cast_slice(buf));
    }

    fn finalize(&mut self) {
        let len_words = self.commit_len;
        let len_bytes = len_words * WORD_SIZE;
        let slice: &[u32] =
            unsafe { slice::from_raw_parts(memory::COMMIT.start() as _, len_words) };

        // Write the full data out to the host
        // NOTE: This is somewhat redundant with the sending of the committed data to
        // the STDOUT channel. We should consider eliminating the write of commit data
        // to STDOUT and instead only commit it via the sys_commit call.
        unsafe { sys_commit(slice.as_ptr(), len_bytes) };

        let mut output = Digest::from([0u32; DIGEST_WORDS]);

        // If the total proof message is small (<= 32 bytes), return it directly
        // from the proof, otherwise SHA it and return the hash.
        if len_words <= 8 {
            let output = output.as_mut_words();
            for i in 0..len_words {
                output[i] = slice[i];
            }
        } else {
            let ptr: *mut Digest = &mut output;
            // NOTE: Hashing here without the standard SHA-256 trailer, instead only padding
            // with zeroes up to the next block boundary saves a copy when the
            // data length is within 9 bytes of the block boundary. As a
            // drawback, it creates an ambiguity of what was committed among messages with
            // some number of trailing zeros. (e.g. between the byte string 0xda7a and
            // 0xda7a0000) Adding (and checking in the verifier) the length of the committed
            // data resolves this issue.
            sha::update_u32(ptr, &SHA256_INIT, slice, sha::WithoutTrailer);
        }
        let output = output.as_words();
        unsafe {
            for i in 0..DIGEST_WORDS {
                sys_output(i as u32, output[i]);
            }
            sys_output(DIGEST_WORDS as u32, len_bytes as u32);
            sys_halt()
        }
    }
}
