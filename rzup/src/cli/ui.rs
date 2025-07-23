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
use crate::{RzupEvent, TransferKind};
use indicatif::{MultiProgress, ProgressBar, ProgressDrawTarget, ProgressStyle};

#[derive(Clone)]
pub(super) struct TerminalUi {
    verbose: bool,
    multi_progress: MultiProgress,
    status: ProgressBar,
    transfer: Option<ProgressBar>,
}

impl TerminalUi {
    pub fn new(verbose: bool) -> Self {
        let multi_progress = MultiProgress::with_draw_target(ProgressDrawTarget::stdout());
        let status = ProgressBar::new_spinner().with_style(
            ProgressStyle::default_spinner()
                .template("{spinner} {msg}")
                .unwrap()
                .tick_chars("⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏"),
        );
        multi_progress.add(status.clone());
        status.enable_steady_tick(std::time::Duration::from_millis(80));
        Self {
            verbose,
            multi_progress,
            status,
            transfer: None,
        }
    }

    pub fn run(mut self, ui_recv: std::sync::mpsc::Receiver<RzupEvent>) {
        while let Ok(event) = ui_recv.recv() {
            match event {
                RzupEvent::TransferStarted {
                    kind,
                    id,
                    url,
                    version,
                    len,
                } => self.handle_transfer(kind, id, version, url, len),
                RzupEvent::TransferProgress { id, incr } => {
                    self.handle_transfer_progress(id, incr);
                }
                RzupEvent::TransferCompleted { kind, id, version } => {
                    self.handle_transfer_complete(kind, id, version)
                }
                RzupEvent::InstallationStarted { id, version } => self.handle_install(id, version),
                RzupEvent::InstallationCompleted { id, version } => {
                    self.handle_install_complete(id, version)
                }
                RzupEvent::ComponentAlreadyInstalled { id, version } => {
                    self.handle_already_installed(id, version)
                }
                RzupEvent::InstallationFailed { id: _, version: _ } => {
                    self.status.finish_and_clear();
                }
                RzupEvent::Uninstalled { id, version } => self.handle_uninstall(id, version),
                RzupEvent::CheckUpdates { id } => self.handle_checking_updates(id),
                RzupEvent::Debug { message } => self.handle_debug(message),
                RzupEvent::Print { message } => self.handle_print(message),
                RzupEvent::BuildingRustToolchain => self.handle_building_rust_toolchain(),
                RzupEvent::BuildingRustToolchainUpdate { message } => {
                    self.handle_building_rust_toolchain_update(message)
                }
                RzupEvent::DoneBuildingRustToolchain { version } => {
                    self.handle_done_building_rust_toolchain(version)
                }
            }
        }
    }

    fn start_progress(&mut self, message: String) {
        self.status.reset();
        self.status
            .enable_steady_tick(std::time::Duration::from_millis(80));
        self.status.set_message(message);
    }

    fn complete_progress(&mut self, message: &str) {
        self.status.finish_and_clear();
        self.multi_progress.println(message).unwrap();
        self.status.reset(); // Reset for next operation
    }

    fn handle_transfer(
        &mut self,
        kind: TransferKind,
        id: String,
        version: Option<String>,
        _url: Option<String>,
        len: Option<u64>,
    ) {
        let action = match kind {
            TransferKind::Upload => "Uploading",
            TransferKind::Download => "Downloading",
            TransferKind::Compress => "Compressing",
        };
        let mut message = format!("{action} {id}");
        if let Some(version) = version {
            message += &format!(" version {version}");
        }
        self.start_progress(message);
        if let Some(len) = len {
            let transfer_progress = ProgressBar::new(len);
            transfer_progress.set_style(
                ProgressStyle::with_template("  [{bar}] {bytes}/{total_bytes}")
                    .unwrap()
                    .progress_chars("=> "),
            );
            self.transfer = Some(transfer_progress.clone());
            self.multi_progress.add(transfer_progress);
        }
    }

    fn handle_transfer_progress(&mut self, _id: String, incr: u64) {
        if let Some(transfer_progress) = &self.transfer {
            transfer_progress.inc(incr);
        }
    }

    fn handle_transfer_complete(
        &mut self,
        kind: TransferKind,
        id: String,
        version: Option<String>,
    ) {
        let action = match kind {
            TransferKind::Upload => "Uploaded",
            TransferKind::Download => "Downloaded",
            TransferKind::Compress => "Compressed",
        };
        let mut message = format!("✓ {action} {id}");
        if let Some(version) = &version {
            message += &format!(" version {version}");
        }
        self.complete_progress(&message);

        if let Some(transfer_progress) = self.transfer.take() {
            transfer_progress.finish_and_clear();
            self.multi_progress.remove(&transfer_progress);
        }

        if kind == TransferKind::Download {
            let mut message = format!("Installing {id}");
            if let Some(version) = &version {
                message += &format!(" version {version}");
            }
            self.start_progress(message);
        }
    }

    fn handle_building_rust_toolchain(&mut self) {
        self.start_progress("Building Rust toolchain".into());
    }

    fn handle_building_rust_toolchain_update(&mut self, message: String) {
        self.status
            .set_message(format!("Building Rust toolchain: {message}"));
    }

    fn handle_done_building_rust_toolchain(&mut self, version: String) {
        self.complete_progress(&format!("✓ Built Rust toolchain version {version}"));
    }

    fn handle_install(&mut self, id: String, version: String) {
        self.start_progress(format!("Installing {id} version {version}"));
    }

    fn handle_install_complete(&mut self, id: String, version: String) {
        self.complete_progress(&format!(
            "\
            ✓ Installed {id} version {version}\n\
            ✓ Setting {id} version {version} as default\
            "
        ));
    }

    fn handle_already_installed(&mut self, id: String, version: String) {
        self.complete_progress(&format!(
            "\
            ! Version {version} of {id} is already installed\n\
            ✓ Setting {id} version {version} as default\
            ",
        ));
    }

    fn handle_uninstall(&mut self, id: String, version: String) {
        self.complete_progress(&format!("Uninstalled {id} version {version}"));
    }

    fn handle_checking_updates(&mut self, id: Option<String>) {
        match id {
            Some(_) => {
                self.start_progress("Checking for updates ...".to_string());
            }
            None => {
                self.status.finish_and_clear();
            }
        }
    }

    fn handle_debug(&mut self, message: String) {
        if self.verbose {
            self.multi_progress.println(message).unwrap();
        }
    }

    fn handle_print(&mut self, message: String) {
        self.multi_progress.println(message).unwrap();
    }
}

impl Drop for TerminalUi {
    fn drop(&mut self) {
        self.status.finish_and_clear();
    }
}

#[derive(Clone)]
pub(super) struct TextUi {
    verbose: bool,
}

impl TextUi {
    pub fn new(verbose: bool) -> Self {
        Self { verbose }
    }

    pub fn run(mut self, ui_recv: std::sync::mpsc::Receiver<RzupEvent>) {
        while let Ok(event) = ui_recv.recv() {
            match event {
                RzupEvent::TransferStarted {
                    kind,
                    id,
                    version,
                    url,
                    len,
                } => self.handle_transfer(kind, id, version, url, len),
                RzupEvent::TransferProgress { id, incr } => {
                    self.handle_transfer_progress(id, incr);
                }
                RzupEvent::TransferCompleted { kind, id, version } => {
                    self.handle_transfer_complete(kind, id, version)
                }
                RzupEvent::InstallationStarted { id, version } => self.handle_install(id, version),
                RzupEvent::InstallationCompleted { id, version } => {
                    self.handle_install_complete(id, version)
                }
                RzupEvent::ComponentAlreadyInstalled { id, version } => {
                    self.handle_already_installed(id, version)
                }
                RzupEvent::InstallationFailed { id: _, version: _ } => {}
                RzupEvent::Uninstalled { id, version } => self.handle_uninstall(id, version),
                RzupEvent::CheckUpdates { id } => self.handle_checking_updates(id),
                RzupEvent::Debug { message } => self.handle_debug(message),
                RzupEvent::Print { message } => self.handle_print(message),
                RzupEvent::BuildingRustToolchain => self.handle_building_rust_toolchain(),
                RzupEvent::BuildingRustToolchainUpdate { message } => {
                    self.handle_building_rust_toolchain_update(message)
                }
                RzupEvent::DoneBuildingRustToolchain { version } => {
                    self.handle_done_building_rust_toolchain(version)
                }
            }
        }
    }

    fn handle_transfer(
        &mut self,
        kind: TransferKind,
        id: String,
        version: Option<String>,
        _url: Option<String>,
        _len: Option<u64>,
    ) {
        let action = match kind {
            TransferKind::Upload => "Uploading",
            TransferKind::Download => "Downloading",
            TransferKind::Compress => "Compressing",
        };
        print!("{action} {id}");
        if let Some(version) = version {
            print!(" version {version}");
        }
        println!();
    }

    fn handle_transfer_progress(&mut self, _id: String, _incr: u64) {}

    fn handle_transfer_complete(
        &mut self,
        kind: TransferKind,
        id: String,
        version: Option<String>,
    ) {
        let action = match kind {
            TransferKind::Upload => "Uploaded",
            TransferKind::Download => "Downloaded",
            TransferKind::Compress => "Compressed",
        };

        print!("✓ {action} {id}");
        if let Some(version) = &version {
            print!(" version {version}");
        }
        println!();

        if kind == TransferKind::Download {
            print!("Installing {id}");
            if let Some(version) = &version {
                print!(" version {version}");
            }
            println!();
        }
    }

    fn handle_building_rust_toolchain(&mut self) {
        println!("Building Rust toolchain");
    }

    fn handle_building_rust_toolchain_update(&mut self, message: String) {
        println!("{message}");
    }

    fn handle_done_building_rust_toolchain(&mut self, version: String) {
        println!("✓ Built Rust toolchain version {version}");
    }

    fn handle_install(&mut self, id: String, version: String) {
        println!("Installing {id} version {version}");
    }

    fn handle_install_complete(&mut self, id: String, version: String) {
        println!(
            "\
            ✓ Installed {id} version {version}\n\
            ✓ Setting {id} version {version} as default\
            "
        );
    }

    fn handle_already_installed(&mut self, id: String, version: String) {
        println!(
            "\
            ! Version {version} of {id} is already installed\n\
            ✓ Setting {id} version {version} as default\
            ",
        );
    }

    fn handle_uninstall(&mut self, id: String, version: String) {
        println!("Uninstalled {id} version {version}");
    }

    fn handle_checking_updates(&mut self, id: Option<String>) {
        if id.is_some() {
            println!("Checking for updates ...");
        }
    }

    fn handle_debug(&mut self, message: String) {
        if self.verbose {
            println!("{message}");
        }
    }

    fn handle_print(&mut self, message: String) {
        println!("{message}");
    }
}
