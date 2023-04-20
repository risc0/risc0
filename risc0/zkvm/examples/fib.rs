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
use risc0_zkp::{
    core::hash::HashSuite,
    hal::{EvalCheck, Hal},
};
use risc0_zkvm::{prove::default_hal, ControlId, Executor, ExecutorEnv, Session, SessionReceipt};
use risc0_zkvm_methods::FIB_ELF;
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

    let (session, receipt) = top(hal.as_ref(), &eval, args.iterations);
    let po2 = session.segments[0].po2;
    let seal = receipt.segments[0].get_seal_bytes().len();
    let journal = receipt.journal.len();
    let total = seal + journal;
    println!("Po2: {po2}, Seal: {seal} bytes, Journal: {journal} bytes, Total: {total} bytes");
}

#[tracing::instrument(skip_all)]
fn top<H, E>(hal: &H, eval: &E, iterations: u32) -> (Session, SessionReceipt)
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    <<H as Hal>::HashSuite as HashSuite<BabyBear>>::HashFn: ControlId,
    E: EvalCheck<H>,
{
    let env = ExecutorEnv::builder().add_input(&[iterations]).build();
    let mut exec = Executor::from_elf(env, FIB_ELF).unwrap();
    let session = exec.run().unwrap();
    let receipt = session.prove(hal, eval).unwrap();
    (session, receipt)
}
