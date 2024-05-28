use risc0_zkvm::{compute_image_id, default_prover, ExecutorEnv};
use std::fs;

fn main() -> anyhow::Result<()> {
    // Load built gcc program and compute it's image ID.
    let consensus_elf = fs::read("./guest/out/main")?;
    let consensus_id = compute_image_id(&consensus_elf)?;
    // Initialize tracing. In order to view logs, run `RUST_LOG=info cargo run`
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    let env = ExecutorEnv::builder().build()?;
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, &consensus_elf)?.receipt;

    assert_eq!(&receipt.journal.bytes, &[0, 1, 2, 3]);

    // The receipt was verified at the end of proving, but the below code is an
    // example of how someone else could verify this receipt.
    receipt.verify(consensus_id)?;

    Ok(())
}
