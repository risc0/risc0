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

use std::{
    net::{IpAddr, Ipv4Addr, SocketAddr},
    path::PathBuf,
};

use risc0_zkvm::DevModeDelay;
use serde::{Deserialize, Serialize};

use crate::actors::protocol::TaskKind;

pub const VERSION: usize = 1;

#[derive(Clone, Debug, Serialize, Deserialize)]
#[serde(rename_all = "kebab-case")]
pub(crate) struct VersionConfig {
    pub version: usize,
}

#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
#[serde(rename_all = "kebab-case")]
pub(crate) struct AppConfig {
    pub version: usize,
    pub release_channel: Option<String>,
    pub api: Option<ApiConfig>,
    pub manager: Option<ManagerConfig>,
    pub allocator: Option<AllocatorConfig>,
    pub executor: Option<ExecutorConfig>,
    pub prover: Option<Vec<ProverConfig>>,
    pub storage: Option<StorageConfig>,
    pub telemetry: Option<TelemetryConfig>,
}

#[derive(Clone, Default, Debug, Serialize, Deserialize, Eq, PartialEq)]
#[serde(rename_all = "kebab-case")]
pub(crate) struct ApiConfig {
    pub listen: Option<SocketAddr>,
}

#[derive(Clone, Default, Debug, Serialize, Deserialize, Eq, PartialEq)]
#[serde(rename_all = "kebab-case")]
pub(crate) struct ManagerConfig {
    pub listen: Option<IpAddr>,
    pub allocator: Option<SocketAddr>,
    pub api_po2: Option<u32>,
}

#[derive(Clone, Default, Debug, Serialize, Deserialize, PartialEq)]
#[serde(rename_all = "kebab-case")]
pub(crate) struct AllocatorConfig {
    pub listen: Option<SocketAddr>,
    pub default_release_channel: Option<String>,
    pub worker_queuing_factor: Option<f32>,
}

#[derive(Clone, Default, Debug, Serialize, Deserialize, Eq, PartialEq)]
#[serde(rename_all = "kebab-case")]
pub(crate) struct ExecutorConfig {
    pub allocator: Option<SocketAddr>,
    pub count: usize,
}

#[derive(Clone, Default, Debug, Serialize, Deserialize, Eq, PartialEq)]
#[serde(rename_all = "kebab-case")]
pub(crate) struct ProverConfig {
    pub allocator: Option<SocketAddr>,
    pub count: Option<usize>,
    pub subscribe: Vec<TaskKind>,
    pub simulate: Option<DevModeDelay>,
}

#[derive(Clone, Debug, Serialize, Deserialize, Eq, PartialEq)]
#[serde(rename_all = "kebab-case")]
pub(crate) struct StorageConfig {
    pub path: PathBuf,
}

#[derive(Clone, Debug, Serialize, Deserialize, Eq, PartialEq)]
#[serde(rename_all = "kebab-case")]
pub(crate) struct TelemetryConfig {
    // Marker struct: presence of `[telemetry]` section in TOML enables OpenTelemetry/OTLP
    // initialization (logs, traces, metrics) in `actors::App`. Export endpoints and filtering
    // are configured via environment variables (e.g. OTEL_*, RUST_LOG).
}

impl Default for AppConfig {
    fn default() -> Self {
        Self {
            version: VERSION,
            release_channel: None,
            api: Some(ApiConfig {
                listen: Some(default_api_listen_addr()),
            }),
            manager: Some(ManagerConfig {
                allocator: None,
                listen: None,
                api_po2: None,
            }),
            allocator: Some(AllocatorConfig {
                listen: Some(default_allocator_listen_addr()),
                default_release_channel: None,
                worker_queuing_factor: None,
            }),
            executor: Some(ExecutorConfig {
                allocator: None,
                count: 1,
            }),
            prover: Some(vec![ProverConfig {
                allocator: None,
                count: None,
                subscribe: vec![
                    TaskKind::ProveSegment,
                    TaskKind::ProveKeccak,
                    TaskKind::Lift,
                    TaskKind::Join,
                    TaskKind::Union,
                    TaskKind::Resolve,
                ],
                simulate: None,
            }]),
            storage: None,
            telemetry: None,
        }
    }
}

pub(crate) fn default_api_listen_addr() -> SocketAddr {
    SocketAddr::new(IpAddr::V4(Ipv4Addr::LOCALHOST), 8000)
}

pub(crate) fn default_allocator_listen_addr() -> SocketAddr {
    SocketAddr::new(IpAddr::V4(Ipv4Addr::LOCALHOST), 9000)
}

#[cfg(test)]
mod tests {
    use std::{net::SocketAddr, str::FromStr as _};

    use super::*;

    #[test]
    fn default() {
        let version: VersionConfig =
            toml::from_str(include_str!("../../testdata/default.toml")).unwrap();
        assert_eq!(version.version, 1);

        let app: AppConfig = toml::from_str(include_str!("../../testdata/default.toml")).unwrap();
        assert_eq!(app, AppConfig::default());
    }

    #[test]
    fn api() {
        let app: AppConfig = toml::from_str(include_str!("../../testdata/api.toml")).unwrap();
        assert_eq!(
            app,
            AppConfig {
                version: 1,
                release_channel: None,
                api: Some(ApiConfig {
                    listen: Some(SocketAddr::from_str("0.0.0.0:8000").unwrap()),
                }),
                manager: None,
                allocator: None,
                executor: None,
                prover: None,
                storage: Some(StorageConfig {
                    path: PathBuf::from_str("/mnt/storage/risc0").unwrap()
                }),
                telemetry: None
            }
        );
    }

    #[test]
    fn manager() {
        let app: AppConfig = toml::from_str(include_str!("../../testdata/manager.toml")).unwrap();
        assert_eq!(
            app,
            AppConfig {
                version: 1,
                release_channel: None,
                api: Some(ApiConfig {
                    listen: Some(SocketAddr::from_str("0.0.0.0:8000").unwrap()),
                }),
                manager: Some(ManagerConfig {
                    allocator: None,
                    listen: None,
                    api_po2: Some(21),
                }),
                allocator: Some(AllocatorConfig {
                    listen: Some(SocketAddr::from_str("0.0.0.0:9000").unwrap()),
                    default_release_channel: None,
                    worker_queuing_factor: None
                }),
                executor: Some(ExecutorConfig {
                    allocator: None,
                    count: 4,
                }),
                prover: None,
                storage: Some(StorageConfig {
                    path: PathBuf::from_str("/mnt/storage/risc0").unwrap()
                }),
                telemetry: Some(TelemetryConfig {})
            }
        );
    }

    #[test]
    fn prover() {
        let app: AppConfig = toml::from_str(include_str!("../../testdata/prover.toml")).unwrap();
        assert_eq!(
            app,
            AppConfig {
                version: 1,
                release_channel: None,
                api: None,
                manager: None,
                allocator: None,
                executor: None,
                prover: Some(vec![
                    ProverConfig {
                        allocator: Some(SocketAddr::from_str("10.0.3.24:9000").unwrap()),
                        count: None,
                        simulate: None,
                        subscribe: vec![
                            TaskKind::ProveSegment,
                            TaskKind::ProveKeccak,
                            TaskKind::Lift,
                            TaskKind::Join,
                            TaskKind::Union,
                            TaskKind::Resolve,
                        ]
                    },
                    ProverConfig {
                        allocator: Some(SocketAddr::from_str("10.0.3.24:9000").unwrap()),
                        count: None,
                        simulate: None,
                        subscribe: vec![
                            TaskKind::Lift,
                            TaskKind::Join,
                            TaskKind::Union,
                            TaskKind::Resolve,
                        ]
                    }
                ]),
                storage: None,
                telemetry: Some(TelemetryConfig {})
            }
        );
    }
}
