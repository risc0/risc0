// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
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
pub(crate) struct VersionConfig {
    pub version: usize,
}

#[derive(Clone, Debug, Serialize, Deserialize, Eq, PartialEq)]
pub(crate) struct AppConfig {
    pub version: usize,
    pub api: Option<ApiConfig>,
    pub manager: Option<ManagerConfig>,
    pub executor: Option<ExecutorConfig>,
    pub prover: Option<Vec<ProverConfig>>,
    pub storage: Option<StorageConfig>,
    pub telemetry: Option<TelemetryConfig>,
}

#[derive(Clone, Debug, Serialize, Deserialize, Eq, PartialEq)]
pub(crate) struct ApiConfig {
    pub listen: Option<SocketAddr>,
    pub manager: Option<SocketAddr>,
    pub po2: Option<u32>,
}

#[derive(Clone, Debug, Serialize, Deserialize, Eq, PartialEq)]
pub(crate) struct ManagerConfig {
    pub listen: Option<SocketAddr>,
}

#[derive(Clone, Debug, Serialize, Deserialize, Eq, PartialEq)]
pub(crate) struct ExecutorConfig {
    pub manager: Option<SocketAddr>,
    pub count: usize,
}

#[derive(Clone, Debug, Serialize, Deserialize, Eq, PartialEq)]
pub(crate) struct ProverConfig {
    pub manager: Option<SocketAddr>,
    pub count: Option<usize>,
    pub subscribe: Vec<TaskKind>,
    pub simulate: Option<DevModeDelay>,
}

#[derive(Clone, Debug, Serialize, Deserialize, Eq, PartialEq)]
pub(crate) struct StorageConfig {
    pub path: PathBuf,
}

#[derive(Clone, Debug, Serialize, Deserialize, Eq, PartialEq)]
pub(crate) struct TelemetryConfig {
    // TODO
}

impl Default for AppConfig {
    fn default() -> Self {
        Self {
            version: VERSION,
            api: Some(ApiConfig {
                listen: Some(default_api_listen_addr()),
                manager: None,
                po2: None,
            }),
            manager: Some(ManagerConfig {
                listen: Some(default_manager_listen_addr()),
            }),
            executor: Some(ExecutorConfig {
                manager: None,
                count: 1,
            }),
            prover: Some(vec![ProverConfig {
                manager: None,
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
                version: 1,
                api: Some(ApiConfig {
                    listen: Some(SocketAddr::from_str("0.0.0.0:8000").unwrap()),
                    manager: Some(SocketAddr::from_str("1.2.3.4:9000").unwrap()),
                    po2: None,
                }),
                manager: None,
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
                api: Some(ApiConfig {
                    listen: Some(SocketAddr::from_str("0.0.0.0:8000").unwrap()),
                    manager: None,
                    po2: None,
                }),
                manager: Some(ManagerConfig {
                    listen: Some(SocketAddr::from_str("0.0.0.0:9000").unwrap())
                }),
                executor: Some(ExecutorConfig {
                    manager: None,
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
                api: None,
                manager: None,
                executor: None,
                prover: Some(vec![
                    ProverConfig {
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
                    ProverConfig {
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
