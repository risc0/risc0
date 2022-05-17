fn main() {
    risc0_build::methods("inner", &["fail", "io", "sha_accel", "sha"]);
}
