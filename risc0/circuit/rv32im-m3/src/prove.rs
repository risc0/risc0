// Copyright 2025 RISC Zero, Inc.
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

#[cfg(test)]
#[cfg(feature = "cuda")]
mod tests {
    use risc0_circuit_rv32im_m3_sys::risc0_circuit_rv32im_m3_prove;
    use risc0_sys::ffi_wrap;

    // These tests come from:
    // https://github.com/riscv-software-src/riscv-tests
    // They were built using the toolchain from:
    // https://github.com/risc0/toolchain/releases/tag/2022.03.25
    // The exception is the test of fence, which was built with
    // https://archlinux.org/packages/extra/x86_64/riscv64-elf-gcc/ v14.0.1-1

    fn run_test(test_name: &str) {
        use std::io::Read;

        use flate2::read::GzDecoder;
        use tar::Archive;

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
            if filename != test_name {
                continue;
            }
            let mut elf = Vec::new();
            entry.read_to_end(&mut elf).unwrap();

            run_program(&elf);
            return;
        }
        panic!("No filename matching '{}'", test_name);
    }

    fn run_program(elf: &[u8]) {
        ffi_wrap(|| unsafe { risc0_circuit_rv32im_m3_prove(elf.as_ptr(), elf.len()) }).unwrap();
    }

    macro_rules! test_case {
        ($func_name:ident) => {
            #[test_log::test]
            #[gpu_guard::gpu_guard]
            fn $func_name() {
                run_test(stringify!($func_name));
            }
        };
    }

    test_case!(add);
    // test_case!(addi);
    // test_case!(and);
    // test_case!(andi);
    // test_case!(auipc);
    // test_case!(beq);
    // test_case!(bge);
    // test_case!(bgeu);
    // test_case!(blt);
    // test_case!(bltu);
    // test_case!(bne);
    // test_case!(div);
    // test_case!(divu);
    // test_case!(fence);
    // test_case!(jal);
    // test_case!(jalr);
    // test_case!(lb);
    // test_case!(lbu);
    // test_case!(lh);
    // test_case!(lhu);
    // test_case!(lui);
    // test_case!(lw);
    // test_case!(mul);
    // test_case!(mulh);
    // test_case!(mulhsu);
    // test_case!(mulhu);
    // test_case!(or);
    // test_case!(ori);
    // test_case!(rem);
    // test_case!(remu);
    // test_case!(sb);
    // test_case!(sh);
    // test_case!(simple);
    // test_case!(sll);
    // test_case!(slli);
    // test_case!(slt);
    // test_case!(slti);
    // test_case!(sltiu);
    // test_case!(sltu);
    // test_case!(sra);
    // test_case!(srai);
    // test_case!(srl);
    // test_case!(srli);
    // test_case!(sub);
    // test_case!(sw);
    // test_case!(xor);
    // test_case!(xori);
}
