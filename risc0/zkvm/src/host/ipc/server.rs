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

use std::io::{stdin, stdout, BufReader, Error as IoError, ErrorKind as IoErrorKind, Read, Write};

use anyhow::{anyhow, bail, Result};
use bytes::Bytes;
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkvm_platform::{memory::MEM_SIZE, PAGE_SIZE};
use serde::{Deserialize, Serialize};

use super::{malformed_err, Channel};
use crate::{
    host::{
        client::slice_io::SliceIo,
        protos::ipc::{
            asset::Kind as AssetKind, binary::BinaryType,
            client_io_reply::Kind as ClientIoReplyKind, generic_reply::Kind as GenericReplyKind,
            server_request::Kind as ServerRequestKind, Asset, ClientIoReply, ClientIoRequest,
            ClientSegmentDoneRequest, ClientSessionDoneRequest, ExitCode, GenericReply, HelloReply,
            PosixCmd, PosixIo, SegmentInfo, ServerExecuteRequest, ServerProveRequest,
            ServerRequest, SessionInfo, Void,
        },
    },
    Executor, ExecutorEnv, Segment, SegmentRef,
};

/// TODO
pub struct IpcServer;

#[derive(Clone, Serialize, Deserialize)]
struct IpcSegmentRef;

#[typetag::serde]
impl SegmentRef for IpcSegmentRef {
    fn resolve(&self) -> Result<Segment> {
        Err(anyhow!("Segment resolution not supported"))
    }
}

impl Asset {
    fn as_bytes(&self) -> Result<Bytes> {
        let bytes = match self.kind.clone().ok_or(malformed_err())? {
            AssetKind::Inline(bytes) => bytes,
            AssetKind::Path(path) => std::fs::read(path)?,
        };
        Ok(bytes.into())
    }

    fn as_image(&self, bin_type: BinaryType) -> Result<MemoryImage> {
        let bytes = self.as_bytes()?;
        let image = match bin_type {
            BinaryType::UNSPECIFIED => bail!(malformed_err()),
            BinaryType::IMAGE => bincode::deserialize(&bytes)?,
            BinaryType::ELF => {
                let program = Program::load_elf(&bytes, MEM_SIZE as u32)?;
                MemoryImage::new(&program, PAGE_SIZE as u32)?
            }
        };
        Ok(image)
    }
}

struct PosixIoProxy<'a> {
    fd: u32,
    channel: Channel<'a>,
}

impl<'a> Read for PosixIoProxy<'a> {
    fn read(&mut self, buf: &mut [u8]) -> std::io::Result<usize> {
        let mut cmd = PosixCmd::new();
        cmd.set_read(Void::default());

        let mut posix_io = PosixIo::new();
        posix_io.fd = self.fd;
        posix_io.cmd = Some(cmd).into();

        let mut request = ClientIoRequest::new();
        request.set_posix(posix_io);

        self.channel
            .send(request)
            .map_err(|err| IoError::new(IoErrorKind::Other, err.to_string()))?;

        let reply: ClientIoReply = self
            .channel
            .recv()
            .map_err(|err| IoError::new(IoErrorKind::Other, err.to_string()))?;

        let kind = reply
            .kind
            .ok_or(IoError::new(IoErrorKind::Other, "Malformed message"))?;

        match kind {
            ClientIoReplyKind::Ok(bytes) => {
                buf.copy_from_slice(&bytes);
                Ok(bytes.len())
            }
            ClientIoReplyKind::Error(err) => Err(IoError::new(IoErrorKind::Other, err)),
        }
    }
}

impl<'a> Write for PosixIoProxy<'a> {
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
        let mut cmd = PosixCmd::new();
        cmd.set_write(buf.into());

        let mut posix_io = PosixIo::new();
        posix_io.fd = self.fd;
        posix_io.cmd = Some(cmd).into();

        let mut request = ClientIoRequest::new();
        request.set_posix(posix_io);

        self.channel
            .send(request)
            .map_err(|err| IoError::new(IoErrorKind::Other, err.to_string()))?;

        let reply: ClientIoReply = self
            .channel
            .recv()
            .map_err(|err| IoError::new(IoErrorKind::Other, err.to_string()))?;

        let kind = reply
            .kind
            .ok_or(IoError::new(IoErrorKind::Other, "Malformed message"))?;

        match kind {
            ClientIoReplyKind::Ok(_) => Ok(buf.len()),
            ClientIoReplyKind::Error(err) => Err(IoError::new(IoErrorKind::Other, err)),
        }
    }

    fn flush(&mut self) -> std::io::Result<()> {
        Ok(())
    }
}

#[derive(Clone)]
struct SliceIoProxy<'a> {
    channel: Channel<'a>,
}

impl<'a> SliceIo for SliceIoProxy<'a> {
    fn handle_io(&mut self, _syscall: &str, _from_guest: Bytes) -> Result<Bytes> {
        let request = ClientIoRequest::new();
        self.channel
            .send(request)
            .map_err(|err| IoError::new(IoErrorKind::Other, err.to_string()))?;

        Ok(Bytes::new())
    }
}

impl IpcServer {
    /// TODO
    pub fn run(&self) -> Result<()> {
        let mut channel = Channel::new(stdin(), stdout());

        let request: ServerRequest = channel.recv()?;
        match request.kind.ok_or(malformed_err())? {
            ServerRequestKind::Hello(_version) => {
                let mut msg = HelloReply::new();
                msg.set_version(0);
                channel.send(msg)?;
            }
            ServerRequestKind::Execute(request) => {
                self.on_execute(channel, request)?;
            }
            ServerRequestKind::Prove(request) => {
                self.on_prove(channel, request)?;
            }
        };

        Ok(())
    }

    fn on_execute(&self, mut channel: Channel, request: ServerExecuteRequest) -> Result<()> {
        let request = request.execute.as_ref().ok_or(malformed_err())?;
        let asset = request.binary.asset.as_ref().ok_or(malformed_err())?;
        let bin_type = request
            .binary
            .kind
            .enum_value()
            .map_err(|x| anyhow!("Unknown BinaryType: {x}"))?;
        let image = asset.as_image(bin_type)?;

        let mut env_builder = ExecutorEnv::builder();
        env_builder.env_vars(request.env_vars.clone());
        for (fd, _) in request.read_fds.iter() {
            let proxy = PosixIoProxy {
                fd: *fd,
                channel: channel.clone(),
            };
            let reader = BufReader::new(proxy);
            env_builder.read_fd(*fd, reader);
        }
        for (fd, _) in request.write_fds.iter() {
            let proxy = PosixIoProxy {
                fd: *fd,
                channel: channel.clone(),
            };
            env_builder.write_fd(*fd, proxy);
        }
        let proxy = SliceIoProxy {
            channel: channel.clone(),
        };
        for (name, _) in request.slice_ios.iter() {
            env_builder.slice_io(&name, proxy.clone());
        }
        let env = env_builder.build()?;

        let mut exec = Executor::new(env, image)?;
        let session = exec.run_with_callback(|segment| {
            let segment_bytes = bincode::serialize(&segment)?;

            let mut segment_asset = Asset::new();
            segment_asset.set_inline(segment_bytes);

            let mut segment_info = SegmentInfo::new();
            segment_info.index = segment.index;
            segment_info.po2 = segment.po2.try_into()?;
            segment_info.insn_cycles = segment.insn_cycles.try_into()?;
            segment_info.segment = Some(segment_asset).into();

            let mut client_request = ClientSegmentDoneRequest::new();
            client_request.segment = Some(segment_info).into();

            channel.send(client_request)?;

            let reply: GenericReply = channel.recv()?;
            let kind = reply.kind.ok_or(malformed_err())?;
            if let GenericReplyKind::Error(reason) = kind {
                bail!(reason)
            }

            Ok(Box::new(IpcSegmentRef))
        })?;

        let mut exit_code = ExitCode::new();
        exit_code.set_halted(0);

        let mut session_info = SessionInfo::new();
        session_info.segments = session.segments.len().try_into()?;
        session_info.journal = session.journal;
        session_info.exit_code = Some(exit_code).into();

        let mut client_request = ClientSessionDoneRequest::new();
        client_request.session = Some(session_info).into();

        channel.send(client_request)?;

        Ok(())
    }

    fn on_prove(&self, _channel: Channel, _request: ServerProveRequest) -> Result<()> {
        todo!()
    }

    // fn on_prove_segment<R: Read, W: Write>(
    //     &self,
    //     reader: R,
    //     writer: W,
    //     request: IpcServerProveSegmentRequest,
    // ) -> Result<()> {
    //     todo!()
    // }
}
