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

use bytemuck::Pod;
use risc0_zkvm_platform::{
    fileno, syscall,
    syscall::{
        sys_alloc_words, sys_cycle_count, sys_halt, sys_log, sys_pause, sys_read, sys_read_words,
        sys_write, syscall_2, SyscallName,
    },
    WORD_SIZE,
};
use serde::{de::DeserializeOwned, Serialize};

use crate::{
    align_up,
    serde::{Deserializer, Result as SerdeResult, Serializer, WordRead, WordWrite},
    sha::rust_crypto::{Digest as _, Sha256},
};

static mut HASHER: Option<Sha256> = None;

/// A random 16 byte value initialized to random data, provided by the host, on
/// guest start and upon resuming from a pause. Setting this value ensures that
/// the total memory image have at least 128-bits of entropy, preventing
/// information leakage through the post-state digest.
static mut MEMORY_IMAGE_ENTROPY: [u8; 16] = [0u8; 16];

pub(crate) fn init() {
    unsafe { HASHER = Some(Sha256::new()) };
    unsafe { getrandom::getrandom(&mut MEMORY_IMAGE_ENTROPY).unwrap() };
}

pub(crate) fn finalize(halt: bool, user_exit: u8) {
    unsafe {
        let hasher = core::mem::take(&mut HASHER);
        let output = hasher.unwrap_unchecked().finalize();
        let words: &[u32; 8] = bytemuck::cast_slice(output.as_slice()).try_into().unwrap();

        if halt {
            sys_halt(user_exit, words)
        } else {
            sys_pause(user_exit, words)
        }
    }
}

/// Exchange data with the host.
pub fn syscall(syscall: SyscallName, to_host: &[u8], from_host: &mut [u32]) -> syscall::Return {
    unsafe {
        syscall_2(
            syscall,
            from_host.as_mut_ptr(),
            from_host.len(),
            to_host.as_ptr() as u32,
            to_host.len() as u32,
        )
    }
}

/// Exhanges slices of plain old data with the host.
///
/// This makes two calls to the given syscall; the first gets the length of the
/// buffer to allocate for the return data, and the second actually
/// receives the return data.
///
/// On the host side, implement SliceIo to provide a handler for this call.
pub fn send_recv_slice<T: Pod, U: Pod>(syscall_name: SyscallName, to_host: &[T]) -> &'static [U] {
    let syscall::Return(nelem, _) = syscall(syscall_name, bytemuck::cast_slice(to_host), &mut []);
    let nwords = align_up(core::mem::size_of::<T>() * nelem as usize, WORD_SIZE) / WORD_SIZE;
    let from_host_buf = unsafe { core::slice::from_raw_parts_mut(sys_alloc_words(nwords), nwords) };
    syscall(syscall_name, &[], from_host_buf);
    &bytemuck::cast_slice(from_host_buf)[..nelem as usize]
}

/// Read private data from the host and deserializes it.
pub fn read<T: DeserializeOwned>() -> T {
    stdin().read()
}

/// Read a slice from the host.
pub fn read_slice<T: Pod>(slice: &mut [T]) {
    stdin().read_slice(slice)
}

/// Serialize the given data and write it to the STDOUT of the zkVM.
///
/// This is available to the host as the private output on the prover.
/// Some implementations, such as [risc0-r0vm] will also write the data to
/// the host's stdout file descriptor. It is not included in the receipt.
pub fn write<T: Serialize>(data: &T) {
    stdout().write(data)
}

/// Write the given slice to the STDOUT of the zkVM.
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
    journal().write(data)
}

/// Commit the given slice to the journal.
///
/// Data in the journal is included in the receipt and is available to the
/// verifier. It is considered "public" data.
pub fn commit_slice<T: Pod>(slice: &[T]) {
    journal().write_slice(slice);
}

/// Return the number of processor cycles that have occurred since the guest
/// began.
pub fn get_cycle_count() -> usize {
    sys_cycle_count()
}

/// Print a message to the debug console.
pub fn log(msg: &str) {
    let msg = msg.as_bytes();
    unsafe {
        sys_log(msg.as_ptr(), msg.len());
    }
}

/// Return a writer for STDOUT.
pub fn stdout() -> FdWriter<impl for<'a> Fn(&'a [u8])> {
    FdWriter::new(fileno::STDOUT, |_| {})
}

/// Return a writer for STDERR.
pub fn stderr() -> FdWriter<impl for<'a> Fn(&'a [u8])> {
    FdWriter::new(fileno::STDERR, |_| {})
}

/// Return a writer for the JOURNAL.
pub fn journal() -> FdWriter<impl for<'a> Fn(&'a [u8])> {
    FdWriter::new(fileno::JOURNAL, |bytes| {
        unsafe { HASHER.as_mut().unwrap_unchecked().update(bytes) };
    })
}

/// Reaturn a reader for the standard input
pub fn stdin() -> FdReader {
    FdReader::new(fileno::STDIN)
}

/// Pause the execution of the zkvm.
///
/// Execution may be continued at a later time.
pub fn pause() {
    finalize(false, 0);
    init();
}

/// Reads and deserializes objects
pub trait Read {
    /// Read data from the host.
    fn read<T: DeserializeOwned>(&mut self) -> T;

    /// Read raw data from the host.
    fn read_slice<T: Pod>(&mut self, buf: &mut [T]);
}

impl<R: Read + ?Sized> Read for &mut R {
    fn read<T: DeserializeOwned>(&mut self) -> T {
        (**self).read()
    }

    fn read_slice<T: Pod>(&mut self, buf: &mut [T]) {
        (**self).read_slice(buf)
    }
}

/// Provides a FdReader which can read from any file descriptor
pub struct FdReader {
    fd: u32,
}

impl FdReader {
    /// Creates a new FdReader reading from the given file descriptor.
    pub fn new(fd: u32) -> FdReader {
        FdReader { fd }
    }

    #[must_use = "read_bytes can potentially do a short read; this case should be handled."]
    fn read_bytes(&mut self, buf: &mut [u8]) -> usize {
        unsafe { sys_read(self.fd, buf.as_mut_ptr(), buf.len()) }
    }

    // Like read_bytes, but fills the buffer completely or until EOF occurs.
    #[must_use = "read_bytes_all can potentially return EOF; this case should be handled."]
    fn read_bytes_all(&mut self, mut buf: &mut [u8]) -> usize {
        let mut tot_read = 0;
        while !buf.is_empty() {
            let nread = self.read_bytes(buf);
            if nread == 0 {
                break;
            }
            tot_read += nread;
            (_, buf) = buf.split_at_mut(nread);
        }

        tot_read
    }
}

impl Read for FdReader {
    fn read<T: DeserializeOwned>(&mut self) -> T {
        T::deserialize(&mut Deserializer::new(self)).unwrap()
    }

    fn read_slice<T: Pod>(&mut self, buf: &mut [T]) {
        if let Ok(words) = bytemuck::try_cast_slice_mut(buf) {
            // Reading words performs significantly better if we're word aligned.
            self.read_words(words).unwrap();
        } else {
            let bytes = bytemuck::cast_slice_mut(buf);
            if self.read_bytes_all(bytes) != bytes.len() {
                panic!("{:?}", crate::serde::Error::DeserializeUnexpectedEnd);
            }
        }
    }
}

impl WordRead for FdReader {
    fn read_words(&mut self, words: &mut [u32]) -> SerdeResult<()> {
        let nread_bytes = unsafe { sys_read_words(self.fd, words.as_mut_ptr(), words.len()) };
        if nread_bytes == words.len() * WORD_SIZE {
            Ok(())
        } else {
            Err(crate::serde::Error::DeserializeUnexpectedEnd)
        }
    }

    fn read_padded_bytes(&mut self, bytes: &mut [u8]) -> SerdeResult<()> {
        if self.read_bytes_all(bytes) != bytes.len() {
            return Err(crate::serde::Error::DeserializeUnexpectedEnd);
        }

        let unaligned = bytes.len() % WORD_SIZE;
        if unaligned != 0 {
            let pad_bytes = WORD_SIZE - unaligned;
            let mut padding = [0u8; WORD_SIZE];
            if self.read_bytes_all(&mut padding[..pad_bytes]) != pad_bytes {
                return Err(crate::serde::Error::DeserializeUnexpectedEnd);
            }
        }
        Ok(())
    }
}

#[cfg(feature = "std")]
impl std::io::Read for FdReader {
    fn read(&mut self, buf: &mut [u8]) -> std::io::Result<usize> {
        Ok(self.read_bytes(buf))
    }
}

/// Serializes and writes objects.
pub trait Write {
    /// Write a serialized object.
    fn write<T: Serialize>(&mut self, val: T);

    /// Write raw data.
    fn write_slice<T: Pod>(&mut self, buf: &[T]);
}

impl<W: Write + ?Sized> Write for &mut W {
    fn write<T: Serialize>(&mut self, val: T) {
        (**self).write(val)
    }

    fn write_slice<T: Pod>(&mut self, buf: &[T]) {
        (**self).write_slice(buf)
    }
}

/// Provides a FdWriter which can write to any file descriptor.
pub struct FdWriter<F: Fn(&[u8])> {
    fd: u32,
    hook: F,
}

impl<F: Fn(&[u8])> FdWriter<F> {
    fn new(fd: u32, hook: F) -> Self {
        FdWriter { fd, hook }
    }

    fn write_bytes(&mut self, bytes: &[u8]) {
        unsafe { sys_write(self.fd, bytes.as_ptr(), bytes.len()) }
        (self.hook)(bytes);
    }
}

impl<F: Fn(&[u8])> Write for FdWriter<F> {
    fn write<T: Serialize>(&mut self, val: T) {
        val.serialize(&mut Serializer::new(self)).unwrap();
    }

    fn write_slice<T: Pod>(&mut self, buf: &[T]) {
        self.write_bytes(bytemuck::cast_slice(buf));
    }
}

impl<F: Fn(&[u8])> WordWrite for FdWriter<F> {
    fn write_words(&mut self, words: &[u32]) -> SerdeResult<()> {
        self.write_bytes(bytemuck::cast_slice(words));
        Ok(())
    }

    fn write_padded_bytes(&mut self, bytes: &[u8]) -> SerdeResult<()> {
        self.write_bytes(bytes);
        let unaligned = bytes.len() % WORD_SIZE;
        if unaligned != 0 {
            let pad_bytes = WORD_SIZE - unaligned;
            self.write_bytes(&[0u8; WORD_SIZE][..pad_bytes]);
        }
        Ok(())
    }
}

#[cfg(feature = "std")]
impl<F: Fn(&[u8])> std::io::Write for FdWriter<F> {
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
        self.write_bytes(buf);
        Ok(buf.len())
    }

    fn flush(&mut self) -> std::io::Result<()> {
        Ok(())
    }
}
