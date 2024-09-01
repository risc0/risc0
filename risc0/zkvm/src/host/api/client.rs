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

use std::path::Path;

use anyhow::{anyhow, bail, Result};
use bytes::Bytes;
use prost::Message;

use super::{
    malformed_err, pb, Asset, AssetRequest, ConnectionWrapper, Connector, ParentProcessConnector,
    SessionInfo,
};
use crate::{
    get_version,
    host::{
        api::SegmentInfo,
        client::{env::ProveZkrRequest, prove::get_r0vm_path},
    },
    receipt::{AssumptionReceipt, SegmentReceipt, SuccinctReceipt},
    ExecutorEnv, Journal, ProveInfo, ProverOpts, Receipt, ReceiptClaim, Unknown,
};

/// A client implementation for interacting with a zkVM server.
pub struct Client {
    connector: Box<dyn Connector>,
}

impl Default for Client {
    fn default() -> Self {
        Self::new().unwrap()
    }
}

impl Client {
    /// Construct a [Client] that connects to `r0vm` in a child process.
    pub fn new() -> Result<Self> {
        Self::new_sub_process("r0vm")
    }

    /// Construct a [Client] that connects to a sub-process which implements
    /// the server by calling the specified `server_path`.
    pub fn new_sub_process<P: AsRef<Path>>(server_path: P) -> Result<Self> {
        let connector = ParentProcessConnector::new(server_path)?;
        Ok(Self::with_connector(Box::new(connector)))
    }

    /// Construct a [Client] based on environment variables.
    pub fn from_env() -> Result<Self> {
        Client::new_sub_process(get_r0vm_path()?)
    }

    /// Construct a [Client] using the specified [Connector] to establish a
    /// connection with the server.
    pub fn with_connector(connector: Box<dyn Connector>) -> Self {
        Self { connector }
    }

    /// Prove the specified ELF binary.
    pub fn prove(
        &self,
        env: &ExecutorEnv<'_>,
        opts: &ProverOpts,
        binary: Asset,
    ) -> Result<ProveInfo> {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::Prove(
                pb::api::ProveRequest {
                    env: Some(self.make_execute_env(env, binary.try_into()?)?),
                    opts: Some(opts.clone().into()),
                    receipt_out: Some(pb::api::AssetRequest {
                        kind: Some(pb::api::asset_request::Kind::Inline(())),
                    }),
                },
            )),
        };
        conn.send(request)?;

        let asset = self.prove_handler(&mut conn, env)?;

        let code = conn.close()?;
        if code != 0 {
            bail!("Child finished with: {code}");
        }

        let prove_info_bytes = asset.as_bytes()?;
        let prove_info_pb = pb::core::ProveInfo::decode(prove_info_bytes)?;
        prove_info_pb.try_into()
    }

    /// Execute the specified ELF binary.
    pub fn execute<F>(
        &self,
        env: &ExecutorEnv<'_>,
        binary: Asset,
        segments_out: AssetRequest,
        segment_callback: F,
    ) -> Result<SessionInfo>
    where
        F: FnMut(SegmentInfo, Asset) -> Result<()>,
    {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::Execute(
                pb::api::ExecuteRequest {
                    env: Some(self.make_execute_env(env, binary.try_into()?)?),
                    segments_out: Some(segments_out.try_into()?),
                },
            )),
        };
        tracing::trace!("tx: {request:?}");
        conn.send(request)?;

        let result = self.execute_handler(segment_callback, &mut conn, env);

        let code = conn.close()?;
        if code != 0 {
            bail!("Child finished with: {code}");
        }

        result
    }

    /// Prove the specified segment.
    pub fn prove_segment(
        &self,
        opts: &ProverOpts,
        segment: Asset,
        receipt_out: AssetRequest,
    ) -> Result<SegmentReceipt> {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::ProveSegment(
                pb::api::ProveSegmentRequest {
                    opts: Some(opts.clone().into()),
                    segment: Some(segment.try_into()?),
                    receipt_out: Some(receipt_out.try_into()?),
                },
            )),
        };
        tracing::trace!("tx: {request:?}");
        conn.send(request)?;

        let reply: pb::api::ProveSegmentReply = conn.recv()?;

        let result = match reply.kind.ok_or(malformed_err())? {
            pb::api::prove_segment_reply::Kind::Ok(result) => {
                let receipt_bytes = result.receipt.ok_or(malformed_err())?.as_bytes()?;
                let receipt_pb = pb::core::SegmentReceipt::decode(receipt_bytes)?;
                receipt_pb.try_into()
            }
            pb::api::prove_segment_reply::Kind::Error(err) => Err(err.into()),
        };

        let code = conn.close()?;
        if code != 0 {
            bail!("Child finished with: {code}");
        }

        result
    }

    /// Prove the specified ZKR proof request.
    #[stability::unstable]
    pub fn prove_zkr(
        &self,
        proof_request: ProveZkrRequest,
        receipt_out: AssetRequest,
    ) -> Result<SuccinctReceipt<Unknown>> {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::ProveZkr(
                pb::api::ProveZkrRequest {
                    claim_digest: Some(proof_request.claim_digest.into()),
                    control_id: Some(proof_request.control_id.into()),
                    input: proof_request.input,
                    receipt_out: Some(receipt_out.try_into()?),
                },
            )),
        };

        tracing::trace!("tx: {request:?}");
        conn.send(request)?;

        let reply: pb::api::ProveZkrReply = conn.recv()?;

        let result = match reply.kind.ok_or(malformed_err())? {
            pb::api::prove_zkr_reply::Kind::Ok(result) => {
                let receipt_bytes = result.receipt.ok_or(malformed_err())?.as_bytes()?;
                let receipt_pb = pb::core::SuccinctReceipt::decode(receipt_bytes)?;
                receipt_pb.try_into()
            }
            pb::api::prove_zkr_reply::Kind::Error(err) => Err(err.into()),
        };

        let code = conn.close()?;
        if code != 0 {
            bail!("Child finished with: {code}");
        }

        result
    }

    /// Run the lift program to transform a [SegmentReceipt] into a [SuccinctReceipt].
    ///
    /// The lift program verifies the rv32im circuit STARK proof inside the recursion circuit,
    /// resulting in a recursion circuit STARK proof. This recursion proof has a single
    /// constant-time verification procedure, with respect to the original segment length, and is then
    /// used as the input to all other recursion programs (e.g. join, resolve, and identity_p254).
    pub fn lift(
        &self,
        opts: &ProverOpts,
        receipt: Asset,
        receipt_out: AssetRequest,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::Lift(pb::api::LiftRequest {
                opts: Some(opts.clone().into()),
                receipt: Some(receipt.try_into()?),
                receipt_out: Some(receipt_out.try_into()?),
            })),
        };
        tracing::trace!("tx: {request:?}");
        conn.send(request)?;

        let reply: pb::api::LiftReply = conn.recv()?;

        let result = match reply.kind.ok_or(malformed_err())? {
            pb::api::lift_reply::Kind::Ok(result) => {
                let receipt_bytes = result.receipt.ok_or(malformed_err())?.as_bytes()?;
                let receipt_pb = pb::core::SuccinctReceipt::decode(receipt_bytes)?;
                receipt_pb.try_into()
            }
            pb::api::lift_reply::Kind::Error(err) => Err(err.into()),
        };

        let code = conn.close()?;
        if code != 0 {
            bail!("Child finished with: {code}");
        }

        result
    }

    /// Run the join program to compress two [SuccinctReceipt]s in the same session into one.
    ///
    /// By repeated application of the join program, any number of receipts for execution spans within
    /// the same session can be compressed into a single receipt for the entire session.
    pub fn join(
        &self,
        opts: &ProverOpts,
        left_receipt: Asset,
        right_receipt: Asset,
        receipt_out: AssetRequest,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::Join(pb::api::JoinRequest {
                opts: Some(opts.clone().into()),
                left_receipt: Some(left_receipt.try_into()?),
                right_receipt: Some(right_receipt.try_into()?),
                receipt_out: Some(receipt_out.try_into()?),
            })),
        };
        tracing::trace!("tx: {request:?}");
        conn.send(request)?;

        let reply: pb::api::JoinReply = conn.recv()?;

        let result = match reply.kind.ok_or(malformed_err())? {
            pb::api::join_reply::Kind::Ok(result) => {
                let receipt_bytes = result.receipt.ok_or(malformed_err())?.as_bytes()?;
                let receipt_pb = pb::core::SuccinctReceipt::decode(receipt_bytes)?;
                receipt_pb.try_into()
            }
            pb::api::join_reply::Kind::Error(err) => Err(err.into()),
        };

        let code = conn.close()?;
        if code != 0 {
            bail!("Child finished with: {code}");
        }

        result
    }

    /// Run the resolve program to remove an assumption from a conditional [SuccinctReceipt] upon
    /// verifying a [SuccinctReceipt] proving the validity of the assumption.
    ///
    /// By applying the resolve program, a conditional receipt (i.e. a receipt for an execution
    /// using the `env::verify` API to logically verify a receipt) can be made into an
    /// unconditional receipt.
    pub fn resolve(
        &self,
        opts: &ProverOpts,
        conditional_receipt: Asset,
        assumption_receipt: Asset,
        receipt_out: AssetRequest,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::Resolve(
                pb::api::ResolveRequest {
                    opts: Some(opts.clone().into()),
                    conditional_receipt: Some(conditional_receipt.try_into()?),
                    assumption_receipt: Some(assumption_receipt.try_into()?),
                    receipt_out: Some(receipt_out.try_into()?),
                },
            )),
        };
        tracing::trace!("tx: {request:?}");
        conn.send(request)?;

        let reply: pb::api::ResolveReply = conn.recv()?;

        let result = match reply.kind.ok_or(malformed_err())? {
            pb::api::resolve_reply::Kind::Ok(result) => {
                let receipt_bytes = result.receipt.ok_or(malformed_err())?.as_bytes()?;
                let receipt_pb = pb::core::SuccinctReceipt::decode(receipt_bytes)?;
                receipt_pb.try_into()
            }
            pb::api::resolve_reply::Kind::Error(err) => Err(err.into()),
        };

        let code = conn.close()?;
        if code != 0 {
            bail!("Child finished with: {code}");
        }

        result
    }

    /// Prove the verification of a recursion receipt using the Poseidon254 hash function for FRI.
    ///
    /// The identity_p254 program is used as the last step in the prover pipeline before running the
    /// Groth16 prover. In Groth16 over BN254, it is much more efficient to verify a STARK that was
    /// produced with Poseidon over the BN254 base field compared to using Poseidon over BabyBear.
    pub fn identity_p254(
        &self,
        opts: &ProverOpts,
        receipt: Asset,
        receipt_out: AssetRequest,
    ) -> Result<SuccinctReceipt<ReceiptClaim>> {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::IdentityP254(
                pb::api::IdentityP254Request {
                    opts: Some(opts.clone().into()),
                    receipt: Some(receipt.try_into()?),
                    receipt_out: Some(receipt_out.try_into()?),
                },
            )),
        };
        tracing::trace!("tx: {request:?}");
        conn.send(request)?;

        let reply: pb::api::IdentityP254Reply = conn.recv()?;

        let result = match reply.kind.ok_or(malformed_err())? {
            pb::api::identity_p254_reply::Kind::Ok(result) => {
                let receipt_bytes = result.receipt.ok_or(malformed_err())?.as_bytes()?;
                let receipt_pb = pb::core::SuccinctReceipt::decode(receipt_bytes)?;
                receipt_pb.try_into()
            }
            pb::api::identity_p254_reply::Kind::Error(err) => Err(err.into()),
        };

        let code = conn.close()?;
        if code != 0 {
            bail!("Child finished with: {code}");
        }

        result
    }

    /// Compress a [Receipt], proving the same computation using a smaller representation.
    ///
    /// Proving will, by default, produce a [CompositeReceipt](crate::CompositeReceipt), which
    /// may contain an arbitrary number of receipts assembled into segments and assumptions.
    /// Together, these receipts collectively prove a top-level
    /// [ReceiptClaim](crate::ReceiptClaim). This function can be used to compress all of the constituent
    /// receipts of a [CompositeReceipt](crate::CompositeReceipt) into a single
    /// [SuccinctReceipt](crate::SuccinctReceipt) or [Groth16Receipt](crate::Groth16Receipt) that proves the same top-level claim.
    ///
    /// Compression from [Groth16Receipt](crate::CompositeReceipt) to
    /// [SuccinctReceipt](crate::SuccinctReceipt) is accomplished by iterative application of the
    /// recursion programs including lift, join, and resolve.
    ///
    /// Compression from [SuccinctReceipt](crate::SuccinctReceipt) to
    /// [Groth16Receipt](crate::Groth16Receipt) is accomplished by running a Groth16 recursive
    /// verifier, refered to as the "STARK-to-SNARK" operation.
    ///
    /// NOTE: Compression to [Groth16Receipt](crate::Groth16Receipt) is currently only supported on
    /// x86 hosts, and requires Docker to be installed. See issue
    /// [#1749](https://github.com/risc0/risc0/issues/1749) for more information.
    ///
    /// If the receipt is already at least as compressed as the requested compression level (e.g.
    /// it is already succinct or Groth16 and a succinct receipt is required) this function is a
    /// no-op. As a result, it is idempotent.
    pub fn compress(
        &self,
        opts: &ProverOpts,
        receipt: Asset,
        receipt_out: AssetRequest,
    ) -> Result<Receipt> {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::Compress(
                pb::api::CompressRequest {
                    opts: Some(opts.clone().into()),
                    receipt: Some(receipt.try_into()?),
                    receipt_out: Some(receipt_out.try_into()?),
                },
            )),
        };
        tracing::trace!("tx: {request:?}");
        conn.send(request)?;

        let reply: pb::api::CompressReply = conn.recv()?;

        let result = match reply.kind.ok_or(malformed_err())? {
            pb::api::compress_reply::Kind::Ok(result) => {
                let receipt_bytes = result.receipt.ok_or(malformed_err())?.as_bytes()?;
                let receipt_pb = pb::core::Receipt::decode(receipt_bytes)?;
                receipt_pb.try_into()
            }
            pb::api::compress_reply::Kind::Error(err) => Err(err.into()),
        };

        let code = conn.close()?;
        if code != 0 {
            bail!("Child finished with: {code}");
        }

        result
    }

    fn connect(&self) -> Result<ConnectionWrapper> {
        let mut conn = self.connector.connect()?;

        let client_version = get_version().map_err(|err| anyhow!(err))?;
        let request = pb::api::HelloRequest {
            version: Some(client_version.clone().into()),
        };
        tracing::trace!("tx: {request:?}");
        conn.send(request)?;

        let reply: pb::api::HelloReply = conn.recv()?;
        tracing::trace!("rx: {reply:?}");
        match reply.kind.ok_or(malformed_err())? {
            pb::api::hello_reply::Kind::Ok(reply) => {
                let server_version: semver::Version = reply
                    .version
                    .ok_or(malformed_err())?
                    .try_into()
                    .map_err(|err: semver::Error| anyhow!(err))?;
                if !check_server_version(&client_version, &server_version) {
                    let msg = format!("incompatible server version: {server_version}");
                    tracing::warn!("{msg}");
                    bail!(msg);
                }
            }
            pb::api::hello_reply::Kind::Error(err) => {
                let code = conn.close()?;
                tracing::debug!("Child finished with: {code}");
                bail!(err);
            }
        }

        Ok(conn)
    }

    fn make_execute_env(
        &self,
        env: &ExecutorEnv<'_>,
        binary: pb::api::Asset,
    ) -> Result<pb::api::ExecutorEnv> {
        Ok(pb::api::ExecutorEnv {
            binary: Some(binary),
            env_vars: env.env_vars.clone(),
            args: env.args.clone(),
            slice_ios: env.slice_io.borrow().inner.keys().cloned().collect(),
            read_fds: env.posix_io.borrow().read_fds(),
            write_fds: env.posix_io.borrow().write_fds(),
            segment_limit_po2: env.segment_limit_po2,
            session_limit: env.session_limit,
            trace_events: (!env.trace.is_empty()).then_some(()),
            coprocessor: env.coprocessor.is_some(),
            pprof_out: env
                .pprof_out
                .as_ref()
                .map(|x| x.to_string_lossy().into())
                .unwrap_or_default(),
            assumptions: env
                .assumptions
                .borrow()
                .iter()
                .map(|a| {
                    Ok(match a {
                        AssumptionReceipt::Proven(inner) => pb::api::AssumptionReceipt {
                            kind: Some(pb::api::assumption_receipt::Kind::Proven(
                                Asset::Inline(
                                    pb::core::InnerReceipt::from(inner.clone())
                                        .encode_to_vec()
                                        .into(),
                                )
                                .try_into()?,
                            )),
                        },
                        AssumptionReceipt::Unresolved(assumption) => pb::api::AssumptionReceipt {
                            kind: Some(pb::api::assumption_receipt::Kind::Unresolved(
                                Asset::Inline(
                                    pb::core::Assumption::from(assumption.clone())
                                        .encode_to_vec()
                                        .into(),
                                )
                                .try_into()?,
                            )),
                        },
                    })
                })
                .collect::<Result<_>>()?,
            segment_path: env
                .segment_path
                .as_ref()
                .map(|x| x.path().to_string_lossy().into())
                .unwrap_or_default(),
        })
    }

    fn execute_handler<F>(
        &self,
        segment_callback: F,
        conn: &mut ConnectionWrapper,
        env: &ExecutorEnv<'_>,
    ) -> Result<SessionInfo>
    where
        F: FnMut(SegmentInfo, Asset) -> Result<()>,
    {
        let mut segment_callback = segment_callback;
        let mut segments = Vec::new();
        loop {
            let reply: pb::api::ServerReply = conn.recv()?;
            tracing::trace!("rx: {reply:?}");

            match reply.kind.ok_or(malformed_err())? {
                pb::api::server_reply::Kind::Ok(request) => {
                    match request.kind.ok_or(malformed_err())? {
                        pb::api::client_callback::Kind::Io(io) => {
                            let msg: pb::api::OnIoReply = self.on_io(env, io).into();
                            tracing::trace!("tx: {msg:?}");
                            conn.send(msg)?;
                        }
                        pb::api::client_callback::Kind::SegmentDone(segment) => {
                            let reply: pb::api::GenericReply = segment
                                .segment
                                .map_or_else(
                                    || Err(malformed_err()),
                                    |segment| {
                                        let asset =
                                            segment.segment.ok_or(malformed_err())?.try_into()?;
                                        let info = SegmentInfo {
                                            po2: segment.po2,
                                            cycles: segment.cycles,
                                        };
                                        segments.push(info.clone());
                                        segment_callback(info, asset)
                                    },
                                )
                                .into();
                            tracing::trace!("tx: {reply:?}");
                            conn.send(reply)?;
                        }
                        pb::api::client_callback::Kind::SessionDone(session) => {
                            return match session.session {
                                Some(session) => Ok(SessionInfo {
                                    segments,
                                    journal: Journal::new(session.journal),
                                    exit_code: session
                                        .exit_code
                                        .ok_or(malformed_err())?
                                        .try_into()?,
                                }),
                                None => Err(malformed_err()),
                            }
                        }
                        pb::api::client_callback::Kind::ProveDone(_) => {
                            return Err(anyhow!("Illegal client callback"))
                        }
                    }
                }
                pb::api::server_reply::Kind::Error(err) => return Err(err.into()),
            }
        }
    }

    fn prove_handler(
        &self,
        conn: &mut ConnectionWrapper,
        env: &ExecutorEnv<'_>,
    ) -> Result<pb::api::Asset> {
        loop {
            let reply: pb::api::ServerReply = conn.recv()?;
            tracing::trace!("rx: {reply:?}");

            match reply.kind.ok_or(malformed_err())? {
                pb::api::server_reply::Kind::Ok(request) => {
                    match request.kind.ok_or(malformed_err())? {
                        pb::api::client_callback::Kind::Io(io) => {
                            let msg: pb::api::OnIoReply = self.on_io(env, io).into();
                            tracing::trace!("tx: {msg:?}");
                            conn.send(msg)?;
                        }
                        pb::api::client_callback::Kind::SegmentDone(_) => {
                            return Err(anyhow!("Illegal client callback"))
                        }
                        pb::api::client_callback::Kind::SessionDone(_) => {
                            return Err(anyhow!("Illegal client callback"))
                        }
                        pb::api::client_callback::Kind::ProveDone(done) => {
                            return done.prove_info.ok_or(malformed_err())
                        }
                    }
                }
                pb::api::server_reply::Kind::Error(err) => return Err(err.into()),
            }
        }
    }

    fn on_io(&self, env: &ExecutorEnv<'_>, request: pb::api::OnIoRequest) -> Result<Bytes> {
        match request.kind.ok_or(malformed_err())? {
            pb::api::on_io_request::Kind::Posix(posix) => {
                let cmd = posix.cmd.ok_or(malformed_err())?;
                match cmd.kind.ok_or(malformed_err())? {
                    pb::api::posix_cmd::Kind::Read(nread) => {
                        self.on_posix_read(env, posix.fd, nread as usize)
                    }
                    pb::api::posix_cmd::Kind::Write(from_guest) => {
                        self.on_posix_write(env, posix.fd, from_guest.into())?;
                        Ok(Bytes::new())
                    }
                }
            }
            pb::api::on_io_request::Kind::Slice(slice_io) => {
                self.on_slice(env, &slice_io.name, slice_io.from_guest.into())
            }
            pb::api::on_io_request::Kind::Trace(event) => {
                self.on_trace(env, event)?;
                Ok(Bytes::new())
            }
            pb::api::on_io_request::Kind::Coprocessor(request) => {
                self.on_coprocessor(env, request)?;
                Ok(Bytes::new())
            }
        }
    }

    fn on_posix_read(&self, env: &ExecutorEnv<'_>, fd: u32, nread: usize) -> Result<Bytes> {
        tracing::debug!("on_posix_read: {fd}, {nread}");
        let mut from_host = vec![0; nread];
        let posix_io = env.posix_io.borrow();
        let reader = posix_io.get_reader(fd)?;
        let nread = reader.borrow_mut().read(&mut from_host)?;
        let slice = from_host[..nread].to_vec();
        Ok(slice.into())
    }

    fn on_posix_write(&self, env: &ExecutorEnv<'_>, fd: u32, from_guest: Bytes) -> Result<()> {
        tracing::debug!("on_posix_write: {fd}");
        let posix_io = env.posix_io.borrow();
        let writer = posix_io.get_writer(fd)?;
        writer.borrow_mut().write_all(&from_guest)?;
        Ok(())
    }

    fn on_slice(&self, env: &ExecutorEnv<'_>, name: &str, from_guest: Bytes) -> Result<Bytes> {
        let table = env.slice_io.borrow();
        let slice_io = table
            .inner
            .get(name)
            .ok_or(anyhow!("Unknown I/O channel name: {name}"))?;
        let result = slice_io.borrow_mut().handle_io(name, from_guest)?;
        Ok(result)
    }

    fn on_trace(&self, env: &ExecutorEnv<'_>, event: pb::api::TraceEvent) -> Result<()> {
        for trace_callback in env.trace.iter() {
            trace_callback
                .borrow_mut()
                .trace_callback(event.clone().try_into()?)?;
        }
        Ok(())
    }

    fn on_coprocessor(
        &self,
        env: &ExecutorEnv<'_>,
        coprocessor_request: pb::api::CoprocessorRequest,
    ) -> Result<()> {
        match coprocessor_request.kind.ok_or(malformed_err())? {
            pb::api::coprocessor_request::Kind::ProveZkr(proof_request) => {
                let proof_request = proof_request.try_into()?;
                let coprocessor = env.coprocessor.clone().ok_or(malformed_err())?;
                let mut coprocessor = coprocessor.borrow_mut();
                coprocessor.prove_zkr(proof_request)
            }
        }
    }
}

impl From<Result<Bytes, anyhow::Error>> for pb::api::OnIoReply {
    fn from(result: Result<Bytes, anyhow::Error>) -> Self {
        Self {
            kind: Some(match result {
                Ok(bytes) => pb::api::on_io_reply::Kind::Ok(bytes.into()),
                Err(err) => pb::api::on_io_reply::Kind::Error(err.into()),
            }),
        }
    }
}

pub(crate) fn check_server_version(requested: &semver::Version, server: &semver::Version) -> bool {
    if requested.pre.is_empty() {
        requested.major == server.major && requested.minor == server.minor
    } else {
        requested == server
    }
}

#[cfg(test)]
mod tests {
    use semver::Version;

    use super::check_server_version;

    #[test]
    fn check_version() {
        fn test(requested: &str, server: &str) -> bool {
            check_server_version(
                &Version::parse(requested).unwrap(),
                &Version::parse(server).unwrap(),
            )
        }

        assert!(test("0.18.0", "0.18.0"));
        assert!(test("0.18.0", "0.18.1"));
        assert!(test("0.18.1", "0.18.1"));
        assert!(test("0.18.1", "0.18.2"));
        assert!(test("0.18.1", "0.18.0"));
        assert!(!test("0.18.0", "0.19.0"));

        assert!(test("1.0.0", "1.0.0"));
        assert!(test("1.0.0", "1.0.1"));
        assert!(test("1.1.0", "1.1.0"));
        assert!(test("1.1.0", "1.1.1"));
        assert!(!test("1.0.0", "0.18.0"));
        assert!(!test("1.0.0", "2.0.0"));
        assert!(!test("1.1.0", "1.0.0"));
        assert!(test("1.0.3", "1.0.1"));

        assert!(test("0.19.0-alpha.1", "0.19.0-alpha.1"));
        assert!(!test("0.19.0-alpha.1", "0.19.0-alpha.2"));
    }
}
