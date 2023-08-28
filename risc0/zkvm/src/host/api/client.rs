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

use super::{malformed_err, pb, void, ConnectionWrapper, Connector, ParentProcessConnector};
use crate::{host::recursion::SuccinctReceipt, ExecutorEnv, ProverOpts, Receipt, SegmentReceipt};

/// TODO
pub struct Client {
    connector: Box<dyn Connector>,
}

impl Client {
    /// Construct an [IpcClient] based on environment variables.
    // pub fn from_env() -> Self {
    //     let server_path = std::env::var("R0VM_PATH").unwrap_or("r0vm".to_string());
    //     IpcClient::new(server_path)
    // }

    pub fn new(connector: Box<dyn Connector>) -> Self {
        Self { connector }
    }

    /// TODO
    pub fn new_sub_process<P: AsRef<Path>>(server_path: P) -> Result<Self> {
        let connector = ParentProcessConnector::new(server_path)?;
        Ok(Self::new(Box::new(connector)))
    }

    fn connect(&self) -> Result<ConnectionWrapper> {
        let mut conn = self.connector.connect()?;

        let request = pb::HelloRequest { version: 0 };
        log::debug!("tx: {request:?}");
        conn.send(request)?;

        let reply: pb::HelloReply = conn.recv()?;
        log::debug!("rx: {reply:?}");
        if let pb::HelloReplyKind::Error(err) = reply.kind.ok_or(malformed_err())? {
            let code = conn.close()?;
            log::debug!("Child finished with: {code}");
            bail!(err);
        }

        Ok(conn)
    }

    fn make_execute_request(
        &self,
        env: &ExecutorEnv<'_>,
        binary: pb::Binary,
        segments: pb::AssetRequest,
    ) -> pb::ExecuteRequest {
        pb::ExecuteRequest {
            binary: Some(binary),
            segments: Some(segments),
            env_vars: env.env_vars.clone(),
            slice_ios: env.slice_io.borrow().inner.keys().cloned().collect(),
            read_fds: env.posix_io.borrow().read_fds.keys().cloned().collect(),
            write_fds: env.posix_io.borrow().write_fds.keys().cloned().collect(),
        }
    }

    /// TODO
    // r0vm prove --ipc --image $IMAGE --hashfn $HFN --output $RECEIPT
    pub fn prove(
        &self,
        _env: &ExecutorEnv<'_>,
        _opts: ProverOpts,
        _image: pb::Asset,
    ) -> Result<Receipt> {
        // let mut conn = self.connect()?;

        // let mut request = protos::ServerProveRequest::new();
        // let execute = self.make_execute_request(env, image);
        // request.execute = Some(execute).into();

        // conn.send(request)?;

        // let request = IpcServerRequest::Prove(IpcServerProveRequest {
        //     bin_type: BinaryType::Image,
        //     binary: image,
        //     opts,
        //     receipt: AssetRequest::Inline,
        //     env_vars: env.env_vars.clone(),
        //     slice_ios,
        // });
        // bincode::serialize_into(&mut writer, &request)?;

        // let receipt = loop {
        //     let request = bincode::deserialize_from(&mut reader)?;
        //     let either = self.prove_dispatch(&env, request)?;
        //     match either {
        //         Either::Response(response) => bincode::serialize_into(&mut writer,
        // &response)?,         Either::Done(receipt) => break receipt,
        //     }
        // };

        // let code = conn.wait()?;
        // if code != 0 {
        //     bail!("Child finished with: {code}");
        // }

        // Ok(receipt)
        todo!()
    }

    /// TODO
    // r0vm execute --ipc --image $IMAGE
    pub fn execute<F>(
        &self,
        env: &ExecutorEnv<'_>,
        binary: pb::Binary,
        segments: pb::AssetRequest,
        callback: F,
    ) -> Result<pb::SessionInfo>
    where
        F: FnMut(pb::SegmentInfo) -> Result<()>,
    {
        let mut conn = self.connect()?;

        let request = pb::ServerRequest {
            kind: Some(pb::ServerRequestKind::Execute(pb::ServerExecuteRequest {
                execute: Some(self.make_execute_request(env, binary, segments)),
            })),
        };
        log::debug!("tx: {request:?}");
        conn.send(request)?;

        let mut callback = callback;
        let result = loop {
            let request: pb::ClientRequest = conn.recv()?;
            log::debug!("rx: {request:?}");
            match request.kind.ok_or(malformed_err())? {
                pb::ClientRequestKind::Io(io) => {
                    let msg: pb::ClientIoReply = self.on_io(env, io).into();
                    log::debug!("tx: {msg:?}");
                    conn.send(msg)?;
                }
                pb::ClientRequestKind::SegmentDone(segment) => {
                    let reply: pb::GenericReply = segment
                        .segment
                        .map_or_else(|| Err(malformed_err()), |segment| callback(segment))
                        .into();
                    log::debug!("tx: {reply:?}");
                    conn.send(reply)?;
                }
                pb::ClientRequestKind::SessionDone(session) => {
                    break match session.session {
                        Some(session) => Ok(session),
                        None => Err(malformed_err()),
                    }
                }
                pb::ClientRequestKind::Error(err) => break Err(err.into()),
            };
        };

        let code = conn.close()?;
        if code != 0 {
            bail!("Child finished with: {code}");
        }

        result
    }

    /// TODO
    // r0vm prove --segment $SEGMENT --lift --hashfn $HFN --output $RECEIPT
    pub fn prove_segment(&self, _opts: ProverOpts, _segment: pb::Asset) -> Result<SegmentReceipt> {
        // let (mut child, channel) = self.connect()?;

        // let request = IpcServerRequest::ProveSegment(IpcServerProveSegmentRequest {
        //     segment,
        //     opts,
        //     receipt: AssetRequest::Inline,
        // });
        // bincode::serialize_into(writer, &request)?;

        // let response: IpcProveSegmentResponse = bincode::deserialize_from(reader)?;
        // let result = match response {
        //     IpcProveSegmentResponse::Ok { receipt } => Ok(receipt),
        //     IpcProveSegmentResponse::Error { reason } => Err(anyhow!(reason)),
        // };

        // let status = child.wait()?;
        // if !status.success() {
        //     bail!("Child finished with: {:?}", status.code())
        // }

        // result
        todo!()
    }

    /// TODO
    // r0vm lift --receipt $INPUT --output $OUTPUT
    pub fn lift(&self, _opts: &ProverOpts, _receipt: &SegmentReceipt) -> Result<SuccinctReceipt> {
        todo!()
    }

    /// TODO
    // r0vm join --left $LHS --right $RHS --output $RECEIPT
    pub fn join(
        &self,
        _opts: &ProverOpts,
        _lhs: &SuccinctReceipt,
        _rhs: &SuccinctReceipt,
    ) -> Result<SuccinctReceipt> {
        todo!()
    }

    fn on_io(&self, env: &ExecutorEnv<'_>, request: pb::ClientIoRequest) -> Result<Bytes> {
        match request.kind.ok_or(malformed_err())? {
            pb::ClientIoRequestKind::Posix(posix) => {
                let cmd = posix.cmd.ok_or(malformed_err())?;
                match cmd.kind.ok_or(malformed_err())? {
                    pb::PosixCmdKind::Read(nread) => {
                        self.on_posix_read(env, posix.fd, nread as usize)
                    }
                    pb::PosixCmdKind::Write(from_guest) => {
                        self.on_posix_write(env, posix.fd, from_guest.into())?;
                        Ok(Bytes::new())
                    }
                }
            }
            pb::ClientIoRequestKind::Slice(slice_io) => {
                self.on_slice(env, &slice_io.name, slice_io.from_guest.into())
            }
            pb::ClientIoRequestKind::Trace(_event) => {
                // self.on_trace(env, event)?;
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

    // fn on_trace(&self, env: &ExecutorEnv<'_>, event: TraceEvent) -> Result<()> {
    //     if let Some(ref trace_callback) = env.trace {
    //         trace_callback.borrow_mut()(event)?;
    //     }
    //     Ok(())
    // }
}

impl From<Result<Bytes, anyhow::Error>> for pb::ClientIoReply {
    fn from(result: Result<Bytes, anyhow::Error>) -> Self {
        pb::ClientIoReply {
            kind: Some(match result {
                Ok(bytes) => pb::ClientIoReplyKind::Ok(bytes.into()),
                Err(err) => pb::ClientIoReplyKind::Error(err.into()),
            }),
        }
    }
}

impl From<Result<(), anyhow::Error>> for pb::GenericReply {
    fn from(result: Result<(), anyhow::Error>) -> Self {
        pb::GenericReply {
            kind: Some(match result {
                Ok(_) => pb::GenericReplyKind::Ok(void()),
                Err(err) => pb::GenericReplyKind::Error(err.into()),
            }),
        }
    }
}

impl From<anyhow::Error> for pb::GenericError {
    fn from(err: anyhow::Error) -> Self {
        pb::GenericError {
            reason: err.to_string(),
        }
    }
}

impl From<pb::GenericError> for anyhow::Error {
    fn from(err: pb::GenericError) -> Self {
        anyhow::Error::msg(err.reason)
    }
}
