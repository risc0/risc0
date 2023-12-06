#![no_main]

use risc0_zkvm::guest::env;
use risc0_zkvm::sha::Digest;

risc0_zkvm::guest::entry!(main);

pub fn main() {
    let image_id_a: Digest = env::read();
    let journal_a: Vec<u8> = env::read();
    let image_id_b: Digest = env::read();
    let journal_b: Vec<u8> = env::read();
    env::verify(image_id_a, &journal_a).unwrap();
    env::verify(image_id_b, &journal_b).unwrap();
}
