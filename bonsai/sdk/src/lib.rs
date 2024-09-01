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

#![deny(missing_docs)]
#![cfg_attr(docsrs, feature(doc_cfg, doc_auto_cfg))]

//! A library to handle HTTP REST requests to the Bonsai-alpha prover interface
//!
//! Both blocking and non-blocking (async) versions of the module are available.
//!
//! ## Example Usage
//!
//! ```no_run
//! # mod methods {
//! #   pub const METHOD_ELF: &[u8] = &[];
//! #   pub const METHOD_ID: [u32; 8] = [0, 0, 0, 0, 0, 0, 0, 0];
//! # }
//! use std::time::Duration;
//!
//! use anyhow::Result;
//! use bonsai_sdk::blocking::Client;
//! use methods::{METHOD_ELF, METHOD_ID};
//! use risc0_zkvm::{compute_image_id, serde::to_vec, Receipt};
//!
//! fn run_bonsai(input_data: Vec<u8>) -> Result<()> {
//!     let client = Client::from_env(risc0_zkvm::VERSION)?;
//!
//!     // Compute the image_id, then upload the ELF with the image_id as its key.
//!     let image_id = hex::encode(compute_image_id(METHOD_ELF)?);
//!     client.upload_img(&image_id, METHOD_ELF.to_vec())?;
//!
//!     // Prepare input data and upload it.
//!     let input_data = to_vec(&input_data).unwrap();
//!     let input_data = bytemuck::cast_slice(&input_data).to_vec();
//!     let input_id = client.upload_input(input_data)?;
//!
//!     // Add a list of assumptions
//!     let assumptions: Vec<String> = vec![];
//!
//!     // Wether to run in execute only mode
//!     let execute_only = false;
//!
//!     // Start a session running the prover
//!     let session = client.create_session(image_id, input_id, assumptions, execute_only)?;
//!     loop {
//!         let res = session.status(&client)?;
//!         if res.status == "RUNNING" {
//!             eprintln!(
//!                 "Current status: {} - state: {} - continue polling...",
//!                 res.status,
//!                 res.state.unwrap_or_default()
//!             );
//!             std::thread::sleep(Duration::from_secs(15));
//!             continue;
//!         }
//!         if res.status == "SUCCEEDED" {
//!             // Download the receipt, containing the output
//!             let receipt_url = res
//!                 .receipt_url
//!                 .expect("API error, missing receipt on completed session");
//!
//!             let receipt_buf = client.download(&receipt_url)?;
//!             let receipt: Receipt = bincode::deserialize(&receipt_buf)?;
//!             receipt
//!                 .verify(METHOD_ID)
//!                 .expect("Receipt verification failed");
//!         } else {
//!             panic!(
//!                 "Workflow exited: {} - | err: {}",
//!                 res.status,
//!                 res.error_msg.unwrap_or_default()
//!             );
//!         }
//!
//!         break;
//!     }
//!
//!     // Optionally run stark2snark
//!     // run_stark2snark(session.uuid)?;
//!
//!     Ok(())
//! }
//!
//! ```
//!
//! ## STARK to SNARK
//!
//! After a STARK proof is generated, it is possible to convert the proof to SNARK.
//!
//! ### Example
//!
//! ```no_run
//! use std::time::Duration;
//!
//! use anyhow::Result;
//! use bonsai_sdk::blocking::Client;
//!
//! fn run_stark2snark(session_id: String) -> Result<()> {
//!     let client = Client::from_env(risc0_zkvm::VERSION)?;
//!
//!     let snark_session = client.create_snark(session_id)?;
//!     eprintln!("Created snark session: {}", snark_session.uuid);
//!     loop {
//!         let res = snark_session.status(&client)?;
//!         match res.status.as_str() {
//!             "RUNNING" => {
//!                 eprintln!("Current status: {} - continue polling...", res.status,);
//!                 std::thread::sleep(Duration::from_secs(15));
//!                 continue;
//!             }
//!             "SUCCEEDED" => {
//!                 let snark_receipt = res.output;
//!                 eprintln!("Snark proof!: {snark_receipt:?}");
//!                 break;
//!             }
//!             _ => {
//!                 panic!(
//!                     "Workflow exited: {} err: {}",
//!                     res.status,
//!                     res.error_msg.unwrap_or_default()
//!                 );
//!             }
//!         }
//!     }
//!     Ok(())
//! }
//! ```

use self::responses::{
    CreateSessRes, ImgUploadRes, ProofReq, Quotas, ReceiptDownload, SessionStatusRes, SnarkReq,
    SnarkStatusRes, UploadRes, VersionInfo,
};
use duplicate::duplicate_item;
use reqwest::header;
use serde::{Deserialize, Serialize};
use std::path::Path;
use thiserror::Error;

/// HTTP header key for the API key
pub const API_KEY_HEADER: &str = "x-api-key";
/// HTTP header for the risc0 version string
pub const VERSION_HEADER: &str = "x-risc0-version";
/// Environment variable name for the API url
pub const API_URL_ENVVAR: &str = "BONSAI_API_URL";
/// Environment variable name for the API key
pub const API_KEY_ENVVAR: &str = "BONSAI_API_KEY";

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
    HttpHeaderErr(#[from] header::InvalidHeaderValue),
    /// Missing BONSAI_API_KEY
    #[error("missing BONSAI_API_KEY env var")]
    MissingApiKey,
    /// Missing BONSAI_API_URL
    #[error("missing BONSAI_API_URL env var")]
    MissingApiUrl,
    /// Missing file
    #[error("failed to find file on disk: {0:?}")]
    FileNotFound(#[from] std::io::Error),
    /// Receipt not found
    #[error("Receipt not found")]
    ReceiptNotFound,
}

enum ImageExistsOpt {
    Exists,
    New(ImgUploadRes),
}

/// Collection of serialization object for the REST api
pub mod responses {
    use risc0_groth16::Seal;
    use serde::{Deserialize, Serialize};

    /// Response of an upload request
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
        /// List of receipt UUIDs
        pub assumptions: Vec<String>,
        /// Execute Only Mode
        pub execute_only: bool,
    }

    /// Session statistics metadata file
    #[derive(Serialize, Deserialize)]
    pub struct SessionStats {
        /// Count of segments in this proof request
        pub segments: usize,
        /// Total cycles run within guest
        pub total_cycles: u64,
        /// User cycles run within guest, slightly below total overhead cycles
        pub cycles: u64,
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
        /// * `ProveSegments: N/M`
        /// * `Planner`
        /// * `Recursion`
        /// * `RecursionJoin: N/M`
        /// * `Resolve`
        /// * `Finalize`
        /// * `InProgress`
        pub state: Option<String>,
        /// Elapsed Time
        ///
        /// Elapsed time for a given session, in seconds
        pub elapsed_time: Option<f64>,
        /// Successful Session Stats
        ///
        /// Stats for a given successful session. Returns:
        /// - Count of segments in this proof request
        /// - User cycles run within guest, slightly below total overhead cycles
        pub stats: Option<SessionStats>,
    }

    /// Response of the receipt/download method
    #[derive(Deserialize, Serialize)]
    pub struct ReceiptDownload {
        /// Pre-Signed URL that the receipt can be downloaded (GET) from
        pub url: String,
    }

    /// Snark proof request object
    #[derive(Deserialize, Serialize)]
    pub struct SnarkReq {
        /// Existing Session ID from [super::SessionId]
        pub session_id: String,
    }

    /// Snark Receipt object
    ///
    /// All relevant data to verify both the snark proof a corresponding
    /// imageId on chain.
    #[derive(Debug, Deserialize, Serialize, PartialEq)]
    pub struct SnarkReceipt {
        /// SNARK Groth16 seal object encoded in big endian
        pub snark: Seal,
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
        pub exec_cycle_limit: i64,
        /// Max concurrent proofs
        pub concurrent_proofs: i64,
        /// Current cycle budget remaining
        pub cycle_budget: i64,
        /// Lifetime cycles used
        pub cycle_usage: i64,
        /// Dedicated Executor
        pub dedicated_executor: i32,
        /// Dedicated GPU
        pub dedicated_gpu: i32,
    }
}

#[cfg_attr(feature = "non_blocking",
duplicate_item(
    [
        module_type      [non_blocking]
        maybe_async_attr [maybe_async::must_be_async]
        File             [tokio::fs::File]
        HttpBody         [reqwest::Body]
        HttpClient       [reqwest::Client]
    ]
    [
        module_type      [blocking]
        maybe_async_attr [maybe_async::must_be_sync]
        File             [std::fs::File]
        HttpBody         [reqwest::blocking::Body]
        HttpClient       [reqwest::blocking::Client]
    ]
))]
#[cfg_attr(not(feature = "non_blocking"),
duplicate_item(
    [
        module_type      [blocking]
        maybe_async_attr [maybe_async::must_be_sync]
        File             [std::fs::File]
        HttpBody         [reqwest::blocking::Body]
        HttpClient       [reqwest::blocking::Client]
    ]
))]
/// Client module async/async
pub mod module_type {
    use super::*;

    /// Represents a client of the REST API
    #[derive(Clone)]
    pub struct Client {
        pub(crate) url: String,
        pub(crate) client: HttpClient,
    }

    /// Proof Session representation
    #[derive(Debug, Clone, PartialEq, Eq, Serialize, Deserialize)]
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
        #[maybe_async_attr]
        pub async fn status(&self, client: &Client) -> Result<SessionStatusRes, SdkErr> {
            let url = format!("{}/sessions/status/{}", client.url, self.uuid);
            let res = client.client.get(url).send().await?;

            if !res.status().is_success() {
                let body = res.text().await?;
                return Err(SdkErr::InternalServerErr(body));
            }
            Ok(res.json::<SessionStatusRes>().await?)
        }

        /// Fetches the zkvm guest logs for a session
        ///
        /// After the Execution phase of proving is completed, you can use this method
        /// to download the logs of the zkvm guest. This is a merged log of stderr and stdout
        /// <https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.ExecutorEnvBuilder.html#method.stdout>
        ///
        /// It should contain the output of all writes to those file descriptors. But does NOT include output
        /// from `env::log`
        #[maybe_async_attr]
        pub async fn logs(&self, client: &Client) -> Result<String, SdkErr> {
            let url = format!("{}/sessions/logs/{}", client.url, self.uuid);
            let res = client.client.get(url).send().await?;

            if !res.status().is_success() {
                let body = res.text().await?;
                return Err(SdkErr::InternalServerErr(body));
            }
            Ok(res.text().await?)
        }

        /// Stops a running proving session
        #[maybe_async_attr]
        pub async fn stop(&self, client: &Client) -> Result<(), SdkErr> {
            let url = format!("{}/sessions/stop/{}", client.url, self.uuid);
            let res = client.client.get(url).send().await?;
            if !res.status().is_success() {
                let body = res.text().await?;
                return Err(SdkErr::InternalServerErr(body));
            }
            Ok(())
        }

        /// Fetchs a journal from execute_only jobs
        ///
        /// After the Execution phase of a execute_only session it is possible to fetch the journal
        /// contents from the executor
        #[maybe_async_attr]
        pub async fn exec_only_journal(&self, client: &Client) -> Result<Vec<u8>, SdkErr> {
            let url = format!("{}/sessions/exec_only_journal/{}", client.url, self.uuid);
            let res = client.client.get(url).send().await?;

            if !res.status().is_success() {
                let body = res.text().await?;
                return Err(SdkErr::InternalServerErr(body));
            }
            Ok(res.bytes().await?.to_vec())
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
        #[maybe_async_attr]
        pub async fn status(&self, client: &Client) -> Result<SnarkStatusRes, SdkErr> {
            let url = format!("{}/snark/status/{}", client.url, self.uuid);
            let res = client.client.get(url).send().await?;

            if !res.status().is_success() {
                let body = res.text().await?;
                return Err(SdkErr::InternalServerErr(body));
            }
            Ok(res.json::<SnarkStatusRes>().await?)
        }
    }

    /// Creates a [reqwest::Client] for internal connection pooling
    fn construct_req_client(api_key: &str, version: &str) -> Result<HttpClient, SdkErr> {
        let mut headers = header::HeaderMap::new();
        headers.insert(API_KEY_HEADER, header::HeaderValue::from_str(api_key)?);
        headers.insert(VERSION_HEADER, header::HeaderValue::from_str(version)?);

        Ok(HttpClient::builder()
            .default_headers(headers)
            .pool_max_idle_per_host(0)
            .build()?)
    }

    impl Client {
        /// Construct a [Client] from url, api key, and zkvm version
        ///
        /// # Example (blocking):
        ///
        /// ```no_run
        /// use bonsai_sdk;
        /// let url = "http://api.bonsai.xyz".to_string();
        /// let api_key = "my_secret_key".to_string();
        /// bonsai_sdk::blocking::Client::from_parts(url, api_key, risc0_zkvm::VERSION)
        ///     .expect("Failed to construct sdk client");
        /// ```
        #[cfg_attr(
            feature = "non_blocking",
            doc = r##"
# Example (non-blocking):

```no_run
use bonsai_sdk;
let url = "http://api.bonsai.xyz".to_string();
let api_key = "my_secret_key".to_string();
bonsai_sdk::non_blocking::Client::from_parts(url, api_key, risc0_zkvm::VERSION)
    .expect("Failed to construct sdk client");
```
"##
        )]
        pub fn from_parts(url: String, key: String, risc0_version: &str) -> Result<Self, SdkErr> {
            let client = construct_req_client(&key, risc0_version)?;
            let url = url.strip_suffix('/').unwrap_or(&url).to_string();
            Ok(Self { url, client })
        }

        /// Construct a [Client] from env vars
        ///
        /// Uses the BONSAI_API_URL and BONSAI_API_KEY environment variables to
        /// construct a client. The risc0_version should be the crate version of the
        /// risc0-zkvm crate
        ///
        /// # Example (blocking):
        ///
        /// ```no_run
        /// use bonsai_sdk;
        /// bonsai_sdk::blocking::Client::from_env(risc0_zkvm::VERSION)
        ///     .expect("Failed to construct sdk client");
        /// ```
        ///
        ///
        #[cfg_attr(
            feature = "non_blocking",
            doc = r##"
# Example (non-blocking):

```no_run
use bonsai_sdk;
bonsai_sdk::non_blocking::Client::from_env(risc0_zkvm::VERSION)
    .expect("Failed to construct sdk client");
```
"##
        )]
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

        #[maybe_async_attr]
        async fn get_image_upload_url(&self, image_id: &str) -> Result<ImageExistsOpt, SdkErr> {
            let res = self
                .client
                .get(format!("{}/images/upload/{}", self.url, image_id))
                .send()
                .await?;

            if res.status() == 204 {
                return Ok(ImageExistsOpt::Exists);
            }

            if !res.status().is_success() {
                let body = res.text().await?;
                return Err(SdkErr::InternalServerErr(body));
            }

            Ok(ImageExistsOpt::New(res.json::<ImgUploadRes>().await?))
        }

        /// Upload body to a given URL
        #[maybe_async_attr]
        async fn put_data<T: Into<HttpBody>>(&self, url: &str, body: T) -> Result<(), SdkErr> {
            let res = self.client.put(url).body(body).send().await?;
            if !res.status().is_success() {
                let body = res.text().await?;
                return Err(SdkErr::InternalServerErr(body));
            }

            Ok(())
        }

        /// Upload a image buffer to the /images/ route
        ///
        /// The boolean return indicates if the image already exists in bonsai
        ///
        /// The image data can be either:
        /// * ELF file bytes
        /// * bincode encoded MemoryImage
        #[maybe_async_attr]
        pub async fn upload_img(&self, image_id: &str, buf: Vec<u8>) -> Result<bool, SdkErr> {
            let res_or_exists = self.get_image_upload_url(image_id).await?;
            match res_or_exists {
                ImageExistsOpt::Exists => Ok(true),
                ImageExistsOpt::New(upload_res) => {
                    self.put_data(&upload_res.url, buf).await?;
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
        #[maybe_async_attr]
        pub async fn upload_img_file(&self, image_id: &str, path: &Path) -> Result<bool, SdkErr> {
            let res_or_exists = self.get_image_upload_url(image_id).await?;
            match res_or_exists {
                ImageExistsOpt::Exists => Ok(true),
                ImageExistsOpt::New(upload_res) => {
                    let fd = File::open(path).await?;
                    self.put_data(&upload_res.url, fd).await?;
                    Ok(false)
                }
            }
        }

        /// Fetch a upload presigned url for a given route
        #[maybe_async_attr]
        async fn get_upload_url(&self, route: &str) -> Result<UploadRes, SdkErr> {
            let res = self
                .client
                .get(format!("{}/{}/upload", self.url, route))
                .send()
                .await?;

            if !res.status().is_success() {
                let body = res.text().await?;
                return Err(SdkErr::InternalServerErr(body));
            }

            Ok(res.json::<UploadRes>().await?)
        }

        /// Upload a input buffer to the /inputs/ route
        #[maybe_async_attr]
        pub async fn upload_input(&self, buf: Vec<u8>) -> Result<String, SdkErr> {
            let upload_data = self.get_upload_url("inputs").await?;
            self.put_data(&upload_data.url, buf).await?;
            Ok(upload_data.uuid)
        }

        /// Upload a input file to the /inputs/ route
        #[maybe_async_attr]
        pub async fn upload_input_file(&self, path: &Path) -> Result<String, SdkErr> {
            let upload_data = self.get_upload_url("inputs").await?;

            let fd = File::open(path).await?;
            self.put_data(&upload_data.url, fd).await?;

            Ok(upload_data.uuid)
        }

        /// Upload a receipt buffer to the /receipts/ route
        #[maybe_async_attr]
        pub async fn upload_receipt(&self, buf: Vec<u8>) -> Result<String, SdkErr> {
            let upload_data = self.get_upload_url("receipts").await?;
            self.put_data(&upload_data.url, buf).await?;
            Ok(upload_data.uuid)
        }

        /// Upload a receipt file to the /receipts/ route
        #[maybe_async_attr]
        pub async fn upload_receipt_file(&self, path: &Path) -> Result<String, SdkErr> {
            let upload_data = self.get_upload_url("receipts").await?;

            let fd = File::open(path).await?;
            self.put_data(&upload_data.url, fd).await?;

            Ok(upload_data.uuid)
        }

        /// Download a existing receipt
        ///
        /// Allows download of older receipts without checking the current session status.
        #[maybe_async_attr]
        pub async fn receipt_download(&self, session_id: &SessionId) -> Result<Vec<u8>, SdkErr> {
            let res = self
                .client
                .get(format!("{}/receipts/{}", self.url, session_id.uuid))
                .send()
                .await?;

            if !res.status().is_success() {
                if res.status() == reqwest::StatusCode::NOT_FOUND {
                    return Err(SdkErr::ReceiptNotFound);
                }
                let body = res.text().await?;
                return Err(SdkErr::InternalServerErr(body));
            }

            let res: ReceiptDownload = res.json().await?;
            self.download(&res.url).await
        }

        /// Delete an existing image
        ///
        /// Allows deletion of a specified image_id.
        #[maybe_async_attr]
        pub async fn image_delete(&self, image_id: &str) -> Result<(), SdkErr> {
            let res = self
                .client
                .delete(format!("{}/images/{}", self.url, image_id))
                .send()
                .await?;

            if !res.status().is_success() {
                let body = res.text().await?;
                return Err(SdkErr::InternalServerErr(body));
            }

            Ok(())
        }

        /// Delete an existing input
        ///
        /// Allows deletion of a specified input Uuid.
        #[maybe_async_attr]
        pub async fn input_delete(&self, input_uuid: &str) -> Result<(), SdkErr> {
            let res = self
                .client
                .delete(format!("{}/inputs/{}", self.url, input_uuid))
                .send()
                .await?;

            if !res.status().is_success() {
                let body = res.text().await?;
                return Err(SdkErr::InternalServerErr(body));
            }

            Ok(())
        }

        // - /sessions

        /// Create a new proof request Session
        ///
        /// Supply the image_id and input_id created from uploading those files in
        /// previous steps
        #[maybe_async_attr]
        pub async fn create_session(
            &self,
            img_id: String,
            input_id: String,
            assumptions: Vec<String>,
            execute_only: bool,
        ) -> Result<SessionId, SdkErr> {
            let url = format!("{}/sessions/create", self.url);

            let req = ProofReq {
                img: img_id,
                input: input_id,
                assumptions,
                execute_only,
            };

            let res = self.client.post(url).json(&req).send().await?;

            if !res.status().is_success() {
                let body = res.text().await?;
                return Err(SdkErr::InternalServerErr(body));
            }

            let res: CreateSessRes = res.json().await?;

            Ok(SessionId::new(res.uuid))
        }

        // Utilities

        /// Download a given url to a buffer
        ///
        /// Useful to download a [SessionId] receipt_url
        #[maybe_async_attr]
        pub async fn download(&self, url: &str) -> Result<Vec<u8>, SdkErr> {
            let data = self.client.get(url).send().await?.bytes().await?;

            Ok(data.into())
        }

        // - /snark

        /// Requests a SNARK proof be created from a existing sessionId
        ///
        /// Supply a completed sessionId to convert the risc0 STARK proof into
        /// a SNARK proof that can be validated on ethereum-like blockchains
        #[maybe_async_attr]
        pub async fn create_snark(&self, session_id: String) -> Result<SnarkId, SdkErr> {
            let url = format!("{}/snark/create", self.url);

            let snark_req = SnarkReq { session_id };

            let res = self.client.post(url).json(&snark_req).send().await?;

            if !res.status().is_success() {
                let body = res.text().await?;
                return Err(SdkErr::InternalServerErr(body));
            }

            // Reuse the session response because its the same member format
            let res: CreateSessRes = res.json().await?;

            Ok(SnarkId::new(res.uuid))
        }

        // - /version

        /// Fetches the current component versions from bonsai
        ///
        /// Fetches the risc0 zkvm supported versions as well as other
        /// sub-components of bonsai
        #[maybe_async_attr]
        pub async fn version(&self) -> Result<VersionInfo, SdkErr> {
            Ok(self
                .client
                .get(format!("{}/version", self.url))
                .send()
                .await?
                .json::<VersionInfo>()
                .await?)
        }

        // - /user

        /// Fetches your current users quotas
        ///
        /// Returns the [Quotas] structure with relevant data on cycle budget, quotas etc.
        #[maybe_async_attr]
        pub async fn quotas(&self) -> Result<Quotas, SdkErr> {
            Ok(self
                .client
                .get(format!("{}/user/quotas", self.url))
                .send()
                .await?
                .json::<Quotas>()
                .await?)
        }
    }
}

#[cfg(test)]
mod tests {
    use httpmock::prelude::*;
    use uuid::Uuid;

    use super::*;
    use blocking::{Client, SessionId, SnarkId};

    const TEST_KEY: &str = "TESTKEY";
    const TEST_ID: &str = "0x5891b5b522d5df086d0ff0b110fbd9d21bb4fc7163af34d08286a2e846f6be03";
    const TEST_VERSION: &str = "0.1.0";

    #[test]
    fn client_from_parts() {
        let url = "http://127.0.0.1/stage".to_string();
        let apikey = TEST_KEY.to_string();
        let client = Client::from_parts(url.clone(), apikey, TEST_VERSION).unwrap();

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
                let client = Client::from_env(TEST_VERSION).unwrap();
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
                let client = Client::from_env(TEST_VERSION).unwrap();
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
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
            .expect("Failed to construct client");
        let exists = client
            .upload_img(TEST_ID, data)
            .expect("Failed to upload input");
        assert!(!exists);
        get_mock.assert();
        put_mock.assert();
    }

    #[cfg(feature = "non_blocking")]
    #[tokio::test]
    async fn image_upload_async() {
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
        let client =
            super::non_blocking::Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
                .expect("Failed to construct client");
        let exists = client
            .upload_img(TEST_ID, data)
            .await
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
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
            .expect("Failed to construct client");
        let exists = client.upload_img(TEST_ID, data).unwrap();
        assert!(exists);
    }

    #[test]
    fn image_delete() {
        let server = MockServer::start();

        let del_mock = server.mock(|when, then| {
            when.method(DELETE)
                .path(format!("/images/{TEST_ID}"))
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(200);
        });

        let server_url = format!("http://{}", server.address());
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
            .expect("Failed to construct client");
        client.image_delete(TEST_ID).unwrap();
        del_mock.assert();
    }

    #[test]
    fn input_upload() {
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
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
            .expect("Failed to construct client");
        let res = client.upload_input(data).expect("Failed to upload input");

        assert_eq!(res, response.uuid);

        get_mock.assert();
        put_mock.assert();
    }

    #[test]
    fn input_delete() {
        let server = MockServer::start();

        let del_mock = server.mock(|when, then| {
            when.method(DELETE)
                .path(format!("/inputs/{TEST_ID}"))
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(200);
        });

        let server_url = format!("http://{}", server.address());
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
            .expect("Failed to construct client");
        client.input_delete(TEST_ID).unwrap();
        del_mock.assert();
    }

    #[test]
    fn receipt_upload() {
        let data = vec![];

        let server = MockServer::start();

        let receipt_uuid = Uuid::new_v4();
        let put_url = format!("http://{}/upload/{}", server.address(), receipt_uuid);
        let response = UploadRes {
            url: put_url,
            uuid: receipt_uuid.to_string(),
        };

        let get_mock = server.mock(|when, then| {
            when.method(GET)
                .path("/receipts/upload")
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(200)
                .header("content-type", "application/json")
                .json_body_obj(&response);
        });

        let put_mock = server.mock(|when, then| {
            when.method(PUT).path(format!("/upload/{}", receipt_uuid));
            then.status(200);
        });

        let server_url = format!("http://{}", server.address());
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
            .expect("Failed to construct client");
        let res = client
            .upload_receipt(data)
            .expect("Failed to upload receipt");

        assert_eq!(res, response.uuid);

        get_mock.assert();
        put_mock.assert();
    }

    #[test]
    fn receipt_download() {
        let server = MockServer::start();
        let receipt_uuid = Uuid::new_v4();

        let download_method = "download_path";
        let download_url = format!("http://{}/{download_method}", server.address());
        let response = ReceiptDownload { url: download_url };

        let get_mock = server.mock(|when, then| {
            when.method(GET)
                .path(format!("/receipts/{}", receipt_uuid))
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(200)
                .header("content-type", "application/json")
                .json_body_obj(&response);
        });

        let receipt_data: Vec<u8> = vec![0x41, 0x41, 0x42, 0x42];
        let download_mock = server.mock(|when, then| {
            when.method(GET)
                .path(format!("/{download_method}"))
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);

            then.body(&receipt_data).status(200);
        });

        let server_url = format!("http://{}", server.address());
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
            .expect("Failed to construct client");
        let res = client
            .receipt_download(&SessionId {
                uuid: receipt_uuid.to_string(),
            })
            .expect("Failed to upload receipt");

        println!("{}", std::str::from_utf8(&res).unwrap());
        assert_eq!(res, receipt_data);

        get_mock.assert();
        download_mock.assert();
    }

    #[test]
    fn session_create() {
        let server = MockServer::start();

        let request = ProofReq {
            img: TEST_ID.to_string(),
            input: Uuid::new_v4().to_string(),
            assumptions: vec![],
            execute_only: false,
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
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION).unwrap();

        let res = client
            .create_session(
                request.img,
                request.input,
                request.assumptions,
                request.execute_only,
            )
            .unwrap();
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
            elapsed_time: None,
            stats: None,
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
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION).unwrap();

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
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION).unwrap();

        let logs = session_id.logs(&client).unwrap();

        assert_eq!(logs, "\"Hello\\nWorld\"");

        create_mock.assert();
    }

    #[test]
    fn session_exec_only_journal() {
        let server = MockServer::start();

        let uuid = Uuid::new_v4().to_string();
        let session_id = SessionId::new(uuid);
        let response = vec![0x41, 0x41, 0x41, 0x41];

        let create_mock = server.mock(|when, then| {
            when.method(GET)
                .path(format!("/sessions/exec_only_journal/{}", session_id.uuid))
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(200)
                .header("content-type", "text/plain")
                .body(&response);
        });

        let server_url = format!("http://{}", server.address());
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION).unwrap();

        let journal = session_id.exec_only_journal(&client).unwrap();

        assert_eq!(journal, response);

        create_mock.assert();
    }

    #[test]
    fn session_stop() {
        let server = MockServer::start();

        let uuid = Uuid::new_v4().to_string();
        let session_id = SessionId::new(uuid);

        let create_mock = server.mock(|when, then| {
            when.method(GET)
                .path(format!("/sessions/stop/{}", session_id.uuid))
                .header(API_KEY_HEADER, TEST_KEY)
                .header(VERSION_HEADER, TEST_VERSION);
            then.status(200).header("content-type", "text/plain");
        });

        let server_url = format!("http://{}", server.address());
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION).unwrap();

        session_id.stop(&client).unwrap();
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
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION).unwrap();

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
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION).unwrap();

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
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
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
            dedicated_executor: 0,
            dedicated_gpu: 0,
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
        let client = Client::from_parts(server_url, TEST_KEY.to_string(), TEST_VERSION)
            .expect("Failed to construct client");
        let quota = client.quotas().expect("Failed to fetch version route");
        assert_eq!(quota.concurrent_proofs, response.concurrent_proofs);
        assert_eq!(quota.cycle_budget, response.cycle_budget);
        assert_eq!(quota.cycle_usage, response.cycle_usage);
        assert_eq!(quota.exec_cycle_limit, response.exec_cycle_limit);
        assert_eq!(quota.dedicated_executor, response.dedicated_executor);
        assert_eq!(quota.dedicated_gpu, response.dedicated_gpu);

        get_mock.assert();
    }
}
