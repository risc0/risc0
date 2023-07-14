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

use std::io::Write;

use anyhow::Context;
use bonsai_ethereum_relay::{resolve_guest_entry, resolve_image_output, Output, ProverMode};
use bonsai_sdk_alpha::alpha::responses::SnarkProof;
use bonsai_starter_methods::GUEST_LIST;
use clap::{Parser, Subcommand};
use ethers::{
    abi::{Hash, Token, Tokenizable},
    types::U256,
};

#[derive(Subcommand)]
pub enum Command {
    /// Runs the RISC-V ELF binary.
    Query {
        /// The name of the guest binary
        guest_binary: String,

        /// The input to provide to the guest binary
        input: Option<String>,

        #[arg(long, env = "BONSAI_PROVING", value_enum, default_value_t = ProverMode::None)]
        prover_mode: ProverMode,
    },
}

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Args {
    #[command(subcommand)]
    command: Command,
}

/// Parse a slice of strings as a fixed array of uint256 tokens.
fn parse_to_tokens(slice: &[String]) -> anyhow::Result<Token> {
    Ok(Token::FixedArray(
        slice
            .iter()
            .map(|s| -> anyhow::Result<_> { Ok(U256::from_str_radix(s, 16)?.into_token()) })
            .collect::<Result<Vec<_>, _>>()?,
    ))
}

fn tokenize_snark_proof(proof: &SnarkProof) -> anyhow::Result<Token> {
    if proof.b.len() != 2 {
        anyhow::bail!("hex-strings encoded proof is not well formed");
    }
    for pair in [&proof.a, &proof.c].into_iter().chain(proof.b.iter()) {
        if pair.len() != 2 {
            anyhow::bail!("hex-strings encoded proof is not well formed");
        }
    }
    Ok(Token::FixedArray(vec![
        parse_to_tokens(&proof.a)?,
        Token::FixedArray(vec![
            parse_to_tokens(&proof.b[0])?,
            parse_to_tokens(&proof.b[1])?,
        ]),
        parse_to_tokens(&proof.c)?,
    ]))
}

#[tokio::main]
async fn main() -> anyhow::Result<()> {
    let args = Args::parse();

    match args.command {
        Command::Query {
            guest_binary,
            input,
            prover_mode,
        } => {
            // Search list for requested binary name
            let guest_entry = resolve_guest_entry(GUEST_LIST, &guest_binary)
                .context("failed to resolve guest entry")?;

            // Execute or return image id
            let output_tokens = match &input {
                // Input provided. Return the Ethereum ABI encoded journal and
                Some(input) => {
                    let output = resolve_image_output(input, guest_entry, prover_mode)
                        .await
                        .context("failed to resolve image output")?;
                    match (prover_mode, output) {
                        (ProverMode::None, Output::Execution { journal }) => {
                            vec![Token::Bytes(journal)]
                        }
                        (ProverMode::Local, Output::Execution { journal }) => {
                            vec![Token::Bytes(journal)]
                        }
                        (
                            ProverMode::Bonsai,
                            Output::Bonsai {
                                journal,
                                receipt_metadata,
                                snark_proof,
                            },
                        ) => {
                            vec![
                                Token::Bytes(journal),
                                Hash::from(<[u8; 32]>::from(receipt_metadata.post.digest()))
                                    .into_token(),
                                tokenize_snark_proof(&snark_proof)?,
                            ]
                        }
                        _ => anyhow::bail!(
                            "invalid prover mode and output combination: {:?}",
                            prover_mode
                        ),
                    }
                }
                // No input. Return the Ethereum ABI encoded bytes32 image ID.
                None => vec![
                    Hash::from(bytemuck::cast::<_, [u8; 32]>(guest_entry.image_id)).into_token(),
                ],
            };

            let output = hex::encode(ethers::abi::encode(&output_tokens));
            print!("{output}");
            std::io::stdout()
                .flush()
                .context("failed to flush stdout buffer")?;
        }
    }
    Ok(())
}
