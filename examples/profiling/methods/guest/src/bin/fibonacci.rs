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

use core::hint::black_box;
use nalgebra::Matrix2;
use risc0_zkvm::guest::env;

risc0_zkvm::guest::entry!(main);

pub fn main() {
    let iterations: u32 = env::read();
    let answer_1 = black_box(fibonacci_1(iterations));
    let answer_2 = black_box(fibonacci_2(iterations));
    let answer_3 = black_box(fibonacci_3(iterations));
    assert_eq!(answer_1, answer_2);
    assert_eq!(answer_1, answer_3);
    env::commit(&answer_1);
}

#[inline(never)]
#[no_mangle]
pub fn fibonacci_1(n: u32) -> u64 {
    let (mut a, mut b) = (0, 1);
    if n <= 1 {
        return n as u64;
    }
    let mut i = 2;
    while i <= n {
        let c = a + b;
        a = b;
        b = c;
        i += 1;
    }
    b
}

#[inline(never)]
#[no_mangle]
pub fn fibonacci_2(n: u32) -> u64 {
    let (mut a, mut b) = (0, 1);
    if n <= 1 {
        return n as u64;
    }
    let mut i = 2;
    while i <= n {
        if i + 5 <= n {
            let c = a + b;
            let d = b + c;
            let e = c + d;
            let f = d + e;
            let g = e + f;
            a = f;
            b = g;
            i += 5;
        } else {
            let c = a + b;
            a = b;
            b = c;
            i += 1;
        }
    }
    b
}

#[inline(never)]
#[no_mangle]
fn fibonacci_3(n: u32) -> u64 {
    Matrix2::new(1, 1, 1, 0).pow(n - 1)[(0, 0)]
}
