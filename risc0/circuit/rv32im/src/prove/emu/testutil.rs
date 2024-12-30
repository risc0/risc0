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

use anyhow::Result;
use risc0_binfmt::Program;
use risc0_zkvm_platform::WORD_SIZE;

use super::exec::{Syscall, SyscallContext};

pub const DEFAULT_SESSION_LIMIT: Option<u64> = Some(1 << 24);

#[derive(Default)]
pub struct NullSyscall;

impl Syscall for NullSyscall {
    fn syscall(
        &self,
        _syscall: &str,
        _ctx: &mut dyn SyscallContext,
        _guest_buf: &mut [u32],
    ) -> Result<(u32, u32)> {
        unimplemented!()
    }
}

/// Constructs a program from an iterator of instructions starting from an entrypoint.
fn program_from_instructions(entry: u32, instructions: impl IntoIterator<Item = u32>) -> Program {
    let mut pc = entry;

    Program {
        entry,
        image: instructions
            .into_iter()
            .map(|instr| {
                let result = (pc, instr);
                pc += WORD_SIZE as u32;
                result
            })
            .collect(),
    }
}

pub fn basic() -> Program {
    program_from_instructions(
        0x40000,
        [
            0x1234b137, // lui x2, 0x1234b000
            0xf387e1b7, // lui x3, 0xf387e000
            0x003100b3, // add x1, x2, x3
            0x000105b7, // lui a1, 0x10
            0x00000073, // ecall(halt)
        ],
    )
}

pub fn simple_loop() -> Program {
    // loop.asm:
    //
    // .global _boot
    // .text
    //
    // _boot:
    //     li      a4,0
    //     li      a5,100
    // loop:
    //     addi    a4,a4,1
    //     blt     a4,a5,loop
    //     lui     a1,0x1000
    //     ecall
    //
    // riscv32-unknown-elf-as loop.asm -o loop; riscv32-unknown-elf-objdump -d loop
    program_from_instructions(
        0x4000,
        [
            0x00000713, // li      a4,0
            0x06400793, // li      a5,100
            0x00170713, // add     a4,a4,1
            0xfef74ee3, // blt     a4,a5,8 <loop>
            0x010005b7, // lui     a1,0x1000
            0x00000073, // ecall
        ],
    )
}

pub fn large_text() -> Program {
    let iter = (0..2500).map(|_| {
        0x1234b137 // lui x2, 0x1234b000
    });

    let iter = iter.chain([
        0x000055b7, // lui a1, 0x00005000
        0xc0058593, // addi a1, a1, -0x400
        0x00000073, // ecall(halt)
    ]);

    program_from_instructions(0x4000, iter)
}
