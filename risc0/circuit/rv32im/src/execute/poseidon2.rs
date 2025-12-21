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
use risc0_zkp::core::{digest::DIGEST_WORDS, hash::poseidon2::CELLS};

use crate::execute::{
    platform::*,
    r0vm::{LoadOp, Risc0Context},
};

#[derive(Clone, Debug, Default)]
pub(crate) struct Poseidon2State {
    pub has_state: u32,
    pub state_addr: u32,
    pub buf_out_addr: u32,
    pub is_elem: u32,
    pub check_out: u32,
    pub next_state: CycleState,
    pub sub_state: u32,
    pub buf_in_addr: u32,
    pub count: u32,
    pub inner: [u32; CELLS],
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
            next_state: CycleState::PoseidonEntry,
            ..Default::default()
        }
    }

    fn step(
        &mut self,
        ctx: &mut (impl Risc0Context + ?Sized),
        cur_state: &mut CycleState,
        next_state: CycleState,
        sub_state: u32,
    ) {
        self.next_state = next_state;
        self.sub_state = sub_state;
        ctx.on_poseidon2_cycle(*cur_state, self);
        *cur_state = next_state;
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

            if self.count != 0 {
                self.trash_digest(ctx)?;
            }
        }

        self.store_buf_out(ctx, &mut cur_state)?;

        self.buf_in_addr = 0;

        if self.has_state == 1 {
            self.store_p2_state(ctx, &mut cur_state)?;
        } else {
            self.trash_state(ctx)?;
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

    /// In M3, store the digest part of the sponge to the trash address.
    fn trash_digest(&mut self, ctx: &mut (impl Risc0Context + ?Sized)) -> Result<()> {
        if ctx.circuit_version() == RV32IM_M3_CIRCUIT_VERSION {
            for i in 0..DIGEST_WORDS {
                ctx.store_u32(RV32IM_M3_P2_TRASH_ADDR.waddr() + i, self.inner[i])?;
            }
        }
        Ok(())
    }

    /// In M3, store the preserved state part of the sponge to the trash address.
    fn trash_state(&mut self, ctx: &mut (impl Risc0Context + ?Sized)) -> Result<()> {
        if ctx.circuit_version() == RV32IM_M3_CIRCUIT_VERSION {
            for i in 0..DIGEST_WORDS {
                ctx.store_u32(
                    RV32IM_M3_P2_TRASH_ADDR.waddr() + i,
                    self.inner[DIGEST_WORDS * 2 + i],
                )?;
            }
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
