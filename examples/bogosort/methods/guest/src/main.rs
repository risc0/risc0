#![no_main]

use rand::{rngs::StdRng, seq::SliceRandom, SeedableRng};
use risc0_zkvm::guest::env;

risc0_zkvm::guest::entry!(main);

pub fn main() {
    // step 1: read the list of words
    let mut word_list: Vec<String> = env::read();

    // step 2: check if the list of words is sorted
    while !is_sorted::IsSorted::is_sorted(&mut word_list.iter()) {
        // step 3: if it's not, randomly shuffle the list
        let mut dest = [0u8; 32];
        env::getrandom(&mut dest).unwrap();
        word_list.shuffle(&mut StdRng::from_seed(dest));
    }

    // step 4: commit and exit
    env::commit(&word_list)
}
