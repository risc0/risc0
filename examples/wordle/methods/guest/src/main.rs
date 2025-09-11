// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::guest::env;
use risc0_zkvm::sha::{Impl, Sha256};
use wordle_core::{GameState, LetterFeedback, WORD_LENGTH, WordFeedback};

fn main() {
    let secret: String = env::read();
    let guess: String = env::read();

    assert_eq!(
        secret.chars().count(),
        WORD_LENGTH,
        "secret must have length 5!"
    );

    assert_eq!(
        guess.chars().count(),
        WORD_LENGTH,
        "guess must have length 5!"
    );

    let mut feedback: WordFeedback = WordFeedback::default();

    // to avoid false positive partial matches, create a pool of only letters
    // that didn't have an exact match
    let mut secret_unmatched: String = String::from("");

    for i in 0..WORD_LENGTH {
        if secret.as_bytes()[i] != guess.as_bytes()[i] {
            secret_unmatched.push(secret.as_bytes()[i] as char);
        }
    }

    // second round for distinguishing partial matches from misses
    for i in 0..WORD_LENGTH {
        feedback.0[i] = if secret.as_bytes()[i] == guess.as_bytes()[i] {
            LetterFeedback::Correct
        } else if secret_unmatched.as_bytes().contains(&guess.as_bytes()[i]) {
            LetterFeedback::Present
        } else {
            LetterFeedback::Miss
        }
    }

    let correct_word_hash = *Impl::hash_bytes(&secret.as_bytes());
    let game_state = GameState {
        correct_word_hash,
        feedback,
    };
    env::commit(&game_state);
}
