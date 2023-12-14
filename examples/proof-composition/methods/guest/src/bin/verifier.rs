#![no_main]
use risc0_zkvm::guest::env;

use halo2_proofs::plonk::VerifyingKey;
use halo2_proofs::poly::commitment::Params;
use halo2_proofs::transcript::{Blake2bRead, Challenge255};

use halo2_proofs::poly::kzg::commitment::ParamsKZG;
use halo2_proofs::poly::kzg::multiopen::VerifierGWC;
use halo2_proofs::poly::kzg::strategy::AccumulatorStrategy;
use halo2_proofs::SerdeFormat;
use halo2curves::bn256::{Bn256, Fr, G1Affine};

use halo2_core::{verify_proof, MyCircuit};

risc0_zkvm::guest::entry!(main);

pub fn main() {
    // read the VerifierComponents struct from the host
    let params_len: usize = env::read();
    let vk_len: usize = env::read();
    let proof_len: usize = env::read();

    // construct buffers for each of the components
    let mut params_buffer = vec![0; params_len];
    let mut vk_buffer = vec![0; vk_len];
    let mut proof_buffer = vec![0; proof_len];

    // read slice for each of the component buffers
    env::read_slice(&mut params_buffer);
    env::read_slice(&mut vk_buffer);
    env::read_slice(&mut proof_buffer);

    println!(
        "Reading in the verification components takes {} cycles",
        env::get_cycle_count()
    );

    let a = env::get_cycle_count();

    // deserialize the params
    let des_verifier_params: ParamsKZG<Bn256> = Params::read::<_>(&mut &params_buffer[..]).unwrap();

    let b = env::get_cycle_count();

    // deserialize the verifier key
    #[allow(clippy::unit_arg)]
    let des_vk = VerifyingKey::<G1Affine>::from_bytes::<MyCircuit<Fr>>(
        &vk_buffer,
        SerdeFormat::RawBytes,
        #[cfg(feature = "circuit-params")]
        des_verifier_params,
    )
    .unwrap();

    // benchmark the performance of the verification step
    let start = env::get_cycle_count();

    println!("Deserializing the params takes {} cycles", b - a);
    println!("Deserializing the verifier key takes {} cycles", start - b);

    // we can now verify the Halo2 proof
    verify_proof::<_, VerifierGWC<_>, _, Blake2bRead<_, _, Challenge255<_>>, AccumulatorStrategy<_>>(
        &des_verifier_params,
        &des_vk,
        &proof_buffer[..],
    );

    // benchmark the performance of the verification step
    let finish = env::get_cycle_count();

    println!(
        "Verification of the Halo2 circuit takes {} cycles",
        finish - start
    );
    // write public output to the journal
    // env::commit(&input);
}
