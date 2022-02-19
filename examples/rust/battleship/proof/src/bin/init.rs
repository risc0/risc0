#![no_main]
#![no_std]

use risc0::{env, sha};

use battleship_proof::GameState;

risc0::entry!(main);

pub fn main() {
    let state: GameState = env::read();
    if !state.check() {
        panic!("Invalid GameState");
    }
    env::commit_digest(&sha::digest(state));
}
