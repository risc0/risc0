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

mod riscv {
    use std::io::Read;

    use anyhow::Result;
    use flate2::read::GzDecoder;
    use risc0_binfmt::ProgramBinary;
    use risc0_zkos_v1compat::V1COMPAT_ELF;
    use risc0_zkvm::{
        ExecutorEnv, ExecutorImpl, ExitCode, ProverOpts, Receipt, Session, SimpleSegmentRef,
        VerifierContext, get_prover_server,
    };
    use tar::Archive;

    fn prove_session(session: &Session) -> Result<Receipt> {
        let opts = ProverOpts::fast();
        let ctx = VerifierContext::default();
        let prover = get_prover_server(&opts)?;
        Ok(prover.prove_session(&ctx, session)?.receipt)
    }

    fn run_test(test_name: &str) {
        // Load guest ELF from testdata archive
        let bytes = include_bytes!("../testdata/riscv-tests.tgz");
        let gz = GzDecoder::new(&bytes[..]);
        let mut tar = Archive::new(gz);

        let mut guest_elf = Vec::new();
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
            entry.read_to_end(&mut guest_elf).unwrap();
            break;
        }

        if guest_elf.is_empty() {
            panic!("No filename matching '{}'", test_name);
        }

        // Create combined binary with guest ELF and v1compat kernel
        let combined_binary = ProgramBinary::new(&guest_elf, V1COMPAT_ELF).encode();

        // Execute the program
        let env = ExecutorEnv::default();
        let session = ExecutorImpl::from_elf(env, &combined_binary)
            .unwrap()
            .run_with_callback(|segment| Ok(Box::new(SimpleSegmentRef::new(segment))))
            .unwrap();

        // Check that execution completed successfully
        assert_eq!(
            session.exit_code,
            ExitCode::Halted(0),
            "Test {} failed with exit code: {:?}",
            test_name,
            session.exit_code
        );

        // Prove the execution
        let _receipt = prove_session(&session).unwrap();
    }

    macro_rules! test_case {
        ($func_name:ident) => {
            #[test_log::test]
            fn $func_name() {
                run_test(stringify!($func_name));
            }
        };
    }

    // Atomic memory operations (RV32A)
    test_case!(amoadd_w);
    test_case!(amoand_w);
    test_case!(amomax_w);
    test_case!(amomaxu_w);
    test_case!(amomin_w);
    test_case!(amominu_w);
    test_case!(amoor_w);
    test_case!(amoswap_w);
    test_case!(amoxor_w);
    test_case!(lrsc);

    // Standard instruction tests (RV32I, RV32M)
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
    test_case!(fence_i);
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
