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

use risc0_circuit_keccak_sys::ScatterInfo;
use risc0_core::scope;
use risc0_zkp::core::digest::DIGEST_WORDS;
use std::collections::BTreeMap;
use std::marker::PhantomData;

use super::KeccakState;
use crate::zirgen::circuit::LAYOUT_TOP;

type ThetaB = [u64; 5];

pub(crate) struct PreflightCycle {
    pub cycle: u32,
    pub preimage_idx: u32,
}

pub(crate) trait PreflightCycleOrder {
    type Key: Ord;

    fn key_for_cycle(state: &ControlState) -> Self::Key;
}

// Default is to run straight through in cycle order.
#[derive(Default, Clone, Copy)]
pub(crate) struct ForwardPreflightOrder;

impl PreflightCycleOrder for ForwardPreflightOrder {
    type Key = ();
    fn key_for_cycle(_: &ControlState) -> Self::Key {}
}

pub(crate) struct PreflightTrace<Order: PreflightCycleOrder = ForwardPreflightOrder> {
    order: PhantomData<Order>,
    pub cycle: usize,
    pub preimages: Vec<KeccakState>,
    pub data: Vec<u32>,
    pub scatter: Vec<ScatterInfo>,
    pub cycles: BTreeMap<Order::Key, Vec<PreflightCycle>>,
}

pub(crate) struct ControlState {
    pub cycle_type: u8,
    pub sub_type: u8,
    pub block: u8,
    pub round: u8,
}

impl ControlState {
    fn new(cycle_type: u8, sub_type: u8, block: u8, round: u8) -> Self {
        Self {
            cycle_type,
            sub_type,
            block,
            round,
        }
    }

    fn as_u32(&self) -> u32 {
        u32::from_le_bytes([self.cycle_type, self.sub_type, self.block, self.round])
    }
}

enum Control {
    Shutdown,
    Read,
    Expand(u8),
    Write,
    Keccak0(u8),
    Keccak1(u8),
    Keccak2(u8),
    Keccak3(u8),
    Keccak4(u8),
    ShaIn(u8, u8),
    ShaOut(u8, u8),
    ShaNextBlockIn(u8),
    ShaNextBlockOut(u8),
    Init,
}

impl Control {
    fn as_state(&self) -> ControlState {
        match self {
            Control::Shutdown => ControlState::new(0, 0, 0, 0),
            Control::Read => ControlState::new(1, 0, 0, 0),
            Control::Expand(subtype) => ControlState::new(2, *subtype, 0, 0),
            Control::Write => ControlState::new(3, 0, 0, 0),
            Control::Keccak0(round) => ControlState::new(4, 0, 0, *round),
            Control::Keccak1(round) => ControlState::new(5, 0, 0, *round),
            Control::Keccak2(round) => ControlState::new(6, 0, 0, *round),
            Control::Keccak3(round) => ControlState::new(7, 0, 0, *round),
            Control::Keccak4(round) => ControlState::new(8, 0, 0, *round),
            Control::ShaIn(block, round) => ControlState::new(9, 0, *block, *round),
            Control::ShaOut(block, round) => ControlState::new(9, 1, *block, *round),
            Control::ShaNextBlockIn(block) => ControlState::new(10, 0, *block, 0),
            Control::ShaNextBlockOut(block) => ControlState::new(10, 1, *block, 0),
            Control::Init => ControlState::new(11, 0, 0, 0),
        }
    }
}

type ShaState = [u32; DIGEST_WORDS];

const SHA_INIT: ShaState = [
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
];

const SHA_K: [u32; 64] = [
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
];

const KECCAK_IOTA: [u64; 24] = [
    0x0000000000000001,
    0x0000000000008082,
    0x800000000000808a,
    0x8000000080008000,
    0x000000000000808b,
    0x0000000080000001,
    0x8000000080008081,
    0x8000000000008009,
    0x000000000000008a,
    0x0000000000000088,
    0x0000000080008009,
    0x000000008000000a,
    0x000000008000808b,
    0x800000000000008b,
    0x8000000000008089,
    0x8000000000008003,
    0x8000000000008002,
    0x8000000000000080,
    0x000000000000800a,
    0x800000008000000a,
    0x8000000080008081,
    0x8000000000008080,
    0x0000000080000001,
    0x8000000080008008,
];
const KECCAK_RHO: [u32; 24] = [
    1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 2, 14, 27, 41, 56, 8, 25, 43, 62, 18, 39, 61, 20, 44,
];

const KECCAK_PI: [usize; 24] = [
    10, 7, 11, 17, 18, 3, 5, 16, 8, 21, 24, 4, 15, 23, 19, 13, 12, 2, 20, 14, 22, 9, 6, 1,
];

#[derive(Clone, Debug, Default)]
struct ShaInfo {
    a: [u32; DIGEST_WORDS],
    e: [u32; DIGEST_WORDS],
    w: [u32; DIGEST_WORDS],
}

fn compute_sha_infos(state: &mut ShaState, data: &[u32]) -> Vec<ShaInfo> {
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

    let &mut [mut a, mut b, mut c, mut d, mut e, mut f, mut g, mut h] = state;
    let mut w = [0u32; 64];
    let mut ret = vec![];
    let mut cur = ShaInfo::default();
    for i in 0..64 {
        if i < 16 {
            w[i] = data[i].to_be();
        } else {
            w[i] = sigma1!(w[i - 2])
                .wrapping_add(w[i - 7])
                .wrapping_add(sigma0!(w[i - 15]))
                .wrapping_add(w[i - 16]);
        }

        let t1 = h
            .wrapping_add(epsilon1!(e))
            .wrapping_add(ch!(e, f, g))
            .wrapping_add(SHA_K[i])
            .wrapping_add(w[i]);
        let t2 = epsilon0!(a).wrapping_add(maj!(a, b, c));
        h = g;
        g = f;
        f = e;
        e = d.wrapping_add(t1);
        d = c;
        c = b;
        b = a;
        a = t1.wrapping_add(t2);

        cur.a[i % 8] = a;
        cur.e[i % 8] = e;
        cur.w[i % 8] = w[i];
        if i % 8 == 7 {
            ret.push(cur.clone());
        }
    }

    state[0] = state[0].wrapping_add(a);
    state[1] = state[1].wrapping_add(b);
    state[2] = state[2].wrapping_add(c);
    state[3] = state[3].wrapping_add(d);
    state[4] = state[4].wrapping_add(e);
    state[5] = state[5].wrapping_add(f);
    state[6] = state[6].wrapping_add(g);
    state[7] = state[7].wrapping_add(h);
    ret.push((*state).into());

    ret
}

impl From<ShaState> for ShaInfo {
    fn from(state: ShaState) -> Self {
        let mut ret = ShaInfo::default();
        for i in 0..4 {
            ret.a[7 - i] = state[i];
            ret.e[7 - i] = state[4 + i];
        }
        ret
    }
}

fn theta_p1(s: &KeccakState) -> ThetaB {
    let mut b = ThetaB::default();
    for i in 0..5 {
        b[i] = s[i] ^ s[i + 5] ^ s[i + 10] ^ s[i + 15] ^ s[i + 20];
    }
    b
}

fn theta_p2_rho_pi(s: &mut KeccakState, bc: &ThetaB) {
    for i in 0..5 {
        let t = bc[(i + 4) % 5] ^ bc[(i + 1) % 5].rotate_left(1);
        for j in (0..25).step_by(5) {
            s[j + i] ^= t;
        }
    }
    let mut t1 = s[1];
    for (&pi, rho) in KECCAK_PI.iter().zip(KECCAK_RHO) {
        let t2 = s[pi];
        s[pi] = t1.rotate_left(rho);
        t1 = t2;
    }
}

fn chi_iota(s: &mut KeccakState, round: usize) {
    let mut t = [0u64; 5];
    for j in (0..25).step_by(5) {
        t.copy_from_slice(&s[j..(5 + j)]);
        for i in 0..5 {
            s[j + i] ^= (!t[(i + 1) % 5]) & t[(i + 2) % 5];
        }
    }
    s[0] ^= KECCAK_IOTA[round];
}

impl<Order: PreflightCycleOrder> PreflightTrace<Order> {
    pub(crate) fn new(inputs: &[KeccakState], cycles: usize) -> Self {
        scope!("preflight");

        let mut cur_idx = 0;
        let mut ret = Self {
            order: PhantomData,
            preimages: inputs.to_vec(),
            data: vec![],
            scatter: vec![],
            cycles: BTreeMap::new(),
            cycle: 0,
        };

        // 100 zeros @ offset zero (for wherever we need zero)
        for _ in 0..100 {
            ret.data.push(0);
        }

        // Initialize sha state (and current data offset)
        let mut cur_sha = SHA_INIT;
        let mut sflat = ret.write_sha_state(&cur_sha);

        // Do an initial 'init' cycle
        ret.add_cycle(Control::Init, 0, 0, sflat, cur_idx);

        for kstate in inputs.iter() {
            let mut kstate = *kstate;
            let mut data = vec![];

            // Do 'read' cycle
            let kflat = ret.write_kflat(&mut data, &kstate);
            let bits = ret.write_sha_info(&cur_sha.into());
            ret.add_cycle(Control::Read, bits, kflat, sflat, cur_idx);
            cur_idx += 1;

            // Sha and write all for blocks
            ret.write_sha(&mut cur_sha, &data, kflat, &mut sflat, cur_idx, true);

            // Expand
            let bits = ret.write_keccak(&kstate, false);
            ret.add_cycle(Control::Expand(0), bits, kflat, sflat, cur_idx);
            let bits = ret.write_keccak(&kstate, true);
            ret.add_cycle(Control::Expand(1), bits, kflat, sflat, cur_idx);

            // Now do the Keccack cycles
            for round in 0..24 {
                let theta = theta_p1(&kstate);
                let bits = ret.write_theta(&theta);
                ret.add_cycle(Control::Keccak0(round as u8), bits, kflat, sflat, cur_idx);
                theta_p2_rho_pi(&mut kstate, &theta);
                let bits = ret.write_keccak(&kstate, false);
                ret.add_cycle(Control::Keccak1(round as u8), bits, kflat, sflat, cur_idx);
                let bits = ret.write_keccak(&kstate, true);
                ret.add_cycle(Control::Keccak2(round as u8), bits, kflat, sflat, cur_idx);
                chi_iota(&mut kstate, round);
                let bits = ret.write_keccak(&kstate, false);
                ret.add_cycle(Control::Keccak3(round as u8), bits, kflat, sflat, cur_idx);
                let bits = ret.write_keccak(&kstate, true);
                ret.add_cycle(Control::Keccak4(round as u8), bits, kflat, sflat, cur_idx);
            }

            // Do 'write' cycle
            let kflat = ret.write_kflat(&mut data, &kstate);
            let bits = ret.write_sha_info(&cur_sha.into());
            ret.add_cycle(Control::Write, bits, kflat, sflat, cur_idx);

            // Sha and write all for blocks
            ret.write_sha(&mut cur_sha, &data, kflat, &mut sflat, cur_idx, false);
        }

        while ret.cycle < cycles {
            ret.add_cycle(Control::Shutdown, 0, 0, sflat, cur_idx);
        }

        ret
    }

    fn add_cycle(&mut self, ctrl: Control, bits: u32, kflat: u32, sflat: u32, preimage_idx: u32) {
        let offset = self.data.len() as u32;
        let cycle = self.cycle as u32;
        let ctrl_state = ctrl.as_state();
        self.data.push(ctrl_state.as_u32());
        self.scatter.push(ScatterInfo {
            offset,
            row: cycle,
            col: LAYOUT_TOP.control_state.cycle_type._super.offset as u16,
            count: 4,
            bits: 8,
        });
        let onehot = 1 << ctrl_state.cycle_type;
        self.data.push(onehot);
        self.scatter.push(ScatterInfo {
            offset: offset + 1,
            row: cycle,
            col: LAYOUT_TOP.cycle_mux._super[0]._super.offset as u16,
            count: 12,
            bits: 1,
        });
        self.add_bits(
            cycle,
            LAYOUT_TOP.cur_state.bits[0]._super.offset as u16,
            bits,
            800,
        );
        self.add_shorts(
            cycle,
            LAYOUT_TOP.cur_state.kflat[0]._super.offset as u16,
            kflat,
            100,
        );
        self.add_shorts(
            cycle,
            LAYOUT_TOP.cur_state.sflat[0]._super.offset as u16,
            sflat,
            16,
        );
        self.cycles
            .entry(Order::key_for_cycle(&ctrl_state))
            .or_default()
            .push(PreflightCycle {
                cycle,
                preimage_idx,
            });
        self.cycle += 1
    }

    fn write_sha_state(&mut self, state: &ShaState) -> u32 {
        let offset = self.data.len() as u32;
        self.data.extend_from_slice(state);
        offset
    }

    fn write_sha_info(&mut self, info: &ShaInfo) -> u32 {
        let offset = self.data.len() as u32;
        self.data.extend_from_slice(&info.a);
        self.data.extend_from_slice(&info.e);
        self.data.extend_from_slice(&info.w);
        self.data.push(0);
        offset
    }

    fn write_sha(
        &mut self,
        cur_sha: &mut ShaState,
        data: &[u32],
        kflat: u32,
        sflat: &mut u32,
        cur_idx: u32,
        is_in: bool,
    ) {
        for block in 0..4 {
            let infos = compute_sha_infos(cur_sha, &data[16 * block..]);
            for (i, info) in infos.iter().enumerate().take(DIGEST_WORDS) {
                let bits = self.write_sha_info(info);
                let ctrl = if is_in {
                    Control::ShaIn(block as u8, i as u8)
                } else {
                    Control::ShaOut(block as u8, i as u8)
                };
                self.add_cycle(ctrl, bits, kflat, *sflat, cur_idx);
            }
            *sflat = self.write_sha_state(cur_sha);
            let bits = self.write_sha_info(&infos[DIGEST_WORDS]);
            let ctrl = if is_in {
                Control::ShaNextBlockIn(block as u8)
            } else {
                Control::ShaNextBlockOut(block as u8)
            };
            self.add_cycle(ctrl, bits, kflat, *sflat, cur_idx);
        }
    }

    fn write_kflat(&mut self, data: &mut Vec<u32>, kstate: &KeccakState) -> u32 {
        data.clear();
        for &x in kstate {
            data.push(x as u32);
            data.push((x >> 32) as u32);
        }
        let offset = self.data.len() as u32;
        self.data.extend_from_slice(data);
        for _ in 0..(64 - 50) {
            data.push(0);
        }
        offset
    }

    fn write_keccak(&mut self, state: &KeccakState, high: bool) -> u32 {
        let offset = self.data.len() as u32;
        for &x in state {
            if high {
                self.data.push((x >> 32) as u32);
            } else {
                self.data.push(x as u32);
            }
        }
        offset
    }

    fn write_theta(&mut self, theta: &ThetaB) -> u32 {
        let offset = self.data.len() as u32;
        for &x in theta {
            self.data.push(x as u32);
            self.data.push((x >> 32) as u32);
        }
        for _ in 0..20 {
            self.data.push(0);
        }
        offset
    }

    fn add_bits(&mut self, row: u32, col: u16, offset: u32, count: u16) {
        assert!(count % 32 == 0);
        self.scatter.push(ScatterInfo {
            offset,
            row,
            col,
            count,
            bits: 1,
        });
    }

    fn add_shorts(&mut self, row: u32, col: u16, offset: u32, count: u16) {
        assert!(count % 2 == 0);
        self.scatter.push(ScatterInfo {
            offset,
            row,
            col,
            count,
            bits: 16,
        });
    }
}
