// Copyright 2023 RISC Zero, Inc.
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
//! this is the recusion module TODO
use risc0_zkp::{
    adapter::{CircuitCoreDef, TapsProvider},
    field::baby_bear::BabyBear,
    taps::TapSet,
};
mod control_id;
mod info;
mod poly_ext;
mod taps;

/// todo
pub mod receipt;

/// this is a fake struct to make the code work with generated info
pub struct CircuitImpl;

impl CircuitImpl {
    /// todo
    pub const fn new() -> Self {
        CircuitImpl
    }
}

impl TapsProvider for CircuitImpl {
    fn get_taps(&self) -> &'static TapSet<'static> {
        taps::TAPSET
    }
}

/// todo
pub const CIRCUIT_CORE: CircuitImpl = CircuitImpl::new();

impl CircuitCoreDef<BabyBear> for CircuitImpl {}
