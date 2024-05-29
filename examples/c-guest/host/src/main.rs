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

    let env = ExecutorEnv::builder()
        .write_slice(&7u32.to_le_bytes())
        .write_slice(&11u32.to_le_bytes())
        .build()?;
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, &consensus_elf)?.receipt;

    // The default serialization for u32 is to (de)serialize as le bytes, so this will match
    // the format committed from the guest.
    let return_value: u32 = receipt.journal.decode()?;

    assert_eq!(return_value, 7u32 * 11);
    println!("proved value is: {}", return_value);

    // The receipt was verified at the end of proving, but the below code is an
    // example of how someone else could verify this receipt.
    receipt.verify(consensus_id)?;

    Ok(())
}
