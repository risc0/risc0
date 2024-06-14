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

use anyhow::{Context, Result};
use reqwest::Client;
use serde::Deserialize;

pub fn handle_check_all() -> Result<()> {
    let client = Client::builder().user_agent("rzup").build()?;

    let rust_repo = "https://api.github.com/repos/risc0/rust/releases/latest";
    let cpp_repo = "https://api.github.com/repos/risc0/toolchain/releases/latest";
    let cargo_risczero_repo = "https://api.github.com/repos/risc0/risc0/releases/latest";

    let rt = tokio::runtime::Runtime::new()?;

    let cargo_risczero_data =
        rt.block_on(fetch_latest_release_info(&client, cargo_risczero_repo))?;
    let rust_release_data = rt.block_on(fetch_latest_release_info(&client, rust_repo))?;
    let cpp_release_data = rt.block_on(fetch_latest_release_info(&client, cpp_repo))?;

    // TODO: Clean up and make pretty
    println!(
        "Latest cargo-risczero release: {} : ({})",
        cargo_risczero_data.tag_name, cargo_risczero_data.published_at
    );
    println!(
        "Latest Rust release: {} : ({})",
        rust_release_data.tag_name, rust_release_data.published_at
    );
    println!(
        "Latest C++ release: {} : ({})",
        cpp_release_data.tag_name, cpp_release_data.published_at
    );

    Ok(())
}

pub async fn fetch_latest_release_info(client: &Client, url: &str) -> Result<GithubReleaseData> {
    let response = client
        .get(url)
        .send()
        .await?
        .error_for_status()
        .context("Failed to fetch latest release info")?
        .json::<GithubReleaseData>()
        .await
        .context("Failed to deserialize release info")?;

    Ok(response)
}

#[derive(Deserialize)]
pub struct GithubReleaseData {
    pub tag_name: String,
    pub published_at: String,
}
