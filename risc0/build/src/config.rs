// Copyright 2025 RISC Zero, Inc.
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

use std::{env, path::PathBuf};

use cargo_metadata::Package;
use derive_builder::Builder;
use risc0_zkos_v1compat::V1COMPAT_ELF;
use serde::{Deserialize, Serialize};

use crate::DEFAULT_DOCKER_TAG;

/// Options for configuring a docker build environment.
#[derive(Clone, Debug, Default, Serialize, Deserialize, Builder)]
#[builder(default)]
#[non_exhaustive]
pub struct DockerOptions {
    /// Specify the root directory for docker builds.
    ///
    /// The current working directory is used if this option is unspecified.
    #[builder(setter(into, strip_option))]
    pub root_dir: Option<PathBuf>,

    /// Additional environment variables for the build container.
    pub env: Vec<(String, String)>,

    /// Docker container tag to use
    #[builder(setter(into, strip_option))]
    pub docker_container_tag: Option<String>,
}

impl DockerOptions {
    /// Get the configured root dir, or current working directory if None.
    pub fn root_dir(&self) -> PathBuf {
        self.root_dir
            .clone()
            .unwrap_or_else(|| env::current_dir().unwrap())
    }

    /// Get the configured custom environment variables.
    pub fn env(&self) -> Vec<(&str, &str)> {
        self.env
            .iter()
            .map(|(key, val)| (key.as_str(), val.as_str()))
            .collect()
    }

    /// Get the docker container tag, or default container tag if none
    ///
    /// This value may be set by using the `RISC0_DOCKER_CONTAINER_TAG` environment variable.
    pub fn docker_container_tag(&self) -> String {
        if let Ok(tag) = env::var("RISC0_DOCKER_CONTAINER_TAG") {
            return tag;
        }

        self.docker_container_tag
            .clone()
            .unwrap_or(DEFAULT_DOCKER_TAG.to_string())
    }
}

/// Options defining how to embed a guest package in
/// [`crate::embed_methods_with_options`].
///
/// ```
/// use risc0_build::{DockerOptionsBuilder, GuestOptionsBuilder};
///
/// let docker_options = DockerOptionsBuilder::default()
///     .root_dir("../../")
///     .env(vec![("ENV_VAR".to_string(), "value".to_string())])
///     .build()
///     .unwrap();
///
/// let guest_options = GuestOptionsBuilder::default()
///     .features(vec!["my-features".to_string()])
///     .use_docker(docker_options)
///     .build()
///     .unwrap();
/// ```
#[derive(Default, Clone, Debug, Builder)]
#[builder(default)]
#[non_exhaustive]
pub struct GuestOptions {
    /// Features for cargo to build the guest with.
    pub features: Vec<String>,

    /// Use a docker environment for building.
    #[builder(setter(strip_option))]
    pub use_docker: Option<DockerOptions>,

    /// Override the default kernel ELF to be used for execution.
    #[builder(setter(strip_option))]
    pub kernel: Option<Vec<u8>>,
}

impl GuestOptions {
    /// Get the kernel ELF to be used for execution.
    pub fn kernel(&self) -> Vec<u8> {
        self.kernel.clone().unwrap_or_else(|| V1COMPAT_ELF.to_vec())
    }
}

/// Metadata defining options to build a guest
#[derive(Serialize, Deserialize, Clone, Default)]
pub(crate) struct GuestMetadata {
    /// Configuration flags to build the guest with.
    #[serde(rename = "rustc-flags")]
    pub(crate) rustc_flags: Option<Vec<String>>,

    /// Indicates whether the guest program is a kernel.
    #[serde(default)]
    pub(crate) kernel: bool,
}

impl From<&Package> for GuestMetadata {
    fn from(pkg: &Package) -> Self {
        let Some(obj) = pkg.metadata.get("risc0") else {
            return Default::default();
        };
        serde_json::from_value(obj.clone()).unwrap()
    }
}

/// Extended options defining how to embed a guest package in
/// [`crate::embed_methods_with_options`].
#[derive(Default, Clone)]
pub(crate) struct GuestInfo {
    /// Options specified by build script or library usage.
    pub(crate) options: GuestOptions,

    /// Metadata specified in guest crate `Cargo.toml`.
    pub(crate) metadata: GuestMetadata,
}
