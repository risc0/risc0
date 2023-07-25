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

    use std::path::Path;

    use ethers::types::{Log, U256};
    use futures::StreamExt as _;

    use crate::{sdk::utils, tests::utils::tests::EventStream};

    #[tokio::test]
    async fn integration_test_http_events() {
        // Get Anvil
        let anvil = utils::get_anvil();

        // Get client config
        let ethers_client_config = utils::get_ethers_client_config(anvil.as_ref()).await.expect("Failed to get ethers client config");

        let provider = utils::get_http_provider(anvil.as_ref()).unwrap();

        let data: Vec<U256> = Vec::from([
            123.into(),
            643253.into(),
            564.into(),
            2324.into(),
            4356.into(),
        ]);
        let compiled_contract =
            utils::compile_contracts(Path::new("tests/solidity/contracts")).unwrap();
        let logger =
            utils::deploy_contract((), "Logger".to_string(), compiled_contract, ethers_client_config.clone())
                .await
                .unwrap();
        let stream = EventStream::new(provider, logger.address()).from_block(0);
        for number in data.clone() {
            logger
                .method::<_, ()>("log", number)
                .expect("log should be a valid function")
                .send()
                .await
                .unwrap()
                .await
                .unwrap();
        }
        let logs: Vec<Log> = stream.poll().await.take(data.len()).collect().await;
        let results: Vec<U256> = logs
            .into_iter()
            .map(|log| U256::from_big_endian(&log.data))
            .collect();
        assert_eq!(results, data);
    }

    #[tokio::test]
    async fn integration_test_ws_events() {
        // Get Anvil
        let anvil = utils::get_anvil();

        // Get client config
        let ethers_client_config = utils::get_ethers_client_config(anvil.as_ref()).await.expect("Failed to get ethers client config");

        let provider = utils::get_ws_provider(anvil.as_ref()).await.unwrap();
        let data: Vec<U256> = Vec::from([
            123.into(),
            643253.into(),
            564.into(),
            2324.into(),
            4356.into(),
        ]);

        let compiled_contract =
            utils::compile_contracts(Path::new("tests/solidity/contracts")).unwrap();
        let logger =
            utils::deploy_contract((), "Logger".to_string(), compiled_contract, ethers_client_config.clone())
                .await
                .unwrap();
        for number in data.clone() {
            logger
                .method::<_, ()>("log", number)
                .expect("log should be a valid function")
                .send()
                .await
                .unwrap()
                .await
                .unwrap();
        }
        let stream = EventStream::new(provider, logger.address()).from_block(0);
        let logs: Vec<Log> = stream.watch().await.take(data.len()).collect().await;
        let results: Vec<U256> = logs
            .into_iter()
            .map(|log| U256::from_big_endian(&log.data))
            .collect();
        assert_eq!(results, data);
    }
}
