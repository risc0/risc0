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

use axum::{extract::State, Extension};
use bonsai_ethereum_contracts::i_bonsai_relay::CallbackRequestFilter;
use bonsai_sdk::alpha_async::get_client_from_parts;

use super::{bincode::Bincode, state::ApiState, Error, Result};
use crate::{
    downloader::{
        event_processor::EventProcessor,
        proxy_callback_proof_processor::ProxyCallbackProofRequestProcessor,
    },
    sdk::client::CallbackRequest,
    storage::Storage,
};

/// Publish a CallbackRequest to the Relayer.
///
/// Return status 200 on success.
#[utoipa::path(
    post,
    path = "/v1/callbacks",
    request_body = CallbackRequest,
    responses(
        (status = 200, description = "Callback request sent successfully"),
        (status = 400, description = "Bad request error"),
        (status = 500, description = "Internal server error"),
    )
)]
pub(crate) async fn post_callback_request<S: Storage + Sync + Send + Clone>(
    Extension(api_key): Extension<String>,
    State(s): State<ApiState<S>>,
    Bincode(request): Bincode<CallbackRequest>,
) -> Result<(), Error> {
    let client = get_client_from_parts(s.bonsai_url, api_key).await?;
    let proxy = ProxyCallbackProofRequestProcessor::new(client, s.storage, Some(s.notifier));
    proxy.process_event(request.into()).await
}

impl From<CallbackRequest> for CallbackRequestFilter {
    fn from(val: CallbackRequest) -> Self {
        CallbackRequestFilter {
            account: val.callback_contract,
            image_id: val.image_id,
            input: val.input.into(),
            callback_contract: val.callback_contract,
            function_selector: val.function_selector,
            gas_limit: val.gas_limit,
        }
    }
}
