use std::path::PathBuf;

fn main() {
    if std::env::var("CARGO_CFG_TARGET_ARCH").unwrap() != "riscv32" {
        let srcs: Vec<PathBuf> = glob::glob("cxx/*.cpp")
            .unwrap()
            .map(|x| x.unwrap())
            .collect();
        cc::Build::new()
            .cpp(true)
            .files(&srcs)
            .flag_if_supported("/std:c++17")
            .flag_if_supported("-std=c++17")
            .compile("circuit");
        for src in srcs {
            println!("cargo:rerun-if-changed={}", src.display());
        }
    }
}
