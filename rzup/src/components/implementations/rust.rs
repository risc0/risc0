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
    use super::*;
    use crate::env::Environment;

    #[test]
    fn test_rust_toolchain_install() {
        let tmp_dir = tempfile::tempdir().unwrap();
        let env = Environment::with_root(tmp_dir.path()).unwrap();
        let component = RustToolchain;

        // Test installation
        component
            .install(&env, Some("1.79.0".to_string()), true)
            .unwrap();

        // Clean up
        component._uninstall(&env).unwrap();
    }
}
