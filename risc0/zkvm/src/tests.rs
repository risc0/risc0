// Copyright 2023 RISC Zero, Inc.
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

use std::{fmt, io::Cursor, str::from_utf8, sync::Mutex};

use anyhow::Result;
use risc0_zkp::core::digest::Digest;
use risc0_zkvm_methods::{
    multi_test::{MultiTestSpec, SYS_MULTI_TEST},
    HELLO_COMMIT_ELF, MULTI_TEST_ELF, MULTI_TEST_ID, SLICE_IO_ELF, STANDARD_LIB_ELF,
};
use risc0_zkvm_platform::{fileno, memory::HEAP, syscall::halt, WORD_SIZE};
use serial_test::serial;
use test_log::test;

use super::{Prover, ProverOpts, Receipt};
use crate::{
    prove::TraceEvent,
    serde::{from_slice, to_vec},
};

#[test]
fn test_poseidon_proof() {
    use risc0_zkp::core::hash::poseidon::PoseidonHashSuite;

    use crate::prove::default_poseidon_hal;
    let (hal, eval) = default_poseidon_hal();
    let opts = ProverOpts::default().with_skip_verify(true);
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, opts).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::DoNothing).unwrap());
    let receipt = prover.run_with_hal(hal.as_ref(), &eval).unwrap();
    receipt
        .verify_with_hash::<PoseidonHashSuite, _>(&MULTI_TEST_ID)
        .unwrap();
}

#[test]
fn test_blake2b_proof() {
    use risc0_circuit_rv32im::cpu::CpuEvalCheck;
    use risc0_core::field::baby_bear::BabyBear;
    use risc0_zkp::{
        core::hash::blake2b::{Blake2bCpuHashSuite, Blake2bCpuImpl, Blake2bHashSuite},
        hal::cpu::CpuHal,
    };

    use crate::CIRCUIT;

    let hal = CpuHal::<BabyBear, Blake2bCpuHashSuite>::new();
    let eval = CpuEvalCheck::new(&CIRCUIT);
    let opts = ProverOpts::default().with_skip_verify(true);
    let mut prover = Prover::new_with_opts(MULTI_TEST_ELF, opts).unwrap();
    prover.add_input_u32_slice(&to_vec(&MultiTestSpec::DoNothing).unwrap());
    let receipt = prover.run_with_hal(&hal, &eval).unwrap();
    receipt
        .verify_with_hash::<Blake2bHashSuite<Blake2bCpuImpl>, _>(&MULTI_TEST_ID)
        .unwrap();
}

// These tests come from:
// https://github.com/riscv-software-src/riscv-tests
// They were built using the toolchain from:
// https://github.com/risc0/toolchain/releases/tag/2022.03.25
mod riscv_tests {
    macro_rules! test_case {
        ($func_name:ident) => {
            #[test_log::test]
            #[cfg_attr(feature = "cuda", serial_test::serial)]
            fn $func_name() {
                use std::io::Read;

                use flate2::read::GzDecoder;
                use tar::Archive;
                use $crate::Prover;

                let bytes = include_bytes!("testdata/riscv-tests.tgz");
                let gz = GzDecoder::new(&bytes[..]);
                let mut tar = Archive::new(gz);
                for entry in tar.entries().unwrap() {
                    let mut entry = entry.unwrap();
                    if !entry.header().entry_type().is_file() {
                        continue;
                    }
                    let path = entry.path().unwrap();
                    let filename = path.file_name().unwrap().to_str().unwrap();
                    if filename != stringify!($func_name) {
                        continue;
                    }
                    let mut elf = Vec::new();
                    entry.read_to_end(&mut elf).unwrap();

                    let mut prover = Prover::new(elf.as_slice()).unwrap();
                    prover.run().unwrap();
                }
            }
        };
    }

    test_case!(add);
    test_case!(addi);
    test_case!(and);
    test_case!(andi);
    test_case!(auipc);
    test_case!(beq);
    test_case!(bge);
    test_case!(bgeu);
    test_case!(blt);
    test_case!(bltu);
    test_case!(bne);
    test_case!(div);
    test_case!(divu);
    test_case!(jal);
    test_case!(jalr);
    test_case!(lb);
    test_case!(lbu);
    test_case!(lh);
    test_case!(lhu);
    test_case!(lui);
    test_case!(lw);
    test_case!(mul);
    test_case!(mulh);
    test_case!(mulhsu);
    test_case!(mulhu);
    test_case!(or);
    test_case!(ori);
    test_case!(rem);
    test_case!(remu);
    test_case!(sb);
    test_case!(sh);
    test_case!(simple);
    test_case!(sll);
    test_case!(slli);
    test_case!(slt);
    test_case!(slti);
    test_case!(sltiu);
    test_case!(sltu);
    test_case!(sra);
    test_case!(srai);
    test_case!(srl);
    test_case!(srli);
    test_case!(sub);
    test_case!(sw);
    test_case!(xor);
    test_case!(xori);
}
