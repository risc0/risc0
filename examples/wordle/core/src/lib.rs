// Copyright 2024 RISC Zero, Inc.
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

use risc0_zkvm::sha::Digest;
use serde::{Deserialize, Serialize};

pub const WORD_LENGTH: usize = 5;

#[derive(Clone, Debug, Default, Deserialize, Eq, PartialEq, Serialize)]
pub enum LetterFeedback {
    Correct,
    Present,
    #[default]
    Miss,
}

#[derive(Clone, Debug, Default, Deserialize, Eq, PartialEq, Serialize)]
pub struct WordFeedback(pub [LetterFeedback; WORD_LENGTH]);

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct GameState {
    pub correct_word_hash: Digest,
    pub feedback: WordFeedback,
}

impl WordFeedback {
    pub fn game_is_won(&self) -> bool {
        self.0.iter().all(|x| *x == LetterFeedback::Correct)
    }

    #[cfg(not(target_os = "zkvm"))]
    pub fn print(&self, guess_word: &str) {
        print!("Your results: ");
        for i in 0..WORD_LENGTH {
            match self.0[i] {
                LetterFeedback::Correct => print!("\x1b[41m"), // green
                LetterFeedback::Present => print!("\x1b[43m"), // yellow
                LetterFeedback::Miss => print!("\x1b[40m"),    // black
            }
            print!("{:}", guess_word.chars().nth(i).unwrap());
        }
        println!("\x1b[0m");
        println!();
    }
}
