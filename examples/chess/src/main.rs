// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use chess_core::Inputs;
use chess_methods::{CHECKMATE_ELF, CHECKMATE_ID};
use clap::Parser;
use risc0_zkvm::{ExecutorEnv, Receipt, default_prover};
use shakmaty::{CastlingMode, Chess, FromSetup, Position, Setup, fen::Fen};

#[derive(Parser)]
struct Cli {
    #[arg(id = "MOVE", default_value = "Qxf7")]
    mv: String,

    #[arg(default_value = "r1bqkb1r/pppp1ppp/2n2n2/4p2Q/2B1P3/8/PPPP1PPP/RNB1K1NR w KQkq - 4 4")]
    board: String,
}

fn main() {
    let args = Cli::parse();

    let inputs = Inputs {
        board: args.board,
        mv: args.mv,
    };

    let receipt = chess(&inputs);

    // Verify receipt and parse it for committed data
    receipt.verify(CHECKMATE_ID).unwrap();
    let committed_state: String = receipt.journal.decode().unwrap();
    assert_eq!(inputs.board, committed_state);
    let fen = Fen::from_ascii(committed_state.as_bytes()).unwrap();
    let setup = Setup::from(fen);
    let pos = Chess::from_setup(setup, CastlingMode::Standard).unwrap();

    println!(
        "There is a checkmate for {:?} in this position:\n{:?}",
        pos.turn(),
        pos.board()
    );
}

fn chess(inputs: &Inputs) -> Receipt {
    let env = ExecutorEnv::builder()
        .write(inputs)
        .unwrap()
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    prover.prove(env, CHECKMATE_ELF).unwrap().receipt
}

#[cfg(test)]
mod tests {
    use chess_core::Inputs;

    use crate::chess;

    #[test]
    fn main() {
        const TEST_BOARD: &str =
            "r1bqkb1r/pppp1ppp/2n2n2/4p2Q/2B1P3/8/PPPP1PPP/RNB1K1NR w KQkq - 4 4";
        const TEST_MOVE: &str = "Qxf7";

        chess(&Inputs {
            board: String::from(TEST_BOARD),
            mv: String::from(TEST_MOVE),
        });
    }
}
