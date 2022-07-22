# risc0-build

Build RISC Zero zkVM guest code and provide handles to the host side

In order for the host to execute guest code in the [RISC Zero zkVM](risc0_zkvm), the host must be provided an ELF file with RISC-V source code and the corresponding [MethodID](risc0_zkvm::host::MethodId). This crate contains the functions needed to take zkVM guest code written in rust, build a corresponding ELF file and MethodID, and make the MethodID and a path to the ELF file available for the host to use.

## Using risc0-build to build guest methods

Using this crate can be a bit delicate, so we encourage you to follow along in our [Risc Zero Rust Starter repository](https://github.com/risc0/risc0-rust-starter). In that repo, `risc0-build` is used in the [`methods` directory](https://github.com/risc0/risc0-rust-starter/tree/main/methods).

Guest methods are embedded for the host to use by calling [embed_methods] (or [embed_methods_with_options]) in a [build script](https://doc.rust-lang.org/cargo/reference/build-scripts.html). An example `build.rs` file would look like
```
fn main() {
    risc0_build::embed_methods();
}
```

This requires including `risc0-build` as a _build_ dependency. You will also need add a `[package.metadata.risc0]` section to your cargo file. In this section, put a `methods` field with a list of relative paths containing the guest code. For example, if your guest code is in the `guest` directory, then `Cargo.toml` might include
```
[build-dependencies]
risc0-build = "0.10"

[package.metadata.risc0]
methods = ["guest"]
```

This builds a file `methods.rs` in your cargo output directory which you must then include for the host to use. For example, you might make a file `src/lib.rs` containing
```
include!(concat!(env!("OUT_DIR"), "/methods.rs"));
```

Inside the guest code directory (so `guest` in the above example), you must again create a [build script](https://doc.rust-lang.org/cargo/reference/build-scripts.html), this time calling [link] to link the embedded methods into the generated `methods.rs` build file. An example `build.rs` file for this is
```
fn main() {
    risc0_build::link();
}
```

Since you are again using `risc0-build` as a build script, remember to include it as a build dependency here just like before:
```
[build-dependencies]
risc0-build = "0.10"
```

Don't forget to include your guest code as well! (If you're following the [starter repository](https://github.com/risc0/risc0-rust-starter) example, it's in `src/build`.)
