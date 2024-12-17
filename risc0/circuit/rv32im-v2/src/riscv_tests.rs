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

use crate::micro_circuit::CircuitField;
use anyhow::Result;
use risc0_zkp::core::hash::sha::Sha256HashSuite;
use risc0_zkp::hal::{cpu::CpuHal, Hal};
use risc0_zkvm::{ExecutorEnv, ExecutorImpl};

pub fn run_elf(elf: &[u8]) -> Result<()> {
    let mut builder = ExecutorEnv::builder();
    let env = builder.build()?;
    let mut exec = ExecutorImpl::from_elf(env, elf)?;
    let session = exec.run()?;

    let hal = CpuHal::new(Sha256HashSuite::<CircuitField>::new_suite());

    for segment in session.segments {
        let segment = segment.resolve()?;
        let micro_hal = crate::cpu::MicroCircuitCpuHal::new(&segment);
        let seal = crate::prove(&hal, &micro_hal, &segment)?;
        crate::verify(seal.as_slice(), hal.get_hash_suite())?;
    }
    Ok(())
}

fn run_test(test_name: &str) {
    use std::io::Read;

    use flate2::read::GzDecoder;
    use tar::Archive;
    let bytes = include_bytes!("../testdata/riscv-tests.tgz");
    let gz = GzDecoder::new(&bytes[..]);
    let mut tar = Archive::new(gz);
    for entry in tar.entries().unwrap() {
        let mut entry = entry.unwrap();
        if !entry.header().entry_type().is_file() {
            continue;
        }
        let path = entry.path().unwrap();
        let filename = path.file_name().unwrap().to_str().unwrap();
        if filename != test_name {
            continue;
        }
        let mut elf = Vec::new();
        entry.read_to_end(&mut elf).unwrap();

        run_elf(elf.as_slice()).expect("Unable to execute elf");
    }
}

macro_rules! test_case {
    ($func_name:ident) => {
        #[test_log::test]
        #[ignore = "TODO: implement host support for circuit needs"]
        #[cfg_attr(feature = "cuda", serial_test::serial)]
        fn $func_name() {
            if true {
                // TODO: Figure out how to ignore this test without
                // having cargo try to test it anyways with --ignored.
                return;
            }
            run_test(stringify!($func_name));
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
