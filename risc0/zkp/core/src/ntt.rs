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

use crate::{fp4::Fp4, rou::ROU_REV};

fn bit_rev_32(mut x: u32) -> u32 {
    x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
    x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2);
    x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
    x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
    (x >> 16) | (x << 16)
}

pub fn bit_reverse(io: &mut [Fp4], n: usize) {
    let size: usize = 1 << n;
    for i in 0..size {
        let rev_idx: usize = (bit_rev_32(i.try_into().unwrap()) >> (32 - n))
            .try_into()
            .unwrap();
        if i < rev_idx {
            let tmp = io[i];
            io[i] = io[rev_idx];
            io[rev_idx] = tmp;
        }
    }
}

pub fn rev_butterfly(io: &mut [Fp4], n: usize) {
    assert!(io.len() == (1 << n));
    if n == 0 {
        return;
    }
    let half = 1 << (n - 1);
    let step = Fp4::from_u32(ROU_REV[n]);
    let mut cur = Fp4::one();
    for i in 0..half {
        let a = io[i];
        let b = io[i + half];
        io[i] = a + b;
        io[i + half] = (a - b) * cur;
        cur *= step;
    }
    rev_butterfly(&mut io[..half], n - 1);
    rev_butterfly(&mut io[half..], n - 1);
}
