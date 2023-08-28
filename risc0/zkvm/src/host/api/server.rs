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

use std::error::Error as StdError;
use std::io::{BufReader, Error as IoError, ErrorKind as IoErrorKind, Read, Write};

use anyhow::{anyhow, bail, Result};
use bytes::Bytes;
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkvm_platform::{memory::MEM_SIZE, PAGE_SIZE};
use serde::{Deserialize, Serialize};

use super::{malformed_err, pb, ConnectionWrapper, Connector, TcpConnector};
use crate::{host::client::slice_io::SliceIo, Executor, ExecutorEnv, Segment, SegmentRef};

/// TODO
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

impl pb::Asset {
    fn as_bytes(&self) -> Result<Bytes> {
        let bytes = match self.kind.clone().ok_or(malformed_err())? {
            pb::AssetKind::Inline(bytes) => bytes,
            pb::AssetKind::Path(path) => std::fs::read(path)?,
        };
        Ok(bytes.into())
    }

    fn as_image(&self, bin_type: pb::BinaryType) -> Result<MemoryImage> {
        let bytes = self.as_bytes()?;
        let image = match bin_type {
            pb::BinaryType::Unspecified => bail!(malformed_err()),
            pb::BinaryType::Image => bincode::deserialize(&bytes)?,
            pb::BinaryType::Elf => {
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

trait IoOtherError<T> {
    fn map_io_err(self) -> Result<T, IoError>;
}

impl<T, E: Into<Box<dyn StdError + Send + Sync>>> IoOtherError<T> for Result<T, E> {
    fn map_io_err(self) -> Result<T, IoError> {
        self.map_err(|err| IoError::new(IoErrorKind::Other, err))
    }
}

impl Read for PosixIoProxy {
    fn read(&mut self, to_guest: &mut [u8]) -> std::io::Result<usize> {
        let nread = to_guest.len().try_into().map_io_err()?;
        let request = pb::ClientRequest {
            kind: Some(pb::ClientRequestKind::Io(pb::ClientIoRequest {
                kind: Some(pb::ClientIoRequestKind::Posix(pb::PosixIo {
                    fd: self.fd,
                    cmd: Some(pb::PosixCmd {
                        kind: Some(pb::PosixCmdKind::Read(nread)),
                    }),
                })),
            })),
        };

        log::debug!("tx: {request:?}");
        self.conn.send(request).map_io_err()?;

        let reply: pb::ClientIoReply = self.conn.recv().map_io_err()?;
        log::debug!("rx: {reply:?}");

        let kind = reply.kind.ok_or("Malformed message").map_io_err()?;
        match kind {
            pb::ClientIoReplyKind::Ok(bytes) => {
                let (head, _) = to_guest.split_at_mut(bytes.len());
                head.copy_from_slice(&bytes);
                Ok(bytes.len())
            }
            pb::ClientIoReplyKind::Error(err) => Err(err.into()),
        }
    }
}

impl Write for PosixIoProxy {
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
        let request = pb::ClientRequest {
            kind: Some(pb::ClientRequestKind::Io(pb::ClientIoRequest {
                kind: Some(pb::ClientIoRequestKind::Posix(pb::PosixIo {
                    fd: self.fd,
                    cmd: Some(pb::PosixCmd {
                        kind: Some(pb::PosixCmdKind::Write(buf.into())),
                    }),
                })),
            })),
        };

        log::debug!("tx: {request:?}");
        self.conn.send(request).map_io_err()?;

        let reply: pb::ClientIoReply = self.conn.recv().map_io_err()?;
        log::debug!("rx: {reply:?}");

        let kind = reply.kind.ok_or("Malformed message").map_io_err()?;
        match kind {
            pb::ClientIoReplyKind::Ok(_) => Ok(buf.len()),
            pb::ClientIoReplyKind::Error(err) => Err(err.into()),
        }
    }

    fn flush(&mut self) -> std::io::Result<()> {
        Ok(())
    }
}

impl From<pb::GenericError> for IoError {
    fn from(err: pb::GenericError) -> Self {
        IoError::new(IoErrorKind::Other, err.reason)
    }
}

struct SliceIoProxy {
    conn: ConnectionWrapper,
}

impl SliceIoProxy {
    fn try_clone(&self) -> Result<Self> {
        Ok(SliceIoProxy {
            conn: self.conn.try_clone()?,
        })
    }
}

impl SliceIo for SliceIoProxy {
    fn handle_io(&mut self, syscall: &str, from_guest: Bytes) -> Result<Bytes> {
        let request = pb::ClientRequest {
            kind: Some(pb::ClientRequestKind::Io(pb::ClientIoRequest {
                kind: Some(pb::ClientIoRequestKind::Slice(pb::SliceIo {
                    name: syscall.to_string(),
                    from_guest: from_guest.into(),
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
            kind: Some(pb::HelloReplyKind::Version(0)),
        };
        log::debug!("tx: {reply:?}");
        conn.send(reply)?;

        let request: pb::ServerRequest = conn.recv()?;
        log::debug!("rx: {request:?}");
        match request.kind.ok_or(malformed_err())? {
            pb::ServerRequestKind::Execute(request) => {
                self.on_execute(conn, request)?;
            }
            pb::ServerRequestKind::Prove(_request) => {
                // self.on_prove(conn, request)?;
                todo!()
            }
        };

        Ok(())
    }

    fn on_execute(
        &self,
        mut conn: ConnectionWrapper,
        request: pb::ServerExecuteRequest,
    ) -> Result<()> {
        let request = request.execute.ok_or(malformed_err())?;
        let binary = request.binary.ok_or(malformed_err())?;
        let asset = binary.asset.as_ref().ok_or(malformed_err())?;
        let bin_type = binary.kind();
        let image = asset.as_image(bin_type)?;
        let segments = request.segments.ok_or(malformed_err())?;
        let work_dir = tempfile::tempdir()?;

        let mut env_builder = ExecutorEnv::builder();
        env_builder.env_vars(request.env_vars.clone());
        for fd in request.read_fds.iter() {
            let proxy = PosixIoProxy {
                fd: *fd,
                conn: conn.try_clone()?,
            };
            let reader = BufReader::new(proxy);
            env_builder.read_fd(*fd, reader);
        }
        for fd in request.write_fds.iter() {
            let proxy = PosixIoProxy {
                fd: *fd,
                conn: conn.try_clone()?,
            };
            env_builder.write_fd(*fd, proxy);
        }
        let proxy = SliceIoProxy {
            conn: conn.try_clone()?,
        };
        for name in request.slice_ios.iter() {
            env_builder.slice_io(&name, proxy.try_clone()?);
        }
        let env = env_builder.build()?;

        let mut exec = Executor::new(env, image)?;
        let session = exec.run_with_callback(|segment| {
            let segment_bytes = bincode::serialize(&segment)?;

            let asset = match segments.kind() {
                pb::AssetRequestKind::Unspecified => bail!(malformed_err()),
                pb::AssetRequestKind::Inline => pb::Asset {
                    kind: Some(pb::AssetKind::Inline(segment_bytes)),
                },
                pb::AssetRequestKind::Path => {
                    let segment_path = work_dir.path().join(format!("segment-{}", segment.index));
                    std::fs::write(&segment_path, segment_bytes)?;
                    let segment_path_str = segment_path
                        .to_str()
                        .ok_or(anyhow!("segment path is not UTF-8"))?;
                    pb::Asset {
                        kind: Some(pb::AssetKind::Path(segment_path_str.to_string())),
                    }
                }
            };

            let msg = pb::ClientRequest {
                kind: Some(pb::ClientRequestKind::SegmentDone(
                    pb::ClientSegmentDoneRequest {
                        segment: Some(pb::SegmentInfo {
                            index: segment.index,
                            po2: segment.po2.try_into()?,
                            insn_cycles: segment.insn_cycles.try_into()?,
                            segment: Some(asset),
                        }),
                    },
                )),
            };
            log::debug!("tx: {msg:?}");
            conn.send(msg)?;

            let reply: pb::GenericReply = conn.recv()?;
            log::debug!("rx: {reply:?}");
            let kind = reply.kind.ok_or(malformed_err())?;
            if let pb::GenericReplyKind::Error(err) = kind {
                bail!(err)
            }

            Ok(Box::new(EmptySegmentRef))
        })?;

        let msg = pb::ClientRequest {
            kind: Some(pb::ClientRequestKind::SessionDone(
                pb::ClientSessionDoneRequest {
                    session: Some(pb::SessionInfo {
                        segments: session.segments.len().try_into()?,
                        journal: session.journal,
                        exit_code: Some(pb::ExitCode {
                            kind: Some(pb::ExitCodeKind::Halted(0)), // TODO
                        }),
                    }),
                },
            )),
        };
        log::debug!("tx: {msg:?}");
        conn.send(msg)?;

        Ok(())
    }

    // fn on_prove(&self, _channel: Channel, _request: ServerProveRequest) -> Result<()> {
    //     todo!()
    // }

    // fn on_prove_segment<R: Read, W: Write>(
    //     &self,
    //     reader: R,
    //     writer: W,
    //     request: ApiServerProveSegmentRequest,
    // ) -> Result<()> {
    //     todo!()
    // }
}
