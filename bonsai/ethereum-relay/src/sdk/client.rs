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

//! An asynchronous Client API.

use anyhow::Context;
use bonsai_sdk::{
    alpha::{responses::CreateSessRes, SessionId},
    API_KEY_HEADER,
};
use reqwest::{header, Client as AsyncClient, Response};
use serde::{Deserialize, Serialize};
use utoipa::ToSchema;

use crate::api::routes::CALLBACK_ROUTE;

/// A Bonsai CallbackRequest for Ethereum.
#[derive(Debug, Deserialize, Serialize, Clone, ToSchema)]
pub struct CallbackRequest {
    /// The image ID of the guest.
    pub image_id: [u8; 32],
    /// The input for the guest.
    pub input: Vec<u8>,
    /// The Ethereum address of the callback.
    pub callback_contract: ethers::types::Address,
    /// The function selector of the callbcak.
    pub function_selector: ethers::types::Selector,
    /// The gas limit.
    pub gas_limit: u64,
}

/// The Errors that may occur when processing a [Client] request.
#[derive(Debug, thiserror::Error)]
pub enum ClientError {
    /// An error returned by the Bonsai-Relay API.
    #[error("API error: {0}")]
    Api(String),
    /// Missing BONSAI_API_KEY
    #[error("missing BONSAI_API_KEY env var")]
    MissingApiKey,
    /// Missing BONSAI_API_URL
    #[error("missing BONSAI_API_URL env var")]
    MissingApiUrl,
    /// A network error returned by the HTTP client.
    #[error("Request error")]
    Network(#[from] reqwest::Error),
    /// An Bincode serialization error.
    #[error("Bincode error")]
    Bincode(#[from] bincode::Error),
    /// An otherwise unspecified error.
    #[error("Unspecified error")]
    Anyhow(#[from] anyhow::Error),
}

/// An asynchronous `Client` for the Bonsai-Relay REST API.
#[derive(Debug, Clone)]
pub struct Client {
    pub(crate) client: AsyncClient,
    pub(crate) url: String,
}

impl Client {
    /// Construct a [Client] from env var
    ///
    /// Uses the BONSAI_API_URL and BONSAI_API_KEY environment variables to
    /// construct a client
    pub fn from_env() -> Result<Self, ClientError> {
        let api_url = std::env::var("BONSAI_API_URL").map_err(|_| ClientError::MissingApiUrl)?;
        let api_key = std::env::var("BONSAI_API_KEY").map_err(|_| ClientError::MissingApiKey)?;

        let mut headers = header::HeaderMap::new();
        let mut auth_value =
            header::HeaderValue::from_str(&api_key).context("invalid API key value")?;
        auth_value.set_sensitive(true);
        headers.insert(API_KEY_HEADER, auth_value);

        let client = AsyncClient::builder()
            .default_headers(headers)
            .gzip(true)
            .build()?;

        Ok(Self {
            client,
            url: api_url,
        })
    }

    /// Construct a [Client] from url + api key strings
    pub fn from_parts(api_url: String, api_key: String) -> Result<Self, ClientError> {
        let mut headers = header::HeaderMap::new();
        let mut auth_value =
            header::HeaderValue::from_str(&api_key).context("invalid API key value")?;
        auth_value.set_sensitive(true);
        headers.insert(API_KEY_HEADER, auth_value);

        let client = AsyncClient::builder()
            .default_headers(headers)
            .gzip(true)
            .build()?;

        Ok(Self {
            client,
            url: api_url,
        })
    }

    /// Post a new [CallbackRequest] to Bonsai.
    pub async fn callback_request(
        &self,
        request: impl Into<CallbackRequest>,
    ) -> Result<SessionId, ClientError> {
        let res = self
            .client
            .post(format!("{}{CALLBACK_ROUTE}", self.url))
            .header(header::CONTENT_TYPE, "application/octet-stream")
            .body(bincode::serialize(&request.into())?)
            .send()
            .await?;
        let session_response = error_for_status(res).await?.json::<CreateSessRes>().await?;
        Ok(SessionId {
            uuid: session_response.uuid,
        })
    }
}

/// Turn a response into an error if the server returned an error.
async fn error_for_status(res: Response) -> Result<Response, ClientError> {
    let status = res.status();
    if status.is_success() {
        return Ok(res);
    }
    // the reason for the error is contained in the body
    let message = res.text().await?;
    Err(ClientError::Api(format!("{status} '{message}'")))
}
