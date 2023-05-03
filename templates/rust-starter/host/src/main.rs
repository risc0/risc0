// TODO: Update the name of the method loaded by the prover. E.g., if the method
// is `multiply`, replace `METHOD_NAME_ELF` with `MULTIPLY_ELF` and replace
// `METHOD_NAME_ID` with `MULTIPLY_ID`
use methods::{METHOD_NAME_ELF, METHOD_NAME_ID};
use risc0_zkvm::{Executor, ExecutorEnv};
use risc0_zkvm::serde::{from_slice, to_vec};

fn main() {
    let env = ExecutorEnv::default();
    let mut exec = Executor::from_elf(env, METHOD_NAME_ELF).unwrap();
    let session = exec.run().unwrap();
    let receipt = session.prove().unwrap();

    // TODO: Implement code for transmitting or serializing the receipt for
    // other parties to verify here

    // Optional: Verify receipt to confirm that recipients will also be able to
    // verify your receipt
    receipt.verify(METHOD_NAME_ID).unwrap();
}
