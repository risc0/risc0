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
use crate::distribution::{
    signature::{PrivateKey, PublicKey},
    Platform,
};
use crate::error::Result;
use crate::{AwsCredentials, RzupError, RzupEvent};

use std::fs;
use std::path::{Path, PathBuf};

fn home_dir() -> Option<PathBuf> {
    std::env::var_os("HOME")
        .and_then(|h| if h.is_empty() { None } else { Some(h) })
        .map(PathBuf::from)
}

type VarResult<T> = std::result::Result<T, std::env::VarError>;

pub struct Environment {
    risc0_dir: PathBuf,
    tmp_dir: PathBuf,
    cargo_bin_dir: PathBuf,
    rustup_toolchain_dir: PathBuf,
    settings_file: PathBuf,
    event_handler: Option<Box<dyn Fn(RzupEvent) + Send + Sync>>,
    platform: Platform,
    github_token: Option<String>,
    aws_creds_factory: Box<dyn Fn() -> Option<AwsCredentials> + Send + Sync>,
    private_key_getter: Box<dyn Fn() -> Result<PrivateKey> + Send + Sync>,
    public_key: PublicKey,
}

fn get_github_token_from_hosts_yml(home_dir: &Path) -> Result<String> {
    let host_yml_path = home_dir.join(".config/gh/hosts.yml");
    let yaml_docs =
        yaml_rust2::YamlLoader::load_from_str(&std::fs::read_to_string(&host_yml_path)?)
            .map_err(|e| RzupError::Other(e.to_string()))?;
    if yaml_docs.len() != 1 {
        return Err(RzupError::Other("unexpected YAML".into()));
    }
    let hosts = &yaml_docs[0];
    hosts["github.com"]["oauth_token"]
        .as_str()
        .map(|s| s.to_owned())
        .ok_or_else(|| RzupError::Other("unexpected YAML".into()))
}

#[cfg(test)]
const TEST_HOSTS_YML: &str = "
github.com:
    oauth_token: mysecret
    user: foo
    git_protocol: https

example.com:
    oauth_token: othersecret
    user: bar
    other_key: baz
";

#[test]
fn get_github_token_from_hosts_yml_test() {
    let tmp_dir = tempfile::tempdir().unwrap();

    // file missing
    get_github_token_from_hosts_yml(tmp_dir.path()).unwrap_err();

    let hosts_yml_path = tmp_dir.path().join(".config/gh/hosts.yml");
    std::fs::create_dir_all(hosts_yml_path.parent().unwrap()).unwrap();

    // file has garbage
    std::fs::write(&hosts_yml_path, "garbage").unwrap();
    get_github_token_from_hosts_yml(tmp_dir.path()).unwrap_err();

    // file has unexpected YAML
    std::fs::write(&hosts_yml_path, "other:\n    foo: bar").unwrap();
    get_github_token_from_hosts_yml(tmp_dir.path()).unwrap_err();

    // file has different unexpected YAML
    std::fs::write(&hosts_yml_path, "github.com:\n    foo: bar").unwrap();
    get_github_token_from_hosts_yml(tmp_dir.path()).unwrap_err();

    // success
    std::fs::write(&hosts_yml_path, TEST_HOSTS_YML).unwrap();
    let token = get_github_token_from_hosts_yml(tmp_dir.path()).unwrap();
    assert_eq!(token, "mysecret");
}

#[cfg(feature = "publish")]
#[tokio::main]
async fn get_aws_creds() -> Result<AwsCredentials> {
    use aws_credential_types::provider::ProvideCredentials as _;

    let config = aws_config::load_from_env().await;
    config
        .credentials_provider()
        .ok_or_else(|| RzupError::Other("no AWS credentials provider".into()))?
        .provide_credentials()
        .await
        .map_err(|err| RzupError::Other(format!("failed to get AWS credentials: {err}")))
}

#[cfg(not(feature = "publish"))]
fn get_aws_creds() -> Result<AwsCredentials> {
    Err(RzupError::Other("publish feature not enabled".into()))
}

#[cfg(feature = "publish")]
const RZUP_PUBLISH_SECRET_ID: &str = "rzup-publish-key";

#[cfg(feature = "publish")]
#[tokio::main]
async fn get_private_key() -> Result<PrivateKey> {
    let config = aws_config::load_from_env().await;
    let client = aws_sdk_secretsmanager::Client::new(&config);
    let secret = client
        .get_secret_value()
        .secret_id(RZUP_PUBLISH_SECRET_ID)
        .send()
        .await
        .map_err(|e| RzupError::Other(format!("failed to get private key: {e}")))?;
    let key_pem = secret
        .secret_string
        .ok_or_else(|| RzupError::Other("missing secret_string".into()))?;
    PrivateKey::new(&key_pem)
}

#[cfg(not(feature = "publish"))]
fn get_private_key() -> Result<PrivateKey> {
    Err(RzupError::Other("publish feature not enabled".into()))
}

impl Environment {
    fn ensure_directories(&self) -> Result<()> {
        if !self.risc0_dir.exists() {
            fs::create_dir_all(&self.risc0_dir)?;
        }

        // This sentinel file is used by older version of the `risc0-build` crate, and without it
        // it will error.
        let rzup_sentinel = self.risc0_dir.join(".rzup");
        if !rzup_sentinel.exists() {
            std::fs::write(rzup_sentinel, "")?;
        }

        if !self.tmp_dir.exists() {
            fs::create_dir_all(&self.tmp_dir)?;
        }

        Ok(())
    }

    #[allow(clippy::too_many_arguments)]
    pub fn with_paths_creds_platform_and_event_handler(
        risc0_dir: impl Into<PathBuf>,
        rustup_dir: impl AsRef<Path>,
        cargo_dir: impl AsRef<Path>,
        github_token: Option<String>,
        aws_creds_factory: impl Fn() -> Option<AwsCredentials> + Send + Sync + 'static,
        private_key_getter: impl Fn() -> Result<PrivateKey> + Send + Sync + 'static,
        public_key: PublicKey,
        platform: Platform,
        event_handler: impl Fn(RzupEvent) + Send + Sync + 'static,
    ) -> Result<Self> {
        let risc0_dir = risc0_dir.into();
        let tmp_dir = risc0_dir.join("tmp");
        let cargo_bin_dir = cargo_dir.as_ref().join("bin");
        let rustup_toolchain_dir = rustup_dir.as_ref().join("toolchains");
        let settings_file = risc0_dir.join("settings.toml");

        let mut env = Self {
            risc0_dir,
            tmp_dir,
            cargo_bin_dir,
            rustup_toolchain_dir,
            settings_file,
            event_handler: None,
            platform,
            github_token,
            aws_creds_factory: Box::new(aws_creds_factory),
            private_key_getter: Box::new(private_key_getter),
            public_key,
        };
        env.set_event_handler(event_handler);

        env.ensure_directories()?;
        Ok(env)
    }

    pub fn new(
        mut env_accessor: impl FnMut(&str) -> VarResult<String>,
        event_handler: impl Fn(RzupEvent) + Send + Sync + 'static,
    ) -> Result<Self> {
        let platform = Platform::detect()?;

        let home_dir = home_dir().ok_or_else(|| {
            RzupError::Environment("Could not determine home directory".to_string())
        })?;

        let risc0_dir = env_accessor("RISC0_HOME")
            .map(PathBuf::from)
            .unwrap_or_else(|_| home_dir.join(".risc0"));

        let rustup_dir = env_accessor("RUSTUP_HOME")
            .map(PathBuf::from)
            .unwrap_or_else(|_| home_dir.join(".rustup"));

        let cargo_dir = env_accessor("CARGO_HOME")
            .map(PathBuf::from)
            .unwrap_or_else(|_| home_dir.join(".cargo"));

        let github_token = env_accessor("GITHUB_TOKEN")
            .or_else(|_| get_github_token_from_hosts_yml(&home_dir))
            .ok();

        let aws_creds_factory = || get_aws_creds().ok();
        let private_key_getter = || get_private_key();
        let public_key = PublicKey::official();

        let env = Self::with_paths_creds_platform_and_event_handler(
            risc0_dir,
            rustup_dir,
            cargo_dir,
            github_token,
            aws_creds_factory,
            private_key_getter,
            public_key,
            platform,
            event_handler,
        )?;
        env.emit(RzupEvent::Debug {
            message: format!("Initialized environment at {}", env.risc0_dir().display()),
        });
        Ok(env)
    }

    pub fn set_event_handler(&mut self, event_handler: impl Fn(RzupEvent) + Send + Sync + 'static) {
        self.event_handler = Some(Box::new(event_handler));
    }

    pub fn emit(&self, event: RzupEvent) {
        if let Some(handler) = &self.event_handler {
            handler(event);
        }
    }

    pub fn risc0_dir(&self) -> &Path {
        &self.risc0_dir
    }

    pub fn cargo_bin_dir(&self) -> &Path {
        &self.cargo_bin_dir
    }

    pub fn rustup_toolchain_dir(&self) -> &Path {
        &self.rustup_toolchain_dir
    }

    pub fn settings_path(&self) -> &Path {
        &self.settings_file
    }

    pub fn tmp_dir(&self) -> &Path {
        &self.tmp_dir
    }

    pub fn platform(&self) -> &Platform {
        &self.platform
    }

    pub fn github_token(&self) -> &Option<String> {
        &self.github_token
    }

    pub fn get_aws_creds(&self) -> Option<AwsCredentials> {
        (self.aws_creds_factory)()
    }

    pub fn get_private_key(&self) -> Result<PrivateKey> {
        (self.private_key_getter)()
    }

    pub fn public_key(&self) -> &PublicKey {
        &self.public_key
    }

    #[cfg(feature = "install")]
    pub fn flock(&self, name: &str) -> Result<LockFile> {
        use fs2::FileExt as _;

        let lock_path = self.tmp_dir().join(format!("{name}.lock"));

        let lock_file = std::fs::OpenOptions::new()
            .write(true)
            .create(true)
            .truncate(true)
            .open(&lock_path)?;

        lock_file.lock_exclusive()?;

        Ok(LockFile { _file: lock_file })
    }

    #[cfg(not(feature = "install"))]
    pub fn flock(&self, _name: &str) -> Result<LockFile> {
        Err(RzupError::Other("not built with install support".into()))
    }
}

pub struct LockFile {
    _file: std::fs::File,
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::distribution::{signature::PublicKey, Os};

    fn no_env(_: &str) -> VarResult<String> {
        Err(std::env::VarError::NotPresent)
    }

    #[test]
    fn test_default_env() {
        let env = Environment::new(no_env, |_| {}).unwrap();
        let home_dir = home_dir().unwrap();
        let expected_risc0_dir = home_dir.join(".risc0");
        let expected_cargo_bin_dir = home_dir.join(".cargo/bin");
        let expected_rustup_toolchain_dir = home_dir.join(".rustup/toolchains");

        assert_eq!(env.risc0_dir, expected_risc0_dir);
        assert!(env.risc0_dir.join(".rzup").is_file());
        assert_eq!(env.cargo_bin_dir, expected_cargo_bin_dir);
        assert_eq!(env.rustup_toolchain_dir, expected_rustup_toolchain_dir);
        assert_eq!(env.tmp_dir, expected_risc0_dir.join("tmp"));
        assert_eq!(env.settings_file, expected_risc0_dir.join("settings.toml"));
    }

    #[test]
    fn test_custom_root() {
        let tmp_dir = tempfile::tempdir().unwrap();
        let env = Environment::with_paths_creds_platform_and_event_handler(
            tmp_dir.path().join(".risc0"),
            tmp_dir.path().join(".rustup"),
            tmp_dir.path().join(".cargo"),
            Some("foo".into()),
            || None,
            || Err(RzupError::Other("no private key".into())),
            PublicKey::official(),
            Platform::new("x86_64", Os::Linux),
            |_| {},
        )
        .unwrap();

        assert_eq!(env.risc0_dir, tmp_dir.path().join(".risc0"));
        assert_eq!(env.cargo_bin_dir, tmp_dir.path().join(".cargo/bin"));
        assert_eq!(
            env.rustup_toolchain_dir,
            tmp_dir.path().join(".rustup/toolchains")
        );
        assert_eq!(env.tmp_dir, tmp_dir.path().join(".risc0/tmp"));
        assert_eq!(
            env.settings_file,
            tmp_dir.path().join(".risc0/settings.toml")
        );
        assert_eq!(env.github_token, Some("foo".into()));
    }

    #[test]
    fn test_environment_with_environment_variables_provided() {
        let tmp_dir = tempfile::tempdir().unwrap();
        let risc0_dir = tmp_dir.path().join("my-risc0");
        let rustup_dir = tmp_dir.path().join("my-rustup");
        let cargo_dir = tmp_dir.path().join("my-cargo");

        let env = Environment::new(
            |key| match key {
                "RISC0_HOME" => Ok(risc0_dir.to_string_lossy().into()),
                "RUSTUP_HOME" => Ok(rustup_dir.to_string_lossy().into()),
                "CARGO_HOME" => Ok(cargo_dir.to_string_lossy().into()),
                "GITHUB_TOKEN" => Ok("foobar".into()),
                other => panic!("unexpected read of {other:?} environment variable"),
            },
            |_| {},
        )
        .unwrap();
        assert_eq!(env.risc0_dir, risc0_dir);
        assert_eq!(env.rustup_toolchain_dir, rustup_dir.join("toolchains"));
        assert_eq!(env.cargo_bin_dir, cargo_dir.join("bin"));
        assert_eq!(env.github_token, Some("foobar".into()));
    }
}
