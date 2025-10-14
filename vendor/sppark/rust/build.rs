// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0


#[cfg(feature = "build")]
fn main() {
}

#[cfg(not(feature = "build"))]
fn main() {
    use std::env;
    use std::path::PathBuf;
    use std::process::Command;

    let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    let mut base_dir = manifest_dir.join("sppark");
    if !base_dir.exists() {
        // Reach out to .., which is the root of the sppark repo.
        // Use an absolute path to avoid issues with relative paths
        // being treated as strings by `cc` and getting concatenated
        // in ways that reach out of the OUT_DIR.
        base_dir = manifest_dir
            .parent()
            .expect("can't access parent of current directory")
            .into();
        println!(
            "cargo:rerun-if-changed={}",
            base_dir.join("ec").to_string_lossy()
        );
        println!(
            "cargo:rerun-if-changed={}",
            base_dir.join("ff").to_string_lossy()
        );
        println!(
            "cargo:rerun-if-changed={}",
            base_dir.join("ntt").to_string_lossy()
        );
        println!(
            "cargo:rerun-if-changed={}",
            base_dir.join("msm").to_string_lossy()
        );
        println!(
            "cargo:rerun-if-changed={}",
            base_dir.join("util").to_string_lossy()
        );
    }
    // pass DEP_SPPARK_* variables to dependents
    println!("cargo:ROOT={}", base_dir.to_string_lossy());

    let all_gpus = base_dir.join("util/all_gpus.cpp");

    println!("cargo:rerun-if-env-changed=NVCC");
    let mut nvcc = match env::var("NVCC") {
        Ok(var) => which::which(var),
        Err(_) => which::which("nvcc"),
    };

    println!("cargo:rerun-if-env-changed=HIPCC");
    let mut hipcc = match env::var("HIPCC") {
        Ok(var) => which::which(var),
        Err(_) => which::which("hipcc"),
    };

    match (cfg!(feature = "cuda"), cfg!(feature = "rocm")) {
        (true, true) => panic!("mutually exclusive features"),
        (true, false) => {
            if nvcc.is_err() {
                panic!("`nvcc` is not available");
            }
            hipcc = Err(which::Error::CannotFindBinaryPath);
        },
        (false, true) => {
            if hipcc.is_err() {
                panic!("`hipcc` is not available");
            }
            nvcc = Err(which::Error::CannotFindBinaryPath);
        },
        (false, false) => (),
    }

    // Detect if there is CUDA compiler and engage "cuda" feature accordingly,
    // even if there is no Nvidia card, but unless there is ROCm compiler.
    // In other words if you have both Nvidia and AMD cards installed, Nvidia
    // will be preferred. To suppress it, set the NVCC environment variable
    // to "off" [or engage "rocm" feature].
    if let Ok(nvcc) = nvcc {
        let cuda_version = Command::new(nvcc)
            .arg("--version")
            .output()
            .expect("impossible");
        if !cuda_version.status.success() {
            panic!("{:?}", cuda_version);
        }
        let cuda_version = String::from_utf8(cuda_version.stdout).unwrap();
        let x = cuda_version
            .find("release ")
            .expect("can't find \"release X.Y,\" in --version output")
            + 8;
        let y = cuda_version[x..]
            .find(",")
            .expect("can't parse \"release X.Y,\" in --version output");
        let v = cuda_version[x..x + y].parse::<f32>().unwrap();
        if v < 11.4 {
            panic!("Unsupported CUDA version {} < 11.4", v);
        }

        let cuda_available = env::var_os("OUT_DIR")
            .map(PathBuf::from)
            .map(|p| p.join("cuda_available"))
            .map(|mut p| {
                p.set_extension(env::consts::EXE_EXTENSION);
                p
            })
            .expect("$OUT_DIR is not set");

        let mut nvcc = cc::Build::new();
        nvcc.cuda(true);

        let _ = nvcc
            .get_compiler()
            .to_command()
            .arg("src/cuda_available.cpp")
            .arg("-o")
            .arg(&cuda_available)
            .status()
            .expect("impossible");

        let cuda_available = Command::new(cuda_available).status().expect("impossible");

        if cuda_available.success() || hipcc.is_err() {
            nvcc.include(&base_dir);
            nvcc.file(&all_gpus)
                .compile("sppark_cuda");
            println!("cargo:rustc-cfg=feature=\"cuda\"");
            println!("cargo:TARGET=cuda");
            return;
        }
    }

    // Detect if there is ROCm compiler and engage "rocm" feature accordingly
    if let Ok(hipcc) = hipcc {
        env::set_var("HIP_PLATFORM", "amd");

        let hipcc_version = Command::new(&hipcc)
            .arg("--version")
            .output()
            .expect("impossible");
        if !hipcc_version.status.success() {
            panic!("{:?}", hipcc_version);
        }
        let hipcc_version = String::from_utf8(hipcc_version.stdout).unwrap();

        let v = hipcc_version
            .find("HIP version: ")
            .expect(format!("{:?} is not a HIP compiler", hipcc).as_str())
            + 13;
        let mut w = hipcc_version[v..]
            .find(|c: char| !c.is_digit(10))
            .expect("can't parse \"HIP version: \" in `hipcc --version`");
        w = w + 1 + hipcc_version[v + w + 1..]
            .find(|c: char| !c.is_digit(10))
            .expect("can't parse \"HIP version: \" in `hipcc --version`");
        let ver = hipcc_version[v..v + w].parse::<f32>().unwrap();
        if ver < 5.7 {
            panic!("Unsupported HIP version {} < 5.7", ver);
        }

        let x = hipcc_version
            .find("InstalledDir: ")
            .expect("can't find \"InstalledDir:\" in `hipcc --version`")
            + 14;
        let y = hipcc_version[x..]
            .find(char::is_control)
            .expect("can't parse \"InstalledDir:\" in `hipcc --version`");

        let mut libpath: PathBuf = hipcc_version[x..x + y].into();

        while libpath.pop() {
            if libpath
                .join("lib")
                .join(if cfg!(unix) {
                    "libamdhip64.so"
                } else {
                    "amdhip64.lib"
                })
                .try_exists()
                .is_ok_and(|exists| exists)
            {
                libpath.push("lib");
                break;
            }
        }

        let mut ccmd = cc::Build::new();
        ccmd.compiler(hipcc);
        ccmd.cpp(true);
        ccmd.include(&base_dir);
        ccmd.flag("-include").flag("util/cuda2hip.hpp");
        ccmd.file(&all_gpus)
            .compile("sppark_rocm");
        println!("cargo:rustc-cfg=feature=\"rocm\"");

        if libpath.parent().is_some() {
            // If libpath is invalid, it's on user to specify one by
            // passing it through RUSTFLAGS environment variable.
            println!(
                "cargo:rustc-link-search=native={}",
                libpath.to_string_lossy()
            );
        }
        println!("cargo:rustc-link-lib=amdhip64");
        println!("cargo:TARGET=rocm");
    }
}
