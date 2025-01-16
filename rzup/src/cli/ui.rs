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
use crate::RzupEvent;
use indicatif::{MultiProgress, ProgressBar, ProgressStyle};

#[derive(Clone)]
pub(super) struct Ui {
    verbose: bool,
    multi_progress: MultiProgress,
    status: ProgressBar,
    download: Option<ProgressBar>,
}

impl Ui {
    pub fn new(verbose: bool) -> Self {
        let multi_progress = MultiProgress::new();
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
            download: None,
        }
    }

    pub fn run(mut self, ui_recv: std::sync::mpsc::Receiver<RzupEvent>) {
        while let Ok(event) = ui_recv.recv() {
            match event {
                RzupEvent::DownloadStarted {
                    id,
                    version,
                    url,
                    len,
                } => self.handle_download(id, version, url, len),
                RzupEvent::DownloadProgress { id, incr } => {
                    self.handle_download_progress(id, incr);
                }
                RzupEvent::DownloadCompleted { id, version } => {
                    self.handle_download_complete(id, version)
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

    fn handle_download(&mut self, id: String, version: String, _url: String, len: Option<u64>) {
        self.start_progress(format!("Downloading {id} version {version}"));
        if let Some(len) = len {
            let download_progress = ProgressBar::new(len);
            download_progress.set_style(
                ProgressStyle::with_template("{wide_bar} {binary_bytes}/{binary_total_bytes}")
                    .unwrap(),
            );
            self.download = Some(download_progress.clone());
            self.multi_progress.add(download_progress);
        }
    }

    fn handle_download_progress(&mut self, _id: String, incr: u64) {
        if let Some(download_progress) = &self.download {
            download_progress.inc(incr);
        }
    }

    fn handle_download_complete(&mut self, id: String, version: String) {
        self.complete_progress(&format!("✓ Downloaded {id} version {version}"));

        if let Some(download_progress) = self.download.take() {
            download_progress.finish_and_clear();
            self.multi_progress.remove(&download_progress);
        }

        self.start_progress(format!("Installing {id} version {version}"));
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
        self.complete_progress(&format!("✓ Installed {id} version {version}"));
    }

    fn handle_already_installed(&mut self, id: String, version: String) {
        self.complete_progress(&format!("! Version {version} of {id} is already installed",));
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

impl Drop for Ui {
    fn drop(&mut self) {
        self.status.finish_and_clear();
    }
}
