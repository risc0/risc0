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

use clap::Parser;
use risc0_zkvm_prove::MethodID;

#[derive(Parser)]
#[clap(author, version, about)]
struct Args {
    /// Input Method ELF path
    input: String,

    /// Output MethodID path
    output: String,
}

fn main() {
    let args = Args::parse();
    println!("Input: {}", args.input);
    println!("Output: {}", args.output);

    let method_id = MethodID::new(&args.input).expect("Failure");
    method_id.write(&args.output).expect("Failure");
}
