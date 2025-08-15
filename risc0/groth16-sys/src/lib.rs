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

use std::{
    ffi::{CStr, CString, NulError, c_char},
    path::{Path, PathBuf},
};

use anyhow::{Result, anyhow};

#[cfg(feature = "cuda")]
pub use sppark::Error as SpparkError;

pub struct SetupParams {
    pub pcoeffs_path: RawPath,
    pub fres_path: RawPath,
    pub srs_path: RawPath,
}

impl SetupParams {
    pub fn new(root_dir: &Path) -> anyhow::Result<Self> {
        Ok(SetupParams {
            pcoeffs_path: root_dir.join("preprocessed_coeffs.bin").try_into()?,
            fres_path: root_dir.join("fuzzed_msm_results.bin").try_into()?,
            srs_path: root_dir.join("stark_verify_final.zkey").try_into()?,
        })
    }
}

pub struct WitnessParams {
    pub graph_path: PathBuf,
}

impl WitnessParams {
    pub fn new(root_dir: &Path) -> Self {
        WitnessParams {
            graph_path: root_dir.join("stark_verify_graph.bin"),
        }
    }
}

pub struct ProverParams {
    pub public_path: RawPath,
    pub proof_path: RawPath,
    pub witness: *const u8,
}

impl ProverParams {
    pub fn new(root_dir: &Path, witness: *const u8) -> anyhow::Result<Self> {
        Ok(Self {
            public_path: root_dir.join("public.json").try_into()?,
            proof_path: root_dir.join("proof.json").try_into()?,
            witness,
        })
    }
}

#[cfg(feature = "cuda")]
pub fn prove(prover_params: &ProverParams, setup_params: &SetupParams) -> anyhow::Result<()> {
    let setup_params = RawSetupParams {
        pcoeffs_path: setup_params.pcoeffs_path.c_str.as_ptr(),
        fres_path: setup_params.fres_path.c_str.as_ptr(),
        srs_path: setup_params.srs_path.c_str.as_ptr(),
    };
    let prover_params = RawProverParams {
        public_path: prover_params.public_path.c_str.as_ptr(),
        proof_path: prover_params.proof_path.c_str.as_ptr(),
        witness: prover_params.witness,
    };

    ffi_wrap(|| unsafe { risc0_groth16_cuda_prove(&setup_params, &prover_params) })
}

#[cfg(all(feature = "cuda", feature = "setup"))]
pub fn setup(params: &SetupParams) -> anyhow::Result<()> {
    let raw_params = RawSetupParams {
        pcoeffs_path: params.pcoeffs_path.c_str.as_ptr(),
        fres_path: params.fres_path.c_str.as_ptr(),
        srs_path: params.srs_path.c_str.as_ptr(),
    };
    ffi_wrap(|| unsafe { risc0_groth16_cuda_setup(&raw_params) })
}

#[cfg_attr(not(feature = "cuda"), allow(dead_code))]
#[repr(C)]
struct RawProverParams {
    pub public_path: *const c_char,
    pub proof_path: *const c_char,
    pub witness: *const u8,
}

#[cfg_attr(not(feature = "cuda"), allow(dead_code))]
#[repr(C)]
struct RawSetupParams {
    pub pcoeffs_path: *const c_char,
    pub fres_path: *const c_char,
    pub srs_path: *const c_char,
}

unsafe extern "C" {
    #[cfg(feature = "cuda")]
    fn risc0_groth16_cuda_prove(
        setup: *const RawSetupParams,
        params: *const RawProverParams,
    ) -> *const c_char;

    #[cfg(all(feature = "cuda", feature = "setup"))]
    fn risc0_groth16_cuda_setup(params: *const RawSetupParams) -> *const c_char;
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

#[cfg_attr(not(feature = "cuda"), allow(dead_code))]
pub struct RawPath {
    path: PathBuf,
    c_str: CString,
}

impl RawPath {
    pub fn as_path(&self) -> &Path {
        &self.path
    }
}

impl TryFrom<&Path> for RawPath {
    type Error = NulError;

    fn try_from(value: &Path) -> Result<Self, Self::Error> {
        Ok(RawPath {
            path: value.to_path_buf(),
            c_str: CString::new(value.as_os_str().as_encoded_bytes())?,
        })
    }
}

impl TryFrom<PathBuf> for RawPath {
    type Error = NulError;

    fn try_from(value: PathBuf) -> Result<Self, Self::Error> {
        RawPath::try_from(value.as_path())
    }
}
