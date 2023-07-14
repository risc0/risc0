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

use anyhow::Context;
use async_trait::async_trait;
use axum::{
    body::Bytes,
    extract::FromRequest,
    http::{Request, StatusCode},
    response::{IntoResponse, Response},
};
use hyper::{body::HttpBody, header, HeaderMap};
use serde::de::DeserializeOwned;

/// Bincode extractor of the request body as a stream.
/// When used as an extractor, it can deserialize request bodies into some type
/// that implements [`serde::Deserialize`] using [`bincode`].
pub(crate) struct Bincode<T>(pub T);

#[async_trait]
impl<T, S, B> FromRequest<S, B> for Bincode<T>
where
    T: DeserializeOwned,
    B: HttpBody + Send + 'static,
    B::Data: Send,
    B::Error: std::error::Error + Send + Sync,
    S: Send + Sync,
{
    type Rejection = Response;

    async fn from_request(req: Request<B>, state: &S) -> Result<Self, Self::Rejection> {
        if !octet_stream_content_type(req.headers()) {
            return Err((
                StatusCode::UNSUPPORTED_MEDIA_TYPE,
                "Expected request with `Content-Type: application/octet-stream`",
            )
                .into_response());
        }

        let bytes = Bytes::from_request(req, state)
            .await
            .map_err(IntoResponse::into_response)?;

        let result = bincode::deserialize(&bytes).context("failed to deserialize");

        let value = result.map_err(|err: anyhow::Error| {
            (
                StatusCode::BAD_REQUEST,
                format!("Failed to parse request body: {err}"),
            )
                .into_response()
        })?;

        Ok(Bincode(value))
    }
}

fn octet_stream_content_type(headers: &HeaderMap) -> bool {
    let Some(content_type) = headers.get(header::CONTENT_TYPE) else {
        return false;
    };
    content_type == "application/octet-stream"
}
