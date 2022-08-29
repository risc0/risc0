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

#[cxx::bridge]
mod bridge {}
mod exception;
#[cfg(not(feature = "pure-prove"))]
mod ffi;
#[cfg(feature = "pure-prove")]
mod prove;

use std::collections::HashMap;

#[cfg(not(feature = "pure-prove"))]
use ffi as prove;

pub use exception::Exception;
pub use prove::{MethodId, Prover, Receipt};

/// The default digest count when generating a MethodId.
pub const DEFAULT_METHOD_ID_LIMIT: u32 = 12;

/// A Result specialized for [Exception].
pub type Result<T> = std::result::Result<T, Exception>;

/// Options available to modify the prover's behavior.
pub struct ProverOpts<'a> {
    pub(crate) skip_seal: bool,

    pub(crate) sendrecv_callbacks: HashMap<u32, Box<dyn Fn(u32, &[u8]) -> Vec<u8> + 'a + Sync>>,
}

impl<'a> ProverOpts<'a> {
    /// If true, skip generating the seal in receipt.  This should
    /// only be used for testing.  In this case, performace will be
    /// much better but we will not be able to cryptographically
    /// verify the execution.
    pub fn with_skip_seal(self, skip_seal: bool) -> Self {
        Self { skip_seal, ..self }
    }

    /// Add a callback handler for sendrecv ports, indexed by channel
    /// numbers.  The guest can call these callbacks by invoking
    /// risc0_zkvm_guest::host_sendrecv.
    pub fn with_sendrecv_callback(
        mut self,
        channel_id: u32,
        callback: impl Fn(u32, &[u8]) -> Vec<u8> + 'a + Sync,
    ) -> Self {
        self.sendrecv_callbacks
            .insert(channel_id, Box::new(callback));
        self
    }
}

impl<'a> Default for ProverOpts<'a> {
    fn default() -> ProverOpts<'a> {
        ProverOpts {
            skip_seal: false,
            sendrecv_callbacks: HashMap::new(),
        }
    }
}

#[cfg(test)]
mod test {
    use super::{MethodId, Prover, ProverOpts, Receipt};
    use crate::serde::{from_slice, to_vec};
    use anyhow::Result;
    use risc0_zkp::core::sha::Digest;
    use risc0_zkvm_methods::{
        FAIL_ID, FAIL_PATH, IO_ID, IO_PATH, SENDRECV_ID, SENDRECV_PATH, SHA_ACCEL_ID,
        SHA_ACCEL_PATH, SHA_ID, SHA_PATH,
    };
    use risc0_zkvm_platform::memory::{COMMIT, HEAP};
    use std::sync::Mutex;
    use test_log::test;

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
        prover.add_input_u32_slice(vec.as_slice());
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
        run_memio_with_opts(pairs, ProverOpts::default().with_skip_seal(true))
    }

    fn run_memio_with_opts(pairs: &[(usize, usize)], opts: ProverOpts) -> Result<Receipt> {
        let mut vec = Vec::new();
        vec.push(pairs.len() as u32);
        for (first, second) in pairs {
            vec.push(*first as u32);
            vec.push(*second as u32);
        }
        let skip_seal = opts.skip_seal;
        let mut prover =
            Prover::new_with_opts(&std::fs::read(IO_PATH).unwrap(), IO_ID, opts).unwrap();
        prover.add_input_u32_slice(vec.as_slice());
        let receipt = prover.run()?;
        if !skip_seal {
            receipt.verify(IO_ID).unwrap();
        }
        Ok(receipt)
    }

    #[test]
    fn receipt_serde() {
        let receipt = run_memio_with_opts(&[(HEAP.start(), 0)], ProverOpts::default()).unwrap();
        let ser: Vec<u32> = crate::serde::to_vec(&receipt).unwrap();
        let de: Receipt = crate::serde::from_slice(&ser).unwrap();
        assert_eq!(de.get_journal().unwrap(), receipt.get_journal().unwrap());
        assert_eq!(de.get_seal().unwrap(), receipt.get_seal().unwrap());
        de.verify(IO_ID).unwrap();
    }

    #[test]
    fn receipt_serde_no_seal() {
        let receipt = run_memio_with_opts(
            &[(HEAP.start(), 0)],
            ProverOpts::default().with_skip_seal(true),
        )
        .unwrap();
        let ser: Vec<u32> = crate::serde::to_vec(&receipt).unwrap();
        let de: Receipt = crate::serde::from_slice(&ser).unwrap();
        assert_eq!(de.get_journal().unwrap(), receipt.get_journal().unwrap());
        assert_eq!(de.get_seal().unwrap(), receipt.get_seal().unwrap());
        assert!(de.verify(IO_ID).is_err());
    }

    #[test]
    fn fail() {
        // Check that a compliant host will fault.
        let mut prover = Prover::new(&std::fs::read(FAIL_PATH).unwrap(), FAIL_ID).unwrap();
        assert!(prover.run().is_err());
    }

    #[test]
    fn clone_method_id() {
        let method_id = MethodId::from_slice(FAIL_ID).unwrap();
        let clone = method_id.clone();
        assert!(method_id == clone);
    }

    #[test]
    fn host_sendrecv() {
        let expected: Vec<Vec<u8>> = vec![
            "".into(),
            "H".into(),
            "He".into(),
            "Hel".into(),
            "Hell".into(),
            "Hello".into(),
        ];
        let actual: Mutex<Vec<Vec<u8>>> = Vec::new().into();
        let opts = ProverOpts::default()
            .with_skip_seal(true)
            .with_sendrecv_callback(5, |channel_id, buf| -> Vec<u8> {
                assert_eq!(channel_id, 5);
                let mut act = actual.lock().unwrap();
                act.push(buf.into());
                expected[act.len()].clone()
            });
        let mut prover =
            Prover::new_with_opts(&std::fs::read(SENDRECV_PATH).unwrap(), SENDRECV_ID, opts)
                .unwrap();
        prover.add_input_u32_slice(&[5, expected.len() as u32 - 1]);
        prover.run().unwrap();

        assert_eq!(*actual.lock().unwrap(), expected[..expected.len() - 1]);
    }

    // Make sure panics in the callback get propagated correctly.
    #[test]
    #[should_panic(expected = "I am panicking from here!")]
    fn host_sendrecv_callback_panic() {
        let opts = ProverOpts::default()
            .with_skip_seal(true)
            .with_sendrecv_callback(5, |_channel_id, _buf| -> Vec<u8> {
                panic!("I am panicking from here!");
            });
        let mut prover =
            Prover::new_with_opts(&std::fs::read(SENDRECV_PATH).unwrap(), SENDRECV_ID, opts)
                .unwrap();
        prover.add_input_u32_slice(&[5, 5]);
        prover.run().unwrap();
    }

    #[test]
    fn sha_accel() {
        let opts = ProverOpts::default().with_skip_seal(true);
        let mut prover =
            Prover::new_with_opts(&std::fs::read(SHA_ACCEL_PATH).unwrap(), SHA_ACCEL_ID, opts)
                .unwrap();
        prover.add_input_u32_slice(&[
            0, // Test risc0_zkvm_guest::sha::Impl
            0, // Compute an empty digest
        ]);
        prover.run().unwrap();
    }

    #[test]
    fn insecure_sha_accel() {
        let opts = ProverOpts::default().with_skip_seal(true);
        let mut prover =
            Prover::new_with_opts(&std::fs::read(SHA_ACCEL_PATH).unwrap(), SHA_ACCEL_ID, opts)
                .unwrap();
        prover.add_input_u32_slice(&[
            1, // Test risc0_zkvm_guest::sha_insecure::Impl
            0, // Compute an empty digest
        ]);
        prover.run().unwrap();
    }

    #[test]
    fn sha_cycle_count() {
        let opts = ProverOpts::default().with_skip_seal(true);
        let mut prover =
            Prover::new_with_opts(&std::fs::read(SHA_ACCEL_PATH).unwrap(), SHA_ACCEL_ID, opts)
                .unwrap();
        prover.add_input_u32_slice(&[
            2, /* Check the cycle count on insecure sha matches what we expect from the
                * acceleration circuit */
            0, // Compute an empty digest
        ]);
        prover.run().unwrap();
    }
}
