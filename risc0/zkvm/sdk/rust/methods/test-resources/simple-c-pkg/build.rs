use risc0_zkvm::build::rcc::Build;

fn main() {
    Build::new()
        .compiler("/usr/bin/clang")
        .include("depend/foo_dev.h")
        .file("src/foo_dev.c")
        .compile("foo_dev");

    Build::new()
        .compiler("/usr/bin/clang")
        .include("depend/foo_rel.h")
        .file("src/foo_rel.c")
        .release(true)
        .compile("foo_rel");
}
