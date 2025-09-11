// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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
