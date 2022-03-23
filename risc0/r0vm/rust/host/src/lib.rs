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

use log::LevelFilter;
use std::{ffi::CString, mem};

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

fn into_words(slice: &[u8]) -> Result<Vec<u32>> {
    log::info!("into_words: {}, {:02x?}", slice.len(), slice);
    let mut vec = Vec::new();
    let chunks = slice.chunks_exact(4);
    assert!(chunks.remainder().len() == 0);
    for chunk in chunks {
        let word = chunk[0] as u32
            | (chunk[1] as u32) << 8
            | (chunk[2] as u32) << 16
            | (chunk[3] as u32) << 24;
        vec.push(word);
    }
    Ok(vec)
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

    pub fn get_message_vec(&self) -> Result<Vec<u32>> {
        into_words(self.get_message()?)
    }
}

impl Prover {
    pub fn new(elf_path: &str) -> Result<Self> {
        let mut err = ffi::RawError::default();
        let str = CString::new(elf_path).unwrap();
        let ptr = unsafe { ffi::risc0_prover_new(&mut err, str.as_ptr()) };
        ffi::check(err, || Prover { ptr })
    }

    pub fn add_input(&mut self, slice: &[u32]) -> Result<()> {
        let mut err = ffi::RawError::default();
        unsafe {
            ffi::risc0_prover_add_input(
                &mut err,
                self.ptr,
                slice.as_ptr().cast(),
                slice.len() * mem::size_of::<u32>(),
            )
        };
        ffi::check(err, || ())
    }

    pub fn get_output(&self) -> Result<&[u8]> {
        unsafe {
            let mut err = ffi::RawError::default();
            let buf = ffi::risc0_prover_get_output_buf(&mut err, self.ptr);
            let buf = ffi::check(err, || buf)?;
            let mut err = ffi::RawError::default();
            let len = ffi::risc0_prover_get_output_len(&mut err, self.ptr);
            let len = ffi::check(err, || len)?;
            Ok(std::slice::from_raw_parts(buf, len))
        }
    }

    pub fn get_output_vec(&self) -> Result<Vec<u32>> {
        into_words(self.get_output()?)
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
