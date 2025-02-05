// Copyright 2025 RISC Zero, Inc.
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

use substrate_bn::Fq;
use risc0_zkvm::guest::env;

fn main() {
    // TODO: switch away from example inputs
    let (example_in1, example_in2): (Vec<u8>, Vec<u8>) =
        env::read();

    // TODO: Do something real
    let mut result1 = Fq::one();
    let mut result2 = Fq::one();

    for i in 0..example_in1[0] {
        result1 = result1 + result1;
    }

    for j in 0..example_in2[0] {
        result2 = result2 + result2;
    }

    let mut output1 = [0u8; 32];
    let mut output2 = [0u8; 32];

    result1.to_big_endian(&mut output1);
    result2.to_big_endian(&mut output2);

    // TODO: Commit something real
    env::commit(&(output1, output2));
}
