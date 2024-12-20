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

use std::time::Instant;

use clap::Parser;
use risc0_circuit_rv32im_v2::{
    execute::{
        platform::LOOKUP_TABLE_CYCLES, testutil, MemoryImage2, DEFAULT_SEGMENT_LIMIT_PO2,
        MAX_INSN_CYCLES,
    },
    prove::segment_prover,
};
use risc0_core::scope;

/// keccak prover benchmarking tool
#[derive(Parser)]
#[command(about, version, author)]
struct Cli {
    /// Circuit PO2
    #[arg(long, default_value_t = DEFAULT_SEGMENT_LIMIT_PO2)]
    po2: usize,

    /// Number of proofs to run
    #[arg(long, default_value_t = 1)]
    count: usize,

    /// Don't verify the seal
    #[arg(long)]
    skip_verification: bool,
}

const PAGING_CYCLES: usize = 1821;
const NON_LOOP_CYCLES: usize = 8;
const RESERVED_CYCLES: usize =
    LOOKUP_TABLE_CYCLES + PAGING_CYCLES + NON_LOOP_CYCLES + MAX_INSN_CYCLES;

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    let args = Cli::parse();

    let po2 = args.po2;
    let cycles = 1 << po2;
    assert!(cycles > RESERVED_CYCLES);
    let iterations = (cycles - RESERVED_CYCLES) / 2;

    let program = testutil::simple_loop(iterations as u32);
    let image = MemoryImage2::new(program);
    let prover = segment_prover().unwrap();

    scope!("top");

    let result = testutil::execute(
        image,
        args.po2,
        MAX_INSN_CYCLES,
        testutil::DEFAULT_SESSION_LIMIT,
        &testutil::NullSyscall,
        None,
    )
    .unwrap();

    let segments = result.segments;
    let segment = segments.first().unwrap();
    assert_eq!(args.po2, segment.po2 as usize);

    let mut tot_time: f64 = 0.0;
    for i in 0..args.count {
        let start_time = Instant::now();
        let seal = prover.prove(segment).unwrap();
        if !args.skip_verification {
            prover.verify(&seal).expect("Verification failed");
        }
        let run_time = start_time.elapsed().as_secs_f64();
        println!(
            "PO2={po2} Run #{i}: {run_time:.3}s, {:.3} cycles/sec",
            cycles as f64 / run_time
        );
        tot_time += run_time;
    }

    println!(
        "{} runs of PO2={po2} completed in {tot_time:.3}s, avg={:.3}s, {:.3} cycles/sec",
        args.count,
        tot_time / (args.count as f64),
        (args.count * cycles) as f64 / tot_time,
    );
}
