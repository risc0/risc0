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

use risc0_circuit_rv32im::ExtVal;
use risc0_core::field::Elem as _;
use risc0_zkvm::Segment;

pub fn main() {
    const START: usize = 49;
    const END: usize = 60;

    let mut segments = vec![];
    for i in START..END {
        let segment: Segment = bincode::deserialize(
            &std::fs::read(format!("/home/remi/src/zeth/zeth_segments/{i}.bincode")).unwrap(),
        )
        .unwrap();
        segments.push(segment);
    }

    let start = std::time::Instant::now();
    for i in START..END {
        segments[i - START].inner.preflight(ExtVal::ONE).unwrap();

        println!("{}/{END}..", i + 1);
    }
    println!("took {:?}", start.elapsed());
}
