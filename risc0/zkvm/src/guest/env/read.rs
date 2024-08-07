// Copyright 2024 RISC Zero, Inc.
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

use bytemuck::Pod;
use risc0_zkvm_platform::{
    syscall::{sys_read, sys_read_words},
    WORD_SIZE,
};
use serde::de::DeserializeOwned;

use crate::serde::{Deserializer, WordRead};

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
    fn read_words(&mut self, words: &mut [u32]) -> crate::serde::Result<()> {
        let nread_bytes = unsafe { sys_read_words(self.fd, words.as_mut_ptr(), words.len()) };
        if nread_bytes == words.len() * WORD_SIZE {
            Ok(())
        } else {
            Err(crate::serde::Error::DeserializeUnexpectedEnd)
        }
    }

    fn read_padded_bytes(&mut self, bytes: &mut [u8]) -> crate::serde::Result<()> {
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
impl WordRead for std::io::BufReader<FdReader> {
    fn read_words(&mut self, words: &mut [u32]) -> crate::serde::Result<()> {
        use std::io::Read;
        let nread_bytes = self
            .read(bytemuck::cast_slice_mut(words))
            .map_err(|_| crate::serde::Error::DeserializeUnexpectedEnd)?;
        if nread_bytes == words.len() * WORD_SIZE {
            Ok(())
        } else {
            Err(crate::serde::Error::DeserializeUnexpectedEnd)
        }
    }

    fn read_padded_bytes(&mut self, bytes: &mut [u8]) -> crate::serde::Result<()> {
        use std::io::Read;
        self.read_exact(bytes)
            .map_err(|_| crate::serde::Error::DeserializeUnexpectedEnd)?;

        let unaligned = bytes.len() % WORD_SIZE;
        if unaligned != 0 {
            let pad_bytes = WORD_SIZE - unaligned;
            let mut padding = [0u8; WORD_SIZE];
            self.read_exact(&mut padding[..pad_bytes])
                .map_err(|_| crate::serde::Error::DeserializeUnexpectedEnd)?;
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
