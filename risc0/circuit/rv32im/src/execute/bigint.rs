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

use super::{
    bibc::{self, BigIntIO},
    platform::*,
    r0vm::{LoadOp, Risc0Context},
};

/// BigInt width, in words, handled by the BigInt accelerator circuit.
pub(crate) const BIGINT_WIDTH_WORDS: usize = 4;

/// BigInt width, in bytes, handled by the BigInt accelerator circuit.
pub(crate) const BIGINT_WIDTH_BYTES: usize = BIGINT_WIDTH_WORDS * WORD_SIZE;

pub(crate) type BigIntBytes = [u8; BIGINT_WIDTH_BYTES];
pub(crate) type BigIntWitness = BTreeMap<WordAddr, BigIntBytes>;

fn bytes_le_to_bigint(bytes: &[u8]) -> Natural {
    let mut limbs = Vec::with_capacity((bytes.len() + 3) / 4);

    for chunk in bytes.chunks(4) {
        let mut arr = [0u8; 4];
        arr[..chunk.len()].copy_from_slice(chunk);
        limbs.push(u32::from_le_bytes(arr));
    }

    Natural::from_limbs_asc(&limbs)
}

fn bigint_to_bytes_le(value: &Natural) -> Vec<u8> {
    let limbs = value.to_limbs_asc();
    let mut out = Vec::with_capacity(limbs.len() * 4);

    for limb in limbs {
        out.extend_from_slice(&limb.to_le_bytes());
    }
    out
}

struct BigIntIOImpl<'a> {
    ctx: &'a mut dyn Risc0Context,
    mode: u32,
    pub witness: BigIntWitness,
}

impl<'a> BigIntIOImpl<'a> {
    pub fn new(ctx: &'a mut dyn Risc0Context, mode: u32) -> Self {
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

impl BigIntIO for BigIntIOImpl<'_> {
    fn load(&mut self, arena: u32, offset: u32, count: u32) -> Result<Natural> {
        tracing::trace!("load(arena: {arena}, offset: {offset}, count: {count})");
        let base = self
            .ctx
            .load_aligned_addr_from_machine_register(LoadOp::Load, arena as usize)?;
        let addr = base + offset * BIGINT_WIDTH_WORDS as u32;
        check_bigint_addr(addr, self.mode)?;
        let bytes = self
            .ctx
            .load_region(LoadOp::Load, addr.baddr(), count as usize)?;
        let val = bytes_le_to_bigint(&bytes);
        Ok(val)
    }

    fn store(&mut self, arena: u32, offset: u32, count: u32, value: &Natural) -> Result<()> {
        let base = self
            .ctx
            .load_aligned_addr_from_machine_register(LoadOp::Load, arena as usize)?;
        let addr = base + offset * BIGINT_WIDTH_WORDS as u32;
        check_bigint_addr(addr, self.mode)?;
        tracing::trace!("store(arena: {arena}, offset: {offset}, count: {count}, addr: {addr:?}, value: {value})");

        let mut witness = vec![0u8; count as usize];
        let bytes = bigint_to_bytes_le(value);
        witness[..bytes.len()].copy_from_slice(&bytes);
        let chunks = witness.chunks_exact(BIGINT_WIDTH_BYTES);
        assert_eq!(chunks.len(), count as usize / BIGINT_WIDTH_BYTES);
        for (i, chunk) in chunks.enumerate() {
            let addr = addr + i * BIGINT_WIDTH_WORDS;
            let chunk = chunk.try_into().unwrap();
            self.witness.insert(addr, chunk);
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

pub fn ecall_execute(ctx: &mut dyn Risc0Context) -> Result<usize> {
    let exec = ecall(ctx)?;
    let cycles = exec.verify_program_size + 1;
    for (addr, bytes) in exec.witness {
        for (i, chunk) in bytes.chunks_exact(WORD_SIZE).enumerate() {
            let word = u32::from_le_bytes(chunk.try_into().unwrap());
            ctx.store_u32(addr + i, word)?;
        }
    }
    Ok(cycles)
}

pub(crate) fn ecall(ctx: &mut dyn Risc0Context) -> Result<BigIntExec> {
    tracing::debug!("ecall");

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
    tracing::debug!("blob_ptr: {blob_ptr:?}");
    tracing::debug!(
        "nondet_program_ptr: {nondet_program_ptr:?}, nondet_program_size: {nondet_program_size}"
    );

    let program_bytes = ctx.load_region(
        LoadOp::Load,
        nondet_program_ptr.baddr(),
        nondet_program_size as usize * WORD_SIZE,
    )?;
    tracing::debug!("program_bytes: {}", program_bytes.len());
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
