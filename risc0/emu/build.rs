fn main() {
    cc::Build::new().file("src/x64/asm.S").compile("jit_x64");

    println!("cargo:rerun-if-changed=src/x64/asm.S");
}
