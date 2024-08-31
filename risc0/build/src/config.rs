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

use std::path::PathBuf;

use cargo_metadata::Package;
use serde::{Deserialize, Serialize};

/// Options for configuring a docker build environment.
#[derive(Clone, Serialize, Deserialize)]
pub struct DockerOptions {
    /// Specify the root directory for docker builds.
    ///
    /// The current working directory is used if `None` is specified.
    pub root_dir: Option<PathBuf>,
}

/// Options defining how to embed a guest package in
/// [`crate::embed_methods_with_options`].
#[derive(Default, Clone)]
pub struct GuestOptions {
    /// Features for cargo to build the guest with.
    pub features: Vec<String>,

    /// Use a docker environment for building.
    pub use_docker: Option<DockerOptions>,
}

#[derive(Debug, Deserialize)]
pub(crate) struct Risc0Metadata {
    /// List of methods to build.
    pub(crate) methods: Vec<String>,

    /// Configuration flags to build the guest with.
    #[serde(rename = "rustc-flags")]
    pub(crate) rustc_flags: Option<Vec<String>>,
}

impl From<&Package> for Risc0Metadata {
    fn from(pkg: &Package) -> Self {
        let obj = pkg.metadata.get("risc0").unwrap();
        serde_json::from_value(obj.clone()).unwrap()
    }
}

/// Extended options defining how to embed a guest package in
/// [`crate::embed_methods_with_options`].
#[derive(Default, Clone)]
pub(crate) struct GuestBuildOptions {
    /// Features for cargo to build the guest with.
    pub(crate) features: Vec<String>,

    /// Use a docker environment for building.
    pub(crate) use_docker: Option<DockerOptions>,

    /// Configuration flags to build the guest with.
    pub(crate) rustc_flags: Vec<String>,
}

impl From<GuestOptions> for GuestBuildOptions {
    fn from(value: GuestOptions) -> Self {
        Self {
            features: value.features,
            use_docker: value.use_docker,
            ..Default::default()
        }
    }
}

impl GuestBuildOptions {
    pub(crate) fn with_metadata(mut self, metadata: &Risc0Metadata) -> Self {
        self.rustc_flags = metadata.rustc_flags.clone().unwrap_or_default();
        self
    }
}
