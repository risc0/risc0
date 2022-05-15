fn main() {
    println!("cargo:rustc-link-lib=static=tbb");
    println!("cargo:rustc-link-lib=static=risc0-core");
    println!("cargo:rustc-link-lib=static=risc0-zkp-core");
    println!("cargo:rustc-link-lib=static=risc0-zkp-accel");
    println!("cargo:rustc-link-lib=static=risc0-zkp-prove");
    println!("cargo:rustc-link-lib=static=risc0-zkp-verify");
    println!("cargo:rustc-link-lib=static=risc0-zkvm-prove");
    println!("cargo:rustc-link-lib=static=risc0-zkvm-verify");
    println!("cargo:rustc-link-lib=static=risc0-zkvm-host-sys");
}
