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

pub fn handle_check() -> Result<()> {
    let client = Client::builder().user_agent("rzup").build()?;

    let rust_repo = "https://api.github.com/repos/risc0/rust/releases/latest";
    let cpp_repo = "https://api.github.com/repos/risc0/toolchain/releases/latest";

    let rt = tokio::runtime::Runtime::new()?;

    let rust_release_data = rt.block_on(get_latest_version(&client, rust_repo))?;
    let cpp_release_data = rt.block_on(get_latest_version(&client, cpp_repo))?;

    // TODO: Clean up and make pretty
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

async fn get_latest_version(client: &Client, url: &str) -> Result<GithubReleaseData> {
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
struct GithubReleaseData {
    tag_name: String,
    published_at: String,
}
