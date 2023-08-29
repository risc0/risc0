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
    net::{SocketAddr, TcpListener},
    path::PathBuf,
    thread,
};

use anyhow::Result;
use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ID, MULTI_TEST_PATH};
use tempfile::{tempdir, TempDir};
use test_log::test;

use super::{pb, Asset, AssetRequest, Binary, ConnectionWrapper, Connector, TcpConnection};
use crate::{
    serde::to_vec, ApiClient, ApiServer, ExecutorEnv, ProverOpts, Receipt, SegmentReceipt,
    VerifierContext,
};

struct TestClientConnector {
    listener: TcpListener,
}

impl TestClientConnector {
    fn new() -> Result<Self> {
        Ok(Self {
            listener: TcpListener::bind("127.0.0.1:0")?,
        })
    }
}

impl Connector for TestClientConnector {
    fn connect(&self) -> Result<ConnectionWrapper> {
        let (stream, _) = self.listener.accept()?;
        Ok(ConnectionWrapper::new(Box::new(TcpConnection::new(stream))))
    }
}

struct TestClient {
    work_dir: TempDir,
    client: ApiClient,
    addr: SocketAddr,
    segments: Vec<pb::SegmentInfo>,
}

impl TestClient {
    fn new() -> Self {
        let connector = TestClientConnector::new().unwrap();
        let addr = connector.listener.local_addr().unwrap();
        let client = ApiClient::with_connector(Box::new(connector));
        Self {
            work_dir: tempdir().unwrap(),
            client,
            addr,
            segments: Vec::new(),
        }
    }

    fn get_work_path(&self) -> PathBuf {
        self.work_dir.path().to_path_buf()
    }

    fn execute(&mut self, env: ExecutorEnv<'_>, binary: Binary) -> Result<pb::SessionInfo> {
        with_server(self.addr, || {
            let segments_out = AssetRequest::Path(self.get_work_path());
            self.client.execute(&env, binary, segments_out, |segment| {
                self.segments.push(segment);
                Ok(())
            })
        })
    }

    fn prove(&self, env: ExecutorEnv<'_>, opts: ProverOpts, binary: Binary) -> Result<Receipt> {
        with_server(self.addr, || self.client.prove(&env, opts, binary))
    }

    fn prove_segment(&self, opts: ProverOpts, segment: Asset) -> Result<SegmentReceipt> {
        with_server(self.addr, || {
            let receipt_out = AssetRequest::Path(self.get_work_path());
            self.client.prove_segment(opts, segment, receipt_out)
        })
    }
}

fn with_server<T, F: FnOnce() -> Result<T>>(addr: SocketAddr, f: F) -> Result<T> {
    let addr = addr.to_string();
    let handle = thread::Builder::new()
        .name("server".into())
        .spawn(move || {
            let server = ApiServer::new_tcp(addr);
            server.run().unwrap();
        })
        .unwrap();

    let result = f();
    handle.join().unwrap();
    result
}

#[test]
fn execute_basic() {
    let input = to_vec(&MultiTestSpec::DoNothing).unwrap();
    let env = ExecutorEnv::builder().add_input(&input).build().unwrap();
    let binary = Binary::new_elf_path(MULTI_TEST_PATH);
    TestClient::new().execute(env, binary).unwrap();
}

#[test]
fn prove_basic() {
    let input = to_vec(&MultiTestSpec::DoNothing).unwrap();
    let env = ExecutorEnv::builder().add_input(&input).build().unwrap();
    let binary = Binary::new_elf_path(MULTI_TEST_PATH);
    let opts = ProverOpts::default();
    let receipt = TestClient::new().prove(env, opts, binary).unwrap();
    receipt.verify(MULTI_TEST_ID).unwrap();
}

#[test]
fn prove_segment_basic() {
    let input = to_vec(&MultiTestSpec::DoNothing).unwrap();
    let env = ExecutorEnv::builder().add_input(&input).build().unwrap();
    let binary = Binary::new_elf_path(MULTI_TEST_PATH);

    let mut client = TestClient::new();

    let session = client.execute(env, binary).unwrap();
    assert_eq!(session.segments as usize, client.segments.len());

    let ctx = VerifierContext::default();
    for segment in client.segments.iter() {
        let opts = ProverOpts::default();
        let segment = segment.segment.clone().unwrap().try_into().unwrap();
        let receipt = client.prove_segment(opts, segment).unwrap();
        receipt.verify_with_context(&ctx).unwrap();
    }
}
