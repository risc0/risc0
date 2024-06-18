use clap::Args;

use crate::{
    toolchain::{
        repo::ToolchainRepo,
        rust::{RustupToolchain, RUSTUP_TOOLCHAIN_NAME},
    },
    utils::get_installed_toolchains,
};

#[derive(Debug, Default, Args, Clone)]
pub struct DefaultOpts {
    #[arg(required = true)]
    pub name: String,
}

pub fn handle_default(opts: DefaultOpts) {
    let toolchains = get_installed_toolchains().expect("Error getting installed toolchains");
    let toolchain = &toolchains
        .iter()
        .find(|t| t.name == opts.name)
        .expect("Error finding toolchain {name}");

    match toolchain.repo {
        ToolchainRepo::Rust => RustupToolchain::link(RUSTUP_TOOLCHAIN_NAME, &toolchain.path)
            .expect("Error linking toolchain {name}"),
        ToolchainRepo::Cpp => todo!(), // TODO
    };
}
