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

use risc0_zkvm_circuit::make_circuit;

#[derive(Parser)]
#[clap(author, version, about)]
struct Args {
    output: String,
}

fn main() {
    let args = Args::parse();
    make_circuit(&args.output).unwrap_or_else(|err| {
        eprintln!("{}", err);
        std::process::exit(-1);
    });
}
