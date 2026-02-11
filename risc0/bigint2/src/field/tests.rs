// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{str::FromStr, time::Instant};

use num_bigint::BigUint;
use risc0_bigint2_methods::{
    EXTFIELD_DEG2_ADD_256_ELF, EXTFIELD_DEG2_ADD_384_ELF, EXTFIELD_DEG2_MUL_ELF,
    EXTFIELD_DEG2_SUB_256_ELF, EXTFIELD_DEG2_SUB_384_ELF, EXTFIELD_DEG4_MUL_ELF,
    EXTFIELD_XXONE_MUL_256_ELF, EXTFIELD_XXONE_MUL_384_ELF, MODADD_256_ELF, MODADD_384_ELF,
    MODINV_256_ELF, MODINV_384_ELF, MODMUL_256_ELF, MODMUL_384_ELF, MODSUB_256_ELF, MODSUB_384_ELF,
    RAW_TEST_ELF,
};
use risc0_zkvm::{DeserializeOwned, ExecutorEnv, ExitCode, Journal, ProverOpts, get_prover_server};
use rstest::rstest;

use crate::BigUintWrap;

fn run_test_no_decode(env: ExecutorEnv, elf: &[u8]) -> Journal {
    gpu_guard::assert_gpu_semaphore_held();

    let opts = ProverOpts::fast();
    let prover = get_prover_server(&opts).unwrap();
    let now = Instant::now();
    let mut prove_info = prover.prove(env, elf).unwrap();
    let elapsed = now.elapsed();
    let receipt = &mut prove_info.receipt;
    assert_eq!(
        receipt.claim().unwrap().as_value().unwrap().exit_code,
        ExitCode::Halted(0)
    );

    tracing::info!("Runtime: {}", elapsed.as_millis());
    tracing::info!("RISC-V instructions: {}", prove_info.stats.insn_count);

    receipt.journal.clone()
}

fn run_test<T: DeserializeOwned>(env: ExecutorEnv, elf: &[u8]) -> T {
    run_test_no_decode(env, elf).decode().unwrap()
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn modadd_256() {
    let lhs = BigUintWrap::from_str("04").unwrap();
    let rhs = BigUintWrap::from_str("07").unwrap();
    let modulus = BigUintWrap::from_str("03").unwrap();
    let expected = BigUintWrap::from_str("02").unwrap();
    let env = ExecutorEnv::builder()
        .write(&(lhs.0, rhs.0, modulus.0))
        .unwrap()
        .build()
        .unwrap();
    let result: BigUint = run_test(env, MODADD_256_ELF);
    assert_eq!(result, expected.0);
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn modinv_256() {
    let inp = BigUintWrap::from_str("02").unwrap();
    let modulus = BigUintWrap::from_str("05").unwrap();
    let expected = BigUintWrap::from_str("03").unwrap();
    let env = ExecutorEnv::builder()
        .write(&(inp.0, modulus.0))
        .unwrap()
        .build()
        .unwrap();
    let result: BigUint = run_test(env, MODINV_256_ELF);
    assert_eq!(result, expected.0);
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn modmul_256() {
    let lhs = BigUintWrap::from_str("04").unwrap();
    let rhs = BigUintWrap::from_str("07").unwrap();
    let modulus = BigUintWrap::from_str("05").unwrap();
    let expected = BigUintWrap::from_str("03").unwrap();
    let env = ExecutorEnv::builder()
        .write(&(lhs.0, rhs.0, modulus.0))
        .unwrap()
        .build()
        .unwrap();
    let result: BigUint = run_test(env, MODMUL_256_ELF);
    assert_eq!(result, expected.0);
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn modsub_256() {
    let lhs = BigUintWrap::from_str("04").unwrap();
    let rhs = BigUintWrap::from_str("07").unwrap();
    let modulus = BigUintWrap::from_str("05").unwrap();
    let expected = BigUintWrap::from_str("02").unwrap();
    let env = ExecutorEnv::builder()
        .write(&(lhs.0, rhs.0, modulus.0))
        .unwrap()
        .build()
        .unwrap();
    let result: BigUint = run_test(env, MODSUB_256_ELF);
    assert_eq!(result, expected.0);
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn modadd_384() {
    let lhs = BigUintWrap::from_str("04").unwrap();
    let rhs = BigUintWrap::from_str("07").unwrap();
    let modulus = BigUintWrap::from_str("03").unwrap();
    let expected = BigUintWrap::from_str("02").unwrap();
    let env = ExecutorEnv::builder()
        .write(&(lhs.0, rhs.0, modulus.0))
        .unwrap()
        .build()
        .unwrap();
    let result: BigUint = run_test(env, MODADD_384_ELF);
    assert_eq!(result, expected.0);
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn modinv_384() {
    let inp = BigUintWrap::from_str("02").unwrap();
    let modulus = BigUintWrap::from_str("05").unwrap();
    let expected = BigUintWrap::from_str("03").unwrap();
    let env = ExecutorEnv::builder()
        .write(&(inp.0, modulus.0))
        .unwrap()
        .build()
        .unwrap();
    let result: BigUint = run_test(env, MODINV_384_ELF);
    assert_eq!(result, expected.0);
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn modmul_384() {
    let lhs = BigUintWrap::from_str("04").unwrap();
    let rhs = BigUintWrap::from_str("07").unwrap();
    let modulus = BigUintWrap::from_str("05").unwrap();
    let expected = BigUintWrap::from_str("03").unwrap();
    let env = ExecutorEnv::builder()
        .write(&(lhs.0, rhs.0, modulus.0))
        .unwrap()
        .build()
        .unwrap();
    let result: BigUint = run_test(env, MODMUL_384_ELF);
    assert_eq!(result, expected.0);
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn modsub_384() {
    let lhs = BigUintWrap::from_str("04").unwrap();
    let rhs = BigUintWrap::from_str("07").unwrap();
    let modulus = BigUintWrap::from_str("05").unwrap();
    let expected = BigUintWrap::from_str("02").unwrap();
    let env = ExecutorEnv::builder()
        .write(&(lhs.0, rhs.0, modulus.0))
        .unwrap()
        .build()
        .unwrap();
    let result: BigUint = run_test(env, MODSUB_384_ELF);
    assert_eq!(result, expected.0);
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn extfieldadd_256() {
    let lhs0 = BigUintWrap::from_str("04").unwrap();
    let lhs1 = BigUintWrap::from_str("06").unwrap();
    let rhs0 = BigUintWrap::from_str("03").unwrap();
    let rhs1 = BigUintWrap::from_str("04").unwrap();
    let prime = BigUintWrap::from_str("07").unwrap();
    let expected0 = BigUintWrap::from_str("00").unwrap();
    let expected1 = BigUintWrap::from_str("03").unwrap();
    let env = ExecutorEnv::builder()
        .write(&(lhs0.0, lhs1.0, rhs0.0, rhs1.0, prime.0))
        .unwrap()
        .build()
        .unwrap();
    let result: (BigUint, BigUint) = run_test(env, EXTFIELD_DEG2_ADD_256_ELF);
    assert_eq!(result, (expected0.0, expected1.0));
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn extfieldadd_384() {
    let lhs0 = BigUintWrap::from_str("04").unwrap();
    let lhs1 = BigUintWrap::from_str("06").unwrap();
    let rhs0 = BigUintWrap::from_str("03").unwrap();
    let rhs1 = BigUintWrap::from_str("04").unwrap();
    let prime = BigUintWrap::from_str("07").unwrap();
    let expected0 = BigUintWrap::from_str("00").unwrap();
    let expected1 = BigUintWrap::from_str("03").unwrap();
    let env = ExecutorEnv::builder()
        .write(&(lhs0.0, lhs1.0, rhs0.0, rhs1.0, prime.0))
        .unwrap()
        .build()
        .unwrap();
    let result: (BigUint, BigUint) = run_test(env, EXTFIELD_DEG2_ADD_384_ELF);
    assert_eq!(result, (expected0.0, expected1.0));
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn extfieldsub_256() {
    let lhs0 = BigUintWrap::from_str("02").unwrap();
    let lhs1 = BigUintWrap::from_str("06").unwrap();
    let rhs0 = BigUintWrap::from_str("03").unwrap();
    let rhs1 = BigUintWrap::from_str("02").unwrap();
    let prime = BigUintWrap::from_str("07").unwrap();
    let expected0 = BigUintWrap::from_str("06").unwrap();
    let expected1 = BigUintWrap::from_str("04").unwrap();
    let expected = (expected0.0, expected1.0);
    let env = ExecutorEnv::builder()
        .write(&(lhs0.0, lhs1.0, rhs0.0, rhs1.0, prime.0))
        .unwrap()
        .build()
        .unwrap();
    let result: (BigUint, BigUint) = run_test(env, EXTFIELD_DEG2_SUB_256_ELF);
    assert_eq!(result, expected);
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn extfieldsub_384() {
    let lhs0 = BigUintWrap::from_str("02").unwrap();
    let lhs1 = BigUintWrap::from_str("06").unwrap();
    let rhs0 = BigUintWrap::from_str("03").unwrap();
    let rhs1 = BigUintWrap::from_str("02").unwrap();
    let prime = BigUintWrap::from_str("07").unwrap();
    let expected0 = BigUintWrap::from_str("06").unwrap();
    let expected1 = BigUintWrap::from_str("04").unwrap();
    let expected = (expected0.0, expected1.0);
    let env = ExecutorEnv::builder()
        .write(&(lhs0.0, lhs1.0, rhs0.0, rhs1.0, prime.0))
        .unwrap()
        .build()
        .unwrap();
    let result: (BigUint, BigUint) = run_test(env, EXTFIELD_DEG2_SUB_384_ELF);
    assert_eq!(result, expected);
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn extfieldmul() {
    // (2x+5)(3x+2) mod (xx+1) =
    //   6xx+4x+15x+10 = 6xx+5x+3 = 6(xx+0x+1)-0x-6 + 5x+3 = 5x+4
    let lhs0 = BigUintWrap::from_str("05").unwrap();
    let lhs1 = BigUintWrap::from_str("02").unwrap();
    let rhs0 = BigUintWrap::from_str("02").unwrap();
    let rhs1 = BigUintWrap::from_str("03").unwrap();
    let monicirr0 = BigUintWrap::from_str("06").unwrap();
    let monicirr1 = BigUintWrap::from_str("00").unwrap();
    let prime = BigUintWrap::from_str("07").unwrap();
    let expected0 = BigUintWrap::from_str("04").unwrap();
    let expected1 = BigUintWrap::from_str("05").unwrap();
    let expected = (expected0.0, expected1.0);
    let env = ExecutorEnv::builder()
        .write(&(
            lhs0.0,
            lhs1.0,
            rhs0.0,
            rhs1.0,
            monicirr0.0,
            monicirr1.0,
            prime.0,
        ))
        .unwrap()
        .build()
        .unwrap();
    let result: (BigUint, BigUint) = run_test(env, EXTFIELD_DEG2_MUL_ELF);
    assert_eq!(result, expected);
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn extfield_xxone_mul_256() {
    // (5x+5)(2x+2) mod (xx+1) =
    //   10xx+10x+10x+10 = 10xx+20x+10 = 10(xx+1)-10 + 6x+3 = 6x+0
    let lhs0 = BigUintWrap::from_str("05").unwrap();
    let lhs1 = BigUintWrap::from_str("05").unwrap();
    let rhs0 = BigUintWrap::from_str("02").unwrap();
    let rhs1 = BigUintWrap::from_str("02").unwrap();
    let prime = BigUintWrap::from_str("07").unwrap();
    let primesqr = BigUintWrap::from_str("31").unwrap();
    let expected0 = BigUintWrap::from_str("00").unwrap();
    let expected1 = BigUintWrap::from_str("06").unwrap();
    let expected = (expected0.0, expected1.0);

    let env = ExecutorEnv::builder()
        .write(&(lhs0.0, lhs1.0, rhs0.0, rhs1.0, prime.0, primesqr.0))
        .unwrap()
        .build()
        .unwrap();
    let result: (BigUint, BigUint) = run_test(env, EXTFIELD_XXONE_MUL_256_ELF);
    assert_eq!(result, expected);
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn extfield_xxone_mul_384() {
    // (5x+5)(2x+2) mod (xx+1) =
    //   10xx+10x+10x+10 = 10xx+20x+10 = 10(xx+1)-10 + 6x+3 = 6x+0
    let lhs0 = BigUintWrap::from_str("05").unwrap();
    let lhs1 = BigUintWrap::from_str("05").unwrap();
    let rhs0 = BigUintWrap::from_str("02").unwrap();
    let rhs1 = BigUintWrap::from_str("02").unwrap();
    let prime = BigUintWrap::from_str("07").unwrap();
    let primesqr = BigUintWrap::from_str("31").unwrap();
    let expected0 = BigUintWrap::from_str("00").unwrap();
    let expected1 = BigUintWrap::from_str("06").unwrap();
    let expected = (expected0.0, expected1.0);

    let env = ExecutorEnv::builder()
        .write(&(lhs0.0, lhs1.0, rhs0.0, rhs1.0, prime.0, primesqr.0))
        .unwrap()
        .build()
        .unwrap();
    let result: (BigUint, BigUint) = run_test(env, EXTFIELD_XXONE_MUL_384_ELF);
    assert_eq!(result, expected);
}

#[test_log::test]
#[gpu_guard::gpu_guard]
fn extfield_deg4_mul() {
    // (4xxx + 2xx + 5x +4)(2xxx + 6xx + 6x + 3) mod (x^4 + 1) =
    //   8x^6 + 24x^5 + 24x^4 + 12xxx +
    //   4x^5 + 12x^4 + 12xxx + 6xx +
    //   10x^4 + 30xxx + 30xx + 15x +
    //   8xxx + 24xx + 24x + 12 ==
    //   1x^6 + 0x^5 + 3x^4 + 6xxx + 4xx + 4x + 5 ==
    //   xx(x^4+1)-xx + 3(x^4+1)-3 + 6xxx + 4xx + 4x + 5 ==
    //   -xx - 3 + 6xxx + 4xx + 4x + 4 == 6xxx + 3xx + 4x + 1
    let lhs0 = BigUintWrap::from_str("04").unwrap();
    let lhs1 = BigUintWrap::from_str("05").unwrap();
    let lhs2 = BigUintWrap::from_str("02").unwrap();
    let lhs3 = BigUintWrap::from_str("04").unwrap();
    let rhs0 = BigUintWrap::from_str("03").unwrap();
    let rhs1 = BigUintWrap::from_str("06").unwrap();
    let rhs2 = BigUintWrap::from_str("06").unwrap();
    let rhs3 = BigUintWrap::from_str("02").unwrap();
    let monicirr0 = BigUintWrap::from_str("06").unwrap();
    let monicirr1 = BigUintWrap::from_str("00").unwrap();
    let monicirr2 = BigUintWrap::from_str("00").unwrap();
    let monicirr3 = BigUintWrap::from_str("00").unwrap();
    let prime = BigUintWrap::from_str("07").unwrap();
    let expected0 = BigUintWrap::from_str("01").unwrap();
    let expected1 = BigUintWrap::from_str("04").unwrap();
    let expected2 = BigUintWrap::from_str("03").unwrap();
    let expected3 = BigUintWrap::from_str("06").unwrap();
    let expected = (expected0.0, expected1.0, expected2.0, expected3.0);
    let env = ExecutorEnv::builder()
        .write(&(
            lhs0.0,
            lhs1.0,
            lhs2.0,
            lhs3.0,
            rhs0.0,
            rhs1.0,
            rhs2.0,
            rhs3.0,
            monicirr0.0,
            monicirr1.0,
            monicirr2.0,
            monicirr3.0,
            prime.0,
        ))
        .unwrap()
        .build()
        .unwrap();
    let result: (BigUint, BigUint, BigUint, BigUint) = run_test(env, EXTFIELD_DEG4_MUL_ELF);
    assert_eq!(result, expected);
}

const BIGINT_LEGAL_ADDR: u32 = 0x3000_0000;
const BIGINT_ILLEGAL_ADDR: u32 = 0xc000_0000;

#[rstest]
#[case(BIGINT_LEGAL_ADDR, BIGINT_LEGAL_ADDR, BIGINT_LEGAL_ADDR)]
#[should_panic(expected = "Invalid bigint address")]
#[case(BIGINT_ILLEGAL_ADDR, BIGINT_LEGAL_ADDR, BIGINT_LEGAL_ADDR)]
#[should_panic(expected = "Invalid bigint address")]
#[case(BIGINT_LEGAL_ADDR, BIGINT_ILLEGAL_ADDR, BIGINT_LEGAL_ADDR)]
#[should_panic(expected = "Invalid bigint address")]
#[case(BIGINT_LEGAL_ADDR, BIGINT_LEGAL_ADDR, BIGINT_ILLEGAL_ADDR)]
#[test_log::test]
#[gpu_guard::gpu_guard]
fn raw_addr(#[case] lhs: u32, #[case] rhs: u32, #[case] result: u32) {
    let env = ExecutorEnv::builder()
        .write(&(lhs, rhs, result))
        .unwrap()
        .build()
        .unwrap();
    run_test_no_decode(env, RAW_TEST_ELF);
}
