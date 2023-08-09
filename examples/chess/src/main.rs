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

use chess_core::Inputs;
use chess_methods::{CHECKMATE_ELF, CHECKMATE_ID};
use clap::{Arg, Command};
use risc0_zkvm::{
    default_prover,
    serde::{from_slice, to_vec},
    ExecutorEnv, Receipt,
};
use shakmaty::{fen::Fen, CastlingMode, Chess, FromSetup, Position, Setup};

fn main() {
    let matches =
        Command::new("chess")
            .arg(Arg::new("move").default_value("Qxf7"))
            .arg(Arg::new("board").default_value(
                "r1bqkb1r/pppp1ppp/2n2n2/4p2Q/2B1P3/8/PPPP1PPP/RNB1K1NR w KQkq - 4 4",
            ))
            .get_matches();
    let mv = matches.get_one::<String>("move").unwrap();
    let initial_state = matches.get_one::<String>("board").unwrap().to_string();

    let inputs = Inputs {
        board: initial_state,
        mv: mv.to_string(),
    };

    let receipt = chess(&inputs);

    // Verify receipt and parse it for committed data
    receipt.verify(CHECKMATE_ID).unwrap();
    let committed_state: String = from_slice(&receipt.journal).unwrap();
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
        .add_input(&to_vec(inputs).unwrap())
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    prover.prove_elf(env, CHECKMATE_ELF).unwrap()
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
