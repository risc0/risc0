use indicatif::{ProgressBar, ProgressStyle};

pub(crate) struct EventPrinter {
    verbose: bool,
    progress: ProgressBar,
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

    fn complete_progress(&self, message: &str) {
        self.progress.finish_and_clear();
        println!("{}", message);
        self.progress.reset(); // Reset for next operation
    }

    pub fn handle_download(&self, id: String, version: String, _url: String) {
        self.start_progress(format!("Downloading {} version {}", id, version));
    }

    pub fn handle_download_complete(&self, id: String, version: String) {
        self.complete_progress(&format!("✓ Downloaded {} version {}", id, version));
        self.start_progress(format!("Installing {} version {}", id, version));
    }

    pub fn handle_install(&self, id: String, version: String) {
        self.start_progress(format!("Installing {} version {}", id, version));
    }

    pub fn handle_install_complete(&self, id: String, version: String) {
        self.complete_progress(&format!("✓ Installed {} version {}", id, version));
    }

    pub fn handle_already_installed(&self, id: String, version: String) {
        self.complete_progress(&format!(
            "! Version {} of {} is already installed",
            version, id
        ));
    }

    pub fn handle_uninstall(&self, id: String, version: String) {
        self.complete_progress(&format!("Uninstalled {} version {}", id, version));
    }

    pub fn handle_debug(&self, message: String) {
        if self.verbose {
            self.progress.suspend(|| {
                println!("Debug: {}", message);
            });
        }
    }
}