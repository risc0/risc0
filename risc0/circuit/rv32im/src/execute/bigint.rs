// Copyright 2025 RISC Zero, Inc.
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

pub mod analyze;

use std::{collections::BTreeMap, io::Cursor};

use anyhow::{ensure, Result};
use malachite::Natural;
use risc0_binfmt::WordAddr;
use smallvec::SmallVec;

use super::{
    bibc::{self, BigIntIO},
    exec_debug, exec_trace,
    platform::*,
    r0vm::{LoadOp, Risc0Context},
};

/// BigInt width, in words, handled by the BigInt accelerator circuit.
pub(crate) const BIGINT_WIDTH_WORDS: usize = 4;

/// BigInt width, in bytes, handled by the BigInt accelerator circuit.
pub(crate) const BIGINT_WIDTH_BYTES: usize = BIGINT_WIDTH_WORDS * WORD_SIZE;

pub(crate) type BigIntBytes = [u8; BIGINT_WIDTH_BYTES];
pub(crate) type BigIntWitness = BTreeMap<WordAddr, BigIntBytes>;

struct BigIntIOImpl<'a, Risc0ContextT> {
    ctx: &'a mut Risc0ContextT,
    mode: u32,
    pub witness: BigIntWitness,
}

impl<'a, Risc0ContextT> BigIntIOImpl<'a, Risc0ContextT> {
    pub fn new(ctx: &'a mut Risc0ContextT, mode: u32) -> Self {
        Self {
            ctx,
            mode,
            witness: BTreeMap::new(),
        }
    }
}

fn check_bigint_addr(addr: WordAddr, mode: u32) -> Result<()> {
    ensure!(
        addr >= ZERO_PAGE_END_ADDR.waddr() && mode == 1 || addr < USER_BIGINT_END_ADDR.waddr(),
        "Invalid bigint address"
    );
    Ok(())
}

impl<Risc0ContextT: Risc0Context> BigIntIO for BigIntIOImpl<'_, Risc0ContextT> {
    fn load(&mut self, arena: u32, offset: u32, count: u32) -> Result<Natural> {
        exec_trace!("load(arena: {arena}, offset: {offset}, count: {count})");
        let base = self
            .ctx
            .load_aligned_addr_from_machine_register(LoadOp::Load, arena as usize)?;
        let start_addr = base + offset * BIGINT_WIDTH_WORDS as u32;
        check_bigint_addr(start_addr, self.mode)?;

        let word_count = count.div_ceil(4);
        // Note: Inline cap of 12 is chosen because blst_fp are 6 u64 limbs, so 12 u32 limbs
        let mut limbs = SmallVec::<[u32; 12]>::with_capacity(word_count as usize);
        let mut addr = start_addr;
        while addr < start_addr + word_count {
            limbs.push(self.ctx.load_u32(LoadOp::Load, addr)?);
            addr.inc();
        }

        if let Some(last_limb) = limbs.last_mut() {
            match count % 4 {
                1 => *last_limb &= 0x000000FF,
                2 => *last_limb &= 0x0000FFFF,
                3 => *last_limb &= 0x00FFFFFF,
                _ => {}
            }
        }

        Ok(Natural::from_limbs_asc(&limbs))
    }

    fn store(&mut self, arena: u32, offset: u32, count: u32, value: &Natural) -> Result<()> {
        let base = self
            .ctx
            .load_aligned_addr_from_machine_register(LoadOp::Load, arena as usize)?;
        let addr = base + offset * BIGINT_WIDTH_WORDS as u32;
        check_bigint_addr(addr, self.mode)?;

        exec_trace!("store(arena: {arena}, offset: {offset}, count: {count}, addr: {addr:?}, value: {value})");

        let limbs = value.to_limbs_asc();
        ensure!(
            count as usize >= limbs.len() * WORD_SIZE,
            "bigint_store: count ({count} bytes) too small for value ({} bytes)",
            limbs.len() * WORD_SIZE
        );
        ensure!(
            count as usize % BIGINT_WIDTH_BYTES == 0,
            "bigint_store: count ({count}) is not a multiple of {BIGINT_WIDTH_BYTES}"
        );

        let mut filled_chunks = 0;
        for (c_i, chunk) in limbs.chunks(BIGINT_WIDTH_WORDS).enumerate() {
            let mut new_chunk = [0; BIGINT_WIDTH_BYTES];
            for (w_i, word) in chunk.iter().enumerate() {
                let s = w_i * WORD_SIZE;
                new_chunk[s..(s + WORD_SIZE)].copy_from_slice(&word.to_le_bytes());
            }
            let addr = addr + c_i * BIGINT_WIDTH_WORDS;
            self.witness.insert(addr, new_chunk);
            filled_chunks += 1;
        }

        let padding = (count as usize / BIGINT_WIDTH_BYTES) - filled_chunks;
        for i in 0..padding {
            let addr = addr + (filled_chunks + i) * BIGINT_WIDTH_WORDS;
            self.witness.insert(addr, [0; BIGINT_WIDTH_BYTES]);
        }

        Ok(())
    }
}

pub(crate) struct BigIntExec {
    pub(crate) mode: u32,
    pub(crate) verify_program_ptr: WordAddr,
    pub(crate) verify_program_size: usize,
    pub(crate) witness: BigIntWitness,
}

fn write_witness_to_memory(witness: BigIntWitness, ctx: &mut impl Risc0Context) -> Result<()> {
    for (addr, bytes) in witness {
        for (i, chunk) in bytes.chunks_exact(WORD_SIZE).enumerate() {
            let word = u32::from_le_bytes(chunk.try_into().unwrap());
            ctx.store_u32(addr + i, word)?;
        }
    }
    Ok(())
}

pub fn ecall_execute(ctx: &mut impl Risc0Context) -> Result<usize> {
    let exec = ecall(ctx)?;
    let cycles = exec.verify_program_size + 1;
    write_witness_to_memory(exec.witness, ctx)?;

    Ok(cycles)
}

pub(crate) fn ecall(ctx: &mut impl Risc0Context) -> Result<BigIntExec> {
    exec_debug!("ecall");

    let mode = ctx.load_machine_register(LoadOp::Record, REG_T0)?;
    ensure!(
        mode == 0 || mode == 1,
        "Invalid mode for bigint ecall: {mode}"
    );
    let blob_ptr = ctx.load_aligned_addr_from_machine_register(LoadOp::Load, REG_A0)?;
    let nondet_program_ptr = ctx.load_aligned_addr_from_machine_register(LoadOp::Load, REG_T1)?;
    let verify_program_ptr =
        ctx.load_aligned_addr_from_machine_register(LoadOp::Record, REG_T2)? - 1;
    let consts_ptr = ctx.load_aligned_addr_from_machine_register(LoadOp::Load, REG_T3)?;

    let nondet_program_size = ctx.load_u32(LoadOp::Load, blob_ptr)?;
    let verify_program_size = ctx.load_u32(LoadOp::Load, blob_ptr + 1)? as usize;
    let consts_size = ctx.load_u32(LoadOp::Load, blob_ptr + 2)?;
    exec_debug!("blob_ptr: {blob_ptr:?}");
    exec_debug!(
        "nondet_program_ptr: {nondet_program_ptr:?}, nondet_program_size: {nondet_program_size}"
    );

    let program_bytes = ctx.load_region(
        LoadOp::Load,
        nondet_program_ptr.baddr(),
        nondet_program_size as usize * WORD_SIZE,
    )?;
    exec_debug!("program_bytes: {}", program_bytes.len());
    let mut cursor = Cursor::new(program_bytes);
    let program = bibc::Program::decode(&mut cursor)?;

    let witness = {
        let mut io = BigIntIOImpl::new(ctx, mode);
        program.eval(&mut io)?;
        std::mem::take(&mut io.witness)
    };

    ctx.load_region(
        LoadOp::Load,
        verify_program_ptr.baddr(),
        verify_program_size * WORD_SIZE,
    )?;
    ctx.load_region(
        LoadOp::Load,
        consts_ptr.baddr(),
        consts_size as usize * WORD_SIZE,
    )?;

    Ok(BigIntExec {
        mode,
        verify_program_ptr,
        verify_program_size,
        witness,
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::execute::r0vm::TestRisc0Context;
    use risc0_binfmt::ByteAddr;

    fn bigint_write(value: Vec<u32>, count: u32, expected: Vec<u8>) -> Result<()> {
        let mut test_context = TestRisc0Context::default();
        let arena = REG_A0;
        let base_addr = ByteAddr(0x1234);
        test_context
            .store_register(MACHINE_REGS_ADDR.waddr(), arena, base_addr.0)
            .unwrap();
        let mut io = BigIntIOImpl::new(&mut test_context, /*mod=*/ 0);

        let natural_in = Natural::from_limbs_asc(&value);
        io.store(arena as u32, 0, count, &natural_in)?;

        write_witness_to_memory(io.witness, &mut test_context).unwrap();

        let actual = test_context
            .load_region(LoadOp::Load, base_addr, expected.len())
            .unwrap();

        // Make sure we didn't write past the end of where we are checking
        test_context.assert_uninit(base_addr + expected.len());

        assert_eq!(actual, expected);
        Ok(())
    }

    fn bigint_read(input: Vec<u8>, count: u32, expected: Vec<u32>) -> Result<()> {
        let mut test_context = TestRisc0Context::default();
        let arena = REG_A0;
        let base_addr = ByteAddr(0x1234);
        test_context
            .store_register(MACHINE_REGS_ADDR.waddr(), arena, base_addr.0)
            .unwrap();

        test_context.store_region(base_addr, &input)?;

        let mut io = BigIntIOImpl::new(&mut test_context, /*mod=*/ 0);
        let natural_out = io.load(arena as u32, 0, count).unwrap();
        assert_eq!(natural_out.to_limbs_asc(), expected);
        Ok(())
    }

    #[test]
    fn bigint_write_basic_case() {
        bigint_write(
            vec![0x1000001, 0x1000002, 0x1000003, 0x1000004],
            16,
            vec![
                0x1, 0x0, 0x0, 0x1, // u32
                0x2, 0x0, 0x0, 0x1, // u32
                0x3, 0x0, 0x0, 0x1, // u32
                0x4, 0x0, 0x0, 0x1, // u32
            ],
        )
        .unwrap();
    }

    #[test]
    fn bigint_write_bigint_unaligned_count_errors() {
        assert_eq!(
            bigint_write(
                vec![0x1, 0x2, 0x3, 0x4],
                20,
                vec![
                    0x1, 0x0, 0x0, 0x0, // u32
                    0x2, 0x0, 0x0, 0x0, // u32
                    0x3, 0x0, 0x0, 0x0, // u32
                    0x4, 0x0, 0x0, 0x0, // u32
                ],
            )
            .unwrap_err()
            .to_string(),
            "bigint_store: count (20) is not a multiple of 16"
        );
    }

    #[test]
    fn bigint_write_bigint_aligned_count_larger_pads() {
        bigint_write(
            vec![0x1, 0x2, 0x3, 0x4],
            16 * 2,
            vec![
                0x1, 0x0, 0x0, 0x0, // u32
                0x2, 0x0, 0x0, 0x0, // u32
                0x3, 0x0, 0x0, 0x0, // u32
                0x4, 0x0, 0x0, 0x0, // u32
                0x0, 0x0, 0x0, 0x0, // u32
                0x0, 0x0, 0x0, 0x0, // u32
                0x0, 0x0, 0x0, 0x0, // u32
                0x0, 0x0, 0x0, 0x0, // u32
            ],
        )
        .unwrap();
    }

    #[test]
    fn bigint_write_small_unaligned_value() {
        bigint_write(
            vec![0x1],
            16 * 2,
            vec![
                0x1, 0x0, 0x0, 0x0, // u32
                0x0, 0x0, 0x0, 0x0, // u32
                0x0, 0x0, 0x0, 0x0, // u32
                0x0, 0x0, 0x0, 0x0, // u32
                0x0, 0x0, 0x0, 0x0, // u32
                0x0, 0x0, 0x0, 0x0, // u32
                0x0, 0x0, 0x0, 0x0, // u32
                0x0, 0x0, 0x0, 0x0, // u32
            ],
        )
        .unwrap();
    }

    #[test]
    fn bigint_write_unaligned_larger_value() {
        bigint_write(
            vec![0x1, 0x2, 0x3, 0x4, 0x5, 0x6],
            16 * 2,
            vec![
                0x1, 0x0, 0x0, 0x0, // u32
                0x2, 0x0, 0x0, 0x0, // u32
                0x3, 0x0, 0x0, 0x0, // u32
                0x4, 0x0, 0x0, 0x0, // u32
                0x5, 0x0, 0x0, 0x0, // u32
                0x6, 0x0, 0x0, 0x0, // u32
                0x0, 0x0, 0x0, 0x0, // u32
                0x0, 0x0, 0x0, 0x0, // u32
            ],
        )
        .unwrap();
    }

    #[test]
    fn bigint_write_count_too_small_errors() {
        assert_eq!(
            bigint_write(vec![0x1, 0x2, 0x3, 0x4], 14, vec![])
                .unwrap_err()
                .to_string(),
            "bigint_store: count (14 bytes) too small for value (16 bytes)"
        );
    }

    #[test]
    fn bigint_read_basic_case() {
        bigint_read(
            vec![
                0x1, 0x0, 0x0, 0x1, // u32
                0x2, 0x0, 0x0, 0x1, // u32
                0x3, 0x0, 0x0, 0x1, // u32
                0x4, 0x0, 0x0, 0x1, // u32
            ],
            16,
            vec![0x1000001, 0x1000002, 0x1000003, 0x1000004],
        )
        .unwrap();
    }

    #[test]
    fn bigint_read_unaligned() {
        for (count, last) in [(13, 0x4), (14, 0x304), (15, 0x20304)] {
            bigint_read(
                vec![
                    0x1, 0x0, 0x0, 0x1, // u32
                    0x2, 0x0, 0x0, 0x1, // u32
                    0x3, 0x0, 0x0, 0x1, // u32
                    0x4, 0x3, 0x2, 0x1, // u32
                ],
                count,
                vec![0x1000001, 0x1000002, 0x1000003, last],
            )
            .unwrap();
        }
    }
}
