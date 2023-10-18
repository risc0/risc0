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

/// Extractor of the callback request body. Uses bincode or json, depending on
/// the Content-Type header When used as an extractor, it can deserialize
/// request bodies into some type that implements [`serde::Deserialize`] using
/// [`bincode`, `serde_json`].
pub(crate) struct RequestExtractor<T>(pub T);

#[async_trait]
impl<T, S, B> FromRequest<S, B> for RequestExtractor<T>
where
    T: DeserializeOwned,
    B: HttpBody + Send + 'static,
    B::Data: Send,
    B::Error: std::error::Error + Send + Sync,
    S: Send + Sync,
{
    type Rejection = Response;

    async fn from_request(req: Request<B>, state: &S) -> Result<Self, Self::Rejection> {
        if octet_stream_content_type(req.headers()) {
            let bytes = Bytes::from_request(req, state)
                .await
                .map_err(IntoResponse::into_response)?;

            let result = bincode::deserialize(&bytes).context("failed to deserialize");

            let value = result.map_err(|err: anyhow::Error| {
                (
                    StatusCode::BAD_REQUEST,
                    format!("Failed to parse request body as bincode: {err}"),
                )
                    .into_response()
            })?;

            return Ok(RequestExtractor(value));
        }

        if json_content_type(req.headers()) {
            let bytes = Bytes::from_request(req, state)
                .await
                .map_err(IntoResponse::into_response)?;

            let bytes_vec = &bytes.to_vec();

            let json_str = std::str::from_utf8(bytes_vec).map_err(|err| {
                (
                    StatusCode::BAD_REQUEST,
                    format!("Failed to parse request body as utf8: {err}"),
                )
                    .into_response()
            })?;

            let result: Result<T, anyhow::Error> =
                serde_json::from_str(&json_str).context("failed to deserialize");

            let value = result.map_err(|err: anyhow::Error| {
                (
                    StatusCode::BAD_REQUEST,
                    format!("Failed to parse request body as json: {err}"),
                )
                    .into_response()
            })?;

            return Ok(RequestExtractor(value));
        }

        Err(
            (
                StatusCode::UNSUPPORTED_MEDIA_TYPE,
                "Expected request with `Content-Type: application/octet-stream` or `Content-Type: application/json`",
            ).into_response()
        )
    }
}

fn octet_stream_content_type(headers: &HeaderMap) -> bool {
    let Some(content_type) = headers.get(header::CONTENT_TYPE) else {
        return false;
    };
    content_type == "application/octet-stream"
}

fn json_content_type(headers: &HeaderMap) -> bool {
    let Some(content_type) = headers.get(header::CONTENT_TYPE) else {
        return false;
    };
    content_type == "application/json"
}

#[cfg(test)]
mod tests {
    use axum::http::{Method, Request};
    use hyper::{header::HeaderValue, Body};
    use serde::Serialize;

    use super::*;
    use crate::sdk::CallbackRequest;

    async fn mock_request<T: Serialize + DeserializeOwned>(
        value: T,
        content_type: &str,
    ) -> RequestExtractor<T> {
        let body = match content_type {
            "application/octet-stream" => {
                let serialized = bincode::serialize(&value).unwrap();
                Body::from(serialized)
            }
            "application/json" => {
                let serialized = serde_json::to_string(&value).unwrap();
                Body::from(serialized)
            }
            _ => panic!("Unsupported content type"),
        };

        let req = Request::builder()
            .method(Method::POST)
            .header(
                header::CONTENT_TYPE,
                HeaderValue::from_str(content_type).unwrap(),
            )
            .body(body)
            .unwrap();

        RequestExtractor::from_request(req, &()).await.unwrap()
    }

    #[tokio::test]
    async fn test_bincode_request() {
        let original = CallbackRequest {
            image_id: [0; 32],
            input: vec![1, 2, 3, 4],
            callback_contract: "0x0000000000000000000000000000000000000000"
                .parse()
                .unwrap(),
            function_selector: [0; 4],
            gas_limit: 21000,
        };
        let extractor = mock_request(original.clone(), "application/octet-stream").await;

        assert_eq!(extractor.0.image_id, original.image_id);
        assert_eq!(extractor.0.input, original.input);
        assert_eq!(extractor.0.callback_contract, original.callback_contract);
        assert_eq!(extractor.0.function_selector, original.function_selector);
        assert_eq!(extractor.0.gas_limit, original.gas_limit);
    }

    #[tokio::test]
    async fn test_json_request() {
        let original = CallbackRequest {
            image_id: [0; 32],
            input: vec![1, 2, 3, 4],
            callback_contract: "0x0000000000000000000000000000000000000000"
                .parse()
                .unwrap(),
            function_selector: [0; 4],
            gas_limit: 21000,
        };
        let extractor = mock_request(original.clone(), "application/json").await;

        assert_eq!(extractor.0.image_id, original.image_id);
        assert_eq!(extractor.0.input, original.input);
        assert_eq!(extractor.0.callback_contract, original.callback_contract);
        assert_eq!(extractor.0.function_selector, original.function_selector);
        assert_eq!(extractor.0.gas_limit, original.gas_limit);
    }
}
