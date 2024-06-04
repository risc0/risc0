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

use std::collections::BTreeMap;

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

pub fn basic() -> Program {
    Program {
        entry: 0x4000,
        image: BTreeMap::from([
            (0x4000, 0x1234b137), // lui x2, 0x1234b000
            (0x4004, 0xf387e1b7), // lui x3, 0xf387e000
            (0x4008, 0x003100b3), // add x1, x2, x3
            (0x400c, 0x000045b7), // lui a1, 0x4
            (0x4010, 0x00000073), // ecall(halt)
        ]),
    }
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
    Program {
        entry: 0x4000,
        image: BTreeMap::from([
            (0x4000, 0x00000713), // li      a4,0
            (0x4004, 0x06400793), // li      a5,100
            (0x4008, 0x00170713), // add     a4,a4,1
            (0x400c, 0xfef74ee3), // blt     a4,a5,8 <loop>
            (0x4010, 0x010005b7), // lui     a1,0x1000
            (0x4014, 0x00000073), // ecall
        ]),
    }
}

pub fn large_text() -> Program {
    let entry = 0x4000;
    let mut image = BTreeMap::new();
    let mut pc = entry;
    for _ in 0..2500 {
        image.insert(pc, 0x1234b137); // lui x2, 0x1234b000
        pc += WORD_SIZE as u32;
    }
    image.insert(pc, 0x000055b7); // lui a1, 0x00005000
    pc += WORD_SIZE as u32;
    image.insert(pc, 0xc0058593); // addi a1, a1, -0x400
    pc += WORD_SIZE as u32;
    image.insert(pc, 0x00000073); // ecall(halt)
    Program { entry, image }
}
