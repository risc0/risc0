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

use std::ffi::{CStr, c_char};

use anyhow::{Result, anyhow};

#[cfg(feature = "cuda")]
pub use sppark::Error as SpparkError;

pub struct ProveParams<'a> {
    pub pcoeffs: &'a [u8],
    pub fres: &'a [u8],
    pub srs: &'a [u8],
}

pub struct SetupParams<'a> {
    pub srs: &'a [u8],
    pub fuzzed_results_out: &'a mut [u8],
    pub preprocessed_coeffs_out: &'a mut [u8],
}

#[cfg(feature = "cuda")]
pub fn prove(witness: &[u8], prove_params: &ProveParams<'_>) -> anyhow::Result<Groth16Proof> {
    let prove_params = RawProveParams {
        pcoeffs: prove_params.pcoeffs.as_ptr(),
        fres: prove_params.fres.as_ptr(),
        srs: prove_params.srs.as_ptr(),
        srs_len: prove_params.srs.len(),
    };

    let mut proof = Groth16Proof::default();
    ffi_wrap(|| unsafe { risc0_groth16_cuda_prove(&prove_params, witness.as_ptr(), &mut proof) })?;
    Ok(proof)
}

/// Returns bytes copied into (fuzzed_results, preprocessed_coeffs)
#[cfg(all(feature = "cuda", feature = "setup"))]
pub fn setup(params: &mut SetupParams<'_>) -> anyhow::Result<(usize, usize)> {
    let mut fuzzed_results_copied = 0usize;
    let mut preprocessed_coeffs_copied = 0usize;

    let mut raw_params = RawSetupParams {
        srs: params.srs.as_ptr(),
        srs_len: params.srs.len(),
        fuzzed_results_len: params.fuzzed_results_out.len(),
        fuzzed_results_out: params.fuzzed_results_out.as_mut_ptr(),
        preprocessed_coeffs_len: params.preprocessed_coeffs_out.len(),
        preprocessed_coeffs_out: params.preprocessed_coeffs_out.as_mut_ptr(),
        fuzzed_results_copied: &mut fuzzed_results_copied,
        preprocessed_coeffs_copied: &mut preprocessed_coeffs_copied,
    };
    ffi_wrap(|| unsafe { risc0_groth16_cuda_setup(&mut raw_params) })?;
    Ok((fuzzed_results_copied, preprocessed_coeffs_copied))
}

#[cfg_attr(not(feature = "cuda"), allow(dead_code))]
#[repr(C)]
struct RawProveParams {
    pub pcoeffs: *const u8,
    pub fres: *const u8,
    pub srs: *const u8,
    pub srs_len: usize,
}

#[cfg_attr(not(all(feature = "cuda", feature = "setup")), allow(dead_code))]
#[repr(C)]
struct RawSetupParams {
    pub srs: *const u8,
    pub srs_len: usize,
    pub fuzzed_results_len: usize,
    pub preprocessed_coeffs_len: usize,
    pub fuzzed_results_copied: *mut usize,
    pub preprocessed_coeffs_copied: *mut usize,
    pub fuzzed_results_out: *mut u8,
    pub preprocessed_coeffs_out: *mut u8,
}

#[cfg_attr(not(feature = "cuda"), allow(dead_code))]
#[repr(C)]
#[derive(Default)]
pub struct Fp {
    pub v: [u32; 8],
}

#[cfg_attr(not(feature = "cuda"), allow(dead_code))]
#[repr(C)]
#[derive(Default)]
pub struct Groth16Proof {
    pub a: [Fp; 2],
    pub c: [Fp; 2],
    pub b: [Fp; 4],
}

unsafe extern "C" {
    #[cfg(feature = "cuda")]
    fn risc0_groth16_cuda_prove(
        setup: *const RawProveParams,
        witness: *const u8,
        proof_out: *mut Groth16Proof,
    ) -> *const c_char;

    #[cfg(all(feature = "cuda", feature = "setup"))]
    fn risc0_groth16_cuda_setup(params: *mut RawSetupParams) -> *const c_char;
}

#[cfg_attr(not(feature = "cuda"), allow(dead_code))]
fn ffi_wrap<F>(mut inner: F) -> Result<()>
where
    F: FnMut() -> *const c_char,
{
    unsafe extern "C" {
        fn free(str: *const c_char);
    }

    let c_ptr = inner();
    if c_ptr.is_null() {
        Ok(())
    } else {
        let what = unsafe {
            let msg = CStr::from_ptr(c_ptr)
                .to_str()
                .unwrap_or("Invalid error msg pointer")
                .to_string();
            free(c_ptr);
            msg
        };
        Err(anyhow!(what))
    }
}
