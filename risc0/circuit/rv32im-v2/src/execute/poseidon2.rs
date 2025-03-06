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
use wide::{u32x4, u32x8, u64x4};

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
    pub inner: [u32x8; CELLS / 8],
    pub zcheck: ExtVal,
}

fn load_u32x8(ctx: &mut dyn Risc0Context, op: LoadOp, addr: WordAddr) -> Result<u32x8> {
    Ok([
        ctx.load_u32(op, addr)?,
        ctx.load_u32(op, addr + 1)?,
        ctx.load_u32(op, addr + 2)?,
        ctx.load_u32(op, addr + 3)?,
        ctx.load_u32(op, addr + 4)?,
        ctx.load_u32(op, addr + 5)?,
        ctx.load_u32(op, addr + 6)?,
        ctx.load_u32(op, addr + 7)?,
    ]
    .into())
}

fn store_u32x8(ctx: &mut dyn Risc0Context, addr: WordAddr, value: &u32x8) -> Result<()> {
    for i in 0..8 {
        ctx.store_u32(addr + i, value.as_array_ref()[i])?;
    }
    Ok(())
}

impl Poseidon2State {
    fn new_ecall(state_addr: u32, buf_in_addr: u32, buf_out_addr: u32, bits_count: u32) -> Self {
        let is_elem = bits_count & PFLAG_IS_ELEM;
        let check_out = bits_count & PFLAG_CHECK_OUT;
        Self {
            state_addr,
            buf_in_addr,
            buf_out_addr,
            has_state: if state_addr == 0 { 0 } else { 1 },
            is_elem: if is_elem == 0 { 0 } else { 1 },
            check_out: if check_out == 0 { 0 } else { 1 },
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

    fn set_inner_word(&mut self, index: usize, word: u32) {
        self.inner[index / 8].as_array_mut()[index % 8] = word;
    }

    pub(crate) fn get_inner_word(&self, index: usize) -> u32 {
        self.inner[index / 8].as_array_ref()[index % 8]
    }

    fn inner_x4(&self) -> &[u32x4; CELLS / 4] {
        // This should be safe since a u32x8 is repr(C) with two `u32x4` fields.
        unsafe { std::mem::transmute(&self.inner) }
    }

    fn inner_x4_mut(&mut self) -> &mut [u32x4; CELLS / 4] {
        // This should be safe since a u32x8 is repr(C) with two `u32x4` fields.
        unsafe { std::mem::transmute(&mut self.inner) }
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
            self.inner[2] = load_u32x8(ctx, LoadOp::Record, state_addr)?;
        }

        // While we have data to process
        let mut buf_in_addr = WordAddr(self.buf_in_addr);
        // tracing::debug!("buf_in_addr: {buf_in_addr:?}");
        // HERE!
        while self.count > 0 {
            // Do load
            self.step(ctx, &mut cur_state, CycleState::PoseidonLoadIn, 0);

            if self.is_elem != 0 {
                self.inner[0] = load_u32x8(ctx, LoadOp::Record, buf_in_addr)?;
                buf_in_addr += 8u32;

                self.buf_in_addr = buf_in_addr.0;
                self.step(ctx, &mut cur_state, CycleState::PoseidonLoadIn, 1);

                self.inner[1] = load_u32x8(ctx, LoadOp::Record, buf_in_addr)?;
                buf_in_addr += 8u32;
                self.buf_in_addr = buf_in_addr.0;
            } else {
                for i in 0..DIGEST_WORDS {
                    let word = ctx.load_u32(LoadOp::Record, buf_in_addr.postfix_inc())?;

                    self.set_inner_word(2 * i, word & 0xffff);
                    self.set_inner_word(2 * i + 1, word >> 16);
                }
                self.buf_in_addr = buf_in_addr.0;
            }

            // Do the mix
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
                let cell = self.get_inner_word(i);
                if word != cell {
                    tracing::warn!(
                        "buf_in_addr: {:?}, buf_out_addr: {buf_out_addr:?}, cell: {i}",
                        WordAddr(self.buf_in_addr)
                    );
                    bail!("poseidon2 check failed: {word:#010x} != {cell:#010x}");
                }
            }
        } else {
            store_u32x8(ctx, buf_out_addr, &self.inner[0])?;
        }

        self.buf_in_addr = 0;

        if self.has_state == 1 {
            self.step(ctx, &mut cur_state, CycleState::PoseidonStoreState, 0);
            store_u32x8(ctx, state_addr, &self.inner[2])?;
        }

        self.step(ctx, &mut cur_state, final_state, 0);

        Ok(())
    }

    // Optimized method for multiplication by M_EXT.
    // See appendix B of Poseidon2 paper for additional details.
    fn multiply_by_m_ext(&mut self) {
        let mut out = [u32x4::from([0u32; 4]); CELLS / 4];
        let mut tmp_sums = u32x4::from([0u32; 4]);

        #[allow(clippy::needless_range_loop)]
        for i in 0..CELLS / 4 {
            let chunk = u32x4::from(multiply_by_4x4_circulant(self.inner_x4()[i].as_array_ref()));

            tmp_sums += chunk;
            u32x4_baby_bear_mod(&mut tmp_sums);

            out[i] += chunk;
            u32x4_baby_bear_mod(&mut out[i]);
        }

        #[allow(clippy::needless_range_loop)]
        for i in 0..CELLS / 4 {
            self.inner_x4_mut()[i] = out[i] + tmp_sums;
        }
        for i in 0..CELLS / 8 {
            u32x8_baby_bear_mod(&mut self.inner[i]);
        }
    }

    // Exploit the fact that off-diagonal entries of M_INT are all 1.
    fn multiply_by_m_int(&mut self) {
        let mut sum = u64x4::from([0u64; 4]);
        for i in 0..CELLS / 4 {
            sum += u64x4_from_u32x4(&self.inner_x4()[i]);
        }
        let sum = sum.as_array_ref().iter().sum::<u64>() % BABY_BEAR_P_U64;

        #[allow(clippy::needless_range_loop)]
        for i in 0..CELLS / 4 {
            let cell = u64x4_from_u32x4(&self.inner_x4()[i]);
            let mut res = u64x4::splat(sum) + M_INT_DIAG_HZN_U64X4[i] * cell;
            u64x4_baby_bear_mod(&mut res);
            self.inner_x4_mut()[i] = u32x4_from_u64x4(&res);
        }
    }

    fn do_ext_round(&mut self, mut idx: usize) {
        if idx >= ROUNDS_HALF_FULL {
            idx += ROUNDS_PARTIAL;
        }

        self.add_round_constants_full(idx);
        for i in 0..CELLS / 4 {
            self.inner_x4_mut()[i] = sbox2x4(&self.inner_x4()[i]);
        }

        self.multiply_by_m_ext();
    }

    fn do_int_rounds(&mut self) {
        for i in 0..ROUNDS_PARTIAL {
            self.add_round_constants_partial(ROUNDS_HALF_FULL + i);
            self.set_inner_word(0, sbox2(self.get_inner_word(0)));
            self.multiply_by_m_int();
        }
    }

    fn add_round_constants_full(&mut self, round: usize) {
        for i in 0..CELLS / 8 {
            self.inner[i] += u32x8::new([
                ROUND_CONSTANTS[round * CELLS + i * 8].as_u32(),
                ROUND_CONSTANTS[round * CELLS + i * 8 + 1].as_u32(),
                ROUND_CONSTANTS[round * CELLS + i * 8 + 2].as_u32(),
                ROUND_CONSTANTS[round * CELLS + i * 8 + 3].as_u32(),
                ROUND_CONSTANTS[round * CELLS + i * 8 + 4].as_u32(),
                ROUND_CONSTANTS[round * CELLS + i * 8 + 5].as_u32(),
                ROUND_CONSTANTS[round * CELLS + i * 8 + 6].as_u32(),
                ROUND_CONSTANTS[round * CELLS + i * 8 + 7].as_u32(),
            ]);

            u32x8_baby_bear_mod(&mut self.inner[i]);
        }
    }

    fn add_round_constants_partial(&mut self, round: usize) {
        let v =
            (self.get_inner_word(0) + ROUND_CONSTANTS[round * CELLS].as_u32()) % BABY_BEAR_P_U32;
        self.set_inner_word(0, v);
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

fn sbox2x4(x: &u32x4) -> u32x4 {
    let x = u64x4_from_u32x4(x);

    let mut x2 = x * x;
    u64x4_baby_bear_mod(&mut x2);

    let mut x4 = x2 * x2;
    u64x4_baby_bear_mod(&mut x4);

    let mut x6 = x4 * x2;
    u64x4_baby_bear_mod(&mut x6);

    let mut x7 = x6 * x;
    u64x4_baby_bear_mod(&mut x7);

    u32x4_from_u64x4(&x7)
}

fn u64x4_from_u32x4(x: &u32x4) -> u64x4 {
    let x_arr = x.as_array_ref();
    u64x4::from([
        x_arr[0] as u64,
        x_arr[1] as u64,
        x_arr[2] as u64,
        x_arr[3] as u64,
    ])
}

fn u32x4_from_u64x4(x: &u64x4) -> u32x4 {
    let x_arr = x.as_array_ref();
    u32x4::from([
        x_arr[0] as u32,
        x_arr[1] as u32,
        x_arr[2] as u32,
        x_arr[3] as u32,
    ])
}

fn u32x4_baby_bear_mod(x: &mut u32x4) {
    for i in 0..4 {
        x.as_array_mut()[i] %= BABY_BEAR_P_U32;
    }
}

fn u64x4_baby_bear_mod(x: &mut u64x4) {
    for i in 0..4 {
        x.as_array_mut()[i] %= BABY_BEAR_P_U64;
    }
}

fn u32x8_baby_bear_mod(x: &mut u32x8) {
    for i in 0..8 {
        x.as_array_mut()[i] %= BABY_BEAR_P_U32;
    }
}

const fn m_int_diag_hzn_u64x4_new(idx: usize) -> u64x4 {
    u64x4::new([
        M_INT_DIAG_HZN[idx * 4].as_u32() as u64,
        M_INT_DIAG_HZN[idx * 4 + 1].as_u32() as u64,
        M_INT_DIAG_HZN[idx * 4 + 2].as_u32() as u64,
        M_INT_DIAG_HZN[idx * 4 + 3].as_u32() as u64,
    ])
}

const M_INT_DIAG_HZN_U64X4: [u64x4; CELLS / 4] = [
    m_int_diag_hzn_u64x4_new(0),
    m_int_diag_hzn_u64x4_new(1),
    m_int_diag_hzn_u64x4_new(2),
    m_int_diag_hzn_u64x4_new(3),
    m_int_diag_hzn_u64x4_new(4),
    m_int_diag_hzn_u64x4_new(5),
];

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

#[cfg(test)]
mod tests {
    use super::*;
    use crate::execute::bigint::BigIntState;
    use crate::execute::rv32im::{DecodedInstruction, Instruction};
    use crate::execute::sha2::Sha2State;
    use risc0_binfmt::ByteAddr;
    use rstest::*;
    use std::collections::BTreeMap;

    #[derive(Default)]
    struct FakeRisc0Context {
        memory: BTreeMap<WordAddr, u32>,
    }

    impl Risc0Context for FakeRisc0Context {
        fn get_pc(&self) -> ByteAddr {
            unimplemented!()
        }

        fn set_pc(&mut self, _addr: ByteAddr) {
            unimplemented!()
        }

        fn set_user_pc(&mut self, _addr: ByteAddr) {
            unimplemented!()
        }

        fn get_machine_mode(&self) -> u32 {
            unimplemented!()
        }

        fn set_machine_mode(&mut self, _mode: u32) {
            unimplemented!()
        }

        fn on_insn_start(
            &mut self,
            _insn: &Instruction,
            _decoded: &DecodedInstruction,
        ) -> Result<()> {
            unimplemented!()
        }

        fn on_insn_end(
            &mut self,
            _insn: &Instruction,
            _decoded: &DecodedInstruction,
        ) -> Result<()> {
            unimplemented!()
        }

        fn load_u32(&mut self, _op: LoadOp, addr: WordAddr) -> Result<u32> {
            Ok(*self.memory.get(&addr).unwrap_or_else(|| {
                panic!("{addr:?} should be pointing to a place we expect a read from")
            }))
        }

        fn store_u32(&mut self, addr: WordAddr, word: u32) -> Result<()> {
            self.memory.insert(addr, word);
            Ok(())
        }

        fn on_ecall_cycle(
            &mut self,
            _cur: CycleState,
            _next: CycleState,
            _s0: u32,
            _s1: u32,
            _s2: u32,
        ) -> Result<()> {
            unimplemented!()
        }

        fn on_terminate(&mut self, _a0: u32, _a1: u32) -> Result<()> {
            unimplemented!()
        }

        fn host_read(&mut self, _fd: u32, _buf: &mut [u8]) -> Result<u32> {
            unimplemented!()
        }

        fn host_write(&mut self, _fd: u32, _buf: &[u8]) -> Result<u32> {
            unimplemented!()
        }

        fn on_sha2_cycle(&mut self, _cur_state: CycleState, _sha2: &Sha2State) {
            unimplemented!()
        }

        fn on_poseidon2_cycle(&mut self, _cur_state: CycleState, _p2: &Poseidon2State) {
            // do nothing
        }

        fn on_bigint_cycle(&mut self, _cur_state: CycleState, _bigint: &BigIntState) {
            unimplemented!()
        }
    }

    fn do_poseidon2_test(
        state: Option<[u32; DIGEST_WORDS]>,
        expected_state: Option<[u32; DIGEST_WORDS]>,
        input: Vec<[u32; DIGEST_WORDS]>,
        is_elem: bool,
        check_out: bool,
        expected_digest: Option<[u32; DIGEST_WORDS]>,
    ) {
        let mut ctx = FakeRisc0Context::default();
        let mut state_addr = 0;
        let buf_in_addr = 0x0000_00f0u32;
        let buf_out_addr = 0x0000_0f00u32;
        let mut bits_count = input.len() as u32;
        if is_elem {
            bits_count /= 2;
            bits_count |= PFLAG_IS_ELEM;
        }
        if check_out {
            bits_count |= PFLAG_CHECK_OUT;

            for (i, word) in expected_digest.as_ref().unwrap().iter().enumerate() {
                ctx.store_u32(WordAddr(buf_out_addr + i as u32), *word)
                    .unwrap();
            }
        }

        if let Some(state) = state {
            state_addr = 0x0000_000fu32;
            for (i, word) in state.iter().enumerate() {
                ctx.store_u32(WordAddr(state_addr + i as u32), *word)
                    .unwrap();
            }
        }

        for (di, digest) in input.iter().enumerate() {
            for (i, word) in digest.iter().enumerate() {
                ctx.store_u32(
                    WordAddr(buf_in_addr + (di * DIGEST_WORDS) as u32 + i as u32),
                    *word,
                )
                .unwrap();
            }
        }

        ctx.store_register(MACHINE_REGS_ADDR.into(), REG_A0, state_addr)
            .unwrap();
        ctx.store_register(MACHINE_REGS_ADDR.into(), REG_A1, buf_in_addr)
            .unwrap();
        ctx.store_register(MACHINE_REGS_ADDR.into(), REG_A2, buf_out_addr)
            .unwrap();
        ctx.store_register(MACHINE_REGS_ADDR.into(), REG_A3, bits_count)
            .unwrap();

        Poseidon2::ecall(&mut ctx).unwrap();

        if !check_out {
            if let Some(expected_digest) = expected_digest {
                let mut result = [0u32; DIGEST_WORDS];
                for (i, entry) in result.iter_mut().enumerate() {
                    *entry = ctx
                        .load_u32(LoadOp::Load, WordAddr(buf_out_addr + i as u32))
                        .unwrap();
                }

                assert_eq!(result, expected_digest);
            }
        }

        if let Some(expected_state) = expected_state {
            let mut result = [0u32; DIGEST_WORDS];
            for (i, entry) in result.iter_mut().enumerate() {
                *entry = ctx
                    .load_u32(LoadOp::Load, WordAddr(state_addr + i as u32))
                    .unwrap();
            }
            assert_eq!(result, expected_state);
        }
    }

    #[rstest]
    #[case(true)]
    #[case(false)]
    fn poseidon2_golden_values_no_state(#[case] check_out: bool) {
        do_poseidon2_test(
            None, // input state
            None, // expected output state
            vec![
                [9, 10, 11, 12, 13, 14, 15, 16],
                [17, 18, 19, 20, 21, 22, 23, 24],
            ], // input
            false, // is_elem
            check_out,
            Some([
                1241390379, 1884310950, 2004172716, 1853849309, 1672721011, 735804474, 153377151,
                952436416,
            ]), // expected output
        );
    }

    #[rstest]
    #[case(true)]
    #[case(false)]
    fn poseidon2_golden_values_with_state(#[case] check_out: bool) {
        do_poseidon2_test(
            Some([1, 2, 3, 4, 5, 6, 7, 8]), // input state
            Some([
                422124962, 343687663, 603825122, 1639060710, 1556827893, 679680067, 606447550,
                1396714734,
            ]), // expected output state
            vec![
                [9, 10, 11, 12, 13, 14, 15, 16],
                [17, 18, 19, 20, 21, 22, 23, 24],
            ], // input
            false,                          // is_elem
            check_out,
            Some([
                6842047, 1969060596, 1995282880, 1672656144, 1703098754, 1618323730, 422751358,
                34172807,
            ]), // expected output
        );
    }

    #[rstest]
    #[case(true)]
    #[case(false)]
    fn poseidon2_golden_values_is_elem(#[case] check_out: bool) {
        do_poseidon2_test(
            Some([1, 2, 3, 4, 5, 6, 7, 8]), // input state
            Some([
                96963433, 323050890, 1098113381, 1153227947, 1063620455, 1699460217, 1373078027,
                1590826877,
            ]), // expected output state
            vec![
                [9, 10, 11, 12, 13, 14, 15, 16],
                [17, 18, 19, 20, 21, 22, 23, 24],
            ], // input
            true,                           // is_elem
            check_out,
            Some([
                3691086, 1319454864, 1208834290, 1281204362, 1699301062, 1294181281, 744596484,
                1693946696,
            ]), // expected output
        );
    }

    fn rand_digest(rng: &mut rand::rngs::ThreadRng) -> [u32; DIGEST_WORDS] {
        use rand::RngCore as _;

        let mut digest = [0u32; DIGEST_WORDS];
        for e in digest.iter_mut() {
            *e = rng.next_u32();
        }
        digest
    }

    #[test]
    fn poseidon2_benchmark() {
        let mut rng = rand::thread_rng();

        for _ in 0..100_000 {
            let mut input = vec![];
            for _ in 0..5 {
                input.push(rand_digest(&mut rng));
            }

            do_poseidon2_test(
                Some(rand_digest(&mut rng)), // input state
                None,                        // expected output state
                input,
                false, // is_elem
                false, // check_out
                None,  // expected output
            );
        }
    }
}
