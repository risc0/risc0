// Copyright 2025 RISC Zero, Inc.
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

// This is based on cargo-wasix: https://github.com/wasix-org/cargo-wasix

use anyhow::{Context, Result};
use bonsai_sdk::{blocking::Client, API_KEY_ENVVAR, API_URL_ENVVAR};
use clap::Args;
use risc0_zkvm::VERSION;

#[derive(Debug, Clone, Default, Args, PartialEq, Eq)]
#[group(multiple = false)]
pub struct ClientEnvs {
    /// API URL for Bonsai.
    #[arg(long)]
    pub api_url: Option<String>,

    /// API key for Bonsai.
    #[arg(long)]
    pub api_key: Option<String>,
}

pub(crate) fn get_client(client_envs: &ClientEnvs) -> Result<Client> {
    let (api_url, api_key) = get_client_envs(client_envs)?;

    Client::from_parts(api_url, api_key, VERSION).context("Failed to create Bonsai client")
}

pub(crate) fn get_client_envs(client_envs: &ClientEnvs) -> Result<(String, String)> {
    let api_url = if let Some(ref api_url) = client_envs.api_url {
        api_url.to_string()
    } else {
        std::env::var(API_URL_ENVVAR).context(format!(
            "Either `--api-url` or `{API_URL_ENVVAR}` env var must be set",
        ))?
    };

    let api_key = if let Some(ref api_key) = client_envs.api_key {
        api_key.to_string()
    } else {
        std::env::var(API_KEY_ENVVAR).context(format!(
            "Either `--api-key` or `{API_KEY_ENVVAR}` env var must be set",
        ))?
    };

    Ok((api_url, api_key))
}
