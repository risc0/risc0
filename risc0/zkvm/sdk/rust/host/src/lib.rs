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

use std::{ffi::CString, mem};

mod exception;
mod ffi;

pub use exception::Exception;

#[cxx::bridge]
mod bridge {}

pub type Result<T> = std::result::Result<T, Exception>;

pub struct Receipt {
    ptr: *const ffi::RawReceipt,
}

pub struct Prover {
    ptr: *mut ffi::RawProver,
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

impl Receipt {
    pub fn verify(&self, id_path: &str) -> Result<()> {
        let mut err = ffi::RawError::default();
        let id_path = CString::new(id_path).unwrap();
        unsafe { ffi::risc0_receipt_verify(&mut err, id_path.as_ptr(), self.ptr) };
        ffi::check(err, || ())
    }

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

    pub fn get_journal_vec(&self) -> Result<Vec<u32>> {
        into_words(self.get_journal()?)
    }
}

impl Prover {
    pub fn new(elf_path: &str, id_path: &str) -> Result<Self> {
        let mut err = ffi::RawError::default();
        let elf_path = CString::new(elf_path).unwrap();
        let id_path = CString::new(id_path).unwrap();
        let ptr = unsafe { ffi::risc0_prover_new(&mut err, elf_path.as_ptr(), id_path.as_ptr()) };
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

    pub fn run(&self) -> Result<Receipt> {
        let mut err = ffi::RawError::default();
        let ptr = unsafe { ffi::risc0_prover_run(&mut err, self.ptr) };
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
    use std::fs;

    use super::Prover;
    use anyhow::Result;
    use risc0_zkvm_core::Digest;
    use risc0_zkvm_methods::methods::{FAIL_ID, FAIL_PATH, IO_ID, IO_PATH, SHA_ID, SHA_PATH};
    use risc0_zkvm_serde::{from_slice, to_vec};
    use tempfile::tempdir;

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
        let temp_dir = tempdir().unwrap();
        let id_path = temp_dir.path().join("sha.id").to_str().unwrap().to_string();
        fs::write(&id_path, SHA_ID).unwrap();

        let mut prover = Prover::new(SHA_PATH, &id_path).unwrap();
        let vec = to_vec(&msg).unwrap();
        prover.add_input(vec.as_slice()).unwrap();
        let receipt = prover.run().unwrap();
        let vec = receipt.get_journal_vec().unwrap();
        from_slice::<Digest>(vec.as_slice()).unwrap()
    }

    #[test]
    fn memory_io() {
        const HEAP_START: u32 = 0x0008_0000;
        const COMMIT_START: u32 = 0x0038_0000;

        // Double write to WOM are fine
        assert!(run_memio(&[(COMMIT_START, 1), (COMMIT_START, 1)]).is_ok());

        // Double write to WOM with different values throw
        assert!(run_memio(&[(COMMIT_START, 1), (COMMIT_START, 2)]).is_err());

        // But they are OK at different addresses
        assert!(run_memio(&[(COMMIT_START, 1), (COMMIT_START + 4, 2)]).is_ok());

        // Aligned write is fine
        assert!(run_memio(&[(HEAP_START, 1)]).is_ok());

        // Unaligned write is bad
        assert!(run_memio(&[(HEAP_START + 1, 1)]).is_err());

        // Aligned read is fine
        assert!(run_memio(&[(HEAP_START, 0)]).is_ok());

        // Unaligned read is bad
        assert!(run_memio(&[(HEAP_START + 1, 0)]).is_err());
    }

    fn run_memio(pairs: &[(u32, u32)]) -> Result<()> {
        let temp_dir = tempdir().unwrap();
        let id_path = temp_dir.path().join("io.id").to_str().unwrap().to_string();
        fs::write(&id_path, IO_ID).unwrap();

        let mut vec = Vec::new();
        vec.push(pairs.len() as u32);
        for (first, second) in pairs {
            vec.push(*first);
            vec.push(*second);
        }

        let mut prover = Prover::new(IO_PATH, &id_path).unwrap();
        prover.add_input(vec.as_slice()).unwrap();
        let receipt = prover.run()?;
        receipt.verify(&id_path).unwrap();
        Ok(())
    }

    #[test]
    fn fail() {
        let temp_dir = tempdir().unwrap();
        let id_path = temp_dir
            .path()
            .join("fail.id")
            .to_str()
            .unwrap()
            .to_string();
        fs::write(&id_path, FAIL_ID).unwrap();

        // Check that a compliant host will fault.
        let prover = Prover::new(FAIL_PATH, &id_path).unwrap();
        assert!(prover.run().is_err());
    }
}
