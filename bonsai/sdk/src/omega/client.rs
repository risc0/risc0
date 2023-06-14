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

//! An asynchronous Client API.

use std::{
    borrow::Borrow,
    io::{BufWriter, Write},
};

use anyhow::Context;
use reqwest::{header, Client as AsyncClient, Response};
use risc0_zkvm::{recursion::SessionRollupReceipt, MemoryImage, Program};

use super::{
    routes::{IMAGE_ROUTE, RECEIPT_ROUTE, SESSION_ROUTE},
    types::{
        CreationRequest, ImageID, ImageResponse, ProofID, ReceiptInfo, ReceiptRequest,
        ReceiptResponse, SessionID, SessionInfo, SessionRequest, SessionResponse,
    },
};

/// The Errors that may occur when processing a [Client] request.
#[derive(Debug, thiserror::Error)]
pub enum ClientError {
    /// An error returned by the Bonsai API.
    #[error("API error: {0}")]
    Api(String),
    /// A network error returned by the HTTP client.
    #[error("Request error")]
    Network(#[from] reqwest::Error),
    /// An IO error.
    #[error("IO Error")]
    IO(#[from] std::io::Error),
    /// An otherwise unspecified error.
    #[error("Unspecified error")]
    Anyhow(#[from] anyhow::Error),
}

/// An asynchronous `Client` for the Bonsai REST API.
#[derive(Debug, Clone)]
pub struct Client {
    pub(crate) client: AsyncClient,
    pub(crate) url: String,
}

impl Client {
    /// Construct a [Client] from the API URL and API key.
    pub fn new(
        api_url: impl Into<String>,
        api_key: impl Into<String>,
    ) -> Result<Client, ClientError> {
        let mut headers = header::HeaderMap::new();

        let mut auth_value =
            header::HeaderValue::from_str(&api_key.into()).context("invalid API key value")?;
        auth_value.set_sensitive(true);
        headers.insert("x-api-key", auth_value);

        let client = AsyncClient::builder()
            .default_headers(headers)
            .gzip(true)
            .build()?;

        Ok(Self {
            client,
            url: api_url.into(),
        })
    }

    /// Upload a [MemoryImage] to Bonsai.
    pub async fn put_image(&self, image: &MemoryImage) -> Result<ImageResponse, ClientError> {
        let bytes = serialize_memory_image(image)?;
        let res = self
            .client
            .put(format!("{}{IMAGE_ROUTE}", self.url))
            .header(header::CONTENT_TYPE, "application/octet-stream")
            .body(bytes)
            .send()
            .await?;

        Ok(error_for_status(res).await?.json().await?)
    }

    /// Upload an ELF file buffer to Bonsai.
    pub async fn put_image_from_elf(
        &self,
        elf: impl AsRef<[u8]>,
    ) -> Result<ImageResponse, ClientError> {
        let image = new_memory_image(elf.as_ref())?;
        self.put_image(&image).await
    }

    /// Request a session of the given image and input from Bonsai.
    pub async fn request_session(
        &self,
        image_id: impl Into<ImageID>,
        input: impl Into<Vec<u8>>,
    ) -> Result<SessionResponse, ClientError> {
        let request = SessionRequest::Create(CreationRequest {
            image_id: image_id.into(),
            input: input.into(),
        });
        let res = self
            .client
            .post(format!("{}{SESSION_ROUTE}", self.url))
            .json(&request)
            .send()
            .await?;
        Ok(error_for_status(res).await?.json().await?)
    }

    /// Download information about the specified session from Bonsai.
    pub async fn get_session_info(
        &self,
        session_id: impl Borrow<SessionID>,
    ) -> Result<SessionInfo, ClientError> {
        let session_id = session_id.borrow();
        let res = self
            .client
            .get(format!("{}{SESSION_ROUTE}/{session_id}", self.url))
            .send()
            .await?;
        Ok(error_for_status(res).await?.json().await?)
    }

    /// Request a receipt of the given image and input from Bonsai.
    pub async fn request_receipt(
        &self,
        image_id: impl Into<ImageID>,
        input: impl Into<Vec<u8>>,
    ) -> Result<ReceiptResponse, ClientError> {
        let request = ReceiptRequest::Create(CreationRequest {
            image_id: image_id.into(),
            input: input.into(),
        });
        let res = self
            .client
            .post(format!("{}{RECEIPT_ROUTE}", self.url))
            .json(&request)
            .send()
            .await?;
        Ok(error_for_status(res).await?.json().await?)
    }

    /// Request a receipt of the given session from Bonsai.
    pub async fn request_receipt_from_session(
        &self,
        session_id: impl Into<SessionID>,
    ) -> Result<ReceiptResponse, ClientError> {
        let request = ReceiptRequest::Session {
            session_id: session_id.into(),
        };
        let res = self
            .client
            .post(format!("{}{RECEIPT_ROUTE}", self.url))
            .json(&request)
            .send()
            .await?;
        Ok(error_for_status(res).await?.json().await?)
    }

    /// Download information about the specified receipt from Bonsai.
    pub async fn get_receipt_info(
        &self,
        receipt_id: impl Borrow<ProofID>,
    ) -> Result<ReceiptInfo, ClientError> {
        let receipt_id = receipt_id.borrow();
        let res: Response = self
            .client
            .get(format!("{}{RECEIPT_ROUTE}/{receipt_id}", self.url))
            .send()
            .await?;
        Ok(error_for_status(res).await?.json().await?)
    }

    /// Download the final [SessionRollupReceipt] from Bonsai.
    pub async fn get_receipt(
        &self,
        receipt_id: impl Borrow<ProofID>,
    ) -> Result<SessionRollupReceipt, ClientError> {
        let receipt_id = receipt_id.borrow();
        let res = self
            .client
            .get(format!("{}{RECEIPT_ROUTE}/{receipt_id}/data", self.url))
            .send()
            .await?;
        let bytes = error_for_status(res).await?.bytes().await?;
        Ok(bincode::deserialize(&bytes).context("failed to deserialize")?)
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

/// Create a [MemoryImage] from an ELF.
fn new_memory_image(elf: &[u8]) -> Result<MemoryImage, anyhow::Error> {
    let program =
        Program::load_elf(elf, risc0_zkvm::MEM_SIZE as u32).context("failed to load elf")?;
    let image = MemoryImage::new(&program, risc0_zkvm::PAGE_SIZE as u32)
        .context("failed to construct memory image")?;
    Ok(image)
}

/// Serializes a [MemoryImage] into a `Vec` of bytes using zstd compression.
fn serialize_memory_image(image: &MemoryImage) -> Result<Vec<u8>, anyhow::Error> {
    let mut bytes = Vec::new();
    let mut encoder = zstd::Encoder::new(&mut bytes, 0)?;
    {
        let mut writer = BufWriter::new(&mut encoder);
        bincode::serialize_into(&mut writer, image).context("failed to serialize")?;
        writer.flush().context("failed to flush buffer")?;
    }
    encoder.do_finish().context("failed to flush encoder")?;

    Ok(bytes)
}

#[cfg(test)]
mod tests {
    use risc0_zkvm::recursion::{ReceiptMeta, SegmentRecursionReceipt, SystemState};
    use risc0_zkvm_methods::{MULTI_TEST_ELF, MULTI_TEST_ID};
    use semver::Version;
    use uuid::{uuid, Uuid};
    use wiremock::{
        matchers::{method, path},
        Mock, MockServer, ResponseTemplate,
    };

    use super::{
        types::{ReceiptStatus, SessionStatus, H256},
        *,
    };

    const ID: Uuid = uuid!("67e55044-10b1-426f-9247-bb680e5fe0c8");
    const VERSION: Version = Version::new(0, 0, 0);

    #[tokio::test]
    async fn put_image() {
        let server = MockServer::start().await;
        Mock::given(method("PUT"))
            .and(path(format!("{IMAGE_ROUTE}")))
            .respond_with(ResponseTemplate::new(200).set_body_json(ImageResponse {
                image_id: H256::from_full_digest_words(MULTI_TEST_ID),
            }))
            .mount(&server)
            .await;

        let client = Client::new(server.uri(), "").unwrap();
        let image = new_memory_image(MULTI_TEST_ELF).unwrap();
        client.put_image(&image).await.unwrap();
    }

    #[tokio::test]
    async fn put_image_from_elf() {
        let server = MockServer::start().await;
        Mock::given(method("PUT"))
            .and(path(format!("{IMAGE_ROUTE}")))
            .respond_with(ResponseTemplate::new(200).set_body_json(ImageResponse {
                image_id: H256::from_full_digest_words(MULTI_TEST_ID),
            }))
            .mount(&server)
            .await;

        let client = Client::new(server.uri(), "").unwrap();
        client.put_image_from_elf(MULTI_TEST_ELF).await.unwrap();
    }

    #[tokio::test]
    async fn request_session() {
        let server = MockServer::start().await;
        Mock::given(method("POST"))
            .and(path(format!("{SESSION_ROUTE}")))
            .respond_with(
                ResponseTemplate::new(200).set_body_json(&SessionResponse { session_id: ID }),
            )
            .mount(&server)
            .await;

        let client = Client::new(server.uri(), "").unwrap();
        client
            .request_session(H256::default(), vec![])
            .await
            .unwrap();
    }

    #[tokio::test]
    async fn get_session_info() {
        let server = MockServer::start().await;
        Mock::given(method("GET"))
            .and(path(format!("{SESSION_ROUTE}/{ID}")))
            .respond_with(ResponseTemplate::new(200).set_body_json(&SessionInfo {
                version: VERSION,
                status: SessionStatus::Pending,
            }))
            .mount(&server)
            .await;

        let client = Client::new(server.uri(), "").unwrap();
        client.get_session_info(ID).await.unwrap();
    }

    #[tokio::test]
    async fn request_receipt() {
        let server = MockServer::start().await;
        Mock::given(method("POST"))
            .and(path(format!("{RECEIPT_ROUTE}")))
            .respond_with(ResponseTemplate::new(200).set_body_json(&ReceiptResponse {
                receipt_id: ID,
                session_id: ID,
            }))
            .mount(&server)
            .await;

        let client = Client::new(server.uri(), "").unwrap();
        client
            .request_receipt(H256::default(), vec![])
            .await
            .unwrap();
    }

    #[tokio::test]
    async fn request_receipt_from_session() {
        let server = MockServer::start().await;
        Mock::given(method("POST"))
            .and(path(format!("{RECEIPT_ROUTE}")))
            .respond_with(ResponseTemplate::new(200).set_body_json(&ReceiptResponse {
                receipt_id: ID,
                session_id: ID,
            }))
            .mount(&server)
            .await;

        let client = Client::new(server.uri(), "").unwrap();
        client.request_receipt_from_session(ID).await.unwrap();
    }

    #[tokio::test]
    async fn get_receipt_info() {
        let server = MockServer::start().await;
        Mock::given(method("GET"))
            .and(path(format!("{RECEIPT_ROUTE}/{ID}")))
            .respond_with(ResponseTemplate::new(200).set_body_json(&ReceiptInfo {
                version: VERSION,
                status: ReceiptStatus::Pending { progress: 0 },
            }))
            .mount(&server)
            .await;

        let client = Client::new(server.uri(), "").unwrap();
        client.get_receipt_info(ID).await.unwrap();
    }

    #[tokio::test]
    async fn get_receipt() {
        // create empty (default) receipt
        let receipt: SessionRollupReceipt = SessionRollupReceipt {
            receipt: SegmentRecursionReceipt {
                seal: Default::default(),
                control_id: Default::default(),
                meta: ReceiptMeta {
                    input: Default::default(),
                    pre: SystemState {
                        pc: 0,
                        image_id: Default::default(),
                    },
                    post: SystemState {
                        pc: 0,
                        image_id: Default::default(),
                    },
                    sys_exit: 0,
                    user_exit: 0,
                    output: Default::default(),
                },
            },
            journal: Default::default(),
        };

        let server = MockServer::start().await;
        Mock::given(method("GET"))
            .and(path(format!("{RECEIPT_ROUTE}/{ID}/data")))
            .respond_with(
                ResponseTemplate::new(200).set_body_bytes(bincode::serialize(&receipt).unwrap()),
            )
            .mount(&server)
            .await;

        let client = Client::new(server.uri(), "").unwrap();
        client.get_receipt(ID).await.unwrap();
    }
}
