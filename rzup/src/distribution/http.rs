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
use reqwest::{IntoUrl, Url, blocking::Client};
use std::time::Duration;

/// 3 hour HTTP timeout, internet can be slow and components can be up to 5gb.
const HTTP_TIMEOUT_SECS: u64 = 3 * 60 * 60;

fn http_client_get(
    url: &Url,
    bearer_token: &Option<String>,
) -> Result<reqwest::blocking::Response> {
    let client = Client::builder()
        .timeout(Duration::from_secs(HTTP_TIMEOUT_SECS))
        .build()
        .map_err(|e| RzupError::Other(format!("Failed to create HTTP client: {e}")))?;

    let mut builder = client.get(url.clone()).header("User-Agent", "rzup");

    if let Some(token) = bearer_token {
        builder = builder.header("Authorization", format!("Bearer {token}"));
    }

    builder
        .send()
        .map_err(|e| RzupError::Other(format!("{e:?}: {url}")))
}

fn error_on_status(
    response: reqwest::blocking::Response,
    url: &Url,
) -> Result<reqwest::blocking::Response> {
    let status = response.status();

    if !status.is_success() {
        let host = response.url().host_str().expect("URL has a host");
        let host = host.to_owned();
        let body = response.text().ok();

        Err(RzupError::Other(format!(
            "Remote error: {host}: {body:?}: {url}"
        )))
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
        .map_err(|e| RzupError::Other(format!("{e:?}: {url}")))
}

pub fn download_text(url: impl IntoUrl, bearer_token: &Option<String>) -> Result<String> {
    let url = url
        .into_url()
        .map_err(|e| RzupError::Other(e.to_string()))?;
    let response = http_client_get(&url, bearer_token)?;
    let response = error_on_status(response, &url)?;
    response
        .text()
        .map_err(|e| RzupError::Other(format!("{e:?}: {url}")))
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

#[cfg_attr(not(feature = "publish"), allow(dead_code))]
pub fn upload_bytes<BodyT: std::io::Read + Send + 'static>(
    url: impl IntoUrl,
    signer: impl FnOnce(&mut http::Request<reqwest::blocking::Body>) -> Result<()>,
    body_stream: BodyT,
    content_length: u64,
) -> Result<()> {
    let url = url
        .into_url()
        .map_err(|e| RzupError::Other(e.to_string()))?;

    let client = Client::builder()
        .timeout(Duration::from_secs(HTTP_TIMEOUT_SECS))
        .build()
        .map_err(|e| RzupError::Other(format!("Failed to create HTTP client: {e:?}")))?;

    let mut request = http::Request::builder()
        .method("PUT")
        .uri(url.as_str())
        .header("user-agent", "rzup")
        .header("content-type", "application/octet-stream")
        .header("content-length", content_length.to_string())
        .body(reqwest::blocking::Body::sized(body_stream, content_length))
        .map_err(|e| RzupError::Other(format!("failed to build HTTP request: {e:?}")))?;

    signer(&mut request)?;

    let request = reqwest::blocking::Request::try_from(request).map_err(|e| {
        RzupError::Other(format!(
            "failed to convert to reqwest::blocking::Request: {e:?}"
        ))
    })?;

    let response = client
        .execute(request)
        .map_err(|e| RzupError::Other(format!("{e:?}: {url}")))?;

    error_on_status(response, &url)?;

    Ok(())
}
