# cargo-risczero

Cargo extension to help create, manage, and test [RISC Zero][risc-zero]
projects. The default template generated from the `cargo risczero new` command
supports both local and remote proving. Refer to the README in [the rust-starter
template][rust-starter] for more information.

## Installation

To install this Cargo subcommand, first you'll want to [install
Rust][install-rust] and then you'll execute:

```bash
curl -L https://risczero.com/install | bash
rzup install
```

To install from local source, use:

```bash
cargo install --path risc0/cargo-risczero
```

After that you can verify it works via:

```bash
cargo risczero --version
```

### Docker

In order to use the `build` command, you will need `docker` available in your
PATH. For developer machines, this is simple with [Docker
Desktop.](https://docs.docker.com/desktop/)

## `install`

The `install` command installs the latest RISC Zero toolchain. This toolchain is
needed to compile guest programs into ELF binaries that the zkVM can execute.

```bash
rzup install
```

You can verify it was installed correctly by running:

```bash
rustup toolchain list --verbose | grep risc0
```

Note that the following pre-built host targets are available:

- `aarch64-apple-darwin`
- `x86_64-unknown-linux-gnu`

If you'd like to install the toolchain on a host not listed above, you can use
the `build-toolchain` command to build the toolchain locally.

## `new`

The `new` command will create a new project from an existing template. It
defaults to the [rust-starter template][rust-starter] but can be used with other
templates locally or hosted on github.

### Examples

```bash
# Create a project from the main template
cargo risczero new my_project

# Create a project with 'no_std' in the guest
cargo risczero new my_project --no-std

# Disable git initialization
cargo risczero new my_project --no-git

# Create from github template
cargo risczero new my_project --template https://github.com/risc0/risc0-rust-starter
```

## `build-toolchain`

Use the `build-toolchain` command to build the toolchain locally for your host.
Warning: this may take a long time. The resulting toolchain will be
automatically installed via `rustup toolchain link`.

## `build`

Use the `build` command to build guest code for the zkVM target
`riscv32im-risc0-zkvm-elf` deterministically.

The compiled ELF is saved in: `./target/riscv-guest/riscv32im-risc0-zkvm-elf/docker/`

With this containerized build process, we ensure that all builds of your guest
code, regardless of the machine or local environment, will produce the same
ImageID. The ImageID, and its importance to
[security,](https://dev.risczero.com/faq#security) is explained in more detail
in our [developer FAQ.](https://dev.risczero.com/faq#zkvm-application-design)

Note: The build command requires the docker CLI installed and in your PATH.

### Example

```bash
# Build the zkVM's test examples
cargo risczero build --manifest-path risc0/zkvm/methods/guest/Cargo.toml

ELFs ready at:
ImageID: 417778745b43c82a20db33a55c2b1d6e0805e0fa7eec80c9654e7321121e97af - "target/riscv-guest/riscv32im-risc0-zkvm-elf/docker/risc0_zkvm_methods_guest/multi_test"
ImageID: c7c399c25ecf26b79e987ed060efce1f0836a594ad1059b138b6ed2f123dad38 - "target/riscv-guest/riscv32im-risc0-zkvm-elf/docker/risc0_zkvm_methods_guest/hello_commit"
ImageID: a51a4b747f18b7e5f36a016bdd6f885e8293dbfca2759d6667a6df8edd5f2489 - "target/riscv-guest/riscv32im-risc0-zkvm-elf/docker/risc0_zkvm_methods_guest/slice_io"
```

## datasheet

The `datasheet` command performs a benchmark to evaluate zkVM performance for
the current machine's hardware, and then prints a table (along with optional
`--json` output).

Schema:

```ts
type Datasheet = BenchmarkData[]

type BenchmarkData = {
    name: string,
    hashfn: string,
    throughput: number,
    duration: number,
    cycles: number,
    seal: number,
}
```

[install-rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[risc-zero]: https://risczero.com
[rust-starter]: https://github.com/risc0/risc0/tree/main/risc0/cargo-risczero/templates/rust-starter
