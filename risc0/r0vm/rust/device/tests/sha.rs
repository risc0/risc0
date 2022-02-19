#![no_main]
#![no_std]
#![allow(non_snake_case)]

use risc0::{env, sha};

risc0::entry!(main);

pub fn main() {
    let data: &[u8] = env::read_slice();
    env::commit_digest(&sha::digest_slice(data));
}
