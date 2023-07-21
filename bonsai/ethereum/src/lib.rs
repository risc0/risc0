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

//! Specifies the Bonsai Relay Ethereum contract and provides
//! structures and procedures for programmatic deployment of and interaction
//! with a `Proxy` contract instance on Ethereum.

use ethers::prelude::*;

abigen!(BonsaiRelay, "out/BonsaiRelay.sol/BonsaiRelay.json");
abigen!(
    BonsaiTestRelay,
    "out/BonsaiTestRelay.sol/BonsaiTestRelay.json"
);

#[derive(Clone, Debug)]
pub struct BonsaiRelayCallback {
    pub auth: CallbackAuthorization,
    pub callback_request: bonsai_relay::CallbackRequestFilter,
    pub payload: Vec<u8>,
    pub gas_limit: u64,
}

impl From<BonsaiRelayCallback> for bonsai_relay::Callback {
    fn from(value: BonsaiRelayCallback) -> Self {
        let payload = [
            value.callback_request.function_selector.as_slice(),
            value.payload.as_slice(),
            value.callback_request.image_id.as_slice(),
        ]
        .concat();
        Self {
            auth: value.auth,
            callback_contract: value.callback_request.callback_contract,
            payload: payload.into(),
            gas_limit: value.gas_limit,
        }
    }
}

#[cfg(test)]
mod tests {

    use std::{sync::Arc, time::Duration};

    use ethers::{
        abi::{ethereum_types::Secret, AbiEncode},
        prelude::{
            k256::{ecdsa::SigningKey, SecretKey},
            *,
        },
        utils::{hex, Anvil, AnvilInstance},
    };
    use risc0_zkvm::SessionReceipt;

    abigen!(CallbackDummy, "out/callback_dummy.sol/CallbackDummy.json");

    async fn get_client() -> (
        Option<AnvilInstance>,
        Arc<SignerMiddleware<Provider<ethers::providers::Ws>, Wallet<SigningKey>>>,
    ) {
        match (
            std::env::var("ETHEREUM_HOST"),
            std::env::var("TEST_PRIVATE_KEY"),
        ) {
            (Ok(endpoint), Ok(test_private_key)) => {
                // Connect to provider
                let provider = Provider::<Ws>::connect(endpoint)
                    .await
                    .unwrap()
                    .interval(Duration::from_millis(10u64));

                // Derive wallet
                let wallet_sk_bytes = hex::decode(test_private_key.trim_start_matches("0x"))
                    .expect("Could not decode input wallet secret key.");
                let wallet_secret_key = SecretKey::from_slice(&wallet_sk_bytes)
                    .expect("Failed to derive SecretKey instance from input.");
                let wallet_signing_key = SigningKey::from(wallet_secret_key);
                let wallet = LocalWallet::from(wallet_signing_key);

                (
                    None,
                    Arc::new(SignerMiddleware::new(
                        provider,
                        wallet.with_chain_id(1337u64),
                    )),
                )
            }
            _ => {
                // Launch anvil instance
                let anvil = Anvil::new().spawn();

                // Get provider endpoint
                let endpoint = anvil.ws_endpoint();

                // Instantiate wallet
                let wallet: LocalWallet =
                    LocalWallet::from(anvil.keys()[0].clone()).with_chain_id(anvil.chain_id());

                // Connect to network

                let provider = Provider::<Ws>::connect(&endpoint)
                    .await
                    .unwrap()
                    .interval(Duration::from_millis(10u64));

                // Instantiate client as wallet on network
                (
                    Some(anvil),
                    Arc::new(SignerMiddleware::new(provider, wallet)),
                )
            }
        }
    }

    #[tokio::test]
    pub async fn test_happy_path() {
        let (_anvil, client) = get_client().await;
        let wallet_address = client.address();

        // Deploy Bonsai Test Relay contract
        let test_relay_contract = BonsaiTestRelay::deploy(client.clone(), ())
            .expect("Failed to create Proxy deployment tx")
            .send()
            .await
            .expect("Failed to send Proxy deployment tx");
        assert_eq!(
            client
                .get_balance(test_relay_contract.address(), None)
                .await
                .unwrap(),
            U256::zero()
        );

        let image_id: [u8; 32] = [0xf2; 32];

        // Deploy dummy Callback contract
        let dummy_callback =
            CallbackDummy::deploy(client.clone(), (image_id, test_relay_contract.address()))
                .unwrap()
                .send()
                .await
                .unwrap();

        let call_me_selector = CallMeCall::selector();
        // Create some dummy callback requests
        let callback_requests = vec![
            bonsai_test_relay::CallbackRequestFilter {
                account: wallet_address.into(),
                image_id: image_id.clone(),
                input: Vec::new().into(),
                callback_contract: dummy_callback.address(),
                function_selector: call_me_selector.clone(),
                gas_limit: 50000,
            },
            bonsai_test_relay::CallbackRequestFilter {
                account: wallet_address.into(),
                image_id: image_id.clone(),
                input: Vec::new().into(),
                callback_contract: dummy_callback.address(),
                function_selector: call_me_selector.clone(),
                gas_limit: 50000,
            },
        ];

        // Send both proof requests to the proxy
        for request in callback_requests.clone() {
            test_relay_contract
                .request_callback(
                    request.image_id,
                    request.input,
                    request.callback_contract,
                    request.function_selector,
                    request.gas_limit,
                )
                .send()
                .await
                .expect("Failed to submit proof request");
        }
        // Ensure callback contract is not affected yet
        assert_eq!(
            dummy_callback
                .counter()
                .call()
                .await
                .expect("Failed to get counter value"),
            U256::zero()
        );

        let call_me_call = CallMeCall {
            number: U256::from(1),
            guess: true,
            callback_image_id: Secret::zero().0,
        };

        let fake_receipt = SessionReceipt {
            segments: Vec::new(),
            journal: call_me_call.encode()[4..4 + 32 + 32].to_vec(),
        };

        let ethereum_callbacks = vec![
            bonsai_test_relay::Callback {
                payload: fake_receipt.journal.clone(),
                gas_limit: 50000,
                callback_request: callback_requests[0].clone(),
            },
            bonsai_test_relay::Callback {
                payload: fake_receipt.journal,
                gas_limit: 50000,
                callback_request: callback_requests[1].clone(),
            },
        ];
        dbg!(&ethereum_callbacks);

        // Submit responses
        let callbacks = ethereum_callbacks.into_iter().map(|p| p.into()).collect();
        let invocation_transaction = test_relay_contract
            .invoke_callbacks(callbacks)
            .send()
            .await
            .expect("Failed to submit proof bundle")
            .await
            .expect("Failed to submit proof bundle")
            .expect("Failed to retrieve transaction receipt");
        dbg!(invocation_transaction);
        // Ensure callback contract counter has been increased twice
        assert_eq!(
            dummy_callback
                .counter()
                .call()
                .await
                .expect("Failed to get counter value"),
            U256::from(2)
        );
    }
}
