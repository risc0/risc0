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

use risc0_zkvm::{ExecutorEnv, ExecutorImpl, ReceiptClaim, serde};
use risc0_zkvm_methods::{BENCH_ELF, BENCH_ID, bench::BenchmarkSpec};

fn run_guest(msg: &str, spec: BenchmarkSpec) {
    let env = ExecutorEnv::builder()
        .write(&spec)
        .unwrap()
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, BENCH_ELF).unwrap();
    let session = exec.run().unwrap();
    println!("{msg}: {}, {}", session.insn_count, session.row_count);
}

fn run_guest_with(msg: &str, env: ExecutorEnv) {
    let mut exec = ExecutorImpl::from_elf(env, BENCH_ELF).unwrap();
    let session = exec.run().unwrap();
    println!("{msg}: {}, {}", session.insn_count, session.row_count);
}

fn run_guest_framed(msg: &str, spec: BenchmarkSpec, payload: &[u8]) {
    let env = ExecutorEnv::builder()
        .write(&spec)
        .unwrap()
        .write_frame(payload)
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, BENCH_ELF).unwrap();
    let session = exec.run().unwrap();
    println!("{msg}: {}, {}", session.insn_count, session.row_count);
}

pub fn main() {
    simple_loop();
    hash_bytes();
    memset();
    memcpy();
    serde();
    bincode();
    borsh();
    cbor();
    message_pack();
    postcard();
}

fn simple_loop() {
    run_guest("SimpleLoop(1)", BenchmarkSpec::SimpleLoop { iters: 1 });
    run_guest(
        "SimpleLoop(1000)",
        BenchmarkSpec::SimpleLoop { iters: 1000 },
    );
}

fn hash_bytes() {
    for len in [0, 64, 512, 2048, 8192] {
        run_guest(
            &format!("hash_bytes({len})"),
            BenchmarkSpec::HashBytes {
                buf: vec![0u8; len],
            },
        );
    }
}

fn memset() {
    for len in [32, 64, 128, 256, 512, 1024, 2048, 4096] {
        run_guest(&format!("memset({len})"), BenchmarkSpec::Memset { len });
    }
}

fn memcpy() {
    for buf_bytes in [32, 64, 128, 256, 512, 1024, 2048, 4096] {
        run_guest(
            &format!("memcpy-aligned({buf_bytes})"),
            BenchmarkSpec::Memcpy {
                src: vec![0u8; buf_bytes],
                src_align: 0,
                dst_align: 0,
            },
        );
        run_guest(
            &format!("memcpy-src-unaligned({buf_bytes})"),
            BenchmarkSpec::Memcpy {
                src: vec![0u8; buf_bytes],
                src_align: 1,
                dst_align: 0,
            },
        );
        run_guest(
            &format!("memcpy-dst-unaligned({buf_bytes})"),
            BenchmarkSpec::Memcpy {
                src: vec![0u8; buf_bytes],
                src_align: 0,
                dst_align: 3,
            },
        );
        run_guest(
            &format!("memcpy-both-unaligned({buf_bytes})"),
            BenchmarkSpec::Memcpy {
                src: vec![0u8; buf_bytes],
                src_align: 1,
                dst_align: 3,
            },
        );
    }
}

fn serde() {
    let claims = vec![ReceiptClaim::ok(BENCH_ID, vec![0; 1024]); 3];
    let encoded_u32 = serde::to_vec(&claims).unwrap();
    let encoded: Vec<u8> = encoded_u32
        .iter()
        .flat_map(|&word| word.to_le_bytes().to_vec())
        .collect();

    run_guest_with(
        "read",
        ExecutorEnv::builder()
            .write(&BenchmarkSpec::Read)
            .unwrap()
            .write(&claims)
            .unwrap()
            .build()
            .unwrap(),
    );

    run_guest_framed("read_framed", BenchmarkSpec::ReadFramed, &encoded);

    run_guest_framed("read_buffered", BenchmarkSpec::ReadBuffered, &encoded);
}

fn bincode() {
    let claims = vec![ReceiptClaim::ok(BENCH_ID, vec![0; 1024]); 3];
    let encoded = bincode::serialize(&claims).unwrap();

    run_guest_with(
        "bincode",
        ExecutorEnv::builder()
            .write(&BenchmarkSpec::Bincode)
            .unwrap()
            .write_slice(&encoded)
            .build()
            .unwrap(),
    );

    run_guest_framed("bincode_framed", BenchmarkSpec::BincodeFramed, &encoded);
    run_guest_framed("bincode_buffered", BenchmarkSpec::BincodeBuffered, &encoded);
}

fn borsh() {
    let claims = vec![ReceiptClaim::ok(BENCH_ID, vec![0; 1024]); 3];
    let encoded = borsh::to_vec(&claims).unwrap();

    run_guest_framed("borsh", BenchmarkSpec::Borsh, &encoded);
}

fn cbor() {
    let claims = vec![ReceiptClaim::ok(BENCH_ID, vec![0; 1024]); 3];
    let mut encoded = vec![];
    ciborium::into_writer(&claims, &mut encoded).unwrap();

    run_guest_framed("cbor", BenchmarkSpec::Cbor, &encoded);
}

fn message_pack() {
    let claims = vec![ReceiptClaim::ok(BENCH_ID, vec![0; 1024]); 3];
    let encoded = rmp_serde::to_vec(&claims).unwrap();

    run_guest_framed("message_pack", BenchmarkSpec::MessagePack, &encoded);
}

fn postcard() {
    let claims = vec![ReceiptClaim::ok(BENCH_ID, vec![0; 1024]); 3];
    let encoded = postcard::to_allocvec(&claims).unwrap();

    run_guest_framed("postcard", BenchmarkSpec::Postcard, &encoded);
}
