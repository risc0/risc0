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

use crate::alpha::{
    responses::{SessionStatusRes, SnarkStatusRes},
    Client, SdkErr, SessionId, SnarkId,
};

/// Construct a Bonsai SDK Client from env var
///
/// Uses the BONSAI_API_URL and BONSAI_API_KEY environment variables to
/// construct a client
pub async fn get_client_from_env() -> Result<Client, SdkErr> {
    tokio::task::spawn_blocking(Client::from_env)
        .await
        .map_err(|err| SdkErr::InternalServerErr(format!("{err}")))?
}

/// Construct a Bonsai SDK Client from url + api key strings
pub async fn get_client_from_parts(url: String, api_key: String) -> Result<Client, SdkErr> {
    tokio::task::spawn_blocking(move || Client::from_parts(url, api_key))
        .await
        .map_err(|err| SdkErr::InternalServerErr(format!("{err}")))?
}

/// Upload a input buffer to the /inputs/ route
pub async fn upload_input(bonsai_client: Client, buf: Vec<u8>) -> Result<String, SdkErr> {
    tokio::task::spawn_blocking(move || bonsai_client.upload_input(buf))
        .await
        .map_err(|err| SdkErr::InternalServerErr(format!("{err}")))?
}

/// Upload a image buffer to the /images/ route
///
/// The boolean return indicates if the image already exists in bonsai
///
/// The image data can be either:
/// * ELF file bytes
/// * bincode encoded MemoryImage
pub async fn upload_img(
    bonsai_client: Client,
    image_id: String,
    image: Vec<u8>,
) -> Result<bool, SdkErr> {
    tokio::task::spawn_blocking(move || bonsai_client.upload_img(&image_id, image))
        .await
        .map_err(|err| SdkErr::InternalServerErr(format!("{err}")))?
}

/// Create a new proof request Session
///
/// Supply the image_id and input_id created from uploading those files in
/// previous steps
pub async fn create_session(
    bonsai_client: Client,
    img_id: String,
    input_id: String,
) -> Result<SessionId, SdkErr> {
    tokio::task::spawn_blocking(move || bonsai_client.create_session(img_id, input_id))
        .await
        .map_err(|err| SdkErr::InternalServerErr(format!("{err}")))?
}

/// Fetches the current status of the Session
pub async fn session_status(
    bonsai_client: Client,
    session: SessionId,
) -> Result<SessionStatusRes, SdkErr> {
    tokio::task::spawn_blocking(move || session.status(&bonsai_client))
        .await
        .map_err(|err| SdkErr::InternalServerErr(format!("{err}")))?
}

/// Requests a SNARK proof be created from a existing sessionId
///
/// Supply a completed sessionId to convert the risc0 STARK proof into
/// a SNARK proof that can be validated on ethereum-like blockchains
pub async fn create_snark(bonsai_client: Client, session_id: String) -> Result<SnarkId, SdkErr> {
    tokio::task::spawn_blocking(move || bonsai_client.create_snark(session_id))
        .await
        .map_err(|err| SdkErr::InternalServerErr(format!("{err}")))?
}

/// Fetches the current status of the Snark Session
pub async fn snark_status(bonsai_client: Client, snark: SnarkId) -> Result<SnarkStatusRes, SdkErr> {
    tokio::task::spawn_blocking(move || snark.status(&bonsai_client))
        .await
        .map_err(|err| SdkErr::InternalServerErr(format!("{err}")))?
}

/// Download a given url to a buffer
///
/// Useful to download a [SessionId] receipt_url
pub async fn download(bonsai_client: Client, url: String) -> Result<Vec<u8>, SdkErr> {
    tokio::task::spawn_blocking(move || bonsai_client.download(&url))
        .await
        .map_err(|err| SdkErr::InternalServerErr(format!("{err}")))?
}
