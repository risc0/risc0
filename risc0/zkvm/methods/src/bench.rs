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

extern crate alloc;

use alloc::vec::Vec;

use risc0_zkvm::{
    guest::{env, memory_barrier, sha},
    sha::Sha256,
    ReceiptClaim,
};
use serde::{Deserialize, Serialize};

// Benchmark support structures for communication between host and guest.
#[derive(Serialize, Deserialize, Debug, Clone)]
pub enum BenchmarkSpec {
    SimpleLoop {
        iters: u32,
    },
    HashBytes {
        buf: Vec<u8>,
    },
    Memcpy {
        src: Vec<u8>,
        src_align: u32,
        dst_align: u32,
    },
    Memset {
        len: u32,
    },
    Read,
    ReadFramed,
    ReadBuffered,
    #[cfg(feature = "std")]
    Bincode,
    #[cfg(feature = "std")]
    BincodeFramed,
    #[cfg(feature = "std")]
    BincodeBuffered,
    Borsh,
    Cbor,
    MessagePack,
    Postcard,
}

impl BenchmarkSpec {
    pub fn run(self) {
        match self {
            BenchmarkSpec::SimpleLoop { iters } => {
                for i in 0..iters {
                    memory_barrier(&i);
                }
            }
            BenchmarkSpec::HashBytes { buf } => {
                memory_barrier(&sha::Impl::hash_bytes(&buf));
            }
            BenchmarkSpec::Memcpy {
                src,
                src_align,
                dst_align,
            } => {
                let src_align = src_align as usize;
                let dst_align = dst_align as usize;
                let src_len = src.len() - src_align;
                let mut dst: Vec<u8> = Vec::new();
                dst.resize(src_len + dst_align, 0);
                let dst_slice: &mut [u8] = &mut dst[dst_align..];
                let src_slice: &[u8] = &src[src_align..];

                dst_slice.copy_from_slice(src_slice);
                memory_barrier(&dst_slice);
            }
            BenchmarkSpec::Memset { len } => {
                let len = len as usize;
                let mut dst: Vec<u8> = Vec::new();
                dst.resize(len, 0);
                let dst_slice = &mut dst[..];

                dst_slice.fill(0);
                memory_barrier(&dst_slice);
            }
            BenchmarkSpec::Read => {
                let claims: Vec<ReceiptClaim> = env::read();
                memory_barrier(&claims);
            }
            BenchmarkSpec::ReadFramed => {
                let claims: Vec<ReceiptClaim> = env::read_framed().unwrap();
                memory_barrier(&claims);
            }
            BenchmarkSpec::ReadBuffered => {
                let claims: Vec<ReceiptClaim> = env::read_buffered().unwrap();
                memory_barrier(&claims);
            }
            #[cfg(feature = "std")]
            BenchmarkSpec::Bincode => {
                let claims: Vec<ReceiptClaim> = bincode::deserialize_from(env::stdin()).unwrap();
                memory_barrier(&claims);
            }
            #[cfg(feature = "std")]
            BenchmarkSpec::BincodeFramed => {
                let bytes = env::read_frame();
                let claims: Vec<ReceiptClaim> = bincode::deserialize(&bytes).unwrap();
                memory_barrier(&claims);
            }
            #[cfg(feature = "std")]
            BenchmarkSpec::BincodeBuffered => {
                let mut len: u32 = 0;
                env::read_slice(core::slice::from_mut(&mut len));
                let reader = std::io::BufReader::with_capacity(len as usize, env::stdin());
                let claims: Vec<ReceiptClaim> = bincode::deserialize_from(reader).unwrap();
                memory_barrier(&claims);
            }
            BenchmarkSpec::Borsh => {
                let bytes = env::read_frame();
                let claims: Vec<ReceiptClaim> = borsh::from_slice(&bytes).unwrap();
                memory_barrier(&claims);
            }
            BenchmarkSpec::Cbor => {
                let bytes = env::read_frame();
                let claims: Vec<ReceiptClaim> = ciborium::from_reader(&bytes[..]).unwrap();
                memory_barrier(&claims);
            }
            BenchmarkSpec::MessagePack => {
                let bytes = env::read_frame();
                let claims: Vec<ReceiptClaim> = rmp_serde::from_slice(&bytes).unwrap();
                memory_barrier(&claims);
            }
            BenchmarkSpec::Postcard => {
                let bytes = env::read_frame();
                let claims: Vec<ReceiptClaim> = postcard::from_bytes(&bytes).unwrap();
                memory_barrier(&claims);
            }
        }
    }
}
