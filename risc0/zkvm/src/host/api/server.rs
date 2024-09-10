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

use std::{
    cell::RefCell,
    error::Error as StdError,
    io::{BufReader, Error as IoError, ErrorKind as IoErrorKind, Read, Write},
    path::{Path, PathBuf},
    rc::Rc,
};

use anyhow::{anyhow, bail, Result};
use bytes::Bytes;
use prost::Message;

use super::{malformed_err, path_to_string, pb, ConnectionWrapper, Connector, TcpConnector};
use crate::{
    get_prover_server, get_version,
    host::{
        client::{
            env::{CoprocessorCallback, ProveZkrRequest},
            slice_io::SliceIo,
        },
        server::session::NullSegmentRef,
    },
    prove_zkr, Assumption, ExecutorEnv, ExecutorImpl, InnerAssumptionReceipt, ProverOpts, Receipt,
    ReceiptClaim, Segment, SegmentReceipt, SuccinctReceipt, TraceCallback, TraceEvent,
    VerifierContext,
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
        self.conn.send(request).map_io_err()?;

        let reply: pb::api::OnIoReply = self.conn.recv().map_io_err()?;
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
        self.conn.send(request).map_io_err()?;

        let reply: pb::api::OnIoReply = self.conn.recv().map_io_err()?;
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

struct SliceIoProxy {
    conn: ConnectionWrapper,
}

impl SliceIoProxy {
    fn new(conn: ConnectionWrapper) -> Self {
        Self { conn }
    }

    fn try_clone(&self) -> Result<Self> {
        Ok(SliceIoProxy {
            conn: self.conn.try_clone()?,
        })
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
        self.conn.send(request)?;

        let reply: pb::api::OnIoReply = self.conn.recv().map_io_err()?;
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
        let request = pb::api::ServerReply {
            kind: Some(pb::api::server_reply::Kind::Ok(pb::api::ClientCallback {
                kind: Some(pb::api::client_callback::Kind::Io(pb::api::OnIoRequest {
                    kind: Some(pb::api::on_io_request::Kind::Trace(event.into())),
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
            .ok_or(malformed_err())?
            .try_into()
            .map_err(|err: semver::Error| anyhow!(err))?;
        if !check_client_version(&client_version, &server_version) {
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
        conn.send(reply)?;

        let request: pb::api::ServerRequest = conn.recv()?;
        tracing::trace!("rx: {request:?}");
        match request.kind.ok_or(malformed_err())? {
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
            pb::api::server_request::Kind::ProveZkr(request) => self.on_prove_zkr(conn, request),
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
            let env_request = request.env.ok_or(malformed_err())?;
            let env = build_env(conn, &env_request)?;

            let binary = env_request.binary.ok_or(malformed_err())?;

            let segments_out = request.segments_out.ok_or(malformed_err())?;
            let bytes = binary.as_bytes()?;
            let mut exec = ExecutorImpl::from_elf(env, &bytes)?;

            let session = exec.run_with_callback(|segment| {
                let segment_bytes = bincode::serialize(&segment)?;
                let asset = pb::api::Asset::from_bytes(
                    &segments_out,
                    segment_bytes.into(),
                    format!("segment-{}", segment.index),
                )?;
                let msg = pb::api::ServerReply {
                    kind: Some(pb::api::server_reply::Kind::Ok(pb::api::ClientCallback {
                        kind: Some(pb::api::client_callback::Kind::SegmentDone(
                            pb::api::OnSegmentDone {
                                segment: Some(pb::api::SegmentInfo {
                                    index: segment.index,
                                    po2: segment.inner.po2 as u32,
                                    cycles: segment.inner.insn_cycles as u32,
                                    segment: Some(asset),
                                }),
                            },
                        )),
                    })),
                };
                tracing::trace!("tx: {msg:?}");
                conn.send(msg)?;

                let reply: pb::api::GenericReply = conn.recv()?;
                tracing::trace!("rx: {reply:?}");
                let kind = reply.kind.ok_or(malformed_err())?;
                if let pb::api::generic_reply::Kind::Error(err) = kind {
                    bail!(err)
                }

                Ok(Box::new(NullSegmentRef))
            })?;

            Ok(pb::api::ServerReply {
                kind: Some(pb::api::server_reply::Kind::Ok(pb::api::ClientCallback {
                    kind: Some(pb::api::client_callback::Kind::SessionDone(
                        pb::api::OnSessionDone {
                            session: Some(pb::api::SessionInfo {
                                segments: session.segments.len().try_into()?,
                                journal: session.journal.unwrap_or_default().bytes,
                                exit_code: Some(session.exit_code.into()),
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
            let env_request = request.env.ok_or(malformed_err())?;
            let env = build_env(conn, &env_request)?;

            let binary = env_request.binary.ok_or(malformed_err())?;
            let bytes = binary.as_bytes()?;

            let opts: ProverOpts = request.opts.ok_or(malformed_err())?.try_into()?;
            let prover = get_prover_server(&opts)?;
            let ctx = VerifierContext::default();
            let prove_info = prover.prove_with_ctx(env, &ctx, &bytes)?;

            let prove_info: pb::core::ProveInfo = prove_info.into();
            let prove_info_bytes = prove_info.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request.receipt_out.ok_or(malformed_err())?,
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
            let opts: ProverOpts = request.opts.ok_or(malformed_err())?.try_into()?;
            let segment_bytes = request.segment.ok_or(malformed_err())?.as_bytes()?;
            let segment: Segment = bincode::deserialize(&segment_bytes)?;

            let prover = get_prover_server(&opts)?;
            let ctx = VerifierContext::default();
            let receipt = prover.prove_segment(&ctx, &segment)?;

            let receipt_pb: pb::core::SegmentReceipt = receipt.into();
            let receipt_bytes = receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request.receipt_out.ok_or(malformed_err())?,
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
            let control_id = request.control_id.ok_or(malformed_err())?.try_into()?;
            let receipt = prove_zkr(&control_id, &request.input)?;

            let receipt_pb: pb::core::SuccinctReceipt = receipt.into();
            let receipt_bytes = receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request.receipt_out.ok_or(malformed_err())?,
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

    fn on_lift(&self, mut conn: ConnectionWrapper, request: pb::api::LiftRequest) -> Result<()> {
        fn inner(request: pb::api::LiftRequest) -> Result<pb::api::LiftReply> {
            let opts: ProverOpts = request.opts.ok_or(malformed_err())?.try_into()?;
            let receipt_bytes = request.receipt.ok_or(malformed_err())?.as_bytes()?;
            let segment_receipt: SegmentReceipt = bincode::deserialize(&receipt_bytes)?;

            let prover = get_prover_server(&opts)?;
            let receipt = prover.lift(&segment_receipt)?;

            let succinct_receipt_pb: pb::core::SuccinctReceipt = receipt.into();
            let succinct_receipt_bytes = succinct_receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request.receipt_out.ok_or(malformed_err())?,
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

        tracing::debug!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_join(&self, mut conn: ConnectionWrapper, request: pb::api::JoinRequest) -> Result<()> {
        fn inner(request: pb::api::JoinRequest) -> Result<pb::api::JoinReply> {
            let opts: ProverOpts = request.opts.ok_or(malformed_err())?.try_into()?;
            let left_receipt_bytes = request.left_receipt.ok_or(malformed_err())?.as_bytes()?;
            let left_succinct_receipt: SuccinctReceipt<ReceiptClaim> =
                bincode::deserialize(&left_receipt_bytes)?;
            let right_receipt_bytes = request.right_receipt.ok_or(malformed_err())?.as_bytes()?;
            let right_succinct_receipt: SuccinctReceipt<ReceiptClaim> =
                bincode::deserialize(&right_receipt_bytes)?;

            let prover = get_prover_server(&opts)?;
            let receipt = prover.join(&left_succinct_receipt, &right_succinct_receipt)?;

            let succinct_receipt_pb: pb::core::SuccinctReceipt = receipt.into();
            let succinct_receipt_bytes = succinct_receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request.receipt_out.ok_or(malformed_err())?,
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

        tracing::debug!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_resolve(
        &self,
        mut conn: ConnectionWrapper,
        request: pb::api::ResolveRequest,
    ) -> Result<()> {
        fn inner(request: pb::api::ResolveRequest) -> Result<pb::api::ResolveReply> {
            let opts: ProverOpts = request.opts.ok_or(malformed_err())?.try_into()?;
            let conditional_receipt_bytes = request
                .conditional_receipt
                .ok_or(malformed_err())?
                .as_bytes()?;
            let conditional_succinct_receipt: SuccinctReceipt<ReceiptClaim> =
                bincode::deserialize(&conditional_receipt_bytes)?;
            let assumption_receipt_bytes = request
                .assumption_receipt
                .ok_or(malformed_err())?
                .as_bytes()?;
            let assumption_succinct_receipt: SuccinctReceipt<ReceiptClaim> =
                bincode::deserialize(&assumption_receipt_bytes)?;

            let prover = get_prover_server(&opts)?;
            let receipt = prover.resolve(
                &conditional_succinct_receipt,
                &assumption_succinct_receipt.into_unknown(),
            )?;

            let succinct_receipt_pb: pb::core::SuccinctReceipt = receipt.into();
            let succinct_receipt_bytes = succinct_receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request.receipt_out.ok_or(malformed_err())?,
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

        tracing::debug!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_identity_p254(
        &self,
        mut conn: ConnectionWrapper,
        request: pb::api::IdentityP254Request,
    ) -> Result<()> {
        fn inner(request: pb::api::IdentityP254Request) -> Result<pb::api::IdentityP254Reply> {
            let opts: ProverOpts = request.opts.ok_or(malformed_err())?.try_into()?;
            let receipt_bytes = request.receipt.ok_or(malformed_err())?.as_bytes()?;
            let succinct_receipt: SuccinctReceipt<ReceiptClaim> =
                bincode::deserialize(&receipt_bytes)?;

            let prover = get_prover_server(&opts)?;
            let receipt = prover.identity_p254(&succinct_receipt)?;

            let succinct_receipt_pb: pb::core::SuccinctReceipt = receipt.into();
            let succinct_receipt_bytes = succinct_receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request.receipt_out.ok_or(malformed_err())?,
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

        tracing::debug!("tx: {msg:?}");
        conn.send(msg)
    }

    fn on_compress(
        &self,
        mut conn: ConnectionWrapper,
        request: pb::api::CompressRequest,
    ) -> Result<()> {
        fn inner(request: pb::api::CompressRequest) -> Result<pb::api::CompressReply> {
            let opts: ProverOpts = request.opts.ok_or(malformed_err())?.try_into()?;
            let receipt_bytes = request.receipt.ok_or(malformed_err())?.as_bytes()?;
            let receipt: Receipt = bincode::deserialize(&receipt_bytes)?;

            let prover = get_prover_server(&opts)?;
            let receipt = prover.compress(&opts, &receipt)?;

            let receipt_pb: pb::core::Receipt = receipt.into();
            let receipt_bytes = receipt_pb.encode_to_vec();
            let asset = pb::api::Asset::from_bytes(
                &request.receipt_out.ok_or(malformed_err())?,
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

        tracing::debug!("tx: {msg:?}");
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
        let proxy = PosixIoProxy::new(*fd, conn.try_clone()?);
        let reader = BufReader::new(proxy);
        env_builder.read_fd(*fd, reader);
    }
    for fd in request.write_fds.iter() {
        let proxy = PosixIoProxy::new(*fd, conn.try_clone()?);
        env_builder.write_fd(*fd, proxy);
    }
    let proxy = SliceIoProxy::new(conn.try_clone()?);
    for name in request.slice_ios.iter() {
        env_builder.slice_io(name, proxy.try_clone()?);
    }
    if let Some(segment_limit_po2) = request.segment_limit_po2 {
        env_builder.segment_limit_po2(segment_limit_po2);
    }
    env_builder.session_limit(request.session_limit);
    if request.trace_events.is_some() {
        let proxy = TraceProxy::new(conn.try_clone()?);
        env_builder.trace_callback(proxy);
    }
    if !request.pprof_out.is_empty() {
        env_builder.enable_profiler(Path::new(&request.pprof_out));
    }
    if !request.segment_path.is_empty() {
        env_builder.segment_path(Path::new(&request.segment_path));
    }
    if request.coprocessor {
        let proxy = CoprocessorProxy::new(conn.try_clone()?);
        env_builder.coprocessor_callback(Rc::new(RefCell::new(proxy)));
    }

    for assumption in request.assumptions.iter() {
        match assumption.kind.as_ref().ok_or(malformed_err())? {
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
        match request.kind.as_ref().ok_or(malformed_err())? {
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
        }
    }
}

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

#[cfg(test)]
mod tests {
    use semver::Version;

    use super::check_client_version;

    #[test]
    fn check_version() {
        fn test(client: &str, server: &str) -> bool {
            check_client_version(
                &Version::parse(client).unwrap(),
                &Version::parse(server).unwrap(),
            )
        }

        assert!(test("0.18.0", "0.18.0"));
        assert!(test("0.18.1", "0.18.0"));
        assert!(test("0.18.0", "0.18.1"));
        assert!(test("0.19.0", "0.18.0"));
        assert!(test("1.0.0", "0.18.0"));
        assert!(test("1.1.0", "1.0.0"));

        assert!(!test("0.18.0", "0.19.0"));
        assert!(!test("0.18.0", "1.0.0"));

        assert!(test("0.19.0-alpha.1", "0.19.0-alpha.1"));
        assert!(!test("0.19.0-alpha.1", "0.19.0-alpha.2"));
    }
}
