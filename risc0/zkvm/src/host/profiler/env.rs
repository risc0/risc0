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

use anyhow::anyhow;
use std::path::PathBuf;

/// Return the requested pprof profile path, set via the RISC0_PPROF_OUT environment variable.
pub(crate) fn pprof_path() -> Option<PathBuf> {
    match std::env::var("RISC0_PPROF_OUT") {
        Ok(path) => {
            log::debug!("pprof output path set to: {path}");
            Some(PathBuf::from(path))
        }
        Err(std::env::VarError::NotPresent) => None,
        Err(std::env::VarError::NotUnicode(_)) => {
            log::warn!("Environment variable RISC0_PPROF_OUT is malformed");
            None
        }
    }
}

/// Write the given pprof profile pprof_path()
pub(crate) fn write_pprof_file(profile: &[u8]) -> anyhow::Result<()> {
    let path = pprof_path().ok_or(anyhow!("no path set to write pprof profile"))?;
    log::debug!("writing profile to: {}", path.display());
    std::fs::write(path, profile)?;
    Ok(())
}
