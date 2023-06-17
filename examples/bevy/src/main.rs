use bevy_core::Outputs;
use bevy_methods::{BEVY_GUEST_ELF, BEVY_GUEST_ID};
use risc0_zkvm::{
    serde::{from_slice, to_vec},
    Executor, ExecutorEnv,
};

fn main() {
    let turns: u32 = 3;
    // For this example, let's say that we want the primary entity to move 3 units
    // on the x-axis.
    let env = ExecutorEnv::builder()
        .add_input(&to_vec(&turns).unwrap())
        .build()
        .unwrap();

    // Next, we make an executor, loading the ELF binary.
    let mut exec = Executor::from_elf(env, BEVY_GUEST_ELF).unwrap();

    // Run the executor to produce a session.
    let session = exec.run().unwrap();

    // Prove the session to produce a receipt.
    let receipt = session.prove().unwrap();

    receipt.verify(BEVY_GUEST_ID.into()).unwrap();

    let outputs: Outputs =
        from_slice(&receipt.get_journal()).expect("Journal should contain an outputs object");

    assert_eq!(outputs.position, turns as f32);
    println!(
        "Game state provably moved primary entity by {} units on the x-axis",
        outputs.position
    );
}
