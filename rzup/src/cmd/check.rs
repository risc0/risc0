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
use termcolor::{Color, ColorChoice, StandardStream};

use crate::{
    toolchain::repo::ToolchainRepo,
    utils::{
        get_toolchain_cwd, parse_toolchain_info, pretty_print_message, pretty_println_message,
    },
};

use super::{
    extension::get_extension_info, install::GithubReleaseData,
    show::get_installed_extension_version, toolchain::get_toolchain_info,
};

pub fn handle_check_all() -> Result<()> {
    let latest_extension_info = get_extension_info(None)?;
    let latest_extension_version = latest_extension_info
        .tag_name
        .strip_prefix('v')
        .expect("failed to strip prefix");

    let curr_extension_version = get_installed_extension_version()?;
    let tag = format!("v{}", curr_extension_version);
    let curr_extension_info = get_extension_info(Some(&tag))?;

    let mut stdout = StandardStream::stdout(ColorChoice::Always);

    // Check for cargo-risczero updates
    if curr_extension_version == latest_extension_version {
        pretty_print_message(&mut stdout, true, None, "cargo-risczero - ")?;
        pretty_print_message(&mut stdout, true, Some(Color::Green), "Up to date ")?;
        pretty_println_message(
            &mut stdout,
            false,
            None,
            &format!(
                ": {} ({})",
                curr_extension_version, latest_extension_info.published_at
            ),
        )?;
    } else {
        pretty_print_message(&mut stdout, true, None, "cargo-risczero - ")?;
        pretty_print_message(&mut stdout, true, Some(Color::Yellow), "Update available ")?;
        pretty_println_message(
            &mut stdout,
            false,
            None,
            &format!(
                ": {} ({}) -> {} ({})",
                curr_extension_version,
                curr_extension_info.published_at,
                latest_extension_version,
                latest_extension_info.published_at
            ),
        )?;
    }

    // Check for rust toolchain updates
    let curr_rust_toolchain = get_toolchain_cwd("risc0")?;
    let curr_rust_info = parse_toolchain_info(&curr_rust_toolchain)?;

    let latest_rust_info =
        get_toolchain_info(ToolchainRepo::from_language(&curr_rust_info.language), None)?;
    if curr_rust_info.tag_name == latest_rust_info.tag_name {
        pretty_print_message(
            &mut stdout,
            true,
            None,
            &format!("{} - ", curr_rust_info.name),
        )?;
        pretty_print_message(&mut stdout, true, Some(Color::Green), "Up to date ")?;
        pretty_println_message(
            &mut stdout,
            false,
            None,
            &format!(
                ": {} ({})",
                curr_rust_info.tag_name, latest_rust_info.published_at
            ),
        )?;
    } else {
        let curr_rust_info_ext = get_toolchain_info(
            ToolchainRepo::from_language(&curr_rust_info.language),
            Some(&curr_rust_info.tag_name),
        )?;
        pretty_print_message(
            &mut stdout,
            true,
            None,
            &format!("{} - ", curr_rust_info.name),
        )?;
        pretty_print_message(&mut stdout, true, Some(Color::Yellow), "Update available ")?;
        pretty_println_message(
            &mut stdout,
            false,
            None,
            &format!(
                ": {} ({}) -> {} ({})",
                curr_rust_info.tag_name,
                curr_rust_info_ext.published_at,
                latest_rust_info.tag_name,
                latest_rust_info.published_at
            ),
        )?;
    }

    // TODO: Check cpp toolchain updates

    Ok(())
}

pub fn fetch_release_info(client: &Client, url: &str) -> Result<GithubReleaseData> {
    let runtime = tokio::runtime::Runtime::new().context("Failed to create Tokio runtime")?;

    runtime.block_on(async {
        let response = client
            .get(url)
            .send()
            .await?
            .error_for_status()
            .context("Failed to fetch release info")?
            .json::<GithubReleaseData>()
            .await
            .context("Failed to deserialize release info")?;

        Ok(response)
    })
}
