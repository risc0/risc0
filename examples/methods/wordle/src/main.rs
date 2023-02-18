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

use risc0_zkvm::guest::env;
use risc0_zkvm::sha::{Impl, Sha256};
use wordle_core::{WORD_LENGTH, WordFeedback, LetterFeedback, GameState};

risc0_zkvm::guest::entry!(main);

pub fn main() {
    let word: String = env::read();
    let guess: String = env::read();

    if word.chars().count() != WORD_LENGTH {
        panic!("secret word must have length 5!")
    }

    if guess.chars().count() != WORD_LENGTH {
        panic!("guess must have length 5!")
    }

    let correct_word_hash = *Impl::hash_bytes(&word.as_bytes());
    env::commit(&correct_word_hash);

    let mut score: WordFeedback = WordFeedback::default();
    for i in 0..WORD_LENGTH {
        score[i] = if word.as_bytes()[i] == guess.as_bytes()[i] {
            LetterFeedback::LetterCorrect
        } else if word.as_bytes().contains(&guess.as_bytes()[i]) {
            LetterFeedback::LetterPresent
        } else {
            LetterFeedback::LetterMiss
        }
    }
    let game_state = GameState {
        correct_word_hash: correct_word_hash,
        feedback: score,
    };
    env::commit(&game_state);
}
