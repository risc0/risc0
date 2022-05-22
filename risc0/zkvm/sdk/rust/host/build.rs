fn main() {
    println!("cargo:rustc-link-lib=static=tbb");
    println!("cargo:rustc-link-lib=static=risc0-core-sys");
    println!("cargo:rustc-link-lib=static=risc0-zkp-sys");
    println!("cargo:rustc-link-lib=static=risc0-zkvm-sys");
}
