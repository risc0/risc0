Build RISC Zero zkVM guest code and provide handles to the host side.

In order for the host to execute guest code in the [RISC Zero
zkVM](https://docs.rs/risc0-zkvm), the host must be provided a compiled RISC-V
ELF file and the corresponding ImageID. This crate contains the functions needed
to take zkVM guest code, build a corresponding ELF file and ImageID, and make
the ImageID and a path to the ELF file available for the host to use.

## Using `risc0-build` to Build Guest Methods

Using this crate can be a bit delicate, so we encourage you to follow along in
our [RISC Zero Rust Starter
repository](https://github.com/risc0/risc0-rust-starter). In that repository,
`risc0-build` is used in the [`methods`
directory](https://github.com/risc0/risc0-rust-starter/tree/main/methods).

Guest methods are embedded for the host to use by calling
`embed_methods` (or
`embed_methods_with_options`) in a [build
script](https://doc.rust-lang.org/cargo/reference/build-scripts.html). An
example `build.rs` file would look like:

```no_run
fn main() {
    risc0_build::embed_methods();
}
```

This requires including `risc0-build` as a _build_ dependency. You will also
need add a `[package.metadata.risc0]` section to your cargo file. In this
section, put a `methods` field with a list of relative paths containing the
guest code. For example, if your guest code is in the `guest` directory,
then `Cargo.toml` might include:

```toml
[build-dependencies]
risc0-build = "0.17"

[package.metadata.risc0]
methods = ["guest"]
```

This builds a file `methods.rs` in your cargo output directory which you
must then include for the host to use. For example, you might make a file
`src/lib.rs` containing:

```text
include!(concat!(env!("OUT_DIR"), "/methods.rs"));
```

This process will generate an image ID (`*_ID`) and the contents of an ELF
file (`*_ELF`). The names will be derived from the name of the ELF
binary, which will be converted to ALL\_CAPS to comply with Rust naming
conventions. Thus, if a method binary is named `multiply`, the image ID
will be named `methods::MULTIPLY_ID` and the contents of the ELF file will
be named `methods::MULTIPLY_ELF`. These are included at the beginning
of the host-side code:

```text
use methods::{MULTIPLY_ELF, MULTIPLY_ID};
```
