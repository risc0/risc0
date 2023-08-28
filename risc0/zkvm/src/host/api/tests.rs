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

use anyhow::Result;
use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_PATH};
use std::{net::TcpListener, thread};

use super::{pb, ConnectionWrapper, Connector, TcpConnection};
use crate::{serde::to_vec, ApiClient, ApiServer, ExecutorEnv};

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

#[test_log::test]
fn basic() {
    let client_connector = TestClientConnector::new().unwrap();
    let addr = client_connector.listener.local_addr().unwrap();

    let client_handle = thread::Builder::new()
        .name("client".into())
        .spawn(move || {
            let input = to_vec(&MultiTestSpec::DoNothing).unwrap();
            let env = ExecutorEnv::builder().add_input(&input).build().unwrap();
            let binary = pb::Binary {
                kind: pb::BinaryType::Elf as i32,
                asset: Some(pb::Asset {
                    kind: Some(pb::AssetKind::Path(MULTI_TEST_PATH.into())),
                }),
            };
            let segments = pb::AssetRequest {
                kind: pb::AssetRequestKind::Path as i32,
            };

            let client = ApiClient::new(Box::new(client_connector));
            client
                .execute(&env, binary, segments, |segment| {
                    println!("segment: {}", segment.index);
                    Ok(())
                })
                .unwrap();
        })
        .unwrap();
    let server_handle = thread::Builder::new()
        .name("server".into())
        .spawn(move || {
            let server = ApiServer::new_tcp(addr.to_string());
            server.run().unwrap();
        })
        .unwrap();

    client_handle.join().unwrap();
    server_handle.join().unwrap();
}
