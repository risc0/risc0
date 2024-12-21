use crate::components::Component;
// use crate::env::Environment;
// use crate::error::Result;
// use std::fs;
// use std::path::Path;

#[derive(Debug)]
pub(crate) struct CargoRiscZero;

// impl CargoRiscZero {
//     fn download_and_install(&self, version_dir: &Path, version: &str) -> Result<()> {
//         // TODO: Replace this placeholder with actual download logic
//         let bin_dir = version_dir.join("bin");
//         let cargo_risczero_binary_path = bin_dir.join("cargo-risczero");
//         let r0vm_binary_path = bin_dir.join("r0vm");
//
//         fs::write(
//             &cargo_risczero_binary_path,
//             format!("#!/bin/sh\necho \"cargo-risczero version {}\"", version),
//         )?;
//
//         fs::write(
//             &r0vm_binary_path,
//             format!("#!/bin/sh\necho \"cargo-risczero version {}\"", version),
//         )?;
//
//         #[cfg(unix)]
//         {
//             use std::os::unix::fs::PermissionsExt;
//             let mut cargo_risczero_perms = fs::metadata(&cargo_risczero_binary_path)?.permissions();
//             cargo_risczero_perms.set_mode(0o755);
//             fs::set_permissions(&cargo_risczero_binary_path, cargo_risczero_perms)?;
//
//             let mut r0vm_perms = fs::metadata(&r0vm_binary_path)?.permissions();
//             r0vm_perms.set_mode(0o755);
//             fs::set_permissions(&r0vm_binary_path, r0vm_perms)?;
//         }
//
//         Ok(())
//     }
// }

impl Component for CargoRiscZero {
    fn id(&self) -> &'static str {
        "cargo-risczero"
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::env::Environment;

    #[test]
    fn test_cargo_risczero_install() {
        let tmp_dir = tempfile::tempdir().unwrap();
        let env = Environment::with_root(tmp_dir.path()).unwrap();
        let component = CargoRiscZero;

        // Test installation
        component
            .install(&env, Some("0.1.0".to_string()), true)
            .unwrap();

        // Verify installation
        let version_dir = env
            .root_dir()
            .join("cargo-risczero")
            .join("v0.1.0-cargo-risczero");
        assert!(version_dir.exists());
        assert!(version_dir.join("bin").join("cargo-risczero").exists());

        // Clean up
        component._uninstall(&env).unwrap();
    }

    #[test]
    fn test_cargo_risczero_component_path() {
        let tmp_dir = tempfile::tempdir().unwrap();
        let env = Environment::with_root(tmp_dir.path()).unwrap();
        let component = CargoRiscZero;
        let path = component.get_path(&env).unwrap();

        let expected_path = env.root_dir().join("cargo-risczero");
        assert_eq!(path, expected_path);
    }
}
