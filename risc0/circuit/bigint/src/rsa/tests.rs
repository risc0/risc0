// Copyright 2024 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use std::borrow::Borrow;

use anyhow::Result;
use num_bigint::BigUint;
use risc0_circuit_bigint_test_methods::{RSA_ELF, RSA_VERIFY_ELF, RSA_VERIFY_ID};
use risc0_zkvm::{get_prover_server, ExecutorEnv, ProverOpts};
use test_log::test;

use crate::{
    rsa::RSA_256_X2,
    testutil::{bigint_short_tests, from_hex},
    zkr::register_zkrs,
};

// "golden" values are the values from running the C++ version:
// bazelisk run //zirgen/Dialect/BigInt/IR/test:test -- --test
fn golden_values() -> Vec<BigUint> {
    vec![
        from_hex("9c98f9aacfc0b73c916a824db9afe39673dcb56c42dffe9de5b86d5748aca4d5"),
        from_hex("de67116c809a5cc876cebb5e8c72d998f983a4d61b499dd9ae23b789a7183677"),
        from_hex("1fb897fac8aa8870b936631d3af1a17930c8af0ca4376b3056677ded52adf5aa"),
    ]
}

// name(zkr, in_values)
bigint_short_tests! {
    rsa_test_256(
        rsa_256_x1,
        [
            "9c98f9aacfc0b73c916a824db9afe39673dcb56c42dffe9de5b86d5748aca4d5",
            "de67116c809a5cc876cebb5e8c72d998f983a4d61b499dd9ae23b789a7183677",
            "1fb897fac8aa8870b936631d3af1a17930c8af0ca4376b3056677ded52adf5aa",
        ]
    ),
    rsa_test_3072(
        rsa_3072_x1,
        [
            "a79633c36a2e9a91cac9505c300edb9a0aa8105f115856024fe27dac4910ab2fad99fe3700ddf532a3c86c5171d28177d55b3112fe73f46917a58006ac747ae396557fe84e62ba0cefd55858258e2aecd756a855ca7bd81be968fc3b908a310508828275065ab91b6f8f7964ef5684ee7fd5188c097a99323dfbe1302ab8723d97f9d1a30b89b9fb7504e8fe1e85f858ae2f07818ff8c89f7f9dbd051e52f5dae0eb33ab85d826906817f6712003c866f878874c503ec4ee02457a3c7012c6c77f66bfe23518d2eddbbe9fc3dbb8ad944d9a38e333c7caa86138f5121b89563067c4bac9c32a26cd7c21830315f8e1c5b3783104f24648f7bf8556500b04d8bf11bc7e777aa5e0653c5af9b085c2c08a16f7d2b4bc323d1b32a5cc8f4ab39f374d30efa01f8009aeb60358e5f22345fea8a123e46f394bcc669d183348b6eb29fa5f972ebe90aa64684973f4e67c0ea7d82c5a05c4a837a0a63c86b201c54cbcb1dbabf26a5bbd533b0ec91892716b7deb54c061d2e8696391f210e16b4714dd",
            "00024f2f68423c422bb8b7b6ea3f3382a379e635f9501bd9e1f09922407b5c4326fb959eadd237ed80972767deeb416749b137fc5c80876126f154f2c129a04c05970e08396dbd5d1285b4fb3a63b80855101bc3bbc9d90dd0500efd79989267ab36d4e2a361761c6ea1e172c741ec59b0aee1f1956b3ba947ed0b0cc2d45b47c041ee2a47bcc53345bd4714831b5d3125ad9a940f8efcc30ae51fc37ee6e3e4e2bd5f43ff762d7dc23017cd67a56ed00f30f09661839a10c2a487ebc1314c5bf77f0f305d040649741f357b6bb478bd72864845c3b62691c6f80199c923d2efd2e9f75751e26dc26495d3ff848d53c0424b5451d644a9903fb8c93bab50227e59c4e05029c1c50d434bd368dc0880910548804093bdd59da572d5513e57c078354f73aa35ba72d39e22e351449849d158a0ec8bc0069cd09f3dbcb7f02c089a054c35dbf7469089a43c679c3eb7f972c6cd569dcc8bf2540b1188083b77c8517a635ea037ec1b46c0f1cec0770c8d25959f80ae0068656c6c6f20776f726c64",
            "6bc245902f8b3c05089a85c2e17e8d00da0b61ac57990bd1fca990ebcb5cf7c1bfbf9adcf72c95ffba1034b62da58361290779dbf92f1e789621dd4cf8926552b5887aff88eeae89eb3dbb7e0bc7d6dd3f93db38ea3f79c0e1ca2fa866a40cad41055e7451c1d180639ecdf69e4e431efa658424c3cb242fd1acf75ce84665a857b50e5e8e5049b6159d926ed193b14f58ef8fd9aab33f308f9a1753daeb4bca467c057822a01a3e3901e2e064a5d8f336ea1ad665055f608f5e0e864ddf9c0c3723a505d649e3be66b10ee525c442e156ec61b288e7913c015804c89d9f983504a0dcf88d5399af4b53f30761484cdd49ef4eff3b6942d10bdbeedbca7b91f1cd20d031d51bf9b34342ad1809d0c4752cfb12ca7a77748c791ede7c06ef89c1017c2a9f81dd270cd504b57c292712e982efc4acd967a260b7c5cf3432a15b05f1da140a7de981338a4aa06b3858a936ef669567f4b9652fc43e806d5575b8bcf2d2a2aef6c33ffa6eeea67b8369d78d6fd952678189bd51d838011111bfa856",
        ]
    ),
}

fn run_guest_compose(claims: &[impl Borrow<[BigUint; 3]>]) -> Result<()> {
    let claims: Vec<[BigUint; 3]> = claims.iter().map(Borrow::borrow).cloned().collect();
    let env = ExecutorEnv::builder()
        // Send a & b to the guest
        .write(&claims)?
        .build()?;

    register_zkrs();

    let prover = get_prover_server(&ProverOpts::fast())?;

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, RSA_VERIFY_ELF)?.receipt;

    // Make sure this receipt actually depends on the assumption;
    // otherwise this test might give a false negative.
    assert!(!receipt
        .inner
        .composite()
        .unwrap()
        .assumption_receipts
        .is_empty());

    // Make sure the receipt verifies OK
    receipt.verify(RSA_VERIFY_ID)?;

    Ok(())
}

// Tries a single claim
#[test]
fn guest_compose_oneclaim() {
    let vals: [BigUint; 3] = golden_values().try_into().unwrap();

    run_guest_compose(&[&vals]).unwrap()
}

// Completely fills up a zkr's claim-verifying capacity
#[test]
fn guest_compose_iters() {
    let vals: [BigUint; 3] = golden_values().try_into().unwrap();

    let claims = vec![&vals; RSA_256_X2.iters];
    run_guest_compose(&claims).unwrap()
}

// Exceeds a zkr's claim-verifying capacity; should not work at all.
#[test]
fn guest_compose_exceed_iters() {
    let vals: [BigUint; 3] = golden_values().try_into().unwrap();

    let claims = vec![&vals; RSA_256_X2.iters + 1];
    run_guest_compose(&claims).expect_err("Expected too many iterations error");
}

// Supplies no claims to the ZKR to verify; at least one is required.
#[test]
fn guest_compose_empty() {
    run_guest_compose(&[] as &[&[BigUint; 3]]).expect_err("Expected empty claims error");
}

// Makes sure composition fails if any of the data changes
#[test]
fn guest_compose_corrupted() {
    for idx in 0..3 {
        let mut vals: [BigUint; 3] = golden_values().try_into().unwrap();
        vals[idx] += 1usize;
        run_guest_compose(&[vals]).expect_err(&format!(
            "Expected zkr verification failure when corrupting RSA value #{idx}"
        ));
    }
}

// Makes sure the RSA `modpow_65537` accelerator can run in the guest
#[test]
fn guest_compute() {
    // Test using small inputs based on Fermat's Little Theorem
    // (Since 65537 is prime, a = modpow_65537(a, 65537) for any 0 <= a < 65537)
    let base = from_hex("47"); // arbitrary (but less than 65537)
    let expected_result = base.clone();
    let mut base = base.to_u32_digits();
    let mut modulus = from_hex("010001").to_u32_digits(); // 65537
    assert!(modulus.len() <= crate::rsa::WIDTH_WORDS && base.len() <= crate::rsa::WIDTH_WORDS);
    modulus.resize(crate::rsa::WIDTH_WORDS, 0);
    base.resize(crate::rsa::WIDTH_WORDS, 0);
    let env = ExecutorEnv::builder()
        .write(&base)
        .unwrap()
        .write(&modulus)
        .unwrap()
        .build()
        .unwrap();

    register_zkrs();

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();
    let result: Vec<u32> = prover
        .prove(env, RSA_ELF)
        .unwrap()
        .receipt
        .journal
        .decode()
        .unwrap();
    assert_eq!(BigUint::from_slice(&result), expected_result);
}
