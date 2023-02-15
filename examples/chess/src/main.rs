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
use clap::{Arg, Command};
use methods::{CHECKMATE_ELF, CHECKMATE_ID};
use risc0_zkvm::serde::{from_slice, to_vec};
use risc0_zkvm::Prover;
use shakmaty::fen::Fen;
use shakmaty::{CastlingMode, Chess, FromSetup, Position, Setup};

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

    // Make the prover.
    let mut prover = Prover::new(CHECKMATE_ELF, CHECKMATE_ID).unwrap();

    prover.add_input_u32_slice(&to_vec(&inputs).expect("Should be serializable"));

    // Run prover & generate receipt
    let receipt = prover
        .run()
        .expect("Legal board state and checkmating move expected");

    // Verify receipt and parse it for committed data
    receipt.verify(&CHECKMATE_ID).unwrap();
    let vec = receipt.journal;
    let committed_state: String = from_slice(&vec).unwrap();
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


#[cfg(test)]
mod tests {
    use chess_core::Inputs;
    use methods::{CHECKMATE_ELF, CHECKMATE_ID};
    use risc0_zkvm::{Prover, serde::to_vec};

    const TEST_BOARD: &str = "r1bqkb1r/pppp1ppp/2n2n2/4p2Q/2B1P3/8/PPPP1PPP/RNB1K1NR w KQkq - 4 4";
    const TEST_MOVE: &str = "Qxf7";

    #[test]
    fn main() {
        let inputs = Inputs {
            board: String::from(TEST_BOARD),
            mv: String::from(TEST_MOVE),
        };

        // Make the prover.
        let mut prover = Prover::new(CHECKMATE_ELF, CHECKMATE_ID).unwrap();
        prover.add_input_u32_slice(&to_vec(&inputs).expect("Should be serializable"));

        // Run prover & generate receipt
        let receipt = prover
            .run()
            .expect("Legal board state and checkmating move expected");

        // Verify receipt and parse it for committed data
        receipt.verify(&CHECKMATE_ID).unwrap();
    }
}
