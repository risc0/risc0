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

use std::{fs::File, path::Path};

use anyhow::{bail, Context, Result};
use reqwest::{blocking::Client as BlockingClient, header};

use self::responses::{CreateSessRes, ProofReq, SessionStatusRes, UploadRes};

/// Collection of serialization object for the REST api
pub mod responses {
    use serde::{Deserialize, Serialize};

    /// Response of a upload request
    #[derive(Deserialize, Serialize)]
    pub struct UploadRes {
        /// Presigned URL to be supplied to a PUT request
        pub url: String,
        /// Generated UUID for this input
        pub uuid: String,
    }

    /// Session creation response
    #[derive(Deserialize, Serialize)]
    pub struct CreateSessRes {
        /// Generated UUID for the session
        pub uuid: String,
    }

    /// Proof Request object to create Session
    #[derive(Deserialize, Serialize)]
    pub struct ProofReq {
        /// Image UUID
        pub img: String,
        /// Input UUID
        pub input: String,
    }

    /// Session Status response
    #[derive(Deserialize, Serialize)]
    pub struct SessionStatusRes {
        /// Current status
        ///
        /// values: [RUNNING | SUCCEEDED | FAILED | TIMED_OUT | ABORTED |
        /// SUCCEEDED]
        pub status: String,
        /// Final receipt download URL
        ///
        /// If the status == 'SUCCEEDED' then this should be present
        pub receipt_url: Option<String>,
    }
}

/// Proof Session representation
#[derive(Debug, Clone, PartialEq)]
pub struct SessionId {
    /// Session UUID
    pub uuid: String,
}

impl SessionId {
    /// Construct a [SessionId] from a UUID [String]
    pub fn new(uuid: String) -> Self {
        Self { uuid }
    }

    /// Retries the current status of the Session
    pub fn status(&self, client: &Client) -> Result<SessionStatusRes> {
        let url = format!("{}/sessions/status/{}", client.url, self.uuid);
        let res = client
            .client
            .get(url)
            .send()
            .context("Failed to GEt session status")?;

        if !res.status().is_success() {
            let body = res.text()?;
            bail!("Request failed - server error: '{body}'");
        }
        res.json::<SessionStatusRes>()
            .context("Failed to deserialize Session status result")
    }
}

/// Represents a client of the REST api
pub struct Client {
    pub(crate) url: String,
    pub(crate) client: BlockingClient,
}

/// Creates a [reqwest::Client] for internal connection pooling
fn construct_req_client(api_key: &str) -> Result<BlockingClient> {
    let mut headers = header::HeaderMap::new();
    headers.insert("x-api-key", header::HeaderValue::from_str(api_key)?);

    BlockingClient::builder()
        .default_headers(headers)
        .pool_max_idle_per_host(0)
        .build()
        .context("Failed to build reqwest client")
}

impl Client {
    /// Construct a [Client] from env var
    ///
    /// Uses the BONSAI_API_URL and BONSAI_API_KEY environment variables to
    /// construct a client
    pub fn from_env() -> Result<Self> {
        let api_url = std::env::var("BONSAI_API_URL").context("Missing BONSAI_API_URL env var")?;
        let api_key = std::env::var("BONSAI_API_KEY").context("Missing BONSAI_API_KEY env var")?;

        let client = construct_req_client(&api_key)?;

        Ok(Self {
            url: api_url,
            client,
        })
    }

    /// Construct a [Client] from url + api key strings
    pub fn from_parts(url: String, key: String) -> Result<Self> {
        let client = construct_req_client(&key)?;
        Ok(Self { url, client })
    }

    /// Fetch a upload presigned url for a given route
    fn get_upload_url(&self, route: &str) -> Result<UploadRes> {
        let res = self
            .client
            .get(format!("{}/{}/upload", self.url, route))
            .send()
            .context("Failed to fetch upload location")?;

        if !res.status().is_success() {
            let body = res.text()?;
            bail!("Request failed - server error: '{body}'");
        }

        res.json::<UploadRes>()
            .context("Failed to deserialize upload response")
    }

    /// Upload body to a given URL
    fn put_data<T: Into<reqwest::blocking::Body>>(&self, url: &str, body: T) -> Result<()> {
        let res = self
            .client
            .put(url)
            .body(body)
            .send()
            .context("Failed to PUT data to destination")?;
        if !res.status().is_success() {
            bail!("Failed to PUT to provided URL");
        }

        Ok(())
    }

    // - /images

    /// Upload a image buffer to the /images/ route
    ///
    /// The image data can be either:
    /// * ELF file bytes
    /// * bincode encoded MemoryImage
    pub fn upload_img(&self, buf: Vec<u8>) -> Result<String> {
        let upload_data = self.get_upload_url("images")?;
        self.put_data(&upload_data.url, buf)?;
        Ok(upload_data.uuid)
    }

    /// Upload a image file to the /images/ route
    ///
    /// The image data can be either:
    /// * ELF file bytes
    /// * bincode encoded MemoryImage
    pub fn upload_img_file(&self, path: &Path) -> Result<String> {
        let upload_data = self.get_upload_url("images")?;

        let fd = File::open(path).context("Unable to open supplied image file")?;
        self.put_data(&upload_data.url, fd)?;

        Ok(upload_data.uuid)
    }

    // - /inputs

    /// Upload a input buffer to the /inputs/ route
    pub fn upload_input(&self, buf: Vec<u8>) -> Result<String> {
        let upload_data = self.get_upload_url("inputs")?;
        self.put_data(&upload_data.url, buf)?;
        Ok(upload_data.uuid)
    }

    /// Upload a input file to the /inputs/ route
    pub fn upload_input_file(&self, path: &Path) -> Result<String> {
        let upload_data = self.get_upload_url("inputs")?;

        let fd = File::open(path).context("Unable to open supplied image file")?;
        self.put_data(&upload_data.url, fd)?;

        Ok(upload_data.uuid)
    }

    // - /sessions

    /// Create a new proof request Session
    ///
    /// Supply the img_id and input_id created from uploading those files in
    /// previous steps
    pub fn create_session(&self, img_id: String, input_id: String) -> Result<SessionId> {
        let url = format!("{}/sessions/create", self.url);

        let req = ProofReq {
            img: img_id,
            input: input_id,
        };

        let res = self
            .client
            .post(url)
            .json(&req)
            .send()
            .context("Failed to submit session/create POST request")?;

        if !res.status().is_success() {
            let body = res.text()?;
            bail!("Request failed - server error: '{body}'");
        }

        let res: CreateSessRes = res
            .json()
            .context("Failed to deserialize Session status result")?;

        Ok(SessionId::new(res.uuid))
    }

    // Utilities

    /// Download a given url to a buffer
    ///
    /// Useful to download a [SessionId] receipt_url
    pub fn download(&self, url: &str) -> Result<Vec<u8>> {
        let data = self
            .client
            .get(url)
            .send()
            .context("Failed to download url to buffer")?
            .bytes()
            .context("Failed to get raw bytes from download")?;

        Ok(data.into())
    }
}

#[cfg(test)]
mod tests {
    use httpmock::prelude::*;
    use uuid::Uuid;

    use super::*;

    const TEST_KEY: &str = "TESTKEY";

    fn run_upload_mock(route_path: &str) {
        let data = vec![];

        let server = MockServer::start();

        let image_uuid = Uuid::new_v4();
        let put_url = format!("http://{}/upload/{}", server.address(), image_uuid);
        let response = UploadRes {
            url: put_url,
            uuid: image_uuid.to_string(),
        };

        let get_mock = server.mock(|when, then| {
            when.method(GET)
                .path(format!("/{route_path}/upload"))
                .header("x-api-key", TEST_KEY);
            then.status(200)
                .header("content-type", "application/json")
                .json_body_obj(&response);
        });

        let put_mock = server.mock(|when, then| {
            when.method(PUT).path(format!("/upload/{}", image_uuid));
            then.status(200);
        });

        let server_url = format!("http://{}", server.address());
        let client = super::Client::from_parts(server_url, TEST_KEY.to_string())
            .expect("Failed to construct client");
        let res = if route_path == "images" {
            client.upload_img(data).expect("Failed to upload img")
        } else {
            client.upload_input(data).expect("Failed to upload input")
        };

        assert_eq!(res, response.uuid);
        get_mock.assert();
        put_mock.assert();
    }

    #[test]
    fn client_from_parts() {
        let url = "http://127.0.0.1/stage".to_string();
        let apikey = TEST_KEY.to_string();
        let client = super::Client::from_parts(url.clone(), apikey).unwrap();

        assert_eq!(client.url, url);
    }

    #[test]
    fn client_from_env() {
        let url = "http://127.0.0.1/stage".to_string();
        let apikey = TEST_KEY.to_string();
        std::env::set_var("BONSAI_API_URL", url.clone());
        std::env::set_var("BONSAI_API_KEY", apikey);

        let client = super::Client::from_env().unwrap();

        assert_eq!(client.url, url);
    }

    #[test]
    fn image_upload() {
        run_upload_mock("images");
    }

    #[test]
    fn input_upload() {
        run_upload_mock("inputs");
    }

    #[test]
    fn session_create() {
        let server = MockServer::start();

        let request = ProofReq {
            img: Uuid::new_v4().to_string(),
            input: Uuid::new_v4().to_string(),
        };
        let response = CreateSessRes {
            uuid: Uuid::new_v4().to_string(),
        };

        let create_mock = server.mock(|when, then| {
            when.method(POST)
                .path("/sessions/create")
                .header("content-type", "application/json")
                .header("x-api-key", TEST_KEY)
                .json_body_obj(&request);
            then.status(200)
                .header("content-type", "application/json")
                .json_body_obj(&response);
        });

        let server_url = format!("http://{}", server.address());
        let client = super::Client::from_parts(server_url, TEST_KEY.to_string()).unwrap();

        let res = client.create_session(request.img, request.input).unwrap();
        assert_eq!(res.uuid, response.uuid);

        create_mock.assert();
    }

    #[test]
    fn session_status() {
        let server = MockServer::start();

        let uuid = Uuid::new_v4().to_string();
        let session_id = SessionId::new(uuid);
        let response = SessionStatusRes {
            status: "RUNNING".to_string(),
            receipt_url: None,
        };

        let create_mock = server.mock(|when, then| {
            when.method(GET)
                .path(format!("/sessions/status/{}", session_id.uuid))
                .header("x-api-key", TEST_KEY);
            then.status(200)
                .header("content-type", "application/json")
                .json_body_obj(&response);
        });

        let server_url = format!("http://{}", server.address());
        let client = super::Client::from_parts(server_url, TEST_KEY.to_string()).unwrap();

        let status = session_id.status(&client).unwrap();
        assert_eq!(status.status, response.status);
        assert_eq!(status.receipt_url, None);

        create_mock.assert();
    }
}
