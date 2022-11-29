use std::{
    env,
    path::{Path, PathBuf},
    process::Command,
    time::UNIX_EPOCH,
};

use sha2::{Digest, Sha256};

const KERNELS: &[&str] = &["eval_check"];

fn main() {
    if env::var("CARGO_CFG_TARGET_OS").unwrap().contains("zkvm")
        || env::var("CARGO_FEATURE_VERIFY_ONLY").is_ok()
    {
        return;
    }

    let out_dir = env::var("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir);

    build_cpu_kernels();

    if env::var("CARGO_CFG_TARGET_OS").unwrap() == "macos" {
        build_metal_kernels(&out_dir);
    }

    if env::var("CARGO_FEATURE_CUDA").is_ok() {
        build_cuda_kernels(&out_dir);
    }
}

fn build_cpu_kernels() {
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

fn build_metal_kernels(out_dir: &Path) {
    let mut src_paths = vec![];
    let mut air_paths = vec![];

    let compiler = String::from_utf8(
        Command::new("xcrun")
            .args(["--find", "--sdk", "macosx", "metal"])
            .output()
            .unwrap()
            .stdout,
    )
    .unwrap();
    let compiler = compiler.trim_end();
    eprintln!("compiler: {compiler}");

    let inc_path = "../../../risc0/zkp/kernels/metal";

    for kernel in KERNELS {
        let out_path = out_dir.join(kernel).with_extension("air");
        let sha_path = out_dir.join(kernel).with_extension("sha");
        let src_path = Path::new("kernels").join(kernel).with_extension("metal");
        let src_path = src_path.display().to_string();
        src_paths.push(src_path.clone());

        let out_path = out_path.display().to_string();
        air_paths.push(out_path.clone());

        let args = vec!["-c", &src_path, "-I", inc_path, "-o", &out_path];

        let (sha, sha_hex) = compute_hash(&src_path, inc_path, &args);
        if let Ok(cached_sha) = std::fs::read(&sha_path) {
            if cached_sha == sha.as_slice() {
                println!("Metal kernel {} ({}) up to date", kernel, sha_hex);
                continue;
            }
        }

        let result = Command::new(compiler).args(args).status().unwrap();
        if !result.success() {
            panic!("Could not build metal kernels");
        }

        std::fs::write(sha_path, sha).unwrap();
    }

    let out_path = out_dir.join("kernels.metallib");
    let result = Command::new("xcrun")
        .args(&["--sdk", "macosx"])
        .arg("metallib")
        .args(air_paths)
        .arg("-o")
        .arg(&out_path)
        .status()
        .unwrap();
    if !result.success() {
        panic!("Could not build metal kernels");
    }

    for src in src_paths {
        println!("cargo:rerun-if-changed={src}");
    }
    for header in glob::glob(&inc_path).unwrap() {
        let header = header.unwrap();
        let header = header.display().to_string();
        println!("cargo:rerun-if-changed={header}");
    }
}

fn build_cuda_kernels(out_dir: &Path) {
    let src_path = "kernels/eval_check.cu";
    let out_path = out_dir.join("kernels.fatbin");
    let out_path = out_path.display().to_string();
    let sha_path = out_dir.join("kernels.sha");
    let inc_path = "../../../risc0/zkp/kernels/cuda";

    let args = ["--fatbin", &src_path, "-I", &inc_path, "-o", &out_path];

    let (sha, sha_hex) = compute_hash(&src_path, inc_path, &args);
    if let Ok(cached_sha) = std::fs::read(&sha_path) {
        if cached_sha == sha.as_slice() {
            println!("CUDA kernel {} ({}) up to date", out_path, sha_hex);
            return;
        }
    }

    let result = Command::new("nvcc").args(args).status().unwrap();
    if !result.success() {
        panic!("Failed to build CUDA kernels");
    }

    std::fs::write(sha_path, sha).unwrap();

    println!("cargo:rerun-if-changed={src_path}");
    for header in glob::glob(&inc_path).unwrap() {
        let header = header.unwrap();
        let header = header.display().to_string();
        println!("cargo:rerun-if-changed={header}");
    }
}

struct Hasher {
    sha: Sha256,
}

impl Hasher {
    fn new() -> Self {
        Self { sha: Sha256::new() }
    }

    fn add_args(&mut self, args: &[&str]) {
        for arg in args.iter() {
            self.sha.update(arg.as_bytes());
        }
    }

    fn add_mtime<P: AsRef<Path>>(&mut self, path: P) {
        let metadata = std::fs::metadata(path).unwrap();
        let mtime = metadata.modified().unwrap();
        let mtime = mtime.duration_since(UNIX_EPOCH).unwrap();
        self.sha.update(mtime.as_nanos().to_le_bytes());
    }

    fn finalize(self) -> (Vec<u8>, String) {
        let digest = self.sha.finalize();
        let digest_hex: String = digest
            .as_slice()
            .iter()
            .map(|x| format!("{:02x}", x))
            .collect();
        (digest.to_vec(), digest_hex)
    }
}

fn compute_hash(src_path: &str, inc_path: &str, args: &[&str]) -> (Vec<u8>, String) {
    let mut hasher = Hasher::new();
    hasher.add_args(args);
    hasher.add_mtime(src_path);
    let inc_path = Path::new(inc_path).join("*.h");
    let inc_path = inc_path.display().to_string();
    for header in glob::glob(&inc_path).unwrap() {
        hasher.add_mtime(header.unwrap());
    }
    hasher.finalize()
}
