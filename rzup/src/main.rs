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
        // pub struct ExitCode(pub i32);
    }

    mod dist {

        use anyhow::Result;
        use downloader::Downloader;
        use reqwest::{header::HeaderMap, Client};
        use std::path::{Path, PathBuf};
        use tempfile::tempdir;

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
        }

        async fn _download_toolchain(
            _target: &str,
            _toolchains_root_dir: &Path,
            _repo: &ToolchainRepo,
        ) -> Result<PathBuf> {
            let headers = HeaderMap::new();
            let client = Client::builder()
                .default_headers(headers)
                .user_agent("rzup")
                .build()?;

            let temp_dir = tempdir()?;

            let mut _dl = Downloader::builder()
                .download_folder(temp_dir.path())
                .build_with_client(client.clone())?;

            todo!()
        }

        async fn get_download_url(
            _client: &Client,
            _target: &str,
            version: &str,
            repo: &ToolchainRepo,
        ) -> Result<(String, String)> {
            let tag = match repo {
                ToolchainRepo::Rust => format!("tags/{}", version),
                ToolchainRepo::Cpp => "tags/2024.01.05".to_string(),
            };

            let repo_name = repo
                .url()
                .trim_start_matches("https://github.com/")
                .trim_end_matches(".git");

            let release_url = format!("https://api.github.com/repos/{repo_name}/releases/{tag}");

            eprintln!("Getting release info: {release_url}...");
            todo!()
        }

        // use crate::cli::utils;
        // use anyhow::Result;
        // use downloader::{Download, Downloader};
        // use flate2::read::GzDecoder;
        // use std::fs;
        // use std::fs::File;
        // use tar::Archive;
        // use tempfile::tempdir;
        //
        // pub async fn _install(opts: &crate::cli::rzup_mode::UpdateOpts) -> Result<utils::ExitCode> {
        //     if opts.install_cargo_risczero {
        //         let cargo_risczero_url = format!(
        //             "https://github.com/risc0/risc0/releases/download/{}/cargo-risczero-{}.tgz",
        //             opts.toolchain[0], opts.toolchain[0]
        //         );
        //
        //         _download_and_extract(&cargo_risczero_url).await?;
        //     }
        //
        //     for toolchain in &opts.toolchain {
        //         let url = format!(
        //             "https://github.com/risc0/risc0/releases/download/{}/{}.tgz",
        //             toolchain, toolchain
        //         );
        //
        //         _download_and_extract(&url).await?;
        //     }
        //
        //     Ok(utils::ExitCode(0))
        // }
        //
        // async fn _download_and_extract(url: &str) -> Result<utils::ExitCode> {
        //     let tmp_dir = tempdir()?;
        //
        //     let file_path = tmp_dir.path().join("r0_downloaded.tgz");
        //
        //     let mut downloader = Downloader::builder()
        //         .download_folder(tmp_dir.path())
        //         .build()?;
        //
        //     let _ = downloader
        //         .download(&[Download::new(url)])
        //         .map_err(|_| utils::ExitCode(1));
        //
        //     let tar_gz = File::open(&file_path)?;
        //     let tar = GzDecoder::new(tar_gz);
        //     let mut archive = Archive::new(tar);
        //
        //     let home_dir =
        //         dirs::home_dir().ok_or_else(|| anyhow::anyhow!("Could not find home dir"))?;
        //     let cargo_bin_dir = home_dir.join(".cargo/bin");
        //
        //     fs::create_dir_all(&cargo_bin_dir)?;
        //
        //     for entry in archive.entries()? {
        //         let mut entry = entry?;
        //         let path = entry.path()?;
        //         let dest_path = cargo_bin_dir.join(
        //             path.file_name()
        //                 .ok_or_else(|| anyhow::anyhow!("Invalid file name"))?,
        //         );
        //         entry.unpack(dest_path)?;
        //     }
        //
        //     println!("Installed to {}", cargo_bin_dir.display());
        //
        //     Ok(utils::ExitCode(0))
        // }
    }
}
