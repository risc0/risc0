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

use reqwest::{blocking::Client as BlockingClient, header};
use thiserror::Error;

use self::responses::{
    CreateSessRes, ImgUploadRes, ProofReq, Quotas, SessionStatusRes, SnarkReq, SnarkStatusRes,
    UploadRes, VersionInfo,
};
use crate::{API_KEY_ENVVAR, API_KEY_HEADER, API_URL_ENVVAR, VERSION_HEADER};

/// Bonsai Alpha SDK error classes
#[derive(Debug, Error)]
pub enum SdkErr {
    /// Server side failure
    #[error("server error `{0}`")]
    InternalServerErr(String),
    /// http reqwest errors
    #[error("HTTP error from reqwest")]
    HttpErr(#[from] reqwest::Error),
    /// Header construction error
    #[error("HTTP header failed to construct")]
    HttpHeaderErr(#[from] reqwest::header::InvalidHeaderValue),
    /// Missing BONSAI_API_KEY
    #[error("missing BONSAI_API_KEY env var")]
    MissingApiKey,
    /// Missing BONSAI_API_URL
    #[error("missing BONSAI_API_URL env var")]
    MissingApiUrl,
    /// Missing file
    #[error("failed to find file on disk")]
    FileNotFound(#[from] std::io::Error),
}

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

    /// Response of a image upload request
    #[derive(Deserialize, Serialize)]
    pub struct ImgUploadRes {
        /// Presigned URL to be supplied to a PUT request
        pub url: String,
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
        /// values: `[ RUNNING | SUCCEEDED | FAILED | TIMED_OUT | ABORTED ]`
        pub status: String,
        /// Final receipt download URL
        ///
        /// If the status == `SUCCEEDED` then this should be present
        pub receipt_url: Option<String>,
        /// Session Error message
        ///
        /// If the session is not `RUNNING` or `SUCCEEDED`, this is the error
        /// raised from within bonsai, otherwise it is [None].
        pub error_msg: Option<String>,
        /// Session Proving State
        ///
        /// If the status is `RUNNING`, this is a indication of where in the
        /// proving pipeline the session currently is, otherwise it is [None].
        /// Possible states in order, include:
        /// * `Setup`
        /// * `Executor`
        /// * `ProveSegments`
        /// * `Planner`
        /// * `Recursion`
        /// * `RecursionJoin`
        /// * `Finalize`
        /// * `InProgress`
        pub state: Option<String>,
    }

    /// Snark proof request object
    #[derive(Deserialize, Serialize)]
    pub struct SnarkReq {
        /// Existing Session ID from [super::SessionId]
        pub session_id: String,
    }

    /// Snark Proof object
    ///
    /// following the snarkjs calldata format:
    /// <https://github.com/iden3/snarkjs#26-simulate-a-verification-call>
    #[derive(Debug, Deserialize, Serialize, PartialEq)]
    pub struct Groth16Seal {
        /// Proof 'a' value
        pub a: Vec<Vec<u8>>,
        /// Proof 'b' value
        pub b: Vec<Vec<Vec<u8>>>,
        /// Proof 'c' value
        pub c: Vec<Vec<u8>>,
        /// Proof public outputs
        pub public: Vec<Vec<u8>>,
    }

    /// Snark Receipt object
    ///
    /// All relevant data to verify both the snark proof an corresponding
    /// imageId on chain.
    #[derive(Debug, Deserialize, Serialize, PartialEq)]
    pub struct SnarkReceipt {
        /// Snark seal from snarkjs
        pub snark: Groth16Seal,
        /// Post State Digest
        ///
        /// Collected from the STARK proof via
        /// `receipt.get_metadata().post.digest()`
        pub post_state_digest: Vec<u8>,
        /// Journal data from the risc-zkvm Receipt object
        pub journal: Vec<u8>,
    }

    /// Session Status response
    #[derive(Deserialize, Serialize)]
    pub struct SnarkStatusRes {
        /// Current status
        ///
        /// values: `[ RUNNING | SUCCEEDED | FAILED | TIMED_OUT | ABORTED ]`
        pub status: String,
        /// SNARK receipt output
        ///
        /// Generated snark receipt,
        pub output: Option<SnarkReceipt>,
        /// Snark Error message
        ///
        /// If the SNARK status is not `RUNNING` or `SUCCEEDED`, this is the
        /// error raised from within bonsai.
        pub error_msg: Option<String>,
    }

    /// Bonsai supported versions
    #[derive(Deserialize, Serialize)]
    pub struct VersionInfo {
        /// Supported versions of the risc0-zkvm crate
        pub risc0_zkvm: Vec<String>,
    }

    /// User quotas and cycle budgets
    #[derive(Deserialize, Serialize)]
    pub struct Quotas {
        /// Executor cycle limit, in millions of cycles
        pub exec_cycle_limit: u64,
        /// Max parallel proving units
        pub max_parallelism: u64,
        /// Max concurrent proofs
        pub concurrent_proofs: u64,
        /// Current cycle budget remaining
        pub cycle_budget: u64,
        /// Lifetime cycles used
        pub cycle_usage: u64,
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

    /// Fetches the current status of the Session
    pub fn status(&self, client: &Client) -> Result<SessionStatusRes, SdkErr> {
        let url = format!("{}/sessions/status/{}", client.url, self.uuid);
        let res = client.client.get(url).send()?;

        if !res.status().is_success() {
            let body = res.text()?;
            return Err(SdkErr::InternalServerErr(body));
        }
        Ok(res.json::<SessionStatusRes>()?)
    }

    /// Fetches the zkvm guest logs for a session
    ///
    /// After the Execution phase of proving is completed, you can use this method
    /// to download the logs of the zkvm guest. This is a merged log of stderr and stdout
    /// <https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.ExecutorEnvBuilder.html#method.stdout>
    ///
    /// It should contain the output of all writes to those file descriptors. But does NOT include output
    /// from `env::log`
    pub fn logs(&self, client: &Client) -> Result<String, SdkErr> {
        let url = format!("{}/sessions/logs/{}", client.url, self.uuid);
        let res = client.client.get(url).send()?;

        if !res.status().is_success() {
            let body = res.text()?;
            return Err(SdkErr::InternalServerErr(body));
        }
        Ok(res.text()?)
    }
}

/// Stark2Snark Session representation
#[derive(Debug, Clone, PartialEq)]
pub struct SnarkId {
    /// Snark Session UUID
    pub uuid: String,
}

impl SnarkId {
    /// Construct a [SnarkId] from a UUID [String]
    pub fn new(uuid: String) -> Self {
        Self { uuid }
    }

    /// Fetches the current status of the Snark Session
    pub fn status(&self, client: &Client) -> Result<SnarkStatusRes, SdkErr> {
        let url = format!("{}/snark/status/{}", client.url, self.uuid);
        let res = client.client.get(url).send()?;

        if !res.status().is_success() {
            let body = res.text()?;
            return Err(SdkErr::InternalServerErr(body));
        }
        Ok(res.json::<SnarkStatusRes>()?)
    }
}

/// Represents a client of the REST api
#[derive(Clone)]
pub struct Client {
    pub(crate) url: String,
    pub(crate) client: BlockingClient,
}

enum ImageExistsOpt {
    Exists,
    New(ImgUploadRes),
}

/// Creates a [reqwest::Client] for internal connection pooling
fn construct_req_client(api_key: &str, version: &str) -> Result<BlockingClient, SdkErr> {
    let mut headers = header::HeaderMap::new();
    headers.insert(API_KEY_HEADER, header::HeaderValue::from_str(api_key)?);
    headers.insert(VERSION_HEADER, header::HeaderValue::from_str(version)?);

    Ok(BlockingClient::builder()
        .default_headers(headers)
        .pool_max_idle_per_host(0)
        .build()?)
}

impl Client {
    /// Construct a [Client] from env vars
    ///
    /// Uses the BONSAI_API_URL and BONSAI_API_KEY environment variables to
    /// construct a client. The risc0_version should be the crate version of the
    /// risc0-zkvm crate
    ///
    /// # Example:
    ///
    /// ```
    /// use bonsai_sdk::alpha as bonsai_sdk;
    /// bonsai_sdk::from_env(risc0_zkvm::VERSION)
    ///     .expect("Failed to construct sdk client");
    /// ```
    pub fn from_env(risc0_version: &str) -> Result<Self, SdkErr> {
        let api_url = std::env::var(API_URL_ENVVAR).map_err(|_| SdkErr::MissingApiUrl)?;
        let api_url = api_url.strip_suffix('/').unwrap_or(&api_url);
        let api_key = std::env::var(API_KEY_ENVVAR).map_err(|_| SdkErr::MissingApiKey)?;

        let client = construct_req_client(&api_key, risc0_version)?;

        Ok(Self {
            url: api_url.to_string(),
            client,
        })
    }

    /// Construct a [Client] from url, api key, and zkvm version
    ///
    /// # Example:
    ///
    /// ```
    /// use bonsai_sdk::alpha as bonsai_sdk;
    /// let url = "http://api.bonsai.xyz".to_string();
    /// let api_key = "my_secret_key".to_string();
    /// bonsai_sdk::from_parts(url, api_key, risc0_zkvm::VERSION)
    ///     .expect("Failed to construct sdk client");
    /// ```
    pub fn from_parts(url: String, key: String, risc0_version: &str) -> Result<Self, SdkErr> {
        let client = construct_req_client(&key, risc0_version)?;
        let url = url.strip_suffix('/').unwrap_or(&url).to_string();
        Ok(Self { url, client })
    }

    /// Fetch a upload presigned url for a given route
    fn get_upload_url(&self, route: &str) -> Result<UploadRes, SdkErr> {
        let res = self
            .client
            .get(format!("{}/{}/upload", self.url, route))
            .send()?;

        if !res.status().is_success() {
            let body = res.text()?;
            return Err(SdkErr::InternalServerErr(body));
        }

        Ok(res.json::<UploadRes>()?)
    }

    fn get_image_upload_url(&self, image_id: &str) -> Result<ImageExistsOpt, SdkErr> {
        let res = self
            .client
            .get(format!("{}/images/upload/{}", self.url, image_id))
            .send()?;

        if res.status() == 204 {
            return Ok(ImageExistsOpt::Exists);
        }

        if !res.status().is_success() {
            let body = res.text()?;
            return Err(SdkErr::InternalServerErr(body));
        }

        Ok(ImageExistsOpt::New(res.json::<ImgUploadRes>()?))
    }

    /// Upload body to a given URL
    fn put_data<T: Into<reqwest::blocking::Body>>(&self, url: &str, body: T) -> Result<(), SdkErr> {
        let res = self.client.put(url).body(body).send()?;
        if !res.status().is_success() {
            let body = res.text()?;
            return Err(SdkErr::InternalServerErr(body));
        }

        Ok(())
    }

    // - /images

    /// Upload a image buffer to the /images/ route
    ///
    /// The boolean return indicates if the image already exists in bonsai
    ///
    /// The image data can be either:
    /// * ELF file bytes
    /// * bincode encoded MemoryImage
    pub fn upload_img(&self, image_id: &str, buf: Vec<u8>) -> Result<bool, SdkErr> {
        let res_or_exists = self.get_image_upload_url(image_id)?;
        match res_or_exists {
            ImageExistsOpt::Exists => Ok(true),
            ImageExistsOpt::New(upload_res) => {
                self.put_data(&upload_res.url, buf)?;
                Ok(false)
            }
        }
    }

    /// Upload a image file to the /images/ route
    ///
    /// The boolean return indicates if the image already exists in bonsai
    ///
    /// The image data can be either:
    /// * ELF file bytes
    /// * bincode encoded MemoryImage
    pub fn upload_img_file(&self, image_id: &str, path: &Path) -> Result<bool, SdkErr> {
        let res_or_exists = self.get_image_upload_url(image_id)?;
        match res_or_exists {
            ImageExistsOpt::Exists => Ok(true),
            ImageExistsOpt::New(upload_res) => {
                let fd = File::open(path)?;
                self.put_data(&upload_res.url, fd)?;
                Ok(false)
            }
        }
    }

    // - /inputs

    /// Upload a input buffer to the /inputs/ route
    pub fn upload_input(&self, buf: Vec<u8>) -> Result<String, SdkErr> {
        let upload_data = self.get_upload_url("inputs")?;
        self.put_data(&upload_data.url, buf)?;
        Ok(upload_data.uuid)
    }

    /// Upload a input file to the /inputs/ route
    pub fn upload_input_file(&self, path: &Path) -> Result<String, SdkErr> {
        let upload_data = self.get_upload_url("inputs")?;

        let fd = File::open(path)?;
        self.put_data(&upload_data.url, fd)?;

        Ok(upload_data.uuid)
    }

    // - /sessions

    /// Create a new proof request Session
    ///
    /// Supply the image_id and input_id created from uploading those files in
    /// previous steps
    pub fn create_session(&self, img_id: String, input_id: String) -> Result<SessionId, SdkErr> {
        let url = format!("{}/sessions/create", self.url);

        let req = ProofReq {
            img: img_id,
            input: input_id,
        };

        let res = self.client.post(url).json(&req).send()?;

        if !res.status().is_success() {
            let body = res.text()?;
            return Err(SdkErr::InternalServerErr(body));
        }

        let res: CreateSessRes = res.json()?;

        Ok(SessionId::new(res.uuid))
    }

    // Utilities

    /// Download a given url to a buffer
    ///
    /// Useful to download a [SessionId] receipt_url
    pub fn download(&self, url: &str) -> Result<Vec<u8>, SdkErr> {
        let data = self.client.get(url).send()?.bytes()?;

        Ok(data.into())
    }

    // - /snark

    /// Requests a SNARK proof be created from a existing sessionId
    ///
    /// Supply a completed sessionId to convert the risc0 STARK proof into
    /// a SNARK proof that can be validated on ethereum-like blockchains
    pub fn create_snark(&self, session_id: String) -> Result<SnarkId, SdkErr> {
        let url = format!("{}/snark/create", self.url);

        let snark_req = SnarkReq { session_id };

        let res = self.client.post(url).json(&snark_req).send()?;

        if !res.status().is_success() {
            let body = res.text()?;
            return Err(SdkErr::InternalServerErr(body));
        }

        // Reuse the session response because its the same member format
        let res: CreateSessRes = res.json()?;

        Ok(SnarkId::new(res.uuid))
    }

    // - /version

    /// Fetches the current component versions from bonsai
    ///
    /// Fetches the risc0 zkvm supported versions as well as other
    /// sub-components of bonsai
    pub fn version(&self) -> Result<VersionInfo, SdkErr> {
        Ok(self
            .client
            .get(format!("{}/version", self.url))
            .send()?
            .json::<VersionInfo>()?)
    }

    // - /user

    /// Fetches your current users quotas
    ///
    /// Returns the [Quotas] structure with relevant data on cycle budget, quotas etc.
    pub fn quotas(&self) -> Result<Quotas, SdkErr> {
        Ok(self
            .client
            .get(format!("{}/user/quotas", self.url))
            .send()?
            .json::<Quotas>()?)
    }
}

#[cfg(test)]
mod tests {
    use httpmock::prelude::*;
    use uuid::Uuid;

    use super::*;

    const TEST_KEY: &str = "TESTKEY";
    const TEST_ID: &str = "0x5891b5b522d5df086d0ff0b110fbd9d21bb4fc7163af34d08286a2e846f6be03";
    const TEST_VERSION: &str = "0.1.0";

    #[test]
    fn client_from_parts() {
        let url = "http://127.0.0.1/stage".to_string();
        let apikey = TEST_KEY.to_string();
        let client = super::Client::from_parts(url.clone(), apikey, TEST_VERSION).unwrap();

        assert_eq!(client.url, url);
    }

    #[test]
    fn client_from_env() {
        let url = "http://127.0.0.1/stage".to_string();
        let apikey = TEST_KEY.to_string();
        temp_env::with_vars(
            vec![
                (API_URL_ENVVAR, Some(url.clone())),
                (API_KEY_ENVVAR, Some(apikey)),
            ],
            || {
                let client = super::Client::from_env(TEST_VERSION).unwrap();
                assert_eq!(client.url, url);
            },
        );
    }

    #[test]
    fn client_test_slash_strip() {
        let url = "http://127.0.0.1/".to_string();
        let apikey = TEST_KEY.to_string();
        temp_env::with_vars(
            vec![(API_URL_ENVVAR, Some(url)), (API_KEY_ENVVAR, Some(apikey))],
            || {
                let client = super::Client::from_env(TEST_VERSION).unwrap();
                assert_eq!(client.url, "http://127.0.0.1");
            },
        );
    }

    #[test]
    fn image_upload() {
        let data = vec![];

        let server = MockServer::start();

        let put_url = format!("http://{}/upload/{TEST_ID}", server.address());
        let response = ImgUploadRes { url: put_url };

        let get_mock = server.mock(|when, then| {
            when.method(GET)
                .path(format!("/images/upload/{TEST_ID}"))
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(200)
                .header("content-type", "application/json")
                .json_body_obj(&response);
        });

        let put_mock = server.mock(|when, then| {
            when.method(PUT).path(format!("/upload/{TEST_ID}"));
            then.status(200);
        });

        let server_url = format!("http://{}", server.address());
        let client = super::Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
            .expect("Failed to construct client");
        let exists = client
            .upload_img(TEST_ID, data)
            .expect("Failed to upload input");
        assert!(!exists);
        get_mock.assert();
        put_mock.assert();
    }

    #[test]
    fn image_upload_dup() {
        let data = vec![0x41];

        let server = MockServer::start();

        let put_url = format!("http://{}/upload/{TEST_ID}", server.address());
        let response = ImgUploadRes { url: put_url };

        server.mock(|when, then| {
            when.method(GET)
                .path(format!("/images/upload/{TEST_ID}"))
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(204).json_body_obj(&response);
        });

        server.mock(|when, then| {
            when.method(PUT).path(format!("/upload/{TEST_ID}"));
            then.status(200);
        });

        let server_url = format!("http://{}", server.address());
        let client = super::Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
            .expect("Failed to construct client");
        let exists = client.upload_img(TEST_ID, data).unwrap();
        assert!(exists);
    }

    #[test]
    fn input_upload() {
        // env_logger::init();
        let data = vec![];

        let server = MockServer::start();

        let input_uuid = Uuid::new_v4();
        let put_url = format!("http://{}/upload/{}", server.address(), input_uuid);
        let response = UploadRes {
            url: put_url,
            uuid: input_uuid.to_string(),
        };

        let get_mock = server.mock(|when, then| {
            when.method(GET)
                .path("/inputs/upload")
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(200)
                .header("content-type", "application/json")
                .json_body_obj(&response);
        });

        let put_mock = server.mock(|when, then| {
            when.method(PUT).path(format!("/upload/{}", input_uuid));
            then.status(200);
        });

        let server_url = format!("http://{}", server.address());
        let client = super::Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
            .expect("Failed to construct client");
        let res = client.upload_input(data).expect("Failed to upload input");

        assert_eq!(res, response.uuid);

        get_mock.assert();
        put_mock.assert();
    }

    #[test]
    fn session_create() {
        let server = MockServer::start();

        let request = ProofReq {
            img: TEST_ID.to_string(),
            input: Uuid::new_v4().to_string(),
        };
        let response = CreateSessRes {
            uuid: Uuid::new_v4().to_string(),
        };

        let create_mock = server.mock(|when, then| {
            when.method(POST)
                .path("/sessions/create")
                .header("content-type", "application/json")
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION)
                .json_body_obj(&request);
            then.status(200)
                .header("content-type", "application/json")
                .json_body_obj(&response);
        });

        let server_url = format!("http://{}", server.address());
        let client =
            super::Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION).unwrap();

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
            error_msg: None,
            state: None,
        };

        let create_mock = server.mock(|when, then| {
            when.method(GET)
                .path(format!("/sessions/status/{}", session_id.uuid))
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(200)
                .header("content-type", "application/json")
                .json_body_obj(&response);
        });

        let server_url = format!("http://{}", server.address());
        let client =
            super::Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION).unwrap();

        let status = session_id.status(&client).unwrap();
        assert_eq!(status.status, response.status);
        assert_eq!(status.receipt_url, None);

        create_mock.assert();
    }

    #[test]
    fn session_logs() {
        let server = MockServer::start();

        let uuid = Uuid::new_v4().to_string();
        let session_id = SessionId::new(uuid);
        let response = "Hello\nWorld";

        let create_mock = server.mock(|when, then| {
            when.method(GET)
                .path(format!("/sessions/logs/{}", session_id.uuid))
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(200)
                .header("content-type", "text/plain")
                .json_body_obj(&response);
        });

        let server_url = format!("http://{}", server.address());
        let client =
            super::Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION).unwrap();

        let logs = session_id.logs(&client).unwrap();

        assert_eq!(logs, "\"Hello\\nWorld\"");

        create_mock.assert();
    }

    #[test]
    fn snark_create() {
        let server = MockServer::start();

        let request = SnarkReq {
            session_id: Uuid::new_v4().to_string(),
        };
        let response = CreateSessRes {
            uuid: Uuid::new_v4().to_string(),
        };

        let create_mock = server.mock(|when, then| {
            when.method(POST)
                .path("/snark/create")
                .header("content-type", "application/json")
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION)
                .json_body_obj(&request);
            then.status(200)
                .header("content-type", "application/json")
                .json_body_obj(&response);
        });

        let server_url = format!("http://{}", server.address());
        let client =
            super::Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION).unwrap();

        let res = client.create_snark(request.session_id).unwrap();
        assert_eq!(res.uuid, response.uuid);

        create_mock.assert();
    }

    #[test]
    fn snark_status() {
        let server = MockServer::start();

        let uuid = Uuid::new_v4().to_string();
        let snark_id = SnarkId::new(uuid);
        let response = SnarkStatusRes {
            status: "RUNNING".to_string(),
            output: None,
            error_msg: None,
        };

        let create_mock = server.mock(|when, then| {
            when.method(GET)
                .path(format!("/snark/status/{}", snark_id.uuid))
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(200)
                .header("content-type", "application/json")
                .json_body_obj(&response);
        });

        let server_url = format!("http://{}", server.address());
        let client =
            super::Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION).unwrap();

        let status = snark_id.status(&client).unwrap();
        assert_eq!(status.status, response.status);
        assert_eq!(status.output, None);

        create_mock.assert();
    }

    #[test]
    fn version() {
        let server = MockServer::start();

        let response = VersionInfo {
            risc0_zkvm: vec![TEST_VERSION.into()],
        };

        let get_mock = server.mock(|when, then| {
            when.method(GET)
                .path("/version")
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(200)
                .header("content-type", "application/json")
                .json_body_obj(&response);
        });

        let server_url = format!("http://{}", server.address());
        let client = super::Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
            .expect("Failed to construct client");
        let info = client.version().expect("Failed to fetch version route");
        assert_eq!(&info.risc0_zkvm[0], TEST_VERSION);
        get_mock.assert();
    }

    #[test]
    fn quotas() {
        let server = MockServer::start();

        let response = Quotas {
            concurrent_proofs: 10,
            cycle_budget: 100000,
            cycle_usage: 1000000,
            exec_cycle_limit: 500,
            max_parallelism: 2,
        };

        let get_mock = server.mock(|when, then| {
            when.method(GET)
                .path("/user/quotas")
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(200)
                .header("content-type", "application/json")
                .json_body_obj(&response);
        });

        let server_url = format!("http://{}", server.address());
        let client = super::Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
            .expect("Failed to construct client");
        let quota = client.quotas().expect("Failed to fetch version route");
        assert_eq!(quota.concurrent_proofs, response.concurrent_proofs);
        assert_eq!(quota.cycle_budget, response.cycle_budget);
        assert_eq!(quota.cycle_usage, response.cycle_usage);
        assert_eq!(quota.exec_cycle_limit, response.exec_cycle_limit);
        assert_eq!(quota.max_parallelism, response.max_parallelism);

        get_mock.assert();
    }
}
