use std::fmt::Display;

use anyhow::Result;

use super::Combine;
use super::Profile;
use super::ProfileSettings;
use super::RiscZeroRepo;

mod utils;
mod batch;
mod profiles;

pub fn get_profiles(path: impl AsRef<str> + Display) -> Result<Vec<Profile>> {
    // Read the whole configuration file
    let content = utils::read_profile(path)?;

    todo!()
    // Parse batch configurations
    // let batch_profiles = batch::parse(&content)?;

    // Parse individual crate configurations
    // let individual_profiles = profiles::parse(&content)?;

    // Combine the two, overwriting batch profiles with individual profiles if
    // crates are defined in both
    // let profiles = utils::combine_profiles(batch_profiles, individual_profiles)?;

    // Ok(profiles)
}

// fn parse_profile(content: impl AsRef<str> + Display) -> Result<Profile> {
//     let profile = toml::from_str::<Profile>(content.as_ref())
//         .with_context(|| format!("Failed to parse toml with content:\n{content}",))?;
//     profile.validate().context("Invalid Profile file")?;
//     Ok(profile)
// }

#[cfg(test)]
mod tests {
    use super::*;
    use rstest::*;
    use semver::Version;

    //     const EXAMPLE_TOML_PATH: &str = "./profiles/example.toml";
    //     const EXAMPLE_TOML_STR: &str = r#"name = "example"
    //     versions = ["0.1.0"]
    //     std = true
    //     fast_mode = true
    //     risc0_gh_branch = "main"
    //     custom_main = "assert_eq!(42, 42);"
    //     import_str = "use example::EXAMPLE;"
    //     should_fail = false
    //     inject_cc_flags = true
    //     patch = '''
    // [patch.crates-io]
    // example = { git = '<git-url>', rev = '<git-rev>' }'''"#;

    // #[fixture]
    // fn profile() -> Profile {
    //     Profile {
    //         name: "example".to_string(),
    //         versions: vec![semver::Version::new(0, 1, 0)],
    //         std: true,
    //         fast_mode: true,
    //         risc_zero_repository: RiscZeroRepo::Github("main".to_string()),
    //         custom_main: Some("assert_eq!(42, 42);".to_string()),
    //         import_str: Some("use example::EXAMPLE;".to_string()),
    //         should_fail: false,
    //         run_prover: false,
    //         inject_cc_flags: true,
    //         patch: Some(
    //             "\
    //             [patch.crates-io]\n\
    //             example = { git = '<git-url>', rev = '<git-rev>' }"
    //                 .to_string(),
    //         ),
    //     }
    // }

    // #[test]
    // fn can_read_toml_file() {
    //     let content = read_profile(EXAMPLE_TOML_PATH).unwrap();
    //     assert!(!content.is_empty());
    // }

    // #[rstest]
    // fn successfully_parse_toml(profile: Profile) {
    //     let parsed = parse_profile(EXAMPLE_TOML_STR).unwrap();
    //     assert_eq!(parsed, profile);
    //     assert!(parsed.validate().is_ok());
    // }

    // #[test]
    // fn profile_accept_multiple_versions() {
    //     let content = r#"name = 'example'
    //     versions = ["0.1.0", "0.2.0"]
    //     risc0_gh_branch = 'main'"#;
    //     let parsed = parse_profile(content).unwrap();
    //     assert_eq!(parsed.versions.len(), 2);
    //     assert_eq!(parsed.versions[0], semver::Version::new(0, 1, 0));
    //     assert_eq!(parsed.versions[1], semver::Version::new(0, 2, 0));
    // }

    // #[rstest]
    // #[case::missing_name_field(None)]
    // #[case::empty_name_field(Some(""))]
    // #[should_panic]
    // fn profile_requires_name(#[case] name: Option<&str>) {
    //     let mut content = String::new();
    //     content.push_str("versions = [\"0.1.0\"]\n");
    //     content.push_str("risc0_gh_branch = 'main'\n");
    //     if let Some(n) = name {
    //         content.push_str(&format!("name = '{}'\n", n));
    //     }
    //     parse_profile(content).unwrap();
    // }

    // #[rstest]
    // #[case::missing_versions_field(None)]
    // #[case::empty_versions_string_field(Some(""))]
    // #[case::empty_versions_array(Some("[]"))]
    // #[should_panic]
    // fn profile_requires_at_least_one_version(
    //     #[case] versions: Option<&str>,
    // ) {
    //     let mut content = String::new();
    //     content.push_str("name = 'example'\n");
    //     content.push_str("risc0_gh_branch = 'main'\n");
    //     if let Some(v) = versions {
    //         content.push_str(&format!("versions = {v}\n"));
    //     }
    //     parse_profile(content).unwrap();
    // }

    #[test]
    fn can_parse_yaml() {
        get_profiles("profiles/profiles.yaml").unwrap();
    }

    #[rstest]
    #[case::single_version(vec!["0.1.0"])]
    #[case::multiple_versions(vec!["0.1.0", "0.2.0"])]
    fn batch_apply_settings(#[case] versions: Vec<&str>) {
        let versions: Vec<Version> = versions
            .iter()
            .map(|v| Version::parse(v).unwrap())
            .collect();
        let versions_str = versions
            .iter()
            .map(|v| format!("'{v}'"))
            .collect::<Vec<String>>()
            .join(", ");
        let content = format!(
            r#"
        batch:
          - name: "example"
            patch: "patch"
            import_str: "import_str"
            custom_main: "custom_main"
            std: true
            fast_mode: true
            should_fail: true
            inject_cc_flags: true
            run_prover: true
            versions: [{versions_str}]
            risc0_path: path
            crates:
              - "example1"
              - "example2"
        "#
        );
        let settings = ProfileSettings {
            versions: Some(versions),
            std: true,
            fast_mode: true,
            risc_zero_repository: RiscZeroRepo::Local("path".to_string()),
            custom_main: Some("custom_main".to_string()),
            import_str: Some("import_str".to_string()),
            run_prover: true,
            should_fail: true,
            inject_cc_flags: true,
            patch: Some("patch".to_string()),
        };

        let profiles = utils::parse_profiles(serde_yaml::from_str(&content).unwrap()).unwrap();
        assert_eq!(profiles.len(), 2);

        let crates = vec!["example1".to_string(), "example2".to_string()];
        crates
            .iter()
            .map(|c| Profile {
                name: c.clone(),
                settings: settings.clone(),
            })
            .for_each(|p| {
                assert!(profiles.contains(&p));
            });
    }
}
