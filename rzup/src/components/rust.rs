use crate::components::Component;

#[derive(Debug)]
pub(crate) struct RustToolchain;

impl Component for RustToolchain {
    fn id(&self) -> &'static str {
        "rust"
    }
}

#[cfg(test)]
mod tests {
    use semver::Version;

    use super::*;
    use crate::env::Environment;

    #[test]
    fn test_rust_toolchain_install() {
        let tmp_dir = tempfile::tempdir().unwrap();
        let env = Environment::with_root(tmp_dir.path()).unwrap();
        let component = RustToolchain;

        let version = Version::new(1, 81, 0);

        // Test installation
        component.install(&env, Some(&version), true).unwrap();

        // Clean up
        component.uninstall(&env, &version).unwrap();
    }
}
