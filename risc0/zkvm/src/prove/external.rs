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

use std::{
    fs::File,
    io::Write,
    path::{Path, PathBuf},
    process::{Command, Stdio},
};

use anyhow::{anyhow, bail, Result};
use risc0_binfmt::MemoryImage;
use tempfile::tempdir;

use super::Prover;
use crate::{ExecutorEnv, Receipt, Segment, SegmentReceipt, Session, VerifierContext};

/// An implementation of a [Prover] that runs proof workloads via an external
/// `r0vm` process.
pub struct ExternalProver {
    name: String,
    r0vm_path: PathBuf,
    hashfn: String,
}

impl ExternalProver {
    /// Construct an [ExternalProver].
    pub fn new<P: AsRef<Path>>(name: &str, r0vm_path: P, hashfn: &str) -> Self {
        Self {
            name: name.to_string(),
            r0vm_path: r0vm_path.as_ref().to_path_buf(),
            hashfn: hashfn.to_string(),
        }
    }
}

impl Prover for ExternalProver {
    fn prove(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        image: MemoryImage,
    ) -> Result<Receipt> {
        log::debug!("Launching {}", &self.r0vm_path.to_string_lossy());
        let temp_dir = tempdir()?;

        let image_path = temp_dir.path().join("image");
        let receipt_path = temp_dir.path().join("receipt");
        {
            let image_file = File::create(&image_path)?;
            bincode::serialize_into(image_file, &image)?;
        }

        let mut cmd = Command::new(&self.r0vm_path);
        cmd.arg("--image")
            .arg(&image_path)
            .arg("--receipt")
            .arg(&receipt_path)
            .arg("--hashfn")
            .arg(&self.hashfn)
            .stdin(Stdio::piped());

        let mut child = cmd.spawn()?;

        let mut stdin = child.stdin.take().ok_or(anyhow!("Failed to open stdin"))?;
        std::thread::spawn(move || stdin.write_all(&env.input));

        let status = child.wait()?;
        if !status.success() {
            bail!("Failed to run r0vm");
        }

        let receipt_bytes = std::fs::read(receipt_path)?;
        let receipt: Receipt = bincode::deserialize(&receipt_bytes)?;
        let image_id = image.compute_id();
        receipt.verify_with_context(ctx, image_id)?;
        Ok(receipt)
    }

    fn prove_session(&self, _ctx: &VerifierContext, _session: &Session) -> Result<Receipt> {
        bail!("this is unimplemented for prover [{}]", self.get_name())
    }

    fn prove_segment(&self, _ctx: &VerifierContext, _segment: &Segment) -> Result<SegmentReceipt> {
        bail!("this is unimplemented for prover [{}]", self.get_name())
    }

    fn get_peak_memory_usage(&self) -> usize {
        // TODO: get execution stats from external process.
        0
    }

    fn get_name(&self) -> String {
        self.name.clone()
    }
}
