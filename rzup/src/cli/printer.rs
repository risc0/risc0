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
use indicatif::{ProgressBar, ProgressStyle};

#[derive(Clone)]
pub(super) struct EventPrinter {
    verbose: bool,
    pub progress: ProgressBar,
}

impl EventPrinter {
    pub fn new(verbose: bool) -> Self {
        let progress = ProgressBar::new_spinner().with_style(
            ProgressStyle::default_spinner()
                .template("{spinner} {msg}")
                .unwrap()
                .tick_chars("⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏"),
        );
        progress.enable_steady_tick(std::time::Duration::from_millis(80));
        Self { verbose, progress }
    }

    fn start_progress(&self, message: String) {
        self.progress.reset();
        self.progress
            .enable_steady_tick(std::time::Duration::from_millis(80));
        self.progress.set_message(message);
    }

    pub fn complete_progress(&self, message: &str) {
        self.progress.finish_and_clear();
        println!("{message}");
        self.progress.reset(); // Reset for next operation
    }

    pub fn handle_download(&self, id: String, version: String, _url: String) {
        self.start_progress(format!("Downloading {id} version {version}"));
    }

    pub fn handle_download_complete(&self, id: String, version: String) {
        self.complete_progress(&format!("✓ Downloaded {id} version {version}"));
        self.start_progress(format!("Installing {id} version {version}"));
    }

    pub fn handle_install(&self, id: String, version: String) {
        self.start_progress(format!("Installing {id} version {version}"));
    }

    pub fn handle_install_complete(&self, id: String, version: String) {
        self.complete_progress(&format!("✓ Installed {id} version {version}"));
    }

    pub fn handle_already_installed(&self, id: String, version: String) {
        self.complete_progress(&format!("! Version {version} of {id} is already installed",));
    }

    pub fn handle_uninstall(&self, id: String, version: String) {
        self.complete_progress(&format!("Uninstalled {id} version {version}"));
    }

    pub fn handle_checking_updates(&self, id: Option<String>) {
        match id {
            Some(_) => {
                self.start_progress("Checking for updates ...".to_string());
            }
            None => {
                self.progress.finish_and_clear();
            }
        }
    }

    pub fn handle_debug(&self, message: String) {
        if self.verbose {
            self.progress.suspend(|| {
                println!("Debug: {message}");
            });
        }
    }
}

impl Drop for EventPrinter {
    fn drop(&mut self) {
        self.progress.finish_and_clear();
    }
}
