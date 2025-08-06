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
    io::{Read, Write},
    os::{fd::OwnedFd, unix::net::UnixStream},
    path::Path,
    process::{Child, Command},
    sync::Arc,
};

use anyhow::{bail, Context as _, Result};

use crate::{
    rpc::{JobInfo, JobStatus, ProofRequest},
    ExecutorEnv, ProveInfo, Receipt, SessionInfo, SessionStats, VerifierContext,
};

use super::{Executor, Prover, ProverOpts};

/// TODO
pub struct DefaultProver {
    child: Child,
    socket: UnixStream,
}

/// An implementation of a [Prover] that runs proof workloads via local `r0vm` cluster.
impl DefaultProver {
    /// Construct a [DefaultProver].
    pub fn new<P: AsRef<Path>>(r0vm_path: P) -> Result<Self> {
        let r0vm_path = r0vm_path.as_ref();

        let (socket, child_socket) = UnixStream::pair()?;
        let child_fd: OwnedFd = child_socket.into();
        let mut cmd = Command::new(r0vm_path);
        cmd.stdin(child_fd).arg("--rpc");
        if let Ok(num_gpus) = std::env::var("RISC0_DEFAULT_PROVER_NUM_GPUS") {
            cmd.arg("--num-gpus").arg(num_gpus);
        }
        let child = cmd.spawn().with_context(|| spawn_fail(r0vm_path))?;

        Ok(Self { child, socket })
    }

    /// TODO
    pub fn stop(&mut self) -> Result<()> {
        self.socket.shutdown(std::net::Shutdown::Both)?;
        self.child.wait()?;

        Ok(())
    }
}

impl Drop for DefaultProver {
    fn drop(&mut self) {
        if let Err(error) = self.stop() {
            tracing::warn!("error stopping r0vm: {error}");
        }
    }
}

fn spawn_fail(path: &Path) -> String {
    format!("Could not launch \"{}\".", path.to_string_lossy())
}

impl Prover for DefaultProver {
    fn get_name(&self) -> String {
        "default".to_string()
    }

    fn prove_with_ctx(
        &self,
        env: ExecutorEnv<'_>,
        _ctx: &VerifierContext,
        elf: &[u8],
        _opts: &ProverOpts,
    ) -> Result<ProveInfo> {
        let proof_request = ProofRequest {
            binary: elf.to_vec(),
            input: env.input,
            assumptions: env.assumptions.borrow().0.clone(),
            segment_limit_po2: env.segment_limit_po2,
        };

        let mut buf = vec![0u8; 4];
        bincode::serialize_into(&mut buf, &proof_request)
            .context("error serializing RPC header")?;
        let body_len = buf.len() as u32 - 4;
        bincode::serialize_into(&mut buf[0..4], &body_len).context("error serializing RPC body")?;
        let mut socket = &self.socket;

        socket
            .write_all(&buf)
            .context("error sending RPC message")?;

        let mut buf = vec![0u8; 4];
        socket
            .read_exact(&mut buf)
            .context("error receiving RPC header")?;
        let body_len: u32 = bincode::deserialize(&buf).context("error deserializing RPC header")?;
        let mut buf = vec![0u8; body_len as usize];
        socket
            .read_exact(&mut buf)
            .context("error receiving RPC body")?;
        let job_info: JobInfo =
            bincode::deserialize(&buf).context("error deserializing RPC body")?;

        tracing::info!("Elapsed time: {:?}", job_info.elapsed_time);

        let prove_info = match job_info.status {
            JobStatus::Running(progress) => bail!("Job is still running: {progress}"),
            JobStatus::Succeeded(result) => ProveInfo {
                receipt: Arc::into_inner(result.receipt).unwrap(),
                work_receipt: None, // TODO(povw): implement PoVW here
                stats: SessionStats {
                    segments: result.session.segment_count,
                    total_cycles: result.session.total_cycles,
                    user_cycles: result.session.user_cycles,
                    paging_cycles: 0,
                    reserved_cycles: 0,
                },
            },
            JobStatus::Failed(err) => bail!(format!("Task error: {err:?}")),
            JobStatus::TimedOut => bail!("TimedOut"),
            JobStatus::Aborted => bail!("Aborted"),
        };

        Ok(prove_info)
    }

    fn compress(&self, _opts: &ProverOpts, _receipt: &Receipt) -> Result<Receipt> {
        unimplemented!()
    }
}

impl Executor for DefaultProver {
    fn execute(&self, _env: ExecutorEnv<'_>, _elf: &[u8]) -> Result<SessionInfo> {
        todo!()
    }
}
