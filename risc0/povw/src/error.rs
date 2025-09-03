// Copyright 2025 RISC Zero, Inc.
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

use risc0_binfmt::PovwLogId;

/// Error types for the RISC Zero PoVW crate.
#[derive(thiserror::Error, Debug)]
#[non_exhaustive]
pub enum Error {
    /// A log ID is already occupied in the work set.
    #[error("log id 0x{id:020x} is already occupied")]
    LogIdOccupied {
        /// The log ID that is already occupied.
        id: PovwLogId,
    },

    /// A job ID is already occupied in the work log.
    #[error("job id 0x{id:08x} is already occupied")]
    JobIdOccupied {
        /// The job ID that is already occupied.
        id: u64,
    },

    /// Bitmap indicates non-inclusion but inclusion was expected during verification.
    #[error("bitmap indicates non-inclusion but inclusion was expected")]
    BitmapNonInclusion,

    /// Bitmap indicates inclusion but non-inclusion was expected during verification.
    #[error("bitmap indicates inclusion but non-inclusion was expected")]
    BitmapInclusion,

    /// Merkle path root does not match the expected commitment root.
    #[error("merkle path root does not match expected root")]
    PathRootMismatch,

    /// An I/O error occurred during operations such as serialization or deserialization.
    #[error("serialization error")]
    SerializationError(#[from] std::io::Error),
}
