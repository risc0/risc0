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

use anyhow::{Result, bail};
use risc0_binfmt::WordAddr;
use risc0_zkp::{
    core::{
        digest::DIGEST_WORDS,
        hash::poseidon2::{
            CELLS, M_INT_DIAG_HZN, ROUND_CONSTANTS, ROUNDS_HALF_FULL, ROUNDS_PARTIAL,
        },
    },
    field::baby_bear::{self},
};

use crate::execute::{
    platform::*,
    r0vm::{LoadOp, Risc0Context},
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
    #[cfg(feature = "prove")]
    pub load_tx_type: u32,
    pub next_state: CycleState,
    pub sub_state: u32,
    pub buf_in_addr: u32,
    pub count: u32,
    #[cfg(feature = "prove")]
    pub mode: u32,
    pub inner: [u32; CELLS],
    #[cfg(feature = "prove")]
    pub zcheck: crate::zirgen::circuit::ExtVal,
}

impl Poseidon2State {
    fn new_ecall(
        state_addr: WordAddr,
        buf_in_addr: WordAddr,
        buf_out_addr: WordAddr,
        bits_count: u32,
    ) -> Self {
        let is_elem = bits_count & PFLAG_IS_ELEM;
        let check_out = bits_count & PFLAG_CHECK_OUT;
        Self {
            state_addr: state_addr.0,
            buf_in_addr: buf_in_addr.0,
            buf_out_addr: buf_out_addr.0,
            has_state: if state_addr.is_null() { 0 } else { 1 },
            is_elem: if is_elem == 0 { 0 } else { 1 },
            check_out: if check_out == 0 { 0 } else { 1 },
            count: bits_count & 0xffff,
            #[cfg(feature = "prove")]
            mode: 1,
            #[cfg(feature = "prove")]
            load_tx_type: tx::READ,
            next_state: CycleState::PoseidonEntry,
            ..Default::default()
        }
    }

    fn step<C>(
        &mut self,
        ctx: &mut C,
        cur_state: &mut CycleState,
        next_state: CycleState,
        sub_state: u32,
    ) where
        C: Risc0Context + ?Sized,
    {
        self.next_state = next_state;
        self.sub_state = sub_state;
        ctx.on_poseidon2_cycle(*cur_state, self);
        *cur_state = next_state;
    }

    pub(crate) fn rest(
        &mut self,
        ctx: &mut (impl Risc0Context + ?Sized),
        final_state: CycleState,
    ) -> Result<()> {
        self.rest_with_mix(ctx, final_state, |p2, cur_state, ctx| {
            p2.mix(ctx, cur_state);
            Ok(())
        })
    }

    pub(crate) fn rest_with_mix<F, C>(
        &mut self,
        ctx: &mut C,
        final_state: CycleState,
        mut mix: F,
    ) -> Result<()>
    where
        F: FnMut(&mut Self, &mut CycleState, &mut C) -> Result<()>,
        C: Risc0Context + ?Sized,
    {
        let mut cur_state = self.next_state;

        // If we have state, load it
        if self.has_state == 1 {
            self.load_p2_state(ctx, &mut cur_state)?;
        }

        // While we have data to process
        // tracing::debug!("buf_in_addr: {buf_in_addr:?}");
        while self.count > 0 {
            self.load_buf_in(ctx, &mut cur_state)?;
            mix(self, &mut cur_state, ctx)?;
            self.count -= 1;
        }

        self.store_buf_out(ctx, &mut cur_state)?;

        self.buf_in_addr = 0;

        if self.has_state == 1 {
            self.store_p2_state(ctx, &mut cur_state)?;
        }

        self.step(ctx, &mut cur_state, final_state, 0);

        Ok(())
    }

    fn load_p2_state(
        &mut self,
        ctx: &mut (impl Risc0Context + ?Sized),
        cur_state: &mut CycleState,
    ) -> Result<()> {
        let state_addr = WordAddr(self.state_addr);

        self.step(ctx, cur_state, CycleState::PoseidonLoadState, 0);
        for i in 0..DIGEST_WORDS {
            self.inner[DIGEST_WORDS * 2 + i] = ctx.load_u32(LoadOp::Record, state_addr + i)?;
        }
        Ok(())
    }

    fn store_p2_state(
        &mut self,
        ctx: &mut (impl Risc0Context + ?Sized),
        cur_state: &mut CycleState,
    ) -> Result<()> {
        let state_addr = WordAddr(self.state_addr);

        self.step(ctx, cur_state, CycleState::PoseidonStoreState, 0);
        for i in 0..DIGEST_WORDS {
            ctx.store_u32(state_addr + i, self.inner[DIGEST_WORDS * 2 + i])?;
        }
        Ok(())
    }

    fn load_buf_in(
        &mut self,
        ctx: &mut (impl Risc0Context + ?Sized),
        cur_state: &mut CycleState,
    ) -> Result<()> {
        let mut buf_in_addr = WordAddr(self.buf_in_addr);
        self.step(ctx, cur_state, CycleState::PoseidonLoadIn, 0);

        // If the data at buf_in_addr is already encoded as field elements, then load iteration can
        // process 16 elements. Otherwise, each u32 needs to be split into two halves and each load
        // iteration processes 8 u32s (roughly half the rate).
        if self.is_elem != 0 {
            for i in 0..DIGEST_WORDS {
                self.inner[i] = ctx.load_u32(LoadOp::Record, buf_in_addr.postfix_inc())?;
            }
            self.buf_in_addr = buf_in_addr.0;
            self.step(ctx, cur_state, CycleState::PoseidonLoadIn, 1);
            for i in 0..DIGEST_WORDS {
                self.inner[DIGEST_WORDS + i] =
                    ctx.load_u32(LoadOp::Record, buf_in_addr.postfix_inc())?;
            }
            self.buf_in_addr = buf_in_addr.0;
        } else {
            for i in 0..DIGEST_WORDS {
                let word = ctx.load_u32(LoadOp::Record, buf_in_addr.postfix_inc())?;
                self.inner[2 * i] = word & 0xffff;
                self.inner[2 * i + 1] = word >> 16;
            }
            self.buf_in_addr = buf_in_addr.0;
        }
        Ok(())
    }

    fn store_buf_out(
        &mut self,
        ctx: &mut (impl Risc0Context + ?Sized),
        cur_state: &mut CycleState,
    ) -> Result<()> {
        self.step(ctx, cur_state, CycleState::PoseidonDoOut, 0);
        let buf_out_addr = WordAddr(self.buf_out_addr);

        // If check_out is true, then the data at buf_out is asserted to be equal to the computed
        // digest. If not, then the value at buf_out is has the computed digest written to it.
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
        Ok(())
    }

    pub(crate) fn mix<C>(&mut self, ctx: &mut C, cur_state: &mut CycleState)
    where
        C: Risc0Context + ?Sized,
    {
        self.multiply_by_m_ext();
        for i in 0..ROUNDS_HALF_FULL {
            self.step(ctx, cur_state, CycleState::PoseidonExtRound, i as u32);
            self.do_ext_round(i);
        }
        self.step(ctx, cur_state, CycleState::PoseidonIntRound, 0);
        self.do_int_rounds();
        for i in ROUNDS_HALF_FULL..ROUNDS_HALF_FULL * 2 {
            self.step(ctx, cur_state, CycleState::PoseidonExtRound, i as u32);
            self.do_ext_round(i);
        }
    }

    // Optimized method for multiplication by M_EXT.
    // See appendix B of Poseidon2 paper for additional details.
    fn multiply_by_m_ext(&mut self) {
        let mut out = [0; CELLS];
        let mut tmp_sums = [0; 4];

        for i in 0..CELLS / 4 {
            let chunk = multiply_by_4x4_circulant(&[
                self.inner[i * 4],
                self.inner[i * 4 + 1],
                self.inner[i * 4 + 2],
                self.inner[i * 4 + 3],
            ]);
            for j in 0..4 {
                let to_add = chunk[j] as u64;
                let to_add = (to_add % BABY_BEAR_P_U64) as u32;
                tmp_sums[j] += to_add;
                tmp_sums[j] %= BABY_BEAR_P_U32;
                out[i * 4 + j] += to_add;
                out[i * 4 + j] %= BABY_BEAR_P_U32;
            }
        }
        for i in 0..CELLS {
            self.inner[i] = (out[i] + tmp_sums[i % 4]) % BABY_BEAR_P_U32;
        }
    }

    // Exploit the fact that off-diagonal entries of M_INT are all 1.
    fn multiply_by_m_int(&mut self) {
        let mut sum = 0u64;
        for i in 0..CELLS {
            sum += self.inner[i] as u64;
        }
        sum %= BABY_BEAR_P_U64;
        for (i, diag) in M_INT_DIAG_HZN.iter().enumerate().take(CELLS) {
            let diag = diag.as_u32() as u64;
            let cell = self.inner[i] as u64;
            self.inner[i] = ((sum + diag * cell) % BABY_BEAR_P_U64) as u32;
        }
    }

    fn do_ext_round(&mut self, mut idx: usize) {
        if idx >= ROUNDS_HALF_FULL {
            idx += ROUNDS_PARTIAL;
        }

        self.add_round_constants_full(idx);
        for i in 0..CELLS {
            self.inner[i] = sbox2(self.inner[i]);
        }

        self.multiply_by_m_ext();
    }

    fn do_int_rounds(&mut self) {
        for i in 0..ROUNDS_PARTIAL {
            self.add_round_constants_partial(ROUNDS_HALF_FULL + i);
            self.inner[0] = sbox2(self.inner[0]);
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
    let t0 = (x[0] as u64 + x[1] as u64) % BABY_BEAR_P_U64;
    let t1 = (x[2] as u64 + x[3] as u64) % BABY_BEAR_P_U64;
    let t2 = (CIRC_FACTOR_2 * x[1] as u64 + t1) % BABY_BEAR_P_U64;
    let t3 = (CIRC_FACTOR_2 * x[3] as u64 + t0) % BABY_BEAR_P_U64;
    let t4 = (CIRC_FACTOR_4 * t1 + t3) % BABY_BEAR_P_U64;
    let t5 = (CIRC_FACTOR_4 * t0 + t2) % BABY_BEAR_P_U64;
    let t6 = (t3 + t5) % BABY_BEAR_P_U64;
    let t7 = (t2 + t4) % BABY_BEAR_P_U64;
    [t6 as u32, t5 as u32, t7 as u32, t4 as u32]
}

fn sbox2(x: u32) -> u32 {
    let x = x as u64;
    let x2 = (x * x) % BABY_BEAR_P_U64;
    let x4 = (x2 * x2) % BABY_BEAR_P_U64;
    let x6 = (x4 * x2) % BABY_BEAR_P_U64;
    let x7 = (x6 * x) % BABY_BEAR_P_U64;
    x7 as u32
}

pub(crate) struct Poseidon2;

impl Poseidon2 {
    pub fn load_ecall(ctx: &mut (impl Risc0Context + ?Sized)) -> Result<Poseidon2State> {
        tracing::trace!("load_ecall");
        let state_addr = ctx.load_aligned_addr_from_machine_register(LoadOp::Record, REG_A0)?;
        let buf_in_addr = ctx.load_aligned_addr_from_machine_register(LoadOp::Record, REG_A1)?;
        let buf_out_addr = ctx.load_aligned_addr_from_machine_register(LoadOp::Record, REG_A2)?;
        let bits_count = ctx.load_machine_register(LoadOp::Record, REG_A3)?;
        Ok(Poseidon2State::new_ecall(
            state_addr,
            buf_in_addr,
            buf_out_addr,
            bits_count,
        ))
    }
}
