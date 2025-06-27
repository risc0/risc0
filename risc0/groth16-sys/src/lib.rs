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

extern crate circom_witnesscalc;

use std::ffi::{c_char, CStr};

use anyhow::{anyhow, Result};

#[repr(C)]
pub struct RawProverParams {
    pub graph_path: *const c_char,
    pub pcoeffs_path: *const c_char,
    pub fres_path: *const c_char,
    pub srs_path: *const c_char,
    pub inputs_path: *const c_char,
    pub public_path: *const c_char,
    pub proof_path: *const c_char,
}

#[cfg(feature = "cuda")]
extern "C" {
    pub fn risc0_groth16_cuda_prove(params: *const RawProverParams) -> *const c_char;
}

pub fn ffi_wrap<F>(mut inner: F) -> Result<()>
where
    F: FnMut() -> *const c_char,
{
    extern "C" {
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

#[cfg(test)]
mod tests {
    use super::*;

    #[cfg(feature = "cuda")]
    #[test_log::test]
    fn test() {
        tracing::info!("hi");

        let params = RawProverParams {
            graph_path: c"/home/flaub/src/risc0/groth16_proof/supra/output-files/parallel-graph"
                .as_ptr(),
            pcoeffs_path:
                c"/home/flaub/src/risc0/groth16_proof/supra/output-files/preprocessed_coeffs.bin"
                    .as_ptr(),
            fres_path:
                c"/home/flaub/src/risc0/groth16_proof/supra/output-files/fuzzed_msm_results.bin"
                    .as_ptr(),
            srs_path:
                c"/home/flaub/src/risc0/groth16_proof/supra/input-files/stark_verify_final.zkey"
                    .as_ptr(),
            inputs_path: c"/home/flaub/src/risc0/groth16_proof/supra/input-files/fib-seal.json"
                .as_ptr(),
            public_path: c"/home/flaub/src/risc0/groth16_proof/supra/public.json".as_ptr(),
            proof_path: c"/home/flaub/src/risc0/groth16_proof/supra/proof.json".as_ptr(),
        };

        ffi_wrap(|| unsafe { risc0_groth16_cuda_prove(&params) }).unwrap();
    }
}
