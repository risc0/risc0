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

// Based from: https://github.com/anoma/zkp-compiler-shootout/blob/main/shootout/risc/methods/guest/src/bin/sudoku.rs
#![no_std]
#![no_main]
#![feature(slice_flatten)]

use risc0_benchmark_lib::Sudoku;
use risc0_zkvm::{guest::env, sha, sha::Sha256};

risc0_zkvm::guest::entry!(main);

pub fn main() {
    let puzzle: Sudoku = env::read();

    if !valid_solution(&puzzle) {
        panic!("invalid solution");
    } else {
        let solution_hash = sha::Impl::hash_bytes(&puzzle.0.flatten()).as_bytes();
        env::commit(&solution_hash);
    }
}

fn valid_solution(sudoku: &Sudoku) -> bool {
    for i in 0..9 {
        let mut line = 0;
        let mut col = 0;
        let mut sub = 0;

        for j in 0..9 {
            line += sudoku.0[i][j];
            col += sudoku.0[j][i];
            sub += sudoku.0[((i / 3) * 3) + j / 3][i % 3 * 3 + j % 3];
        }

        if line != 45 || col != 45 || sub != 45 {
            return false;
        }
    }
    return true;
}
