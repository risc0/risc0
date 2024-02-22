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

pub mod argument;
pub mod loader;
pub mod machine;

#[cfg(test)]
mod tests {
    use std::collections::BTreeMap;

    use anyhow::Result;
    use risc0_binfmt::{MemoryImage, Program};
    use risc0_zkp::prove::executor::Executor;
    use risc0_zkvm_platform::PAGE_SIZE;
    use test_log::test;

    use crate::{
        prove::emu::{
            exec::{execute, Syscall, SyscallContext},
            preflight::preflight_segment,
        },
        CIRCUIT,
    };

    use super::{loader::Loader, machine::MachineContext};

    #[derive(Default)]
    struct NullSyscall;

    impl Syscall for NullSyscall {
        fn syscall(
            &self,
            _syscall: &str,
            _ctx: &mut dyn SyscallContext,
            _guest_buf: &mut [u32],
        ) -> Result<(u32, u32)> {
            todo!()
        }
    }

    #[test]
    fn basic() {
        let raw_image = BTreeMap::from([
            (0x4000, 0x1234b137), // lui x2, 0x1234b000
            (0x4004, 0xf387e1b7), // lui x3, 0xf387e000
            (0x4008, 0x003100b3), // add x1, x2, x3
            (0x400c, 0x000055b7), // lui a1, 0x00005000
            (0x4010, 0x00000073), // ecall(halt)
        ]);
        let program = Program {
            entry: 0x4000,
            image: raw_image.clone(),
        };
        let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();

        let segments = execute(image, 1 << 20, 1 << 4, &NullSyscall::default()).unwrap();
        let segment = segments.first().unwrap();

        let trace = preflight_segment(segment).unwrap();

        let machine = MachineContext::new(trace);
        let po2 = 15;
        let io = segment.prepare_globals();

        let mut executor = Executor::new(&CIRCUIT, machine, po2, po2, &io);

        let loader = Loader::new();
        loader
            .load(|chunk, fini| executor.step(chunk, fini))
            .unwrap();
        executor.finalize();
    }
}
