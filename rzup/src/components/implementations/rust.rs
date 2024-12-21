use crate::components::Component;
// use crate::env::Environment;
// use crate::error::Result;
// use std::fs;
// use std::path::Path;

#[derive(Debug)]
pub(crate) struct RustToolchain;

// impl RustToolchain {
//     fn download_and_install(&self, version_dir: &Path, version: &str) -> Result<()> {
//         // TODO: Replace this with actual download logic
//         let bin_dir = version_dir.join("bin");
//
//         let binaries = ["rustc", "cargo", "rustup"];
//         for binary in binaries {
//             let binary_path = bin_dir.join(binary);
//             fs::write(
//                 &binary_path,
//                 format!("#!/bin/sh\necho \"{} version {}\"", binary, version),
//             )?;
//
//             #[cfg(unix)]
//             {
//                 use std::os::unix::fs::PermissionsExt;
//                 let mut perms = fs::metadata(&binary_path)?.permissions();
//                 perms.set_mode(0o755);
//                 fs::set_permissions(&binary_path, perms)?;
//             }
//         }
//
//         Ok(())
//     }
//
//     fn setup_toolchain(&self, version_dir: &Path) -> Result<()> {
//         // TODO: replace with actual dirs
//         let dirs = ["lib", "share/doc", "share/man", "include"];
//
//         for dir in dirs {
//             fs::create_dir_all(version_dir.join(dir))?;
//         }
//
//         Ok(())
//     }
// }

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
            .install(&env, Some("1.70.0".to_string()), true)
            .unwrap();

        // Verify installation
        let version_dir = env.root_dir().join("rust").join("v1.70.0-rust");
        assert!(version_dir.exists());

        // Clean up
        component._uninstall(&env).unwrap();
    }
}
