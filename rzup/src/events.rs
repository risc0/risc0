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

#[derive(Debug, PartialEq, Eq, Copy, Clone)]
pub enum TransferKind {
    Upload,
    Download,
    Compress,
}

#[derive(Debug, PartialEq, Eq)]
pub enum RzupEvent {
    TransferStarted {
        kind: TransferKind,
        id: String,
        version: Option<String>,
        url: Option<String>,
        len: Option<u64>,
    },
    TransferProgress {
        id: String,
        incr: u64,
    },
    TransferCompleted {
        kind: TransferKind,
        id: String,
        version: Option<String>,
    },
    InstallationStarted {
        id: String,
        version: String,
    },
    InstallationCompleted {
        id: String,
        version: String,
    },
    ComponentAlreadyInstalled {
        id: String,
        version: String,
    },
    InstallationFailed {
        id: String,
        version: String,
    },
    Uninstalled {
        id: String,
        version: String,
    },
    BuildingRustToolchain,
    BuildingRustToolchainUpdate {
        message: String,
    },
    DoneBuildingRustToolchain {
        version: String,
    },
    CheckUpdates {
        id: Option<String>, // none means finished checking
    },
    Debug {
        message: String,
    },
    Print {
        message: String,
    },
}
