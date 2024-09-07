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

To install a specific release version:

```sh
rzup install --version <VERSION>
```

Where `VERSION` can be replaced with a specified RISC Zero release (e.g.,
`1.0.0`). See our [releases](https://github.com/risc0/risc0/releases) for more
information.

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
