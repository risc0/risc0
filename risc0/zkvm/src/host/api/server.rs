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
    error::Error as StdError,
    io::{BufReader, Error as IoError, ErrorKind as IoErrorKind, Read, Write},
    path::{Path, PathBuf},
};

use anyhow::{anyhow, bail, Result};
use bytes::Bytes;
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkvm_platform::{memory::MEM_SIZE, PAGE_SIZE};
use serde::{Deserialize, Serialize};

use super::{malformed_err, path_to_string, pb, ConnectionWrapper, Connector, TcpConnector};
use crate::{
    get_prover_server, host::client::slice_io::SliceIo, Executor, ExecutorEnv, ProverOpts, Segment,
    SegmentRef, VerifierContext,
};

/// A server implementation for handling requests by clients of the zkVM.
pub struct Server {
    connector: Box<dyn Connector>,
}

#[derive(Clone, Serialize, Deserialize)]
struct EmptySegmentRef;

#[typetag::serde]
impl SegmentRef for EmptySegmentRef {
    fn resolve(&self) -> Result<Segment> {
        Err(anyhow!("Segment resolution not supported"))
    }
}

impl pb::Binary {
    fn as_image(&self) -> Result<MemoryImage> {
        let bytes = self.asset.as_ref().ok_or(malformed_err())?.as_bytes()?;
        let image = match self.kind() {
            pb::binary::Kind::Unspecified => bail!(malformed_err()),
            pb::binary::Kind::Image => bincode::deserialize(&bytes)?,
            pb::binary::Kind::Elf => {
                let program = Program::load_elf(&bytes, MEM_SIZE as u32)?;
                MemoryImage::new(&program, PAGE_SIZE as u32)?
            }
        };
        Ok(image)
    }
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
        let request = pb::ServerReply {
            kind: Some(pb::server_reply::Kind::Ok(pb::ClientCallback {
                kind: Some(pb::client_callback::Kind::Io(pb::OnIoRequest {
                    kind: Some(pb::on_io_request::Kind::Posix(pb::PosixIo {
                        fd: self.fd,
                        cmd: Some(pb::PosixCmd {
                            kind: Some(pb::posix_cmd::Kind::Read(nread)),
                        }),
                    })),
                })),
            })),
        };

        log::debug!("tx: {request:?}");
        self.conn.send(request).map_io_err()?;

        let reply: pb::OnIoReply = self.conn.recv().map_io_err()?;
        log::debug!("rx: {reply:?}");

        let kind = reply.kind.ok_or("Malformed message").map_io_err()?;
        match kind {
            pb::on_io_reply::Kind::Ok(bytes) => {
                let (head, _) = to_guest.split_at_mut(bytes.len());
                head.copy_from_slice(&bytes);
                Ok(bytes.len())
            }
            pb::on_io_reply::Kind::Error(err) => Err(err.into()),
        }
    }
}

impl Write for PosixIoProxy {
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
        let request = pb::ServerReply {
            kind: Some(pb::server_reply::Kind::Ok(pb::ClientCallback {
                kind: Some(pb::client_callback::Kind::Io(pb::OnIoRequest {
                    kind: Some(pb::on_io_request::Kind::Posix(pb::PosixIo {
                        fd: self.fd,
                        cmd: Some(pb::PosixCmd {
                            kind: Some(pb::posix_cmd::Kind::Write(buf.into())),
                        }),
                    })),
                })),
            })),
        };

        log::debug!("tx: {request:?}");
        self.conn.send(request).map_io_err()?;

        let reply: pb::OnIoReply = self.conn.recv().map_io_err()?;
        log::debug!("rx: {reply:?}");

        let kind = reply.kind.ok_or("Malformed message").map_io_err()?;
        match kind {
            pb::on_io_reply::Kind::Ok(_) => Ok(buf.len()),
            pb::on_io_reply::Kind::Error(err) => Err(err.into()),
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
        let request = pb::ServerReply {
            kind: Some(pb::server_reply::Kind::Ok(pb::ClientCallback {
                kind: Some(pb::client_callback::Kind::Io(pb::OnIoRequest {
                    kind: Some(pb::on_io_request::Kind::Slice(pb::SliceIo {
                        name: syscall.to_string(),
                        from_guest: from_guest.into(),
                    })),
                })),
            })),
        };
        log::debug!("tx: {request:?}");
        self.conn.send(request)?;

        Ok(Bytes::new())
    }
}

impl Server {
    /// TODO
    pub fn new(connector: Box<dyn Connector>) -> Self {
        Self { connector }
    }

    /// TODO
    pub fn new_tcp<A: AsRef<str>>(addr: A) -> Self {
        let connector = TcpConnector::new(addr.as_ref());
        Self::new(Box::new(connector))
    }

    /// TODO
    pub fn run(&self) -> Result<()> {
        log::debug!("connect");
        let mut conn = self.connector.connect()?;

        let request: pb::HelloRequest = conn.recv()?;
        log::debug!("rx: {request:?}");
        // TODO: check version
        let reply = pb::HelloReply {
            kind: Some(pb::hello_reply::Kind::Ok(pb::HelloResult {
                version: Some(pb::Version { version: 0 }),
            })),
        };
        log::debug!("tx: {reply:?}");
        conn.send(reply)?;

        let request: pb::ServerRequest = conn.recv()?;
        log::debug!("rx: {request:?}");
        match request.kind.ok_or(malformed_err())? {
            pb::server_request::Kind::Prove(request) => {
                self.on_prove(conn, request)?;
            }
            pb::server_request::Kind::Execute(request) => {
                self.on_execute(conn, request)?;
            }
            pb::server_request::Kind::ProveSegment(request) => {
                self.on_prove_segment(conn, request)?
            }
            pb::server_request::Kind::Lift(_) => todo!(),
            pb::server_request::Kind::Join(_) => todo!(),
        };

        Ok(())
    }

    fn on_execute(&self, mut conn: ConnectionWrapper, request: pb::ExecuteRequest) -> Result<()> {
        let env_request = request.env.ok_or(malformed_err())?;
        let env = self.build_env(&conn, &env_request)?;

        let binary = env_request.binary.ok_or(malformed_err())?;
        let image = binary.as_image()?;
        let segments_out = request.segments_out.ok_or(malformed_err())?;

        let mut exec = Executor::new(env, image)?;
        let session = exec.run_with_callback(|segment| {
            let segment_bytes = bincode::serialize(&segment)?;
            let asset = pb::Asset::from_bytes(
                &segments_out,
                segment_bytes.into(),
                format!("segment-{}", segment.index),
            )?;
            let msg = pb::ServerReply {
                kind: Some(pb::server_reply::Kind::Ok(pb::ClientCallback {
                    kind: Some(pb::client_callback::Kind::SegmentDone(pb::OnSegmentDone {
                        segment: Some(pb::SegmentInfo {
                            index: segment.index,
                            po2: segment.po2.try_into()?,
                            insn_cycles: segment.insn_cycles.try_into()?,
                            segment: Some(asset),
                        }),
                    })),
                })),
            };
            log::debug!("tx: {msg:?}");
            conn.send(msg)?;

            let reply: pb::GenericReply = conn.recv()?;
            log::debug!("rx: {reply:?}");
            let kind = reply.kind.ok_or(malformed_err())?;
            if let pb::generic_reply::Kind::Error(err) = kind {
                bail!(err)
            }

            Ok(Box::new(EmptySegmentRef))
        })?;

        let msg = pb::ServerReply {
            kind: Some(pb::server_reply::Kind::Ok(pb::ClientCallback {
                kind: Some(pb::client_callback::Kind::SessionDone(pb::OnSessionDone {
                    session: Some(pb::SessionInfo {
                        segments: session.segments.len().try_into()?,
                        journal: session.journal,
                        exit_code: Some(session.exit_code.into()),
                    }),
                })),
            })),
        };
        log::debug!("tx: {msg:?}");
        conn.send(msg)?;

        Ok(())
    }

    fn on_prove(&self, mut conn: ConnectionWrapper, request: pb::ProveRequest) -> Result<()> {
        let env_request = request.env.ok_or(malformed_err())?;
        let env = self.build_env(&conn, &env_request)?;

        let binary = env_request.binary.ok_or(malformed_err())?;
        let image = binary.as_image()?;

        let opts: ProverOpts = request.opts.ok_or(malformed_err())?.into();
        let prover = get_prover_server(&opts)?;
        let ctx = VerifierContext::default();
        let receipt = prover.prove(env, &ctx, image)?;

        let receipt_bytes = bincode::serialize(&receipt)?;
        let asset = pb::Asset::from_bytes(
            &request.receipt_out.ok_or(malformed_err())?,
            receipt_bytes.into(),
            "receipt.zkp",
        )?;

        let msg = pb::ServerReply {
            kind: Some(pb::server_reply::Kind::Ok(pb::ClientCallback {
                kind: Some(pb::client_callback::Kind::ProveDone(pb::OnProveDone {
                    receipt: Some(asset),
                })),
            })),
        };
        log::debug!("tx: {msg:?}");
        conn.send(msg)?;

        Ok(())
    }

    fn on_prove_segment(
        &self,
        mut conn: ConnectionWrapper,
        request: pb::ProveSegmentRequest,
    ) -> Result<()> {
        let opts: ProverOpts = request.opts.ok_or(malformed_err())?.into();
        let segment_bytes = request.segment.ok_or(malformed_err())?.as_bytes()?;
        let segment: Segment = bincode::deserialize(&segment_bytes)?;

        let prover = get_prover_server(&opts)?;
        let ctx = VerifierContext::default();
        let receipt = prover.prove_segment(&ctx, &segment)?;

        let receipt_bytes = bincode::serialize(&receipt)?;
        let asset = pb::Asset::from_bytes(
            &request.receipt_out.ok_or(malformed_err())?,
            receipt_bytes.into(),
            "receipt.zkp",
        )?;

        let msg = pb::ProveSegmentReply {
            kind: Some(pb::prove_segment_reply::Kind::Ok(pb::ProveSegmentResult {
                receipt: Some(asset),
            })),
        };
        log::debug!("tx: {msg:?}");
        conn.send(msg)?;

        Ok(())
    }

    fn build_env(
        &self,
        conn: &ConnectionWrapper,
        request: &pb::ExecutorEnv,
    ) -> Result<ExecutorEnv> {
        let mut env_builder = ExecutorEnv::builder();
        env_builder.env_vars(request.env_vars.clone());
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
            env_builder.slice_io(&name, proxy.try_clone()?);
        }
        // TODO: add trace callback proxy
        env_builder.build()
    }
}

trait IoOtherError<T> {
    fn map_io_err(self) -> Result<T, IoError>;
}

impl<T, E: Into<Box<dyn StdError + Send + Sync>>> IoOtherError<T> for Result<T, E> {
    fn map_io_err(self) -> Result<T, IoError> {
        self.map_err(|err| IoError::new(IoErrorKind::Other, err))
    }
}

impl From<pb::GenericError> for IoError {
    fn from(err: pb::GenericError) -> Self {
        IoError::new(IoErrorKind::Other, err.reason)
    }
}

impl pb::Asset {
    pub fn from_bytes<P: AsRef<Path>>(
        request: &pb::AssetRequest,
        bytes: Bytes,
        path: P,
    ) -> Result<Self> {
        match request.kind.as_ref().ok_or(malformed_err())? {
            pb::asset_request::Kind::Inline(()) => Ok(Self {
                kind: Some(pb::asset::Kind::Inline(bytes.into())),
            }),
            pb::asset_request::Kind::Path(base_path) => {
                let base_path = PathBuf::from(base_path);
                let path = base_path.join(path);
                std::fs::write(&path, bytes)?;
                Ok(Self {
                    kind: Some(pb::asset::Kind::Path(path_to_string(path)?)),
                })
            }
        }
    }
}
