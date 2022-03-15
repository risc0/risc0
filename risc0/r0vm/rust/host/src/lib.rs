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

use byte_slice_cast::AsSliceOf;
use log::LevelFilter;
use std::{ffi::CString, fmt::Debug, fmt::Display};

mod exception;
mod ffi;

pub use exception::Exception;

pub type Result<T> = std::result::Result<T, Exception>;

pub struct Proof {
    ptr: *const ffi::RawProof,
}

pub struct Prover {
    ptr: *mut ffi::RawProver,
}

const DIGEST_WORDS: usize = 8;

#[derive(Clone, Copy, Default, Eq, Hash, Ord, PartialOrd, PartialEq)]
pub struct Digest([u32; DIGEST_WORDS]);

impl Digest {
    /// Constructs a new `Digest` from a byte array.
    pub fn new(data: [u32; DIGEST_WORDS]) -> Self {
        Self(data)
    }

    pub fn as_slice(&self) -> &[u32] {
        &self.0
    }
}

impl Display for Digest {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        for byte in self.0 {
            write!(f, "{:02x?}", byte)?;
        }
        Ok(())
    }
}

impl Debug for Digest {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for byte in self.0 {
            write!(f, "{:02x?}", byte)?;
        }
        Ok(())
    }
}

impl TryFrom<&[u8]> for Digest {
    type Error = Exception;

    fn try_from(value: &[u8]) -> Result<Self> {
        let slice = value.as_slice_of().unwrap();
        let mut ret = Digest::new([0; DIGEST_WORDS]);
        ret.0.copy_from_slice(slice);
        Ok(ret)
    }
}

impl Proof {
    pub fn verify(&self, elf_path: &str) -> Result<()> {
        let mut err = ffi::RawError::default();
        let str = CString::new(elf_path).unwrap();
        unsafe { ffi::risc0_proof_verify(&mut err, str.as_ptr(), self.ptr) };
        ffi::check(err, || ())
    }

    pub fn get_core(&self) -> Result<&[u32]> {
        unsafe {
            let mut err = ffi::RawError::default();
            let buf = ffi::risc0_proof_get_core_buf(&mut err, self.ptr);
            let buf = ffi::check(err, || buf)?;
            let mut err = ffi::RawError::default();
            let len = ffi::risc0_proof_get_core_len(&mut err, self.ptr);
            let len = ffi::check(err, || len)?;
            Ok(std::slice::from_raw_parts(buf, len))
        }
    }

    pub fn get_message(&self) -> Result<&[u8]> {
        unsafe {
            let mut err = ffi::RawError::default();
            let buf = ffi::risc0_proof_get_message_buf(&mut err, self.ptr);
            let buf = ffi::check(err, || buf)?;
            let mut err = ffi::RawError::default();
            let len = ffi::risc0_proof_get_message_len(&mut err, self.ptr);
            let len = ffi::check(err, || len)?;
            Ok(std::slice::from_raw_parts(buf, len))
        }
    }
}

impl Prover {
    pub fn new(elf_path: &str) -> Result<Self> {
        let mut err = ffi::RawError::default();
        let str = CString::new(elf_path).unwrap();
        let ptr = unsafe { ffi::risc0_prover_new(&mut err, str.as_ptr()) };
        ffi::check(err, || Prover { ptr })
    }

    pub fn add_input(&mut self, slice: &[u8]) -> Result<()> {
        let mut err = ffi::RawError::default();
        unsafe { ffi::risc0_prover_add_input(&mut err, self.ptr, slice.as_ptr(), slice.len()) };
        ffi::check(err, || ())
    }

    pub fn get_num_outputs(&self) -> Result<usize> {
        let mut err = ffi::RawError::default();
        let len = unsafe { ffi::risc0_prover_get_num_outputs(&mut err, self.ptr) };
        ffi::check(err, || len)
    }

    pub fn get_output(&self, idx: usize, len: usize) -> Result<&[u8]> {
        assert!(idx < self.get_num_outputs()?);
        let mut err = ffi::RawError::default();
        let buf = unsafe { ffi::risc0_prover_get_output(&mut err, self.ptr, idx, len) };
        ffi::check(err, || unsafe { std::slice::from_raw_parts(buf, len) })
    }

    pub fn run(&self) -> Result<Proof> {
        let mut err = ffi::RawError::default();
        let ptr = unsafe { ffi::risc0_prover_run(&mut err, self.ptr) };
        ffi::check(err, || Proof { ptr })
    }
}

impl Drop for Proof {
    fn drop(&mut self) {
        let mut err = ffi::RawError::default();
        unsafe { ffi::risc0_proof_free(&mut err, self.ptr) };
        ffi::check(err, || ()).unwrap()
    }
}

impl Drop for Prover {
    fn drop(&mut self) {
        let mut err = ffi::RawError::default();
        unsafe { ffi::risc0_prover_free(&mut err, self.ptr) };
        ffi::check(err, || ()).unwrap()
    }
}

#[ctor::ctor]
fn init() {
    env_logger::builder().filter_level(LevelFilter::Info).init();
    unsafe { ffi::risc0_init() };
}
