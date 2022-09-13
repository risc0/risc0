fn main() {
    if std::env::var("CARGO_CFG_TARGET_ARCH").unwrap() != "riscv32" {
        println!("cargo:rustc-link-lib=static=tbb");
        println!("cargo:rustc-link-lib=static=risc0-core-sys");
        println!("cargo:rustc-link-lib=static=risc0-zkp-sys");
        println!("cargo:rustc-link-lib=static=risc0-zkvm-sys");
    }

    #[cfg(feature = "profiler")]
    {
        std::env::set_var("PROTOC", protobuf_src::protoc());
        prost_build::compile_protos(&["src/host/profile.proto"], &["src/host/"]).unwrap();
    }
}
