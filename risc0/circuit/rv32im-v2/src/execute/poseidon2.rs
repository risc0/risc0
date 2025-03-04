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

use anyhow::{bail, Result};
use risc0_binfmt::WordAddr;
use risc0_zkp::{
    core::{
        digest::DIGEST_WORDS,
        hash::poseidon2::{
            CELLS, M_INT_DIAG_HZN, ROUNDS_HALF_FULL, ROUNDS_PARTIAL, ROUND_CONSTANTS,
        },
    },
    field::baby_bear::{self},
};

use crate::{
    execute::{
        platform::*,
        r0vm::{LoadOp, Risc0Context},
    },
    zirgen::circuit::ExtVal,
};

const BABY_BEAR_P_U32: u32 = baby_bear::P;
const BABY_BEAR_P_U64: u64 = baby_bear::P as u64;

#[derive(Clone, Debug, Default)]
pub(crate) struct Poseidon2State {
    pub has_state: u32,
    pub state_addr: u32,
    pub buf_out_addr: u32,
    pub is_elem: u32,
    pub check_out: u32,
    pub load_tx_type: u32,
    pub next_state: CycleState,
    pub sub_state: u32,
    pub buf_in_addr: u32,
    pub count: u32,
    pub mode: u32,
    pub inner: [u32; CELLS],
    pub zcheck: ExtVal,
}

impl Poseidon2State {
    fn new_ecall(state_addr: u32, buf_in_addr: u32, buf_out_addr: u32, bits_count: u32) -> Self {
        let is_elem = bits_count & PFLAG_IS_ELEM;
        let check_out = bits_count & PFLAG_CHECK_OUT;
        Self {
            state_addr,
            buf_in_addr,
            buf_out_addr,
            has_state: (state_addr != 0) as u32,
            is_elem: (is_elem != 0) as u32,
            check_out: (check_out != 0) as u32,
            count: bits_count & 0xffff,
            mode: 1,
            load_tx_type: tx::READ,
            next_state: CycleState::PoseidonEntry,
            ..Default::default()
        }
    }

    fn step(
        &mut self,
        ctx: &mut dyn Risc0Context,
        cur_state: &mut CycleState,
        next_state: CycleState,
        sub_state: u32,
    ) {
        self.next_state = next_state;
        self.sub_state = sub_state;
        ctx.on_poseidon2_cycle(*cur_state, self);
        *cur_state = next_state;
    }

    pub(crate) fn rest(
        &mut self,
        ctx: &mut dyn Risc0Context,
        final_state: CycleState,
    ) -> Result<()> {
        let mut cur_state = self.next_state;
        let state_addr = WordAddr(self.state_addr);

        // If we have state, load it
        if self.has_state == 1 {
            // tracing::trace!("has_state");
            self.step(ctx, &mut cur_state, CycleState::PoseidonLoadState, 0);
            for i in 0..DIGEST_WORDS {
                self.inner[DIGEST_WORDS * 2 + i] = ctx.load_u32(LoadOp::Record, state_addr + i)?;
            }
        }

        // While we have data to process
        let mut buf_in_addr = WordAddr(self.buf_in_addr);
        // tracing::debug!("buf_in_addr: {buf_in_addr:?}");

        // Pre-compute iteration count for faster loops
        let iterations = self.count;
        for _ in 0..iterations {
            // Do load
            self.step(ctx, &mut cur_state, CycleState::PoseidonLoadIn, 0);

            // Use a temporary buffer to avoid direct manipulation of self.inner during loading
            let mut temp_buffer = [0u32; 2 * DIGEST_WORDS];

            if self.is_elem != 0 {
                // Load all words first, then copy to inner array
                for item in &mut temp_buffer[..DIGEST_WORDS] {
                    *item = ctx.load_u32(LoadOp::Record, buf_in_addr.postfix_inc())?;
                }
                // Copy to inner in one batch
                self.inner[..DIGEST_WORDS].copy_from_slice(&temp_buffer[..DIGEST_WORDS]);

                self.buf_in_addr = buf_in_addr.0;
                self.step(ctx, &mut cur_state, CycleState::PoseidonLoadIn, 1);

                for item in &mut temp_buffer[DIGEST_WORDS..2 * DIGEST_WORDS] {
                    *item = ctx.load_u32(LoadOp::Record, buf_in_addr.postfix_inc())?;
                }
                // Copy second half in one batch
                self.inner[DIGEST_WORDS..2 * DIGEST_WORDS]
                    .copy_from_slice(&temp_buffer[DIGEST_WORDS..2 * DIGEST_WORDS]);
            } else {
                // We need the index for the computation, so suppress the clippy warning
                #[allow(clippy::needless_range_loop)]
                for i in 0..DIGEST_WORDS {
                    let word = ctx.load_u32(LoadOp::Record, buf_in_addr.postfix_inc())?;
                    temp_buffer[2 * i] = word & 0xffff;
                    temp_buffer[2 * i + 1] = word >> 16;
                }
                // Copy to inner in one batch
                self.inner[..2 * DIGEST_WORDS].copy_from_slice(&temp_buffer[..2 * DIGEST_WORDS]);
            }
            self.buf_in_addr = buf_in_addr.0;

            // Keep the original round structure to maintain constraint consistency
            self.multiply_by_m_ext();
            for i in 0..ROUNDS_HALF_FULL {
                self.step(ctx, &mut cur_state, CycleState::PoseidonExtRound, i as u32);
                self.do_ext_round(i);
            }
            self.step(ctx, &mut cur_state, CycleState::PoseidonIntRound, 0);
            self.do_int_rounds();
            for i in ROUNDS_HALF_FULL..ROUNDS_HALF_FULL * 2 {
                self.step(ctx, &mut cur_state, CycleState::PoseidonExtRound, i as u32);
                self.do_ext_round(i);
            }
            self.count -= 1;
        }

        self.step(ctx, &mut cur_state, CycleState::PoseidonDoOut, 0);

        let buf_out_addr = WordAddr(self.buf_out_addr);
        if self.check_out != 0 {
            for i in 0..DIGEST_WORDS {
                let addr = buf_out_addr + i;
                let word = ctx.load_u32(LoadOp::Record, addr)?;
                let cell = self.inner[i];
                if word != cell {
                    tracing::warn!(
                        "buf_in_addr: {:?}, buf_out_addr: {buf_out_addr:?}, cell: {i}",
                        WordAddr(self.buf_in_addr)
                    );
                    bail!("poseidon2 check failed: {word:#010x} != {cell:#010x}");
                }
            }
        } else {
            for i in 0..DIGEST_WORDS {
                ctx.store_u32(buf_out_addr + i, self.inner[i])?;
            }
        }

        self.buf_in_addr = 0;

        if self.has_state == 1 {
            self.step(ctx, &mut cur_state, CycleState::PoseidonStoreState, 0);
            for i in 0..DIGEST_WORDS {
                ctx.store_u32(state_addr + i, self.inner[DIGEST_WORDS * 2 + i])?;
            }
        }

        self.step(ctx, &mut cur_state, final_state, 0);

        Ok(())
    }

    // Optimized method for multiplication by M_EXT.
    // See appendix B of Poseidon2 paper for additional details.
    fn multiply_by_m_ext(&mut self) {
        // Pre-allocate output array
        let mut out = [0u32; CELLS];
        let mut tmp_sums = [0u32; 4];

        // Process 4 elements at a time for better cache utilization
        for i in 0..CELLS / 4 {
            // Get a reference to the current 4-element chunk to reduce array access overhead
            let base_idx = i * 4;
            let chunk_in = &self.inner[base_idx..base_idx + 4];

            // Use the 4x4 circulant multiplication
            let chunk =
                multiply_by_4x4_circulant(&[chunk_in[0], chunk_in[1], chunk_in[2], chunk_in[3]]);

            // Update sums and output values in a single pass
            for j in 0..4 {
                // Convert once to u64 to avoid potential overflow
                let to_add = chunk[j] as u64 % BABY_BEAR_P_U64;
                let to_add_u32 = to_add as u32;

                // Update temporary sums
                tmp_sums[j] = (tmp_sums[j] + to_add_u32) % BABY_BEAR_P_U32;

                // Update output array
                let out_idx = base_idx + j;
                out[out_idx] = (out[out_idx] + to_add_u32) % BABY_BEAR_P_U32;
            }
        }

        // Final combination step
        for i in 0..CELLS {
            self.inner[i] = (out[i] + tmp_sums[i % 4]) % BABY_BEAR_P_U32;
        }
    }

    // Exploit the fact that off-diagonal entries of M_INT are all 1.
    fn multiply_by_m_int(&mut self) {
        // Exploit the fact that off-diagonal entries of M_INT are all 1.
        let mut sum = 0u64;
        for val in self.inner.iter() {
            sum += *val as u64;
        }
        sum %= BABY_BEAR_P_U64;

        // Following the reference implementation:
        // cells[i] = sum + M_INT_DIAG_HZN[i] * cells[i];
        for (i, diag) in M_INT_DIAG_HZN.iter().enumerate().take(CELLS) {
            let curr_val = self.inner[i] as u64;
            let diag_val = diag.as_u32() as u64;

            // Directly apply the formula from the reference implementation
            let new_val = (sum + (diag_val * curr_val) % BABY_BEAR_P_U64) % BABY_BEAR_P_U64;
            self.inner[i] = new_val as u32;
        }
    }

    fn do_ext_round(&mut self, mut idx: usize) {
        // Adjust index if needed
        if idx >= ROUNDS_HALF_FULL {
            idx += ROUNDS_PARTIAL;
        }

        // Add round constants to all cells
        self.add_round_constants_full(idx);

        // Apply S-box to each cell
        #[allow(clippy::needless_range_loop)]
        for i in 0..CELLS {
            // Apply the S-box function directly to avoid function call overhead
            let x = self.inner[i] as u64;
            let x2 = (x * x) % BABY_BEAR_P_U64;
            let x4 = (x2 * x2) % BABY_BEAR_P_U64;
            let x6 = (x4 * x2) % BABY_BEAR_P_U64;
            let x7 = (x6 * x) % BABY_BEAR_P_U64;
            self.inner[i] = x7 as u32;
        }

        // Apply matrix multiplication
        self.multiply_by_m_ext();
    }

    fn do_int_rounds(&mut self) {
        // Process all internal rounds at once for better efficiency
        for i in 0..ROUNDS_PARTIAL {
            // Add round constants only to the first element (partial round)
            self.add_round_constants_partial(ROUNDS_HALF_FULL + i);

            // Apply S-box directly to the first element to avoid function call overhead
            {
                let x = self.inner[0] as u64;
                let x2 = (x * x) % BABY_BEAR_P_U64;
                let x4 = (x2 * x2) % BABY_BEAR_P_U64;
                let x6 = (x4 * x2) % BABY_BEAR_P_U64;
                let x7 = (x6 * x) % BABY_BEAR_P_U64;
                self.inner[0] = x7 as u32;
            }

            // Apply internal matrix multiplication
            self.multiply_by_m_int();
        }
    }

    fn add_round_constants_full(&mut self, round: usize) {
        for i in 0..CELLS {
            self.inner[i] += ROUND_CONSTANTS[round * CELLS + i].as_u32();
            self.inner[i] %= BABY_BEAR_P_U32;
        }
    }

    fn add_round_constants_partial(&mut self, round: usize) {
        self.inner[0] += ROUND_CONSTANTS[round * CELLS].as_u32();
        self.inner[0] %= BABY_BEAR_P_U32;
    }
}

fn multiply_by_4x4_circulant(x: &[u32; 4]) -> [u32; 4] {
    // See appendix B of Poseidon2 paper.
    const CIRC_FACTOR_2: u64 = 2;
    const CIRC_FACTOR_4: u64 = 4;

    // Convert all inputs to u64 at once to reduce conversions
    let x0 = x[0] as u64;
    let x1 = x[1] as u64;
    let x2 = x[2] as u64;
    let x3 = x[3] as u64;

    // Combine operations to reduce the number of modulo operations
    // Only apply modulo when necessary to prevent overflow
    let t0 = (x0 + x1) % BABY_BEAR_P_U64;
    let t1 = (x2 + x3) % BABY_BEAR_P_U64;

    // Use temporary variables with descriptive names
    let two_x1_plus_t1 = (CIRC_FACTOR_2 * x1 + t1) % BABY_BEAR_P_U64;
    let two_x3_plus_t0 = (CIRC_FACTOR_2 * x3 + t0) % BABY_BEAR_P_U64;

    let four_t1_plus_two_x3_plus_t0 = (CIRC_FACTOR_4 * t1 + two_x3_plus_t0) % BABY_BEAR_P_U64;
    let four_t0_plus_two_x1_plus_t1 = (CIRC_FACTOR_4 * t0 + two_x1_plus_t1) % BABY_BEAR_P_U64;

    let result0 = (two_x3_plus_t0 + four_t0_plus_two_x1_plus_t1) % BABY_BEAR_P_U64;
    let result2 = (two_x1_plus_t1 + four_t1_plus_two_x3_plus_t0) % BABY_BEAR_P_U64;

    // Convert back to u32 only at the end
    [
        result0 as u32,
        four_t0_plus_two_x1_plus_t1 as u32,
        result2 as u32,
        four_t1_plus_two_x3_plus_t0 as u32,
    ]
}

pub(crate) struct Poseidon2;

impl Poseidon2 {
    pub fn ecall(ctx: &mut dyn Risc0Context) -> Result<()> {
        tracing::trace!("ecall");
        let state_addr = ctx.load_machine_register(LoadOp::Record, REG_A0)?;
        let buf_in_addr = ctx.load_machine_register(LoadOp::Record, REG_A1)?;
        let buf_out_addr = ctx.load_machine_register(LoadOp::Record, REG_A2)?;
        let bits_count = ctx.load_machine_register(LoadOp::Record, REG_A3)?;
        let mut p2 = Poseidon2State::new_ecall(state_addr, buf_in_addr, buf_out_addr, bits_count);
        p2.rest(ctx, CycleState::Decode)
    }
}
