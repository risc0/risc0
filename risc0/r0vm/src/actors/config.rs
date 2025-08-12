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

use std::{net::SocketAddr, path::PathBuf};

use risc0_zkvm::DevModeDelay;
use serde::{Deserialize, Serialize};

use crate::actors::protocol::TaskKind;

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct AppConfig {
    manager: Option<ManagerConfig>,
    worker: Option<WorkerConfig>,
    storage: Option<StorageConfig>,
}

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct StorageConfig {
    path: PathBuf,
}

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct ManagerConfig {
    bind: Option<SocketAddr>,
}

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct WorkerConfig {
    pub pools: Vec<PoolConfig>,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) struct PoolConfig {
    pub count: usize,
    pub profile: Option<DevModeDelay>,
    pub task_kinds: Vec<TaskKind>,
}
