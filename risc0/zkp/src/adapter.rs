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

// If true, enable tracing of adapter internals.
const ADAPTER_TRACE_ENABLED: bool = false;

macro_rules! trace_if_enabled {
    ($($args:tt)*) => {
        if ADAPTER_TRACE_ENABLED {
            tracing::trace!($($args)*)
        }
    }
}

#[derive(Clone, Copy, Debug)]
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

#[derive(Debug)]
pub enum PolyExtStep {
    Const(u32),
    ConstExt(u32, u32, u32, u32),
    Get(usize),
    GetGlobal(Arg, usize),
    Add(Var, Var),
    Sub(Var, Var),
    Mul(Var, Var),
    True,
    AndEqz(Var, Var),
    AndCond(Var, Var, Var),
    Shift,
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
                trace_if_enabled!("[{}] {self:?} -> {elem:?}", fp_vars.len());
                fp_vars.push(F::ExtElem::from_subfield(&elem));
            }
            PolyExtStep::ConstExt(x0, x1, x2, x3) => {
                let elem = F::ExtElem::from_u32_words(&[*x0, *x1, *x2, *x3]);
                trace_if_enabled!("[{}] {self:?} -> {elem:?}", fp_vars.len());
                fp_vars.push(elem);
            }
            PolyExtStep::Get(tap) => {
                let val = u[*tap];
                trace_if_enabled!("[{}] {self:?} -> {val:?}", fp_vars.len());
                fp_vars.push(val);
            }
            PolyExtStep::GetGlobal(base, offset) => {
                let val = F::ExtElem::from_subfield(&args[*base][*offset]);
                trace_if_enabled!("[{}] {self:?} -> {val:?}", fp_vars.len());
                fp_vars.push(val);
            }
            PolyExtStep::Add(x1, x2) => {
                let val = fp_vars[*x1] + fp_vars[*x2];
                trace_if_enabled!("[{}] {self:?} -> {val:?}", fp_vars.len());
                fp_vars.push(val);
            }
            PolyExtStep::Sub(x1, x2) => {
                let val = fp_vars[*x1] - fp_vars[*x2];
                trace_if_enabled!("[{}] {self:?} -> {val:?}", fp_vars.len());
                fp_vars.push(val);
            }
            PolyExtStep::Mul(x1, x2) => {
                let val = fp_vars[*x1] * fp_vars[*x2];
                trace_if_enabled!("[{}] {self:?} -> {val:?}", fp_vars.len());
                fp_vars.push(val);
            }
            PolyExtStep::Shift => {
                // Return [0, 1, ...] to allow construction of
                // values in the extension field
                let val = F::ExtElem::from_subelems(
                    [F::Elem::ZERO, F::Elem::ONE]
                        .into_iter()
                        .chain(core::iter::repeat(F::Elem::ZERO))
                        .take(F::ExtElem::EXT_SIZE),
                );
                trace_if_enabled!("[{}] {self:?} -> {val:?}", mix_vars.len());
                fp_vars.push(val);
            }
            PolyExtStep::True => {
                let mix_val = MixState {
                    tot: F::ExtElem::ZERO,
                    mul: F::ExtElem::ONE,
                };
                trace_if_enabled!("[{}] {self:?} -> {mix_val:?}", mix_vars.len());
                mix_vars.push(mix_val);
            }
            PolyExtStep::AndEqz(x, val) => {
                let x = mix_vars[*x];
                let val = fp_vars[*val];
                let mix_val = MixState {
                    tot: x.tot + x.mul * val,
                    mul: x.mul * *mix,
                };
                trace_if_enabled!("[{}] {self:?} -> {mix_val:?}", mix_vars.len());
                mix_vars.push(mix_val);
            }
            PolyExtStep::AndCond(x, cond, inner) => {
                let x = mix_vars[*x];
                let cond = fp_vars[*cond];
                let inner = mix_vars[*inner];
                let mix_val = MixState {
                    tot: x.tot + cond * inner.tot * x.mul,
                    mul: x.mul * inner.mul,
                };
                trace_if_enabled!("[{}] {self:?} -> {mix_val:?}", mix_vars.len());
                mix_vars.push(mix_val);
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
