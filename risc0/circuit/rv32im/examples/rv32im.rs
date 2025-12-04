// Copyright 2025 RISC Zero, Inc.
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

use std::time::Instant;

use clap::Parser;
use risc0_binfmt::MemoryImage;
use risc0_circuit_rv32im::{
    MAX_INSN_CYCLES,
    execute::{DEFAULT_SEGMENT_LIMIT_PO2, platform::RESERVED_CYCLES, testutil},
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
const BEFORE_LOOP_CYCLES: usize = 8;
const NON_LOOP_CYCLES: usize =
    RESERVED_CYCLES + PAGING_CYCLES + BEFORE_LOOP_CYCLES + MAX_INSN_CYCLES;

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    let args = Cli::parse();

    // DO NOT MERGE: Is NON_LOOP_CYCLES correct with the moving of max_insn_cycles into Executor.
    let po2 = args.po2;
    let segment_cycles = 1 << po2;
    assert!(segment_cycles > NON_LOOP_CYCLES);
    let iterations = (segment_cycles - NON_LOOP_CYCLES) / 2;

    let program = testutil::kernel::simple_loop(iterations as u32);
    let image = MemoryImage::new_kernel(program);
    let prover = segment_prover().unwrap();

    let result = testutil::execute(
        image.clone(),
        testutil::DEFAULT_EXECUTION_LIMIT.with_segment_po2(args.po2),
        testutil::NullSyscall,
        None,
    )
    .unwrap();
    let user_cycles = result.result.user_cycles as usize;
    let total_cycles = result.result.total_cycles as usize;

    scope!("top");

    let mut tot_exec_time: f64 = 0.0;
    let mut tot_prove_time: f64 = 0.0;
    for i in 0..args.count {
        let image = image.clone();

        let start_time = Instant::now();
        let result = testutil::execute(
            image,
            testutil::DEFAULT_EXECUTION_LIMIT.with_segment_po2(args.po2),
            testutil::NullSyscall,
            None,
        )
        .unwrap();
        let exec_time = start_time.elapsed().as_secs_f64();

        let segments = result.segments;
        let segment = segments.first().unwrap();
        assert_eq!(args.po2, segment.po2 as usize);

        let start_time = Instant::now();
        let seal = prover.prove(segment).unwrap();
        if !args.skip_verification {
            risc0_circuit_rv32im::verify(&seal).expect("Verification failed");
        }
        let prove_time = start_time.elapsed().as_secs_f64();

        println!(
            "PO2={po2} Run [{i}] exec: {exec_time:.3}s, {:.3} cycles/sec | prove: {prove_time:.3}s, {:.3} cycles/sec",
            user_cycles as f64 / exec_time,
            total_cycles as f64 / prove_time
        );
        tot_exec_time += exec_time;
        tot_prove_time += prove_time;
    }

    println!(
        "{} runs of PO2={po2} exec: {tot_exec_time:.3}s, avg={:.3}s, {:.3} cycles/sec | prove: {tot_prove_time:.3}s, avg={:.3}s, {:.3} cycles/sec",
        args.count,
        tot_exec_time / (args.count as f64),
        (args.count * user_cycles) as f64 / tot_exec_time,
        tot_prove_time / (args.count as f64),
        (args.count * total_cycles) as f64 / tot_prove_time,
    );
}
