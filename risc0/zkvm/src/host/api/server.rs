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
    error::Error as StdError,
    io::{BufReader, Error as IoError, ErrorKind as IoErrorKind, Read, Write},
    path::{Path, PathBuf},
};

use anyhow::{anyhow, bail, Context, Result};
use bytes::Bytes;
use prost::Message;
use risc0_zkp::core::digest::Digest;

use super::{malformed_err, path_to_string, pb, ConnectionWrapper, Connector, TcpConnector};
use crate::{
    get_prover_server, get_version,
    host::{
        api::convert::keccak_input_to_bytes,
        client::{
            env::{CoprocessorCallback, ProveKeccakRequest, ProveZkrRequest},
            slice_io::SliceIo,
        },
        server::{
            exec::executor::ExecutorImpl, prove::keccak::prove_keccak, session::NullSegmentRef,
        },
    },
    prove_registered_zkr,
    recursion::identity_p254,
    AssetRequest, Assumption, ExecutorEnv, InnerAssumptionReceipt, ProverOpts, Receipt,
    ReceiptClaim, Segment, SegmentReceipt, SegmentRef, Session, SuccinctReceipt, TraceCallback,
    TraceEvent, Unknown, VerifierContext,
};

/// A server implementation for handling requests by clients of the zkVM.
pub struct Server {
    connector: Box<dyn Connector>,
}

struct PosixIoProxy {
    fd: u32,
    conn: ConnectionWrapper,
}

impl PosixIoProxy {
    fn new(fd: u32, conn: ConnectionWrapper) -> Self {
        PosixIoProxy { fd, conn }
    }
}

impl Read for PosixIoProxy {
    fn read(&mut self, to_guest: &mut [u8]) -> std::io::Result<usize> {
        let nread = to_guest.len().try_into().map_io_err()?;
        let request = pb::api::ServerReply {
            kind: Some(pb::api::server_reply::Kind::Ok(pb::api::ClientCallback {
                kind: Some(pb::api::client_callback::Kind::Io(pb::api::OnIoRequest {
                    kind: Some(pb::api::on_io_request::Kind::Posix(pb::api::PosixIo {
                        fd: self.fd,
                        cmd: Some(pb::api::PosixCmd {
                            kind: Some(pb::api::posix_cmd::Kind::Read(nread)),
                        }),
                    })),
                })),
            })),
        };

        tracing::trace!("tx: {request:?}");
        let reply: pb::api::OnIoReply = self.conn.send_recv(request).map_io_err()?;
        tracing::trace!("rx: {reply:?}");

        let kind = reply.kind.ok_or("Malformed message").map_io_err()?;
        match kind {
            pb::api::on_io_reply::Kind::Ok(bytes) => {
                let (head, _) = to_guest.split_at_mut(bytes.len());
                head.copy_from_slice(&bytes);
                Ok(bytes.len())
            }
            pb::api::on_io_reply::Kind::Error(err) => Err(err.into()),
        }
    }
}

impl Write for PosixIoProxy {
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
        let request = pb::api::ServerReply {
            kind: Some(pb::api::server_reply::Kind::Ok(pb::api::ClientCallback {
                kind: Some(pb::api::client_callback::Kind::Io(pb::api::OnIoRequest {
                    kind: Some(pb::api::on_io_request::Kind::Posix(pb::api::PosixIo {
                        fd: self.fd,
                        cmd: Some(pb::api::PosixCmd {
                            kind: Some(pb::api::posix_cmd::Kind::Write(buf.into())),
                        }),
                    })),
                })),
            })),
        };

        tracing::trace!("tx: {request:?}");
        let reply: pb::api::OnIoReply = self.conn.send_recv(request).map_io_err()?;
        tracing::trace!("rx: {reply:?}");

        let kind = reply.kind.ok_or("Malformed message").map_io_err()?;
        match kind {
            pb::api::on_io_reply::Kind::Ok(_) => Ok(buf.len()),
            pb::api::on_io_reply::Kind::Error(err) => Err(err.into()),
        }
    }

    fn flush(&mut self) -> std::io::Result<()> {
        Ok(())
    }
}

#[derive(Clone)]
struct SliceIoProxy {
    conn: ConnectionWrapper,
}

impl SliceIoProxy {
    fn new(conn: ConnectionWrapper) -> Self {
        Self { conn }
    }
}

impl SliceIo for SliceIoProxy {
    fn handle_io(&mut self, syscall: &str, from_guest: Bytes) -> Result<Bytes> {
        let request = pb::api::ServerReply {
            kind: Some(pb::api::server_reply::Kind::Ok(pb::api::ClientCallback {
                kind: Some(pb::api::client_callback::Kind::Io(pb::api::OnIoRequest {
                    kind: Some(pb::api::on_io_request::Kind::Slice(pb::api::SliceIo {
                        name: syscall.to_string(),
                        from_guest: from_guest.into(),
                    })),
                })),
            })),
        };
        tracing::trace!("tx: {request:?}");
        let reply: pb::api::OnIoReply = self.conn.send_recv(request).map_io_err()?;
        tracing::trace!("rx: {reply:?}");

        let kind = reply.kind.ok_or("Malformed message").map_io_err()?;
        match kind {
            pb::api::on_io_reply::Kind::Ok(buf) => Ok(buf.into()),
            pb::api::on_io_reply::Kind::Error(err) => Err(err.into()),
        }
    }
}

struct TraceProxy {
    conn: ConnectionWrapper,
}

impl TraceProxy {
    fn new(conn: ConnectionWrapper) -> Self {
        Self { conn }
    }
}

impl TraceCallback for TraceProxy {
    fn trace_callback(&mut self, event: TraceEvent) -> Result<()> {
        let Ok(event) = event.clone().try_into() else {
            tracing::trace!("ignoring unknown event {event:?}");
            return Ok(());
        };

        let request = pb::api::ServerReply {
            kind: Some(pb::api::server_reply::Kind::Ok(pb::api::ClientCallback {
                kind: Some(pb::api::client_callback::Kind::Io(pb::api::OnIoRequest {
                    kind: Some(pb::api::on_io_request::Kind::Trace(event)),
                })),
            })),
        };
        tracing::trace!("tx: {request:?}");
        let reply: pb::api::OnIoReply = self.conn.send_recv(request).map_io_err()?;
        tracing::trace!("rx: {reply:?}");

        let kind = reply.kind.ok_or("Malformed message").map_io_err()?;
        match kind {
            pb::api::on_io_reply::Kind::Ok(_) => Ok(()),
            pb::api::on_io_reply::Kind::Error(err) => Err(err.into()),
        }
    }
}

struct CoprocessorProxy {
    conn: ConnectionWrapper,
}

impl CoprocessorProxy {
    fn new(conn: ConnectionWrapper) -> Self {
        Self { conn }
    }
}

impl CoprocessorCallback for CoprocessorProxy {
    fn prove_zkr(&mut self, proof_request: ProveZkrRequest) -> Result<()> {
        let request = pb::api::ServerReply {
            kind: Some(pb::api::server_reply::Kind::Ok(pb::api::ClientCallback {
                kind: Some(pb::api::client_callback::Kind::Io(pb::api::OnIoRequest {
                    kind: Some(pb::api::on_io_request::Kind::Coprocessor(
                        pb::api::CoprocessorRequest {
                            kind: Some(pb::api::coprocessor_request::Kind::ProveZkr({
                                pb::api::ProveZkrRequest {
                                    claim_digest: Some(proof_request.claim_digest.into()),
                                    control_id: Some(proof_request.control_id.into()),
                                    input: proof_request.input,
                                    receipt_out: None,
                                }
                            })),
                        },
                    )),
                })),
            })),
        };
        tracing::trace!("tx: {request:?}");
        let reply: pb::api::OnIoReply = self.conn.send_recv(request).map_io_err()?;
        tracing::trace!("rx: {reply:?}");

        let kind = reply.kind.ok_or("Malformed message").map_io_err()?;
        match kind {
            pb::api::on_io_reply::Kind::Ok(_) => Ok(()),
            pb::api::on_io_reply::Kind::Error(err) => Err(err.into()),
        }
    }

    fn prove_keccak(&mut self, proof_request: ProveKeccakRequest) -> Result<()> {
        let input = keccak_input_to_bytes(&proof_request.input);
        let request = pb::api::ServerReply {
            kind: Some(pb::api::server_reply::Kind::Ok(pb::api::ClientCallback {
                kind: Some(pb::api::client_callback::Kind::Io(pb::api::OnIoRequest {
                    kind: Some(pb::api::on_io_request::Kind::Coprocessor(
                        pb::api::CoprocessorRequest {
                            kind: Some(pb::api::coprocessor_request::Kind::ProveKeccak({
                                pb::api::ProveKeccakRequest {
                                    claim_digest: Some(proof_request.claim_digest.into()),
                                    po2: proof_request.po2 as u32,
                                    control_root: Some(proof_request.control_root.into()),
                                    input,
                                    receipt_out: None,
                                }
                            })),
                        },
                    )),
                })),
            })),
        };
        tracing::trace!("tx: {request:?}");
        self.conn.send(request)?;

        let reply: pb::api::OnIoReply = self.conn.recv().map_io_err()?;
        tracing::trace!("rx: {reply:?}");

        let kind = reply.kind.ok_or("Malformed message").map_io_err()?;
        match kind {
            pb::api::on_io_reply::Kind::Ok(_) => Ok(()),
            pb::api::on_io_reply::Kind::Error(err) => Err(err.into()),
        }
    }
}

impl Server {
    /// Construct a new [Server] with the specified [Connector].
    pub fn new(connector: Box<dyn Connector>) -> Self {
        Self { connector }
    }

    /// Construct a new [Server] which will connect to the specified TCP/IP
    /// address.
    pub fn new_tcp<A: AsRef<str>>(addr: A) -> Self {
        let connector = TcpConnector::new(addr.as_ref());
        Self::new(Box::new(connector))
    }

    /// Start the [Server] and run until all requests are complete.
    pub fn run(&self) -> Result<()> {
        tracing::debug!("connect");
        let mut conn = self.connector.connect()?;

        let server_version = get_version().map_err(|err| anyhow!(err))?;

        let request: pb::api::HelloRequest = conn.recv()?;
        tracing::trace!("rx: {request:?}");

        let client_version: semver::Version = request
            .version
            .ok_or_else(|| malformed_err("HelloRequest.version"))?
            .try_into()
            .map_err(|err: semver::Error| anyhow!(err))?;

        #[cfg(not(feature = "r0vm-ver-compat"))]
        let check_client_func = check_client_version;
        #[cfg(feature = "r0vm-ver-compat")]
        let check_client_func = check_client_version_compat;

        if !check_client_func(&client_version, &server_version) {
            let msg = format!(
                "incompatible client version: {client_version}, server version: {server_version}"
            );
            tracing::debug!("{msg}");
            bail!(msg);
        }

        let reply = pb::api::HelloReply {
            kind: Some(pb::api::hello_reply::Kind::Ok(pb::api::HelloResult {
                version: Some(server_version.into()),
            })),
        };
        tracing::trace!("tx: {reply:?}");
        let request: pb::api::ServerRequest = conn.send_recv(reply)?;
        tracing::trace!("rx: {request:?}");

        match request
            .kind
            .ok_or_else(|| malformed_err("ServerRequest.kind"))?
        {
            pb::api::server_request::Kind::Prove(request) => self.on_prove(conn, request),
            pb::api::server_request::Kind::Execute(request) => self.on_execute(conn, request),
            pb::api::server_request::Kind::ProveSegment(request) => {
                self.on_prove_segment(conn, request)
            }
            pb::api::server_request::Kind::Lift(request) => self.on_lift(conn, request),
            pb::api::server_request::Kind::Join(request) => self.on_join(conn, request),
            pb::api::server_request::Kind::Resolve(request) => self.on_resolve(conn, request),
            pb::api::server_request::Kind::IdentityP254(request) => {
                self.on_identity_p254(conn, request)
            }
            pb::api::server_request::Kind::Compress(request) => self.on_compress(conn, request),
            pb::api::server_request::Kind::Verify(request) => self.on_verify(conn, request),
            pb::api::server_request::Kind::ProveZkr(request) => self.on_prove_zkr(conn, request),
            pb::api::server_request::Kind::ProveKeccak(request) => {
                self.on_prove_keccak(conn, request)
            }
            pb::api::server_request::Kind::Union(request) => self.on_union(conn, request),
        }
    }

    fn on_execute(
        &self,
        mut conn: ConnectionWrapper,
        request: pb::api::ExecuteRequest,
    ) -> Result<()> {
        fn inner(
            conn: &mut ConnectionWrapper,
            request: pb::api::ExecuteRequest,
        ) -> Result<pb::api::ServerReply> {
            let env_request = request
                .env
                .ok_or_else(|| malformed_err("ExecuteRequest.env"))?;
            let env = build_env(conn, &env_request)?;

            let binary = env_request
                .binary
                .ok_or_else(|| malformed_err("ExecuteRequest.binary"))?;

            let segments_out = request
                .segments_out
                .ok_or_else(|| malformed_err("ExecuteRequest.segments_out"))?;
            let bytes = binary.as_bytes()?;

            // TODO(povw): Add PoVW here
            let session = match AssetRequest::try_from(segments_out.clone())? {
                #[cfg(feature = "redis")]
                AssetRequest::Redis(params) => execute_redis(conn, env, bytes, params)?,
                _ => execute_default(conn, env, bytes, &segments_out)?,
            };

            let receipt_claim = session.claim()?;
            Ok(pb::api::ServerReply {
                kind: Some(pb::api::server_reply::Kind::Ok(pb::api::ClientCallback {
                    kind: Some(pb::api::client_callback::Kind::SessionDone(
                        pb::api::OnSessionDone {
                            session: Some(pb::api::SessionInfo {
                                segments: session.segments.len().try_into()?,
                                journal: session.journal.unwrap_or_default().bytes,
                                exit_code: Some(session.exit_code.try_into()?),
                                receipt_claim: Some(pb::api::Asset::from_bytes(
                                    &pb::api::AssetRequest {
                                        kind: Some(pb::api::asset_request::Kind::Inline(())),
                                    },
                                    pb::core::ReceiptClaim::try_from(receipt_claim)?
                                        .encode_to_vec()
                                        .into(),
                                    "session_info.claim",
                                )?),
                            }),
                        },
                    )),
                })),
            })
        }

        let msg = inner(&mut conn, request).unwrap_or_else(|err| pb::api::ServerReply {
            kind: Some(pb::api::server_reply::Kind::Error(pb::api::GenericError {
                reason: err.to_string(),
            })),
        });

        tracing::trace!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_prove(&self, mut conn: ConnectionWrapper, request: pb::api::ProveRequest) -> Result<()> {
        fn inner(
            conn: &mut ConnectionWrapper,
            request: pb::api::ProveRequest,
        ) -> Result<pb::api::ServerReply> {
            let env_request = request
                .env
                .ok_or_else(|| malformed_err("ProveRequest.env"))?;
            let env = build_env(conn, &env_request)?;

            let binary = env_request
                .binary
                .ok_or_else(|| malformed_err("ProveRequest.env_request.binary"))?;
            let bytes = binary.as_bytes()?;

            let opts: ProverOpts = request
                .opts
                .ok_or_else(|| malformed_err("ProveRequest.opts"))?
                .try_into()?;
            let prover = get_prover_server(&opts)?;
            let ctx = VerifierContext::default();
            let prove_info = prover.prove_with_ctx(env, &ctx, &bytes)?;

            let prove_info: pb::core::ProveInfo = prove_info.try_into()?;
            let prove_info_bytes = prove_info.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request
                    .receipt_out
                    .ok_or_else(|| malformed_err("ProveRequest.receipt_out"))?,
                prove_info_bytes.into(),
                "prove_info.zkp",
            )?;

            Ok(pb::api::ServerReply {
                kind: Some(pb::api::server_reply::Kind::Ok(pb::api::ClientCallback {
                    kind: Some(pb::api::client_callback::Kind::ProveDone(
                        pb::api::OnProveDone {
                            prove_info: Some(asset),
                        },
                    )),
                })),
            })
        }

        let msg = inner(&mut conn, request).unwrap_or_else(|err| pb::api::ServerReply {
            kind: Some(pb::api::server_reply::Kind::Error(pb::api::GenericError {
                reason: err.to_string(),
            })),
        });

        tracing::trace!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_prove_segment(
        &self,
        mut conn: ConnectionWrapper,
        request: pb::api::ProveSegmentRequest,
    ) -> Result<()> {
        fn inner(request: pb::api::ProveSegmentRequest) -> Result<pb::api::ProveSegmentReply> {
            let opts: ProverOpts = request
                .opts
                .ok_or_else(|| malformed_err("ProveSegmentRequest.opts"))?
                .try_into()?;
            let segment_bytes = request
                .segment
                .ok_or_else(|| malformed_err("ProveSegmentRequest.segment"))?
                .as_bytes()?;
            let segment: Segment = bincode::deserialize(&segment_bytes)?;

            let prover = get_prover_server(&opts)?;
            let ctx = VerifierContext::default();
            let receipt = prover.prove_segment(&ctx, &segment)?;

            let receipt_pb: pb::core::SegmentReceipt = receipt.try_into()?;
            let receipt_bytes = receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request
                    .receipt_out
                    .ok_or_else(|| malformed_err("ProveSegmentRequest.receipt_out"))?,
                receipt_bytes.into(),
                "receipt.zkp",
            )?;

            Ok(pb::api::ProveSegmentReply {
                kind: Some(pb::api::prove_segment_reply::Kind::Ok(
                    pb::api::ProveSegmentResult {
                        receipt: Some(asset),
                    },
                )),
            })
        }

        let msg = inner(request).unwrap_or_else(|err| pb::api::ProveSegmentReply {
            kind: Some(pb::api::prove_segment_reply::Kind::Error(
                pb::api::GenericError {
                    reason: err.to_string(),
                },
            )),
        });

        tracing::trace!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_prove_zkr(
        &self,
        mut conn: ConnectionWrapper,
        request: pb::api::ProveZkrRequest,
    ) -> Result<()> {
        fn inner(request: pb::api::ProveZkrRequest) -> Result<pb::api::ProveZkrReply> {
            let control_id = request
                .control_id
                .ok_or_else(|| malformed_err("ProveZkrRequest.control_id"))?
                .try_into()?;
            let receipt = prove_registered_zkr(&control_id, vec![control_id], &request.input)?;

            let receipt_pb: pb::core::SuccinctReceipt = receipt.try_into()?;
            let receipt_bytes = receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request
                    .receipt_out
                    .ok_or_else(|| malformed_err("ProveZkrRequest.receipt_out"))?,
                receipt_bytes.into(),
                "receipt.zkp",
            )?;

            Ok(pb::api::ProveZkrReply {
                kind: Some(pb::api::prove_zkr_reply::Kind::Ok(
                    pb::api::ProveZkrResult {
                        receipt: Some(asset),
                    },
                )),
            })
        }

        let msg = inner(request).unwrap_or_else(|err| pb::api::ProveZkrReply {
            kind: Some(pb::api::prove_zkr_reply::Kind::Error(
                pb::api::GenericError {
                    reason: err.to_string(),
                },
            )),
        });

        tracing::trace!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_prove_keccak(
        &self,
        mut conn: ConnectionWrapper,
        request: pb::api::ProveKeccakRequest,
    ) -> Result<()> {
        fn inner(request_pb: pb::api::ProveKeccakRequest) -> Result<pb::api::ProveKeccakReply> {
            let request: ProveKeccakRequest = request_pb.clone().try_into()?;
            let receipt = prove_keccak(&request)?;

            let receipt_pb: pb::core::SuccinctReceipt = receipt.try_into()?;
            let receipt_bytes = receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request_pb
                    .receipt_out
                    .ok_or_else(|| malformed_err("ProveKeccakRequest.receipt_out"))?,
                receipt_bytes.into(),
                "receipt.zkp",
            )?;

            Ok(pb::api::ProveKeccakReply {
                kind: Some(pb::api::prove_keccak_reply::Kind::Ok(
                    pb::api::ProveKeccakResult {
                        receipt: Some(asset),
                    },
                )),
            })
        }

        let msg = inner(request).unwrap_or_else(|err| pb::api::ProveKeccakReply {
            kind: Some(pb::api::prove_keccak_reply::Kind::Error(
                pb::api::GenericError {
                    reason: err.to_string(),
                },
            )),
        });

        tracing::trace!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_lift(&self, mut conn: ConnectionWrapper, request: pb::api::LiftRequest) -> Result<()> {
        fn inner(request: pb::api::LiftRequest) -> Result<pb::api::LiftReply> {
            let opts: ProverOpts = request
                .opts
                .ok_or_else(|| malformed_err("LiftRequest.opts"))?
                .try_into()?;
            let receipt_bytes = request
                .receipt
                .ok_or_else(|| malformed_err("LiftRequest.receipt"))?
                .as_bytes()?;
            let segment_receipt: SegmentReceipt = bincode::deserialize(&receipt_bytes)?;

            let prover = get_prover_server(&opts)?;
            let receipt = prover.lift(&segment_receipt)?;

            let succinct_receipt_pb: pb::core::SuccinctReceipt = receipt.try_into()?;
            let succinct_receipt_bytes = succinct_receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request
                    .receipt_out
                    .ok_or_else(|| malformed_err("LiftRequest.receipt_out"))?,
                succinct_receipt_bytes.into(),
                "receipt.zkp",
            )?;

            Ok(pb::api::LiftReply {
                kind: Some(pb::api::lift_reply::Kind::Ok(pb::api::LiftResult {
                    receipt: Some(asset),
                })),
            })
        }

        let msg = inner(request).unwrap_or_else(|err| pb::api::LiftReply {
            kind: Some(pb::api::lift_reply::Kind::Error(pb::api::GenericError {
                reason: err.to_string(),
            })),
        });

        // tracing::trace!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_join(&self, mut conn: ConnectionWrapper, request: pb::api::JoinRequest) -> Result<()> {
        fn inner(request: pb::api::JoinRequest) -> Result<pb::api::JoinReply> {
            let opts: ProverOpts = request
                .opts
                .ok_or_else(|| malformed_err("JoinRequest.opts"))?
                .try_into()?;
            let left_receipt_bytes = request
                .left_receipt
                .ok_or_else(|| malformed_err("JoinRequest.left_receipt"))?
                .as_bytes()?;
            let left_succinct_receipt: SuccinctReceipt<ReceiptClaim> =
                bincode::deserialize(&left_receipt_bytes)?;
            let right_receipt_bytes = request
                .right_receipt
                .ok_or_else(|| malformed_err("JoinRequest.right_receipt"))?
                .as_bytes()?;
            let right_succinct_receipt: SuccinctReceipt<ReceiptClaim> =
                bincode::deserialize(&right_receipt_bytes)?;

            let prover = get_prover_server(&opts)?;
            let receipt = prover.join(&left_succinct_receipt, &right_succinct_receipt)?;

            let succinct_receipt_pb: pb::core::SuccinctReceipt = receipt.try_into()?;
            let succinct_receipt_bytes = succinct_receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request
                    .receipt_out
                    .ok_or_else(|| malformed_err("JoinRequest.receipt_out"))?,
                succinct_receipt_bytes.into(),
                "receipt.zkp",
            )?;

            Ok(pb::api::JoinReply {
                kind: Some(pb::api::join_reply::Kind::Ok(pb::api::JoinResult {
                    receipt: Some(asset),
                })),
            })
        }

        let msg = inner(request).unwrap_or_else(|err| pb::api::JoinReply {
            kind: Some(pb::api::join_reply::Kind::Error(pb::api::GenericError {
                reason: err.to_string(),
            })),
        });

        // tracing::trace!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_union(&self, mut conn: ConnectionWrapper, request: pb::api::UnionRequest) -> Result<()> {
        fn inner(request: pb::api::UnionRequest) -> Result<pb::api::UnionReply> {
            let opts: ProverOpts = request
                .opts
                .ok_or_else(|| malformed_err("UnionRequest.opts"))?
                .try_into()?;
            let left_receipt_bytes = request
                .left_receipt
                .ok_or_else(|| malformed_err("UnionRequest.left_receipt"))?
                .as_bytes()?;
            let left_succinct_receipt: SuccinctReceipt<Unknown> =
                bincode::deserialize(&left_receipt_bytes)?;
            let right_receipt_bytes = request
                .right_receipt
                .ok_or_else(|| malformed_err("UnionRequest.right_receipt"))?
                .as_bytes()?;
            let right_succinct_receipt: SuccinctReceipt<Unknown> =
                bincode::deserialize(&right_receipt_bytes)?;

            let prover = get_prover_server(&opts)?;
            let receipt = prover.union(&left_succinct_receipt, &right_succinct_receipt)?;

            let succinct_receipt_pb: pb::core::SuccinctReceipt = receipt.try_into()?;
            let succinct_receipt_bytes = succinct_receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request
                    .receipt_out
                    .ok_or_else(|| malformed_err("UnionRequest.receipt_out"))?,
                succinct_receipt_bytes.into(),
                "receipt.zkp",
            )?;

            Ok(pb::api::UnionReply {
                kind: Some(pb::api::union_reply::Kind::Ok(pb::api::UnionResult {
                    receipt: Some(asset),
                })),
            })
        }

        let msg = inner(request).unwrap_or_else(|err| pb::api::UnionReply {
            kind: Some(pb::api::union_reply::Kind::Error(pb::api::GenericError {
                reason: err.to_string(),
            })),
        });

        // tracing::trace!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_resolve(
        &self,
        mut conn: ConnectionWrapper,
        request: pb::api::ResolveRequest,
    ) -> Result<()> {
        fn inner(request: pb::api::ResolveRequest) -> Result<pb::api::ResolveReply> {
            let opts: ProverOpts = request
                .opts
                .ok_or_else(|| malformed_err("ResolveRequest.opts"))?
                .try_into()?;
            let conditional_receipt_bytes = request
                .conditional_receipt
                .ok_or_else(|| malformed_err("ResolveRequest.conditional_receipt"))?
                .as_bytes()?;
            let conditional_succinct_receipt: SuccinctReceipt<ReceiptClaim> =
                bincode::deserialize(&conditional_receipt_bytes)?;
            let assumption_receipt_bytes = request
                .assumption_receipt
                .ok_or_else(|| malformed_err("ResolveRequest.assumption_receipt"))?
                .as_bytes()?;
            let assumption_succinct_receipt: SuccinctReceipt<ReceiptClaim> =
                bincode::deserialize(&assumption_receipt_bytes)?;

            let prover = get_prover_server(&opts)?;
            let receipt = prover.resolve(
                &conditional_succinct_receipt,
                &assumption_succinct_receipt.into_unknown(),
            )?;

            let succinct_receipt_pb: pb::core::SuccinctReceipt = receipt.try_into()?;
            let succinct_receipt_bytes = succinct_receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request
                    .receipt_out
                    .ok_or_else(|| malformed_err("ResolveRequest.receipt_out"))?,
                succinct_receipt_bytes.into(),
                "receipt.zkp",
            )?;

            Ok(pb::api::ResolveReply {
                kind: Some(pb::api::resolve_reply::Kind::Ok(pb::api::ResolveResult {
                    receipt: Some(asset),
                })),
            })
        }

        let msg = inner(request).unwrap_or_else(|err| pb::api::ResolveReply {
            kind: Some(pb::api::resolve_reply::Kind::Error(pb::api::GenericError {
                reason: err.to_string(),
            })),
        });

        // tracing::trace!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_identity_p254(
        &self,
        mut conn: ConnectionWrapper,
        request: pb::api::IdentityP254Request,
    ) -> Result<()> {
        fn inner(request: pb::api::IdentityP254Request) -> Result<pb::api::IdentityP254Reply> {
            let receipt_bytes = request
                .receipt
                .ok_or_else(|| malformed_err("IdentityP254Request.receipt"))?
                .as_bytes()?;
            let succinct_receipt: SuccinctReceipt<ReceiptClaim> =
                bincode::deserialize(&receipt_bytes)?;

            let receipt = identity_p254(&succinct_receipt)?;
            let succinct_receipt_pb: pb::core::SuccinctReceipt = receipt.try_into()?;
            let succinct_receipt_bytes = succinct_receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request
                    .receipt_out
                    .ok_or_else(|| malformed_err("IdentityP254Request.receipt_out"))?,
                succinct_receipt_bytes.into(),
                "receipt.zkp",
            )?;

            Ok(pb::api::IdentityP254Reply {
                kind: Some(pb::api::identity_p254_reply::Kind::Ok(
                    pb::api::IdentityP254Result {
                        receipt: Some(asset),
                    },
                )),
            })
        }

        let msg = inner(request).unwrap_or_else(|err| pb::api::IdentityP254Reply {
            kind: Some(pb::api::identity_p254_reply::Kind::Error(
                pb::api::GenericError {
                    reason: err.to_string(),
                },
            )),
        });

        // tracing::trace!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_compress(
        &self,
        mut conn: ConnectionWrapper,
        request: pb::api::CompressRequest,
    ) -> Result<()> {
        fn inner(request: pb::api::CompressRequest) -> Result<pb::api::CompressReply> {
            let opts: ProverOpts = request
                .opts
                .ok_or_else(|| malformed_err("CompressRequest.opts"))?
                .try_into()?;
            let receipt_bytes = request
                .receipt
                .ok_or_else(|| malformed_err("CompressRequest.receipt"))?
                .as_bytes()?;
            let receipt: Receipt = bincode::deserialize(&receipt_bytes)?;

            let prover = get_prover_server(&opts)?;
            let receipt = prover.compress(&opts, &receipt)?;

            let receipt_pb: pb::core::Receipt = receipt.try_into()?;
            let receipt_bytes = receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request
                    .receipt_out
                    .ok_or_else(|| malformed_err("CompressRequest.receipt_out"))?,
                receipt_bytes.into(),
                "receipt.zkp",
            )?;

            Ok(pb::api::CompressReply {
                kind: Some(pb::api::compress_reply::Kind::Ok(pb::api::CompressResult {
                    receipt: Some(asset),
                })),
            })
        }

        let msg = inner(request).unwrap_or_else(|err| pb::api::CompressReply {
            kind: Some(pb::api::compress_reply::Kind::Error(
                pb::api::GenericError {
                    reason: err.to_string(),
                },
            )),
        });

        // tracing::trace!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_verify(
        &self,
        mut conn: ConnectionWrapper,
        request: pb::api::VerifyRequest,
    ) -> Result<()> {
        fn inner(request: pb::api::VerifyRequest) -> Result<()> {
            let receipt_bytes = request
                .receipt
                .ok_or_else(|| malformed_err("VerifyRequest.receipt"))?
                .as_bytes()?;
            let receipt: Receipt =
                bincode::deserialize(&receipt_bytes).context("deserialize receipt")?;
            let image_id: Digest = request
                .image_id
                .ok_or_else(|| malformed_err("VerifyRequest.image_id"))?
                .try_into()?;
            receipt
                .verify(image_id)
                .map_err(|err| anyhow!("verify failed: {err}"))
        }

        let msg: pb::api::GenericReply = inner(request).into();
        // tracing::trace!("tx: {msg:?}");
        conn.send(msg)
    }
}

fn build_env<'a>(
    conn: &ConnectionWrapper,
    request: &pb::api::ExecutorEnv,
) -> Result<ExecutorEnv<'a>> {
    let mut env_builder = ExecutorEnv::builder();
    env_builder.env_vars(request.env_vars.clone());
    env_builder.args(&request.args);
    for fd in request.read_fds.iter() {
        let proxy = PosixIoProxy::new(*fd, conn.clone());
        let reader = BufReader::new(proxy);
        env_builder.read_fd(*fd, reader);
    }
    for fd in request.write_fds.iter() {
        let proxy = PosixIoProxy::new(*fd, conn.clone());
        env_builder.write_fd(*fd, proxy);
    }
    let proxy = SliceIoProxy::new(conn.clone());
    for name in request.slice_ios.iter() {
        env_builder.slice_io(name, proxy.clone());
    }
    if let Some(segment_limit_po2) = request.segment_limit_po2 {
        env_builder.segment_limit_po2(segment_limit_po2);
    }
    if let Some(keccak_max_po2) = request.keccak_max_po2 {
        env_builder.keccak_max_po2(keccak_max_po2)?;
    }
    env_builder.session_limit(request.session_limit);
    if request.trace_events.is_some() {
        let proxy = TraceProxy::new(conn.clone());
        env_builder.trace_callback(proxy);
    }
    if !request.pprof_out.is_empty() {
        env_builder.enable_profiler(Path::new(&request.pprof_out));
    }
    if !request.segment_path.is_empty() {
        env_builder.segment_path(Path::new(&request.segment_path));
    }
    if request.coprocessor {
        let proxy = CoprocessorProxy::new(conn.clone());
        env_builder.coprocessor_callback(proxy);
    }

    for assumption in request.assumptions.iter() {
        match assumption
            .kind
            .as_ref()
            .ok_or_else(|| malformed_err("Assumption.kind"))?
        {
            pb::api::assumption_receipt::Kind::Proven(asset) => {
                let receipt: InnerAssumptionReceipt =
                    pb::core::InnerReceipt::decode(asset.as_bytes()?)?.try_into()?;
                env_builder.add_assumption(receipt)
            }
            pb::api::assumption_receipt::Kind::Unresolved(asset) => {
                let assumption: Assumption =
                    pb::core::Assumption::decode(asset.as_bytes()?)?.try_into()?;
                env_builder.add_assumption(assumption)
            }
        };
    }
    env_builder.build()
}

trait IoOtherError<T> {
    fn map_io_err(self) -> Result<T, IoError>;
}

impl<T, E: Into<Box<dyn StdError + Send + Sync>>> IoOtherError<T> for Result<T, E> {
    fn map_io_err(self) -> Result<T, IoError> {
        self.map_err(|err| IoError::new(IoErrorKind::Other, err))
    }
}

impl From<pb::api::GenericError> for IoError {
    fn from(err: pb::api::GenericError) -> Self {
        IoError::new(IoErrorKind::Other, err.reason)
    }
}

impl pb::api::Asset {
    pub fn from_bytes<P: AsRef<Path>>(
        request: &pb::api::AssetRequest,
        bytes: Bytes,
        path: P,
    ) -> Result<Self> {
        match request
            .kind
            .as_ref()
            .ok_or_else(|| malformed_err("AssetRequest.kind"))?
        {
            pb::api::asset_request::Kind::Inline(()) => Ok(Self {
                kind: Some(pb::api::asset::Kind::Inline(bytes.into())),
            }),
            pb::api::asset_request::Kind::Path(base_path) => {
                let base_path = PathBuf::from(base_path);
                let path = base_path.join(path);
                std::fs::write(&path, bytes)?;
                Ok(Self {
                    kind: Some(pb::api::asset::Kind::Path(path_to_string(path)?)),
                })
            }
            pb::api::asset_request::Kind::Redis(_) => {
                tracing::error!("It's likely that r0vm is not installed with the redis feature");
                bail!("from_bytes not supported for redis")
            }
        }
    }
}

#[allow(dead_code)]
fn check_client_version(client: &semver::Version, server: &semver::Version) -> bool {
    if server.pre.is_empty() {
        let comparator = semver::Comparator {
            op: semver::Op::GreaterEq,
            major: server.major,
            minor: Some(server.minor),
            patch: None,
            pre: semver::Prerelease::EMPTY,
        };
        comparator.matches(client)
    } else {
        client == server
    }
}

#[allow(dead_code)]
fn check_client_version_compat(client: &semver::Version, server: &semver::Version) -> bool {
    client.major == server.major
}

#[cfg(feature = "redis")]
fn execute_redis(
    conn: &mut ConnectionWrapper,
    env: ExecutorEnv,
    bytes: Bytes,
    params: super::RedisParams,
) -> Result<Session> {
    use redis::{Client, Commands, ConnectionLike, SetExpiry, SetOptions};
    use std::{
        sync::{
            mpsc::{sync_channel, Receiver},
            Arc, Mutex,
        },
        thread::{spawn, JoinHandle},
    };

    let channel_size = match std::env::var("RISC0_REDIS_CHANNEL_SIZE") {
        Ok(val_str) => val_str.parse::<usize>().unwrap_or(100),
        Err(_) => 100,
    };
    let (sender, receiver) = sync_channel::<(String, Segment)>(channel_size);
    let opts = SetOptions::default().with_expiration(SetExpiry::EX(params.ttl));

    let redis_err = Arc::new(Mutex::new(None));
    let redis_err_clone = redis_err.clone();

    let conn = conn.clone();
    let join_handle: JoinHandle<()> = spawn(move || {
        fn inner(
            redis_url: String,
            receiver: &Receiver<(String, Segment)>,
            opts: SetOptions,
            mut conn: ConnectionWrapper,
        ) -> Result<()> {
            let client = Client::open(redis_url).context("Failed to open Redis connection")?;
            let mut connection = client
                .get_connection()
                .context("Failed to get redis connection")?;
            while let Ok((segment_key, segment)) = receiver.recv() {
                if !connection.is_open() {
                    connection = client
                        .get_connection()
                        .context("Failed to get redis connection")?;
                }
                let segment_bytes =
                    bincode::serialize(&segment).context("Failed to deserialize segment")?;
                match connection.set_options(segment_key.clone(), segment_bytes.clone(), opts) {
                    Ok(()) => (),
                    Err(err) => {
                        tracing::warn!(
                            "Failed to set redis key with TTL, trying again. Error: {err}"
                        );
                        connection = client
                            .get_connection()
                            .context("Failed to get redis connection")?;
                        let _: () = connection
                            .set_options(segment_key.clone(), segment_bytes, opts)
                            .context("Failed to set redis key with TTL again")?;
                    }
                };
                let asset = pb::api::Asset {
                    kind: Some(pb::api::asset::Kind::Redis(segment_key)),
                };
                send_segment_done_msg(&mut conn, segment, Some(asset))
                    .context("Failed to send segment_done msg")?;
            }
            Ok(())
        }

        if let Err(err) = inner(params.url, &receiver, opts, conn) {
            *redis_err_clone.lock().unwrap() = Some(err);
        }
    });

    let callback = |segment: Segment| -> Result<Box<dyn SegmentRef>> {
        let segment_key = format!("{}:{}", params.key, segment.index);
        if let Err(send_err) = sender.send((segment_key, segment)) {
            let mut redis_err_opt = redis_err.lock().unwrap();
            let redis_err_inner = redis_err_opt.take();
            return Err(match redis_err_inner {
                Some(redis_thread_err) => {
                    tracing::error!(
                        "Redis err: {redis_thread_err} root: {:?}",
                        redis_thread_err.root_cause()
                    );
                    anyhow!(redis_thread_err)
                }
                None => send_err.into(),
            });
        }
        Ok(Box::new(NullSegmentRef))
    };

    let session = ExecutorImpl::from_elf(env, &bytes)?.run_with_callback(callback);

    drop(sender);

    join_handle
        .join()
        .map_err(|err| anyhow!("redis task join failed: {err:?}"))?;

    session
}

fn execute_default(
    conn: &mut ConnectionWrapper,
    env: ExecutorEnv,
    bytes: Bytes,
    segments_out: &pb::api::AssetRequest,
) -> Result<Session> {
    let callback = |segment: Segment| -> Result<Box<dyn SegmentRef>> {
        let segment_bytes = bincode::serialize(&segment)?;
        let asset = pb::api::Asset::from_bytes(
            segments_out,
            segment_bytes.into(),
            format!("segment-{}", segment.index),
        )?;
        send_segment_done_msg(conn, segment, Some(asset))?;
        Ok(Box::new(NullSegmentRef))
    };

    ExecutorImpl::from_elf(env, &bytes)?.run_with_callback(callback)
}

fn send_segment_done_msg(
    conn: &mut ConnectionWrapper,
    segment: Segment,
    some_asset: Option<pb::api::Asset>,
) -> Result<()> {
    let segment = Some(pb::api::SegmentInfo {
        index: segment.index,
        po2: segment.po2() as u32,
        cycles: segment.user_cycles(),
        segment: some_asset,
    });

    let msg = pb::api::ServerReply {
        kind: Some(pb::api::server_reply::Kind::Ok(pb::api::ClientCallback {
            kind: Some(pb::api::client_callback::Kind::SegmentDone(
                pb::api::OnSegmentDone { segment },
            )),
        })),
    };

    tracing::trace!("tx: {msg:?}");
    let reply: pb::api::GenericReply = conn.send_recv(msg)?;
    tracing::trace!("rx: {reply:?}");

    let kind = reply
        .kind
        .ok_or_else(|| malformed_err("GenericReply.kind"))?;
    if let pb::api::generic_reply::Kind::Error(err) = kind {
        bail!(err)
    }
    Ok(())
}

#[cfg(test)]
mod tests {
    use semver::Version;

    use super::{check_client_version, check_client_version_compat};

    fn test_inner(check_func: fn(&Version, &Version) -> bool, client: &str, server: &str) -> bool {
        check_func(
            &Version::parse(client).unwrap(),
            &Version::parse(server).unwrap(),
        )
    }

    #[test]
    fn check_version() {
        fn test(client: &str, server: &str) -> bool {
            test_inner(check_client_version, client, server)
        }

        assert!(test("0.18.0", "0.18.0"));
        assert!(test("0.18.1", "0.18.0"));
        assert!(test("0.18.0", "0.18.1"));
        assert!(test("0.19.0", "0.18.0"));
        assert!(test("1.0.0", "0.18.0"));
        assert!(test("1.1.0", "1.0.0"));
        assert!(test("0.19.0-alpha.1", "0.19.0-alpha.1"));

        assert!(!test("0.19.0-alpha.1", "0.19.0-alpha.2"));
        assert!(!test("0.18.0", "0.19.0"));
        assert!(!test("0.18.0", "1.0.0"));
    }

    #[test]
    fn check_version_compat() {
        fn test(client: &str, server: &str) -> bool {
            test_inner(check_client_version_compat, client, server)
        }

        assert!(test("1.1.0", "1.1.0"));
        assert!(test("1.1.1", "1.1.1"));
        assert!(test("1.2.0", "1.1.1"));
        assert!(test("1.2.0-rc.1", "1.1.1"));

        assert!(!test("2.0.0", "1.1.1"));
    }
}
