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

pub(crate) mod client;
pub(crate) mod convert;
#[cfg(feature = "prove")]
pub(crate) mod server;
#[cfg(test)]
#[cfg(feature = "prove")]
mod tests;

use std::{
    cell::RefCell,
    io::{Error as IoError, ErrorKind as IoErrorKind, Read, Write},
    net::{TcpListener, TcpStream},
    path::{Path, PathBuf},
    process::{Child, Command},
    sync::{
        Arc, Mutex,
        atomic::{AtomicBool, Ordering},
        mpsc::channel,
    },
    thread,
    time::Duration,
};

use anyhow::{Context, Result, anyhow, bail};
use bytes::{Buf, BufMut, Bytes};
use lazy_regex::regex_captures;
use prost::Message;
use semver::Version;
use serde::{Deserialize, Serialize};

use crate::{ExitCode, Journal, ReceiptClaim, get_version};

mod pb {
    pub(crate) mod api {
        pub use crate::host::protos::api::*;
    }
    pub(crate) mod base {
        pub use crate::host::protos::base::*;
    }
    pub(crate) mod core {
        pub use crate::host::protos::core::*;
    }
}

const CONNECT_TIMEOUT: Duration = Duration::from_secs(10);

trait RootMessage: Message {}

pub trait Connection {
    fn stream(&mut self) -> &mut TcpStream;
    fn close(&mut self) -> Result<i32>;
}

#[derive(Clone)]
pub struct ConnectionWrapper {
    inner: Arc<Mutex<dyn Connection + Send>>,
}

thread_local! {
    static LOCAL_BUF: RefCell<Vec<u8>> = const { RefCell::new(Vec::new()) };
}

impl RootMessage for pb::api::HelloRequest {}
impl RootMessage for pb::api::HelloReply {}
impl RootMessage for pb::api::ServerRequest {}
impl RootMessage for pb::api::ServerReply {}
impl RootMessage for pb::api::GenericReply {}
impl RootMessage for pb::api::OnIoReply {}
impl RootMessage for pb::api::ProveKeccakReply {}
impl RootMessage for pb::api::ProveSegmentReply {}
impl RootMessage for pb::api::ProveZkrReply {}
impl RootMessage for pb::api::LiftRequest {}
impl RootMessage for pb::api::LiftReply {}
impl RootMessage for pb::api::JoinRequest {}
impl RootMessage for pb::api::JoinReply {}
impl RootMessage for pb::api::ResolveRequest {}
impl RootMessage for pb::api::ResolveReply {}
impl RootMessage for pb::api::IdentityP254Request {}
impl RootMessage for pb::api::IdentityP254Reply {}
impl RootMessage for pb::api::CompressRequest {}
impl RootMessage for pb::api::CompressReply {}
impl RootMessage for pb::api::UnionRequest {}
impl RootMessage for pb::api::UnionReply {}

fn lock_err() -> IoError {
    IoError::new(IoErrorKind::WouldBlock, "Failed to lock connection mutex")
}

impl ConnectionWrapper {
    fn new(inner: Arc<Mutex<dyn Connection + Send>>) -> Self {
        Self { inner }
    }

    fn send<T: RootMessage>(&mut self, msg: T) -> Result<()> {
        let mut guard = self.inner.lock().map_err(|_| lock_err())?;
        self.inner_send(guard.stream(), msg)
    }

    fn recv<T: Default + RootMessage>(&mut self) -> Result<T> {
        let mut guard = self.inner.lock().map_err(|_| lock_err())?;
        self.inner_recv(guard.stream())
    }

    #[cfg(feature = "prove")]
    fn send_recv<S: RootMessage, R: Default + RootMessage>(&mut self, msg: S) -> Result<R> {
        let mut guard = self.inner.lock().map_err(|_| lock_err())?;
        let stream = guard.stream();
        self.inner_send(stream, msg)?;
        self.inner_recv(stream)
    }

    fn close(&mut self) -> Result<i32> {
        self.inner.lock().map_err(|_| lock_err())?.close()
    }

    fn inner_send<T: RootMessage>(&self, stream: &mut TcpStream, msg: T) -> Result<()> {
        let len = msg.encoded_len();
        LOCAL_BUF.with_borrow_mut(|buf| {
            buf.clear();
            buf.put_u32_le(len as u32);
            msg.encode(buf)?;
            Ok(stream.write_all(buf)?)
        })
    }

    fn inner_recv<T: Default + RootMessage>(&self, stream: &mut TcpStream) -> Result<T> {
        LOCAL_BUF.with_borrow_mut(|buf| {
            buf.resize(4, 0);
            stream.read_exact(buf).context("rx len failed")?;
            let len = buf.as_slice().get_u32_le() as usize;
            buf.resize(len, 0);
            stream.read_exact(buf).context("rx payload failed")?;
            T::decode(buf.as_slice()).context("rx decode failed")
        })
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

    pub fn new_narrow_version<P: AsRef<Path>>(server_path: P) -> Result<Self> {
        // Check the version of the client and server to ensure that they're compatible
        let client_version = get_version().map_err(|err| anyhow!(err))?;
        let server_version = get_server_version(&server_path)?;
        if !client::Compat::Narrow.check(&client_version, &server_version) {
            let server_suggestion = if client_version.pre.is_empty() {
                format!(
                    "1. Install r0vm server version {}.{}\n",
                    client_version.major, client_version.minor
                )
            } else {
                format!(
                    "1. Your risc0 dependencies are using a pre-released version {client_version}.\n   \
                    If you encounter this error message when running code on the risc0 codebase, you must\n   \
                    either run the command `git checkout origin/release-{}.{}` to checkout the version of the\n   \
                    risc0 code that is compatible with your server or build the r0vm server from source\n   \
                    https://github.com/risc0/risc0/blob/main/CONTRIBUTING.md\n",
                    server_version.major, server_version.minor
                )
            };
            let msg = format!(
                "Your installation of the r0vm server is not compatible with your host's risc0-zkvm crate.\n\
                Do one of the following to fix this issue:\n\n\
                {server_suggestion}\
                2. Change the risc0-zkvm and risc0-build dependencies in your project to {}.{}\n\n\
                risc0-zkvm version: {client_version}\n\
                r0vm server version: {server_version}",
                server_version.major, server_version.minor
            );
            tracing::warn!("{msg}");
            bail!(msg);
        }

        Self::new(server_path)
    }

    fn spawn_fail(&self) -> String {
        format!(
            "Could not launch zkvm: \"{}\". \n
            Use `cargo binstall cargo-risczero` to install the latest zkvm.",
            self.server_path.to_string_lossy()
        )
    }
}

fn get_server_version<P: AsRef<Path>>(server_path: P) -> Result<Version> {
    let output = Command::new(server_path.as_ref().as_os_str())
        .arg("--version")
        .output()?;
    let cmd_output = String::from_utf8(output.stdout)?;
    let (_, version_str) = regex_captures!(r".* (.*)\n$", &cmd_output)
        .ok_or_else(|| anyhow!("failed to parse server version number"))?;
    Version::parse(version_str).map_err(|e| anyhow!(e))
}

impl Connector for ParentProcessConnector {
    fn connect(&self) -> Result<ConnectionWrapper> {
        let addr = self.listener.local_addr()?;
        let child = Command::new(&self.server_path)
            .arg("--port")
            .arg(addr.port().to_string())
            .spawn()
            .with_context(|| self.spawn_fail())?;

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
        let stream = stream.inspect_err(|_| {
            shutdown.store(true, Ordering::Relaxed);
            let _ = TcpStream::connect(addr);
            handle.join().unwrap();
        })?;

        Ok(ConnectionWrapper::new(Arc::new(Mutex::new(
            ParentProcessConnection::new(child, stream),
        ))))
    }
}

#[cfg(feature = "prove")]
struct TcpConnector {
    addr: String,
}

#[cfg(feature = "prove")]
impl TcpConnector {
    pub(crate) fn new(addr: &str) -> Self {
        Self {
            addr: addr.to_string(),
        }
    }
}

#[cfg(feature = "prove")]
impl Connector for TcpConnector {
    fn connect(&self) -> Result<ConnectionWrapper> {
        tracing::debug!("connect");
        let stream = TcpStream::connect(&self.addr)?;
        Ok(ConnectionWrapper::new(Arc::new(Mutex::new(
            TcpConnection::new(stream),
        ))))
    }
}

struct ParentProcessConnection {
    child: Child,
    stream: TcpStream,
}

#[cfg(feature = "prove")]
struct TcpConnection {
    stream: TcpStream,
}

impl ParentProcessConnection {
    pub fn new(child: Child, stream: TcpStream) -> Self {
        Self { child, stream }
    }
}

impl Connection for ParentProcessConnection {
    fn stream(&mut self) -> &mut TcpStream {
        &mut self.stream
    }

    fn close(&mut self) -> Result<i32> {
        let status = self.child.wait()?;
        Ok(status.code().unwrap_or_default())
    }
}

#[cfg(feature = "prove")]
impl TcpConnection {
    pub fn new(stream: TcpStream) -> Self {
        Self { stream }
    }
}

#[cfg(feature = "prove")]
impl Connection for TcpConnection {
    fn stream(&mut self) -> &mut TcpStream {
        &mut self.stream
    }

    fn close(&mut self) -> Result<i32> {
        Ok(0)
    }
}

fn malformed_err(field: &str) -> anyhow::Error {
    anyhow!("Malformed error: {field}")
}

impl pb::api::Asset {
    fn as_bytes(&self) -> Result<Bytes> {
        let bytes = match self
            .kind
            .as_ref()
            .ok_or_else(|| malformed_err("Asset.kind"))?
        {
            pb::api::asset::Kind::Inline(bytes) => bytes.clone(),
            pb::api::asset::Kind::Path(path) => std::fs::read(path)?,
            pb::api::asset::Kind::Redis(_) => bail!("as_bytes not supported for redis"),
        };
        Ok(bytes.into())
    }
}

/// Determines the format of an asset.
#[derive(Clone)]
pub enum Asset {
    /// The asset is encoded inline.
    Inline(Bytes),

    /// The asset is written to disk.
    Path(PathBuf),

    /// The asset is written to redis.
    Redis(String),
}

/// Determines the parameters for AssetRequest::Redis
#[derive(Clone)]
pub struct RedisParams {
    /// The url of the redis instance
    pub url: String,

    /// The key used to write to redis
    pub key: String,

    /// time to live (expiration) for the key being set
    pub ttl: u64,
}

/// Determines the format of an asset request.
#[derive(Clone)]
pub enum AssetRequest {
    /// The asset is encoded inline.
    Inline,

    /// The asset is written to disk.
    Path(PathBuf),

    /// The asset is written to redis.
    Redis(RedisParams),
}

/// Provides information about the result of execution.
#[derive(Clone, Debug)]
#[non_exhaustive]
pub struct SessionInfo {
    /// The number of user cycles for each segment.
    pub segments: Vec<SegmentInfo>,

    /// The data publicly committed by the guest program.
    pub journal: Journal,

    /// The [ExitCode] of the session.
    pub exit_code: ExitCode,

    /// The [ReceiptClaim] associated with the executed session. This receipt claim is what will be
    /// proven if this session is passed to the Prover.
    pub receipt_claim: Option<ReceiptClaim>,
}

impl SessionInfo {
    /// The total number of user cycles across all segments, without any
    /// overhead for continuations or po2 padding.
    pub fn cycles(&self) -> u64 {
        self.segments.iter().map(|s| s.cycles as u64).sum()
    }
}

/// Provides information about a segment of execution.
#[derive(Clone, Debug, Serialize, Deserialize)]
#[non_exhaustive]
pub struct SegmentInfo {
    /// The number of cycles used for proving in powers of 2.
    pub po2: u32,

    /// The number of user cycles without any overhead for continuations or po2
    /// padding.
    pub cycles: u32,
}

impl Asset {
    /// Return the bytes for this asset.
    pub fn as_bytes(&self) -> Result<Bytes> {
        Ok(match self {
            Asset::Inline(bytes) => bytes.clone(),
            Asset::Path(path) => std::fs::read(path)?.into(),
            Asset::Redis(_) => bail!("as_bytes not supported for Asset::Redis"),
        })
    }
}

fn invalid_path() -> anyhow::Error {
    anyhow::Error::msg("Path must be UTF-8")
}

fn path_to_string<P: AsRef<Path>>(path: P) -> Result<String> {
    Ok(path.as_ref().to_str().ok_or_else(invalid_path)?.to_string())
}
