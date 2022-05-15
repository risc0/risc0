use std::{env, fs::File, io::Write, path::Path, process::Command};

fn build() {
    let out_dir = env::var("OUT_DIR").unwrap();
    let args = vec![
        "build",
        "--release",
        "--target",
        "../../../../bazel/rules/rust/riscv32im-unknown-none-elf.json",
        "-Z",
        "build-std=alloc,core",
        "--target-dir",
        &out_dir,
    ];
    let status = Command::new(env!("CARGO")).args(args).status().unwrap();
    if !status.success() {
        std::process::exit(status.code().unwrap());
    }
}

fn generate_module(methods: &[&str]) {
    let out_dir = env::var_os("OUT_DIR").unwrap();
    let dest_path = Path::new(&out_dir).join("methods.rs");
    let mut file = File::create(&dest_path).unwrap();

    for method in methods {
        let elf_path = Path::new(&out_dir)
            .join("riscv32im-unknown-none-elf")
            .join("release")
            .join(method);
        let mut id_path = Path::new(&out_dir).join(method);
        id_path.set_extension("id");

        let status = Command::new("make-id")
            .args([&elf_path, &id_path])
            .status()
            .unwrap();
        if !status.success() {
            std::process::exit(status.code().unwrap());
        }

        let elf_path = elf_path.display();
        let id_path = id_path.display();
        let upper = method.to_uppercase();
        let content = format!(
            r#"
    pub const {upper}: &[u8] = include_bytes!("{elf_path}");
    pub const {upper}_ID: &[u8] = include_bytes!("{id_path}");
    "#
        );
        file.write_all(content.as_bytes()).unwrap();
    }
}

fn main() {
    if env::var("CARGO_CFG_TARGET_ARCH").unwrap() != "riscv32" {
        build();
        generate_module(&["init", "turn"]);
    }
}
