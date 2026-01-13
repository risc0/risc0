// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use thiserror::Error;

#[derive(Debug, Error, Clone, PartialEq, Eq)]
pub enum RzupError {
    #[error("Component not found: {0}")]
    ComponentNotFound(String),

    #[error("Installation failed: {0}")]
    InstallationFailed(String),

    #[error("Invalid version: {0}")]
    InvalidVersion(String),

    #[error("Version not found: {0}")]
    VersionNotFound(semver::Version),

    #[error("IO error: {0}")]
    Io(String),

    #[error("Environment error: {0}")]
    Environment(String),

    #[error("{0}")]
    Other(String),

    #[error("Rate limited: {0}")]
    RateLimited(String),

    #[error("Unsupported platform: {0}")]
    UnsupportedPlatform(String),

    #[error("Unsupported distribution platform: {0}")]
    UnsupportedDistributionPlatform(String),

    #[error("SHA-256 sum mismatch: expected = {expected}, actual = {actual}")]
    Sha256Mismatch { expected: String, actual: String },

    #[error("Signature failed to verify: {0}")]
    InvalidSignature(String),
}

impl From<std::io::Error> for RzupError {
    fn from(e: std::io::Error) -> Self {
        RzupError::Io(e.to_string())
    }
}

impl From<semver::Error> for RzupError {
    fn from(e: semver::Error) -> Self {
        Self::InvalidVersion(e.to_string())
    }
}
pub type Result<T> = std::result::Result<T, RzupError>;
