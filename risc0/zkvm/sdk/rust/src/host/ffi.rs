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

use serde::{Deserialize, Deserializer, Serialize, Serializer};
use std::{ffi::CStr, mem, os::raw::c_char};

use super::exception::Exception;

pub(crate) enum RawString {}
pub(crate) enum RawProver {}
pub(crate) enum RawReceipt {}
pub(crate) enum RawMethodId {}

#[repr(C)]
pub(crate) struct RawError {
    msg: *const RawString,
}

impl Default for RawError {
    fn default() -> Self {
        Self {
            msg: std::ptr::null(),
        }
    }
}

#[inline]
pub(crate) fn check<T, F>(err: RawError, ok: F) -> super::Result<T>
where
    F: FnOnce() -> T,
{
    if err.msg.is_null() {
        Ok(ok())
    } else {
        let what = unsafe {
            let str = risc0_string_ptr(err.msg);
            let msg = CStr::from_ptr(str).to_str().unwrap().to_string();
            risc0_string_free(err.msg);
            msg
        };
        Err(Exception { what })
    }
}

extern "C" {
    pub(crate) fn risc0_init();

    pub(crate) fn risc0_string_ptr(str: *const RawString) -> *const c_char;

    pub(crate) fn risc0_string_free(str: *const RawString);

    pub(crate) fn risc0_method_id_compute(
        err: *mut RawError,
        elf_contents: *const u8,
        elf_len: usize,
        limit: u32,
    ) -> *const RawMethodId;

    pub(crate) fn risc0_method_id_load(
        err: *mut RawError,
        bytes: *const u8,
        len: usize,
    ) -> *const RawMethodId;

    pub(crate) fn risc0_method_id_get_buf(
        err: *mut RawError,
        ptr: *const RawMethodId,
        len: *mut u32,
    ) -> *const u8;

    pub(crate) fn risc0_method_id_free(err: *mut RawError, ptr: *const RawMethodId);

    pub(crate) fn risc0_prover_new(
        err: *mut RawError,
        elf_bytes: *const u8,
        elf_len: usize,
        method_id: *const u8,
        method_id_len: usize,
    ) -> *mut RawProver;

    pub(crate) fn risc0_prover_free(err: *mut RawError, prover: *mut RawProver);

    pub(crate) fn risc0_prover_add_input(
        err: *mut RawError,
        prover: *mut RawProver,
        buf: *const u8,
        len: usize,
    );

    pub(crate) fn risc0_prover_get_output_buf(
        err: *mut RawError,
        prover: *mut RawProver,
    ) -> *const u8;

    pub(crate) fn risc0_prover_get_output_len(err: *mut RawError, prover: *mut RawProver) -> usize;

    pub(crate) fn risc0_prover_run(err: *mut RawError, prover: *mut RawProver)
        -> *const RawReceipt;

    pub(crate) fn risc0_prover_run_without_seal(
        err: *mut RawError,
        prover: *mut RawProver,
    ) -> *const RawReceipt;

    pub(crate) fn risc0_receipt_new(
        err: *mut RawError,
        journal: *const u8,
        journal_len: usize,
        seal: *const u32,
        seal_len: usize,
    ) -> *const RawReceipt;

    pub(crate) fn risc0_receipt_verify(
        err: *mut RawError,
        receipt: *const RawReceipt,
        method_id: *const u8,
        method_id_len: usize,
    );

    pub(crate) fn risc0_receipt_get_seal_buf(
        err: *mut RawError,
        receipt: *const RawReceipt,
    ) -> *mut u32;

    pub(crate) fn risc0_receipt_get_seal_len(
        err: *mut RawError,
        receipt: *const RawReceipt,
    ) -> usize;

    pub(crate) fn risc0_receipt_get_journal_buf(
        err: *mut RawError,
        receipt: *const RawReceipt,
    ) -> *const u8;

    pub(crate) fn risc0_receipt_get_journal_len(
        err: *mut RawError,
        receipt: *const RawReceipt,
    ) -> usize;

    pub(crate) fn risc0_receipt_free(err: *mut RawError, receipt: *const RawReceipt);
}

/// A record attesting to the correct execution of a 'method'.
///
/// Consists of:
/// * journal: all data the method wants to publicly output and commit to.
/// * seal: the cryptographic blob which proves that the receipt is valid.
pub struct Receipt {
    ptr: *const RawReceipt,
}

/// The prover generates a [Receipt] by executing a given method in a ZKVM.
pub struct Prover {
    ptr: *mut RawProver,
    opts: ProverOpts,
}

/// Options available to modify the prover's behavior.
#[non_exhaustive]
#[derive(Default, Debug, Clone, Copy)]
pub struct ProverOpts {
    /// Skip generating the seal in receipt.  This should only be used
    /// for testing.  In this case, performace will be much better but
    /// we will not be able to cryptographically verify the execution.
    pub skip_seal: bool,
}

/// A MethodId represents a unique identifier associated with a particular ELF
/// binary.
pub struct MethodId {
    ptr: *const RawMethodId,
}

fn into_words(slice: &[u8]) -> super::Result<Vec<u32>> {
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

impl MethodId {
    /// Compute the MethodId associated with an existing ELF binary.
    pub fn compute(elf_contents: &[u8]) -> super::Result<Self> {
        use crate::method_id::DEFAULT_METHOD_ID_LIMIT;
        Self::compute_with_limit(elf_contents, DEFAULT_METHOD_ID_LIMIT)
    }

    /// Compute the MethodId associated with an existing ELF binary.
    pub fn compute_with_limit(elf_contents: &[u8], limit: u32) -> super::Result<Self> {
        let mut err = RawError::default();
        let ptr = unsafe {
            risc0_method_id_compute(&mut err, elf_contents.as_ptr(), elf_contents.len(), limit)
        };
        check(err, || MethodId { ptr })
    }

    /// Load an existing MethodId from a buffer.
    pub fn from_slice(slice: &[u8]) -> super::Result<Self> {
        let mut err = RawError::default();
        let ptr = unsafe { risc0_method_id_load(&mut err, slice.as_ptr(), slice.len()) };
        check(err, || MethodId { ptr })
    }

    /// Access the raw slice of a MethodId.
    pub fn as_slice(&self) -> super::Result<&[u8]> {
        let mut err = RawError::default();
        let mut len: u32 = 0;
        let ptr = unsafe { risc0_method_id_get_buf(&mut err, self.ptr, &mut len) };
        check(err, || unsafe {
            std::slice::from_raw_parts(ptr, len as usize)
        })
    }
}

impl Clone for MethodId {
    fn clone(&self) -> Self {
        MethodId::from_slice(self.as_slice().unwrap()).unwrap()
    }
}

impl PartialEq for MethodId {
    fn eq(&self, other: &Self) -> bool {
        self.as_slice().unwrap() == other.as_slice().unwrap()
    }
}

impl Drop for MethodId {
    fn drop(&mut self) {
        let mut err = RawError::default();
        unsafe { risc0_method_id_free(&mut err, self.ptr) };
        check(err, || ()).unwrap()
    }
}

impl Receipt {
    /// Construct a new [Receipt] from individual journal and seal parts.
    pub fn new(journal: &[u8], seal: &[u32]) -> super::Result<Self> {
        let mut err = RawError::default();
        let ptr = unsafe {
            risc0_receipt_new(
                &mut err,
                journal.as_ptr(),
                journal.len(),
                seal.as_ptr(),
                seal.len(),
            )
        };
        check(err, || Receipt { ptr })
    }

    /// Verify that the current [Receipt] is a valid result of executing the
    /// method associated with the given method ID in a ZKVM.
    pub fn verify(&self, method_id: &[u8]) -> super::Result<()> {
        let mut err = RawError::default();
        unsafe { risc0_receipt_verify(&mut err, self.ptr, method_id.as_ptr(), method_id.len()) };
        check(err, || ())
    }

    /// Provides access to the `seal` of a [Receipt].
    pub fn get_seal(&self) -> super::Result<&[u32]> {
        unsafe {
            let mut err = RawError::default();
            let buf = risc0_receipt_get_seal_buf(&mut err, self.ptr);
            let buf = check(err, || buf)?;
            let mut err = RawError::default();
            let len = risc0_receipt_get_seal_len(&mut err, self.ptr);
            let len = check(err, || len)?;
            Ok(std::slice::from_raw_parts(buf, len))
        }
    }

    /// Provides access to the `journal` of a [Receipt].
    pub fn get_journal(&self) -> super::Result<&[u8]> {
        unsafe {
            let mut err = RawError::default();
            let buf = risc0_receipt_get_journal_buf(&mut err, self.ptr);
            let buf = check(err, || buf)?;
            let mut err = RawError::default();
            let len = risc0_receipt_get_journal_len(&mut err, self.ptr);
            let len = check(err, || len)?;
            Ok(std::slice::from_raw_parts(buf, len))
        }
    }

    /// Provides access to the `journal` of a [Receipt] as a [`Vec<u32>`].
    pub fn get_journal_vec(&self) -> super::Result<Vec<u32>> {
        into_words(self.get_journal()?)
    }
}

// TODO(nils): Lift "Receipt" from the pure-rust verify implementation so we
// don't have to proxy through this structure.
#[derive(Serialize, Deserialize)]
struct ReceiptData {
    journal: Vec<u8>,
    seal: Vec<u32>,
}

impl Serialize for Receipt {
    /// Generate a serialized version of the whole receipt.
    fn serialize<S: Serializer>(&self, serializer: S) -> std::result::Result<S::Ok, S::Error> {
        let data: ReceiptData = ReceiptData {
            journal: self.get_journal().unwrap().into(),
            seal: self.get_seal().unwrap().into(),
        };
        data.serialize(serializer)
    }
}

impl<'de> Deserialize<'de> for Receipt {
    /// Deserialize a receipt.
    fn deserialize<D>(deserializer: D) -> std::result::Result<Self, D::Error>
    where
        D: Deserializer<'de>,
    {
        let data = ReceiptData::deserialize(deserializer)?;
        Ok(Receipt::new(&data.journal, &data.seal).unwrap())
    }
}

impl Prover {
    /// Create a new [Prover] with the given method (specified via
    /// `elf_contents`) and an associated method ID (specified via
    /// `method_id`).
    pub fn new(elf_contents: &[u8], method_id: &[u8]) -> super::Result<Self> {
        Self::new_with_opts(elf_contents, method_id, ProverOpts::default())
    }

    /// Create a new [Prover] with the given method (specified via
    /// `elf_contents`) and an associated method ID (specified via
    /// `method_id`) and additional options.
    pub fn new_with_opts(
        elf_contents: &[u8],
        method_id: &[u8],
        opts: ProverOpts,
    ) -> super::Result<Self> {
        let mut err = RawError::default();
        let ptr = unsafe {
            risc0_prover_new(
                &mut err,
                elf_contents.as_ptr(),
                elf_contents.len(),
                method_id.as_ptr(),
                method_id.len(),
            )
        };
        check(err, || Prover { ptr, opts })
    }

    /// Provide private input data that is availble to guest-side method code
    /// to 'read'.
    pub fn add_input(&mut self, slice: &[u32]) -> super::Result<()> {
        let mut err = RawError::default();
        unsafe {
            risc0_prover_add_input(
                &mut err,
                self.ptr,
                slice.as_ptr().cast(),
                slice.len() * mem::size_of::<u32>(),
            )
        };
        check(err, || ())
    }

    /// Compatibility with pure-rust prover
    pub fn add_input_u8_slice(&mut self, slice: &[u8]) {
        let mut v: Vec<u32> = Vec::new();
        v.resize((slice.len() + 3) / 4, 0);
        bytemuck::cast_slice_mut(v.as_mut_slice())[..slice.len()].clone_from_slice(slice);
        self.add_input(v.as_slice()).unwrap()
    }

    /// Compatibility with pure-rust prover
    pub fn add_input_u32_slice(&mut self, slice: &[u32]) {
        self.add_input(slice).unwrap()
    }

    /// Provide access to private output data written by guest-side method code.
    pub fn get_output(&self) -> super::Result<&[u8]> {
        unsafe {
            let mut err = RawError::default();
            let buf = risc0_prover_get_output_buf(&mut err, self.ptr);
            let buf = check(err, || buf)?;
            let mut err = RawError::default();
            let len = risc0_prover_get_output_len(&mut err, self.ptr);
            let len = check(err, || len)?;
            Ok(std::slice::from_raw_parts(buf, len))
        }
    }

    /// Provide access to private output data written to by guest-side method
    /// code.
    ///
    /// This returns the data as a [`Vec<u32>`].
    pub fn get_output_vec(&self) -> super::Result<Vec<u32>> {
        into_words(self.get_output()?)
    }

    /// Execute the ZKVM to produce a [Receipt].
    pub fn run(&self) -> super::Result<Receipt> {
        let mut err = RawError::default();

        let ptr = unsafe {
            if self.opts.skip_seal {
                risc0_prover_run_without_seal(&mut err, self.ptr)
            } else {
                risc0_prover_run(&mut err, self.ptr)
            }
        };
        check(err, || Receipt { ptr })
    }
}

impl Drop for Receipt {
    fn drop(&mut self) {
        let mut err = RawError::default();
        unsafe { risc0_receipt_free(&mut err, self.ptr) };
        check(err, || ()).unwrap()
    }
}

impl Drop for Prover {
    fn drop(&mut self) {
        let mut err = RawError::default();
        unsafe { risc0_prover_free(&mut err, self.ptr) };
        check(err, || ()).unwrap()
    }
}

#[ctor::ctor]
fn init() {
    unsafe { risc0_init() };
}
