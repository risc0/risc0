// Copyright 2023 RISC Zero, Inc.
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

use clap::Parser;
use risc0_core::field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem};
use risc0_zkp::{core::config::HashSuite, hal::{EvalCheck, Hal}};
use risc0_zkvm::{ControlIdLocator, prove::default_hal, Prover, Receipt};
use risc0_zkvm_methods::{FIB_ELF, FIB_ID};
use tracing_subscriber::{prelude::*, EnvFilter};

#[derive(Parser)]
#[clap()]
struct Args {
    /// Number of iterations.
    #[clap(long)]
    iterations: u32,
}

fn main() {
    tracing_subscriber::registry()
        .with(EnvFilter::from_default_env())
        .with(tracing_forest::ForestLayer::default())
        .init();

    let args = Args::parse();
    let (hal, eval) = default_hal();

    let (receipt, cycles) = top(hal.as_ref(), &eval, args.iterations);
    let seal = receipt.get_seal_bytes().len();
    let journal = receipt.get_journal_bytes().len();
    println!(
        "Cycles: {}, Seal: {} bytes, Journal: {} bytes, Total: {} bytes",
        cycles,
        seal,
        journal,
        seal + journal
    );
}

#[tracing::instrument(skip_all)]
fn top<H, E>(hal: &H, eval: &E, iterations: u32) -> (Receipt, usize)
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    <<H as Hal>::HashSuite as HashSuite<BabyBear>>::Hash: ControlIdLocator,
    E: EvalCheck<H>,
{
    let mut prover = Prover::new(FIB_ELF, FIB_ID).unwrap();
    prover.add_input_u32_slice(&[iterations]);
    (prover.run_with_hal(hal, eval).unwrap(), prover.cycles)
}
