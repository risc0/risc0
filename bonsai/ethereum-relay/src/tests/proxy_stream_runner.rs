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

use crate::downloader::proxy_callback_proof_request_stream::ProxyCallbackProofRequestStream;
use ethers::types::{Bytes, H160, H256};

#[tokio::test]
async fn integration_test_proxy_stream_runner() {
    let anvil = utils::get_anvil();
    let client = utils::get_ethers_client(
        utils::get_ws_provider(anvil.as_ref()).await,
        utils::get_wallet(anvil.as_ref()),
    )
    .await;

    let proxy = utils::deploy_proxy_contract(client.clone()).await;

    // create an event
    let fake_image_id: [u8; 32] =
        hex::decode("de11d9df3349a60bec5cd7271dc81d4f8c7089921b0b645f21d333e818b14d32")
            .expect("should be valid hex")
            .try_into()
            .expect("should be 32 bytes");

    let fake_address: [u8; 20] = hex::decode("9ebda139eba69a5d232828bfd551ab80d0cebf05")
        .expect("should be valid hex")
        .try_into()
        .expect("should be 20 bytes");

    let processor = utils::test_callback_proof_request_processor::TestAddressTopicCallbackProofRequestProcessor {
        expected_account: client.address(),
        expected_image_id: H256::from(fake_image_id),
        expected_input: Bytes::from("hello world".to_string().as_bytes().to_vec()),
        expected_callback_contract: H160::from(fake_address),
    };

    let runner = ProxyCallbackProofRequestStream::new(client.clone(), proxy.address(), processor);
    let runner_handle = tokio::spawn(runner.run());

    let function_selector: [u8; 4] = [0xab, 0xcd, 0xef, 0xab];
    let gas_limit: u64 = 3000000;
    proxy
        .method::<_, ()>(
            "requestCallback",
            (
                H256::from(fake_image_id),
                Bytes::from("hello world".to_string().as_bytes().to_vec()),
                H160::from(fake_address),
                function_selector,
                gas_limit,
            ),
        )
        .expect("requestCallback should be a valid function")
        .send()
        .await
        .unwrap()
        .await
        .unwrap();

    assert!(match runner_handle
        .await
        .expect("tokio task should have succeeded")
    {
        Err(ethereum_relay::api::error::Error::Unspecified(source)) => {
            source.to_string() == "terminate success"
        }
        _ => false,
    });
}
