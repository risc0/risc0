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

#[cfg(test)]
pub(crate) mod tests {
    use bonsai_ethereum_contracts::i_bonsai_relay::CallbackRequestFilter;
    use bonsai_sdk::alpha::{
        responses::{CreateSessRes, SessionStatusRes, SnarkProof, SnarkStatusRes},
        SessionId,
    };
    use ethers::types::{Address, Bytes, H256, U256};
    use risc0_zkvm::{receipt::InnerReceipt, Receipt};
    use uuid::Uuid;
    use wiremock::{
        matchers::{method, path},
        Mock, MockServer, ResponseTemplate,
    };

    use crate::downloader::event_processor::EventProcessor;

    pub(crate) async fn get_test_bonsai_server() -> (SessionId, MockServer) {
        // Mock API server
        let server = MockServer::start().await;

        let receipt_id = Uuid::new_v4();

        // Mock receipt response
        let status_response = SessionStatusRes {
            status: "SUCCEEDED".to_string(),
            receipt_url: Some(format!("{}/fake/receipt/path", server.uri())),
        };

        let receipt_data_response = Receipt {
            journal: vec![],
            inner: InnerReceipt::Fake,
        };

        let create_snark_res = CreateSessRes {
            uuid: receipt_id.to_string(),
        };
        let zeroes = &U256::zero().to_string();
        let a = vec![zeroes.to_string(), zeroes.to_string()];
        let b = vec![
            vec![zeroes.to_string(), zeroes.to_string()],
            vec![zeroes.to_string(), zeroes.to_string()],
        ];
        let c = vec![zeroes.to_string(), zeroes.to_string()];
        let public = vec![
            zeroes.to_string(),
            zeroes.to_string(),
            zeroes.to_string(),
            zeroes.to_string(),
        ];
        let dummy_snark = Some(SnarkProof { a, b, c, public });
        let snark_status_res = SnarkStatusRes {
            status: "SUCCEEDED".to_string(),
            output: dummy_snark,
        };

        Mock::given(method("POST"))
            .and(path(format!("inputs/upload")))
            .respond_with(ResponseTemplate::new(200).set_body_json(&receipt_id))
            .mount(&server)
            .await;

        Mock::given(method("GET"))
            .and(path(format!("sessions/status/{receipt_id}")))
            .respond_with(ResponseTemplate::new(200).set_body_json(&status_response))
            .mount(&server)
            .await;

        Mock::given(method("POST"))
            .and(path(format!("snark/create")))
            .respond_with(ResponseTemplate::new(200).set_body_json(&create_snark_res))
            .mount(&server)
            .await;

        Mock::given(method("GET"))
            .and(path(format!("snark/status/{receipt_id}")))
            .respond_with(ResponseTemplate::new(200).set_body_json(&snark_status_res))
            .mount(&server)
            .await;

        Mock::given(method("GET"))
            .and(path(format!("fake/receipt/path")))
            .respond_with(
                ResponseTemplate::new(200)
                    .set_body_bytes(bincode::serialize(&receipt_data_response).unwrap()),
            )
            .mount(&server)
            .await;

        (SessionId::new(receipt_id.to_string()), server)
    }

    pub(crate) struct TestAddressTopicCallbackProofRequestProcessor {
        pub expected_account: Address,
        pub expected_image_id: H256,
        pub expected_input: Bytes,
        pub expected_callback_contract: Address,
    }

    #[async_trait::async_trait]
    impl EventProcessor for TestAddressTopicCallbackProofRequestProcessor {
        type Event = CallbackRequestFilter;

        async fn process_event(
            &self,
            event: CallbackRequestFilter,
        ) -> Result<(), crate::api::error::Error> {
            assert_eq!(event.account, self.expected_account);
            assert_eq!(H256::from(event.image_id), self.expected_image_id);
            assert_eq!(event.input, self.expected_input);
            assert_eq!(event.callback_contract, self.expected_callback_contract);

            // Throwing an error signals for the runner loop to stop.
            Err(anyhow::anyhow!("terminate success").into())
        }
    }
}
