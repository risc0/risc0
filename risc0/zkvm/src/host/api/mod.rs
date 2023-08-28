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

use crate::ProverOpts;

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
impl RootMessage for pb::ClientCallback {}
impl RootMessage for pb::GenericReply {}
impl RootMessage for pb::OnIoReply {}
impl RootMessage for pb::ProveSegmentReply {}

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

pub trait Connector {
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

fn void() -> pb::Void {
    pb::Void {}
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
                Ok(_) => pb::generic_reply::Kind::Ok(void()),
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
            lift: opts.lift,
        }
    }
}

impl From<ProverOpts> for pb::ProverOpts {
    fn from(opts: ProverOpts) -> Self {
        Self {
            hashfn: opts.hashfn,
            lift: opts.lift,
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
            asset: Some(pb::Asset {
                kind: Some(match binary.asset {
                    Asset::Inline(bytes) => pb::asset::Kind::Inline(bytes.into()),
                    Asset::Path(path) => {
                        let path_str = path.to_str().ok_or(anyhow!("path is not UTF-8"))?;
                        pb::asset::Kind::Path(path_str.to_string())
                    }
                }),
            }),
        })
    }
}

pub struct Binary {
    kind: BinaryKind,
    asset: Asset,
}

#[allow(unused)]
pub enum BinaryKind {
    Elf,
    Image,
}

#[allow(unused)]
pub enum Asset {
    Inline(Bytes),
    Path(PathBuf),
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
