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

#![no_main]

use risc0_zkp::core::sha::Sha;
use risc0_zkvm::guest::{env, memory_barrier, sha};
use risc0_zkvm_methods::bench::{BenchmarkSpec, SpecWithIters};

risc0_zkvm::entry!(main);

pub fn main() {
    let SpecWithIters(spec, iters) = env::read();
    match spec {
        BenchmarkSpec::SimpleLoop => {
            for i in 0..iters {
                memory_barrier(&i);
            }
        }
        BenchmarkSpec::HashBytes { buf } => {
            let sha = sha::Impl {};
            for _ in 0..iters {
                memory_barrier(&sha.hash_bytes(&buf));
            }
        }
        BenchmarkSpec::HashRawWords { buf } => {
            let sha = sha::Impl {};
            for _ in 0..iters {
                memory_barrier(&sha.hash_raw_words(&buf));
            }
        }
        BenchmarkSpec::Memcpy {
            src,
            src_align,
            dst_align,
        } => {
            let src_len = src.len() - src_align;
            let mut dst: Vec<u8> = Vec::new();
            dst.resize(src_len + dst_align, 0);
            let dst_slice: &mut [u8] = &mut dst[dst_align..];
            let src_slice: &[u8] = &src[src_align..];

            for _ in 0..iters {
                dst_slice.copy_from_slice(src_slice);
                memory_barrier(&dst_slice);
            }
        }
        BenchmarkSpec::Memset { len } => {
            let mut dst: Vec<u8> = Vec::new();
            dst.resize(len, 0);
            let dst_slice = &mut dst[..];

            for i in 0..iters {
                dst_slice.fill(i as u8);
                memory_barrier(&dst_slice);
            }
        }
    }
}
