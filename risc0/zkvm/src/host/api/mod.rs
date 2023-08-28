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

use core::{sync::atomic::Ordering, time::Duration};
use std::{
    io::{Read, Write},
    net::{TcpListener, TcpStream},
    path::{Path, PathBuf},
    process::{Child, Command},
    sync::Arc,
    sync::{atomic::AtomicBool, mpsc::channel},
    thread,
};

use anyhow::{anyhow, Result};
use bytes::{Buf, BufMut};
use prost::Message;

mod pb {
    pub use crate::host::protos::api::*;
    pub use crate::host::protos::api::{
        asset::Kind as AssetKind, asset_request::Kind as AssetRequestKind, binary::BinaryType,
        client_io_reply::Kind as ClientIoReplyKind, client_io_request::Kind as ClientIoRequestKind,
        client_request::Kind as ClientRequestKind, exit_code::Kind as ExitCodeKind,
        generic_reply::Kind as GenericReplyKind, hello_reply::Kind as HelloReplyKind,
        posix_cmd::Kind as PosixCmdKind, server_request::Kind as ServerRequestKind,
    };
}

pub trait Connection {
    fn stream(&self) -> &TcpStream;
    fn close(&mut self) -> Result<i32>;
    fn try_clone(&self) -> Result<Box<dyn Connection>>;
}

pub struct ConnectionWrapper {
    inner: Box<dyn Connection>,
    buf: Vec<u8>,
}

impl ConnectionWrapper {
    fn new(inner: Box<dyn Connection>) -> Self {
        Self {
            inner,
            buf: Vec::new(),
        }
    }

    fn send<T: Message>(&mut self, msg: T) -> Result<()> {
        let len = msg.encoded_len();
        self.buf.clear();
        self.buf.put_u32_le(len as u32);
        msg.encode(&mut self.buf)?;
        Ok(self.inner.stream().write_all(&self.buf)?)
    }

    fn recv<T: Default + Message>(&mut self) -> Result<T> {
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

        let stream = rx.recv_timeout(Duration::from_secs(3));
        let stream = stream.map_err(|_| {
            shutdown.store(true, Ordering::Relaxed);
            let _ = TcpStream::connect(addr);
            handle.join().unwrap();
            anyhow!("Fail")
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
