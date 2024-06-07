use clap::Parser;
use cli::dist::InstallToolchain;
use cli::dist::ToolchainRepo;
use cli::rzup_mode::InstallSubcmd;
use cli::rzup_mode::RzupSubcmd;
use cli::rzup_mode::ShowSubcmd;
use cli::rzup_mode::ToolchainSubcmd;
use cli::utils::risc0_data;
use std::fs;
use std::io::Write;
use termcolor::{Color, ColorChoice, ColorSpec, StandardStream, WriteColor};

fn main() {
    let matches = cli::rzup_mode::Rzup::parse();

    let subcmd = matches.subcmd;

    match subcmd {
        Some(RzupSubcmd::Install { subcmd }) => {
            match subcmd {
                InstallSubcmd::Rust { toolchain } => {
                    // Install Rust toolchain
                    InstallToolchain {
                        toolchain: Some(toolchain),
                        repo: ToolchainRepo::Rust,
                    }
                    .run()
                    .expect("Error during Rust toolchain installation");
                }
                InstallSubcmd::Cpp { toolchain } => {
                    // Install C++ toolchain
                    InstallToolchain {
                        toolchain: Some(toolchain),
                        repo: ToolchainRepo::Cpp,
                    }
                    .run()
                    .expect("Error during C++ toolchain installation");
                }
                InstallSubcmd::All => {
                    // Install all toolchains
                    InstallToolchain {
                        toolchain: None,
                        repo: ToolchainRepo::Rust,
                    }
                    .run()
                    .expect("Error during Rust toolchain installation");
                    InstallToolchain {
                        toolchain: None,
                        repo: ToolchainRepo::Cpp,
                    }
                    .run()
                    .expect("Error during C++ toolchain installation");
                }
            }
        }
        Some(RzupSubcmd::Toolchain { subcmd }) => {
            match subcmd {
                ToolchainSubcmd::List { verbose } => {
                    if let Err(e) = show_installed_toolchains(verbose) {
                        eprintln!("Error showing toolchains: {}", e);
                        std::process::exit(1);
                    }
                }
                ToolchainSubcmd::Install { subcmd } => {
                    match subcmd {
                        InstallSubcmd::Rust { toolchain } => {
                            // Install Rust toolchain
                            InstallToolchain {
                                toolchain: Some(toolchain),
                                repo: ToolchainRepo::Rust,
                            }
                            .run()
                            .expect("Error during Rust toolchain installation");
                        }
                        InstallSubcmd::Cpp { toolchain } => {
                            // Install C++ toolchain
                            InstallToolchain {
                                toolchain: Some(toolchain),
                                repo: ToolchainRepo::Cpp,
                            }
                            .run()
                            .expect("Error during C++ toolchain installation");
                        }
                        InstallSubcmd::All => {
                            // Install all toolchains
                            InstallToolchain {
                                toolchain: None,
                                repo: ToolchainRepo::Rust,
                            }
                            .run()
                            .expect("Error during Rust toolchain installation");
                            InstallToolchain {
                                toolchain: None,
                                repo: ToolchainRepo::Cpp,
                            }
                            .run()
                            .expect("Error during C++ toolchain installation");
                        }
                    }
                }
                ToolchainSubcmd::Build(cmd) => {
                    if let Err(e) = cmd.run() {
                        eprintln!("Error building toolchain: {}", e);
                        std::process::exit(1);
                    }
                }
            }
        }
        Some(RzupSubcmd::Show { verbose, subcmd }) => {
            match subcmd {
                Some(ShowSubcmd::ActiveToolchain { .. }) => {
                    // Placeholder for active toolchain logic
                    println!("Active toolchain logic not implemented yet.");
                }
                Some(ShowSubcmd::Home) => {
                    // Placeholder for RZUP_HOME logic
                    println!("RZUP_HOME logic not implemented yet.");
                }
                None => {
                    // Call the function to list all installed toolchains
                    if let Err(e) = show_installed_toolchains(verbose) {
                        eprintln!("Error showing toolchains: {}", e);
                        std::process::exit(1);
                    }
                }
            }
        }
        Some(RzupSubcmd::Check { .. }) => todo!(),
        Some(RzupSubcmd::Update { .. }) => todo!(),
        Some(RzupSubcmd::Default { .. }) => todo!(),
        Some(RzupSubcmd::Uninstall { .. }) => todo!(),
        None => todo!(),
    }
}

fn show_installed_toolchains(verbose: bool) -> anyhow::Result<()> {
    let toolchains_dir = risc0_data()?.join("toolchains");

    if !toolchains_dir.exists() {
        eprintln!("No toolchains directory found.");
        return Ok(());
    }

    let entries = fs::read_dir(&toolchains_dir)?
        .filter_map(|res| res.ok())
        .filter(|entry| entry.path().is_dir())
        .collect::<Vec<_>>();

    if entries.is_empty() {
        println!("No installed toolchains found.");
        return Ok(());
    }

    for entry in entries {
        let toolchain_name = entry.file_name().to_string_lossy().to_string();
        if verbose {
            println!("Toolchain: {}", toolchain_name);
            // Optionally add more detailed information about the toolchain here
        } else {
            // println!("{}", toolchain_name);
            let mut stdout = StandardStream::stdout(ColorChoice::Always);
            stdout.set_color(ColorSpec::new().set_fg(Some(Color::Green)))?;
            writeln!(&mut stdout, "{}", toolchain_name)?;
        }
    }

    Ok(())
}

mod cli {

    pub mod rzup_mode {
        use crate::cli::{build_toolchain, common, help};
        use clap::{Parser, Subcommand};

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
                #[command(subcommand)]
                subcmd: InstallSubcmd,
            },

            /// Manage toolchains
            Toolchain {
                #[command(subcommand)]
                subcmd: ToolchainSubcmd,
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

            /// Uninstall RISC Zero toolchains
            Uninstall,
        }

        #[derive(Debug, Subcommand)]
        pub enum ToolchainSubcmd {
            /// List installed toolchains
            List {
                #[arg(short, long)]
                verbose: bool,
            },

            /// Install or update a given toolchain
            Install {
                #[command(subcommand)]
                subcmd: InstallSubcmd,
            },

            /// Build the toolchain
            Build(build_toolchain::BuildToolchain),
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

        #[derive(Debug, Subcommand)]
        pub enum InstallSubcmd {
            /// Install Rust toolchain
            Rust {
                /// Toolchain version (i.e. stable)
                #[arg(required = false)]
                toolchain: String,
            },
            /// Install C++ toolchain
            Cpp {
                /// Toolchain version
                #[arg(required = false)]
                toolchain: String,
            },
            /// Install all avaliable toolchains
            All,
        }
    }

    mod common {
        pub fn version() -> &'static str {
            "0.2.0"
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

    #[allow(dead_code)]
    pub mod utils {
        use anyhow::{anyhow, Context};
        use anyhow::{bail, Result};
        use fs2::FileExt;
        use std::fmt;
        use std::fs::{File, OpenOptions};
        use std::path::{Path, PathBuf};
        use std::process::{Command, ExitStatus, Output, Stdio};

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

        /// Make sure a binary exists and runs with the given arguments.
        pub fn ensure_binary(command: &str, args: &[&str]) -> Result<()> {
            Command::new(command)
                .args(args)
                .stdout(std::process::Stdio::piped())
                .run_verbose()
                .with_context(|| format!("Could not find or execute binary: {command}"))?;

            Ok(())
        }

        pub trait CommandExt {
            fn as_command_mut(&mut self) -> &mut Command;

            fn capture_stdout(&mut self) -> Result<String> {
                let cmd = self.as_command_mut();
                let output = cmd.stderr(Stdio::inherit()).output_if_success()?;
                let str = String::from_utf8(output.stdout)
                    .map_err(|_| anyhow!("process output was not utf-8"))
                    .with_context(|| format!("failed to execute {:?}", cmd))?;
                Ok(str)
            }

            fn run_verbose(&mut self) -> Result<()> {
                let cmd = self.as_command_mut();
                eprintln!(
                    "Running {} {}:",
                    cmd.get_program().to_string_lossy(),
                    cmd.get_args()
                        .map(|x| x.to_string_lossy())
                        .collect::<Vec<_>>()
                        .join(" ")
                );
                self.run()
            }

            fn run(&mut self) -> Result<()> {
                let cmd = self.as_command_mut();
                cmd.stderr(Stdio::inherit())
                    .stdout(Stdio::inherit())
                    .stdin(Stdio::inherit())
                    .output_if_success()?;
                Ok(())
            }

            fn output_if_success(&mut self) -> Result<Output> {
                let cmd = self.as_command_mut();
                let output = cmd
                    .output()
                    .with_context(|| format!("failed to create process {:?}", cmd))?;
                check_success(cmd, &output.status, &output.stdout, &output.stderr)?;
                Ok(output)
            }
        }

        impl CommandExt for Command {
            fn as_command_mut(&mut self) -> &mut Command {
                self
            }
        }

        pub fn check_success(
            cmd: &Command,
            status: &ExitStatus,
            stdout: &[u8],
            stderr: &[u8],
        ) -> Result<()> {
            if status.success() {
                return Ok(());
            }
            Err(ProcessError {
                cmd_desc: format!("{:?}", cmd),
                status: *status,
                stdout: stdout.to_vec(),
                stderr: stderr.to_vec(),
                hidden: false,
            }
            .into())
        }

        #[derive(Debug)]
        struct ProcessError {
            status: ExitStatus,
            #[allow(dead_code)]
            hidden: bool,
            stdout: Vec<u8>,
            stderr: Vec<u8>,
            cmd_desc: String,
        }

        impl fmt::Display for ProcessError {
            fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
                write!(f, "failed to execute {}", self.cmd_desc)?;
                write!(f, "\n    status: {}", self.status)?;
                if !self.stdout.is_empty() {
                    let stdout = String::from_utf8_lossy(&self.stdout);
                    let stdout = stdout.replace('\n', "\n        ");
                    write!(f, "\n    stdout:\n        {}", stdout)?;
                }
                if !self.stderr.is_empty() {
                    let stderr = String::from_utf8_lossy(&self.stderr);
                    let stderr = stderr.replace('\n', "\n        ");
                    write!(f, "\n    stderr:\n        {}", stderr)?;
                }
                Ok(())
            }
        }

        impl std::error::Error for ProcessError {}

        pub struct FileLock(File);

        impl Drop for FileLock {
            fn drop(&mut self) {
                drop(self.0.unlock());
            }
        }

        pub fn flock(path: &Path) -> Result<FileLock> {
            let parent = path.parent().unwrap();
            std::fs::create_dir_all(parent)
                .context(format!("failed to create directory `{}`", parent.display()))?;
            let file = OpenOptions::new()
                .create(true)
                .read(true)
                .write(true)
                .open(path)?;
            file.lock_exclusive()?;
            return Ok(FileLock(file));
        }
    }

    #[allow(dead_code)]
    pub mod dist {

        use crate::cli::help;
        use crate::cli::utils::{flock, CommandExt};
        use anyhow::{anyhow, bail, Context, Result};
        use clap::Args;
        use clap::Parser;
        use clap::ValueEnum;
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

        pub const RUSTUP_TOOLCHAIN_NAME: &str = "risc0";

        #[derive(Default, Debug, Clone, Parser, ValueEnum)]
        pub enum ToolchainRepo {
            #[default]
            Rust,
            Cpp,
            All,
        }

        impl ToolchainRepo {
            pub const fn url(&self) -> &str {
                match self {
                    Self::Rust => "https://github.com/risc0/rust.git",
                    Self::Cpp => "https://github.com/risc0/toolchain.git",
                    Self::All => todo!(),
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
                    Self::All => todo!(),
                }
            }

            pub const fn language(&self) -> &str {
                match self {
                    Self::Rust => "rust",
                    Self::Cpp => "cpp",
                    Self::All => todo!(),
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
                    .capture_stdout()?;

                let path_raw = out
                    .lines()
                    .find(|line| line.trim().starts_with(name))
                    .and_then(|line| line.strip_prefix(name))
                    .map(|line| line.trim());

                if let Some(path) = path_raw {
                    Ok(Some(Self {
                        name: name.to_string(),
                        path: path.into(),
                    }))
                } else {
                    Ok(None)
                }
            }

            pub fn link(name: &str, dir: &Path) -> Result<Self> {
                eprintln!("Activating rustup toolchain {} at {}", name, dir.display());

                #[cfg(not(target_os = "windows"))]
                let rustc_exe = "rustc";

                #[cfg(target_os = "windows")]
                let rustc_exe = "rustc.exe";

                let rustc_path = dir.join("bin").join(rustc_exe);
                if !rustc_path.is_file() {
                    bail!(
                        "Invalid toolchain directory: rustc executable not found at {}",
                        rustc_path.display()
                    );
                }

                if Self::find_by_name(name)?.is_some() {
                    Command::new("rustup")
                        .args(["toolchain", "remove", name])
                        .run()
                        .context("Could not remove existing toolchain")?;
                }

                Command::new("rustup")
                    .args(["toolchain", "link", name])
                    .arg(dir)
                    .run_verbose()
                    .context("Could not link toolchain: rustup not installed?")?;

                eprintln!("rusutp toolcahin {name} was linked sucessfully");

                Ok(Self {
                    name: name.to_string(),
                    path: dir.into(),
                })
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

        #[derive(Debug, Default, Args)]
        pub struct InstallToolchain {
            #[arg(
                required = false,
                help = help::TOOLCHAIN_ARG_HELP,
                num_args = 1..,
            )]
            pub toolchain: Option<String>,
            pub repo: ToolchainRepo,
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
                        .toolchain
                        .clone()
                        .map_or("latest".to_string(), |tag| format!("tags/{tag}")),
                    ToolchainRepo::Cpp => "tags/2024.01.05".to_string(),
                    ToolchainRepo::All => todo!(),
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
                    toolchain_root_dir.join(format!("{}-{}-{target}", tag_name, repo.language()));

                if toolchain_dir.is_dir() {
                    eprintln!(
                        "Toolchain path {} already exists - deleting existing files!",
                        toolchain_dir.display()
                    );
                    std::fs::remove_dir_all(&toolchain_dir)?;
                }

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
                        ToolchainRepo::All => todo!(),
                    }
                }

                Ok(toolchain_dir)
            }

            pub fn run(&self) -> Result<()> {
                let root_dir = risc0_data()?;
                let lockfile_path = root_dir.join("lock");
                let _lock = flock(&lockfile_path);

                let toolchain_dir = root_dir.join("toolchains");

                match self.repo {
                    ToolchainRepo::Rust => {
                        let rust_path = self.download_toolchain(
                            guess_host_target().ok_or(anyhow!("Unsupported host target"))?,
                            &toolchain_dir,
                            &ToolchainRepo::Rust,
                        )?;
                        let rust_chain = RustupToolchain::link(RUSTUP_TOOLCHAIN_NAME, &rust_path)?;
                        eprintln!(
                            "Rust Toolchain {} downloaded and installed to path {}.",
                            rust_chain.name,
                            rust_chain.path.display()
                        );
                    }
                    ToolchainRepo::Cpp => {
                        let cpp_path = self.download_toolchain(
                            guess_host_target().ok_or(anyhow!("Unsupported host target"))?,
                            &toolchain_dir,
                            &ToolchainRepo::Cpp,
                        )?;
                        let cpp_chain = CppToolchain::link(&cpp_path)?;
                        eprintln!(
                            "C++ Toolchain downloaded and installed to path {}.",
                            cpp_chain.path.display()
                        );
                    }
                    ToolchainRepo::All => {
                        let rust_path = self.download_toolchain(
                            guess_host_target().ok_or(anyhow!("Unsupported host target"))?,
                            &toolchain_dir,
                            &ToolchainRepo::Rust,
                        )?;
                        let rust_chain = RustupToolchain::link(RUSTUP_TOOLCHAIN_NAME, &rust_path)?;
                        eprintln!(
                            "Rust Toolchain {} downloaded and installed to path {}.",
                            rust_chain.name,
                            rust_chain.path.display()
                        );

                        let cpp_path = self.download_toolchain(
                            guess_host_target().ok_or(anyhow!("Unsupported host target"))?,
                            &toolchain_dir,
                            &ToolchainRepo::Cpp,
                        )?;
                        let cpp_chain = CppToolchain::link(&cpp_path)?;
                        eprintln!(
                            "C++ Toolchain downloaded and installed to path {}.",
                            cpp_chain.path.display()
                        );
                    }
                }

                eprintln!("The risc0 toolchain is now ready to use.");
                Ok(())
            }
        }

        /// Try to get the host target triple.
        ///
        /// Only checks for targets that have pre-built toolchains.
        #[allow(unreachable_code)]
        fn guess_host_target() -> Option<&'static str> {
            #[cfg(all(target_arch = "x86_64", target_os = "linux"))]
            return Some("x86_64-unknown-linux-gnu");

            #[cfg(all(target_arch = "x86_64", target_os = "macos"))]
            return Some("x86_64-apple-darwin");

            #[cfg(all(target_arch = "aarch64", target_os = "macos"))]
            return Some("aarch64-apple-darwin");

            #[cfg(all(target_arch = "x86_64", target_os = "windows"))]
            return Some("x86_64-pc-windows-msvc");

            None
        }
    }

    pub mod build_toolchain {
        use std::{
            path::{Path, PathBuf},
            process::Command,
        };

        use anyhow::{bail, Context, Result};
        use clap::Parser;

        use crate::{
            cli::dist::{RustupToolchain, ToolchainRepo, RUSTUP_TOOLCHAIN_NAME},
            cli::utils::{ensure_binary, CommandExt},
        };

        const CONFIG_TOML: &'static str = include_str!("config.toml");

        /// `cargo risczero build-toolchain`
        #[derive(Debug, Parser)]
        pub struct BuildToolchain {
            /// Version tag of the toolchain to build.
            #[arg(long)]
            version: Option<String>,
        }

        /// Output info of a successful rust toolchain build.
        pub struct RustBuildOutput {
            pub target: String,
            pub toolchain_dir: PathBuf,
        }

        impl BuildToolchain {
            pub fn run(&self) -> Result<()> {
                eprintln!("Building the riscv32im-risc0-zkvm-elf toolchain...");

                let root_dir = if let Ok(dir) = std::env::var("RISC0_BUILD_DIR") {
                    PathBuf::from(dir)
                } else {
                    dirs::home_dir()
                        .context("Could not determine home dir. Set RISC0_BUILD_DIR env var!")?
                        .join(".rzup")
                };
                let rust_dir = root_dir.join("rust");

                let tag = match &self.version {
                    Some(tag) => tag,
                    None => "risc0",
                };
                let is_ci = std::env::var("CI").is_ok();
                if !is_ci {
                    self.prepare_git_repo(ToolchainRepo::Rust.url(), tag, &rust_dir)?;
                }

                let out = self.build_toolchain(&rust_dir)?;
                let tools_bin_dir = out.toolchain_dir.parent().unwrap().join("stage2-tools-bin");
                let target_bin_dir = out.toolchain_dir.join("bin");

                for tool in tools_bin_dir.read_dir()? {
                    let tool = tool?;
                    let tool_name = tool.file_name();
                    eprintln!("copy tool: {tool_name:?}");
                    std::fs::copy(&tool.path(), target_bin_dir.join(tool_name))?;
                }

                RustupToolchain::link(RUSTUP_TOOLCHAIN_NAME, &out.toolchain_dir)?;

                Ok(())
            }

            /// Initialize a Git repo.
            ///
            /// Clone if it doesn't exist yet, otherwise update the branch/tag.
            fn prepare_git_repo(&self, source: &str, tag: &str, path: &Path) -> Result<()> {
                eprintln!("Preparing git repo {source} with tag/branch {tag}");
                ensure_binary("git", &["--version"])?;

                if !path.join(".git").is_dir() {
                    Command::new("git")
                        .args(["clone", source])
                        .arg(path)
                        .run_verbose()?;
                } else {
                    // fetch to update tag names. Otherwise, new git tags will not appear.
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

            fn build_toolchain(&self, rust_dir: &Path) -> Result<RustBuildOutput> {
                std::fs::write(rust_dir.join("config.toml"), CONFIG_TOML)?;

                let has_python3 = Command::new("python3").arg("--version").run().is_ok();
                let python_cmd = if has_python3 { "python3" } else { "python" };

                // Stage 1.
                Command::new(python_cmd)
                    .env(
                        "CARGO_TARGET_RISCV32IM_RISC0_ZKVM_ELF_RUSTFLAGS",
                        "-Cpasses=loweratomic",
                    )
                    .current_dir(&rust_dir)
                    .args(["x.py", "build"])
                    .run_verbose()?;

                // Stage 2.
                Command::new(python_cmd)
                    .env(
                        "CARGO_TARGET_RISCV32IM_RISC0_ZKVM_ELF_RUSTFLAGS",
                        "-Cpasses=loweratomic",
                    )
                    .args(["x.py", "build", "--stage", "2"])
                    .current_dir(&rust_dir)
                    .run_verbose()?;

                eprintln!("Rust build complete!");

                for result in std::fs::read_dir(rust_dir.join("build"))? {
                    let entry = result?;
                    let toolchain_dir = entry.path().join("stage2");
                    if toolchain_dir.is_dir() {
                        let target = entry.file_name().to_string_lossy().to_string();
                        return Ok(RustBuildOutput {
                            target,
                            toolchain_dir,
                        });
                    }
                }

                bail!("Could not find build directory")
            }
        }
    }
}
