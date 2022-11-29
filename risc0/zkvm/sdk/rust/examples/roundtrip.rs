// extern crate ec_gpu;

use std::time::Instant;

use risc0_zkp::{
    core::sha::{default_implementation, Digest as R0Digest, Sha},
    field::baby_bear::BabyBear,
    hal::{
        cpu::CpuHal,
        gpu::{GpuEvalCheck, GpuHal, GpuVerifyHal},
        EvalCheck, Hal,
    },
    verify::{CpuVerifyHal, VerifyHal},
};
use risc0_zkvm::{
    prove::cpu_eval::CpuEvalCheck,
    // host::Prover,
    prove::Prover, // todo: use this instead, of hsot::Prover
    receipt::Receipt,
    serde::{from_slice, to_vec},
    CIRCUIT,
};
use risc0_zkvm_methods::{SHA_ID, SHA_PATH};
use serde::{Deserialize, Serialize};
use sha2::{Digest, Sha256};

#[derive(Serialize, Deserialize)]
struct Request {
    preimage: [u8; 32],
}
impl<T: AsRef<[u8]>> From<T> for Request {
    fn from(preimage_in: T) -> Self {
        let preimage_in = preimage_in.as_ref();
        let len = usize::min(32, preimage_in.len());

        let mut preimage = [0u8; 32];
        preimage[..len].copy_from_slice(&preimage_in[..len]);
        Self { preimage: preimage }
    }
}
impl std::fmt::Debug for Request {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        self.preimage
            .iter()
            .try_for_each(|b| std::fmt::Debug::fmt(&b, f))
    }
}

/// Set up the CPU hal and rust prover + verifier.
fn setup_cpu() -> (
    CpuHal<BabyBear>,
    impl EvalCheck<CpuHal<BabyBear>>,
    impl VerifyHal,
) {
    let hal = CpuHal::new();
    let eval = CpuEvalCheck::new(&CIRCUIT);

    let sha = default_implementation();
    let verify_hal = CpuVerifyHal::<_, _, BabyBear>::new(sha, &CIRCUIT);
    (hal, eval, verify_hal)
}

/// Set up the GPU hal and rust prover + verifier.
fn setup_gpu() -> (
    GpuHal<BabyBear>,
    impl EvalCheck<GpuHal<BabyBear>>,
    impl VerifyHal,
) {
    let hal = GpuHal::new();
    let eval = GpuEvalCheck::new(&CIRCUIT);

    let sha = default_implementation();
    let verify_hal = GpuVerifyHal::<_, _, BabyBear>::new(sha, &CIRCUIT);
    (hal, eval, verify_hal)
}

fn roundtrip(preimage: impl AsRef<[u8]>) {
    // set up hal
    let (hal, eval, verify_hal) = setup_gpu();

    let req = Request::from(preimage);
    println!("preimage hex:\n\t{:x?}", &req);

    // manually run sha256 on preimage
    let start = Instant::now();
    let expected = {
        let mut out = [0u8; 32];
        out.copy_from_slice(&Sha256::new().chain_update(&req.preimage).finalize());
        out
    };
    let expected_hex: String = expected.iter().map(|b| format!("{b:x}")).collect();
    println!(
        "expected took: {:09}us\n\t{}",
        start.elapsed().as_micros(),
        &expected_hex,
    );

    // generate sha256 pok of preimage
    let start = Instant::now();
    let receipt = {
        let mut prover =
            Prover::new(&std::fs::read(SHA_PATH).unwrap(), SHA_ID).expect("failed to init prover");
        prover.add_input_u8_slice(&req.preimage);
        prover
            .run_with_hal(&hal, &eval)
            .expect("failed to run prover")
    };
    println!("receipt took: {:09}us", start.elapsed().as_micros(),);

    // verify
    let (digest, digest_hex) = {
        let journal = receipt
            .get_journal_vec()
            .expect("failed to retrieve journal words");
        let digest: R0Digest = from_slice(&journal).expect("failed to parse receipt");
        let digest_hex = digest.to_hex();
        (digest, digest_hex)
    };

    let start = Instant::now();
    println!("digest hex:\n\t{}", &digest_hex);
    receipt
        .verify_with_hal(&verify_hal, SHA_ID)
        .expect("seal verification failed");
    println!("verification took: {:09}us", start.elapsed().as_micros());

    // assert_eq!(&expected_hex, &digest_hex);
}

fn main() {
    roundtrip("sunnyg")
}
