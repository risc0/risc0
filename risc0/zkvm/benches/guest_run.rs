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

use risc0_zkvm::{serde, ExecutorEnv, ExecutorImpl, ReceiptClaim};
use risc0_zkvm_methods::{bench::BenchmarkSpec, BENCH_ELF, BENCH_ID};

fn run_guest(msg: &str, spec: BenchmarkSpec) {
    let env = ExecutorEnv::builder()
        .write(&spec)
        .unwrap()
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, BENCH_ELF).unwrap();
    let session = exec.run().unwrap();
    println!("{msg}: {}, {}", session.user_cycles, session.total_cycles);
}

fn run_guest_with(msg: &str, env: ExecutorEnv) {
    let mut exec = ExecutorImpl::from_elf(env, BENCH_ELF).unwrap();
    let session = exec.run().unwrap();
    println!("{msg}: {}, {}", session.user_cycles, session.total_cycles);
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
    println!("{msg}: {}, {}", session.user_cycles, session.total_cycles);
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
    let encoded = serde::to_vec(&claims).unwrap();

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

    run_guest_framed(
        "read_framed",
        BenchmarkSpec::ReadFramed,
        bytemuck::cast_slice(&encoded),
    );

    run_guest_framed(
        "read_buffered",
        BenchmarkSpec::ReadBuffered,
        bytemuck::cast_slice(&encoded),
    );
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
