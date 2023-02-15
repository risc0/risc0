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

use risc0_zkp::core::sha::{Digest, DIGEST_BYTES, DIGEST_WORDS, SHA256_INIT};
use risc0_zkvm_platform::{
    io::{SENDRECV_CHANNEL_INITIAL_INPUT, SENDRECV_CHANNEL_STDOUT},
    memory,
    syscall::{sys_commit, sys_cycle_count, sys_halt, sys_io, sys_log, sys_output},
    WORD_SIZE,
};
use serde::{Deserialize, Serialize};

use crate::{
    guest::{align_up, memory_barrier, sha},
    serde::{serializer::StreamWriter, CommitHasher, Committer, Deserializer, Serializer, Slice},
};

struct Env {
    output: Serializer<Slice<'static>>,
    commit: Serializer<CommitHasher<sha::Impl, SyscallCommitter>>,
    initial_input_reader: Option<Reader>,
}

#[derive(Default, Debug)]
struct SyscallCommitter {}

impl Committer for SyscallCommitter {
    fn commit(&mut self, data: &[u32]) {
        unsafe { sys_commit(data.as_ptr(), data.len() * WORD_SIZE) };
    }
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

    /// TODO(victor) Add doc string.
    pub fn bytes_remaining(&mut self) -> usize {
        self.0.slice.len() * WORD_SIZE
    }

    /// TODO(victor) Add doc string.
    pub fn words_remaining(&mut self) -> usize {
        self.0.slice.len()
    }

    /// TODO(victor) Add doc string.
    pub fn read_bytes(&mut self, len: usize) -> crate::serde::err::Result<&'static [u8]> {
        self.0.try_take_n_bytes(len)
    }

    /// TODO(victor) Add doc string.
    pub fn read_words(&mut self, len: usize) -> crate::serde::err::Result<&'static [u32]> {
        self.0.try_take_n(len)
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

/// TODO(victor) Add doc string.
pub fn read_bytes(len: usize) -> crate::serde::err::Result<&'static [u8]> {
    ENV.get().read_bytes(len)
}

/// TODO(victor) Add doc string.
pub fn read_words(len: usize) -> crate::serde::err::Result<&'static [u32]> {
    ENV.get().read_words(len)
}

/// TODO(victor) Add doc string.
pub fn input_bytes_remaining() -> usize {
    ENV.get().input_bytes_remaining()
}

/// TODO(victor) Add doc string.
pub fn input_words_remaining() -> usize {
    ENV.get().input_words_remaining()
}

/// Writes the serialization of the data to the STDOUT channel of the zkVM.
///
/// This is availble to the host as the private output on the prover.
/// Some hosts, such that the [risc0-r0vm] will also write the data to
/// the stdout file descriptor. It is not included in the receipt.
pub fn write<T: Serialize>(data: &T) {
    ENV.get().write(data)
}

/// Writes given data bytes to the STDOUT channel of the zkVM.
///
/// This is availble to the host as the private output on the prover.
/// Some hosts, such that the [risc0-r0vm] will also write the data to
/// the stdout file descriptor. It is not included in the receipt.
pub fn write_bytes(data: &[u8]) {
    ENV.get().write_bytes(data)
}

/// Writes given data words to the STDOUT channel of the zkVM.
///
/// This is availble to the host as the private output on the prover.
/// Some hosts, such that the [risc0-r0vm] will also write the data to
/// the stdout file descriptor. It is not included in the receipt.
pub fn write_words(data: &[u32]) {
    ENV.get().write_words(data)
}

/// Commits the serialization of the data to the journal.
///
/// Data in the journal is included in the receipt and is available to the
/// verifier. It is condiered "public" data.
pub fn commit<T: Serialize>(data: &T) {
    ENV.get().commit(data)
}

/// Commits the given data bytes to the journal.
///
/// Data in the journal is included in the receipt and is available to the
/// verifier. It is condiered "public" data.
pub fn commit_bytes(data: &[u8]) {
    ENV.get().commit_bytes(data)
}

/// Commits the given data words to the journal.
///
/// Data in the journal is included in the receipt and is available to the
/// verifier. It is condiered "public" data.
pub fn commit_words(data: &[u32]) {
    ENV.get().commit_words(data)
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
    pub fn new() -> Self {
        Env {
            commit: Serializer::new(CommitHasher::<sha::Impl, SyscallCommitter>::default()),
            output: Serializer::new(Slice::new(unsafe {
                slice::from_raw_parts_mut(memory::OUTPUT.start() as _, memory::OUTPUT.len_words())
            })),

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

    pub fn read_bytes(&mut self, len: usize) -> crate::serde::err::Result<&'static [u8]> {
        self.initial_input().read_bytes(len)
    }

    pub fn read_words(&mut self, len: usize) -> crate::serde::err::Result<&'static [u32]> {
        self.initial_input().read_words(len)
    }

    pub fn input_bytes_remaining(&mut self) -> usize {
        self.initial_input().bytes_remaining()
    }

    pub fn input_words_remaining(&mut self) -> usize {
        self.initial_input().words_remaining()
    }

    pub fn write<T: Serialize>(&mut self, data: &T) {
        data.serialize(&mut self.output).unwrap();
        let buf = self.output.release().unwrap();
        send_recv(SENDRECV_CHANNEL_STDOUT, bytemuck::cast_slice(buf));
    }

    pub fn write_bytes(&mut self, data: &[u8]) {
        send_recv(SENDRECV_CHANNEL_STDOUT, data);
    }

    pub fn write_words(&mut self, data: &[u32]) {
        send_recv(SENDRECV_CHANNEL_STDOUT, bytemuck::cast_slice(data));
    }

    pub fn commit<T: Serialize>(&mut self, data: &T) {
        data.serialize(&mut self.commit).unwrap();
    }

    pub fn commit_bytes(&mut self, data: &[u8]) {
        self.commit.stream.try_extend(data).unwrap();
    }

    pub fn commit_words(&mut self, data: &[u32]) {
        self.commit
            .stream
            .try_extend(bytemuck::cast_slice(data))
            .unwrap();
    }

    pub fn finalize(&mut self) {
        // TODO(victor) Remove the length field.
        let output = self.commit.release().unwrap();
        unsafe {
            for i in 0..DIGEST_WORDS {
                sys_output(i as u32, output.as_words()[i]);
            }
            sys_output(DIGEST_WORDS as u32, DIGEST_BYTES as u32);
            sys_halt()
        }
    }
}
