use std::{env, path::Path, process::Command};

fn main() {
    if env::var("CARGO_CFG_TARGET_OS").unwrap().contains("zkvm") {
        return;
    }

    let out_dir = env::var("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir);

    if env::var("CARGO_CFG_TARGET_OS").unwrap() == "macos" {
        build_metal_kernels(&out_dir);
    }

    if env::var("CARGO_FEATURE_CUDA").is_ok() {
        build_cuda_kernels(&out_dir);
    }
}

fn build_metal_kernels(out_dir: &Path) {
    const KERNELS: &[&str] = &["eltwise", "fri", "mix", "ntt", "sha", "zk"];

    let out_path = out_dir.join("kernels.metallib");
    let mut src_paths = vec![];
    let mut air_paths = vec![];

    for kernel in KERNELS {
        let out_path = out_dir.join(kernel).with_extension("air");
        let src_path = Path::new("kernels/metal")
            .join(kernel)
            .with_extension("metal");
        src_paths.push(src_path.display().to_string());

        let result = Command::new("xcrun")
            .args(&["--sdk", "macosx"])
            .arg("metal")
            .arg("-c")
            .arg(src_path)
            .arg("-o")
            .arg(&out_path)
            .status()
            .unwrap();
        if !result.success() {
            panic!("Failed to build metal kernels");
        }
        air_paths.push(out_path);
    }

    let result = Command::new("xcrun")
        .args(&["--sdk", "macosx"])
        .arg("metallib")
        .args(air_paths)
        .arg("-o")
        .arg(&out_path)
        .status()
        .unwrap();
    if result.success() {
        for src in src_paths {
            println!("cargo:rerun-if-changed={src}");
        }
    }
}

fn build_cuda_kernels(out_dir: &Path) {
    let src_paths = [
        "kernels/cuda/all.cu",
        "kernels/cuda/eltwise.cu",
        "kernels/cuda/sha.cu",
    ];
    let out_path = Path::new(out_dir).join("kernels.fatbin");
    let result = Command::new("nvcc")
        .arg("--fatbin")
        .arg("kernels/cuda/all.cu")
        .arg("-o")
        .arg(&out_path)
        .status()
        .unwrap();
    if result.success() {
        for src in src_paths {
            println!("cargo:rerun-if-changed={src}");
        }
    } else {
        panic!("Failed to build cuda kernels");
    }
}
