// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use anyhow::{Result, bail};
use risc0_binfmt::WordAddr;
use risc0_zkp::core::hash::sha::BLOCK_WORDS;

use crate::execute::{
    platform::*,
    r0vm::{LoadOp, Risc0Context, guest_addr},
};

const SHA2_LOAD_STATE_CYCLES: u32 = 4;
const SHA2_LOAD_DATA_CYCLES: u32 = BLOCK_WORDS as u32;
const SHA2_MIX_CYCLES: u32 = 48;
const SHA2_STORE_CYCLES: u32 = 4;
const SHA2_BACK: usize =
    (SHA2_LOAD_STATE_CYCLES + SHA2_LOAD_DATA_CYCLES + SHA2_MIX_CYCLES) as usize;

#[derive(Clone, Debug)]
pub(crate) struct Sha2State {
    pub state_in_addr: WordAddr,
    pub state_out_addr: WordAddr,
    pub data_addr: WordAddr,
    pub count: u32,
    pub k_addr: WordAddr,
    pub round: u32,
    pub next_state: CycleState,
    pub a: u32,
    pub e: u32,
    pub w: u32,
}

impl Sha2State {
    fn step(
        &mut self,
        ctx: &mut impl Risc0Context,
        cur_state: &mut CycleState,
        next_state: CycleState,
    ) {
        self.next_state = next_state;
        ctx.on_sha2_cycle(*cur_state, self);
        *cur_state = next_state;
    }
}

pub fn ecall(ctx: &mut impl Risc0Context) -> Result<()> {
    let state_in_addr = guest_addr(ctx.load_machine_register(LoadOp::Record, REG_A0)?)?.waddr();
    let state_out_addr = guest_addr(ctx.load_machine_register(LoadOp::Record, REG_A1)?)?.waddr();
    let data_addr = guest_addr(ctx.load_machine_register(LoadOp::Record, REG_A2)?)?.waddr();
    let count = ctx.load_machine_register(LoadOp::Record, REG_A3)? & 0xffff;
    let k_addr = guest_addr(ctx.load_machine_register(LoadOp::Record, REG_A4)?)?.waddr();
    tracing::trace!("sha2: {count} blocks");

    if count > MAX_SHA_COUNT {
        bail!("Invalid count (too big) in sha2 ecall: {count}");
    }

    let mut sha2 = Sha2State {
        state_in_addr,
        state_out_addr,
        data_addr,
        count,
        k_addr,
        round: 0,
        next_state: CycleState::ShaEcall,
        a: 0,
        e: 0,
        w: 0,
    };

    let mut cur_state = CycleState::ShaEcall;
    let mut old_a = RingBuffer::<SHA2_BACK>::new();
    let mut old_e = RingBuffer::<SHA2_BACK>::new();
    let mut old_w = RingBuffer::<BLOCK_WORDS>::new();

    for i in 0..SHA2_LOAD_STATE_CYCLES {
        sha2.round = i;
        sha2.step(ctx, &mut cur_state, CycleState::ShaLoadState);
        let a = ctx.load_u32(LoadOp::Record, sha2.state_in_addr + 3u32 - i)?;
        let e = ctx.load_u32(LoadOp::Record, sha2.state_in_addr + 7u32 - i)?;
        sha2.a = a.to_be();
        sha2.e = e.to_be();
        old_a.push(sha2.a);
        old_e.push(sha2.e);
        ctx.store_u32(sha2.state_out_addr + 3u32 - i, a)?;
        ctx.store_u32(sha2.state_out_addr + 7u32 - i, e)?;
    }

    // HERE!
    while sha2.count != 0 {
        for i in 0..SHA2_LOAD_DATA_CYCLES {
            sha2.round = i;
            sha2.step(ctx, &mut cur_state, CycleState::ShaLoadData);
            let k = ctx.load_u32(LoadOp::Record, sha2.k_addr + i)?;
            sha2.w = ctx.load_u32(LoadOp::Record, sha2.data_addr)?.to_be();
            sha2.data_addr += 1u32;
            old_w.push(sha2.w);
            let (a, e) = compute_ae(&old_a, &old_e, k, sha2.w);
            sha2.a = a;
            sha2.e = e;
            old_a.push(a);
            old_e.push(e);
        }

        for i in 0..SHA2_MIX_CYCLES {
            sha2.round = i;
            sha2.step(ctx, &mut cur_state, CycleState::ShaMix);
            let k = ctx.load_u32(LoadOp::Record, sha2.k_addr + BLOCK_WORDS + i)?;
            sha2.w = compute_w(&old_w);
            old_w.push(sha2.w);
            let (a, e) = compute_ae(&old_a, &old_e, k, sha2.w);
            sha2.a = a;
            sha2.e = e;
            old_a.push(a);
            old_e.push(e);
        }

        for i in 0..SHA2_STORE_CYCLES {
            sha2.round = i;
            sha2.step(ctx, &mut cur_state, CycleState::ShaStoreState);
            sha2.a = old_a.back(4).wrapping_add(old_a.back(SHA2_BACK));
            sha2.e = old_e.back(4).wrapping_add(old_e.back(SHA2_BACK));
            sha2.w = 0;
            if i == 3 {
                sha2.count -= 1;
            }
            old_a.push(sha2.a);
            old_e.push(sha2.e);
            ctx.store_u32(sha2.state_out_addr + 3u32 - i, sha2.a.to_be())?;
            ctx.store_u32(sha2.state_out_addr + 7u32 - i, sha2.e.to_be())?;
        }
    }

    sha2.round = 0;
    sha2.step(ctx, &mut cur_state, CycleState::Decode);

    Ok(())
}

fn compute_ae(
    old_a: &RingBuffer<SHA2_BACK>,
    old_e: &RingBuffer<SHA2_BACK>,
    k: u32,
    w: u32,
) -> (u32, u32) {
    macro_rules! ch {
        ($x:expr, $y:expr, $z:expr) => {
            ($x & $y) ^ (!($x) & $z)
        };
    }

    macro_rules! maj {
        ($x:expr, $y:expr, $z:expr) => {
            ($x & $y) ^ ($x & $z) ^ ($y & $z)
        };
    }

    macro_rules! epsilon0 {
        ($x:expr) => {
            ($x.rotate_right(2) ^ $x.rotate_right(13) ^ $x.rotate_right(22))
        };
    }

    macro_rules! epsilon1 {
        ($x:expr) => {
            $x.rotate_right(6) ^ $x.rotate_right(11) ^ $x.rotate_right(25)
        };
    }

    let a = old_a.back(1);
    let b = old_a.back(2);
    let c = old_a.back(3);
    let d = old_a.back(4);
    let e = old_e.back(1);
    let f = old_e.back(2);
    let g = old_e.back(3);
    let h = old_e.back(4);

    let t1 = h
        .wrapping_add(epsilon1!(e))
        .wrapping_add(ch!(e, f, g))
        .wrapping_add(k)
        .wrapping_add(w);
    let t2 = epsilon0!(a).wrapping_add(maj!(a, b, c));
    let e = d.wrapping_add(t1);
    let a = t1.wrapping_add(t2);
    (a, e)
}

fn compute_w(old_w: &RingBuffer<16>) -> u32 {
    macro_rules! sigma0 {
        ($x:expr) => {
            $x.rotate_right(7) ^ $x.rotate_right(18) ^ ($x >> 3)
        };
    }

    macro_rules! sigma1 {
        ($x:expr) => {
            $x.rotate_right(17) ^ $x.rotate_right(19) ^ ($x >> 10)
        };
    }

    sigma1!(old_w.back(2))
        .wrapping_add(old_w.back(7))
        .wrapping_add(sigma0!(old_w.back(15)))
        .wrapping_add(old_w.back(16))
}

struct RingBuffer<const N: usize> {
    buf: [u32; N],
    cur: usize,
}

impl<const N: usize> RingBuffer<N> {
    fn new() -> Self {
        Self {
            buf: [0; N],
            cur: 0,
        }
    }

    fn push(&mut self, value: u32) {
        self.buf[self.cur] = value;
        self.cur += 1;
        self.cur %= N;
    }

    fn back(&self, i: usize) -> u32 {
        self.buf[(N + self.cur - i) % N]
    }
}
