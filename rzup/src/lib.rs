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
#[cfg(feature = "cli")]
pub mod cli;
mod components;
mod distribution;
mod env;

mod events;
mod paths;
mod registry;
mod settings;

pub mod error;

use env::Environment;
use events::RzupEvent;
use paths::Paths;
use registry::Registry;
use semver::Version;
use settings::Settings;
use std::collections::HashMap;
use std::path::PathBuf;

pub use error::{Result, RzupError};

#[derive(Clone, Debug)]
pub struct BaseUrls {
    pub risc0_github_base_url: String,
    pub github_api_base_url: String,
}

impl Default for BaseUrls {
    fn default() -> Self {
        Self {
            risc0_github_base_url: "https://github.com/risc0".into(),
            github_api_base_url: "https://api.github.com".into(),
        }
    }
}

/// Rzup manages the RISC Zero toolchain components by handling installation, uninstallation,
/// and version management of various tools like the Rust toolchain and cargo extensions.
pub struct Rzup {
    environment: Environment,
    registry: Registry,
}

impl Rzup {
    /// Creates a new Rzup instance using default environment paths.
    ///
    /// This will initialize the registry, settings, and scan the environment for installed components.
    pub fn new() -> Result<Self> {
        let environment = Environment::new(|s| std::env::var(s))?;
        let mut registry = Registry::new(&environment, Default::default())?;
        Self::initialize_settings(&environment, &mut registry)?;
        registry.scan_environment(&environment)?;

        Ok(Self {
            environment,
            registry,
        })
    }

    /// Creates a new Rzup instance with a custom root directory.
    ///
    /// # Arguments
    /// * `root` - The root directory path for storing components and settings
    /// * `base_urls` - The base URLs used to communicate with GitHub
    pub fn with_root(root: impl Into<PathBuf>, base_urls: BaseUrls) -> Result<Self> {
        let environment = Environment::with_root(root)?;
        let mut registry = Registry::new(&environment, base_urls)?;
        Self::initialize_settings(&environment, &mut registry)?;
        registry.scan_environment(&environment)?;

        Ok(Self {
            environment,
            registry,
        })
    }

    fn initialize_settings(environment: &Environment, registry: &mut Registry) -> Result<()> {
        if !environment.settings_path().exists() {
            environment.emit(RzupEvent::Debug {
                message: format!(
                    "Creating new settings file at {}",
                    environment.settings_path().display()
                ),
            });
        }
        registry.settings().save(environment)?;
        Ok(())
    }

    /// Sets an event handler for receiving notifications about operations.
    ///
    /// # Arguments
    /// * `handler` - Function that will be called for each event
    pub fn set_event_handler<F>(&mut self, handler: F)
    where
        F: Fn(RzupEvent) + Send + Sync + 'static,
    {
        self.environment.set_event_handler(handler);
    }

    /// Installs all default components.
    ///
    /// # Arguments
    /// * `force` - If true, reinstalls even if already installed
    pub fn install_all(&mut self, force: bool) -> Result<()> {
        self.registry
            .install_all_components(&self.environment, force)?;
        self.registry.scan_environment(&self.environment)?;
        Ok(())
    }

    /// Installs a specific component version.
    ///
    /// # Arguments
    /// * `component` - Component identifier (e.g. "rust", "cargo-risczero")
    /// * `version` - Specific version to install, or None for latest
    /// * `force` - If true, reinstalls even if already installed
    pub fn install_component(
        &mut self,
        component: &str,
        version: Option<Version>,
        force: bool,
    ) -> Result<()> {
        self.registry
            .install_component(&self.environment, component, version, force)?;
        self.registry.scan_environment(&self.environment)?;
        Ok(())
    }

    /// Uninstalls a specific component version.
    ///
    /// # Arguments
    /// * `component` - Component identifier
    /// * `version` - Version to uninstall
    pub fn uninstall_component(&mut self, component: &str, version: Version) -> Result<()> {
        self.registry
            .uninstall_component(&self.environment, component, version)?;
        self.registry.scan_environment(&self.environment)?;
        Ok(())
    }

    /// Lists all installed versions of a component.
    ///
    /// # Arguments
    /// * `id` - Component identifier
    ///
    /// # Returns
    /// A newest-to-oldest list of installed component versions
    pub fn list_versions(&self, id: &str) -> Result<Vec<Version>> {
        self.registry.list_component_versions(&self.environment, id)
    }

    /// Gets the currently active version of a component and its path.
    ///
    /// # Arguments
    /// * `id` - Component identifier
    pub fn get_active_version(&self, id: &str) -> Result<Option<(Version, std::path::PathBuf)>> {
        self.registry
            .get_active_component_version(&self.environment, id)
    }

    fn emit(&self, event: RzupEvent) {
        self.environment.emit(event)
    }

    /// Fetches the latest available version of a component.
    ///
    /// # Arguments
    /// * `id` - Component identifier
    pub fn get_latest_version(&self, id: &str) -> Result<Version> {
        let component = self.registry.create_component(id)?;
        component.get_latest_version(&self.environment, self.registry.base_urls())
    }

    /// Sets the active version for a component.
    ///
    /// # Arguments
    /// * `id` - Component identifier
    /// * `version` - Version to set as active
    pub fn set_active_version(&mut self, id: &str, version: Version) -> Result<()> {
        self.registry
            .set_active_component_version(&self.environment, id, version)
    }

    /// Checks if a specific version of a component exists.
    ///
    /// # Arguments
    /// * `id` - Component identifier
    /// * `version` - Version to check
    pub fn version_exists(&self, id: &str, version: &Version) -> Result<bool> {
        Paths::version_exists(&self.environment, id, version)
    }

    /// Gets the settings manager.
    pub fn settings(&self) -> &Settings {
        self.registry.settings()
    }

    pub fn latest_version(&self, component_id: &str) -> Result<Version> {
        let components = &self.registry.components;
        let component = components.get(component_id).unwrap();
        component.get_latest_version(&self.environment, self.registry.base_urls())
    }

    /// Gets the mapping of all installed versions and their paths for a component.
    ///
    /// # Arguments
    /// * `component_id` - Component identifier
    pub fn installed_versions(&self, component_id: &str) -> HashMap<Version, PathBuf> {
        let mut versions = HashMap::new();
        let component_dir = Paths::get_component_dir(&self.environment, component_id);

        if let Ok(entries) = std::fs::read_dir(component_dir) {
            for entry in entries.filter_map(|e| e.ok()) {
                let file_name = entry.file_name().to_string_lossy().to_string();
                if let Some(version_str) = file_name
                    .strip_prefix('v')
                    .and_then(|s| s.strip_suffix(&format!("-{component_id}")))
                {
                    if let Ok(version) = Version::parse(version_str) {
                        versions.insert(version, entry.path());
                    }
                }
            }
        }
        versions
    }

    /// Checks if a specific version of a component is installed.
    ///
    /// # Arguments
    /// * `component_id` - Component identifier
    /// * `version` - Version to check
    pub fn is_installed(&self, component_id: &str, version: &Version) -> bool {
        Paths::version_exists(&self.environment, component_id, version).unwrap_or(false)
    }

    /// Gets the binary path for a component version.
    ///
    /// For virtual components, returns the path within the parent component.
    ///
    /// # Arguments
    /// * `component_id` - Component identifier
    /// * `version` - Version to get path for
    pub fn get_bin_path(&self, component_id: &str, version: &Version) -> Option<PathBuf> {
        match self.registry.create_component(component_id) {
            Ok(component) => {
                if let Some(parent_id) = component.parent_component() {
                    // For virtual components, look at parent
                    if let Ok(true) = Paths::version_exists(&self.environment, parent_id, version) {
                        Some(Paths::get_bin_path(
                            &self.environment,
                            parent_id,
                            version,
                            component_id,
                        ))
                    } else {
                        None
                    }
                } else if let Ok(true) =
                    Paths::version_exists(&self.environment, component_id, version)
                {
                    Some(Paths::get_bin_dir(&self.environment, component_id, version))
                } else {
                    None
                }
            }
            Err(_) => None,
        }
    }

    /// Ensures version directories exist for a component.
    ///
    /// Creates the necessary directory structure if it doesn't exist.
    ///
    /// # Arguments
    /// * `component_id` - Component identifier
    /// * `version` - Version to create directories for
    pub fn ensure_version_dirs(&self, component_id: &str, version: &Version) -> Result<()> {
        Paths::create_version_dirs(&self.environment, component_id, version)
    }

    /// Gets the component directory path.
    ///
    /// # Arguments
    /// * `component_id` - Component identifier
    pub fn get_component_dir(&self, component_id: &str) -> PathBuf {
        Paths::get_component_dir(&self.environment, component_id)
    }

    /// Gets the version-specific directory path for a component.
    ///
    /// # Arguments
    /// * `component_id` - Component identifier
    /// * `version` - Version to get directory for
    pub fn get_version_dir(&self, component_id: &str, version: &Version) -> PathBuf {
        Paths::get_version_dir(&self.environment, component_id, version)
    }
}
#[cfg(test)]
mod tests {
    use super::*;
    use std::convert::Infallible;
    use std::io::Write as _;
    use std::net::SocketAddr;
    use tempfile::TempDir;

    pub struct MockDistributionServer {
        pub base_urls: BaseUrls,
    }

    type HyperResponse = hyper::Response<http_body_util::Full<hyper::body::Bytes>>;

    async fn request_handler(
        req: hyper::Request<hyper::body::Incoming>,
    ) -> std::result::Result<HyperResponse, Infallible> {
        fn json_response(json: &'static str) -> HyperResponse {
            hyper::Response::builder()
                .status(200)
                .header("content-type", "application/json")
                .body(http_body_util::Full::new(hyper::body::Bytes::from(json)))
                .unwrap()
        }

        fn not_found() -> HyperResponse {
            hyper::Response::builder()
                .status(404)
                .body(http_body_util::Full::new(hyper::body::Bytes::from("")))
                .unwrap()
        }

        fn empty_tar_gz_response() -> HyperResponse {
            let mut tar_bytes = vec![];
            let mut tar_builder = tar::Builder::new(&mut tar_bytes);
            let mut header = tar::Header::new_gnu();
            header.set_size(4);
            tar_builder
                .append_data(&mut header, "tar_contents.bin", &[1, 2, 3, 4][..])
                .unwrap();
            tar_builder.finish().unwrap();
            drop(tar_builder);

            let mut tar_gz_bytes = vec![];
            let mut encoder =
                flate2::write::GzEncoder::new(&mut tar_gz_bytes, flate2::Compression::default());
            encoder.write_all(&tar_bytes).unwrap();
            drop(encoder);

            hyper::Response::builder()
                .status(200)
                .header("content-type", "application/octet-stream")
                .body(http_body_util::Full::new(hyper::body::Bytes::from(
                    tar_gz_bytes,
                )))
                .unwrap()
        }

        fn empty_tar_xz_response() -> HyperResponse {
            let mut tar_bytes = vec![];
            let mut tar_builder = tar::Builder::new(&mut tar_bytes);
            let mut header = tar::Header::new_gnu();
            header.set_size(4);
            tar_builder
                .append_data(&mut header, "tar_contents.bin", &[1, 2, 3, 4][..])
                .unwrap();
            tar_builder.finish().unwrap();
            drop(tar_builder);

            let mut tar_xz_bytes = vec![];
            let mut encoder = xz::write::XzEncoder::new(&mut tar_xz_bytes, 1);
            encoder.write_all(&tar_bytes).unwrap();
            drop(encoder);

            hyper::Response::builder()
                .status(200)
                .header("content-type", "application/octet-stream")
                .body(http_body_util::Full::new(hyper::body::Bytes::from(
                    tar_xz_bytes,
                )))
                .unwrap()
        }

        Ok(match &req.uri().to_string()[..] {
            "/gihub_api/repos/risc0/risc0/releases/latest" => {
                json_response("{\"tag_name\":\"v1.1.0\"}")
            }
            "/gihub_api/repos/risc0/risc0/releases/tags/v1.0.0" => json_response("{}"),
            "/gihub_api/repos/risc0/rust/releases/tags/r0.1.79.0" => json_response("{}"),
            "/risc0_github/risc0/releases/download/v1.0.0/\
                cargo-risczero-x86_64-unknown-linux-gnu.tgz" => empty_tar_gz_response(),
            "/risc0_github/rust/releases/download/r0.1.79.0/\
                rust-toolchain-x86_64-unknown-linux-gnu.tar.gz" => empty_tar_gz_response(),
            "/gihub_api/repos/risc0/toolchain/releases/tags/2024.01.05" => json_response("{}"),
            "/risc0_github/toolchain/releases/download/2024.01.05/riscv32im-linux-x86_64.tar.xz" =>
                empty_tar_xz_response(),
            "/gihub_api/repos/risc0/rust/releases/tags/r0.1.81.0" => json_response("{}"),
            "/risc0_github/rust/releases/download/r0.1.81.0/\
                rust-toolchain-x86_64-unknown-linux-gnu.tar.gz" => empty_tar_gz_response(),
            "/gihub_api/repos/risc0/risc0/releases/tags/v5.0.0" => not_found(),
            "/gihub_api/repos/risc0/risc0/releases/tags/v1.1.0" => json_response("{}"),
            "/risc0_github/risc0/releases/download/v1.1.0/\
                cargo-risczero-x86_64-unknown-linux-gnu.tgz" => empty_tar_gz_response(),
            unknown => panic!("unexpected URI: {unknown}"),
        })
    }

    #[tokio::main]
    async fn server_main(sender: tokio::sync::oneshot::Sender<SocketAddr>) {
        let listener = tokio::net::TcpListener::bind("localhost:0").await.unwrap();
        sender.send(listener.local_addr().unwrap()).unwrap();

        while let Ok((stream, _)) = listener.accept().await {
            hyper::server::conn::http1::Builder::new()
                .serve_connection(
                    hyper_util::rt::TokioIo::new(stream),
                    hyper::service::service_fn(request_handler),
                )
                .await
                .unwrap()
        }
    }

    impl MockDistributionServer {
        pub fn new() -> Self {
            let (send, recv) = tokio::sync::oneshot::channel();
            std::thread::spawn(move || server_main(send));
            let address = recv.blocking_recv().unwrap();
            Self {
                base_urls: BaseUrls {
                    risc0_github_base_url: format!("http://{address}/risc0_github"),
                    github_api_base_url: format!("http://{address}/gihub_api"),
                },
            }
        }
    }

    #[macro_export]
    macro_rules! http_test_harness {
        ($test_name:ident) => {
            paste::paste! {
                #[test]
                #[ignore = "requires GitHub API access"]
                fn [<$test_name _against_real_github>]() {
                    $test_name(Default::default())
                }

                #[test]
                fn [<$test_name _against_mock_server>]() {
                    let server = crate::tests::MockDistributionServer::new();
                    $test_name(server.base_urls.clone())
                }
            }
        };
    }

    pub fn invalid_base_urls() -> BaseUrls {
        BaseUrls {
            risc0_github_base_url: "".into(),
            github_api_base_url: "".into(),
        }
    }

    fn setup_test_env(base_urls: BaseUrls) -> (TempDir, Rzup) {
        let tmp_dir = TempDir::new().unwrap();
        let rzup = Rzup::with_root(tmp_dir.path(), base_urls).unwrap();
        (tmp_dir, rzup)
    }

    #[test]
    fn test_rzup_initialization() {
        let (_tmp_dir, rzup) = setup_test_env(invalid_base_urls());
        assert!(rzup.settings().get_active_version("rust").is_none());
        assert!(rzup
            .settings()
            .get_active_version("cargo-risczero")
            .is_none());
    }

    #[test]
    fn test_path_operations() {
        let (_tmp_dir, rzup) = setup_test_env(invalid_base_urls());
        let version = Version::new(1, 2, 0);
        let component_id = "cargo-risczero";

        // Create necessary directories without actual installation
        rzup.ensure_version_dirs(component_id, &version).unwrap();

        // Create the bin directory for the component
        let bin_dir = rzup.get_version_dir(component_id, &version);
        std::fs::create_dir_all(&bin_dir).unwrap();

        // Test binary path retrieval with platform-specific path
        let bin_path = rzup.get_bin_path(component_id, &version).unwrap();
        let bin_path = bin_path;
        assert!(bin_path.ends_with(format!(
            "v{version}-{component_id}-{}/bin",
            rzup.environment.platform()
        )));

        // Test virtual component (r0vm is inside cargo-risczero's bin directory)
        let virtual_component = "r0vm";
        let virtual_bin_path = rzup.get_bin_path(virtual_component, &version).unwrap();
        let virtual_bin_path = virtual_bin_path;
        assert!(virtual_bin_path.ends_with(format!("bin/{virtual_component}")));
    }

    fn test_install_and_uninstall_end_to_end(base_urls: BaseUrls) {
        let (_tmp_dir, mut rzup) = setup_test_env(base_urls);
        let cargo_risczero_version = Version::new(1, 0, 0);

        // Test installation
        rzup.install_component(
            "cargo-risczero",
            Some(cargo_risczero_version.clone()),
            false,
        )
        .unwrap();
        assert!(rzup.is_installed("cargo-risczero", &cargo_risczero_version));
        assert_eq!(
            rzup.settings()
                .get_active_version("cargo-risczero")
                .unwrap(),
            cargo_risczero_version
        );

        // Test uninstallation
        rzup.uninstall_component("cargo-risczero", cargo_risczero_version.clone())
            .unwrap();
        assert!(!rzup.is_installed("cargo-risczero", &cargo_risczero_version));

        // Rust
        let rust_version = Version::new(1, 79, 0);
        rzup.install_component("rust", Some(rust_version.clone()), false)
            .unwrap();
        assert!(rzup.is_installed("rust", &rust_version));

        // Test uninstallation
        rzup.uninstall_component("rust", rust_version.clone())
            .unwrap();
        assert!(!rzup.is_installed("rust", &rust_version));
    }

    http_test_harness!(test_install_and_uninstall_end_to_end);

    fn run_and_assert_events(
        rzup: &mut Rzup,
        body: impl FnOnce(&mut Rzup),
        expected_events: Vec<RzupEvent>,
    ) {
        let (event_send, event_recv) = std::sync::mpsc::channel();
        rzup.set_event_handler(move |event| {
            event_send.send(event).unwrap();
        });

        body(rzup);
        rzup.set_event_handler(|_| {});

        let mut events = vec![];
        while let Ok(event) = event_recv.recv() {
            if !matches!(event, RzupEvent::Debug { .. }) {
                events.push(event);
            }
        }
        assert_eq!(events, expected_events);
    }

    #[test]
    fn install() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, mut rzup) = setup_test_env(server.base_urls.clone());
        let cargo_risczero_version = Version::new(1, 0, 0);

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                rzup.install_component(
                    "cargo-risczero",
                    Some(cargo_risczero_version.clone()),
                    false,
                )
                .unwrap();
            },
            vec![
                RzupEvent::InstallationStarted {
                    id: "cargo-risczero".into(),
                    version: "1.0.0".into(),
                },
                RzupEvent::InstallationCompleted {
                    id: "cargo-risczero".into(),
                    version: "1.0.0".into(),
                },
            ],
        );
    }

    #[test]
    fn set_active_version() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, mut rzup) = setup_test_env(server.base_urls.clone());
        let cargo_risczero_version1 = Version::new(1, 0, 0);
        let cargo_risczero_version2 = Version::new(1, 1, 0);

        rzup.install_component(
            "cargo-risczero",
            Some(cargo_risczero_version1.clone()),
            false,
        )
        .unwrap();

        rzup.install_component(
            "cargo-risczero",
            Some(cargo_risczero_version2.clone()),
            false,
        )
        .unwrap();

        assert_eq!(
            rzup.get_active_version("cargo-risczero")
                .unwrap()
                .unwrap()
                .0,
            cargo_risczero_version2
        );

        rzup.set_active_version("cargo-risczero", cargo_risczero_version1.clone())
            .unwrap();

        assert_eq!(
            rzup.get_active_version("cargo-risczero")
                .unwrap()
                .unwrap()
                .0,
            cargo_risczero_version1
        );
    }

    #[test]
    fn install_non_existent() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, mut rzup) = setup_test_env(server.base_urls.clone());
        let cargo_risczero_version = Version::new(5, 0, 0);

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                let error = rzup
                    .install_component(
                        "cargo-risczero",
                        Some(cargo_risczero_version.clone()),
                        false,
                    )
                    .unwrap_err();
                assert_eq!(
                    error,
                    RzupError::InvalidVersion("5.0.0 is not available for cargo-risczero".into())
                );
            },
            vec![
                RzupEvent::InstallationStarted {
                    id: "cargo-risczero".into(),
                    version: "5.0.0".into(),
                },
                RzupEvent::InstallationFailed {
                    id: "cargo-risczero".into(),
                    version: "5.0.0".into(),
                },
            ],
        );
    }

    #[test]
    fn already_installed() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, mut rzup) = setup_test_env(server.base_urls.clone());
        let cargo_risczero_version = Version::new(1, 0, 0);

        rzup.install_component(
            "cargo-risczero",
            Some(cargo_risczero_version.clone()),
            false,
        )
        .unwrap();

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                rzup.install_component(
                    "cargo-risczero",
                    Some(cargo_risczero_version.clone()),
                    false,
                )
                .unwrap();
            },
            vec![RzupEvent::ComponentAlreadyInstalled {
                id: "cargo-risczero".into(),
                version: "1.0.0".into(),
            }],
        );
    }

    #[test]
    fn uninstall_events() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, mut rzup) = setup_test_env(server.base_urls.clone());
        let cargo_risczero_version = Version::new(1, 0, 0);

        rzup.install_component(
            "cargo-risczero",
            Some(cargo_risczero_version.clone()),
            false,
        )
        .unwrap();

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                rzup.uninstall_component("cargo-risczero", cargo_risczero_version.clone())
                    .unwrap();
            },
            vec![RzupEvent::Uninstalled {
                id: "cargo-risczero".into(),
                version: "1.0.0".into(),
            }],
        );
    }
}
