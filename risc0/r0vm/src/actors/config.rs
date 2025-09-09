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

use std::{
    net::{IpAddr, Ipv4Addr, SocketAddr},
    path::PathBuf,
};

use risc0_zkvm::DevModeDelay;
use serde::{Deserialize, Serialize};

use crate::actors::protocol::TaskKind;

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct VersionConfig {
    pub version: usize,
}

#[derive(Debug, Serialize, Deserialize, Eq, PartialEq)]
pub(crate) struct AppConfig {
    pub api: Option<ApiConfig>,
    pub manager: Option<ManagerConfig>,
    pub worker: Option<Vec<WorkerConfig>>,
    pub storage: Option<StorageConfig>,
    pub telemetry: Option<TelemetryConfig>,
}

#[derive(Debug, Serialize, Deserialize, Eq, PartialEq)]
pub(crate) struct ApiConfig {
    pub listen: Option<SocketAddr>,
    pub manager: Option<SocketAddr>,
}

#[derive(Debug, Serialize, Deserialize, Eq, PartialEq)]
pub(crate) struct ManagerConfig {
    pub listen: Option<SocketAddr>,
}

#[derive(Debug, Serialize, Deserialize, Eq, PartialEq)]
pub(crate) struct WorkerConfig {
    pub manager: Option<SocketAddr>,
    pub count: Option<usize>,
    pub subscribe: Vec<TaskKind>,
    pub simulate: Option<DevModeDelay>,
}

#[derive(Debug, Serialize, Deserialize, Eq, PartialEq)]
pub(crate) struct StorageConfig {
    pub path: PathBuf,
}

#[derive(Debug, Serialize, Deserialize, Eq, PartialEq)]
pub(crate) struct TelemetryConfig {
    // TODO
}

impl Default for AppConfig {
    fn default() -> Self {
        Self {
            api: Some(ApiConfig {
                listen: Some(default_api_listen_addr()),
                manager: None,
            }),
            manager: Some(ManagerConfig {
                listen: Some(default_manager_listen_addr()),
            }),
            worker: Some(vec![WorkerConfig {
                manager: None,
                count: None,
                subscribe: vec![
                    TaskKind::Execute,
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

pub(crate) fn default_manager_listen_addr() -> SocketAddr {
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
                api: Some(ApiConfig {
                    listen: Some(SocketAddr::from_str("0.0.0.0:8000").unwrap()),
                    manager: Some(SocketAddr::from_str("1.2.3.4:9000").unwrap()),
                }),
                manager: None,
                worker: None,
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
                api: Some(ApiConfig {
                    listen: Some(SocketAddr::from_str("0.0.0.0:8000").unwrap()),
                    manager: None,
                }),
                manager: Some(ManagerConfig {
                    listen: Some(SocketAddr::from_str("0.0.0.0:9000").unwrap())
                }),
                worker: Some(vec![WorkerConfig {
                    manager: None,
                    count: Some(4),
                    simulate: None,
                    subscribe: vec![TaskKind::Execute]
                }]),
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
                api: None,
                manager: None,
                worker: Some(vec![
                    WorkerConfig {
                        manager: Some(SocketAddr::from_str("10.0.3.24:9000").unwrap()),
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
                    WorkerConfig {
                        manager: Some(SocketAddr::from_str("10.0.3.24:9000").unwrap()),
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
