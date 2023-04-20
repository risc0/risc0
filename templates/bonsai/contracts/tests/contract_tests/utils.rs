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

//! Utilities for writing tests for Bonsai applications. Supports testing of
//! applications that use the Bonsai proxy to make requests for processing by a
//! RISC Zero guest by providing utilities to run a mock of Bonsai.

use std::{collections::HashMap, error::Error, future::Future, ops::Deref, sync::Arc};

use ethers::{
    core::k256::ecdsa::SigningKey,
    prelude::*,
    utils::{Ganache, GanacheInstance},
};
use risc0_zkvm::{sha::Digest, Executor, ExecutorEnv};
use tokio::{sync::oneshot, task::JoinHandle};

abigen!(
    MockBonsaiProxy,
    "artifacts/MockBonsaiProxy.sol/MockBonsaiProxy.json"
);

pub type Client = Arc<SignerMiddleware<Provider<Ws>, Wallet<SigningKey>>>;

pub async fn get_ganache_client() -> Result<(GanacheInstance, Client), Box<dyn Error>> {
    // Launch Ganache instance
    let ganache = Ganache::new().spawn();

    // Instantiate wallet
    let wallet: LocalWallet = ganache.keys()[0].clone().into();

    // Connect to Ganache
    let provider = Provider::<Ws>::connect(ganache.ws_endpoint()).await?;

    // Instantiate client as wallet on network
    let client = Arc::new(SignerMiddleware::new(
        provider,
        wallet.with_chain_id(1337u64),
    ));

    Ok((ganache, client))
}

pub struct BonsaiMock {
    pub contract_address: Address,
    pub task_handle: JoinHandle<()>,
}

impl BonsaiMock {
    pub async fn spawn<Bytes: AsRef<[u8]> + Send + 'static>(
        client: Client,
        registry: HashMap<Digest, Bytes>,
    ) -> Result<Self, Box<dyn Error>> {
        let (tx, rx) = oneshot::channel();

        let task_handle: JoinHandle<()> = tokio::spawn(async move {
            // Deploy the MockBonsaiProxy
            let mock_bonsai_proxy = MockBonsaiProxy::deploy(client.clone(), ())
                .unwrap()
                .send()
                .await
                .unwrap();

            let events = mock_bonsai_proxy.events();
            let mut subscription = events.subscribe().await.unwrap();
            tx.send(mock_bonsai_proxy.address()).unwrap();

            while let Some(event) = subscription.next().await {
                let submit_request_log =
                    event.expect("error in getting next event from subscription");
                let session = {
                    let elf = registry
                        .get(&Digest::from(submit_request_log.image_id))
                        .expect(&format!(
                            "image ID not found in registry: {:x?}",
                            submit_request_log.image_id
                        ));
                    let input = submit_request_log.input;
                    let env = ExecutorEnv::builder().add_input(input.deref()).build();
                    let mut exec = Executor::from_elf(env, elf.as_ref()).unwrap();
                    exec.run().unwrap()
                };

                mock_bonsai_proxy
                    .send_callback(
                        submit_request_log.callback_address,
                        submit_request_log.image_id.into(),
                        session.journal.into(),
                    )
                    .send()
                    .await
                    .expect("failed to send callback");
            }
            panic!("unexpected end of event stream");
        });

        // Wait for the contract to be deployed, then return the mock.
        Ok(Self {
            contract_address: rx.await.unwrap(),
            task_handle,
        })
    }
}

pub async fn bonsai_test<F, Bytes>(
    registry: HashMap<Digest, Bytes>,
    test: impl FnOnce(Client, Address) -> F,
) -> Result<(), Box<dyn Error>>
where
    F: Future<Output = Result<(), Box<dyn Error>>>,
    Bytes: AsRef<[u8]> + Send + 'static,
{
    // Instantiate client as wallet on network
    let (_ganache, client) = get_ganache_client().await?;

    // Deploy the Bonsai mock contract and start a background worker.
    let mut bonsai_mock = BonsaiMock::spawn(client.clone(), registry).await?;

    // Run the test inside `tokio::select` such that it will exit if the mock exits.
    tokio::select! {
        result = test(client.clone(), bonsai_mock.contract_address) => result,
        error = &mut bonsai_mock.task_handle => Err(format!("Bonsai mock died with result: {:?}", error).into()),
    }
}
