# `rzup`

Install, update, or revert to a specific RISC Zero version.

## Install

```sh
curl -L https://raw.githubusercontent.com/risc0/risc0/main/rzup/install | bash
```

## Usage

To install the latest RISC Zero release version:

```sh
rzup
```

To install a specific release version:

```sh
rzup --version <VERSION>
```

Where `VERSION` can be replaced with specified RISC Zero release (e.g., `1.0.0-rc.3`). See our [releases](https://github.com/risc0/risc0/releases) for more information.


To enable verbose installation logs:
```sh
rzup --verbose
```

To view usage/help information:

```sh
rzup --help
```

---
**Tip**: Most flags have a single character shorthand. See `rzup -h` for more information.
