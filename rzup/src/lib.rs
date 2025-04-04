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
mod build;
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

use distribution::Platform;
use env::Environment;
use events::RzupEvent;
use paths::Paths;
use registry::Registry;
use semver::Version;
use settings::Settings;
use std::path::{Path, PathBuf};

pub use components::Component;
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
    pub fn new() -> Result<Self> {
        let environment = Environment::new(|s| std::env::var(s), |_| {})?;
        let registry = Registry::new(&environment, Default::default())?;

        Ok(Self {
            environment,
            registry,
        })
    }

    /// Creates a new Rzup instance using default environment paths, and the given event handler.
    pub fn new_with_event_handler(
        event_handler: impl Fn(RzupEvent) + Send + Sync + 'static,
    ) -> Result<Self> {
        let environment = Environment::new(|s| std::env::var(s), event_handler)?;
        let registry = Registry::new(&environment, Default::default())?;

        Ok(Self {
            environment,
            registry,
        })
    }

    /// Creates a new Rzup instance with a custom root directory, base URLs, and GitHub token.
    ///
    /// # Arguments
    /// * `risc0_dir` - The root directory path for storing components and settings
    /// * `rustup_dir` - The path to rustup's home directory (usually ~/.rustup)
    /// * `cargo_dir` - The path to cargo's home directory (usually ~/.cargo)
    /// * `base_urls` - The base URLs used to communicate with GitHub
    /// * `github_token` - The token to use when communicating with GitHub
    pub fn with_paths_urls_token_platform_and_event_handler(
        risc0_dir: impl Into<PathBuf>,
        rustup_dir: impl AsRef<Path>,
        cargo_dir: impl AsRef<Path>,
        base_urls: BaseUrls,
        github_token: Option<String>,
        platform: Platform,
        event_handler: impl Fn(RzupEvent) + Send + Sync + 'static,
    ) -> Result<Self> {
        let environment = Environment::with_paths_token_platform_and_event_handler(
            risc0_dir,
            rustup_dir,
            cargo_dir,
            github_token,
            platform,
            event_handler,
        )?;
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
    #[cfg(test)]
    pub(crate) fn set_event_handler(
        &mut self,
        event_handler: impl Fn(RzupEvent) + Send + Sync + 'static,
    ) {
        self.environment.set_event_handler(event_handler);
    }

    /// Installs all default components.
    ///
    /// # Arguments
    /// * `force` - If true, reinstalls even if already installed
    #[cfg_attr(not(feature = "cli"), expect(dead_code))]
    pub(crate) fn install_all(&mut self, force: bool) -> Result<()> {
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
    #[cfg_attr(not(feature = "cli"), expect(dead_code))]
    pub(crate) fn install_component(
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
    #[cfg_attr(not(feature = "cli"), expect(dead_code))]
    pub(crate) fn uninstall_component(
        &mut self,
        component: &Component,
        version: Version,
    ) -> Result<()> {
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
    #[cfg_attr(not(feature = "cli"), expect(dead_code))]
    pub(crate) fn list_versions(&self, component: &Component) -> Result<Vec<Version>> {
        Ok(
            Registry::list_component_versions(&self.environment, component)?
                .into_iter()
                .map(|(v, _)| v)
                .collect(),
        )
    }

    /// Gets the currently default version of a component and its path.
    ///
    /// # Arguments
    /// * `component` - Component
    pub fn get_default_version(
        &self,
        component: &Component,
    ) -> Result<Option<(Version, std::path::PathBuf)>> {
        self.registry
            .get_default_component_version(&self.environment, component)
    }

    fn emit(&self, event: RzupEvent) {
        self.environment.emit(event)
    }

    #[cfg_attr(not(feature = "cli"), expect(dead_code))]
    pub(crate) fn print(&self, message: String) {
        self.emit(RzupEvent::Print { message });
    }

    /// Fetches the latest available version of a component.
    ///
    /// # Arguments
    /// * `component` - Component
    #[cfg_attr(not(feature = "cli"), expect(dead_code))]
    pub(crate) fn get_latest_version(&self, component: &Component) -> Result<Version> {
        components::get_latest_version(component, &self.environment, self.registry.base_urls())
    }

    /// Sets the default version for a component.
    ///
    /// # Arguments
    /// * `component` - Component
    /// * `version` - Version to set as default
    pub(crate) fn set_default_version(
        &mut self,
        component: &Component,
        version: Version,
    ) -> Result<()> {
        self.registry
            .set_default_component_version(&self.environment, component, version)
    }

    /// Checks if a specific version of a component exists.
    ///
    /// # Arguments
    /// * `component` - Component
    /// * `version` - Version to check
    #[cfg_attr(not(feature = "cli"), expect(dead_code))]
    pub(crate) fn version_exists(&self, component: &Component, version: &Version) -> Result<bool> {
        let component_installed = component.parent_component().unwrap_or(*component);
        Ok(Paths::find_version_dir(&self.environment, &component_installed, version)?.is_some())
    }

    /// Gets the settings manager.
    #[cfg_attr(not(feature = "cli"), expect(dead_code))]
    pub(crate) fn settings(&self) -> &Settings {
        self.registry.settings()
    }

    /// Gets the version-specific directory path for a component.
    ///
    /// Errors if the version isn't installed.
    ///
    /// # Arguments
    /// * `component` - Component
    /// * `version` - Version to get directory for
    pub fn get_version_dir(&self, component: &Component, version: &Version) -> Result<PathBuf> {
        let component = component.parent_component().unwrap_or(*component);
        Paths::find_version_dir(&self.environment, &component, version)?
            .ok_or_else(|| RzupError::VersionNotFound(version.clone()))
    }

    /// Update rzup by downloading and re-running the installation script.
    #[cfg_attr(not(feature = "cli"), expect(dead_code))]
    pub(crate) fn self_update(&self) -> Result<()> {
        self.emit(RzupEvent::InstallationStarted {
            id: "rzup".to_string(),
            version: "latest".to_string(),
        });

        let script_contents = distribution::download_text(
            format!(
                "{base_url}/install",
                base_url = self.registry.base_urls().risc0_base_url
            ),
            &None,
        )?;

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

    #[cfg_attr(not(feature = "cli"), expect(dead_code))]
    pub(crate) fn build_rust_toolchain(
        &mut self,
        repo_url: &str,
        tag_or_commit: &Option<String>,
        path: &Option<String>,
    ) -> Result<()> {
        let version =
            build::build_rust_toolchain(&self.environment, repo_url, tag_or_commit, path)?;
        self.set_default_version(&Component::RustToolchain, version)?;
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::distribution::Os;
    use std::convert::Infallible;
    use std::io::Write as _;
    use std::net::SocketAddr;
    use std::path::Path;
    use tempfile::TempDir;

    pub struct MockDistributionServer {
        pub base_urls: BaseUrls,
    }

    type HyperResponse = hyper::Response<http_body_util::Full<hyper::body::Bytes>>;

    async fn request_handler(
        install_script: String,
        require_bearer_token: bool,
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

        fn dummy_tar_xz_response(sub_dir: &str) -> HyperResponse {
            let mut tar_bytes = vec![];
            let mut tar_builder = tar::Builder::new(&mut tar_bytes);
            let mut header = tar::Header::new_gnu();
            header.set_size(4);
            tar_builder
                .append_data(
                    &mut header,
                    format!("{sub_dir}/tar_contents.bin"),
                    &[1, 2, 3, 4][..],
                )
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

        if require_bearer_token {
            let value = req
                .headers()
                .get("Authorization")
                .expect("Authorization provided");
            assert_eq!(value, "Bearer suchsecrettesttoken");
        }

        Ok(match &req.uri().to_string()[..] {
            "/github_api/repos/risc0/risc0/releases/latest" => {
                json_response("{\"tag_name\":\"v1.1.0\"}")
            }
            "/github_api/repos/risc0/risc0/releases/tags/v1.0.0" => json_response("{}"),
            "/github_api/repos/risc0/risc0/releases/tags/v1.0.0-rc.1" => json_response("{}"),
            "/github_api/repos/risc0/risc0/releases/tags/v1.0.0-rc.2" => json_response("{}"),
            "/github_api/repos/risc0/rust/releases/tags/r0.1.79.0" => json_response("{}"),
            "/risc0_github/risc0/releases/download/v1.0.0/\
                cargo-risczero-x86_64-unknown-linux-gnu.tgz" => dummy_tar_gz_response(),
            "/risc0_github/risc0/releases/download/v1.0.0-rc.1/\
                cargo-risczero-x86_64-unknown-linux-gnu.tgz" => dummy_tar_gz_response(),
            "/risc0_github/risc0/releases/download/v1.0.0-rc.2/\
                cargo-risczero-x86_64-unknown-linux-gnu.tgz" => dummy_tar_gz_response(),
            "/risc0_github/risc0/releases/download/v1.0.0/\
                cargo-risczero-aarch64-apple-darwin.tgz" => dummy_tar_gz_response(),
            "/risc0_github/rust/releases/download/r0.1.79.0/\
                rust-toolchain-x86_64-unknown-linux-gnu.tar.gz" => dummy_tar_gz_response(),
            "/risc0_github/rust/releases/download/r0.1.79.0/\
                rust-toolchain-aarch64-apple-darwin.tar.gz" => dummy_tar_gz_response(),
            "/github_api/repos/risc0/toolchain/releases/tags/2024.01.05" => json_response("{}"),
            "/risc0_github/toolchain/releases/download/2024.01.05/riscv32im-linux-x86_64.tar.xz" =>
                dummy_tar_xz_response("riscv32im-linux-x86_64"),
            "/risc0_github/toolchain/releases/download/2024.01.05/riscv32im-osx-arm64.tar.xz" =>
                dummy_tar_xz_response("riscv32im-osx-arm64"),
            "/github_api/repos/risc0/toolchain/releases/tags/2024.01.06" => json_response("{}"),
            "/risc0_github/toolchain/releases/download/2024.01.06/riscv32im-linux-x86_64.tar.xz" =>
                dummy_tar_xz_response("riscv32im-linux-x86_64"),
            "/github_api/repos/risc0/rust/releases/tags/r0.1.81.0" => json_response("{}"),
            "/risc0_github/rust/releases/download/r0.1.81.0/\
                rust-toolchain-x86_64-unknown-linux-gnu.tar.gz" => dummy_tar_gz_response(),
            "/risc0_github/rust/releases/download/r0.1.81.0/\
                rust-toolchain-aarch64-apple-darwin.tar.gz" => dummy_tar_gz_response(),
            "/github_api/repos/risc0/risc0/releases/tags/v5.0.0" => not_found(),
            "/github_api/repos/risc0/risc0/releases/tags/v1.1.0" => json_response("{}"),
            "/risc0_github/risc0/releases/download/v1.1.0/\
                cargo-risczero-x86_64-unknown-linux-gnu.tgz" => dummy_tar_gz_response(),
            "/risc0/install" => text_response(install_script.clone()),
            unknown => panic!("unexpected URI: {unknown}"),
        })
    }

    #[tokio::main]
    async fn server_main(
        install_script: String,
        require_bearer_token: bool,
        sender: tokio::sync::oneshot::Sender<SocketAddr>,
    ) {
        let listener = tokio::net::TcpListener::bind("localhost:0").await.unwrap();
        sender.send(listener.local_addr().unwrap()).unwrap();

        while let Ok((stream, _)) = listener.accept().await {
            let install_script = install_script.clone();
            hyper::server::conn::http1::Builder::new()
                .serve_connection(
                    hyper_util::rt::TokioIo::new(stream),
                    hyper::service::service_fn(move |req| {
                        request_handler(install_script.clone(), require_bearer_token, req)
                    }),
                )
                .await
                .unwrap()
        }
    }

    impl MockDistributionServer {
        pub fn new_with_options(install_script: String, require_bearer_token: bool) -> Self {
            let (send, recv) = tokio::sync::oneshot::channel();
            std::thread::spawn(move || server_main(install_script, require_bearer_token, send));
            let address = recv.blocking_recv().unwrap();
            Self {
                base_urls: BaseUrls {
                    risc0_github_base_url: format!("http://{address}/risc0_github"),
                    github_api_base_url: format!("http://{address}/github_api"),
                    risc0_base_url: format!("http://{address}/risc0"),
                },
            }
        }

        pub fn new() -> Self {
            Self::new_with_options("".into(), false)
        }

        pub fn new_with_install_script(install_script: String) -> Self {
            Self::new_with_options(install_script, false)
        }

        pub fn new_with_required_bearer_token() -> Self {
            Self::new_with_options("".into(), true)
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
                    let server = $crate::tests::MockDistributionServer::new();
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

    fn setup_test_env(
        base_urls: BaseUrls,
        github_token: Option<String>,
        platform: Platform,
    ) -> (TempDir, Rzup) {
        let tmp_dir = TempDir::new().unwrap();
        let rzup = Rzup::with_paths_urls_token_platform_and_event_handler(
            tmp_dir.path().join(".risc0"),
            tmp_dir.path().join(".rustup"),
            tmp_dir.path().join(".cargo"),
            base_urls,
            github_token,
            platform,
            |_| {},
        )
        .unwrap();
        (tmp_dir, rzup)
    }

    #[test]
    fn test_rzup_initialization() {
        let (_tmp_dir, rzup) = setup_test_env(
            invalid_base_urls(),
            None,
            Platform::new("x86_64", Os::Linux),
        );
        assert!(rzup
            .settings()
            .get_default_version(&Component::RustToolchain)
            .is_none());
        assert!(rzup
            .settings()
            .get_default_version(&Component::CargoRiscZero)
            .is_none());
    }

    fn test_install_and_uninstall_end_to_end(base_urls: BaseUrls) {
        let (_tmp_dir, mut rzup) = setup_test_env(base_urls, None, Platform::detect().unwrap());
        let cargo_risczero_version = Version::new(1, 0, 0);

        assert_eq!(
            rzup.get_version_dir(&Component::CargoRiscZero, &cargo_risczero_version),
            Err(RzupError::VersionNotFound(cargo_risczero_version.clone()))
        );
        assert_eq!(
            rzup.get_version_dir(&Component::R0Vm, &cargo_risczero_version),
            Err(RzupError::VersionNotFound(cargo_risczero_version.clone()))
        );

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
                .get_default_version(&Component::CargoRiscZero)
                .unwrap(),
            cargo_risczero_version
        );
        assert_eq!(
            rzup.list_versions(&Component::CargoRiscZero).unwrap(),
            vec![Version::new(1, 0, 0)]
        );
        assert!(rzup
            .get_version_dir(&Component::CargoRiscZero, &cargo_risczero_version)
            .is_ok());

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
        assert_eq!(
            rzup.get_version_dir(&Component::CargoRiscZero, &cargo_risczero_version),
            Err(RzupError::VersionNotFound(cargo_risczero_version.clone()))
        );

        // Test virtual installation
        rzup.install_component(
            &Component::R0Vm,
            Some(cargo_risczero_version.clone()),
            false,
        )
        .unwrap();
        assert!(rzup
            .version_exists(&Component::R0Vm, &cargo_risczero_version)
            .unwrap());
        assert_eq!(
            rzup.settings()
                .get_default_version(&Component::R0Vm)
                .unwrap(),
            cargo_risczero_version
        );
        assert_eq!(
            rzup.list_versions(&Component::R0Vm).unwrap(),
            vec![Version::new(1, 0, 0)]
        );
        assert!(rzup
            .get_version_dir(&Component::R0Vm, &cargo_risczero_version)
            .is_ok());

        // Test uninstallation
        rzup.uninstall_component(&Component::R0Vm, cargo_risczero_version.clone())
            .unwrap();
        assert!(!rzup
            .version_exists(&Component::R0Vm, &cargo_risczero_version)
            .unwrap());
        assert_eq!(rzup.list_versions(&Component::R0Vm).unwrap(), vec![]);
        assert_eq!(
            rzup.get_version_dir(&Component::R0Vm, &cargo_risczero_version),
            Err(RzupError::VersionNotFound(cargo_risczero_version.clone()))
        );

        // Rust
        let rust_version = Version::new(1, 79, 0);
        assert_eq!(
            rzup.get_version_dir(&Component::RustToolchain, &rust_version),
            Err(RzupError::VersionNotFound(rust_version.clone()))
        );
        rzup.install_component(&Component::RustToolchain, Some(rust_version.clone()), false)
            .unwrap();
        assert!(rzup
            .version_exists(&Component::RustToolchain, &rust_version)
            .unwrap());
        assert_eq!(
            rzup.list_versions(&Component::RustToolchain).unwrap(),
            vec![Version::new(1, 79, 0)]
        );
        assert!(rzup
            .get_version_dir(&Component::RustToolchain, &rust_version)
            .is_ok());

        // Test uninstallation
        rzup.uninstall_component(&Component::RustToolchain, rust_version.clone())
            .unwrap();
        assert!(!rzup
            .version_exists(&Component::RustToolchain, &rust_version)
            .unwrap());
        assert_eq!(
            rzup.list_versions(&Component::RustToolchain).unwrap(),
            vec![]
        );
        assert_eq!(
            rzup.get_version_dir(&Component::RustToolchain, &rust_version),
            Err(RzupError::VersionNotFound(rust_version.clone()))
        );

        // C++
        let cpp_version = Version::new(2024, 1, 5);
        assert_eq!(
            rzup.get_version_dir(&Component::CppToolchain, &cpp_version),
            Err(RzupError::VersionNotFound(cpp_version.clone()))
        );
        rzup.install_component(&Component::CppToolchain, Some(cpp_version.clone()), false)
            .unwrap();
        assert!(rzup
            .version_exists(&Component::CppToolchain, &cpp_version)
            .unwrap());
        assert_eq!(
            rzup.list_versions(&Component::CppToolchain).unwrap(),
            vec![Version::new(2024, 1, 5)]
        );
        assert!(rzup
            .get_version_dir(&Component::CppToolchain, &cpp_version)
            .is_ok());

        // Test uninstallation
        rzup.uninstall_component(&Component::CppToolchain, cpp_version.clone())
            .unwrap();
        assert!(!rzup
            .version_exists(&Component::CppToolchain, &cpp_version)
            .unwrap());
        assert_eq!(
            rzup.list_versions(&Component::CppToolchain).unwrap(),
            vec![]
        );
        assert_eq!(
            rzup.get_version_dir(&Component::CppToolchain, &cpp_version),
            Err(RzupError::VersionNotFound(cpp_version.clone()))
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

    fn assert_symlinks(path: &Path, mut expected_symlinks: Vec<(String, String)>) {
        let mut found_symlinks = vec![];
        for entry in walkdir::WalkDir::new(path) {
            let entry = entry.unwrap();
            if entry.path_is_symlink() {
                let entry_path = entry.path();
                let entry_relative_path = entry_path.strip_prefix(path).unwrap();
                let target_path = std::fs::read_link(entry_path).unwrap();
                let target_relative_path = target_path.strip_prefix(path).unwrap();
                found_symlinks.push((
                    entry_relative_path.to_str().unwrap().to_owned(),
                    target_relative_path.to_str().unwrap().to_owned(),
                ));
            }
        }

        found_symlinks.sort();
        expected_symlinks.sort();
        assert_eq!(found_symlinks, expected_symlinks);
    }

    fn assert_files(path: &Path, mut expected_files: Vec<String>) {
        // These files are expected to be here always more or less
        expected_files.push(".risc0/settings.toml".into());
        expected_files.push(".risc0/.rzup".into());

        let mut found_files = vec![];
        for entry in walkdir::WalkDir::new(path.join(".risc0")) {
            let entry = entry.unwrap();
            if entry.file_type().is_file() {
                let entry_path = entry.path();
                if entry_path.extension().is_none_or(|ext| ext != "lock") {
                    let entry_relative_path = entry_path.strip_prefix(path).unwrap();
                    found_files.push(entry_relative_path.to_str().unwrap().to_owned());
                }
            }
        }

        found_files.sort();
        expected_files.sort();
        assert_eq!(found_files, expected_files);
    }

    #[allow(clippy::too_many_arguments)]
    fn fresh_install_test(
        base_urls: BaseUrls,
        component: Component,
        component_to_install: Component,
        version: Version,
        expected_url: String,
        download_length: u64,
        expected_files: Vec<String>,
        expected_symlinks: Vec<(String, String)>,
        expected_version_dir: &str,
        use_github_token: bool,
        platform: Platform,
    ) {
        let github_token = use_github_token.then_some("suchsecrettesttoken".into());
        let (tmp_dir, mut rzup) = setup_test_env(base_urls.clone(), github_token, platform);

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                rzup.install_component(&component, Some(version.clone()), false)
                    .unwrap();
                assert!(rzup.version_exists(&component, &version).unwrap());
            },
            vec![
                RzupEvent::InstallationStarted {
                    id: component.to_string(),
                    version: version.to_string(),
                },
                RzupEvent::DownloadStarted {
                    id: component_to_install.to_string(),
                    version: version.to_string(),
                    url: expected_url,
                    len: Some(download_length),
                },
                RzupEvent::DownloadProgress {
                    id: component_to_install.to_string(),
                    incr: download_length,
                },
                RzupEvent::DownloadCompleted {
                    id: component_to_install.to_string(),
                    version: version.to_string(),
                },
                RzupEvent::InstallationCompleted {
                    id: component.to_string(),
                    version: version.to_string(),
                },
            ],
        );

        let actual_version_dir = rzup.get_version_dir(&component, &version).unwrap();
        assert_eq!(
            actual_version_dir
                .strip_prefix(tmp_dir.path())
                .unwrap()
                .to_str()
                .unwrap(),
            expected_version_dir
        );

        assert_symlinks(tmp_dir.path(), expected_symlinks);
        assert_files(tmp_dir.path(), expected_files);
    }

    #[allow(clippy::too_many_arguments)]
    fn already_installed_test(
        base_urls: BaseUrls,
        component: Component,
        version: Version,
        expected_files: Vec<String>,
        expected_symlinks: Vec<(String, String)>,
        expected_version_dir: &str,
        use_github_token: bool,
        platform: Platform,
    ) {
        let github_token = use_github_token.then_some("suchsecrettesttoken".into());
        let (tmp_dir, mut rzup) = setup_test_env(base_urls.clone(), github_token, platform);

        rzup.install_component(&component, Some(version.clone()), false)
            .unwrap();

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                rzup.install_component(&component, Some(version.clone()), false)
                    .unwrap();
            },
            vec![RzupEvent::ComponentAlreadyInstalled {
                id: component.to_string(),
                version: version.to_string(),
            }],
        );

        let actual_version_dir = rzup.get_version_dir(&component, &version).unwrap();
        assert_eq!(
            actual_version_dir
                .strip_prefix(tmp_dir.path())
                .unwrap()
                .to_str()
                .unwrap(),
            expected_version_dir
        );

        assert_symlinks(tmp_dir.path(), expected_symlinks);
        assert_files(tmp_dir.path(), expected_files);
    }

    #[allow(clippy::too_many_arguments)]
    fn already_installed_force_test(
        base_urls: BaseUrls,
        component: Component,
        component_to_install: Component,
        version: Version,
        expected_url: String,
        download_length: u64,
        expected_files: Vec<String>,
        expected_symlinks: Vec<(String, String)>,
        expected_version_dir: &str,
        use_github_token: bool,
        platform: Platform,
    ) {
        let github_token = use_github_token.then_some("suchsecrettesttoken".into());
        let (tmp_dir, mut rzup) = setup_test_env(base_urls.clone(), github_token, platform);

        rzup.install_component(&component, Some(version.clone()), false)
            .unwrap();

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                rzup.install_component(&component, Some(version.clone()), true)
                    .unwrap();
            },
            vec![
                RzupEvent::InstallationStarted {
                    id: component.to_string(),
                    version: version.to_string(),
                },
                RzupEvent::DownloadStarted {
                    id: component_to_install.to_string(),
                    version: version.to_string(),
                    url: expected_url,
                    len: Some(download_length),
                },
                RzupEvent::DownloadProgress {
                    id: component_to_install.to_string(),
                    incr: download_length,
                },
                RzupEvent::DownloadCompleted {
                    id: component_to_install.to_string(),
                    version: version.to_string(),
                },
                RzupEvent::InstallationCompleted {
                    id: component.to_string(),
                    version: version.to_string(),
                },
            ],
        );

        let actual_version_dir = rzup.get_version_dir(&component, &version).unwrap();
        assert_eq!(
            actual_version_dir
                .strip_prefix(tmp_dir.path())
                .unwrap()
                .to_str()
                .unwrap(),
            expected_version_dir
        );

        assert_symlinks(tmp_dir.path(), expected_symlinks);
        assert_files(tmp_dir.path(), expected_files);
    }

    #[allow(clippy::too_many_arguments)]
    fn install_test(
        base_urls: BaseUrls,
        component: Component,
        component_to_install: Component,
        version: Version,
        expected_url: String,
        download_length: u64,
        expected_files: Vec<String>,
        expected_symlinks: Vec<(String, String)>,
        expected_version_dir: &str,
        use_github_token: bool,
        platform: Platform,
    ) {
        fresh_install_test(
            base_urls.clone(),
            component,
            component_to_install,
            version.clone(),
            expected_url.clone(),
            download_length,
            expected_files.clone(),
            expected_symlinks.clone(),
            expected_version_dir,
            use_github_token,
            platform,
        );

        already_installed_test(
            base_urls.clone(),
            component,
            version.clone(),
            expected_files.clone(),
            expected_symlinks.clone(),
            expected_version_dir,
            use_github_token,
            platform,
        );

        already_installed_force_test(
            base_urls.clone(),
            component,
            component_to_install,
            version.clone(),
            expected_url.clone(),
            download_length,
            expected_files.clone(),
            expected_symlinks.clone(),
            expected_version_dir,
            use_github_token,
            platform,
        );
    }

    fn test_install_cargo_risczero(platform: Platform, target_triple: &str) {
        let server = MockDistributionServer::new();
        install_test(
            server.base_urls.clone(),
            Component::CargoRiscZero,
            Component::CargoRiscZero,
            Version::new(1, 0, 0),
            format!(
                "{base_url}/risc0/releases/download/v1.0.0/\
                cargo-risczero-{target_triple}.tgz",
                base_url = server.base_urls.risc0_github_base_url
            ),
            86,
            vec![format!(
                ".risc0/extensions/v1.0.0-cargo-risczero-{target_triple}/tar_contents.bin"
            )],
            vec![(
                ".cargo/bin/cargo-risczero".into(),
                format!(".risc0/extensions/v1.0.0-cargo-risczero-{target_triple}/cargo-risczero"),
            )],
            &format!(".risc0/extensions/v1.0.0-cargo-risczero-{target_triple}"),
            false, /* use_github_token */
            platform,
        )
    }

    #[test]
    fn install_cargo_risczero_x86_64_linux() {
        test_install_cargo_risczero(
            Platform::new("x86_64", Os::Linux),
            "x86_64-unknown-linux-gnu",
        );
    }

    #[test]
    fn install_cargo_risczero_aarch64_mac() {
        test_install_cargo_risczero(Platform::new("aarch64", Os::MacOs), "aarch64-apple-darwin");
    }

    fn test_install_r0vm(platform: Platform, target_triple: &str) {
        let server = MockDistributionServer::new();
        install_test(
            server.base_urls.clone(),
            Component::R0Vm,
            Component::CargoRiscZero,
            Version::new(1, 0, 0),
            format!(
                "{base_url}/risc0/releases/download/v1.0.0/\
                cargo-risczero-{target_triple}.tgz",
                base_url = server.base_urls.risc0_github_base_url
            ),
            86,
            vec![format!(
                ".risc0/extensions/v1.0.0-cargo-risczero-{target_triple}/tar_contents.bin"
            )],
            vec![
                (
                    ".cargo/bin/cargo-risczero".into(),
                    format!(
                        ".risc0/extensions/v1.0.0-cargo-risczero-{target_triple}/cargo-risczero"
                    ),
                ),
                (
                    ".cargo/bin/r0vm".into(),
                    format!(".risc0/extensions/v1.0.0-cargo-risczero-{target_triple}/r0vm"),
                ),
            ],
            &format!(".risc0/extensions/v1.0.0-cargo-risczero-{target_triple}"),
            false, /* use_github_token */
            platform,
        )
    }

    #[test]
    fn install_r0vm_x86_64_linux() {
        test_install_r0vm(
            Platform::new("x86_64", Os::Linux),
            "x86_64-unknown-linux-gnu",
        );
    }

    #[test]
    fn install_r0vm_aarch64_mac() {
        test_install_r0vm(Platform::new("aarch64", Os::MacOs), "aarch64-apple-darwin");
    }

    fn test_install_rust(platform: Platform, target_triple: &str) {
        let server = MockDistributionServer::new();
        install_test(
            server.base_urls.clone(),
            Component::RustToolchain,
            Component::RustToolchain,
            Version::new(1, 81, 0),
            format!(
                "{base_url}/rust/releases/download/r0.1.81.0/\
                rust-toolchain-{target_triple}.tar.gz",
                base_url = server.base_urls.risc0_github_base_url
            ),
            86,
            vec![format!(
                ".risc0/toolchains/v1.81.0-rust-{target_triple}/tar_contents.bin"
            )],
            vec![(
                ".rustup/toolchains/risc0".into(),
                format!(".risc0/toolchains/v1.81.0-rust-{target_triple}"),
            )],
            &format!(".risc0/toolchains/v1.81.0-rust-{target_triple}"),
            false, /* use_github_token */
            platform,
        )
    }

    #[test]
    fn install_rust_x86_64_linux() {
        test_install_rust(
            Platform::new("x86_64", Os::Linux),
            "x86_64-unknown-linux-gnu",
        );
    }

    #[test]
    fn install_rust_aarch64_mac() {
        test_install_rust(Platform::new("aarch64", Os::MacOs), "aarch64-apple-darwin");
    }

    fn test_install_cpp(platform: Platform, target_double: &str, target_triple: &str) {
        let server = MockDistributionServer::new();

        // This is just the size of the archive we end up creating.
        let download_size = if target_double == "linux-x86_64" {
            152
        } else {
            148
        };

        install_test(
            server.base_urls.clone(),
            Component::CppToolchain,
            Component::CppToolchain,
            Version::new(2024, 1, 5),
            format!(
                "{base_url}/toolchain/releases/download/2024.01.05/\
                riscv32im-{target_double}.tar.xz",
                base_url = server.base_urls.risc0_github_base_url
            ),
            download_size,
            vec![format!(
                ".risc0/toolchains/v2024.1.5-cpp-{target_triple}/\
                riscv32im-{target_double}/tar_contents.bin"
            )],
            vec![(
                ".risc0/cpp".into(),
                format!(
                    ".risc0/toolchains/v2024.1.5-cpp-{target_triple}/riscv32im-{target_double}"
                ),
            )],
            &format!(".risc0/toolchains/v2024.1.5-cpp-{target_triple}/riscv32im-{target_double}"),
            false, /* use_github_token */
            platform,
        )
    }

    #[test]
    fn install_cpp_x86_64_linux() {
        test_install_cpp(
            Platform::new("x86_64", Os::Linux),
            "linux-x86_64",
            "x86_64-unknown-linux-gnu",
        );
    }

    #[test]
    fn install_cpp_aarch64_mac() {
        test_install_cpp(
            Platform::new("aarch64", Os::MacOs),
            "osx-arm64",
            "aarch64-apple-darwin",
        );
    }

    #[test]
    fn install_with_github_token() {
        let server = MockDistributionServer::new_with_required_bearer_token();
        install_test(
            server.base_urls.clone(),
            Component::CargoRiscZero,
            Component::CargoRiscZero,
            Version::new(1, 0, 0),
            format!(
                "{base_url}/risc0/releases/download/v1.0.0/\
                cargo-risczero-x86_64-unknown-linux-gnu.tgz",
                base_url = server.base_urls.risc0_github_base_url
            ),
            86,
            vec![
                ".risc0/extensions/v1.0.0-cargo-risczero-x86_64-unknown-linux-gnu/tar_contents.bin"
                    .into(),
            ],
            vec![(
                ".cargo/bin/cargo-risczero".into(),
                ".risc0/extensions/v1.0.0-cargo-risczero-x86_64-unknown-linux-gnu/cargo-risczero"
                    .into(),
            )],
            ".risc0/extensions/v1.0.0-cargo-risczero-x86_64-unknown-linux-gnu",
            true, /* use_github_token */
            Platform::new("x86_64", Os::Linux),
        )
    }

    fn test_list_multiple_versions(component: Component, version1: Version, version2: Version) {
        let server = MockDistributionServer::new();
        let (_tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        rzup.install_component(&component, Some(version1.clone()), false)
            .unwrap();

        rzup.install_component(&component, Some(version2.clone()), false)
            .unwrap();

        assert_eq!(
            rzup.list_versions(&component).unwrap(),
            vec![version2, version1]
        );
    }

    #[test]
    fn list_multiple_versions_cargo_risczero() {
        test_list_multiple_versions(
            Component::CargoRiscZero,
            Version::new(1, 0, 0),
            Version::new(1, 1, 0),
        );
    }

    #[test]
    fn list_multiple_versions_r0vm() {
        test_list_multiple_versions(
            Component::R0Vm,
            Version::new(1, 0, 0),
            Version::new(1, 1, 0),
        );
    }

    #[test]
    fn list_multiple_versions_rust() {
        test_list_multiple_versions(
            Component::RustToolchain,
            Version::new(1, 79, 0),
            Version::new(1, 81, 0),
        );
    }

    #[test]
    fn list_multiple_versions_cpp() {
        test_list_multiple_versions(
            Component::CppToolchain,
            Version::new(2024, 1, 5),
            Version::new(2024, 1, 6),
        );
    }

    fn set_default_version_test(
        rzup: &mut Rzup,
        tmp_dir: &TempDir,
        component: Component,
        version1: Version,
        version2: Version,
        expected_symlinks1: Vec<(String, String)>,
        expected_symlinks2: Vec<(String, String)>,
    ) {
        rzup.install_component(&component, Some(version1.clone()), false)
            .unwrap();

        assert_eq!(
            rzup.get_default_version(&component).unwrap().unwrap().0,
            version1
        );

        rzup.install_component(&component, Some(version2.clone()), false)
            .unwrap();
        assert_symlinks(tmp_dir.path(), expected_symlinks2.clone());

        assert_eq!(
            rzup.get_default_version(&component).unwrap().unwrap().0,
            version2
        );

        rzup.set_default_version(&component, version1.clone())
            .unwrap();
        assert_symlinks(tmp_dir.path(), expected_symlinks1.clone());

        assert_eq!(
            rzup.get_default_version(&component).unwrap().unwrap().0,
            version1
        );
    }

    #[test]
    fn set_default_version_cargo_risczero() {
        let server = MockDistributionServer::new();
        let (tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        set_default_version_test(
            &mut rzup,
            &tmp_dir,
            Component::CargoRiscZero,
            Version::new(1, 0, 0),
            Version::new(1, 1, 0),
            vec![(
                ".cargo/bin/cargo-risczero".into(),
                ".risc0/extensions/v1.0.0-cargo-risczero-x86_64-unknown-linux-gnu/cargo-risczero"
                    .into(),
            )],
            vec![(
                ".cargo/bin/cargo-risczero".into(),
                ".risc0/extensions/v1.1.0-cargo-risczero-x86_64-unknown-linux-gnu/cargo-risczero"
                    .into(),
            )],
        );
    }

    #[test]
    fn set_default_version_r0vm() {
        let server = MockDistributionServer::new();
        let (tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        set_default_version_test(
            &mut rzup,
            &tmp_dir,
            Component::R0Vm,
            Version::new(1, 0, 0),
            Version::new(1, 1, 0),
            vec![
                (
                    ".cargo/bin/cargo-risczero".into(),
                    ".risc0/extensions/v1.0.0-cargo-risczero-x86_64-unknown-linux-gnu/cargo-risczero"
                        .into(),
                ),
                (
                    ".cargo/bin/r0vm".into(),
                    ".risc0/extensions/v1.0.0-cargo-risczero-x86_64-unknown-linux-gnu/r0vm".into(),
                )
            ],
            vec![
                (
                    ".cargo/bin/cargo-risczero".into(),
                    ".risc0/extensions/v1.0.0-cargo-risczero-x86_64-unknown-linux-gnu/cargo-risczero"
                        .into(),
                ),
                (
                    ".cargo/bin/r0vm".into(),
                    ".risc0/extensions/v1.1.0-cargo-risczero-x86_64-unknown-linux-gnu/r0vm".into(),
                )
            ],
        );
    }

    #[test]
    fn set_default_version_r0vm_rc_version() {
        let server = MockDistributionServer::new();
        let (tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        set_default_version_test(
            &mut rzup,
            &tmp_dir,
            Component::R0Vm,
            Version::parse("1.0.0-rc.1").unwrap(),
            Version::parse("1.0.0-rc.2").unwrap(),
            vec![
                (
                    ".cargo/bin/cargo-risczero".into(),
                    ".risc0/extensions/v1.0.0-rc.1-cargo-risczero-x86_64-unknown-linux-gnu/cargo-risczero"
                        .into(),
                ),
                (
                    ".cargo/bin/r0vm".into(),
                    ".risc0/extensions/v1.0.0-rc.1-cargo-risczero-x86_64-unknown-linux-gnu/r0vm"
                        .into(),
                )
            ],
            vec![
                (
                    ".cargo/bin/cargo-risczero".into(),
                    ".risc0/extensions/v1.0.0-rc.1-cargo-risczero-x86_64-unknown-linux-gnu/cargo-risczero"
                        .into(),
                ),
                (
                    ".cargo/bin/r0vm".into(),
                    ".risc0/extensions/v1.0.0-rc.2-cargo-risczero-x86_64-unknown-linux-gnu/r0vm"
                        .into(),
                )
            ],
        );
    }

    #[test]
    fn set_default_version_r0vm_after_cargo_risczero_installed() {
        let server = MockDistributionServer::new();
        let (tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        rzup.install_component(
            &Component::CargoRiscZero,
            Some(Version::new(1, 0, 0)),
            false, /* force */
        )
        .unwrap();
        rzup.install_component(
            &Component::CargoRiscZero,
            Some(Version::new(1, 1, 0)),
            false, /* force */
        )
        .unwrap();

        set_default_version_test(
            &mut rzup,
            &tmp_dir,
            Component::R0Vm,
            Version::new(1, 0, 0),
            Version::new(1, 1, 0),
            vec![
                (
                    ".cargo/bin/cargo-risczero".into(),
                    ".risc0/extensions/v1.1.0-cargo-risczero-x86_64-unknown-linux-gnu/cargo-risczero"
                        .into(),
                ),
                (
                    ".cargo/bin/r0vm".into(),
                    ".risc0/extensions/v1.0.0-cargo-risczero-x86_64-unknown-linux-gnu/r0vm".into(),
                )
            ],
            vec![
                (
                    ".cargo/bin/cargo-risczero".into(),
                    ".risc0/extensions/v1.1.0-cargo-risczero-x86_64-unknown-linux-gnu/cargo-risczero"
                        .into(),
                ),
                (
                    ".cargo/bin/r0vm".into(),
                    ".risc0/extensions/v1.1.0-cargo-risczero-x86_64-unknown-linux-gnu/r0vm".into(),
                )
            ],
        );
    }

    #[test]
    fn set_default_version_rust() {
        let server = MockDistributionServer::new();
        let (tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        set_default_version_test(
            &mut rzup,
            &tmp_dir,
            Component::RustToolchain,
            Version::new(1, 79, 0),
            Version::new(1, 81, 0),
            vec![(
                ".rustup/toolchains/risc0".into(),
                ".risc0/toolchains/v1.79.0-rust-x86_64-unknown-linux-gnu".into(),
            )],
            vec![(
                ".rustup/toolchains/risc0".into(),
                ".risc0/toolchains/v1.81.0-rust-x86_64-unknown-linux-gnu".into(),
            )],
        );
    }

    #[test]
    fn set_default_version_cpp() {
        let server = MockDistributionServer::new();
        let (tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        set_default_version_test(
            &mut rzup,
            &tmp_dir,
            Component::CppToolchain,
            Version::new(2024, 1, 5),
            Version::new(2024, 1, 6),
            vec![(
                ".risc0/cpp".into(),
                ".risc0/toolchains/v2024.1.5-cpp-x86_64-unknown-linux-gnu/riscv32im-linux-x86_64"
                    .into(),
            )],
            vec![(
                ".risc0/cpp".into(),
                ".risc0/toolchains/v2024.1.6-cpp-x86_64-unknown-linux-gnu/riscv32im-linux-x86_64"
                    .into(),
            )],
        );
    }

    fn default_version_after_uninstall(
        tmp_dir: &TempDir,
        rzup: &mut Rzup,
        component: Component,
        version1: Version,
        version2: Version,
        uninstall_with_rm: bool,
        expected_path: &Path,
    ) {
        rzup.install_component(&component, Some(version2.clone()), false)
            .unwrap();

        rzup.install_component(&component, Some(version1.clone()), false)
            .unwrap();

        if uninstall_with_rm {
            let mut version_dir = rzup.get_version_dir(&component, &version1).unwrap();
            // Remove C++ sub-dir component
            if component == Component::CppToolchain {
                version_dir.pop();
            }
            std::fs::remove_dir_all(version_dir).unwrap()
        } else {
            rzup.uninstall_component(&component, version1.clone())
                .unwrap();

            // ensure we updated the settings.toml
            let settings: settings::Settings = toml::from_str(
                &std::fs::read_to_string(tmp_dir.path().join(".risc0/settings.toml")).unwrap(),
            )
            .unwrap();
            let mut expected = settings::Settings::default();
            expected.set_default_version(&component, &version2);
            if let Some(parent) = component.parent_component() {
                expected.set_default_version(&parent, &version2);
            }
            assert_eq!(settings, expected);
        }

        let (default_version, path) = rzup.get_default_version(&component).unwrap().unwrap();
        assert_eq!(default_version, version2);
        assert_eq!(path, expected_path);
    }

    #[test]
    fn default_version_after_uninstall_cargo_risczero() {
        let server = MockDistributionServer::new();
        let (tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        for uninstall_with_rm in [true, false] {
            default_version_after_uninstall(
                &tmp_dir,
                &mut rzup,
                Component::CargoRiscZero,
                Version::new(1, 0, 0),
                Version::new(1, 1, 0),
                uninstall_with_rm,
                &tmp_dir
                    .path()
                    .join(".risc0/extensions/v1.1.0-cargo-risczero-x86_64-unknown-linux-gnu"),
            );
        }
    }

    #[test]
    fn default_version_after_uninstall_r0vm() {
        let server = MockDistributionServer::new();
        let (tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        for uninstall_with_rm in [true, false] {
            default_version_after_uninstall(
                &tmp_dir,
                &mut rzup,
                Component::R0Vm,
                Version::new(1, 0, 0),
                Version::new(1, 1, 0),
                uninstall_with_rm,
                &tmp_dir
                    .path()
                    .join(".risc0/extensions/v1.1.0-cargo-risczero-x86_64-unknown-linux-gnu"),
            );
        }
    }

    #[test]
    fn default_version_after_uninstall_rust() {
        let server = MockDistributionServer::new();
        let (tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        for uninstall_with_rm in [true, false] {
            default_version_after_uninstall(
                &tmp_dir,
                &mut rzup,
                Component::RustToolchain,
                Version::new(1, 79, 0),
                Version::new(1, 81, 0),
                uninstall_with_rm,
                &tmp_dir
                    .path()
                    .join(".risc0/toolchains/v1.81.0-rust-x86_64-unknown-linux-gnu"),
            );
        }
    }

    #[test]
    fn default_version_after_uninstall_cpp() {
        let server = MockDistributionServer::new();
        let (tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        for uninstall_with_rm in [true, false] {
            default_version_after_uninstall(
                &tmp_dir,
                &mut rzup,
                Component::CppToolchain,
                Version::new(2024, 1, 5),
                Version::new(2024, 1, 6),
                uninstall_with_rm,
                &tmp_dir.path().join(
                    ".risc0/toolchains/v2024.1.6-cpp-x86_64-unknown-linux-gnu/riscv32im-linux-x86_64",
                ),
            );
        }
    }

    #[test]
    fn install_non_existent() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );
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

    fn uninstall_test(component: Component, version: Version) {
        let server = MockDistributionServer::new();
        let (tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        rzup.install_component(&component, Some(version.clone()), false)
            .unwrap();

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                rzup.uninstall_component(&component, version.clone())
                    .unwrap();
            },
            vec![RzupEvent::Uninstalled {
                id: component.to_string(),
                version: version.to_string(),
            }],
        );

        assert_files(tmp_dir.path(), vec![]);
    }

    #[test]
    fn uninstall_cargo_risczero() {
        uninstall_test(Component::CargoRiscZero, Version::new(1, 0, 0));
    }

    #[test]
    fn uninstall_r0vm() {
        uninstall_test(Component::R0Vm, Version::new(1, 0, 0));
    }

    #[test]
    fn uninstall_rust() {
        uninstall_test(Component::RustToolchain, Version::new(1, 81, 0));
    }

    #[test]
    fn uninstall_cpp() {
        uninstall_test(Component::CppToolchain, Version::new(2024, 1, 5));
    }

    #[test]
    fn get_latest_version() {
        let server = MockDistributionServer::new();
        let (_tmp_dir, rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        assert_eq!(
            rzup.get_latest_version(&Component::CargoRiscZero).unwrap(),
            Version::new(1, 1, 0)
        );
    }

    struct LegacyVersionsFixture {
        rzup: Rzup,
        tmp_dir: TempDir,
        legacy_rust_dir: PathBuf,
        legacy_cargo_risczero_dir: PathBuf,
        legacy_cpp_dir: PathBuf,
    }

    impl LegacyVersionsFixture {
        fn new(rust_dir_name: &str, cargo_risczero_dir_name: &str, cpp_dir_name: &str) -> Self {
            let (tmp_dir, rzup) = setup_test_env(
                invalid_base_urls(),
                None,
                Platform::new("x86_64", Os::Linux),
            );

            let legacy_rust_dir = tmp_dir.path().join(".risc0/toolchains").join(rust_dir_name);
            std::fs::create_dir_all(&legacy_rust_dir).unwrap();

            let legacy_cargo_risczero_dir = tmp_dir
                .path()
                .join(".risc0/extensions")
                .join(cargo_risczero_dir_name);
            std::fs::create_dir_all(&legacy_cargo_risczero_dir).unwrap();

            let legacy_cpp_dir = tmp_dir.path().join(".risc0/toolchains").join(cpp_dir_name);
            std::fs::create_dir_all(&legacy_cpp_dir).unwrap();

            Self {
                rzup,
                tmp_dir,
                legacy_rust_dir,
                legacy_cargo_risczero_dir,
                legacy_cpp_dir,
            }
        }
    }

    fn get_legacy_versions(rust_dir_name: &str, cargo_risczero_dir_name: &str, cpp_dir_name: &str) {
        let fix = LegacyVersionsFixture::new(rust_dir_name, cargo_risczero_dir_name, cpp_dir_name);

        assert_eq!(
            fix.rzup
                .get_version_dir(&Component::RustToolchain, &Version::new(1, 81, 0))
                .unwrap(),
            fix.legacy_rust_dir
        );
        assert_eq!(
            fix.rzup
                .get_version_dir(
                    &Component::CargoRiscZero,
                    &Version::parse("1.2.1-rc.0").unwrap()
                )
                .unwrap(),
            fix.legacy_cargo_risczero_dir
        );
        assert_eq!(
            fix.rzup
                .get_version_dir(&Component::CppToolchain, &Version::new(2024, 1, 5))
                .unwrap(),
            fix.legacy_cpp_dir
        );
    }

    #[test]
    fn get_legacy_versions_old_rzup_apple_aarch64() {
        get_legacy_versions(
            "r0.1.81.0-risc0-rust-aarch64-apple-darwin",
            "v1.2.1-rc.0-cargo-risczero",
            "2024.01.05-risc0-cpp-aarch64-apple-darwin",
        );
    }

    #[test]
    fn get_legacy_versions_old_rzup_linux_x86() {
        get_legacy_versions(
            "r0.1.81.0-risc0-rust-x86_64-unknown-linux-gnu",
            "v1.2.1-rc.0-cargo-risczero",
            "2024.01.05-risc0-cpp-x86_64-unknown-linux-gnu",
        );
    }

    #[test]
    fn get_legacy_versions_cargo_risczero_install_apple_aarch64() {
        get_legacy_versions(
            "rust_aarch64-apple-darwin_r0.1.81.0",
            "v1.2.1-rc.0-cargo-risczero",
            "c_aarch64-apple-darwin_2024.01.05",
        );
    }

    #[test]
    fn get_legacy_versions_cargo_risczero_install_linux_x86() {
        get_legacy_versions(
            "rust_x86_64-unknown-linux-gnu_r0.1.81.0",
            "v1.2.1-rc.0-cargo-risczero",
            "c_x86_64-unknown-linux-gnu_2024.01.05",
        );
    }

    fn get_default_legacy_versions(
        rust_dir_name: &str,
        cargo_risczero_dir_name: &str,
        cpp_dir_name: &str,
    ) {
        let fix = LegacyVersionsFixture::new(rust_dir_name, cargo_risczero_dir_name, cpp_dir_name);

        assert_eq!(
            fix.rzup
                .get_default_version(&Component::RustToolchain)
                .unwrap()
                .unwrap()
                .0,
            Version::new(1, 81, 0)
        );

        assert_eq!(
            fix.rzup
                .get_default_version(&Component::CargoRiscZero)
                .unwrap()
                .unwrap()
                .0,
            Version::parse("1.2.1-rc.0").unwrap()
        );

        assert_eq!(
            fix.rzup
                .get_default_version(&Component::CppToolchain)
                .unwrap()
                .unwrap()
                .0,
            Version::new(2024, 1, 5)
        );
    }

    #[test]
    fn get_default_legacy_versions_old_rzup_apple_aarch64() {
        get_default_legacy_versions(
            "r0.1.81.0-risc0-rust-aarch64-apple-darwin",
            "v1.2.1-rc.0-cargo-risczero",
            "2024.01.05-risc0-cpp-aarch64-apple-darwin",
        );
    }

    #[test]
    fn get_default_legacy_versions_old_rzup_linux_x86() {
        get_default_legacy_versions(
            "r0.1.81.0-risc0-rust-x86_64-unknown-linux-gnu",
            "v1.2.1-rc.0-cargo-risczero",
            "2024.01.05-risc0-cpp-x86_64-unknown-linux-gnu",
        );
    }

    #[test]
    fn get_default_legacy_versions_cargo_risczero_install_apple_aarch64() {
        get_default_legacy_versions(
            "rust_aarch64-apple-darwin_r0.1.81.0",
            "v1.2.1-rc.0-cargo-risczero",
            "c_aarch64-apple-darwin_2024.01.05",
        );
    }

    #[test]
    fn get_default_legacy_versions_cargo_risczero_install_linux_x86() {
        get_default_legacy_versions(
            "rust_x86_64-unknown-linux-gnu_r0.1.81.0",
            "v1.2.1-rc.0-cargo-risczero",
            "c_x86_64-unknown-linux-gnu_2024.01.05",
        );
    }

    fn list_legacy_versions(dir1: &str, dir2: &str, expected_versions: Vec<Version>) {
        let (tmp_dir, rzup) = setup_test_env(
            invalid_base_urls(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        let legacy_rust_dir1 = tmp_dir.path().join(".risc0/toolchains").join(dir1);
        std::fs::create_dir_all(&legacy_rust_dir1).unwrap();

        let legacy_rust_dir2 = tmp_dir.path().join(".risc0/toolchains").join(dir2);
        std::fs::create_dir_all(&legacy_rust_dir2).unwrap();

        assert_eq!(
            rzup.list_versions(&Component::RustToolchain).unwrap(),
            expected_versions
        );
    }

    #[test]
    fn list_legacy_versions_old_rzup_apple_aarch64() {
        list_legacy_versions(
            "r0.1.79.0-risc0-rust-aarch64-apple-darwin",
            "r0.1.81.0-risc0-rust-aarch64-apple-darwin",
            vec![Version::new(1, 81, 0), Version::new(1, 79, 0)],
        );
    }

    #[test]
    fn list_legacy_versions_old_rzup_linux_x86() {
        list_legacy_versions(
            "r0.1.79.0-risc0-rust-x86_64-unknown-linux-gnu",
            "r0.1.81.0-risc0-rust-x86_64-unknown-linux-gnu",
            vec![Version::new(1, 81, 0), Version::new(1, 79, 0)],
        );
    }

    #[test]
    fn list_legacy_versions_cargo_risczero_install_aaple_aarch64() {
        list_legacy_versions(
            "rust_aarch64-apple-darwin_r0.1.79.0",
            "rust_aarch64-apple-darwin_r0.1.81.0",
            vec![Version::new(1, 81, 0), Version::new(1, 79, 0)],
        );
    }

    #[test]
    fn list_legacy_versions_cargo_risczero_install_linux_x86() {
        list_legacy_versions(
            "rust_x86_64-unknown-linux-gnu_r0.1.79.0",
            "rust_x86_64-unknown-linux-gnu_r0.1.81.0",
            vec![Version::new(1, 81, 0), Version::new(1, 79, 0)],
        );
    }

    fn set_default_version_legacy_versions(
        rust_dir_name: &str,
        cargo_risczero_dir_name: &str,
        cpp_dir_name: &str,
    ) {
        let mut fix =
            LegacyVersionsFixture::new(rust_dir_name, cargo_risczero_dir_name, cpp_dir_name);
        fix.rzup
            .set_default_version(&Component::RustToolchain, Version::new(1, 81, 0))
            .unwrap();

        fix.rzup
            .set_default_version(
                &Component::CargoRiscZero,
                Version::parse("1.2.1-rc.0").unwrap(),
            )
            .unwrap();

        fix.rzup
            .set_default_version(&Component::CppToolchain, Version::new(2024, 1, 5))
            .unwrap();

        assert_symlinks(
            fix.tmp_dir.path(),
            vec![
                (
                    ".cargo/bin/cargo-risczero".into(),
                    fix.legacy_cargo_risczero_dir
                        .strip_prefix(fix.tmp_dir.path())
                        .unwrap()
                        .join("cargo-risczero")
                        .to_str()
                        .unwrap()
                        .into(),
                ),
                (
                    ".rustup/toolchains/risc0".into(),
                    fix.legacy_rust_dir
                        .strip_prefix(fix.tmp_dir.path())
                        .unwrap()
                        .to_str()
                        .unwrap()
                        .into(),
                ),
                (
                    ".risc0/cpp".into(),
                    fix.legacy_cpp_dir
                        .strip_prefix(fix.tmp_dir.path())
                        .unwrap()
                        .to_str()
                        .unwrap()
                        .into(),
                ),
            ],
        );
    }

    #[test]
    fn set_default_version_legacy_versions_old_rzup_apple_aarch64() {
        set_default_version_legacy_versions(
            "r0.1.81.0-risc0-rust-aarch64-apple-darwin",
            "v1.2.1-rc.0-cargo-risczero",
            "2024.01.05-risc0-cpp-aarch64-apple-darwin",
        );
    }

    #[test]
    fn set_default_version_legacy_versions_old_rzup_linux_x86() {
        set_default_version_legacy_versions(
            "r0.1.81.0-risc0-rust-x86_64-unknown-linux-gnu",
            "v1.2.1-rc.0-cargo-risczero",
            "2024.01.05-risc0-cpp-x86_64-unknown-linux-gnu",
        );
    }

    #[test]
    fn set_default_version_legacy_versions_cargo_risczero_install_apple_aarch64() {
        set_default_version_legacy_versions(
            "rust_aarch64-apple-darwin_r0.1.81.0",
            "v1.2.1-rc.0-cargo-risczero",
            "c_aarch64-apple-darwin_2024.01.05",
        );
    }

    #[test]
    fn set_default_version_legacy_versions_cargo_risczero_install_linux_x86() {
        set_default_version_legacy_versions(
            "rust_x86_64-unknown-linux-gnu_r0.1.81.0",
            "v1.2.1-rc.0-cargo-risczero",
            "c_x86_64-unknown-linux-gnu_2024.01.05",
        );
    }

    #[test]
    fn set_default_version_legacy_version_has_dir_instead_of_symlink() {
        let (tmp_dir, mut rzup) = setup_test_env(
            invalid_base_urls(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        let legacy_cpp_dir =
            PathBuf::from(".risc0/toolchains/2024.01.05-risc0-cpp-x86_64-unknown-linux-gnu");
        std::fs::create_dir_all(tmp_dir.path().join(&legacy_cpp_dir)).unwrap();

        // I'm not sure why some machine would have a directory here instead of a symlink, but
        // there was an automation machine in this state.
        std::fs::create_dir(tmp_dir.path().join(".risc0/cpp")).unwrap();

        rzup.set_default_version(&Component::CppToolchain, Version::new(2024, 1, 5))
            .unwrap();

        assert_symlinks(
            tmp_dir.path(),
            vec![(".risc0/cpp".into(), legacy_cpp_dir.to_str().unwrap().into())],
        );
    }

    fn uninstall_legacy_versions(
        rust_dir_name: &str,
        cargo_risczero_dir_name: &str,
        cpp_dir_name: &str,
    ) {
        let mut fix =
            LegacyVersionsFixture::new(rust_dir_name, cargo_risczero_dir_name, cpp_dir_name);

        fix.rzup
            .set_default_version(&Component::RustToolchain, Version::new(1, 81, 0))
            .unwrap();

        fix.rzup
            .uninstall_component(&Component::RustToolchain, Version::new(1, 81, 0))
            .unwrap();

        fix.rzup
            .set_default_version(
                &Component::CargoRiscZero,
                Version::parse("1.2.1-rc.0").unwrap(),
            )
            .unwrap();

        fix.rzup
            .uninstall_component(
                &Component::CargoRiscZero,
                Version::parse("1.2.1-rc.0").unwrap(),
            )
            .unwrap();

        fix.rzup
            .set_default_version(&Component::CppToolchain, Version::new(2024, 1, 5))
            .unwrap();

        fix.rzup
            .uninstall_component(&Component::CppToolchain, Version::new(2024, 1, 5))
            .unwrap();

        assert_files(fix.tmp_dir.path(), vec![]);
    }

    #[test]
    fn uninstall_legacy_versions_old_rzup_apple_aarch64() {
        uninstall_legacy_versions(
            "r0.1.81.0-risc0-rust-aarch64-apple-darwin",
            "v1.2.1-rc.0-cargo-risczero",
            "2024.01.05-risc0-cpp-aarch64-apple-darwin",
        )
    }

    #[test]
    fn uninstall_legacy_versions_old_rzup_linux_x86() {
        uninstall_legacy_versions(
            "r0.1.81.0-risc0-rust-x86_64-unknown-linux-gnu",
            "v1.2.1-rc.0-cargo-risczero",
            "2024.01.05-risc0-cpp-x86_64-unknown-linux-gnu",
        )
    }

    #[test]
    fn uninstall_legacy_versions_cargo_risczero_install_apple_aarch64() {
        uninstall_legacy_versions(
            "rust_aarch64-apple-darwin_r0.1.81.0",
            "v1.2.1-rc.0-cargo-risczero",
            "c_aarch64-apple-darwin_2024.01.05",
        )
    }

    #[test]
    fn uninstall_legacy_versions_cargo_risczero_install_linux_x86() {
        uninstall_legacy_versions(
            "rust_x86_64-unknown-linux-gnu_r0.1.81.0",
            "v1.2.1-rc.0-cargo-risczero",
            "c_x86_64-unknown-linux-gnu_2024.01.05",
        )
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
        let (_, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

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
        let (_, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

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

    fn write_script(path: &Path, contents: &str) {
        use std::os::unix::fs::PermissionsExt as _;

        std::fs::write(path, contents).unwrap();
        let mut perms = std::fs::metadata(path).unwrap().permissions();
        perms.set_mode(0o775);
        std::fs::set_permissions(path, perms).unwrap();
    }

    fn create_fake_rust_repo(tmp_dir: &TempDir) -> (PathBuf, Version) {
        let test_repo = tmp_dir.path().join("test-repo");
        std::fs::create_dir(&test_repo).unwrap();
        build::run_command(
            "git",
            &["-c", "init.defaultBranch=master", "init"],
            Some(&test_repo),
            &[
                ("GIT_CONFIG_SYSTEM", "/dev/null"),
                ("GIT_CONFIG_GLOBAL", "/dev/null"),
            ],
        )
        .unwrap();

        std::fs::create_dir(test_repo.join("src")).unwrap();
        std::fs::write(test_repo.join("src/version"), "1.34.0").unwrap();
        write_script(
            &test_repo.join("x"),
            "\
            #!/bin/bash
            mkdir -p build/foo/stage2/bin
            mkdir -p build/foo/stage2-tools-bin
            touch build/foo/stage2/bin/rustc
            touch build/foo/stage2-tools-bin/cargo-fmt
            echo 'build output line 1'
            echo 'build output line 2'
            ",
        );

        build::run_command("git", &["add", "."], Some(&test_repo), &[]).unwrap();
        build::run_command(
            "git",
            &[
                "-c",
                "user.name=Testy",
                "-c",
                "user.email=testy@example.com",
                "commit",
                "--message",
                "initial commit",
            ],
            Some(&test_repo),
            &[
                ("GIT_CONFIG_SYSTEM", "/dev/null"),
                ("GIT_CONFIG_GLOBAL", "/dev/null"),
            ],
        )
        .unwrap();
        build::run_command("git", &["tag", "foo"], Some(&test_repo), &[]).unwrap();

        write_script(
            &test_repo.join("x"),
            "\
            #!/bin/bash
            mkdir -p build/foo/stage2/bin
            mkdir -p build/foo/stage2-tools-bin
            touch build/foo/stage2/bin/rustc
            touch build/foo/stage2-tools-bin/cargo-fmt
            touch build/foo/stage2-tools-bin/bar-fmt
            echo 'build output line 1'
            echo 'build output line 2'
            ",
        );

        build::run_command("git", &["add", "."], Some(&test_repo), &[]).unwrap();
        build::run_command(
            "git",
            &[
                "-c",
                "user.name=Testy",
                "-c",
                "user.email=testy@example.com",
                "commit",
                "--message",
                "bar",
            ],
            Some(&test_repo),
            &[
                ("GIT_CONFIG_SYSTEM", "/dev/null"),
                ("GIT_CONFIG_GLOBAL", "/dev/null"),
            ],
        )
        .unwrap();

        let commit = build::git_short_rev_parse(&test_repo, "HEAD").unwrap();
        let mut version = Version::new(1, 34, 0);
        version.build = semver::BuildMetadata::new(&commit).unwrap();

        (test_repo, version)
    }

    #[test]
    fn build_rust_toolchain() {
        let server = MockDistributionServer::new();
        let (tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        let (test_repo, version) = create_fake_rust_repo(&tmp_dir);

        let repo_url = format!("file://{}", test_repo.display());

        run_and_assert_events(
            &mut rzup,
            |rzup| {
                rzup.build_rust_toolchain(&repo_url, &Some("master".to_string()), &None)
                    .unwrap();
            },
            vec![
                RzupEvent::BuildingRustToolchain,
                RzupEvent::BuildingRustToolchainUpdate {
                    message: "cloning git repository".into(),
                },
                RzupEvent::BuildingRustToolchainUpdate {
                    message: "./x build".into(),
                },
                RzupEvent::BuildingRustToolchainUpdate {
                    message: "build output line 1".into(),
                },
                RzupEvent::BuildingRustToolchainUpdate {
                    message: "build output line 2".into(),
                },
                RzupEvent::BuildingRustToolchainUpdate {
                    message: "./x build --stage 2".into(),
                },
                RzupEvent::BuildingRustToolchainUpdate {
                    message: "build output line 1".into(),
                },
                RzupEvent::BuildingRustToolchainUpdate {
                    message: "build output line 2".into(),
                },
                RzupEvent::BuildingRustToolchainUpdate {
                    message: "installing".into(),
                },
                RzupEvent::DoneBuildingRustToolchain {
                    version: version.to_string(),
                },
            ],
        );

        assert_eq!(
            rzup.get_default_version(&Component::RustToolchain)
                .unwrap()
                .unwrap()
                .0,
            version
        );

        std::fs::remove_dir_all(tmp_dir.path().join(".risc0/tmp")).unwrap();
        assert_files(
            tmp_dir.path(),
            vec![
                format!(".risc0/toolchains/v{version}-rust-x86_64-unknown-linux-gnu/bin/bar-fmt"),
                format!(".risc0/toolchains/v{version}-rust-x86_64-unknown-linux-gnu/bin/cargo-fmt"),
                format!(".risc0/toolchains/v{version}-rust-x86_64-unknown-linux-gnu/bin/rustc"),
            ],
        );
    }

    #[test]
    fn build_rust_toolchain_twice_different_versions() {
        let server = MockDistributionServer::new();
        let (tmp_dir, mut rzup) = setup_test_env(
            server.base_urls.clone(),
            None,
            Platform::new("x86_64", Os::Linux),
        );

        let (test_repo, master) = create_fake_rust_repo(&tmp_dir);

        let repo_url = format!("file://{}", test_repo.display());
        rzup.build_rust_toolchain(&repo_url, &Some("foo".to_string()), &None)
            .unwrap();

        let foo_commit = build::git_short_rev_parse(&test_repo, "foo").unwrap();
        let mut foo = master.clone();
        foo.build = semver::BuildMetadata::new(&foo_commit).unwrap();

        rzup.build_rust_toolchain(&repo_url, &Some("master".to_string()), &None)
            .unwrap();

        std::fs::remove_dir_all(tmp_dir.path().join(".risc0/tmp")).unwrap();
        assert_files(
            tmp_dir.path(),
            vec![
                format!(".risc0/toolchains/v{master}-rust-x86_64-unknown-linux-gnu/bin/bar-fmt"),
                format!(".risc0/toolchains/v{master}-rust-x86_64-unknown-linux-gnu/bin/cargo-fmt"),
                format!(".risc0/toolchains/v{master}-rust-x86_64-unknown-linux-gnu/bin/rustc"),
                format!(".risc0/toolchains/v{foo}-rust-x86_64-unknown-linux-gnu/bin/cargo-fmt"),
                format!(".risc0/toolchains/v{foo}-rust-x86_64-unknown-linux-gnu/bin/rustc"),
            ],
        );
    }
}
