# `rzup`

Install, update, or revert to a specific RISC Zero version.

## Install

```sh
curl -L https://risczero.com/install | bash
```

## Usage

To install the latest RISC Zero release version:

```sh
rzup install
```

Optionally, you can specify which version of `cargo-risczero` to install with:

```bash
rzup install cargo-risczero $VERSION
```

Where the `$VERSION` is a [release tag](https://github.com/risc0/risc0/releases) (e.g `v1.1.1`).

To enable verbose installation logs:

```sh
rzup --verbose install
```

To view usage/help information:

```sh
rzup --help
```

***

**Tip**: Most flags have a single-character shorthand. See `rzup -h` for more information.
