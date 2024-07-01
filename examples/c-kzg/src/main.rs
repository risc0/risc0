use c_kzg_methods::KZG_ELF;
use hex_literal::hex;
use risc0_zkvm::{default_executor, ExecutorEnv};

fn main() {
    let proof = c_kzg_core::Proof {
     commitment: hex!("c00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000").to_vec(),
     z: hex!("5eb7004fe57383e6c88b99d839937fddf3f99279353aaf8d5c9a75f91ce33c62").to_vec(),
     y: hex!("0000000000000000000000000000000000000000000000000000000000000000").to_vec(),
     proof: hex!("c00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000").to_vec(),
 };

    let env = ExecutorEnv::builder()
        .write(&proof)
        .unwrap()
        .build()
        .unwrap();

    // this takes several hundred million segments. Only run executor.
    let exec = default_executor();
    exec.execute(env, KZG_ELF).unwrap();
}
