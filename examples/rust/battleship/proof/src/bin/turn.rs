#![no_main]
#![no_std]

use risc0::{env, sha};

use battleship_proof::RoundParams;

risc0::entry!(main);

pub fn main() {
    let params: RoundParams = env::read();
    let result = params.process();
    env::write(&result);
    env::commit_digest(&sha::digest(params.state));
    env::commit_digest(&sha::digest(result.state));
    env::commit(&params.shot);
    env::commit(&result.hit);
}
