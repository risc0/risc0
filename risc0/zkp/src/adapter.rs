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

//! Interface between the circuit and prover/verifier

use alloc::{str::from_utf8, vec::Vec};
use core::fmt;

use anyhow::Result;
use risc0_core::field::{Elem, ExtElem, Field};
use serde::{Deserialize, Serialize};

use crate::{hal::cpu::SyncSlice, taps::TapSet};

// TODO: Remove references to these constants so we don't depend on a
// fixed set of register groups.
pub const REGISTER_GROUP_ACCUM: usize = 0;
pub const REGISTER_GROUP_CODE: usize = 1;
pub const REGISTER_GROUP_DATA: usize = 2;

#[derive(Clone, Copy)]
pub struct MixState<EE: ExtElem> {
    pub tot: EE,
    pub mul: EE,
}

pub trait CircuitStepHandler<E: Elem> {
    fn call(
        &mut self,
        cycle: usize,
        name: &str,
        extra: &str,
        args: &[E],
        outs: &mut [E],
    ) -> Result<()>;

    fn sort(&mut self, name: &str);
}

pub struct CircuitStepContext {
    pub size: usize,
    pub cycle: usize,
}

pub trait CircuitStep<E: Elem> {
    fn step_exec<S: CircuitStepHandler<E>>(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &[SyncSlice<E>],
    ) -> Result<E>;

    fn step_verify_bytes<S: CircuitStepHandler<E>>(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &[SyncSlice<E>],
    ) -> Result<E>;

    fn step_verify_mem<S: CircuitStepHandler<E>>(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &[SyncSlice<E>],
    ) -> Result<E>;

    fn step_compute_accum<S: CircuitStepHandler<E>>(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &[SyncSlice<E>],
    ) -> Result<E>;

    fn step_verify_accum<S: CircuitStepHandler<E>>(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &[SyncSlice<E>],
    ) -> Result<E>;
}

pub trait PolyFp<F: Field> {
    fn poly_fp(
        &self,
        cycle: usize,
        steps: usize,
        mix: &[F::ExtElem],
        args: &[&[F::Elem]],
    ) -> F::ExtElem;
}

pub trait PolyExt<F: Field> {
    fn poly_ext(
        &self,
        mix: &F::ExtElem,
        u: &[F::ExtElem],
        args: &[&[F::Elem]],
    ) -> MixState<F::ExtElem>;
}

pub trait TapsProvider {
    fn get_taps(&self) -> &'static TapSet<'static>;

    fn accum_size(&self) -> usize {
        self.get_taps().group_size(REGISTER_GROUP_ACCUM)
    }

    fn code_size(&self) -> usize {
        self.get_taps().group_size(REGISTER_GROUP_CODE)
    }

    fn ctrl_size(&self) -> usize {
        self.get_taps().group_size(REGISTER_GROUP_CODE)
    }

    fn data_size(&self) -> usize {
        self.get_taps().group_size(REGISTER_GROUP_DATA)
    }
}

/// A protocol info string for the proof system and circuits.
/// Used to seed the Fiat-Shamir transcript and provide domain separation between different
/// protocol and circuit versions.
#[derive(Copy, Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub struct ProtocolInfo(pub [u8; 16]);

impl ProtocolInfo {
    /// Encode a fixed context byte-string to elements, with one element per byte.
    // NOTE: This function is intended to be compatible with const, but is not const currently because
    // E::from_u64 is not const, as const functions on traits is not stable.
    pub fn encode<E: Elem>(&self) -> [E; 16] {
        let mut elems = [E::ZERO; 16];
        for (i, elem) in elems.iter_mut().enumerate().take(self.0.len()) {
            *elem = E::from_u64(self.0[i] as u64);
        }
        elems
    }
}

impl fmt::Display for ProtocolInfo {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match from_utf8(&self.0) {
            Ok(s) => write!(f, "{}", s),
            Err(_) => write!(f, "0x{}", hex::encode(self.0)),
        }
    }
}

/// Versioned info string for the proof system.
///
/// NOTE: This string should be bumped with every change to the proof system, as defined by a
/// change to checks applied by the verifier.
pub const PROOF_SYSTEM_INFO: ProtocolInfo = ProtocolInfo(*b"RISC0_STARK:v1__");

pub trait CircuitInfo {
    const CIRCUIT_INFO: ProtocolInfo;
    const OUTPUT_SIZE: usize;
    const MIX_SIZE: usize;
}

/// traits implemented by generated rust code used in both prover and verifier
pub trait CircuitCoreDef<F: Field>: CircuitInfo + PolyExt<F> + TapsProvider {}

/// traits implemented by generated rust code used in only the prover
pub trait CircuitProveDef<F: Field>:
    CircuitStep<F::Elem> + PolyFp<F> + CircuitCoreDef<F> + Sync
{
}

pub type Arg = usize;
pub type Var = usize;

pub struct PolyExtStepDef {
    pub block: &'static [PolyExtStep],
    pub ret: Var,
}

pub enum PolyExtStep {
    Const(u32),
    Get(usize),
    GetGlobal(Arg, usize),
    Add(Var, Var),
    Sub(Var, Var),
    Mul(Var, Var),
    True,
    AndEqz(Var, Var),
    AndCond(Var, Var, Var),
}

impl PolyExtStep {
    pub fn step<F: Field>(
        &self,
        fp_vars: &mut Vec<F::ExtElem>,
        mix_vars: &mut Vec<MixState<F::ExtElem>>,
        mix: &F::ExtElem,
        u: &[F::ExtElem],
        args: &[&[F::Elem]],
    ) {
        match self {
            PolyExtStep::Const(value) => {
                let elem = F::Elem::from_u64(*value as u64);
                fp_vars.push(F::ExtElem::from_subfield(&elem));
            }
            PolyExtStep::Get(tap) => {
                fp_vars.push(u[*tap]);
            }
            PolyExtStep::GetGlobal(base, offset) => {
                fp_vars.push(F::ExtElem::from_subfield(&args[*base][*offset]));
            }
            PolyExtStep::Add(x1, x2) => {
                fp_vars.push(fp_vars[*x1] + fp_vars[*x2]);
            }
            PolyExtStep::Sub(x1, x2) => {
                fp_vars.push(fp_vars[*x1] - fp_vars[*x2]);
            }
            PolyExtStep::Mul(x1, x2) => {
                fp_vars.push(fp_vars[*x1] * fp_vars[*x2]);
            }
            PolyExtStep::True => {
                mix_vars.push(MixState {
                    tot: F::ExtElem::ZERO,
                    mul: F::ExtElem::ONE,
                });
            }
            PolyExtStep::AndEqz(x, val) => {
                let x = mix_vars[*x];
                let val = fp_vars[*val];
                mix_vars.push(MixState {
                    tot: x.tot + x.mul * val,
                    mul: x.mul * *mix,
                });
            }
            PolyExtStep::AndCond(x, cond, inner) => {
                let x = mix_vars[*x];
                let cond = fp_vars[*cond];
                let inner = mix_vars[*inner];
                mix_vars.push(MixState {
                    tot: x.tot + cond * inner.tot * x.mul,
                    mul: x.mul * inner.mul,
                });
            }
        }
    }
}

impl PolyExtStepDef {
    pub fn step<F: Field>(
        &self,
        mix: &F::ExtElem,
        u: &[F::ExtElem],
        args: &[&[F::Elem]],
    ) -> MixState<F::ExtElem> {
        let mut fp_vars = Vec::with_capacity(self.block.len() - (self.ret + 1));
        let mut mix_vars = Vec::with_capacity(self.ret + 1);
        for op in self.block.iter() {
            op.step::<F>(&mut fp_vars, &mut mix_vars, mix, u, args);
        }
        assert_eq!(
            fp_vars.len(),
            self.block.len() - (self.ret + 1),
            "Miscalculated capacity for fp_vars"
        );
        assert_eq!(
            mix_vars.len(),
            self.ret + 1,
            "Miscalculated capacity for mix_vars"
        );
        mix_vars[self.ret]
    }
}
