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

use prorata_core::AllocationQuery;
use risc0_zkvm::ExecutorEnv;
use rust_decimal::Decimal;

use crate::{exec, CycleCounter, Metrics};

pub struct Job {}

impl CycleCounter for Job {
    const NAME: &'static str = "prorata";
    const METHOD_ELF: &'static [u8] = prorata_methods::PRORATA_GUEST_ELF;

    fn run() -> Metrics {
        let recipients_csv =
            std::fs::read("../prorata/sample/ingen.csv").expect("Failed to read input file");
        let target = "John Hammond".to_string();
        let amount = Decimal::from_str_radix("1000000000", 10).unwrap();
        let env = ExecutorEnv::builder()
            .write(&AllocationQuery {
                amount,
                recipients_csv,
                target,
            })
            .unwrap()
            .build()
            .unwrap();

        exec(Self::NAME, Self::METHOD_ELF, env)
    }
}
