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
mod tests {

    use std::{path::Path, time::SystemTime};

    use bonsai_ethereum_relay::{
        sdk::{
            client::{CallbackRequest, Client},
            utils,
        },
        Relayer,
    };
    use bonsai_relay_contract::BonsaiTestRelay;
    use bonsai_sdk::{
        alpha::{Client as BonsaiClient, SdkErr},
        alpha_async::{get_client_from_parts, put_image},
    };
    use ethers::types::{Bytes, H256 as ethers_H256, U256};
    use ethers_signers::Signer;
    use risc0_zkvm::{MemoryImage, Program, MEM_SIZE, PAGE_SIZE};
    use risc0_zkvm_methods::{SLICE_IO_ELF, SLICE_IO_ID};
    use tokio::time::{sleep, Duration};

    const BONSAI_API_URI: &str = "http://localhost:8081";

    fn get_bonsai_url() -> String {
        let endpoint = match std::env::var("BONSAI_API_URL") {
            Ok(endpoint) => endpoint,
            Err(_) => BONSAI_API_URI.to_string(),
        };

        let bonsai_api_endpoint = endpoint
            .is_empty()
            .then(|| BONSAI_API_URI.to_string())
            .unwrap_or(endpoint);

        bonsai_api_endpoint
    }

    fn get_api_key() -> String {
        match std::env::var("BONSAI_API_KEY") {
            Ok(api_key) => api_key,
            _ => "test_key".to_string(),
        }
    }

    async fn get_bonsai_client(api_key: String) -> BonsaiClient {
        let bonsai_api_endpoint = get_bonsai_url();
        get_client_from_parts(bonsai_api_endpoint, api_key)
            .await
            .unwrap()
    }

    #[tokio::test]
    #[ignore]
    async fn e2e_test_counter() {
        // deploy the contracts
        let anvil = utils::get_anvil();
        let ethers_client = utils::get_ethers_client(
            utils::get_ws_provider(anvil.as_ref()).await.unwrap(),
            utils::get_wallet(anvil.as_ref()).unwrap(),
        )
        .await
        .unwrap();
        let bonsai_relay_contract =
            BonsaiTestRelay::deploy(ethers_client.clone(), ethers_client.signer().chain_id())
                .expect("should be able to deploy the proxy contract")
                .send()
                .await
                .expect("deployment should succeed");
        let compiled_contract =
            utils::compile_contracts(Path::new("tests/solidity/contracts")).unwrap();
        let counter = utils::deploy_contract(
            (),
            "Counter".to_string(),
            compiled_contract,
            ethers_client.clone(),
        )
        .await
        .unwrap();
        assert_eq!(
            counter
                .method::<_, U256>("value", ())
                .expect("value should be a function")
                .call()
                .await
                .expect("a call to value should succeed"),
            U256::from(0),
        );

        // run the bonsai relayer
        let relayer = Relayer {
            publish_mode: false,
            publish_port: "8080".to_string(),
            bonsai_api_url: get_bonsai_url(),
            bonsai_api_key: get_api_key(),
            relay_contract_address: bonsai_relay_contract.address(),
        };

        dbg!("starting bonsai relayer");
        tokio::spawn(relayer.run(ethers_client.clone()));

        // wait for relay to start
        sleep(Duration::from_secs(2)).await;

        // register elf
        let bonsai_client = get_bonsai_client(get_api_key()).await;
        // create the memoryImg, upload it and return the imageId
        let image_key = {
            let program =
                Program::load_elf(SLICE_IO_ELF, MEM_SIZE as u32).expect("unable to load elf");
            let image = MemoryImage::new(&program, PAGE_SIZE as u32)
                .expect("unable to create memory image");
            let image_id = hex::encode(image.compute_id());
            let image = bincode::serialize(&image).expect("Failed to serialize memory img");
            let upload_result = put_image(bonsai_client.clone(), image_id.clone(), image).await;
            match upload_result {
                Ok(_) | Err(SdkErr::ImageIdExists) => {}
                Err(_) => upload_result.expect("unable to upload result"),
            }
            image_id
        };
        dbg!(&image_key);

        // Since we are using the True Elf, the first 4 bytes need to be the length
        // of the slice (in little endian)
        let mut input = vec![0; 36];
        input[0] = 32;
        input[35] = 100;

        // Invoke the Counter contract which should request a callback through bonsai
        let gas_limit: u64 = 3000000;
        let image_id_bytes: [u8; 32] = hex::decode(image_key)
            .expect("image key should be valid hex")
            .try_into()
            .expect("hex should be 32 bytes");
        counter
            .method::<_, ()>(
                "request_callback",
                (
                    ethers_H256::from(image_id_bytes),
                    Bytes::from(input),
                    gas_limit,
                    bonsai_relay_contract.address(),
                ),
            )
            .expect("request_callback should be a function")
            .send()
            .await
            .expect("request_callback should succeed");

        let now = SystemTime::now();
        let max_seconds_to_wait = 120;
        let expected_value = U256::from(100);
        while now.elapsed().expect("error occured getting time").as_secs() < max_seconds_to_wait {
            let value = counter
                .method::<_, U256>("value", ())
                .expect("value should be a function")
                .call()
                .await
                .expect("a call to value should succeed");

            if value == expected_value {
                // noticed in dev e2e tests, this condition returns true but the
                // assertion at the end of the test fails. I believe this is because
                // Infura does not ask the same node that returned the value for this
                // call. Adding a sleep of 5 seconds to allow for nodes to sync and
                // catch up.
                dbg!("Success! Waiting 5 seconds for nodes to catch up...");
                sleep(Duration::new(5, 0)).await;
                break;
            }

            dbg!(
                format!("waiting {max_seconds_to_wait} seconds for bridge to finish"),
                now.elapsed().expect("valid time").as_secs(),
            );
            sleep(Duration::new(1, 0)).await
        }
    }

    #[tokio::test]
    #[ignore]
    async fn e2e_test_counter_publish_mode() {
        // deploy the contracts
        let anvil = utils::get_anvil();
        let ethers_client = utils::get_ethers_client(
            utils::get_ws_provider(anvil.as_ref()).await.unwrap(),
            utils::get_wallet(anvil.as_ref()).unwrap(),
        )
        .await
        .unwrap();
        let bonsai_relay_contract =
            BonsaiTestRelay::deploy(ethers_client.clone(), ethers_client.signer().chain_id())
                .expect("should be able to deploy the proxy contract")
                .send()
                .await
                .expect("deployment should succeed");
        let compiled_contract =
            utils::compile_contracts(Path::new("tests/solidity/contracts")).unwrap();
        let counter = utils::deploy_contract(
            (),
            "Counter".to_string(),
            compiled_contract,
            ethers_client.clone(),
        )
        .await
        .unwrap();
        assert_eq!(
            counter
                .method::<_, U256>("value", ())
                .expect("value should be a function")
                .call()
                .await
                .expect("a call to value should succeed"),
            U256::from(0),
        );

        // run the bonsai relayer
        let relayer = Relayer {
            publish_mode: true,
            publish_port: "8080".to_string(),
            bonsai_api_url: get_bonsai_url(),
            bonsai_api_key: get_api_key(),
            relay_contract_address: bonsai_relay_contract.address(),
        };

        dbg!("starting bonsai relayer");
        tokio::spawn(relayer.run(ethers_client.clone()));

        // wait for relay to start
        sleep(Duration::from_secs(2)).await;

        // register elf
        let bonsai_client = get_bonsai_client(get_api_key()).await;
        // create the memoryImg, upload it and return the imageId
        let program = Program::load_elf(SLICE_IO_ELF, MEM_SIZE as u32).expect("unable to load elf");
        let image =
            MemoryImage::new(&program, PAGE_SIZE as u32).expect("unable to create memory image");
        let image_id = hex::encode(image.compute_id());
        let image = bincode::serialize(&image).expect("Failed to serialize memory img");
        let upload_result = put_image(bonsai_client.clone(), image_id.clone(), image).await;
        match upload_result {
            Ok(_) | Err(SdkErr::ImageIdExists) => {}
            Err(_) => upload_result.expect("unable to upload result"),
        }

        // Since we are using the True Elf, the first 4 bytes need to be the length
        // of the slice (in little endian)
        let mut input = vec![0; 36];
        input[0] = 32;
        input[35] = 100;

        // Invoke the Counter contract which should request a callback through bonsai
        let gas_limit: u64 = 3000000;
        let image_id: [u8; 32] = bytemuck::cast(SLICE_IO_ID);
        let request = CallbackRequest {
            callback_contract: counter.address(),
            function_selector: [0xff, 0x58, 0x5c, 0xaf],
            gas_limit,
            image_id,
            input,
        };

        let relay_client =
            Client::from_parts("http://localhost:8080".to_string(), get_api_key()).unwrap();

        relay_client
            .callback_request(request)
            .await
            .expect("Callback request failed");

        let now = SystemTime::now();
        let max_seconds_to_wait = 120;
        let expected_value = U256::from(100);
        while now.elapsed().expect("error occured getting time").as_secs() < max_seconds_to_wait {
            let value = counter
                .method::<_, U256>("value", ())
                .expect("value should be a function")
                .call()
                .await
                .expect("a call to value should succeed");

            if value == expected_value {
                // noticed in dev e2e tests, this condition returns true but the
                // assertion at the end of the test fails. I believe this is because
                // Infura does not ask the same node that returned the value for this
                // call. Adding a sleep of 5 seconds to allow for nodes to sync and
                // catch up.
                dbg!("Success! Waiting 5 seconds for nodes to catch up...");
                sleep(Duration::new(5, 0)).await;
                break;
            }

            dbg!(
                format!("waiting {max_seconds_to_wait} seconds for bridge to finish"),
                now.elapsed().expect("valid time").as_secs(),
            );
            sleep(Duration::new(1, 0)).await
        }
    }
}
