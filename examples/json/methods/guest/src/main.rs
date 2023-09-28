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

#![no_main]

use json::parse;
use json_core::Outputs;
use risc0_zkvm::{
    guest::env,
    sha::{Impl, Sha256},
};

risc0_zkvm::guest::entry!(main);

pub fn main() {
    let data: String = env::read();
    let sha = *Impl::hash_bytes(&data.as_bytes());
    let data = parse(&data).unwrap();
    let proven_val = data["critical_data"].as_u32().unwrap();
    let out = Outputs {
        data: proven_val,
        hash: sha,
    };
    env::commit(&out);
}
