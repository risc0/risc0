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

pub(crate) mod client;
pub(crate) mod server;
#[cfg(test)]
mod tests;

use std::{
    io::{Read, Write},
    net::{TcpListener, TcpStream},
    path::{Path, PathBuf},
    process::{Child, Command},
    sync::Arc,
    sync::{
        atomic::{AtomicBool, Ordering},
        mpsc::channel,
    },
    thread,
    time::Duration,
};

use anyhow::{anyhow, Result};
use bytes::{Buf, BufMut, Bytes};
use prost::Message;
use risc0_binfmt::MemoryImage;

use crate::{ExitCode, ProverOpts, TraceEvent};

mod pb {
    pub use crate::host::protos::api::*;
}

const CONNECT_TIMEOUT: Duration = Duration::from_secs(10);

trait RootMessage: Message {}

pub trait Connection {
    fn stream(&self) -> &TcpStream;
    fn close(&mut self) -> Result<i32>;
    fn try_clone(&self) -> Result<Box<dyn Connection>>;
}

pub struct ConnectionWrapper {
    inner: Box<dyn Connection>,
    buf: Vec<u8>,
}

impl RootMessage for pb::HelloRequest {}
impl RootMessage for pb::HelloReply {}
impl RootMessage for pb::ServerRequest {}
impl RootMessage for pb::ServerReply {}
impl RootMessage for pb::GenericReply {}
impl RootMessage for pb::OnIoReply {}
impl RootMessage for pb::ProveSegmentReply {}
impl RootMessage for pb::LiftRequest {}
impl RootMessage for pb::LiftReply {}
impl RootMessage for pb::JoinRequest {}
impl RootMessage for pb::JoinReply {}

impl ConnectionWrapper {
    fn new(inner: Box<dyn Connection>) -> Self {
        Self {
            inner,
            buf: Vec::new(),
        }
    }

    fn send<T: RootMessage>(&mut self, msg: T) -> Result<()> {
        let len = msg.encoded_len();
        self.buf.clear();
        self.buf.put_u32_le(len as u32);
        msg.encode(&mut self.buf)?;
        Ok(self.inner.stream().write_all(&self.buf)?)
    }

    fn recv<T: Default + RootMessage>(&mut self) -> Result<T> {
        let mut stream = self.inner.stream();
        self.buf.resize(4, 0);
        stream.read_exact(&mut self.buf)?;
        let len = self.buf.as_slice().get_u32_le() as usize;
        self.buf.resize(len, 0);
        stream.read_exact(&mut self.buf)?;
        Ok(T::decode(self.buf.as_slice())?)
    }

    fn close(&mut self) -> Result<i32> {
        self.inner.close()
    }

    fn try_clone(&self) -> Result<Self> {
        Ok(Self::new(self.inner.try_clone()?))
    }
}

/// Connects a zkVM client and server
pub trait Connector {
    /// Create a client-server connection
    fn connect(&self) -> Result<ConnectionWrapper>;
}

struct ParentProcessConnector {
    server_path: PathBuf,
    listener: TcpListener,
}

impl ParentProcessConnector {
    pub fn new<P: AsRef<Path>>(server_path: P) -> Result<Self> {
        Ok(Self {
            server_path: server_path.as_ref().to_path_buf(),
            listener: TcpListener::bind("127.0.0.1:0")?,
        })
    }
}

impl Connector for ParentProcessConnector {
    fn connect(&self) -> Result<ConnectionWrapper> {
        let addr = self.listener.local_addr()?;
        let child = Command::new(&self.server_path)
            .arg("--port")
            .arg(addr.port().to_string())
            .spawn()?;

        let shutdown = Arc::new(AtomicBool::new(false));
        let server_shutdown = shutdown.clone();
        let (tx, rx) = channel();
        let listener = self.listener.try_clone()?;
        let handle = thread::spawn(move || {
            let stream = listener.accept();
            if server_shutdown.load(Ordering::Relaxed) {
                return;
            }
            if let Ok((stream, _addr)) = stream {
                tx.send(stream).unwrap();
            }
        });

        let stream = rx.recv_timeout(CONNECT_TIMEOUT);
        let stream = stream.map_err(|err| {
            shutdown.store(true, Ordering::Relaxed);
            let _ = TcpStream::connect(addr);
            handle.join().unwrap();
            err
        })?;

        Ok(ConnectionWrapper::new(Box::new(
            ParentProcessConnection::new(child, stream),
        )))
    }
}

struct TcpConnector {
    addr: String,
}

impl TcpConnector {
    pub fn new(addr: &str) -> Self {
        Self {
            addr: addr.to_string(),
        }
    }
}

impl Connector for TcpConnector {
    fn connect(&self) -> Result<ConnectionWrapper> {
        log::debug!("connect");
        let stream = TcpStream::connect(&self.addr)?;
        Ok(ConnectionWrapper::new(Box::new(TcpConnection::new(stream))))
    }
}

struct ParentProcessConnection {
    child: Child,
    stream: TcpStream,
}

struct TcpConnection {
    stream: TcpStream,
}

impl ParentProcessConnection {
    pub fn new(child: Child, stream: TcpStream) -> Self {
        Self { child, stream }
    }
}

impl Connection for ParentProcessConnection {
    fn stream(&self) -> &TcpStream {
        &self.stream
    }

    fn close(&mut self) -> Result<i32> {
        let status = self.child.wait()?;
        Ok(status.code().unwrap_or_default())
    }

    fn try_clone(&self) -> Result<Box<dyn Connection>> {
        unimplemented!()
    }
}

impl TcpConnection {
    pub fn new(stream: TcpStream) -> Self {
        Self { stream }
    }
}

impl Connection for TcpConnection {
    fn stream(&self) -> &TcpStream {
        &self.stream
    }

    fn close(&mut self) -> Result<i32> {
        Ok(0)
    }

    fn try_clone(&self) -> Result<Box<dyn Connection>> {
        Ok(Box::new(Self::new(self.stream.try_clone()?)))
    }
}

fn malformed_err() -> anyhow::Error {
    anyhow!("Malformed error")
}

impl pb::Asset {
    fn as_bytes(&self) -> Result<Bytes> {
        let bytes = match self.kind.clone().ok_or(malformed_err())? {
            pb::asset::Kind::Inline(bytes) => bytes,
            pb::asset::Kind::Path(path) => std::fs::read(path)?,
        };
        Ok(bytes.into())
    }
}

impl From<Result<(), anyhow::Error>> for pb::GenericReply {
    fn from(result: Result<(), anyhow::Error>) -> Self {
        Self {
            kind: Some(match result {
                Ok(_) => pb::generic_reply::Kind::Ok(()),
                Err(err) => pb::generic_reply::Kind::Error(err.into()),
            }),
        }
    }
}

impl From<anyhow::Error> for pb::GenericError {
    fn from(err: anyhow::Error) -> Self {
        Self {
            reason: err.to_string(),
        }
    }
}

impl From<pb::GenericError> for anyhow::Error {
    fn from(err: pb::GenericError) -> Self {
        anyhow::Error::msg(err.reason)
    }
}

impl From<pb::ProverOpts> for ProverOpts {
    fn from(opts: pb::ProverOpts) -> Self {
        Self {
            hashfn: opts.hashfn,
        }
    }
}

impl From<ProverOpts> for pb::ProverOpts {
    fn from(opts: ProverOpts) -> Self {
        Self {
            hashfn: opts.hashfn,
        }
    }
}

impl TryFrom<Binary> for pb::Binary {
    type Error = anyhow::Error;

    fn try_from(binary: Binary) -> Result<Self> {
        Ok(Self {
            kind: match binary.kind {
                BinaryKind::Elf => pb::binary::Kind::Elf,
                BinaryKind::Image => pb::binary::Kind::Image,
            } as i32,
            asset: Some(binary.asset.try_into()?),
        })
    }
}

pub struct Binary {
    kind: BinaryKind,
    asset: Asset,
}

pub enum BinaryKind {
    Elf,
    Image,
}

pub enum Asset {
    Inline(Bytes),
    Path(PathBuf),
}

pub enum AssetRequest {
    Inline,
    Path(PathBuf),
}

impl Binary {
    pub fn new_elf_inline(bytes: Bytes) -> Self {
        Self {
            kind: BinaryKind::Elf,
            asset: Asset::Inline(bytes),
        }
    }

    pub fn new_elf_path<P: AsRef<Path>>(path: P) -> Self {
        Self {
            kind: BinaryKind::Elf,
            asset: Asset::Path(path.as_ref().to_path_buf()),
        }
    }

    pub fn new_image_inline(bytes: Bytes) -> Self {
        Self {
            kind: BinaryKind::Image,
            asset: Asset::Inline(bytes),
        }
    }

    pub fn new_image_path<P: AsRef<Path>>(path: P) -> Self {
        Self {
            kind: BinaryKind::Image,
            asset: Asset::Path(path.as_ref().to_path_buf()),
        }
    }
}

impl TryFrom<MemoryImage> for Binary {
    type Error = anyhow::Error;

    fn try_from(image: MemoryImage) -> Result<Self> {
        let bytes = bincode::serialize(&image)?;
        Ok(Self {
            kind: BinaryKind::Image,
            asset: Asset::Inline(bytes.into()),
        })
    }
}

fn invalid_path() -> anyhow::Error {
    anyhow::Error::msg("Path must be UTF-8")
}

fn path_to_string<P: AsRef<Path>>(path: P) -> Result<String> {
    Ok(path.as_ref().to_str().ok_or(invalid_path())?.to_string())
}

impl TryFrom<AssetRequest> for pb::AssetRequest {
    type Error = anyhow::Error;

    fn try_from(value: AssetRequest) -> Result<Self> {
        Ok(Self {
            kind: Some(match value {
                AssetRequest::Inline => pb::asset_request::Kind::Inline(()),
                AssetRequest::Path(path) => pb::asset_request::Kind::Path(path_to_string(path)?),
            }),
        })
    }
}

impl TryFrom<Asset> for pb::Asset {
    type Error = anyhow::Error;

    fn try_from(value: Asset) -> Result<Self> {
        Ok(Self {
            kind: match value {
                Asset::Inline(bytes) => Some(pb::asset::Kind::Inline(bytes.into())),
                Asset::Path(path) => Some(pb::asset::Kind::Path(path_to_string(path)?)),
            },
        })
    }
}

impl TryFrom<pb::Asset> for Asset {
    type Error = anyhow::Error;

    fn try_from(value: pb::Asset) -> Result<Self> {
        Ok(match value.kind.ok_or(malformed_err())? {
            pb::asset::Kind::Inline(bytes) => Asset::Inline(bytes.into()),
            pb::asset::Kind::Path(path) => Asset::Path(PathBuf::from(path)),
        })
    }
}

impl TryFrom<pb::TraceEvent> for TraceEvent {
    type Error = anyhow::Error;

    fn try_from(event: pb::TraceEvent) -> Result<Self> {
        Ok(match event.kind.ok_or(malformed_err())? {
            pb::trace_event::Kind::InsnStart(event) => TraceEvent::InstructionStart {
                cycle: event.cycle,
                pc: event.pc,
            },
            pb::trace_event::Kind::RegisterSet(event) => TraceEvent::RegisterSet {
                idx: event.idx as usize,
                value: event.value,
            },
            pb::trace_event::Kind::MemorySet(event) => TraceEvent::MemorySet {
                addr: event.addr,
                value: event.value,
            },
        })
    }
}

impl From<ExitCode> for pb::ExitCode {
    fn from(value: ExitCode) -> Self {
        Self {
            kind: Some(match value {
                ExitCode::SystemSplit => pb::exit_code::Kind::SystemSplit(()),
                ExitCode::SessionLimit => pb::exit_code::Kind::SessionLimit(()),
                ExitCode::Paused(code) => pb::exit_code::Kind::Paused(code),
                ExitCode::Halted(code) => pb::exit_code::Kind::Halted(code),
            }),
        }
    }
}
