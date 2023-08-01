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

use std::{path::Path, sync::Arc};

use anyhow::{anyhow, Context, Result};
use ethers::{
    abi::Tokenize,
    prelude::{
        k256::{ecdsa::SigningKey, SecretKey},
        *,
    },
    providers::{Http, Provider, Ws},
    signers::{LocalWallet, Signer},
    solc::{CompilerOutput, Solc},
    utils::AnvilInstance,
};

const POLL_INTERVAL: std::time::Duration = std::time::Duration::from_secs(1);

pub(crate) type Client<P> = Arc<SignerMiddleware<Provider<P>, LocalWallet>>;

/// Returns a [LocalWallet] derived from either a private key as a hex string,
/// or an AWS KMS key identifier defined by the env variable
/// `WALLET_KEY_IDENTIFIER`. If no key is set, returns a new [LocalWallet] from
/// the given optional `anvil` instance.
pub fn get_wallet(anvil: Option<&AnvilInstance>) -> Result<Wallet<SigningKey>> {
    match std::env::var("WALLET_KEY_IDENTIFIER") {
        Ok(test_private_key) => {
            // Derive wallet
            let wallet_sk_bytes = hex::decode(test_private_key.trim_start_matches("0x"))
                .context("Could not decode input wallet secret key.")?;
            let wallet_secret_key = SecretKey::from_slice(&wallet_sk_bytes)
                .context("Failed to derive SecretKey instance from input.")?;
            let wallet_signing_key = SigningKey::from(wallet_secret_key);
            Ok(LocalWallet::from(wallet_signing_key))
        }
        _ => {
            let anvil = anvil.context("Anvil not instantiated.")?;
            Ok(LocalWallet::from(anvil.keys()[0].clone()).with_chain_id(anvil.chain_id()))
        }
    }
}

/// Returns an abstract provider for interacting with the Ethereum JSON RPC API
/// over HTTP.
pub fn get_http_provider(anvil: Option<&AnvilInstance>) -> Result<Provider<Http>> {
    let endpoint = match std::env::var("ETHEREUM_HOST") {
        Ok(ethereum_host) => format!("http://{ethereum_host}"),
        _ => anvil.context("Anvil not instantiated.")?.endpoint(),
    };
    Ok(Provider::<Http>::try_from(endpoint)
        .context("could not connect to {endpoint}")?
        .interval(POLL_INTERVAL))
}

/// Returns an abstract provider for interacting with the Ethereum JSON RPC API
/// over Websockets.
pub async fn get_ws_provider(anvil: Option<&AnvilInstance>) -> Result<Provider<Ws>> {
    let endpoint = match std::env::var("ETHEREUM_HOST") {
        Ok(ethereum_host) => format!("ws://{ethereum_host}"),
        _ => anvil.context("Anvil not instantiated.")?.ws_endpoint(),
    };
    Ok(Provider::<Ws>::connect(&endpoint)
        .await
        .context("could not connect to {endpoint}")?
        .interval(POLL_INTERVAL))
}

/// Returns an Ethereum Client Middleware used for locally signing transactions.
pub async fn get_ethers_client<P: JsonRpcClient>(
    provider: Provider<P>,
    wallet: LocalWallet,
) -> Result<Client<P>> {
    let chain_id = provider
        .get_chainid()
        .await
        .context("could not get chain id")?
        .as_u64();
    Ok(Arc::new(SignerMiddleware::new(
        provider,
        wallet.with_chain_id(chain_id),
    )))
}

/// Returns an empty Anvil builder. The default port is 8545. The mnemonic is
/// chosen randomly.
pub fn get_anvil() -> Option<AnvilInstance> {
    match std::env::var("ETHEREUM_HOST") {
        Ok(_) => None,
        _ => Some(ethers::utils::Anvil::new().spawn()),
    }
}

/// Constructs the deployment transaction of the contract based on
/// the provided constructor arguments and returns a Deployer instance.
/// You must call send() in order to actually deploy the contract.
/// Notes:
///
/// If there are no constructor arguments, you should pass () as the argument.
pub async fn deploy_contract<T: Tokenize, M: Middleware, S: Signer>(
    constructor_args: T,
    contract_name: String,
    compiled: CompilerOutput,
    signer: Arc<SignerMiddleware<M, S>>,
) -> Result<ethers::contract::Contract<SignerMiddleware<M, S>>> {
    let (abi, bytecode, _runtime_bytecode) = compiled
        .find(contract_name.clone())
        .context(format!(
            "could not find contract {} in compiler output",
            contract_name.clone()
        ))?
        .into_parts_or_default();

    let client = signer;
    let factory = ContractFactory::new(abi, bytecode, client.clone());
    factory
        .deploy(constructor_args)
        .map_err(|err| {
            anyhow!(format!(
                "constructing deploy transaction failed for {} - {}",
                contract_name.clone(),
                err
            ))
        })?
        .send()
        .await
        .map_err(|err| {
            anyhow!(format!(
                "deployed failed for {} - {}",
                contract_name.clone(),
                err
            ))
        })
}

/// Convenience function for compiling all sources under the given path.
pub fn compile_contracts(path: &Path) -> Result<CompilerOutput> {
    let compiled = Solc::default().compile_source(path)?;
    Ok(compiled)
}
