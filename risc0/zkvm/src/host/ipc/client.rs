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
    path::{Path, PathBuf},
    process::{Child, Command, Stdio},
};

use anyhow::{anyhow, bail, Result};
use bytes::Bytes;

use super::{malformed_err, Channel};
use crate::{
    host::{
        protos::ipc::{
            binary::BinaryType, client_io_request::Kind as ClientIoRequestKind,
            client_request::Kind as ClientRequestKind, hello_reply::Kind as HelloReplyKind,
            posix_cmd::Kind as PosixCmdKind, Asset, Binary, ClientIoReply, ClientIoRequest,
            ClientRequest, ExecuteRequest, GenericReply, HelloReply, HelloRequest, SegmentInfo,
            ServerExecuteRequest, ServerProveRequest, SessionInfo, Void,
        },
        recursion::SuccinctReceipt,
    },
    ExecutorEnv, ProverOpts, Receipt, SegmentReceipt,
};

/// TODO
pub struct IpcClient {
    server_path: PathBuf,
}

impl IpcClient {
    /// Construct an [IpcClient].
    pub fn new<P: AsRef<Path>>(server_path: P) -> Self {
        Self {
            server_path: server_path.as_ref().to_path_buf(),
        }
    }

    /// Construct an [IpcClient] based on environment variables.
    pub fn from_env() -> Self {
        let server_path = std::env::var("R0VM_PATH").unwrap_or("r0vm".to_string());
        IpcClient::new(server_path)
    }

    fn connect(&self) -> Result<(Child, Channel)> {
        let mut child = Command::new(&self.server_path)
            .arg("--ipc")
            .stdin(Stdio::piped())
            .stdout(Stdio::piped())
            .spawn()?;

        let reader = child.stdout.take().ok_or(anyhow!("Cannot open stdout"))?;
        let writer = child.stdin.take().ok_or(anyhow!("Cannot open stdin"))?;
        let mut channel = Channel::new(reader, writer);

        let mut msg = HelloRequest::new();
        msg.version = 0;
        channel.send(msg)?;

        let reply: HelloReply = channel.recv()?;
        if let HelloReplyKind::Error(reason) = reply.kind.ok_or(malformed_err())? {
            let status = child.wait()?;
            log::debug!("Child finished with: {:?}", status.code());
            bail!(reason);
        }

        Ok((child, channel))
    }

    fn make_execute_request(&self, env: &ExecutorEnv<'_>, image: Asset) -> ExecuteRequest {
        let mut binary = Binary::new();
        binary.kind = BinaryType::IMAGE.into();
        binary.asset = Some(image).into();

        let mut execute = ExecuteRequest::new();
        execute.binary = Some(binary).into();
        execute.env_vars = env.env_vars.clone();
        for key in env.slice_io.borrow().inner.keys() {
            execute.slice_ios.insert(key.clone(), Void::default());
        }
        for key in env.posix_io.borrow().read_fds.keys() {
            execute.read_fds.insert(*key, Void::default());
        }
        for key in env.posix_io.borrow().write_fds.keys() {
            execute.write_fds.insert(*key, Void::default());
        }
        execute
    }

    /// TODO
    // r0vm prove --ipc --image $IMAGE --hashfn $HFN --output $RECEIPT
    pub fn prove(&self, env: &ExecutorEnv<'_>, _opts: ProverOpts, image: Asset) -> Result<Receipt> {
        let (mut child, mut channel) = self.connect()?;

        let mut request = ServerProveRequest::new();
        let execute = self.make_execute_request(env, image);
        request.execute = Some(execute).into();

        channel.send(request)?;

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

        let status = child.wait()?;
        if !status.success() {
            bail!("Child finished with: {:?}", status.code())
        }

        // Ok(receipt)
        todo!()
    }

    /// TODO
    // r0vm execute --ipc --image $IMAGE
    pub fn execute<F>(
        &self,
        env: &ExecutorEnv<'_>,
        image: Asset,
        callback: F,
    ) -> Result<SessionInfo>
    where
        F: FnMut(SegmentInfo) -> Result<()>,
    {
        let (mut child, mut channel) = self.connect()?;

        let mut request = ServerExecuteRequest::new();
        let execute = self.make_execute_request(env, image);
        request.execute = Some(execute).into();

        channel.send(request)?;

        let mut callback = callback;
        let session = loop {
            let request: ClientRequest = channel.recv()?;
            let kind = request.kind.ok_or(malformed_err())?;
            match kind {
                ClientRequestKind::Io(io) => {
                    let reply: ClientIoReply = self.on_io(env, io).into();
                    channel.send(reply)?;
                }
                ClientRequestKind::SegmentDone(segment) => {
                    let reply: GenericReply = segment
                        .segment
                        .into_option()
                        .map_or_else(|| Err(malformed_err()), |segment| callback(segment))
                        .into();
                    channel.send(reply)?;
                }
                ClientRequestKind::SessionDone(session) => {
                    break session.session.into_option().ok_or(malformed_err())?
                }
            };
        };

        let status = child.wait()?;
        if !status.success() {
            bail!("Child finished with: {:?}", status.code())
        }

        Ok(session)
    }

    /// TODO
    // r0vm prove --segment $SEGMENT --lift --hashfn $HFN --output $RECEIPT
    pub fn prove_segment(&self, _opts: ProverOpts, _segment: Asset) -> Result<SegmentReceipt> {
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

    fn on_io(&self, env: &ExecutorEnv<'_>, request: ClientIoRequest) -> Result<Bytes> {
        match request.kind.ok_or(malformed_err())? {
            ClientIoRequestKind::Posix(posix) => {
                let kind = posix.cmd.kind.clone().ok_or(malformed_err())?;
                match kind {
                    PosixCmdKind::Read(_) => self.on_posix_read(env, posix.fd),
                    PosixCmdKind::Write(from_guest) => {
                        self.on_posix_write(env, posix.fd, from_guest.into())?;
                        Ok(Bytes::new())
                    }
                }
            }
            ClientIoRequestKind::Slice(slice_io) => {
                self.on_slice(env, &slice_io.name, slice_io.from_guest.into())
            }
            ClientIoRequestKind::Trace(_event) => {
                // self.on_trace(env, event)?;
                Ok(Bytes::new())
            }
        }
    }

    fn on_posix_read(&self, env: &ExecutorEnv<'_>, fd: u32) -> Result<Bytes> {
        let mut from_host = Vec::new();
        let posix_io = env.posix_io.borrow();
        let reader = posix_io
            .read_fds
            .get(&fd)
            .ok_or(anyhow!("Bad read file descriptor: {fd}"))?;
        reader.borrow_mut().read_to_end(&mut from_host)?;
        Ok(from_host.into())
    }

    fn on_posix_write(&self, env: &ExecutorEnv<'_>, fd: u32, from_guest: Bytes) -> Result<()> {
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
            .ok_or(anyhow!("Unknown io channel name: {name}"))?;
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

impl From<Result<Bytes, anyhow::Error>> for ClientIoReply {
    fn from(result: Result<Bytes, anyhow::Error>) -> Self {
        let mut reply = ClientIoReply::new();
        match result {
            Ok(bytes) => reply.set_ok(bytes.into()),
            Err(err) => reply.set_error(err.to_string()),
        }
        reply
    }
}

impl From<Result<(), anyhow::Error>> for GenericReply {
    fn from(result: Result<(), anyhow::Error>) -> Self {
        let mut reply = GenericReply::new();
        match result {
            Ok(_) => reply.set_ok(Void::default()),
            Err(err) => reply.set_error(err.to_string()),
        }
        reply
    }
}
