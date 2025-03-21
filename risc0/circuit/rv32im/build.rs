fn main() {
    println!("cargo::rustc-link-arg=-L/tmp/qemu-build");
    println!("cargo::rustc-link-arg=-lqemu-riscv32-r0vm");
    println!("cargo::rustc-link-arg=-lglib-2.0");
    println!("cargo::rustc-link-arg=-lm");
    println!("cargo::rustc-link-arg=-lz");
    println!("cargo::rerun-if-changed=/tmp/qemu-build/libqemu-riscv32-r0vm.a");
}
