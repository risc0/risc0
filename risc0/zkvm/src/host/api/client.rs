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

use std::path::Path;

use anyhow::{anyhow, bail, Result};
use bytes::Bytes;
use prost::Message;

use super::{
    malformed_err, pb, Asset, AssetRequest, Binary, ConnectionWrapper, Connector,
    ParentProcessConnector, SessionInfo,
};
use crate::{
    get_version,
    host::{api::SegmentInfo, client::prove::get_r0vm_path, recursion::SuccinctReceipt},
    ExecutorEnv, Journal, ProverOpts, Receipt, SegmentReceipt,
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
        Client::new_sub_process(get_r0vm_path())
    }

    /// Construct a [Client] using the specified [Connector] to establish a
    /// connection with the server.
    pub fn with_connector(connector: Box<dyn Connector>) -> Self {
        Self { connector }
    }

    /// Prove the specified [Binary].
    pub fn prove(
        &self,
        env: &ExecutorEnv<'_>,
        opts: ProverOpts,
        binary: Binary,
    ) -> Result<Receipt> {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::Prove(
                pb::api::ProveRequest {
                    env: Some(self.make_execute_env(env, binary.try_into()?)),
                    opts: Some(opts.into()),
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

        let receipt_bytes = asset.as_bytes()?;
        let receipt_pb = pb::core::Receipt::decode(receipt_bytes)?;
        receipt_pb.try_into()
    }

    /// Execute the specified [Binary].
    pub fn execute<F>(
        &self,
        env: &ExecutorEnv<'_>,
        binary: Binary,
        segments_out: AssetRequest,
        callback: F,
    ) -> Result<SessionInfo>
    where
        F: FnMut(SegmentInfo, Asset) -> Result<()>,
    {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::Execute(
                pb::api::ExecuteRequest {
                    env: Some(self.make_execute_env(env, binary.try_into()?)),
                    segments_out: Some(segments_out.try_into()?),
                },
            )),
        };
        log::debug!("tx: {request:?}");
        conn.send(request)?;

        let result = self.execute_handler(callback, &mut conn, env);

        let code = conn.close()?;
        if code != 0 {
            bail!("Child finished with: {code}");
        }

        result
    }

    /// Prove the specified segment.
    pub fn prove_segment(
        &self,
        opts: ProverOpts,
        segment: Asset,
        receipt_out: AssetRequest,
    ) -> Result<SegmentReceipt> {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::ProveSegment(
                pb::api::ProveSegmentRequest {
                    opts: Some(opts.into()),
                    segment: Some(segment.try_into()?),
                    receipt_out: Some(receipt_out.try_into()?),
                },
            )),
        };
        log::debug!("tx: {request:?}");
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

    /// Lift a [SegmentReceipt] into a [SuccinctReceipt].
    pub fn lift(
        &self,
        opts: ProverOpts,
        receipt: Asset,
        receipt_out: AssetRequest,
    ) -> Result<SuccinctReceipt> {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::Lift(pb::api::LiftRequest {
                opts: Some(opts.into()),
                receipt: Some(receipt.try_into()?),
                receipt_out: Some(receipt_out.try_into()?),
            })),
        };
        log::debug!("tx: {request:?}");
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

    /// Recursively join two receipts into a [SuccinctReceipt].
    pub fn join(
        &self,
        opts: ProverOpts,
        left_receipt: Asset,
        right_receipt: Asset,
        receipt_out: AssetRequest,
    ) -> Result<SuccinctReceipt> {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::Join(pb::api::JoinRequest {
                opts: Some(opts.into()),
                left_receipt: Some(left_receipt.try_into()?),
                right_receipt: Some(right_receipt.try_into()?),
                receipt_out: Some(receipt_out.try_into()?),
            })),
        };
        log::debug!("tx: {request:?}");
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

    /// Convert a [SuccinctReceipt] with a poseidon hash function that uses a 254-bit field
    pub fn identity_p254(
        &self,
        opts: ProverOpts,
        receipt: Asset,
        receipt_out: AssetRequest,
    ) -> Result<SuccinctReceipt> {
        let mut conn = self.connect()?;

        let request = pb::api::ServerRequest {
            kind: Some(pb::api::server_request::Kind::IdentiyP254(
                pb::api::IdentityP254Request {
                    opts: Some(opts.into()),
                    receipt: Some(receipt.try_into()?),
                    receipt_out: Some(receipt_out.try_into()?),
                },
            )),
        };
        log::debug!("tx: {request:?}");
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

    fn connect(&self) -> Result<ConnectionWrapper> {
        let mut conn = self.connector.connect()?;

        let client_version = get_version().map_err(|err| anyhow!(err))?;
        let request = pb::api::HelloRequest {
            version: Some(client_version.clone().into()),
        };
        log::debug!("tx: {request:?}");
        conn.send(request)?;

        let reply: pb::api::HelloReply = conn.recv()?;
        log::debug!("rx: {reply:?}");
        match reply.kind.ok_or(malformed_err())? {
            pb::api::hello_reply::Kind::Ok(reply) => {
                let server_version: semver::Version = reply
                    .version
                    .ok_or(malformed_err())?
                    .try_into()
                    .map_err(|err: semver::Error| anyhow!(err))?;
                if !check_server_version(&client_version, &server_version) {
                    let msg = format!("incompatible server version: {server_version}");
                    log::debug!("{msg}");
                    bail!(msg);
                }
            }
            pb::api::hello_reply::Kind::Error(err) => {
                let code = conn.close()?;
                log::debug!("Child finished with: {code}");
                bail!(err);
            }
        }

        Ok(conn)
    }

    fn make_execute_env(
        &self,
        env: &ExecutorEnv<'_>,
        binary: pb::api::Binary,
    ) -> pb::api::ExecutorEnv {
        pb::api::ExecutorEnv {
            binary: Some(binary),
            env_vars: env.env_vars.clone(),
            slice_ios: env.slice_io.borrow().inner.keys().cloned().collect(),
            read_fds: env.posix_io.borrow().read_fds.keys().cloned().collect(),
            write_fds: env.posix_io.borrow().write_fds.keys().cloned().collect(),
            segment_limit_po2: env.segment_limit_po2,
            session_limit: env.session_limit,
        }
    }

    fn execute_handler<F>(
        &self,
        callback: F,
        conn: &mut ConnectionWrapper,
        env: &ExecutorEnv<'_>,
    ) -> Result<SessionInfo>
    where
        F: FnMut(SegmentInfo, Asset) -> Result<()>,
    {
        let mut callback = callback;
        let mut segments = Vec::new();
        loop {
            let reply: pb::api::ServerReply = conn.recv()?;
            log::debug!("rx: {reply:?}");

            match reply.kind.ok_or(malformed_err())? {
                pb::api::server_reply::Kind::Ok(request) => {
                    match request.kind.ok_or(malformed_err())? {
                        pb::api::client_callback::Kind::Io(io) => {
                            let msg: pb::api::OnIoReply = self.on_io(env, io).into();
                            log::debug!("tx: {msg:?}");
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
                                        callback(info, asset)
                                    },
                                )
                                .into();
                            log::debug!("tx: {reply:?}");
                            conn.send(reply)?;
                        }
                        pb::api::client_callback::Kind::SessionDone(session) => {
                            return match session.session {
                                Some(session) => Ok(SessionInfo {
                                    segments,
                                    journal: Journal::new(session.journal.into()),
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
            match reply.kind.ok_or(malformed_err())? {
                pb::api::server_reply::Kind::Ok(request) => {
                    match request.kind.ok_or(malformed_err())? {
                        pb::api::client_callback::Kind::Io(io) => {
                            let msg: pb::api::OnIoReply = self.on_io(env, io).into();
                            log::debug!("tx: {msg:?}");
                            conn.send(msg)?;
                        }
                        pb::api::client_callback::Kind::SegmentDone(_) => {
                            return Err(anyhow!("Illegal client callback"))
                        }
                        pb::api::client_callback::Kind::SessionDone(_) => {
                            return Err(anyhow!("Illegal client callback"))
                        }
                        pb::api::client_callback::Kind::ProveDone(done) => {
                            return Ok(done.receipt.ok_or(malformed_err())?)
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
        }
    }

    fn on_posix_read(&self, env: &ExecutorEnv<'_>, fd: u32, nread: usize) -> Result<Bytes> {
        log::debug!("on_posix_read: {fd}, {nread}");
        let mut from_host = Vec::with_capacity(nread);
        from_host.resize(nread, 0);
        let posix_io = env.posix_io.borrow();
        let reader = posix_io
            .read_fds
            .get(&fd)
            .ok_or(anyhow!("Bad read file descriptor: {fd}"))?;
        let nread = reader.borrow_mut().read(&mut from_host)?;
        let slice = from_host[..nread].to_vec();
        Ok(slice.into())
    }

    fn on_posix_write(&self, env: &ExecutorEnv<'_>, fd: u32, from_guest: Bytes) -> Result<()> {
        log::debug!("on_posix_write: {fd}");
        let posix_io = env.posix_io.borrow();
        let writer = posix_io
            .write_fds
            .get(&fd)
            .ok_or(anyhow!("Bad write file descriptor: {fd}"))?;
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
        if let Some(ref trace_callback) = env.trace {
            trace_callback.borrow_mut()(event.try_into()?)?;
        }
        Ok(())
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

fn check_server_version(requested: &semver::Version, server: &semver::Version) -> bool {
    if requested.pre.is_empty() {
        let comparator = semver::Comparator {
            op: semver::Op::Tilde,
            major: requested.major,
            minor: Some(requested.minor),
            patch: Some(requested.patch),
            pre: semver::Prerelease::EMPTY,
        };
        comparator.matches(server)
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
        assert!(!test("0.18.1", "0.18.0"));
        assert!(!test("0.18.0", "0.19.0"));

        assert!(test("1.0.0", "1.0.0"));
        assert!(test("1.0.0", "1.0.1"));
        assert!(test("1.1.0", "1.1.0"));
        assert!(test("1.1.0", "1.1.1"));
        assert!(!test("1.0.0", "0.18.0"));
        assert!(!test("1.0.0", "2.0.0"));
        assert!(!test("1.1.0", "1.0.0"));

        assert!(test("0.19.0-alpha.1", "0.19.0-alpha.1"));
        assert!(!test("0.19.0-alpha.1", "0.19.0-alpha.2"));
    }
}
