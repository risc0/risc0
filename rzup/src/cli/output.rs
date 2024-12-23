use indicatif::{ProgressBar, ProgressStyle};
use std::sync::Arc;
use std::sync::Mutex;

pub(crate) struct Spinner(Arc<Mutex<Option<ProgressBar>>>);

impl Spinner {
    pub fn new() -> Self {
        Self(Arc::new(Mutex::new(None)))
    }

    pub fn start(&self, message: &str) {
        let pb = ProgressBar::new_spinner().with_style(
            ProgressStyle::with_template(&format!("{{spinner}} {}...", message))
                .unwrap()
                .tick_chars("⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏"),
        );
        pb.enable_steady_tick(std::time::Duration::from_millis(80));
        *self.0.lock().unwrap() = Some(pb);
    }

    pub fn stop(&self) {
        if let Some(pb) = self.0.lock().unwrap().take() {
            pb.finish_and_clear();
        }
    }
}

pub(crate) struct EventPrinter {
    verbose: bool,
    spinner: Spinner,
}

impl EventPrinter {
    pub fn new(verbose: bool, spinner: Spinner) -> Self {
        Self { verbose, spinner }
    }

    pub fn handle_download(&self, id: String, version: String, _url: String) {
        self.spinner
            .start(&format!("Downloading {} version {}", id, version));
    }

    pub fn handle_download_complete(&self, id: String, version: String) {
        self.spinner.stop();
        println!("✓ Download completed for {} version {}", id, version);
    }

    pub fn handle_install(&self, id: String, version: String) {
        self.spinner
            .start(&format!("Installing {} version {}", id, version));
    }

    pub fn handle_install_complete(&self, id: String, version: String) {
        self.spinner.stop();
        println!("✓ Successfully installed {} version {}", id, version);
    }

    pub fn handle_already_installed(&self, id: String, version: String) {
        println!("! Version {} of {} is already installed", version, id);
    }

    pub fn handle_settings_created(&self, path: std::path::PathBuf) {
        println!(
            "\n! Missing settings.toml\n  Created settings.toml at {}\n",
            path.display()
        );
    }

    pub fn handle_uninstall(&self, id: String, version: String) {
        println!(" Uninstalled {} version {}", id, version);
    }

    pub fn handle_debug(&self, message: String) {
        if self.verbose {
            println!("Debug: {}", message);
        }
    }
}
