use clap::Parser;
use std::path::PathBuf;
use std::process::Command;

const DIST_SERVER: &str = "https://storage.googleapis.com/risc0-rust-dist";

#[derive(Parser)]
#[clap(name = "cargo")]
#[clap(bin_name = "cargo")]
enum Cargo {
    #[clap(name = "risc0")]
    Risc0(Risc0),
}

#[derive(Parser)]
struct Risc0 {
    #[clap(short, long, action = clap::ArgAction::Count)]
    verbose: u8,

    #[clap(subcommand)]
    subcommand: Subcommand,
}

#[derive(Debug, Parser)]
enum Subcommand {
    /// Install the risc0 toolchain for riscv32im-risc0-zkvm-elf.
    Install,

    /// Update the risc0 toolchain for riscv32im-risc0-zkvm-elf to the latest version.
    Update,

    /// Uninstall the risc0 toolchain.
    Uninstall,
}

fn rustup_exe() -> PathBuf {
    home::cargo_home()
        .expect("Unable to determine cargo home directory")
        .join("bin")
        .join("rustup")
        .into()
}
fn risc0_root() -> PathBuf {
    home::home_dir().unwrap().join(".risc0").into()
}

fn set_verbose(args: &Risc0, cmd: &mut Command) {
    for _ in 0..args.verbose {
        cmd.arg("-v");
    }
}

fn risc0_rustup(args: &Risc0) -> Command {
    let mut cmd = Command::new(rustup_exe());

    cmd.env("RUSTUP_HOME", risc0_root().join("rustup"));
    cmd.env("RUSTUP_DIST_SERVER", DIST_SERVER);
    set_verbose(&args, &mut cmd);

    cmd
}

fn install_toolchain() {}

fn cmd_install(args: &Risc0) {
    std::fs::create_dir_all(risc0_root().join("rustup")).expect("Could not create risc0 root");

    risc0_rustup(&args)
        .arg("toolchain")
        .arg("install")
        .arg("nightly")
        .arg("--no-self-update")
        .arg("--target")
        .arg("riscv32im-risc0-zkvm-elf")
        .status()
        .expect("Could not use rustup to install riscv32im toolchain");

    let toolchains_dir = risc0_root().join("rustup").join("toolchains");

    let toolchains: Vec<String> = std::fs::read_dir(&toolchains_dir)
        .unwrap_or_else(|err| {
            panic!(
                "Unable to enumerate risc0 toolchains in {:?}: {:?}",
                toolchains_dir, err
            )
        })
        .filter_map(|ent| {
            let fname = ent.ok()?.file_name().into_string().ok()?;
            if fname.starts_with("nightly-") {
                Option::Some(fname)
            } else {
                Option::None
            }
        })
        .collect();
    let toolchain = match toolchains.as_slice() {
        [] => panic!("No toolchains downloaded"),
        [toolchain] => toolchain,
        _ => panic!("Ambiguous toolchains downloaded: {:?}", toolchains),
    };

    let mut cmd = Command::new(rustup_exe());
    set_verbose(&args, &mut cmd);
    cmd.arg("toolchain")
        .arg("link")
        .arg("risc0")
        .arg(toolchains_dir.join(toolchain))
        .status()
        .expect("Unable to alias 'risc0' to point to the risc0 custom toolchain");

    install_toolchain();
}

fn cmd_update(args: &Risc0) {
    risc0_rustup(&args)
        .arg("update")
        .arg("--no-self-update")
        .status()
        .expect("'rustup update' failed");
}

fn cmd_uninstall(args: &Risc0) {
    std::fs::remove_dir_all(risc0_root()).unwrap_or_else(|err| {
        panic!(
            "Unable to remove risc0 directory {}: {}",
            risc0_root().display(),
            err
        );
    });

    let mut cmd = Command::new(rustup_exe());
    set_verbose(&args, &mut cmd);
    cmd.arg("toolchain")
        .arg("uninstall")
        .arg("risc0")
        .status()
        .expect("Unable to unalias 'risc0' from the risc0 custom toolchain");
}

fn main() {
    let Cargo::Risc0(args) = Cargo::parse();
    match args.subcommand {
        Subcommand::Install => cmd_install(&args),
        Subcommand::Update => cmd_update(&args),
        Subcommand::Uninstall => cmd_uninstall(&args),
    }
}
