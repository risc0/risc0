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

//use core::ffi::{c_void, CStr};

//use anyhow::{anyhow, Result};
use risc0_circuit_keccak_sys::ffi::{
    // get_trampoline,
    risc0_circuit_keccak_poly_fp,
    //risc0_circuit_keccak_step_compute_accum,
    //risc0_circuit_keccak_step_exec, risc0_circuit_keccak_step_verify_accum,
    //    risc0_circuit_keccak_step_verify_bytes, risc0_circuit_keccak_step_verify_mem,
    // risc0_circuit_keccak_string_free,
    //     risc0_circuit_keccak_string_ptr,
    //    Callback,
    //    RawError,
};
use risc0_zkp::{
    adapter::{
        //CircuitProveDef,
        //CircuitStep, CircuitStepContext, CircuitStepHandler,
        PolyFp,
    },
    field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
    //    hal::cpu::SyncSlice,
};

use crate::CircuitImpl;

impl PolyFp<BabyBear> for CircuitImpl {
    fn poly_fp(
        &self,
        cycle: usize,
        steps: usize,
        mix: &[BabyBearExtElem],
        args: &[&[BabyBearElem]],
    ) -> BabyBearExtElem {
        let args: Vec<*const BabyBearElem> = args.iter().map(|x| (*x).as_ptr()).collect();
        unsafe { risc0_circuit_keccak_poly_fp(cycle, steps, mix.as_ptr(), args.as_ptr()) }
    }
}
