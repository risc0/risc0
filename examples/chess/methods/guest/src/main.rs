// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use chess_core::Inputs;
use risc0_zkvm::guest::env;
use shakmaty::{CastlingMode, Chess, FromSetup, Move, Position, Setup, fen::Fen, san::San};

fn main() {
    let inputs: Inputs = env::read();
    let mv: String = inputs.mv;
    let initial_state: String = inputs.board;
    env::commit(&initial_state);

    let setup = Setup::from(Fen::from_ascii(initial_state.as_bytes()).unwrap());
    let pos = Chess::from_setup(setup, CastlingMode::Standard).unwrap();

    let mv: Move = mv.parse::<San>().unwrap().to_move(&pos).unwrap();
    let pos = pos.play(&mv).unwrap();
    assert!(pos.is_checkmate());
}
