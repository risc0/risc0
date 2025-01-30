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

use risc0_zkvm::guest::env;

fn main() {
    let x: u32 = if std::env::var("ALL_FORKS") == Ok(String::from("1")) {
        1
    } else {
        0
    };

    risc0_zkvm::guest::env::commit(&x);

    let iterations: u32 = env::read();
    for _ in 0..iterations {
        env::log("alloc");
        let tmp = vec![0; 10 * 1024];
        println!("{:#?}", tmp.as_ptr());
    }
}
