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

use core::{cell::UnsafeCell, default::Default, mem::MaybeUninit, ptr, slice};

use bytemuck::Pod;
use risc0_zkp::core::sha::{Digest, DIGEST_BYTES, DIGEST_WORDS};
use risc0_zkvm_platform::{
    io::{SENDRECV_CHANNEL_INITIAL_INPUT, SENDRECV_CHANNEL_JOURNAL, SENDRECV_CHANNEL_STDOUT},
    memory,
    syscall::{sys_cycle_count, sys_halt, sys_io, sys_log, sys_output},
    WORD_SIZE,
};
use serde::{Deserialize, Serialize};

use crate::{
    guest::{align_up, memory_barrier, sha},
    serde::{Deserializer, Result as SerdeResult, Serializer, StreamWriter},
    sha::rust_crypto::{Digest as _, Output, Sha256},
};

struct Once<T> {
    data: UnsafeCell<MaybeUninit<T>>,
}

unsafe impl<T: Send + Sync> Sync for Once<T> {}

impl<T: Default> Once<T> {
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
static mut HASHER: Option<Sha256> = None;

/// Reads and deserializes objects from a section of memory.
struct Reader(Deserializer<'static>);

impl Reader {
    /// Read private data from the host.
    pub fn read<T: Deserialize<'static>>(&mut self) -> T {
        T::deserialize(&mut self.0).unwrap()
    }

    /// Read raw private data from the host.
    pub fn read_slice<T: Pod>(&mut self, len: usize) -> &'static [T] {
        bytemuck::cast_slice(self.0.read_bytes(core::mem::size_of::<T>() * len).unwrap())
    }
}

pub(crate) fn init() {
    ENV.init(Env::new());
    unsafe { HASHER = Some(Sha256::new()) };
}

pub(crate) fn finalize() {
    unsafe {
        let hasher = core::mem::take(&mut HASHER);
        let output = hasher.unwrap_unchecked().finalize();
        let words = bytemuck::cast_slice(output.as_slice());
        for i in 0..DIGEST_WORDS {
            sys_output(i as u32, words[i]);
        }
        sys_output(DIGEST_WORDS as u32, DIGEST_BYTES as u32);
        sys_halt()
    }
}

/// Exchange data with the host, returning the data from the host
/// as a slice of bytes.
pub fn send_recv(channel: u32, buf: &[u8]) -> &'static [u8] {
    unsafe { sys_io(channel, buf.as_ptr(), buf.len()) }
}

/// Exchange data with the host, returning the data from the host as
/// a slice of words and the length in bytes.
pub fn send_recv_as_u32(channel: u32, buf: &[u8]) -> &'static [u32] {
    bytemuck::cast_slice(send_recv(channel, buf))
}

/// Read private data from the host and deserializes it.
pub fn read<T: Deserialize<'static>>() -> T {
    ENV.get().read()
}

/// Read a slice from the host.
pub fn read_slice<T: Pod>(len: usize) -> &'static [T] {
    ENV.get().read_slice(len)
}

/// Serialize the given data and write it to the STDOUT channel of the zkVM.
///
/// This is available to the host as the private output on the prover.
/// Some implementations, such as [risc0-r0vm] will also write the data to
/// the host's stdout file descriptor. It is not included in the receipt.
pub fn write<T: Serialize>(data: &T) {
    let mut serializer = Serializer::new(stdout());
    data.serialize(&mut serializer).unwrap();
}

/// Write the given slice to the STDOUT channel of the zkVM.
///
/// This is available to the host as the private output on the prover.
/// Some implementations, such as [risc0-r0vm] will also write the data to
/// the host's stdout file descriptor. It is not included in the receipt.
pub fn write_slice<T: Pod>(slice: &[T]) {
    stdout().write_slice(slice);
}

/// Serialize the given data and commit it to the journal.
///
/// Data in the journal is included in the receipt and is available to the
/// verifier. It is considered "public" data.
pub fn commit<T: Serialize>(data: &T) {
    let mut serializer = Serializer::new(journal());
    data.serialize(&mut serializer).unwrap();
}

/// Commit the given slice to the journal.
///
/// Data in the journal is included in the receipt and is available to the
/// verifier. It is considered "public" data.
pub fn commit_slice<T: Pod>(slice: &[T]) {
    journal().write_slice(slice);
}

/// Return the number of processor cycles that have occured since the guest
/// began.
pub fn get_cycle_count() -> usize {
    unsafe { sys_cycle_count() }
}

/// Print a message to the debug console.
pub fn log(msg: &str) {
    unsafe { sys_log(msg.as_ptr(), msg.len()) };
}

/// Return a StreamWriter on the specified channel.
pub fn get_writer<F: Fn(&[u8])>(channel: u32, hook: F) -> impl StreamWriter {
    OutputStreamWriter::new(channel, hook)
}

/// Return the STDOUT channel.
pub fn stdout() -> impl StreamWriter {
    get_writer(SENDRECV_CHANNEL_STDOUT, |_| {})
}

/// Return the JOURNAL channel.
pub fn journal() -> impl StreamWriter {
    get_writer(SENDRECV_CHANNEL_JOURNAL, |bytes| {
        unsafe { HASHER.as_mut().unwrap_unchecked().update(bytes) };
    })
}

#[derive(Default)]
struct Env {
    initial_input_reader: Option<Reader>,
}

impl Env {
    pub fn new() -> Self {
        Env {
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

    pub fn read_slice<T: Pod>(&mut self, len: usize) -> &'static [T] {
        self.initial_input().read_slice(len)
    }
}

struct OutputStreamWriter<F: Fn(&[u8])> {
    channel: u32,
    hook: F,
}

impl<F: Fn(&[u8])> OutputStreamWriter<F> {
    pub fn new(channel: u32, hook: F) -> Self {
        Self { channel, hook }
    }
}

impl<F: Fn(&[u8])> StreamWriter for OutputStreamWriter<F> {
    type Output = ();

    fn write_u32(&mut self, data: u32) -> SerdeResult<()> {
        let bytes = data.to_ne_bytes();
        unsafe { sys_io(self.channel, bytes.as_ptr(), bytes.len()) };
        (self.hook)(&bytes);
        Ok(())
    }

    fn write_slice<T: Pod>(&mut self, slice: &[T]) -> SerdeResult<()> {
        let bytes: &[u8] = bytemuck::cast_slice(slice);
        unsafe { sys_io(self.channel, bytes.as_ptr(), bytes.len()) };
        (self.hook)(bytes);
        Ok(())
    }

    fn release(&mut self) -> SerdeResult<Self::Output> {
        Ok(())
    }
}
