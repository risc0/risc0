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
use crate::error::{Result, RzupError};
use reqwest::{blocking::Client, IntoUrl, Url};
use serde::Deserialize;
use std::time::Duration;

fn http_client_get(
    url: &Url,
    bearer_token: &Option<String>,
) -> Result<reqwest::blocking::Response> {
    let client = Client::builder()
        .timeout(Duration::from_secs(10))
        .build()
        .map_err(|e| RzupError::Other(format!("Failed to create HTTP client: {e}")))?;

    let mut builder = client.get(url.clone()).header("User-Agent", "rzup");

    if let Some(token) = bearer_token {
        builder = builder.header("Authorization", format!("Bearer {token}"));
    }

    builder
        .send()
        .map_err(|e| RzupError::Other(format!("{e}: {url}")))
}

#[derive(Deserialize)]
struct RemoteResponse {
    message: String,
}

fn error_on_status(
    response: reqwest::blocking::Response,
    url: &Url,
) -> Result<reqwest::blocking::Response> {
    let status = response.status();

    if !status.is_success() {
        let host = response.url().host_str().expect("URL has a host");
        let host = host.to_owned();
        if let Ok(RemoteResponse { message }) = response.json() {
            Err(RzupError::Other(format!(
                "Remote error: {host}: {message}: {url}"
            )))
        } else {
            Err(RzupError::Other(format!(
                "Unexpected response: {host}: {status}: {url}"
            )))
        }
    } else {
        Ok(response)
    }
}

pub fn check_for_not_found(url: impl IntoUrl, bearer_token: &Option<String>) -> Result<bool> {
    let url = url
        .into_url()
        .map_err(|e| RzupError::Other(e.to_string()))?;
    let response = http_client_get(&url, bearer_token)?;
    let status = response.status();
    if status == reqwest::StatusCode::NOT_FOUND {
        return Ok(false);
    }
    error_on_status(response, &url)?;
    Ok(true)
}

pub fn download_json<RetT: serde::de::DeserializeOwned>(
    url: impl IntoUrl,
    bearer_token: &Option<String>,
) -> Result<RetT> {
    let url = url
        .into_url()
        .map_err(|e| RzupError::Other(e.to_string()))?;
    let response = http_client_get(&url, bearer_token)?;
    let response = error_on_status(response, &url)?;
    response
        .json()
        .map_err(|e| RzupError::Other(format!("{e}: {url}")))
}

pub fn download_text(url: impl IntoUrl, bearer_token: &Option<String>) -> Result<String> {
    let url = url
        .into_url()
        .map_err(|e| RzupError::Other(e.to_string()))?;
    let response = http_client_get(&url, bearer_token)?;
    let response = error_on_status(response, &url)?;
    response
        .text()
        .map_err(|e| RzupError::Other(format!("{e}: {url}")))
}

pub fn download_bytes(
    url: impl IntoUrl,
    bearer_token: &Option<String>,
) -> Result<reqwest::blocking::Response> {
    let url = url
        .into_url()
        .map_err(|e| RzupError::Other(e.to_string()))?;
    let response = http_client_get(&url, bearer_token)?;
    let response = error_on_status(response, &url)?;
    Ok(response)
}
