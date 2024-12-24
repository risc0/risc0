# rzup

`rzup` is a tool for managing RISC Zero toolchain components. It helps you install, update, and switch between different versions of RISC Zero tools.

## Installation

rzup can be installed with:

```sh
curl -L https://risczero.com/install | bash
```

## Commands

### Install

Install RISC Zero components.

```sh
rzup install [OPTIONS] [NAME] [VERSION]
```

Arguments:
- `NAME`: Optional component name to install (e.g., "rust", "cargo-risczero")
- `VERSION`: Optional specific version to install

Options:
- `-f, --force`: Force reinstallation even if already installed

Examples:

```sh
# Install latest versions of all components
rzup install

# Install specific version of cargo-risczero
rzup install cargo-risczero 1.0.0

# Force reinstall latest rust toolchain
rzup install rust --force
```

### Check

Check for available updates to installed components.

```sh
rzup check
```

This command will:
1. Compare installed versions with latest available versions
2. Tell you which components have updates available


### Use

Switch to a specific version of a component.

```sh
rzup use <NAME> <VERSION>
```

Arguments:
- `NAME`: Component name (required)
- `VERSION`: Version to activate (required)

### Show

Display information about installed components and versions.

Example output:

```sh
Installed components:
--------------------

cargo-risczero
* 1.1.0
  1.0.0

rust
* 1.79.0
  1.81.0
```

The `*` indicates the currently active version.

### Uninstall

Remove a specific version of a component.

```sh
rzup uninstall <NAME> <VERSION>
```

Arguments:
- `NAME`: Component name (required)
- `VERSION`: Version to uninstall (required)

## Component Types

rzup manages the following components:

1. **rust**: The RISC Zero Rust toolchain
   - Rust compiler and tools optimized for the RISC Zero zkVM

2. **cargo-risczero**: The RISC Zero Cargo extension
   - Provides cargo subcommands for RISC Zero development

## Configuration

rzup stores its installations in:
- Default: Linux/macOS: `$HOME/.risc0/`
- Custom: Set with the `RISC0_HOME` environment variable

