use clap::Parser;
use cli::rzup_mode::RzupSubcmd;

#[tokio::main]
async fn main() {
    let matches = cli::rzup_mode::Rzup::parse();

    let subcmd = matches.subcmd;

    match subcmd {
        Some(RzupSubcmd::Install { .. }) => todo!(),
        Some(RzupSubcmd::Show { .. }) => todo!(),
        Some(RzupSubcmd::Check { .. }) => todo!(),
        Some(RzupSubcmd::Update { .. }) => todo!(),
        Some(RzupSubcmd::Toolchain { .. }) => todo!(),
        Some(RzupSubcmd::Default { .. }) => todo!(),
        None => todo!(),
    }
}

mod cli {

    pub mod rzup_mode {
        use crate::cli::{common, help};
        use clap::{Args, Parser, Subcommand};

        #[derive(Debug, Parser)]
        #[command(
            name = "rzup",
            bin_name = "rustup[EXE]",
            version = common::version(),
            before_help = format!("rzup {}", common::version()),
            after_help = help::RZUP_HELP
        )]
        pub struct Rzup {
            /// Enable verbose output
            #[arg(short, long)]
            verbose: bool,

            #[command(subcommand)]
            pub subcmd: Option<RzupSubcmd>,
        }

        #[derive(Debug, Subcommand)]
        #[command(name = "rzup", bin_name = "rzup[EXE]")]
        pub enum RzupSubcmd {
            /// Update RISC Zero toolchains
            #[command(after_help = help::INSTALL_HELP)]
            Install {
                #[command(flatten)]
                opts: UpdateOpts,
            },

            /// Show the active and installed toolchains
            #[command(after_help = help::SHOW_HELP)]
            Show {
                /// Enable verbose output for all installed toolchains
                #[arg(short, long)]
                verbose: bool,

                #[command(subcommand)]
                subcmd: Option<ShowSubcmd>,
            },

            /// Update RISC Zero toolchains and cargo-risczero
            #[command(after_help = help::UPDATE_HELP, aliases = ["upgrade", "up"])]
            Update {
                /// Toolchain name, such as latest, tag.
                #[arg(num_args = 1..)]
                toolchain: Vec<String>, // TODO

                /// Force an update
                #[arg(long)]
                force: bool,
            },

            /// Check for updates to RISC Zero toolchains and rzup
            Check,

            /// Set the default RISC Zero toolchain
            Default,

            /// Modify or query the installed toolchains
            Toolchain,
        }

        #[derive(Debug, Subcommand)]
        pub enum ShowSubcmd {
            /// Show the active toolchain
            #[command(after_help = help::SHOW_ACTIVE_TOOLCHAIN_HELP)]
            ActiveToolchain {
                /// Enable verbose output with toolchain information
                #[arg(short, long)]
                verbose: bool,
            },

            /// Display the computed value or RZUP_HOME
            Home,
        }

        #[derive(Debug, Default, Args)]
        pub struct UpdateOpts {
            #[arg(
                required = true,
                help = help::TOOLCHAIN_ARG_HELP,
                num_args = 1..,
            )]
            pub toolchain: Vec<String>,

            /// Install cargo-risczero
            #[arg(long)]
            pub install_cargo_risczero: bool,
        }
    }

    mod common {
        pub fn version() -> &'static str {
            "0.0.0"
        }
    }

    mod help {
        pub static RZUP_HELP: &str = r"Discussion:
        This is the RZUP help
        ";
        pub static INSTALL_HELP: &str = r"Discussion:
        This is the RZUP help
        ";
        pub static SHOW_HELP: &str = r"Discussion:
        This is the RZUP help
        ";
        pub static UPDATE_HELP: &str = r"Discussion:
        This is the RZUP help
        ";
        pub static SHOW_ACTIVE_TOOLCHAIN_HELP: &str = r"Discussion:
        This is the RZUP help
        ";
        pub static TOOLCHAIN_ARG_HELP: &str = r"Discussion:
        This is the RZUP help
        ";
    }

    mod utils {
        use anyhow::{bail, Result};
        use std::path::PathBuf;

        pub fn risc0_data() -> Result<PathBuf> {
            let dir = if let Ok(dir) = std::env::var("RISC0_DATA_DIR") {
                dir.into()
            } else if let Some(home) = dirs::home_dir() {
                home.join(".rzup")
            } else {
                bail!("Could not determine rzup directory. Set RISC0_DATA_DIR env var.");
            };

            Ok(dir)
        }
    }

    #[allow(dead_code)]
    mod dist {

        use anyhow::{bail, Context, Result};
        use clap::Parser;
        use downloader::{Download, Downloader};
        use flate2::bufread::GzDecoder;
        use fs_extra::dir::CopyOptions;
        use reqwest::{header::HeaderMap, Client};
        use serde::Deserialize;
        use std::fs::File;
        use std::io::BufReader;
        use std::path::{Path, PathBuf};
        use std::process::Command;
        use tar::Archive;
        use tempfile::tempdir;
        use xz::read::XzDecoder;

        use crate::cli::utils::risc0_data;

        enum ToolchainRepo {
            Rust,
            Cpp,
        }

        impl ToolchainRepo {
            pub const fn url(&self) -> &str {
                match self {
                    Self::Rust => "https://github.com/risc0/rust.git",
                    Self::Cpp => "https://github.com/risc0/toolchain.git",
                }
            }

            pub fn asset_name(&self, target: &str) -> String {
                match self {
                    Self::Rust => format!("rust-toolchain-{target}.tar.gz"),
                    Self::Cpp => match target {
                        "aarch64-apple-darwin" => "riscv32im-osx-arm64.tar.xz".to_string(),
                        "x86_64-unknown-linux-gnu" => "riscv32im-linux-x86_64.tar.xz".to_string(),
                        _ => panic!("binaries for {target} are not available"),
                    },
                }
            }

            pub const fn language(&self) -> &str {
                match self {
                    Self::Rust => "rust",
                    Self::Cpp => "cpp",
                }
            }
        }

        #[derive(Clone, Debug)]
        pub struct CppToolchain {
            pub path: PathBuf,
        }

        impl CppToolchain {
            fn get_subdir(path: &Path) -> Result<PathBuf> {
                let sub_dir: Vec<std::result::Result<std::fs::DirEntry, std::io::Error>> =
                    std::fs::read_dir(path)?.into_iter().collect();
                if sub_dir.len() != 1 {
                    bail!(
                        "Expected {} to only have 1 subdirectory, found {}",
                        path.display(),
                        sub_dir.len()
                    );
                }
                let entry = sub_dir[0].as_ref().unwrap();
                Ok(entry.path())
            }

            pub fn link(path: &Path) -> Result<Self> {
                let cpp_download_dir = Self::get_subdir(path)?;
                let r0_data = risc0_data()?;
                fs_extra::dir::copy(
                    cpp_download_dir.clone(),
                    &r0_data,
                    &CopyOptions::new().overwrite(true).copy_inside(true),
                )?;

                let cpp_install_dir = &r0_data.join("cpp");
                if cpp_install_dir.exists() {
                    std::fs::remove_dir_all(cpp_install_dir)?;
                }
                std::fs::rename(
                    r0_data.join(cpp_download_dir.file_name().unwrap()),
                    cpp_install_dir,
                )?;

                Ok(Self {
                    path: cpp_install_dir.into(),
                })
            }
        }

        #[derive(Clone, Debug)]
        pub struct RustupToolchain {
            pub path: PathBuf,
            pub name: String,
        }

        impl RustupToolchain {
            fn find_by_name(name: &str) -> Result<Option<Self>, anyhow::Error> {
                let out = Command::new("rustup")
                    .args(["toolchain", "list", "--verbose"])
                    .output()
                    .expect("failed to run rustup");
                let path_raw = out
                    .stdout
                    .lines()
                    .find(|line| line.trim().starts_with(name))
                    .and_then(|line| line.strip_prefix(name))
                    .map(|line| line.trim());
            }
        }

        /// Release returned by Github API.
        #[derive(Deserialize)]
        struct GithubReleaseData {
            assets: Vec<GithubAsset>,
            tag_name: String,
        }

        /// Release asset returned by Github API.
        #[derive(Deserialize)]
        struct GithubAsset {
            browser_download_url: String,
            name: String,
        }

        #[derive(Parser)]
        struct InstallToolchain {
            #[arg(long)]
            version: Option<String>,
        }

        impl InstallToolchain {
            async fn get_download_url(
                &self,
                client: &Client,
                target: &str,
                repo: &ToolchainRepo,
            ) -> Result<(String, String)> {
                let tag = match repo {
                    ToolchainRepo::Rust => self
                        .version
                        .clone()
                        .map_or("latest".to_string(), |tag| format!("tags/{tag}")),
                    ToolchainRepo::Cpp => "tags/2024.01.05".to_string(),
                };

                let repo_name = repo
                    .url()
                    .trim_start_matches("https://github.com/")
                    .trim_end_matches(".git");

                let release_url =
                    format!("https://api.github.com/repos/{repo_name}/releases/{tag}");

                eprintln!("Getting release info: {release_url}...");

                let release: GithubReleaseData = client
                    .get(&release_url)
                    .send()
                    .await?
                    .error_for_status()
                    .context(format!("Could not download release info"))?
                    .json()
                    .await
                    .context("could not deserialize release info")?;

                let asset_name = repo.asset_name(target);

                let asset = release
                    .assets
                    .iter()
                    .find(|asset| asset.name == asset_name)
                    .with_context(|| {
                        format!(
                            "Release {} does not have a prebuilt toolchain for host {}",
                            release.tag_name, target
                        )
                    })?;

                Ok((release.tag_name, asset.browser_download_url.clone()))
            }

            fn download_toolchain(
                &self,
                target: &str,
                toolchain_root_dir: &Path,
                repo: &ToolchainRepo,
            ) -> Result<PathBuf> {
                // TODO: Add github access token to avoid rate limiting
                let headers = HeaderMap::new();

                let client = Client::builder()
                    .default_headers(headers)
                    .user_agent("rzup")
                    .build()?;

                let temp_dir = tempdir()?;

                let mut downloader = Downloader::builder()
                    .download_folder(temp_dir.path())
                    .build_with_client(client.clone())?;

                let rt = tokio::runtime::Runtime::new()?;

                let (tag_name, download_url) =
                    rt.block_on(self.get_download_url(&client, target, repo))?;

                let toolchain_dir =
                    toolchain_root_dir.join(format!("{}_{target}_{}", repo.language(), tag_name));

                // TODO: Check about deleting toolchains
                if toolchain_dir.is_dir() {
                    eprintln!(
                        "Toolchain path {} already exists - deleting existing files!",
                        toolchain_dir.display()
                    );
                    std::fs::remove_dir_all(&toolchain_dir)?;
                }

                // Download the toolchain
                eprintln!(
                    "Downloading {} toolchain from '{}'...",
                    repo.language(),
                    &download_url
                );

                let dl = Download::new(&download_url);
                let download_res = downloader.download(&[dl])?;

                for res in download_res {
                    let summary = res.context(format!("Download failed."))?;
                    let tarball = File::open(summary.file_name)?;

                    eprintln!("Extracting toolchain...");

                    match repo {
                        ToolchainRepo::Rust => {
                            let decoder = GzDecoder::new(BufReader::new(tarball));
                            let mut archive = Archive::new(decoder);
                            archive.unpack(toolchain_dir.clone())?;
                        }
                        ToolchainRepo::Cpp => {
                            let decoder = XzDecoder::new(BufReader::new(tarball));
                            let mut archive = Archive::new(decoder);
                            archive.unpack(toolchain_dir.clone())?;
                        }
                    }
                }

                Ok(toolchain_dir)
            }

            fn download_toolchains(
                &self,
                target: &str,
                toolchains_root_dir: &Path,
            ) -> Result<(PathBuf, PathBuf)> {
                let cpp_toolchain_dir =
                    self.download_toolchain(target, toolchains_root_dir, &ToolchainRepo::Cpp)?;
                eprintln!(
                    "Downloaded C++ toolchain to {}",
                    cpp_toolchain_dir.display()
                );

                let rust_toolchain_dir =
                    self.download_toolchain(target, toolchains_root_dir, &ToolchainRepo::Rust)?;

                let rust_dir = rust_toolchain_dir.clone();

                #[cfg(target_family = "unix")]
                {
                    use std::os::unix::fs::PermissionsExt;

                    let iter1 = std::fs::read_dir(rust_dir.join("bin"))?;
                    let iter2 =
                        std::fs::read_dir(rust_dir.join(format!("lib/rustlib/{target}/bin")))?;

                    // make executable
                    for res in iter1.chain(iter2) {
                        let entry = res?;
                        if entry.file_type()?.is_file() {
                            let mut perms = entry.metadata()?.permissions();
                            perms.set_mode(0o755);
                            std::fs::set_permissions(entry.path(), perms)?;
                        }
                    }
                }

                eprintln!(
                    "Downloaded Rust toolchain to {}",
                    rust_toolchain_dir.display()
                );

                Ok((rust_toolchain_dir, cpp_toolchain_dir))
            }

            fn install_prebuilt_toolchains(
                &self,
                toolchain_dir: &Path,
            ) -> Result<(RustupToolchain, CppToolchain)> {
                if let Some(target) = guess_host_target() {
                    match self.download_toolchains(target, toolchain_dir) {
                        Ok((rust_path, cpp_path)) => {
                            let rust = RustupToolchain::link(RUSTUP_TOOLCHAIN_NAME, &rust_path)?;
                            let cpp = CppToolchain::link(&cpp_path)?;
                            Ok((rust, cpp))
                        }
                        Err(err) => {
                            eprintln!("Could not download pre-built toolchains: {err:?}");
                            Err(err.context("Download of pre-built toolchain failed"))
                        }
                    }
                } else {
                    bail!("The risc0 toolchain is not available for download on this platform. Build it yourself with: 'cargo risczero build-toolchain'")
                }
            }
        }
    }
}
