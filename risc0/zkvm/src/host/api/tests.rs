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
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkvm_methods::{
    multi_test::MultiTestSpec, MULTI_TEST_ELF, MULTI_TEST_ID, MULTI_TEST_PATH,
};
use risc0_zkvm_platform::{memory::GUEST_MAX_MEM, PAGE_SIZE};
use tempfile::{tempdir, TempDir};
use test_log::test;

use super::{Asset, AssetRequest, Binary, ConnectionWrapper, Connector, TcpConnection};
use crate::{
    recursion::SuccinctReceipt, ApiClient, ApiServer, ExecutorEnv, InnerReceipt, ProverOpts,
    Receipt, SegmentReceipt, SessionInfo, VerifierContext,
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
    segments: Vec<Asset>,
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

    fn execute(&mut self, env: ExecutorEnv<'_>, binary: Binary) -> SessionInfo {
        with_server(self.addr, || {
            let segments_out = AssetRequest::Path(self.get_work_path());
            self.client
                .execute(&env, binary, segments_out, |_info, asset| {
                    self.segments.push(asset);
                    Ok(())
                })
        })
    }

    fn prove(&self, env: ExecutorEnv<'_>, opts: ProverOpts, binary: Binary) -> Receipt {
        with_server(self.addr, || self.client.prove(&env, opts, binary))
    }

    fn prove_segment(&self, opts: ProverOpts, segment: Asset) -> SegmentReceipt {
        with_server(self.addr, || {
            let receipt_out = AssetRequest::Path(self.get_work_path());
            self.client.prove_segment(opts, segment, receipt_out)
        })
    }

    fn lift(&self, opts: ProverOpts, receipt: Asset) -> SuccinctReceipt {
        with_server(self.addr, || {
            let receipt_out = AssetRequest::Path(self.get_work_path());
            self.client.lift(opts, receipt, receipt_out)
        })
    }

    fn join(&self, opts: ProverOpts, left_receipt: Asset, right_receipt: Asset) -> SuccinctReceipt {
        with_server(self.addr, || {
            let receipt_out = AssetRequest::Path(self.get_work_path());
            self.client
                .join(opts, left_receipt, right_receipt, receipt_out)
        })
    }

    fn identity_p254(&self, opts: ProverOpts, receipt: Asset) -> SuccinctReceipt {
        with_server(self.addr, || {
            let receipt_out = AssetRequest::Path(self.get_work_path());
            self.client.identity_p254(opts, receipt, receipt_out)
        })
    }
}

fn with_server<T, F: FnOnce() -> Result<T>>(addr: SocketAddr, f: F) -> T {
    let addr = addr.to_string();
    let handle = thread::Builder::new()
        .name("server".into())
        .spawn(move || {
            let server = ApiServer::new_tcp(addr);
            server.run().unwrap();
        })
        .unwrap();

    let result = f().unwrap();
    handle.join().unwrap();
    result
}

#[test]
fn execute_elf() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    let binary = Binary::new_elf_path(MULTI_TEST_PATH);
    TestClient::new().execute(env, binary);
}

#[test]
fn execute_image() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    let program = Program::load_elf(&MULTI_TEST_ELF, GUEST_MAX_MEM as u32).unwrap();
    let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();
    let binary = image.into();
    TestClient::new().execute(env, binary);
}

#[test]
fn prove_elf() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    let binary = Binary::new_elf_path(MULTI_TEST_PATH);
    let opts = ProverOpts::default();
    let receipt = TestClient::new().prove(env, opts, binary);
    receipt.verify(MULTI_TEST_ID).unwrap();
}

#[test]
fn prove_segment_elf() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    let binary = Binary::new_elf_path(MULTI_TEST_PATH);

    let mut client = TestClient::new();

    let session = client.execute(env, binary);
    assert_eq!(session.segments.len(), client.segments.len());

    let ctx = VerifierContext::default();
    for segment in client.segments.iter() {
        let opts = ProverOpts::default();
        let receipt = client.prove_segment(opts, segment.clone());
        receipt.verify_with_context(&ctx).unwrap();
    }
}

#[test]
fn lift_join_identity() {
    let segment_limit_po2 = 16; // 64k cycles
    let cycles = 1 << segment_limit_po2;
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::BusyLoop { cycles })
        .unwrap()
        .segment_limit_po2(segment_limit_po2)
        .build()
        .unwrap();
    let binary = Binary::new_elf_path(MULTI_TEST_PATH);

    let mut client = TestClient::new();

    let session = client.execute(env, binary);
    assert_eq!(session.segments.len(), client.segments.len());

    let opts = ProverOpts::default();

    let receipt = client.prove_segment(opts.clone(), client.segments[0].clone());
    let mut rollup = client.lift(opts.clone(), receipt.try_into().unwrap());

    for segment in &client.segments[1..] {
        let receipt = client.prove_segment(opts.clone(), segment.clone());
        let rec_receipt = client.lift(opts.clone(), receipt.try_into().unwrap());

        rollup = client.join(
            opts.clone(),
            rollup.try_into().unwrap(),
            rec_receipt.try_into().unwrap(),
        );
        rollup
            .verify_with_context(&VerifierContext::default())
            .unwrap();
    }
    client.identity_p254(opts, rollup.clone().try_into().unwrap());

    let rollup_receipt = Receipt::new(InnerReceipt::Succinct(rollup), session.journal.bytes.into());
    rollup_receipt.verify(MULTI_TEST_ID).unwrap();
}

#[test]
#[should_panic(expected = "Guest panicked: panicked at 'MultiTestSpec::Fail invoked'")]
fn guest_error_forwarding() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::Fail)
        .unwrap()
        .build()
        .unwrap();
    let binary = Binary::new_elf_path(MULTI_TEST_PATH);
    TestClient::new().execute(env, binary);
}
