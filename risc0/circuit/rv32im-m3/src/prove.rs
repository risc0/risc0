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

use anyhow::Result;
use cfg_if::cfg_if;
use risc0_circuit_rv32im::execute::Segment;
use risc0_circuit_rv32im_m3_sys::*;
use risc0_sys::ffi_wrap;

use crate::verify::verify_m3;

pub type Seal = Vec<u32>;

pub trait SegmentProver {
    fn prove(&self, segment: &Segment) -> Result<Seal>;
}

struct SegmentProverImpl {
    ctx: *const ProverContext,
    po2: usize,
}

impl SegmentProver for SegmentProverImpl {
    fn prove(&self, segment: &Segment) -> Result<Seal> {
        tracing::debug!("{segment:#?}");

        // unsafe { risc0_circuit_rv32im_m3_set_log_level(2) };

        self.load_segment(segment)?;
        self.preflight()?;
        self.prove()?;

        let transcript = self.transcript()?;
        verify_m3(&transcript, self.po2)?;

        Ok(transcript)
    }
}

impl SegmentProverImpl {
    #[allow(dead_code)]
    fn new_cpu(po2: usize) -> Self {
        let ctx = unsafe { risc0_circuit_rv32im_m3_prover_new_cpu(po2) };
        Self { ctx, po2 }
    }

    #[cfg(feature = "cuda")]
    fn new_cuda(po2: usize) -> Self {
        let ctx = unsafe { risc0_circuit_rv32im_m3_prover_new_cuda(po2) };
        Self { ctx, po2 }
    }

    fn load_segment(&self, segment: &Segment) -> Result<()> {
        tracing::debug!("load_segment");
        let mut pages: Vec<RawPage> = Vec::with_capacity(segment.partial_image.pages.len());
        for (&addr, page) in segment.partial_image.pages.iter() {
            let slice: &[u32] = bytemuck::cast_slice(page.data().as_slice());
            pages.push(RawPage {
                addr,
                data: slice.as_ptr(),
            });
        }

        let raw_pages = RawSlice {
            ptr: pages.as_ptr(),
            len: pages.len(),
        };
        let image = RawMemoryImage { pages: raw_pages };
        let raw_segment = RawSegment { image };

        ffi_wrap(|| unsafe { risc0_circuit_rv32im_m3_load_segment(self.ctx, &raw_segment) })
    }

    fn preflight(&self) -> Result<()> {
        tracing::debug!("preflight");
        ffi_wrap(|| unsafe { risc0_circuit_rv32im_m3_preflight(self.ctx) })
    }

    fn prove(&self) -> Result<()> {
        tracing::debug!("prove");
        ffi_wrap(|| unsafe { risc0_circuit_rv32im_m3_prove(self.ctx) })
    }

    fn transcript(&self) -> Result<Seal> {
        let transcript = unsafe {
            let transcript = risc0_circuit_rv32im_m3_prover_transcript(self.ctx);
            std::slice::from_raw_parts(transcript.ptr, transcript.len)
        };
        Ok(transcript.to_vec())
    }
}

impl Drop for SegmentProverImpl {
    fn drop(&mut self) {
        unsafe { risc0_circuit_rv32im_m3_prover_free(self.ctx) };
    }
}

pub fn segment_prover(po2: usize) -> Result<Box<dyn SegmentProver>> {
    cfg_if! {
        if #[cfg(feature = "cuda")] {
            Ok(Box::new(SegmentProverImpl::new_cuda(po2)))
        // } else if #[cfg(any(all(target_os = "macos", target_arch = "aarch64"), target_os = "ios"))] {
        // self::hal::metal::segment_prover(hashfn)
        } else {
            Ok(
            Box::new(SegmentProverImpl::new_cpu(po2)))
        }
    }
}

#[cfg(test)]
#[cfg(feature = "cuda")]
mod tests {
    use risc0_binfmt::{MemoryImage, Program};
    use risc0_circuit_rv32im::execute::{CycleLimit, Executor, Syscall, SyscallContext};

    use super::*;

    // These tests come from:
    // https://github.com/riscv-software-src/riscv-tests
    // They were built using the toolchain from:
    // https://github.com/risc0/toolchain/releases/tag/2022.03.25
    // The exception is the test of fence, which was built with
    // https://archlinux.org/packages/extra/x86_64/riscv64-elf-gcc/ v14.0.1-1

    fn run_test(test_name: &str, po2: usize) {
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

            run_program(&elf, po2);
            return;
        }
        panic!("No filename matching '{test_name}'");
    }

    /*  This test code was used to verify that recursion lift works (and fails if
     *  transcript is modified), but relies on bringing in recursion circuit
     *  as a test-dep and some hand done copies, and is slow
    fn lift(transcript: &[u32]) -> () {
        use bytemuck::cast_slice;
        let mut transcript_vec = transcript.to_vec();
        // transcript_vec[100] += 1;
        use risc0_circuit_recursion::prove::{Program, Prover};
        tracing::info!("Loading ZKR");
        let zkr_bytes = std::fs::read("/tmp/rv32im_m3_lift_12.zkr").unwrap();
        const RECURSION_PO2: usize = 18;
        tracing::info!("Creating program");
        let program = Program::from_encoded(cast_slice::<u8, u32>(&zkr_bytes), RECURSION_PO2);
        tracing::info!("Creating prover");
        let mut prover = Prover::new(program, "poseidon2");
        prover.add_input(&transcript_vec);
        tracing::info!("Running prover");
        prover.run().unwrap();
        tracing::info!("It worked");
    }
    */

    #[derive(Default)]
    pub struct NullSyscall;

    impl Syscall for NullSyscall {
        fn host_read(
            &self,
            _ctx: &mut dyn SyscallContext,
            _fd: u32,
            _buf: &mut [u8],
        ) -> Result<u32> {
            unimplemented!()
        }

        fn host_write(&self, _ctx: &mut dyn SyscallContext, _fd: u32, _buf: &[u8]) -> Result<u32> {
            unimplemented!()
        }
    }

    fn run_program(elf: &[u8], po2: usize) {
        let program = Program::load_elf(elf, u32::MAX).unwrap();
        let image = MemoryImage::new_kernel(program);

        let mut segments = Vec::new();
        let trace = Vec::new();
        let session_limit = CycleLimit::Hard(1 << 24);
        Executor::new(image, &NullSyscall, None, trace, None)
            .run(po2, 0, session_limit, |segment| {
                segments.push(segment);
                Ok(())
            })
            .unwrap();
        let segment = segments.first().unwrap();

        let prover = segment_prover(po2).unwrap();
        prover.prove(segment).unwrap();
    }

    const DEFAULT_PO2: usize = 13;

    macro_rules! test_case {
        ($func_name:ident) => {
            #[test_log::test]
            #[gpu_guard::gpu_guard]
            fn $func_name() {
                run_test(stringify!($func_name), DEFAULT_PO2);
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
    // test_case!(fence);
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
