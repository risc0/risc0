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
}
