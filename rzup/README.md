# `rzup`

Install, manage, and build RISC Zero tooling.

## Quick Start

Install `rzup`:

```sh
curl -L https://risczero.com/install | bash
```

You may need to source your PATH for non-interactive shells (i.e. docker).

## Usage

### Installation

Install the default RISC Zero suite (`cargo-risczero`, `r0vm`, and toolchains).
```sh
rzup install
```

Install a specific extension version:

```sh
rzup extension install <EXTENSION> [VERSION]
```
`<EXTENSION>` is a supported extension (e.g. `cargo-risczero`).


`[VERSION]` optionally specifies an extension [release tag](https://github.com/risc0/risc0/releases) (e.g., `v1.0.0`).

Install a specific toolchain:

```sh
rzup toolchain install <TOOLCHAIN> [VERSION]
```
`<TOOLCHAIN>` is a supported toolchain (e.g. `rust`, `cpp`, etc.).

`[VERSION]` optionally specifies a toolchain [release tag](https://github.com/risc0/rust/releases/tag/r0.1.81.0) (e.g., `r0.1.81.0`).
### Updating

To check for updates:

```sh
rzup check
```

Update to latest release:

```sh
rzup update
```

See `update -h` for more options.

### Build

Build from source:

```sh
rzup extension build <EXTENSION> [TAG]
rzup toolchain build <TOOLCHAIN> [TAG]
```

`[TAG]` optionally specifies a git tag/commit. Uses default branch if unspecified.
Built artifacts are automatically installed.

### Misc.

Update `rzup`:

```sh
rzup self update
```

Show active installations:

```sh
rzup show
```

Enable verbose logging:

```sh
rzup --verbose <COMMAND>
```

Show help:

```sh
rzup --help
```

***
**Tip**: Most subcommands have a single-character shorthand. See `rzup -h`.

