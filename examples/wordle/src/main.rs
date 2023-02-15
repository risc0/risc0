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

use std::io;

use methods::{WORDLE_ELF, WORDLE_ID};
use risc0_zkvm::serde::to_vec;
use risc0_zkvm::{Prover, Receipt};
use wordle_core::WORD_LENGTH;

#[cfg(test)]
use crate::wordlist::words::pick_fixed_word;
use crate::wordlist::words::pick_word;

mod wordlist;

// The "server" is an agent in the Wordle game that checks the player's guesses.
struct Server<'a> {
    // The server chooses the secret word, and remembers it until the end of the game. It is
    // private because the player shouldn't know the word until the game is over.
    secret_word: &'a str,
}

impl Server<'_> {
    pub fn new() -> Self {
        Self {
            secret_word: pick_word(),
        }
    }

    pub fn get_secret_word_hash(&self) -> Vec<u32> {
        let receipt = self.check_round("_____");
        let journal = receipt.journal;
        journal[..16].to_owned()
    }

    pub fn check_round(&self, guess_word: &str) -> Receipt {
        let mut prover = Prover::new(WORDLE_ELF, WORDLE_ID).expect("failed to construct prover");

        prover.add_input_u32_slice(to_vec(self.secret_word).unwrap().as_slice());
        prover.add_input_u32_slice(to_vec(&guess_word).unwrap().as_slice());

        return prover.run().unwrap();
    }

    #[cfg(test)]
    pub fn new_for_testing() -> Self {
        Self {
            secret_word: pick_fixed_word(),
        }
    }
}

// The "player" is an agent in the Wordle game that tries to guess the server's
// secret word.
struct Player {
    // The player remembers the hash of the secret word that the server commits to at the beginning
    // of the game. By comparing the hash after each guess, the player knows if the server cheated
    // by changing the word.
    pub hash: Vec<u32>,
}

impl Player {
    pub fn check_receipt(&self, receipt: Receipt) -> Vec<u32> {
        receipt
            .verify(&WORDLE_ID)
            .expect("receipt verification failed");

        let journal = receipt.journal;
        let hash = &journal[..16];

        if hash != self.hash {
            panic!("The hash mismatched, so the server cheated!");
        }

        let score = &journal[16..];
        return score.to_owned();
    }
}

fn read_stdin_guess() -> String {
    let mut guess = String::new();
    loop {
        io::stdin().read_line(&mut guess).unwrap();
        guess.pop(); // remove trailing newline

        if guess.chars().count() == WORD_LENGTH {
            break;
        } else {
            println!("Your guess must have 5 letters!");
            guess.clear();
        }
    }
    guess
}

fn print_wordle_feedback(guess_word: &str, score: &Vec<u32>) {
    for i in 0..WORD_LENGTH {
        match score[i] {
            0 => print!("\x1b[41m"), // correct: green
            1 => print!("\x1b[43m"), // present: yellow
            _ => print!("\x1b[40m"), // miss: black
        }
        print!("{:}", guess_word.chars().nth(i).unwrap());
    }
    println!("\x1b[0m");
}

fn game_is_won(score: Vec<u32>) -> bool {
    return score.iter().all(|x| *x == 0u32);
}

fn main() {
    println!("Welcome to fair wordle!");

    let server = Server::new();
    let player = Player {
        hash: server.get_secret_word_hash(),
    };

    let mut game_won = false;

    for _ in 0..6 {
        let guess_word = read_stdin_guess();
        let receipt = server.check_round(guess_word.as_str());
        let score = player.check_receipt(receipt);
        print_wordle_feedback(guess_word.as_str(), &score);
        if game_is_won(score) {
            game_won = true;
            break;
        }
    }

    if game_won {
        println!("You won!");
    } else {
        println!("Game over");
    }
}

#[cfg(test)]
mod tests {

    use crate::{game_is_won, Player, Server};

    const TEST_GUESS_WRONG: &str = "roofs";
    const TEST_GUESS_RIGHT: &str = "proof";

    #[test]
    fn main() {
        let server = Server::new_for_testing();
        let player = Player {
            hash: server.get_secret_word_hash(),
        };

        let guess_word = TEST_GUESS_WRONG;
        let receipt = server.check_round(&guess_word);
        let score = player.check_receipt(receipt);
        assert!(
            !game_is_won(score),
            "Incorrect guess should not win the game"
        );
        let guess_word = TEST_GUESS_RIGHT;
        let receipt = server.check_round(&guess_word);
        let score = player.check_receipt(receipt);
        assert!(game_is_won(score), "Correct guess should win the game");
    }
}
