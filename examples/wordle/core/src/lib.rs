// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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
