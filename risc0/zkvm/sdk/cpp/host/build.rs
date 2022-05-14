use cxx_build::CFG;

fn main() {
    CFG.include_prefix = "risc0/zkvm/sdk/cpp/host";

    cxx_build::bridge("src/lib.rs")
        .file("c_api.cpp")
        .file("receipt.cpp")
        .flag_if_supported("/std:c++17")
        .flag_if_supported("-std=c++17")
        .warnings(false)
        .compile("risc0-zkvm-host-sys");

    println!("cargo:rustc-link-lib=static=tbb");
    println!("cargo:rustc-link-lib=static=risc0-core");
    println!("cargo:rustc-link-lib=static=risc0-zkp-core");
    println!("cargo:rustc-link-lib=static=risc0-zkp-accel");
    println!("cargo:rustc-link-lib=static=risc0-zkp-prove");
    println!("cargo:rustc-link-lib=static=risc0-zkp-verify");
    println!("cargo:rustc-link-lib=static=risc0-zkvm-prove");
    println!("cargo:rustc-link-lib=static=risc0-zkvm-verify");
}
