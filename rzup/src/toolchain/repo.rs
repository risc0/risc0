use clap::{Parser, ValueEnum};

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
