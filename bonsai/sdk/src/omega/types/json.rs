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

use semver::Version;
use serde::{Deserialize, Serialize};
use serde_with::{base64::Base64, serde_as};
use time::{format_description::well_known::Rfc3339, OffsetDateTime};

use super::{ImageID, ProofID, SessionID};

/// Information about an uploaded `MemoryImage`.
#[serde_as]
#[derive(Debug, Deserialize, Serialize, Clone, PartialEq)]
#[cfg_attr(feature = "utoipa", derive(utoipa::ToSchema))]
#[serde(rename_all = "camelCase")]
pub struct ImageInfo {
    /// The corresponding ZKVM version.
    #[cfg_attr(feature = "utoipa", schema(value_type = String, example = "0.0.0"))]
    pub version: Version,
    /// Image expiration.
    #[serde_as(as = "Option<Rfc3339>")]
    pub expires_at: Option<OffsetDateTime>,
}

/// API response for an uploaded `MemoryImage`.
#[derive(Debug, Deserialize, Serialize, Clone, PartialEq)]
#[cfg_attr(feature = "utoipa", derive(utoipa::ToSchema))]
#[serde(rename_all = "camelCase")]
pub struct ImageResponse {
    /// The ID of the uploaded `MemoryImage`.
    #[cfg_attr(feature = "utoipa", schema(value_type = String, example = "03AC674216F3E15C761EE1A5E255F067953623C8B388B4459E13F978D7C846F4"))]
    pub image_id: ImageID,
}

/// Information about a created `Session` request.
#[derive(Debug, Deserialize, Serialize, Clone, PartialEq)]
#[cfg_attr(feature = "utoipa", derive(utoipa::ToSchema))]
#[serde(rename_all = "camelCase")]
pub struct SessionInfo {
    /// The corresponding ZKVM version.
    #[cfg_attr(feature = "utoipa", schema(value_type = String, example = "0.0.0"))]
    pub version: Version,
    /// Execution status of the session.
    pub status: SessionStatus,
}

/// Status of a created `Session` request.
#[derive(Debug, Deserialize, Serialize, Clone, PartialEq)]
#[cfg_attr(feature = "utoipa", derive(utoipa::ToSchema))]
#[serde(rename_all = "camelCase")]
pub enum SessionStatus {
    /// Session execution in progress.
    Pending,
    /// Session execution failed.
    Failed {
        /// Error message for the failure.
        error: String,
    },
    /// Session execution finished successfully.
    Finished {
        /// The number of cycles used to execute the session.
        cycle_count: u64,
        /// Number of segments in the session.
        segment_count: u32,
    },
}

/// Request part to crate a new `Session` or `Receipt`.
#[serde_as]
#[derive(Debug, Deserialize, Serialize, Clone, PartialEq)]
#[cfg_attr(feature = "utoipa", derive(utoipa::ToSchema))]
#[serde(rename_all = "camelCase")]
pub struct CreationRequest {
    /// ID of the corresponding guest `MemoryImage`.
    #[cfg_attr(feature = "utoipa", schema(value_type = String, example = "03AC674216F3E15C761EE1A5E255F067953623C8B388B4459E13F978D7C846F4"))]
    pub image_id: ImageID,
    /// Input for the guest.
    #[serde_as(as = "Base64")]
    #[cfg_attr(feature = "utoipa", schema(value_type = String, format = Byte, example = "AAAAAQ=="))]
    pub input: Vec<u8>,
}

/// API request to crate a new `Session`.
#[derive(Debug, Deserialize, Serialize, Clone, PartialEq)]
#[cfg_attr(feature = "utoipa", derive(utoipa::ToSchema))]
#[serde(rename_all = "camelCase")]
pub enum SessionRequest {
    /// Create a session without proving.
    Create(CreationRequest),
}

/// API response for a [SessionRequest].
#[derive(Debug, Deserialize, Serialize, Clone, PartialEq)]
#[cfg_attr(feature = "utoipa", derive(utoipa::ToSchema))]
#[serde(rename_all = "camelCase")]
pub struct SessionResponse {
    /// ID of the session.
    #[cfg_attr(feature = "utoipa", schema(value_type = String, format = Uuid))]
    pub session_id: SessionID,
}

/// Information about a created `Receipt` request.
#[derive(Debug, Deserialize, Serialize, Clone, PartialEq)]
#[cfg_attr(feature = "utoipa", derive(utoipa::ToSchema))]
#[serde(rename_all = "camelCase")]
pub struct ReceiptInfo {
    /// The corresponding ZKVM version.
    #[cfg_attr(feature = "utoipa", schema(value_type = String, example = "0.0.0"))]
    pub version: Version,
    /// Status of the receipt computation.
    pub status: ReceiptStatus,
}

/// Status of a created `Receipt` request.
#[derive(Debug, Deserialize, Serialize, Clone, PartialEq)]
#[cfg_attr(feature = "utoipa", derive(utoipa::ToSchema))]
#[serde(rename_all = "camelCase")]
pub enum ReceiptStatus {
    /// Receipt computation in progress.
    Pending {
        /// Progress of the computation from 0 to 255.
        progress: u8,
    },
    /// Receipt computation failed.
    Failed {
        /// Error message for the failure.
        error: String,
    },
    /// Receipt computation finished successfully.
    Finished,
}

/// API request to crate a new `Receipt`.
#[derive(Debug, Deserialize, Serialize, Clone, PartialEq)]
#[cfg_attr(feature = "utoipa", derive(utoipa::ToSchema))]
#[serde(rename_all = "camelCase")]
pub enum ReceiptRequest {
    /// Create a receipt of a new session.
    Create(CreationRequest),
    /// Create a receipt of an existing session.
    Session {
        /// ID of the session to proof.
        #[cfg_attr(feature = "utoipa", schema(value_type = String, format = Uuid))]
        session_id: SessionID,
    },
}

/// API response for a [ReceiptRequest].
#[derive(Debug, Deserialize, Serialize, Clone, PartialEq)]
#[cfg_attr(feature = "utoipa", derive(utoipa::ToSchema))]
#[serde(rename_all = "camelCase")]
pub struct ReceiptResponse {
    /// ID of the receipt.
    #[cfg_attr(feature = "utoipa", schema(value_type = String, format = Uuid))]
    pub receipt_id: ProofID,
    /// ID of the session.
    #[cfg_attr(feature = "utoipa", schema(value_type = String, format = Uuid))]
    pub session_id: SessionID,
}
