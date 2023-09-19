// Copyright 2023 RISC Zero, Inc.
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

use std::fmt::Display;

use crate::CrateProfile;
use anyhow::{Context, Result};
use serde_valid::Validate;

pub fn lookup_crate(crate_name: &str, mut profile: CrateProfile) -> CrateProfile {
    profile.customized = true;
    match crate_name {
        "lazy_static" => {
            profile.std = true;
            profile.import_str = Some(
                "use lazy_static::lazy_static;\nlazy_static! {\n\tstatic ref EXAMPLE: u8 = 42;\n}"
                    .to_string(),
            );
            profile.custom_main = Some("assert_eq!(*EXAMPLE, 42);".to_string());
            profile.run_prover = true;
        }
        // Requires CFLAGS for native code
        "ring" => {
            profile.inject_cc_flags = true;
        }
        "zip" => {
            profile.std = true;
            profile.inject_cc_flags = true;
        }
        "async-channel" | "async-executor" | "async-io" | "blocking" | "concurrent-queue"
        | "crossbeam-deque" | "crossbeam-epoch" | "crossbeam-queue" | "rayon" | "rayon-core"
        | "redox_users" | "vsdb" | "vsdbsled" => {
            // NOTE: the crate 'crossbeam-utils'|'crossbeam-channel'|'crossbeam' itself
            // still fails to build because you can't crates-io patch itself
            profile.crossbeam_patch = true;
        }
        "criterion" => {
            profile.crossbeam_patch = true;
            profile.std = true;
        }
        // Just need 'std' block:
        "anyhow" | "cargo_metadata" | "clap" | "crypto-bigint" | "csv" | "env_logger"
        | "ethers-core" | "h2" | "headers" | "hex" | "hyper" | "hyper-timeout" | "k256"
        | "md-5" | "multimap" | "openssl" | "rand" | "revm" | "revm-primitives" | "serde"
        | "serde_bytes" | "serde_cbor" | "serde_json" | "serde_urlencoded" | "serde_with"
        | "serde_yaml" | "sha-1" | "sha1" | "sha2" | "sha3" | "string_cache" | "tfhe"
        | "tinytemplate" | "toml" | "tower" | "tracing" | "tracing-core" | "tracing-futures"
        | "tracing-log" | "tracing-serde" | "tracing-subscriber" | "tungstenite" => {
            profile.std = true
        }
        _ => profile.customized = false,
    }
    profile
}

#[derive(
    Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize, serde_valid::Validate,
)]
pub struct Profile {
    #[validate(min_length = 1)]
    pub name: String,
    #[validate(min_items = 1)]
    pub versions: Vec<semver::Version>,
    #[serde(default)]
    pub std: bool,
    #[serde(default = "default_true")]
    pub fast_mode: bool,
    #[serde(flatten)]
    pub risc_zero_repository: RiscZeroRepo,
    #[serde(default)]
    pub custom_main: Option<String>,
    #[serde(default)]
    pub import_str: Option<String>,
    #[serde(default)]
    pub should_fail: bool,
    #[serde(default)]
    pub inject_cc_flags: bool,
    #[serde(default)]
    pub patch: Option<String>,
}

#[derive(Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize)]
pub enum RiscZeroRepo {
    #[serde(rename = "risc0_gh_branch")]
    Github(String),
    #[serde(rename = "risc0_path")]
    Local(String),
}

pub fn parse_toml(content: impl AsRef<str> + Display) -> Result<Profile> {
    let profile = toml::from_str::<Profile>(content.as_ref())
        .with_context(|| format!("Failed to parse toml with content:\n{content}",))?;
    profile.validate().context("Invalid Profile file")?;
    Ok(profile)
}

pub fn read_toml(path: impl AsRef<str> + Display) -> Result<String> {
    std::fs::read_to_string(path.as_ref())
        .with_context(|| format!("Failed to read profile file: {path}",))
}

const fn default_true() -> bool {
    true
}

#[cfg(test)]
mod tests {
    use super::*;
    use rstest::*;
    use serde_valid::Validate;

    const EXAMPLE_TOML_PATH: &str = "./profiles/example.toml";
    const EXAMPLE_TOML_STR: &str = r#"name = "example"
    versions = ["0.1.0"]
    std = true
    fast_mode = true
    risc0_gh_branch = "main"
    custom_main = "assert_eq!(42, 42);"
    import_str = "use example::EXAMPLE;"
    should_fail = false
    inject_cc_flags = true
    patch = '''
[patch.crates-io]
example = { git = '<git-url>', rev = '<git-rev>' }'''"#;

    #[fixture]
    fn profile() -> Profile {
        Profile {
            name: "example".to_string(),
            versions: vec![semver::Version::new(0, 1, 0)],
            std: true,
            fast_mode: true,
            risc_zero_repository: RiscZeroRepo::Github("main".to_string()),
            custom_main: Some("assert_eq!(42, 42);".to_string()),
            import_str: Some("use example::EXAMPLE;".to_string()),
            should_fail: false,
            inject_cc_flags: true,
            patch: Some(
                "\
                [patch.crates-io]\n\
                example = { git = '<git-url>', rev = '<git-rev>' }"
                    .to_string(),
            ),
        }
    }

    #[test]
    fn can_read_toml_file() {
        let content = read_toml(EXAMPLE_TOML_PATH).unwrap();
        assert!(!content.is_empty());
    }

    #[rstest]
    fn successfully_parse_toml(profile: Profile) {
        let parsed = parse_toml(EXAMPLE_TOML_STR).unwrap();
        assert_eq!(parsed, profile);
        assert!(parsed.validate().is_ok());
    }

    #[test]
    fn profile_accept_multiple_versions() {
        let content = r#"name = 'example'
        versions = ["0.1.0", "0.2.0"]
        risc0_gh_branch = 'main'"#;
        let parsed = parse_toml(content).unwrap();
        assert_eq!(parsed.versions.len(), 2);
        assert_eq!(parsed.versions[0], semver::Version::new(0, 1, 0));
        assert_eq!(parsed.versions[1], semver::Version::new(0, 2, 0));
    }

    #[rstest]
    #[case::missing_name_field(None)]
    #[case::empty_name_field(Some(""))]
    #[should_panic]
    fn profile_requires_name(#[case] name: Option<&str>) {
        let mut content = String::new();
        content.push_str("versions = [\"0.1.0\"]\n");
        content.push_str("risc0_gh_branch = 'main'\n");
        if let Some(n) = name {
            content.push_str(&format!("name = '{}'\n", n));
        }
        parse_toml(content).unwrap();
    }

    #[rstest]
    #[case::missing_versions_field(None)]
    #[case::empty_versions_string_field(Some(""))]
    #[case::empty_versions_array(Some("[]"))]
    #[should_panic]
    fn profile_requires_at_least_one_version(
        #[case] versions: Option<&str>,
    ) {
        let mut content = String::new();
        content.push_str("name = 'example'\n");
        content.push_str("risc0_gh_branch = 'main'\n");
        if let Some(v) = versions {
            content.push_str(&format!("versions = {v}\n"));
        }
        parse_toml(content).unwrap();
    }
}
