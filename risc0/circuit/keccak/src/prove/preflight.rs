// Copyright 2026 RISC Zero, Inc.
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

use anyhow::{Result, ensure};

use risc0_circuit_keccak_sys::ScatterInfo;
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_core::scope;
use risc0_zkp::core::hash::poseidon2::{CELLS, poseidon2_mix};
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
    pub round: u8,
}

impl ControlState {
    fn new(cycle_type: u8, sub_type: u8, round: u8) -> Self {
        Self {
            cycle_type,
            sub_type,
            round,
        }
    }

    fn as_u32(&self) -> u32 {
        u32::from_le_bytes([self.cycle_type, self.sub_type, self.round, 0])
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
    PoseidonIn(u8),
    PoseidonOut(u8),
    Init,
}

impl Control {
    fn as_state(&self) -> ControlState {
        match self {
            Control::Shutdown => ControlState::new(0, 0, 0),
            Control::Read => ControlState::new(1, 0, 0),
            Control::Expand(subtype) => ControlState::new(2, *subtype, 0),
            Control::Write => ControlState::new(3, 0, 0),
            Control::Keccak0(round) => ControlState::new(4, 0, *round),
            Control::Keccak1(round) => ControlState::new(5, 0, *round),
            Control::Keccak2(round) => ControlState::new(6, 0, *round),
            Control::Keccak3(round) => ControlState::new(7, 0, *round),
            Control::Keccak4(round) => ControlState::new(8, 0, *round),
            Control::PoseidonIn(round) => ControlState::new(9, 0, *round),
            Control::PoseidonOut(round) => ControlState::new(9, 1, *round),
            Control::Init => ControlState::new(10, 0, 0),
        }
    }
}

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
    pub(crate) fn new(inputs: &[KeccakState], cycles: usize) -> Result<Self> {
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
        let mut cells = [BabyBearElem::new(0); CELLS];
        let mut pflat = ret.write_pflat(&cells);

        // Do an initial 'init' cycle
        ret.add_cycle(Control::Init, 0, 0, pflat, cur_idx);

        for kstate in inputs.iter() {
            let mut kstate = *kstate;
            let mut data = vec![];

            // Do 'read' cycle
            let kflat = ret.write_kflat(&mut data, &kstate);
            ret.add_cycle(Control::Read, 0, kflat, pflat, cur_idx);
            cur_idx += 1;

            // Do Poseidon2 hashing
            ret.write_poseidon(&mut cells, &data, kflat, &mut pflat, cur_idx, true);

            // Expand
            let bits = ret.write_keccak(&kstate, false);
            ret.add_cycle(Control::Expand(0), bits, kflat, pflat, cur_idx);
            let bits = ret.write_keccak(&kstate, true);
            ret.add_cycle(Control::Expand(1), bits, kflat, pflat, cur_idx);

            // Now do the Keccack cycles
            for round in 0..24 {
                let theta = theta_p1(&kstate);
                let bits = ret.write_theta(&theta);
                ret.add_cycle(Control::Keccak0(round as u8), bits, kflat, pflat, cur_idx);
                theta_p2_rho_pi(&mut kstate, &theta);
                let bits = ret.write_keccak(&kstate, false);
                ret.add_cycle(Control::Keccak1(round as u8), bits, kflat, pflat, cur_idx);
                let bits = ret.write_keccak(&kstate, true);
                ret.add_cycle(Control::Keccak2(round as u8), bits, kflat, pflat, cur_idx);
                chi_iota(&mut kstate, round);
                let bits = ret.write_keccak(&kstate, false);
                ret.add_cycle(Control::Keccak3(round as u8), bits, kflat, pflat, cur_idx);
                let bits = ret.write_keccak(&kstate, true);
                ret.add_cycle(Control::Keccak4(round as u8), bits, kflat, pflat, cur_idx);
            }

            // Do 'write' cycle
            let kflat = ret.write_kflat(&mut data, &kstate);
            ret.add_cycle(Control::Write, 0, kflat, pflat, cur_idx);

            // Sha and write all for blocks
            ret.write_poseidon(&mut cells, &data, kflat, &mut pflat, cur_idx, false);

            ensure!(
                ret.cycle <= cycles,
                "Too many inputs for given po2={}",
                cycles.ilog2()
            );
        }

        while ret.cycle < cycles {
            ret.add_cycle(Control::Shutdown, 0, 0, pflat, cur_idx);
        }

        Ok(ret)
    }

    fn add_cycle(&mut self, ctrl: Control, bits: u32, kflat: u32, pflat: u32, preimage_idx: u32) {
        let offset = self.data.len() as u32;
        let cycle = self.cycle as u32;
        let ctrl_state = ctrl.as_state();
        self.data.push(ctrl_state.as_u32());
        self.scatter.push(ScatterInfo {
            offset,
            row: cycle,
            col: LAYOUT_TOP.control_state.cycle_type._super.offset as u16,
            count: 3,
            bits: 8,
        });
        let onehot = 1 << ctrl_state.cycle_type;
        self.data.push(onehot);
        self.scatter.push(ScatterInfo {
            offset: offset + 1,
            row: cycle,
            col: LAYOUT_TOP.cycle_mux._super[0]._super.offset as u16,
            count: 11,
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
        self.add_words(
            cycle,
            LAYOUT_TOP.cur_state.pflat[0]._super.offset as u16,
            pflat,
            24,
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

    fn write_pflat(&mut self, state: &[BabyBearElem; CELLS]) -> u32 {
        let offset = self.data.len() as u32;
        for s in state {
            self.data.push(s.as_u32());
        }
        offset
    }

    fn write_poseidon(
        &mut self,
        cells: &mut [BabyBearElem; CELLS],
        data: &[u32],
        kflat: u32,
        pflat: &mut u32,
        cur_idx: u32,
        is_in: bool,
    ) {
        for round in 0..7 {
            for i in 0..8 {
                let word = data[round * 8 + i];
                cells[2 * i] = BabyBearElem::new(word & 0xffff);
                cells[2 * i + 1] = BabyBearElem::new(word >> 16);
            }
            poseidon2_mix(cells);
            *pflat = self.write_pflat(cells);
            let ctrl = if is_in {
                Control::PoseidonIn(round as u8)
            } else {
                Control::PoseidonOut(round as u8)
            };
            self.add_cycle(ctrl, 0, kflat, *pflat, cur_idx);
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
        for _ in 0..(56 - 50) {
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
        assert!(count.is_multiple_of(32));
        self.scatter.push(ScatterInfo {
            offset,
            row,
            col,
            count,
            bits: 1,
        });
    }

    fn add_shorts(&mut self, row: u32, col: u16, offset: u32, count: u16) {
        assert!(count.is_multiple_of(2));
        self.scatter.push(ScatterInfo {
            offset,
            row,
            col,
            count,
            bits: 16,
        });
    }

    fn add_words(&mut self, row: u32, col: u16, offset: u32, count: u16) {
        self.scatter.push(ScatterInfo {
            offset,
            row,
            col,
            count,
            bits: 32,
        });
    }
}
