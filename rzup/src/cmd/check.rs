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
    toolchain::{repo::ToolchainRepo, rust::RUSTUP_TOOLCHAIN_NAME},
    utils::{
        get_toolchain_cwd, parse_toolchain_info, pretty_print_message, pretty_println_message,
    },
};

use super::{
    extension::get_extension_info,
    install::{GithubReleaseData, Installable},
    show::get_installed_extension_version,
    toolchain::get_toolchain_info,
};

#[derive(Debug)]
pub struct UpdateInfo {
    pub name: String,
    pub current_version: String,
    pub current_published_at: String,
    pub latest_version: String,
    pub latest_published_at: String,
    pub up_to_date: bool,
    pub installable: Installable,
}

pub fn handle_check_all() -> Result<()> {
    let updates = get_updatable_items()?;
    print_updates(&updates);
    Ok(())
}

pub fn get_updatable_items() -> Result<Vec<UpdateInfo>> {
    let mut updates = Vec::new();

    // Check for cargo-risczero updates
    let latest_extension_info = get_extension_info(None)?;
    let latest_extension_version = latest_extension_info
        .tag_name
        .strip_prefix('v')
        .expect("failed to strip prefix");

    let curr_extension_version = get_installed_extension_version()?;
    let tag = format!("v{}", curr_extension_version);
    let curr_extension_info = get_extension_info(Some(&tag))?;

    updates.push(UpdateInfo {
        name: "cargo-risczero".to_string(),
        current_version: curr_extension_version.clone(),
        current_published_at: curr_extension_info.published_at.clone(),
        latest_version: latest_extension_version.to_string(),
        latest_published_at: latest_extension_info.published_at.clone(),
        up_to_date: curr_extension_version == latest_extension_version,
        installable: Installable::Extension,
    });

    // Check for rust toolchain updates
    let curr_rust_toolchain = get_toolchain_cwd(RUSTUP_TOOLCHAIN_NAME)?;
    let curr_rust_info = parse_toolchain_info(&curr_rust_toolchain)?;

    let latest_rust_info =
        get_toolchain_info(ToolchainRepo::from_language(&curr_rust_info.language), None)?;

    let curr_rust_info_ext = get_toolchain_info(
        ToolchainRepo::from_language(&curr_rust_info.language),
        Some(&curr_rust_info.tag_name),
    )?;

    updates.push(UpdateInfo {
        name: curr_rust_info.name.clone(),
        current_version: curr_rust_info.tag_name.clone(),
        current_published_at: curr_rust_info_ext.published_at.clone(),
        latest_version: latest_rust_info.tag_name.clone(),
        latest_published_at: latest_rust_info.published_at.clone(),
        up_to_date: curr_rust_info.tag_name == latest_rust_info.tag_name,
        installable: Installable::Rust,
    });

    // TODO: Check for cpp updates

    Ok(updates)
}

fn print_updates(updates: &[UpdateInfo]) {
    let mut stdout = StandardStream::stdout(ColorChoice::Always);

    for update in updates {
        if update.up_to_date {
            pretty_print_message(&mut stdout, true, None, &format!("{} - ", update.name)).unwrap();
            pretty_print_message(&mut stdout, true, Some(Color::Green), "Up to date ").unwrap();
            pretty_println_message(
                &mut stdout,
                false,
                None,
                &format!(
                    ": {} ({})",
                    update.current_version, update.current_published_at
                ),
            )
            .unwrap();
        } else {
            pretty_print_message(&mut stdout, true, None, &format!("{} - ", update.name)).unwrap();
            pretty_print_message(&mut stdout, true, Some(Color::Yellow), "Update available ")
                .unwrap();
            pretty_println_message(
                &mut stdout,
                false,
                None,
                &format!(
                    ": {} ({}) -> {} ({})",
                    update.current_version,
                    update.current_published_at,
                    update.latest_version,
                    update.latest_published_at,
                ),
            )
            .unwrap();
        }
    }
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
