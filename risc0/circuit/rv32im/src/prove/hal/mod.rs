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

pub(crate) mod cpp;
pub mod cpu;
#[cfg(feature = "cuda")]
pub mod cuda;
#[cfg(feature = "metal")]
pub mod metal;
pub mod testutil;

use risc0_circuit_rv32im_sys::ffi::RawPreflightTrace;
use risc0_zkp::hal::Hal;

pub(crate) trait CircuitWitnessGenerator<H: Hal> {
    fn generate_witness(
        &self,
        _trace: &RawPreflightTrace,
        _steps: usize,
        _count: usize,
        _ctrl: &H::Buffer<H::Elem>,
        _io: &H::Buffer<H::Elem>,
        _data: &H::Buffer<H::Elem>,
    ) {
        todo!();
    }
}
