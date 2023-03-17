// TODO: Update the name of the method loaded by the prover. E.g., if the method is `multiply`, replace `METHOD_NAME_ELF` with `MULTIPLY_ELF` and replace `METHOD_NAME_ID` with `MULTIPLY_ID`
use methods::{METHOD_NAME_ELF, METHOD_NAME_ID};
use risc0_zkvm::Prover;
// use risc0_zkvm::serde::{from_slice, to_vec};

fn main() {
    // Make the prover.
    let mut prover = Prover::new(METHOD_NAME_ELF, METHOD_NAME_ID).expect(
        "Prover should be constructed from valid method source code and corresponding method ID",
    );

    // TODO: Implement communication with the guest here

    // Run prover & generate receipt
    let receipt = prover.run()
        .expect("Code should be provable unless it had an error or overflowed the maximum cycle count");

    // Optional: Verify receipt to confirm that recipients will also be able to verify your receipt
    receipt.verify(METHOD_NAME_ID).expect(
        "Code you have proven should successfully verify; did you specify the correct method ID?",
    );

    // TODO: Implement code for transmitting or serializing the receipt for other parties to verify here
}
