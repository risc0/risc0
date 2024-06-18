use anyhow::Result;
use reqwest::Client;

use crate::utils::{fetch_release_info, GithubReleaseData};

pub fn fetch_extension_info(version: Option<&str>) -> Result<GithubReleaseData> {
    let client = Client::builder().user_agent("rzup").build()?;

    let base_url = "https://api.github.com/repos/risc0/risc0/releases";
    let url = match version {
        Some(tag) => format!("{}/tags/{}", base_url, tag),
        None => format!("{}/latest", base_url),
    };

    let release_data = fetch_release_info(&client, &url)?;

    Ok(release_data)
}
