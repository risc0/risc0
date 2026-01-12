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

use bytemuck::Pod;
use risc0_zkvm_platform::{WORD_SIZE, syscall::sys_write};
use serde::Serialize;

use crate::serde::{Serializer, WordWrite};

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
    /// Creates a new FdWriter writing to the given file descriptor.
    pub fn new(fd: u32, hook: F) -> Self {
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
    fn write_words(&mut self, words: &[u32]) -> crate::serde::Result<()> {
        self.write_bytes(bytemuck::cast_slice(words));
        Ok(())
    }

    fn write_padded_bytes(&mut self, bytes: &[u8]) -> crate::serde::Result<()> {
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
