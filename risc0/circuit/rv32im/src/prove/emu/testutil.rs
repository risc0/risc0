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

/// SHA256 digest of empty commit and assumption.
const EMPTY_DIGEST_WORDS: &[u32] = &[
    0x5C176F83, 0x53F3C062, 0x42651683, 0x340B8B7E, 0x19D2D1F6, 0xAE4D7602, 0xB8C606B4, 0xB075B53D,
];

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
    //     lui     a1, 0x1000    # Set output to digest (see `digest_addr`)
    //     ecall                 # Halt (and catch fire)
    //
    // riscv32-unknown-elf-as loop.asm -o loop; riscv32-unknown-elf-objdump -d loop
    //
    // NOTE: Checks use `bltu` instead of `blt` because of `u32`.

    #[derive(Clone, Copy)]
    enum Reg {
        A1 = 0b01011,
        A5 = 0b01111,
        A6 = 0b10000,
    }

    /// Encodes a pair of `lui` (Load Upper Imm) and `addi` (ADD Immediate)
    /// instructions for loading a 32-bit value into the given register.
    ///
    /// This is based off the instruction encodings for setting all 32 bits:
    /// - 0xfffff7b7: lui  a5, 0xfffff
    /// - 0xfff78793: addi a5, a5, -1
    /// - 0xfffff837: lui  a6, 0xfffff
    /// - 0xfff80813: addi a6, a6, -1
    fn enc_load_u32(reg: Reg, val: u32) -> [u32; 2] {
        // Decompose value into high 20 bits and low 12 bits:
        let val_hi = val & 0xfffff000;
        let val_lo = val & 0xfff;

        // Encode register in `rd` and `rs1` offsets:
        let out_reg = (reg as u32) << 7;
        let in_reg = (reg as u32) << 15;

        // `lui` clears the register and sets the high 20 bits, which is also
        // encoded in the instruction at the high 20 bits.
        let lui = 0b0110111 | out_reg | val_hi;

        // `addi` adds a 12-bit immediate value, which is encoded in the
        // instruction at the high 12 bits.
        let addi = 0b0010011 | out_reg | in_reg | (val_lo << 20);

        [lui, addi]
    }

    let [lui_a5, addi_a5] = enc_load_u32(Reg::A5, limit);
    let [lui_a6, addi_a6] = enc_load_u32(Reg::A6, step);

    // Store the digest at offset past the instruction stream. We only need the
    // `lui` instruction because the low 12 bits are not set.
    let digest_addr = 0x10000;
    let [lui_a1, _] = enc_load_u32(Reg::A1, digest_addr);

    let mut program = program_from_instructions(
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
            lui_a1,     // lui   a1, (digest address)
            0x00000073, // ecall
        ],
    );

    // Write output digest.
    {
        let mut current_addr = digest_addr;

        program.image.extend(EMPTY_DIGEST_WORDS.iter().map(|&word| {
            let addr = current_addr;
            current_addr += WORD_SIZE as u32;
            (addr, word)
        }));
    }

    program
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
