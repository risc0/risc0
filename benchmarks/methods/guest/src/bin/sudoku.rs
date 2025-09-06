// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

// Based from: https://github.com/anoma/zkp-compiler-shootout/blob/main/shootout/risc/methods/guest/src/bin/sudoku.rs
#![no_std]
#![no_main]

use risc0_benchmark_lib::Sudoku;
use risc0_zkvm::{
    guest::env,
    sha::{Impl, Sha256},
};

risc0_zkvm::guest::entry!(main);

fn main() {
    let puzzle: Sudoku = env::read();

    if !valid_solution(&puzzle) {
        panic!("invalid solution");
    }

    let digest = Impl::hash_bytes(&puzzle.0.as_flattened());
    env::commit(&digest);
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
