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

#![deny(missing_docs)]
#![doc = include_str!("README.md")]

mod exception;
mod ffi;

use std::mem;

use serde::{Deserialize, Deserializer, Serialize, Serializer};

pub use exception::Exception;

#[cxx::bridge]
mod bridge {}

/// The default digest count when generating a MethodId.
pub const DEFAULT_METHOD_ID_LIMIT: u32 = 12;

/// A Result specialized for [Exception].
pub type Result<T> = std::result::Result<T, Exception>;

/// A record attesting to the correct execution of a 'method'.
///
/// Consists of:
/// * journal: all data the method wants to publicly output and commit to.
/// * seal: the cryptographic blob which proves that the receipt is valid.
pub struct Receipt {
    ptr: *const ffi::RawReceipt,
}

/// The prover generates a [Receipt] by executing a given method in a ZKVM.
pub struct Prover {
    ptr: *mut ffi::RawProver,
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
    ptr: *const ffi::RawMethodId,
}

fn into_words(slice: &[u8]) -> Result<Vec<u32>> {
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
    pub fn compute(elf_contents: &[u8], limit: u32) -> Result<Self> {
        let mut err = ffi::RawError::default();
        let ptr = unsafe {
            ffi::risc0_method_id_compute(&mut err, elf_contents.as_ptr(), elf_contents.len(), limit)
        };
        ffi::check(err, || MethodId { ptr })
    }

    /// Load an existing MethodId from a buffer.
    pub fn from_slice(slice: &[u8]) -> Result<Self> {
        let mut err = ffi::RawError::default();
        let ptr = unsafe { ffi::risc0_method_id_load(&mut err, slice.as_ptr(), slice.len()) };
        ffi::check(err, || MethodId { ptr })
    }

    /// Access the raw slice of a MethodId.
    pub fn as_slice(&self) -> Result<&[u8]> {
        let mut err = ffi::RawError::default();
        let mut len: u32 = 0;
        let ptr = unsafe { ffi::risc0_method_id_get_buf(&mut err, self.ptr, &mut len) };
        ffi::check(err, || unsafe {
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
        let mut err = ffi::RawError::default();
        unsafe { ffi::risc0_method_id_free(&mut err, self.ptr) };
        ffi::check(err, || ()).unwrap()
    }
}

impl Receipt {
    /// Construct a new [Receipt] from individual journal and seal parts.
    pub fn new(journal: &[u8], seal: &[u32]) -> Result<Self> {
        let mut err = ffi::RawError::default();
        let ptr = unsafe {
            ffi::risc0_receipt_new(
                &mut err,
                journal.as_ptr(),
                journal.len(),
                seal.as_ptr(),
                seal.len(),
            )
        };
        ffi::check(err, || Receipt { ptr })
    }

    /// Verify that the current [Receipt] is a valid result of executing the
    /// method associated with the given method ID in a ZKVM.
    pub fn verify(&self, method_id: &[u8]) -> Result<()> {
        let mut err = ffi::RawError::default();
        unsafe {
            ffi::risc0_receipt_verify(&mut err, self.ptr, method_id.as_ptr(), method_id.len())
        };
        ffi::check(err, || ())
    }

    /// Provides access to the `seal` of a [Receipt].
    pub fn get_seal(&self) -> Result<&[u32]> {
        unsafe {
            let mut err = ffi::RawError::default();
            let buf = ffi::risc0_receipt_get_seal_buf(&mut err, self.ptr);
            let buf = ffi::check(err, || buf)?;
            let mut err = ffi::RawError::default();
            let len = ffi::risc0_receipt_get_seal_len(&mut err, self.ptr);
            let len = ffi::check(err, || len)?;
            Ok(std::slice::from_raw_parts(buf, len))
        }
    }

    /// Provides access to the `journal` of a [Receipt].
    pub fn get_journal(&self) -> Result<&[u8]> {
        unsafe {
            let mut err = ffi::RawError::default();
            let buf = ffi::risc0_receipt_get_journal_buf(&mut err, self.ptr);
            let buf = ffi::check(err, || buf)?;
            let mut err = ffi::RawError::default();
            let len = ffi::risc0_receipt_get_journal_len(&mut err, self.ptr);
            let len = ffi::check(err, || len)?;
            Ok(std::slice::from_raw_parts(buf, len))
        }
    }

    /// Provides access to the `journal` of a [Receipt] as a [`Vec<u32>`].
    pub fn get_journal_vec(&self) -> Result<Vec<u32>> {
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
    pub fn new(elf_contents: &[u8], method_id: &[u8]) -> Result<Self> {
        Self::new_with_opts(elf_contents, method_id, ProverOpts::default())
    }

    /// Create a new [Prover] with the given method (specified via
    /// `elf_contents`) and an associated method ID (specified via
    /// `method_id`) and additional options.
    pub fn new_with_opts(elf_contents: &[u8], method_id: &[u8], opts: ProverOpts) -> Result<Self> {
        let mut err = ffi::RawError::default();
        let ptr = unsafe {
            ffi::risc0_prover_new(
                &mut err,
                elf_contents.as_ptr(),
                elf_contents.len(),
                method_id.as_ptr(),
                method_id.len(),
            )
        };
        ffi::check(err, || Prover { ptr, opts })
    }

    /// Provide private input data that is availble to guest-side method code
    /// to 'read'.
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

    /// Provide access to private output data written by guest-side method code.
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

    /// Provide access to private output data written to by guest-side method
    /// code.
    ///
    /// This returns the data as a [`Vec<u32>`].
    pub fn get_output_vec(&self) -> Result<Vec<u32>> {
        into_words(self.get_output()?)
    }

    /// Execute the ZKVM to produce a [Receipt].
    pub fn run(&self) -> Result<Receipt> {
        let mut err = ffi::RawError::default();

        let ptr = unsafe {
            if self.opts.skip_seal {
                ffi::risc0_prover_run_without_seal(&mut err, self.ptr)
            } else {
                ffi::risc0_prover_run(&mut err, self.ptr)
            }
        };
        ffi::check(err, || Receipt { ptr })
    }
}

impl Drop for Receipt {
    fn drop(&mut self) {
        let mut err = ffi::RawError::default();
        unsafe { ffi::risc0_receipt_free(&mut err, self.ptr) };
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
    unsafe { ffi::risc0_init() };
}

#[cfg(test)]
mod test {
    use super::{MethodId, Prover, ProverOpts, Receipt};
    use crate::platform::memory::{COMMIT, HEAP};
    use crate::serde::{from_slice, to_vec};
    use anyhow::Result;
    use risc0_zkp::core::sha::Digest;
    use risc0_zkvm_methods::{FAIL_ID, FAIL_PATH, IO_ID, IO_PATH, SHA_ID, SHA_PATH};

    #[test]
    fn sha() {
        assert_eq!(
            run_sha(""),
            Digest::new([
                0xe3b0c442, 0x98fc1c14, 0x9afbf4c8, 0x996fb924, 0x27ae41e4, 0x649b934c, 0xa495991b,
                0x7852b855,
            ])
        );
        assert_eq!(
            run_sha("a"),
            Digest::new([
                0xca978112, 0xca1bbdca, 0xfac231b3, 0x9a23dc4d, 0xa786eff8, 0x147c4e72, 0xb9807785,
                0xafee48bb,
            ])
        );
        assert_eq!(
            run_sha("abc"),
            Digest::new([
                0xba7816bf, 0x8f01cfea, 0x414140de, 0x5dae2223, 0xb00361a3, 0x96177a9c, 0xb410ff61,
                0xf20015ad
            ])
        );
        assert_eq!(
            run_sha("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"),
            Digest::new([
                0x248d6a61, 0xd20638b8, 0xe5c02693, 0x0c3e6039, 0xa33ce459, 0x64ff2167, 0xf6ecedd4,
                0x19db06c1
            ])
        );
    }

    fn run_sha(msg: &str) -> Digest {
        let mut prover = Prover::new(&std::fs::read(SHA_PATH).unwrap(), SHA_ID).unwrap();
        let vec = to_vec(&msg).unwrap();
        prover.add_input(vec.as_slice()).unwrap();
        let receipt = prover.run().unwrap();
        let vec = receipt.get_journal_vec().unwrap();
        from_slice::<Digest>(vec.as_slice()).unwrap()
    }

    #[test]
    fn memory_io() {
        // Double write to WOM are fine
        assert!(run_memio(&[(COMMIT.start(), 1), (COMMIT.start(), 1)]).is_ok());

        // Double write to WOM with different values throw
        assert!(run_memio(&[(COMMIT.start(), 1), (COMMIT.start(), 2)]).is_err());

        // But they are OK at different addresses
        assert!(run_memio(&[(COMMIT.start(), 1), (COMMIT.start() + 4, 2)]).is_ok());

        // Aligned write is fine
        assert!(run_memio(&[(HEAP.start(), 1)]).is_ok());

        // Unaligned write is bad
        assert!(run_memio(&[(HEAP.start() + 1, 1)]).is_err());

        // Aligned read is fine
        assert!(run_memio(&[(HEAP.start(), 0)]).is_ok());

        // Unaligned read is bad
        assert!(run_memio(&[(HEAP.start() + 1, 0)]).is_err());
    }

    fn run_memio(pairs: &[(usize, usize)]) -> Result<Receipt> {
        run_memio_with_opts(pairs, ProverOpts::default())
    }

    fn run_memio_with_opts(pairs: &[(usize, usize)], opts: ProverOpts) -> Result<Receipt> {
        let mut vec = Vec::new();
        vec.push(pairs.len() as u32);
        for (first, second) in pairs {
            vec.push(*first as u32);
            vec.push(*second as u32);
        }
        let mut prover =
            Prover::new_with_opts(&std::fs::read(IO_PATH).unwrap(), IO_ID, opts).unwrap();
        prover.add_input(vec.as_slice()).unwrap();
        let receipt = prover.run()?;
        if !opts.skip_seal {
            receipt.verify(IO_ID).unwrap();
        }
        Ok(receipt)
    }

    #[test]
    fn receipt_serde() {
        let receipt: Receipt = run_memio(&[(HEAP.start(), 0)]).unwrap();
        let ser: Vec<u32> = crate::serde::to_vec(&receipt).unwrap();
        let de: Receipt = crate::serde::from_slice(&ser).unwrap();
        assert_eq!(de.get_journal().unwrap(), receipt.get_journal().unwrap());
        assert_eq!(de.get_seal().unwrap(), receipt.get_seal().unwrap());
        de.verify(IO_ID).unwrap();
    }

    #[test]
    fn receipt_serde_no_seal() {
        let receipt: Receipt =
            run_memio_with_opts(&[(HEAP.start(), 0)], ProverOpts { skip_seal: true }).unwrap();
        let ser: Vec<u32> = crate::serde::to_vec(&receipt).unwrap();
        let de: Receipt = crate::serde::from_slice(&ser).unwrap();
        assert_eq!(de.get_journal().unwrap(), receipt.get_journal().unwrap());
        assert_eq!(de.get_seal().unwrap(), receipt.get_seal().unwrap());
        assert!(de.verify(IO_ID).is_err());
    }

    #[test]
    fn fail() {
        // Check that a compliant host will fault.
        let prover = Prover::new(&std::fs::read(FAIL_PATH).unwrap(), FAIL_ID).unwrap();
        assert!(prover.run().is_err());
    }

    #[test]
    fn clone_method_id() {
        let method_id = MethodId::from_slice(FAIL_ID).unwrap();
        let clone = method_id.clone();
        assert!(method_id == clone);
    }
}
