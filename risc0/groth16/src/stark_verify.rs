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

//! This module wraps the stark_verify witness generator.
//!
//! Call `stark_verify`, passing in the path of an input file and the
//! desired path of the output `.wtns` file.


use std::{
    os::raw::{c_int, c_ulong},
    path::Path,
};

extern "C" {
    #[allow(dead_code)]
    /// Verify an input and generate a witness file.
    fn internal_calc_witness(datbuf: *const u8, datsize: c_ulong, jsonfile: *const u8, wtnsfile: *const u8) -> c_int;
}

#[allow(dead_code)]
/// Circuit data which must be provided to stark_verify.
const CIRCUIT_DATA: &[u8] = include_bytes!("../stark_verify_cpp/stark_verify.dat");

/// Verify an input and generate a witness file.
pub fn calc_witness(jsonfile: &Path, wtnsfile: &Path) -> i32 {
    let datptr = CIRCUIT_DATA.as_ptr();
    let datlen = CIRCUIT_DATA.len() as u64;
    let json_arg = jsonfile.to_str().unwrap().as_bytes().as_ptr();
    let wtns_arg = wtnsfile.to_str().unwrap().as_bytes().as_ptr();
    unsafe {
        return internal_calc_witness(datptr, datlen, json_arg, wtns_arg);
    }
}
