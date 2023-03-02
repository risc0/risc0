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

use std::error::Error;
use std::ops::Deref;
use std::str::FromStr;
use std::sync::Arc;

use clap::Parser;
use ethers::middleware::SignerMiddleware;
use ethers::providers::{Http, Middleware, Provider};
use ethers::signers::{LocalWallet, Signer};
use ethers::types::{Address, H256};
use hello_bonsai_contracts::HelloBonsai;
use hello_bonsai_methods::{FIBONACCI_ELF, FIBONACCI_ID};
use reqwest::{Client, Url};
use risc0_zkvm::sha::{self, Digest, Sha256};

#[derive(Parser, Debug)]
#[clap(author, version, about, long_about = None)]
struct Args {
    /// JSON RPC URL for an Ethereum node that will serve call and transaction requests.
    /// Currently only HTTP(S) URLs are supported.
    #[clap(short = 'e', long, env, value_hint = clap::ValueHint::Url)]
    ethereum_node_url: String,

    /// URL for the Bonsai service for to upload the ELF binary.
    #[clap(short = 'b', long, env, value_hint = clap::ValueHint::Url)]
    bonsai_url: String,

    /// Ethereum contract address for the Bonsai proxy.
    #[clap(short = 'p', long, env)]
    bonsai_proxy_contract_address: Address,

    /// API Key for Bonsai to authorize requests.
    #[clap(env, long)]
    bonsai_api_key: String,

    /// Ethereum private key to use for sending transactions.
    // NOTE: Provided as an example and for testing. Integrate your preferred key management.
    // https://docs.rs/ethers/latest/ethers/signers/index.html
    #[clap(env, long)]
    ethereum_private_key: String,
}

async fn upload_elf(
    bonsai_url: &Url,
    bonsai_api_key: &str,
    elf: &'static [u8],
) -> Result<String, Box<dyn Error>> {
    let elf_hash = hex::encode(sha::Impl::hash_bytes(elf).deref());
    Client::new()
        .put(bonsai_url.join(&format!("/v1/elf/{elf_hash}"))?)
        .bearer_auth(bonsai_api_key)
        .header("Content-Type", "application/octet-stream")
        .header("Expect", "100-continue")
        .body(elf)
        .send()
        .await?
        .error_for_status()?;

    Ok(elf_hash)
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn Error>> {
    let args = Args::parse();

    // Create a wallet and connection to the Ethereum node.
    let wallet = LocalWallet::from_str(args.ethereum_private_key.trim_start_matches("0x"))?;
    let provider = Provider::<Http>::try_from(&args.ethereum_node_url)?;
    let chain_id = provider.get_chainid().await?;
    println!("Loaded private key for Ethereum wallet");
    println!("    Wallet address: {:?}", wallet.address());

    let client = Arc::new(SignerMiddleware::new(
        provider,
        wallet.with_chain_id(chain_id.as_u64()),
    ));

    // Upload the guest binary to Bonsai.
    println!("Uploading guest binary to Bonsai...");
    let elf_hash = upload_elf(
        &Url::parse(&args.bonsai_url)?,
        &args.bonsai_api_key,
        FIBONACCI_ELF,
    )
    .await?;
    println!("Uploaded guest binary");
    println!("    SHA-256:  {}", elf_hash);
    println!("    Image ID: {}", hex::encode(Digest::from(FIBONACCI_ID)));

    // Deploy the HelloBonsai contract.
    println!("Deploying guest binary to Bonsai...");
    let hello_bonsai = HelloBonsai::deploy(
        client.clone(),
        (
            args.bonsai_proxy_contract_address,
            H256(Digest::from(FIBONACCI_ID).into()),
        ),
    )?
    .send()
    .await?;
    println!("Deployed HelloBonsai contract at");
    println!("    HelloBonsai address: {:?}", hello_bonsai.address());

    Ok(())
}
