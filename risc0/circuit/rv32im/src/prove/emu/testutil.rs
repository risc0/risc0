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
        0x4000,
        [
            0x1234b137, // lui x2, 0x1234b000
            0xf387e1b7, // lui x3, 0xf387e000
            0x003100b3, // add x1, x2, x3
            0x000045b7, // lui a1, 0x4
            0x00000073, // ecall(halt)
        ],
    )
}

pub fn simple_loop() -> Program {
    loop_with_iters(100, 1)
}

pub fn loop_with_iters(limit: u32, step: u32) -> Program {
    // loop.asm:
    //
    // .global _boot
    // .text
    //
    // _boot:
    //     li      a4, 0         # i = 0
    //     lui     a5, 0xfffff   # Fill upper 20 bits of `limit`
    //     addi    a5, a5, -1    # Fill lower 12 bits of `limit`
    //     lui     a6, 0xfffff   # Fill upper 20 bits of `step`
    //     addi    a6, a6, -1    # Fill lower 12 bits of `step`
    // loop:
    //     add     a4, a4, a6    # i += step
    //     bltu    a4, a6, exit  # if (i < step)  goto exit (step overflow)
    //     bltu    a4, a5, loop  # if (i < limit) goto loop
    // exit:
    //     lui     a1, 0x1000    # Set digest address to dummy null page
    //     ecall                 # Halt (and catch fire)
    //
    // riscv32-unknown-elf-as loop.asm -o loop; riscv32-unknown-elf-objdump -d loop
    //
    // NOTE: Checks use `bltu` instead of `blt` because of `u32`.

    // Pack `limit` into `a5` by encoding it directly in the instructions as:
    // - Load Upper Imm (20 bits)
    // - ADD Immediate (12 bits)
    //
    // This is based off the instruction encoding for setting all 32 bits:
    // - 0xfffff7b7: lui  a5, 0xfffff
    // - 0xfff78793: addi a5, a5, -1
    let lui_a5 = (limit & 0xfffff000) | 0x7b7;
    let addi_a5 = ((limit & 0xfff) << 20) | 0x78793;

    // Pack `step` into `a6` similarly to `limit`.
    //
    // This is based off the instruction encoding for setting all 32 bits:
    // - 0xfffff837: lui  a6, 0xfffff
    // - 0xfff80813: addi a6, a6, -1
    let lui_a6 = (step & 0xfffff000) | 0x837;
    let addi_a6 = ((step & 0xfff) << 20) | 0x80813;

    program_from_instructions(
        0x4000,
        [
            // _boot:
            0x00000713, // li    a4, 0
            lui_a5,     // lui   a5,     (upper 20 bits of `limit`)
            addi_a5,    // addi  a5, a5, (lower 12 bits of `limit`)
            lui_a6,     // lui   a6,     (upper 20 bits of `step`)
            addi_a6,    // addi  a6, a6, (lower 12 bits of `step`)
            // loop:
            0x01070733, // add   a4, a4, a6         [i += step]
            0x01076463, // bltu  a4, a6, 20 <exit>  [i < step on overflow]
            0xfef76ce3, // bltu  a4, a5, 14 <loop>  [i < limit]
            // exit:
            0x010005b7, // lui   a1, 0x1000
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
