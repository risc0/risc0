// Copyright 2024 RISC Zero, Inc.
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

use crate::{
    errors::RzupError,
    info_msg,
    repo::GithubReleaseInfo,
    utils::{
        command::CommandExt, ensure_binary, flock, http_client, rzup_home, target::Target,
        CPP_TOOLCHAIN_NAME, RUSTUP_TOOLCHAIN_NAME,
    },
    verbose_msg,
};
use anyhow::{bail, Context, Result};
use flate2::bufread::GzDecoder;
use std::{
    fs,
    io::{BufReader, Write},
    os::unix::fs::PermissionsExt,
    path::{Path, PathBuf},
    process::Command,
    str::FromStr,
};
use tar::Archive;
use tempfile::tempdir;
use xz::bufread::XzDecoder;

const CONFIG_TOML: &str = include_str!("config.toml");

struct BuildOutput {
    toolchain_dir: PathBuf,
}

#[derive(Debug, Clone, Copy, Default)]
pub enum Toolchain {
    #[default]
    Rust,
    Cpp,
}

impl FromStr for Toolchain {
    type Err = RzupError;

    fn from_str(input: &str) -> Result<Toolchain, Self::Err> {
        match input.to_lowercase().as_str() {
            "rust" => Ok(Toolchain::Rust),
            "cpp" => Ok(Toolchain::Cpp),
            _ => Err(RzupError::InvalidToolchain),
        }
    }
}

impl Toolchain {
    pub fn to_str(self) -> &'static str {
        match self {
            Toolchain::Rust => "rust",
            Toolchain::Cpp => "cpp",
        }
    }

    fn git_url(&self) -> &'static str {
        match self {
            Self::Rust => "https://github.com/risc0/rust.git",
            Self::Cpp => "https://github.com/risc0/toolchain.git",
        }
    }

    fn api_url(&self, tag: Option<&str>) -> String {
        let base_url = match self {
            Self::Rust => "https://api.github.com/repos/risc0/rust/releases",
            Self::Cpp => "https://api.github.com/repos/risc0/toolchain/releases",
        };
        match tag {
            Some(tag) => format!("{}/tags/{}", base_url, tag),
            None => format!("{}/latest", base_url),
        }
    }

    pub async fn release_info(&self, tag: Option<&str>) -> Result<GithubReleaseInfo> {
        let client = http_client()?;

        let url = self.api_url(tag);

        verbose_msg!(format!("Getting toolchain release info from {}", &url));

        let res = client.get(&url).send().await?;

        if res.status() == 403 {
            return Err(RzupError::Other(
                "Rate limited by GitHub API. Please set a GitHub token in the GITHUB_TOKEN environment variable."
                    .into(),
            ).into());
        }

        let release_info: GithubReleaseInfo = res.json().await?;

        Ok(release_info)
    }

    async fn download(
        &self,
        target: Target,
        tag: Option<&str>,
        toolchain_root_dir: &Path,
        force: bool,
    ) -> Result<PathBuf> {
        let client = http_client()?;

        let temp_dir = tempdir()?;

        let temp_file_path = match self {
            Toolchain::Rust => temp_dir.path().join("tmp_r0_rust_toolchain.tar.gz"),
            Toolchain::Cpp => temp_dir.path().join("tmp_r0_cpp_toolchain.tar.xz"),
        };

        verbose_msg!(format!(
            "Created temp toolchain filepath at {}",
            temp_file_path.display()
        ));

        let release_info = self.release_info(tag).await?;
        let Some(asset) = release_info.assets.get(&target) else {
            return Err(
                RzupError::Other(format!("No asset found for target: {:?}", target)).into(),
            );
        };

        let toolchain_dir = toolchain_root_dir.join(format!(
            "{}-risc0-{}-{}",
            release_info.tag_name,
            self.to_str(),
            target.to_str(),
        ));

        // Remove directory if it exists and force is set
        if toolchain_dir.is_dir() && force {
            info_msg!(format!(
                "Toolchain path {} already exists - deleting existing files!",
                toolchain_dir.display()
            ));

            verbose_msg!(format!(
                "Removing toolchain directory at {}",
                toolchain_dir.display()
            ));

            fs::remove_dir_all(&toolchain_dir)?;
        }

        // Skip download if directory already exists and force is not set
        if toolchain_dir.is_dir() && !force {
            info_msg!(format!(
                "Toolchain path {} already exists - skipping download.",
                toolchain_dir.display()
            ));
            return Ok(toolchain_dir);
        }

        info_msg!(format!("Downloading {} toolchain...", self.to_str()));

        verbose_msg!(format!(
            "Requesting toolchain download from {}",
            &asset.browser_download_url
        ));
        let response = client.get(&asset.browser_download_url).send().await?;
        if !response.status().is_success() {
            return Err(RzupError::Other(format!(
                "Failed to download asset: {:?}",
                response.status()
            ))
            .into());
        }

        verbose_msg!(format!(
            "Creating temporary path at {}",
            &temp_file_path.display()
        ));

        let mut file = fs::File::create(&temp_file_path)?;
        let content = response.bytes().await?;

        verbose_msg!(format!(
            "Writing contents to file {}",
            temp_file_path.display()
        ));

        file.write_all(&content)?;

        let tarball = fs::File::open(temp_file_path)?;

        info_msg!(format!("Extracting {} toolchain...", self.to_str()));

        match self {
            Toolchain::Rust => {
                let decoder = GzDecoder::new(BufReader::new(tarball));
                let mut archive = Archive::new(decoder);

                verbose_msg!(format!(
                    "Unpacking {} to {}",
                    self.to_str(),
                    &toolchain_dir.display()
                ));

                archive.unpack(&toolchain_dir)?;

                #[cfg(target_family = "unix")]
                {
                    let iter1 = std::fs::read_dir(toolchain_dir.join("bin"))?;
                    let iter2 = std::fs::read_dir(
                        toolchain_dir.join(format!("lib/rustlib/{}/bin", target.to_str())),
                    )?;

                    for res in iter1.chain(iter2) {
                        let entry = res?;
                        if entry.file_type()?.is_file() {
                            let mut perms = entry.metadata()?.permissions();
                            verbose_msg!(format!(
                                "Setting permissons for {} to 0o755",
                                entry.file_name().to_string_lossy()
                            ));
                            perms.set_mode(0o755);
                            std::fs::set_permissions(entry.path(), perms)?;
                        }
                    }
                }
            }
            Toolchain::Cpp => {
                let decoder = XzDecoder::new(BufReader::new(tarball));
                let mut archive = Archive::new(decoder);
                let tmp_dir = tempdir()?;

                verbose_msg!(format!(
                    "Unpacking {} to {}",
                    self.to_str(),
                    &toolchain_dir.display()
                ));

                archive.unpack(&tmp_dir)?;

                // NOTE: This is to move down a directory during the unpacking phase of a toolchain
                // i.e. unpacking `XYZ.tar.xz` to `dir` -> `dir/contents`, rather than `dir/XYZ/contents`
                let subdir = fs::read_dir(&tmp_dir)?
                    .filter_map(Result::ok)
                    .map(|entry| entry.path())
                    .find(|path| path.is_dir()) // Find the unpacked child dir
                    .ok_or_else(|| RzupError::Other("No subdirectory found in archive".into()))?;

                verbose_msg!(format!(
                    "Moving toolchain from {} to {}",
                    subdir.display(),
                    toolchain_dir.display()
                ));

                // Move subdir contents to toolchain dir
                self.move_toolchain(&subdir, &toolchain_dir)?;
            }
        }

        Ok(toolchain_dir)
    }

    pub fn link(&self, dir: &Path) -> Result<()> {
        match self {
            Toolchain::Rust => {
                info_msg!(format!(
                    "Activating rustup toolchain {} at {}",
                    RUSTUP_TOOLCHAIN_NAME,
                    dir.display()
                ));

                let rustc_path = dir.join("bin").join("rustc");
                if !rustc_path.is_file() {
                    bail!(
                        "Invalid toolchain directory: rustc executable not found at {}",
                        rustc_path.display()
                    );
                }

                self.unlink(RUSTUP_TOOLCHAIN_NAME)?;

                verbose_msg!(format!(
                    "Creating symlinks from {} to {}",
                    dir.display(),
                    RUSTUP_TOOLCHAIN_NAME
                ));

                Command::new("rustup")
                    .args(["toolchain", "link", RUSTUP_TOOLCHAIN_NAME])
                    .arg(dir)
                    .run_verbose()
                    .context("Could not link toolchain: rustup not installed?")?;

                info_msg!(format!(
                    "rustup toolchain {RUSTUP_TOOLCHAIN_NAME} was linked successfully"
                ));

                Ok(())
            }
            Toolchain::Cpp => {
                let rzup_home = rzup_home()?;
                let cpp_link = rzup_home.join(CPP_TOOLCHAIN_NAME);

                if let Ok(meta) = fs::symlink_metadata(&cpp_link) {
                    verbose_msg!(format!("Removing cpp link: {}", cpp_link.display()));
                    if meta.is_dir() {
                        fs::remove_dir_all(&cpp_link)
                            .context("Failed to remove existing cpp link (directory)")?;
                    } else {
                        fs::remove_file(&cpp_link).context("Failed to remove existing cpp link")?;
                    }
                }

                verbose_msg!(format!(
                    "Creating symlink for toolchain at {}",
                    cpp_link.display()
                ));

                std::os::unix::fs::symlink(dir, &cpp_link)
                    .context("Failed to create symlink for cpp")?;

                info_msg!(format!(
                    "Symlink for cpp toolchain created at {}",
                    cpp_link.display()
                ));
                Ok(())
            }
        }
    }

    pub fn unlink(&self, name: &str) -> Result<()> {
        match self {
            Toolchain::Rust => {
                if self.toolchain_link_exists(name)? {
                    verbose_msg!(format!("Removing toolchain link {}", &name));
                    Command::new("rustup")
                        .args(["toolchain", "remove", name])
                        .run()
                        .context("Could not remove existing toolchain")?;
                }
            }
            Toolchain::Cpp => {
                let rzup_home = rzup_home()?;
                let cpp_link = rzup_home.join(name);

                if self.toolchain_link_exists(name)? {
                    verbose_msg!(format!("Removing symlink at {}", cpp_link.display()));
                    fs::remove_file(&cpp_link).context("Failed to remove existing cpp symlink")?;
                }
            }
        }
        Ok(())
    }

    pub async fn install(&self, tag: Option<&str>, force: bool) -> Result<()> {
        let target = Target::host_target()
            .ok_or_else(|| RzupError::Other("Failed to determine the host target".to_string()))?;
        let root_dir = rzup_home()?;
        let lockfile_path = root_dir.join("lock");
        let _lock = flock(&lockfile_path)?;

        let toolchains_root_dir = root_dir.join("toolchains");

        match self {
            Toolchain::Rust => {
                let rust_path = self
                    .download(target, tag, &toolchains_root_dir, force)
                    .await?;
                self.link(&rust_path)?;
            }
            Toolchain::Cpp => {
                let cpp_path = self
                    .download(target, tag, &toolchains_root_dir, force)
                    .await?;
                self.link(&cpp_path)?;
            }
        }
        Ok(())
    }

    pub fn build(&self, version: Option<&str>) -> Result<()> {
        match self {
            Toolchain::Rust => {
                let source_url = self.git_url();
                let tag = version.unwrap_or("risc0");
                let root_dir = if let Ok(dir) = std::env::var("RISC0_BUILD_DIR") {
                    PathBuf::from(dir)
                } else {
                    dirs::home_dir()
                        .context("Could not determine home dir. Set RISC0_BUILD_DIR env var!")?
                        .join(".rzup")
                };
                let build_dir = root_dir.join(format!("build-{}", self.to_str()));
                let toolchains_root_dir = rzup_home()?.join("toolchains");
                let target = Target::host_target().ok_or_else(|| {
                    RzupError::Other("Failed to determine the host target".to_string())
                })?;

                // append "-local" to denote a local build. Useful for those working toolchains by building them locally.
                let toolchain_name =
                    format!("{}-risc0-{}-{}-local", tag, self.to_str(), target.to_str());
                let final_toolchain_dir = toolchains_root_dir.join(toolchain_name);

                if final_toolchain_dir.exists() {
                    fs::remove_dir_all(&final_toolchain_dir)
                        .context("Failed to remove existing toolchain directory")?;
                }

                // Ensure the build directory exists before running git commands
                fs::create_dir_all(&build_dir)?;

                self.prepare_git_repo(source_url, tag, &build_dir)?;

                let build_output = self.build_toolchain(&build_dir)?;
                self.move_toolchain(&build_output.toolchain_dir, &final_toolchain_dir)?;
                self.copy_tools(&build_output.toolchain_dir, &final_toolchain_dir)?;
                self.link(&final_toolchain_dir)?;
            }
            Toolchain::Cpp => {
                // TODO: Implement C++ toolchain build logic
                bail!("C++ toolchain build not yet supported")
            }
        }

        Ok(())
    }

    fn prepare_git_repo(&self, source: &str, tag: &str, path: &Path) -> Result<()> {
        eprintln!("Preparing git repo {source} with tag/branch {tag}");
        ensure_binary("git", &["--version"])?;

        if !path.join(".git").is_dir() {
            Command::new("git")
                .args(["clone", source, "."])
                .current_dir(path)
                .run_verbose()?;
        } else {
            Command::new("git")
                .args(["fetch", "--all", "--prune"])
                .current_dir(path)
                .run_verbose()?;
        }

        Command::new("git")
            .args(["checkout", tag])
            .current_dir(path)
            .run_verbose()?;

        Command::new("git")
            .args(["reset", "--hard"])
            .current_dir(path)
            .run_verbose()?;

        Command::new("git")
            .args(["submodule", "update", "--init", "--recursive", "--progress"])
            .current_dir(path)
            .run_verbose()?;

        eprintln!("Git repo ready at {}", path.display());

        Ok(())
    }

    fn build_toolchain(&self, build_dir: &Path) -> Result<BuildOutput> {
        match self {
            Toolchain::Rust => {
                std::fs::write(build_dir.join("config.toml"), CONFIG_TOML)?;

                let has_python3 = Command::new("python3").arg("--version").run().is_ok();
                let python_cmd = if has_python3 { "python3" } else { "python" };

                Command::new(python_cmd)
                    .env(
                        "CARGO_TARGET_RISCV32IM_RISC0_ZKVM_ELF_RUSTFLAGS",
                        "-Cpasses=loweratomic",
                    )
                    .current_dir(build_dir)
                    .args(["x.py", "build"])
                    .run_verbose()?;

                Command::new(python_cmd)
                    .env(
                        "CARGO_TARGET_RISCV32IM_RISC0_ZKVM_ELF_RUSTFLAGS",
                        "-Cpasses=loweratomic",
                    )
                    .args(["x.py", "build", "--stage", "2"])
                    .current_dir(build_dir)
                    .run_verbose()?;

                eprintln!("Rust build complete!");

                for result in std::fs::read_dir(build_dir.join("build"))? {
                    let entry = result?;
                    let build_dir = entry.path().join("stage2");
                    if build_dir.is_dir() {
                        return Ok(BuildOutput {
                            toolchain_dir: build_dir,
                        });
                    }
                }

                bail!("Could not find build directory")
            }
            Toolchain::Cpp => {
                // TODO: Implement C++ toolchain build logic
                bail!("C++ toolchain build not yet supported")
            }
        }
    }

    fn move_toolchain(&self, src: &Path, dst: &Path) -> Result<()> {
        fs::create_dir_all(dst)?;
        for entry in fs::read_dir(src)? {
            let entry = entry?;
            let entry_path = entry.path();
            let file_name = entry.file_name();
            fs::rename(entry_path, dst.join(file_name))?;
        }
        Ok(())
    }

    fn copy_tools(&self, toolchain_dir: &Path, toolchain_dest: &Path) -> Result<()> {
        let tools_bin_dir = toolchain_dir.parent().unwrap().join("stage2-tools-bin");
        let target_bin_dir = toolchain_dest.join("bin");

        for tool in tools_bin_dir.read_dir()? {
            let tool = tool?;
            let tool_name = tool.file_name();
            eprintln!("copy tool: {tool_name:?}");
            fs::copy(&tool.path(), target_bin_dir.join(tool_name))?;
        }

        Ok(())
    }

    fn toolchain_link_exists(&self, name: &str) -> Result<bool> {
        match self {
            Toolchain::Rust => {
                let output = Command::new("rustup")
                    .args(["toolchain", "list"])
                    .output()
                    .context("Failed to list rustup toolchains")?;

                let toolchains = String::from_utf8(output.stdout)
                    .context("Failed to parse rustup toolchains list")?;

                Ok(toolchains.lines().any(|line| line.contains(name)))
            }
            Toolchain::Cpp => {
                let rzup_home = rzup_home()?;
                let cpp_link = rzup_home.join(name);
                Ok(fs::symlink_metadata(cpp_link).is_ok())
            }
        }
    }
}
