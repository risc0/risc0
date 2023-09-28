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

use risc0_zkvm::guest::env;

pub fn main() {
    let iterations: u32 = env::read();
    let answer = fibonacci(iterations);
    env::commit(&answer);
}

fn fibonacci(n: u32) -> u32 {
    let mut a = 0u32;
    let mut b = 1u32;
    if n <= 1 {
        return n;
    }
    let mut i = 2;
    while i <= n {
        if i + 10 <= n {
            let c = a + b;
            let d = b + c;
            let e = c + d;
            let f = d + e;
            let g = e + f;
            let h = f + g;
            let j = g + h;
            let k = h + j;
            let l = j + k;
            let m = k + l;
            a = l;
            b = m;
            i += 10;
        } else {
            let c = a + b;
            a = b;
            b = c;
            i += 1;
        }
    }

    b
}
