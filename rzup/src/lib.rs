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

use components::Component;
use env::Environment;
use events::RzupEvent;
use paths::Paths;
use registry::Registry;
use semver::Version;
use settings::Settings;
use std::path::PathBuf;

pub use error::{Result, RzupError};

#[derive(Clone, Debug)]
pub struct BaseUrls {
    pub risc0_github_base_url: String,
    pub github_api_base_url: String,
    pub risc0_base_url: String,
}

impl Default for BaseUrls {
    fn default() -> Self {
        Self {
            risc0_github_base_url: "https://github.com/risc0".into(),
            github_api_base_url: "https://api.github.com".into(),
            risc0_base_url: "https://risczero.com".into(),
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
        let registry = Registry::new(&environment, Default::default())?;

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
        let registry = Registry::new(&environment, base_urls)?;

        Ok(Self {
            environment,
            registry,
        })
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
        Ok(())
    }

    /// Installs a specific component version.
    ///
    /// # Arguments
    /// * `component` - Component
    /// * `version` - Specific version to install, or None for latest
    /// * `force` - If true, reinstalls even if already installed
    pub fn install_component(
        &mut self,
        component: &Component,
        version: Option<Version>,
        force: bool,
    ) -> Result<()> {
        self.registry
            .install_component(&self.environment, component, version, force)?;
        Ok(())
    }

    /// Uninstalls a specific component version.
    ///
    /// # Arguments
    /// * `component` - Component
    /// * `version` - Version to uninstall
    pub fn uninstall_component(&mut self, component: &Component, version: Version) -> Result<()> {
        self.registry
            .uninstall_component(&self.environment, component, version)?;
        Ok(())
    }

    /// Lists all installed versions of a component.
    ///
    /// # Arguments
    /// * `component` - Component
    ///
    /// # Returns
    /// A newest-to-oldest list of installed component versions
    pub fn list_versions(&self, component: &Component) -> Result<Vec<Version>> {
        Registry::list_component_versions(&self.environment, component)
    }

    /// Gets the currently active version of a component and its path.
    ///
    /// # Arguments
    /// * `component` - Component
    pub fn get_active_version(
        &self,
        component: &Component,
    ) -> Result<Option<(Version, std::path::PathBuf)>> {
        self.registry
            .get_active_component_version(&self.environment, component)
    }

    fn emit(&self, event: RzupEvent) {
        self.environment.emit(event)
    }

    /// Fetches the latest available version of a component.
    ///
    /// # Arguments
    /// * `component` - Component
    pub fn get_latest_version(&self, component: &Component) -> Result<Version> {
        components::get_latest_version(component, &self.environment, self.registry.base_urls())
    }

    /// Sets the active version for a component.
    ///
    /// # Arguments
    /// * `component` - Component
    /// * `version` - Version to set as active
    pub fn set_active_version(&mut self, component: &Component, version: Version) -> Result<()> {
        self.registry
            .set_active_component_version(&self.environment, component, version)
    }

    /// Checks if a specific version of a component exists.
    ///
    /// # Arguments
    /// * `component` - Component
    /// * `version` - Version to check
    pub fn version_exists(&self, component: &Component, version: &Version) -> Result<bool> {
        Paths::version_exists(&self.environment, component, version)
    }

    /// Gets the settings manager.
    pub fn settings(&self) -> &Settings {
        self.registry.settings()
    }

    /// Gets the binary path for a component version.
    ///
    /// For virtual components, returns the path within the parent component.
    ///
    /// # Arguments
    /// * `component` - Component
    /// * `version` - Version to get path for
    pub fn get_bin_path(&self, component: &Component, version: &Version) -> Option<PathBuf> {
        if let Some(parent_id) = component.parent_component() {
            // For virtual components, look at parent
            if let Ok(true) = Paths::version_exists(&self.environment, &parent_id, version) {
                Some(Paths::get_bin_path(
                    &self.environment,
                    &parent_id,
                    version,
                    component.as_str(),
                ))
            } else {
                None
            }
        } else if let Ok(true) = Paths::version_exists(&self.environment, component, version) {
            Some(Paths::get_bin_dir(&self.environment, component, version))
        } else {
            None
        }
    }

    /// Gets the component directory path.
    ///
    /// # Arguments
    /// * `component` - Component
    pub fn get_component_dir(&self, component: &Component) -> PathBuf {
        Paths::get_component_dir(&self.environment, component)
    }

    /// Gets the version-specific directory path for a component.
    ///
    /// # Arguments
    /// * `component` - Component
    /// * `version` - Version to get directory for
    pub fn get_version_dir(&self, component: &Component, version: &Version) -> PathBuf {
        Paths::get_version_dir(&self.environment, component, version)
    }

    /// Update rzup by downloading and re-running the installation script.
    pub fn self_update(&self) -> Result<()> {
        self.emit(RzupEvent::InstallationStarted {
            id: "rzup".to_string(),
            version: "latest".to_string(),
        });

        let script_contents = distribution::download_text(format!(
            "{base_url}/install",
            base_url = self.registry.base_urls().risc0_base_url
        ))?;

        let output = std::process::Command::new("/usr/bin/env")
            .args(["bash", "-c", &script_contents])
            .output()
            .map_err(|e| RzupError::Other(format!("Failed to execute update script: {e}")))?;

        if !output.status.success() {
            self.emit(RzupEvent::InstallationFailed {
                id: "rzup".to_string(),
                version: "latest".to_string(),
            });
            return Err(RzupError::Other(format!(
                "Self-update failed: {}",
                String::from_utf8_lossy(&output.stderr)
            )));
        }

        self.emit(RzupEvent::InstallationCompleted {
            id: "rzup".to_string(),
            version: "latest".to_string(),
        });

        Ok(())
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
        install_script: String,
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

        fn text_response(text: String) -> HyperResponse {
            hyper::Response::builder()
                .status(200)
                .header("content-type", "text/plain")
                .body(http_body_util::Full::new(hyper::body::Bytes::from(text)))
                .unwrap()
        }

        fn dummy_tar_gz_response() -> HyperResponse {
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

        fn dummy_tar_xz_response() -> HyperResponse {
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
                cargo-risczero-x86_64-unknown-linux-gnu.tgz" => dummy_tar_gz_response(),
            "/risc0_github/rust/releases/download/r0.1.79.0/\
                rust-toolchain-x86_64-unknown-linux-gnu.tar.gz" => dummy_tar_gz_response(),
            "/gihub_api/repos/risc0/toolchain/releases/tags/2024.01.05" => json_response("{}"),
            "/risc0_github/toolchain/releases/download/2024.01.05/riscv32im-linux-x86_64.tar.xz" =>
                dummy_tar_xz_response(),
            "/gihub_api/repos/risc0/rust/releases/tags/r0.1.81.0" => json_response("{}"),
            "/risc0_github/rust/releases/download/r0.1.81.0/\
                rust-toolchain-x86_64-unknown-linux-gnu.tar.gz" => dummy_tar_gz_response(),
            "/gihub_api/repos/risc0/risc0/releases/tags/v5.0.0" => not_found(),
            "/gihub_api/repos/risc0/risc0/releases/tags/v1.1.0" => json_response("{}"),
            "/risc0_github/risc0/releases/download/v1.1.0/\
                cargo-risczero-x86_64-unknown-linux-gnu.tgz" => dummy_tar_gz_response(),
            "/risc0/install" => text_response(install_script.clone()),
            unknown => panic!("unexpected URI: {unknown}"),
        })
    }

    #[tokio::main]
    async fn server_main(install_script: String, sender: tokio::sync::oneshot::Sender<SocketAddr>) {
        let listener = tokio::net::TcpListener::bind("localhost:0").await.unwrap();
        sender.send(listener.local_addr().unwrap()).unwrap();

        while let Ok((stream, _)) = listener.accept().await {
            let install_script = install_script.clone();
            hyper::server::conn::http1::Builder::new()
                .serve_connection(
                    hyper_util::rt::TokioIo::new(stream),
                    hyper::service::service_fn(move |req| {
                        request_handler(install_script.clone(), req)
                    }),
                )
                .await
                .unwrap()
        }
    }

    impl MockDistributionServer {
        pub fn new_with_install_script(install_script: String) -> Self {
            let (send, recv) = tokio::sync::oneshot::channel();
            std::thread::spawn(move || server_main(install_script, send));
            let address = recv.blocking_recv().unwrap();
            Self {
                base_urls: BaseUrls {
                    risc0_github_base_url: format!("http://{address}/risc0_github"),
                    github_api_base_url: format!("http://{address}/gihub_api"),
                    risc0_base_url: format!("http://{address}/risc0"),
                },
            }
        }

        pub fn new() -> Self {
            Self::new_with_install_script("".into())
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
            risc0_base_url: "".into(),
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
        assert!(rzup
            .settings()
            .get_active_version(&Component::RustToolchain)
            .is_none());
        assert!(rzup
            .settings()
            .get_active_version(&Component::CargoRiscZero)
            .is_none());
    }

    #[test]
    fn test_path_operations() {
        let (_tmp_dir, rzup) = setup_test_env(invalid_base_urls());
        let version = Version::new(1, 2, 0);
        let component = Component::CargoRiscZero;

        // Create the bin directory for the component
        let bin_dir = rzup.get_version_dir(&component, &version);
        std::fs::create_dir_all(&bin_dir).unwrap();

        // Test binary path retrieval with platform-specific path
        let bin_path = rzup.get_bin_path(&component, &version).unwrap();
        let bin_path = bin_path;
        assert!(bin_path.ends_with(format!(
            "v{version}-{component}-{}/bin",
            rzup.environment.platform()
        )));

        // Test virtual component (r0vm is inside cargo-risczero's bin directory)
        let virtual_component = Component::R0Vm;
        let virtual_bin_path = rzup.get_bin_path(&virtual_component, &version).unwrap();
        let virtual_bin_path = virtual_bin_path;
        assert!(virtual_bin_path.ends_with(format!("bin/{virtual_component}")));
    }

    fn test_install_and_uninstall_end_to_end(base_urls: BaseUrls) {
        let (_tmp_dir, mut rzup) = setup_test_env(base_urls);
        let cargo_risczero_version = Version::new(1, 0, 0);

        // Test installation
        rzup.install_component(
            &Component::CargoRiscZero,
            Some(cargo_risczero_version.clone()),
            false,
        )
        .unwrap();
        assert!(rzup
            .version_exists(&Component::CargoRiscZero, &cargo_risczero_version)
            .unwrap());
        assert_eq!(
            rzup.settings()
                .get_active_version(&Component::CargoRiscZero)
                .unwrap(),
            cargo_risczero_version
        );
        assert_eq!(
            rzup.list_versions(&Component::CargoRiscZero).unwrap(),
            vec![Version::new(1, 0, 0)]
        );

        // Test uninstallation
        rzup.uninstall_component(&Component::CargoRiscZero, cargo_risczero_version.clone())
            .unwrap();
        assert!(!rzup
            .version_exists(&Component::CargoRiscZero, &cargo_risczero_version)
            .unwrap());
        assert_eq!(
            rzup.list_versions(&Component::CargoRiscZero).unwrap(),
            vec![]
        );

        // Rust
        let rust_version = Version::new(1, 79, 0);
        rzup.install_component(&Component::RustToolchain, Some(rust_version.clone()), false)
            .unwrap();
        assert!(rzup
            .version_exists(&Component::RustToolchain, &rust_version)
            .unwrap());
        assert_eq!(
            rzup.list_versions(&Component::RustToolchain).unwrap(),
            vec![Version::new(1, 79, 0)]
        );

        // Test uninstallation
        rzup.uninstall_component(&Component::RustToolchain, rust_version.clone())
            .unwrap();
        assert!(!rzup
            .version_exists(&Component::RustToolchain, &rust_version)
            .unwrap());
        assert_eq!(
            rzup.list_versions(&Component::CargoRiscZero).unwrap(),
            vec![]
        );
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
                    &Component::CargoRiscZero,
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
                RzupEvent::DownloadStarted {
                    id: "cargo-risczero".into(),
                    version: "1.0.0".into(),
                    url: format!(
                        "{base_url}/risc0/releases/download/v1.0.0/\
                        cargo-risczero-x86_64-unknown-linux-gnu.tgz",
                        base_url = server.base_urls.risc0_github_base_url
                    ),
                    len: Some(86),
                },
                RzupEvent::DownloadProgress {
                    id: "cargo-risczero".into(),
                    incr: 86,
                },
                RzupEvent::DownloadCompleted {
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
    fn list_multiple_versions() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, mut rzup) = setup_test_env(server.base_urls.clone());
        let cargo_risczero_version1 = Version::new(1, 0, 0);
        let cargo_risczero_version2 = Version::new(1, 1, 0);

        rzup.install_component(
            &Component::CargoRiscZero,
            Some(cargo_risczero_version1.clone()),
            false,
        )
        .unwrap();

        rzup.install_component(
            &Component::CargoRiscZero,
            Some(cargo_risczero_version2.clone()),
            false,
        )
        .unwrap();

        assert_eq!(
            rzup.list_versions(&Component::CargoRiscZero).unwrap(),
            vec![cargo_risczero_version2, cargo_risczero_version1]
        );
    }

    #[test]
    fn set_active_version() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, mut rzup) = setup_test_env(server.base_urls.clone());
        let cargo_risczero_version1 = Version::new(1, 0, 0);
        let cargo_risczero_version2 = Version::new(1, 1, 0);

        rzup.install_component(
            &Component::CargoRiscZero,
            Some(cargo_risczero_version1.clone()),
            false,
        )
        .unwrap();

        rzup.install_component(
            &Component::CargoRiscZero,
            Some(cargo_risczero_version2.clone()),
            false,
        )
        .unwrap();

        assert_eq!(
            rzup.get_active_version(&Component::CargoRiscZero)
                .unwrap()
                .unwrap()
                .0,
            cargo_risczero_version2
        );

        rzup.set_active_version(&Component::CargoRiscZero, cargo_risczero_version1.clone())
            .unwrap();

        assert_eq!(
            rzup.get_active_version(&Component::CargoRiscZero)
                .unwrap()
                .unwrap()
                .0,
            cargo_risczero_version1
        );
    }

    #[test]
    fn active_version_after_uninstall() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, mut rzup) = setup_test_env(server.base_urls.clone());
        let cargo_risczero_version1 = Version::new(1, 0, 0);
        let cargo_risczero_version2 = Version::new(1, 1, 0);

        rzup.install_component(
            &Component::CargoRiscZero,
            Some(cargo_risczero_version2.clone()),
            false,
        )
        .unwrap();

        rzup.install_component(
            &Component::CargoRiscZero,
            Some(cargo_risczero_version1.clone()),
            false,
        )
        .unwrap();

        rzup.uninstall_component(&Component::CargoRiscZero, cargo_risczero_version1.clone())
            .unwrap();

        assert_eq!(
            rzup.get_active_version(&Component::CargoRiscZero)
                .unwrap()
                .unwrap()
                .0,
            cargo_risczero_version2
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
                        &Component::CargoRiscZero,
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

        assert_eq!(
            rzup.list_versions(&Component::CargoRiscZero).unwrap(),
            vec![]
        );
    }

    #[test]
    fn already_installed() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, mut rzup) = setup_test_env(server.base_urls.clone());
        let cargo_risczero_version = Version::new(1, 0, 0);

        rzup.install_component(
            &Component::CargoRiscZero,
            Some(cargo_risczero_version.clone()),
            false,
        )
        .unwrap();

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                rzup.install_component(
                    &Component::CargoRiscZero,
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
    fn already_installed_forced() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, mut rzup) = setup_test_env(server.base_urls.clone());
        let cargo_risczero_version = Version::new(1, 0, 0);

        rzup.install_component(
            &Component::CargoRiscZero,
            Some(cargo_risczero_version.clone()),
            false,
        )
        .unwrap();

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                rzup.install_component(
                    &Component::CargoRiscZero,
                    Some(cargo_risczero_version.clone()),
                    true,
                )
                .unwrap();
            },
            vec![
                RzupEvent::InstallationStarted {
                    id: "cargo-risczero".into(),
                    version: "1.0.0".into(),
                },
                RzupEvent::DownloadStarted {
                    id: "cargo-risczero".into(),
                    version: "1.0.0".into(),
                    url: format!(
                        "{base_url}/risc0/releases/download/v1.0.0/\
                        cargo-risczero-x86_64-unknown-linux-gnu.tgz",
                        base_url = server.base_urls.risc0_github_base_url
                    ),
                    len: Some(86),
                },
                RzupEvent::DownloadProgress {
                    id: "cargo-risczero".into(),
                    incr: 86,
                },
                RzupEvent::DownloadCompleted {
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
    fn uninstall_events() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, mut rzup) = setup_test_env(server.base_urls.clone());
        let cargo_risczero_version = Version::new(1, 0, 0);

        rzup.install_component(
            &Component::CargoRiscZero,
            Some(cargo_risczero_version.clone()),
            false,
        )
        .unwrap();

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                rzup.uninstall_component(&Component::CargoRiscZero, cargo_risczero_version.clone())
                    .unwrap();
            },
            vec![RzupEvent::Uninstalled {
                id: "cargo-risczero".into(),
                version: "1.0.0".into(),
            }],
        );
    }

    #[test]
    fn get_latest_version() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, rzup) = setup_test_env(server.base_urls.clone());

        assert_eq!(
            rzup.get_latest_version(&Component::CargoRiscZero).unwrap(),
            Version::new(1, 1, 0)
        );
    }

    #[test]
    fn self_update() {
        let temp_dir = TempDir::new().unwrap();
        let server = MockDistributionServer::new_with_install_script(format!(
            "#!/bin/bash
            set -eo pipefail
            touch {}/self_update_ran
            ",
            temp_dir.path().display()
        ));
        let (_, mut rzup) = setup_test_env(server.base_urls.clone());

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                rzup.self_update().unwrap();
            },
            vec![
                RzupEvent::InstallationStarted {
                    id: "rzup".into(),
                    version: "latest".into(),
                },
                RzupEvent::InstallationCompleted {
                    id: "rzup".into(),
                    version: "latest".into(),
                },
            ],
        );
        assert!(temp_dir.path().join("self_update_ran").exists());
    }

    #[test]
    fn self_update_failure() {
        let temp_dir = TempDir::new().unwrap();
        let server = MockDistributionServer::new_with_install_script(
            "#!/bin/bash
            set -eo pipefail
            echo test_failure 1>&2
            exit 1
            "
            .into(),
        );
        let (_, mut rzup) = setup_test_env(server.base_urls.clone());

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                let error = rzup.self_update().unwrap_err();
                assert_eq!(
                    error,
                    RzupError::Other("Self-update failed: test_failure\n".into())
                );
            },
            vec![
                RzupEvent::InstallationStarted {
                    id: "rzup".into(),
                    version: "latest".into(),
                },
                RzupEvent::InstallationFailed {
                    id: "rzup".into(),
                    version: "latest".into(),
                },
            ],
        );
        assert!(!temp_dir.path().join("self_update_ran").exists());
    }
}
