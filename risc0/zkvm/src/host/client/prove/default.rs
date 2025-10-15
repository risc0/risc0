// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{
    io::{Read, Write},
    os::{fd::OwnedFd, unix::net::UnixStream},
    path::Path,
    process::{Child, Command},
    sync::Arc,
};

use anyhow::{Context as _, Result, bail, ensure};
use risc0_zkvm_platform::fileno;
use serde::de::DeserializeOwned;

use crate::{
    ExecutorEnv, InnerReceipt, ProveInfo, Receipt, ReceiptKind, SessionInfo, VerifierContext,
    rpc::{
        JobInfo, JobRequest, JobStatus, ProofRequest, ProofResult, ShrinkWrapKind,
        ShrinkWrapRequest, ShrinkWrapResult,
    },
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
        cmd.env_remove("RISC0_DEV_MODE")
            .stdin(child_fd)
            .arg("--rpc");
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
        opts: &ProverOpts,
    ) -> Result<ProveInfo> {
        let stdout_writer = env
            .posix_io
            .borrow()
            .get_writer(fileno::STDOUT)
            .ok()
            .clone();

        let dev_mode = opts.dev_mode();
        let result = self.prove(env, elf, false /* execute_only */, dev_mode)?;

        let mut prove_info = ProveInfo {
            receipt: Arc::into_inner(result.receipt.unwrap()).unwrap(),
            work_receipt: None, // TODO(povw): implement PoVW here
            stats: result.session.stats.clone(),
        };

        prove_info.stats.log_if_risc0_info_set();

        if opts.receipt_kind == ReceiptKind::Groth16 {
            prove_info.receipt = self.shrink_wrap_groth16(&prove_info.receipt, dev_mode)?;
        }

        if let Some(stdout_writer) = stdout_writer {
            stdout_writer
                .borrow_mut()
                .write_all(&result.session.stdout)?;
        }

        Ok(prove_info)
    }

    fn compress(&self, opts: &ProverOpts, receipt: &Receipt) -> Result<Receipt> {
        let dev_mode = opts.dev_mode();

        match &receipt.inner {
            InnerReceipt::Composite(_) => match opts.receipt_kind {
                ReceiptKind::Composite => Ok(receipt.clone()),
                ReceiptKind::Succinct => unimplemented!("missing composite -> succinct conversion"),
                ReceiptKind::Groth16 => self.shrink_wrap_groth16(receipt, dev_mode),
            },
            InnerReceipt::Succinct(_) => match opts.receipt_kind {
                ReceiptKind::Composite | ReceiptKind::Succinct => Ok(receipt.clone()),
                ReceiptKind::Groth16 => self.shrink_wrap_groth16(receipt, dev_mode),
            },
            InnerReceipt::Groth16(_) => match opts.receipt_kind {
                ReceiptKind::Composite | ReceiptKind::Succinct | ReceiptKind::Groth16 => {
                    Ok(receipt.clone())
                }
            },
            InnerReceipt::Fake(_) => {
                ensure!(
                    dev_mode,
                    "dev mode must be enabled to compress fake receipts"
                );
                Ok(receipt.clone())
            }
        }
    }
}

impl Executor for DefaultProver {
    fn execute(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<SessionInfo> {
        Ok(Arc::into_inner(
            self.prove(
                env, elf, true,  /* execute_only */
                false, /* dev_mode */
            )?
            .session,
        )
        .unwrap()
        .into())
    }
}

impl DefaultProver {
    fn rpc_request<RequestT, ResultT>(&self, request: RequestT) -> Result<ResultT>
    where
        JobRequest: From<RequestT>,
        ResultT: DeserializeOwned,
    {
        let mut socket = &self.socket;

        let mut buf = vec![0u8; 4];
        bincode::serialize_into(&mut buf, &JobRequest::from(request))
            .context("error serializing RPC header")?;
        let body_len = buf.len() as u32 - 4;
        bincode::serialize_into(&mut buf[0..4], &body_len).context("error serializing RPC body")?;

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
        let job_info: JobInfo<ResultT> =
            bincode::deserialize(&buf).context("error deserializing RPC body")?;

        tracing::info!("Elapsed time: {:?}", job_info.elapsed_time);

        Ok(match job_info.status {
            JobStatus::Running(progress) => bail!("Job is still running: {progress}"),
            JobStatus::Succeeded(result) => result,
            JobStatus::Failed(err) => bail!(format!("Task error: {err:?}")),
            JobStatus::TimedOut => bail!("TimedOut"),
            JobStatus::Aborted => bail!("Aborted"),
        })
    }

    fn prove(
        &self,
        env: ExecutorEnv<'_>,
        elf: &[u8],
        execute_only: bool,
        dev_mode: bool,
    ) -> Result<ProofResult> {
        let proof_request = ProofRequest {
            binary: elf.to_vec(),
            input: env.input,
            assumptions: env.assumptions.borrow().0.clone(),
            segment_limit_po2: env.segment_limit_po2,
            execute_only,
            dev_mode,
        };

        self.rpc_request(proof_request)
    }

    fn shrink_wrap_groth16(&self, receipt: &Receipt, dev_mode: bool) -> Result<Receipt> {
        let shrink_wrap_request = ShrinkWrapRequest {
            kind: ShrinkWrapKind::Groth16,
            receipt: receipt.clone(),
            dev_mode,
        };
        let result: ShrinkWrapResult = self.rpc_request(shrink_wrap_request)?;
        Ok(Arc::into_inner(result.receipt).unwrap())
    }
}
