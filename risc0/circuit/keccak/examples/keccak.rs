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

use std::time::Instant;

use clap::Parser;
use risc0_circuit_keccak::{KeccakState, prove::keccak_prover};

/// keccak prover benchmarking tool
#[derive(Parser)]
#[command(about, version, author)]
struct Cli {
    /// Circuit PO2
    #[arg(long, default_value_t = risc0_circuit_keccak::KECCAK_DEFAULT_PO2)]
    po2: usize,

    /// Number of proofs to run
    #[arg(long, default_value_t = 1)]
    count: usize,

    /// Don't verify the seal
    #[arg(long)]
    skip_verification: bool,
}

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    let args = Cli::parse();

    let mut state = KeccakState::default();
    let mut pows = 987654321_u64;
    for part in state.as_mut_slice() {
        *part = pows;
        pows = pows.wrapping_mul(123456789);
    }

    let po2 = args.po2;
    let cycles = 1 << po2;
    let count = cycles / 200; // roughly 200 cycles per keccakf
    let inputs = vec![state; count];

    let mut tot_time: f64 = 0.0;
    for i in 0..args.count {
        let start_time = Instant::now();
        let prover = keccak_prover().unwrap();
        let seal = prover.prove(&inputs, po2).unwrap();
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
        "{} runs of PO2={po2} completed in {tot_time:.3}s, avg={:.3}s, {:.3} cycles/sec, {:.3} keccak/sec",
        args.count,
        tot_time / (args.count as f64),
        (args.count * cycles) as f64 / tot_time,
        (args.count * count) as f64 / tot_time,
    );
}
