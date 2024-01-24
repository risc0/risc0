// Copyright 2024 RISC Zero, Inc.
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
use risc0_zkvm_methods::{
    HELLO_COMMIT_ELF, HELLO_COMMIT_ID, MULTI_TEST_ELF, MULTI_TEST_ID, MULTI_TEST_PATH,
};
use risc0_zkvm_methods_core::multi_test::MultiTestSpec;
use tempfile::{tempdir, TempDir};
use test_log::test;

use super::{Asset, AssetRequest, ConnectionWrapper, Connector, TcpConnection};
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

    fn execute(&mut self, env: ExecutorEnv<'_>, binary: Asset) -> SessionInfo {
        with_server(self.addr, || {
            let segments_out = AssetRequest::Path(self.get_work_path());
            self.client
                .execute(&env, binary, segments_out, |_info, asset| {
                    self.segments.push(asset);
                    Ok(())
                })
        })
    }

    fn prove(&self, env: ExecutorEnv<'_>, opts: ProverOpts, binary: Asset) -> Receipt {
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

    fn resolve(
        &self,
        opts: ProverOpts,
        conditional_receipt: Asset,
        assumption_receipt: Asset,
    ) -> SuccinctReceipt {
        with_server(self.addr, || {
            let receipt_out = AssetRequest::Path(self.get_work_path());
            self.client
                .resolve(opts, conditional_receipt, assumption_receipt, receipt_out)
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
fn execute() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    let binary = Asset::Inline(MULTI_TEST_ELF.into());
    TestClient::new().execute(env, binary);
}

#[test]
fn prove() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    let binary = Asset::Path(MULTI_TEST_PATH.into());
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
    let binary = Asset::Inline(MULTI_TEST_ELF.into());

    let mut client = TestClient::new();

    let session = client.execute(env, binary);
    assert_eq!(session.segments.len(), client.segments.len());

    let ctx = VerifierContext::default();
    for segment in client.segments.iter() {
        let opts = ProverOpts::default();
        let receipt = client.prove_segment(opts, segment.clone());
        receipt.verify_integrity_with_context(&ctx).unwrap();
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
    let binary = Asset::Inline(MULTI_TEST_ELF.into());

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
            .verify_integrity_with_context(&VerifierContext::default())
            .unwrap();
    }
    client.identity_p254(opts, rollup.clone().try_into().unwrap());

    let rollup_receipt = Receipt::new(InnerReceipt::Succinct(rollup), session.journal.bytes.into());
    rollup_receipt.verify(MULTI_TEST_ID).unwrap();
}

#[test]
fn lift_resolve() {
    let mut client = TestClient::new();

    // Execute the hello commit guest to use as an assumption.
    let hello_commit_binary = Asset::Inline(HELLO_COMMIT_ELF.into());
    let assumption_session = client.execute(ExecutorEnv::default(), hello_commit_binary);
    assert_eq!(assumption_session.segments.len(), 1);
    assert_eq!(client.segments.len(), 1);

    let opts = ProverOpts::default();

    // Prove and lift the assumption.
    let assumption_segment_receipt = client.prove_segment(opts.clone(), client.segments[0].clone());
    assumption_segment_receipt
        .verify_integrity_with_context(&VerifierContext::default())
        .unwrap();
    let assumption_succinct_receipt =
        client.lift(opts.clone(), assumption_segment_receipt.try_into().unwrap());
    assumption_succinct_receipt
        .verify_integrity_with_context(&VerifierContext::default())
        .unwrap();

    // Drop the old client and create a new one to reset the segment list.
    let mut client = TestClient::new();

    // Execute the composition multitest
    let env = ExecutorEnv::builder()
        .add_assumption(assumption_succinct_receipt.claim.clone())
        .write(&MultiTestSpec::SysVerify(vec![(
            HELLO_COMMIT_ID.into(),
            b"hello world".to_vec(),
        )]))
        .unwrap()
        .build()
        .unwrap();
    let multi_test_binary = Asset::Inline(MULTI_TEST_ELF.into());
    let composition_session = client.execute(env, multi_test_binary);
    assert_eq!(assumption_session.segments.len(), 1);
    assert_eq!(client.segments.len(), 1);

    // Prove and lift the composition
    let composition_segment_receipt =
        client.prove_segment(opts.clone(), client.segments[0].clone());
    composition_segment_receipt
        .verify_integrity_with_context(&VerifierContext::default())
        .unwrap();
    let composition_succinct_receipt = client.lift(
        opts.clone(),
        composition_segment_receipt.try_into().unwrap(),
    );
    composition_succinct_receipt
        .verify_integrity_with_context(&VerifierContext::default())
        .unwrap();

    // Use resolve to create an unconditional succinct receipt
    let succint_receipt = client.resolve(
        opts.clone(),
        composition_succinct_receipt.try_into().unwrap(),
        assumption_succinct_receipt.try_into().unwrap(),
    );

    // Wrap into a Receipt and verify
    let receipt = Receipt::new(
        InnerReceipt::Succinct(succint_receipt),
        composition_session.journal.bytes,
    );
    receipt.verify(MULTI_TEST_ID).unwrap();
}

#[test]
#[should_panic(expected = "MultiTestSpec::Panic invoked")]
fn guest_error_forwarding() {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::Panic)
        .unwrap()
        .build()
        .unwrap();
    let binary = Asset::Inline(MULTI_TEST_ELF.into());
    TestClient::new().execute(env, binary);
}
