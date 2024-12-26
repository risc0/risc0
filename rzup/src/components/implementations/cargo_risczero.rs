use crate::components::Component;

#[derive(Debug)]
pub(crate) struct CargoRiscZero;

impl Component for CargoRiscZero {
    fn id(&self) -> &'static str {
        "cargo-risczero"
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::env::Environment;
    use semver::Version;

    #[test]
    fn test_cargo_risczero_install() {
        let tmp_dir = tempfile::tempdir().unwrap();
        let env = Environment::with_root(tmp_dir.path()).unwrap();
        let component = CargoRiscZero;

        let version = Version::new(1, 0, 0);

        // Test installation
        component.install(&env, Some(&version), true).unwrap();

        // Clean up
        component.uninstall(&env, &version).unwrap();
    }
}
