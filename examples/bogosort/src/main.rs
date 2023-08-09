use methods::BOGOSORT_ELF;
use risc0_zkvm::{
    default_prover,
    serde::{from_slice, to_vec},
    ExecutorEnv,
};

fn main() {
    let unsorted_list_strings = vec![
        "Michelle".to_string(),
        "Zoe".to_string(),
        "Abdul".to_string(),
        "Peter".to_string(),
        "Eric".to_string(),
    ];

    let env = ExecutorEnv::builder()
        .enable_host_randomness()
        .add_input(&to_vec(&unsorted_list_strings).unwrap())
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove_elf(env, BOGOSORT_ELF).unwrap();

    // Extract journal of receipt
    let sorted_list: Vec<String> = from_slice(&receipt.journal).expect(
        "Journal output should deserialize into the same types (& order) that it was written",
    );

    println!("{:?}", sorted_list);
}
