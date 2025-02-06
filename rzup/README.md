# rzup

`rzup` is a tool for managing RISC Zero toolchain components. It helps you install, update, and switch between different versions of RISC Zero tools.

## Installation

`rzup` can be installed with:

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

- `NAME`: (Optional) component name to install (e.g., "rust", "cargo-risczero")
- `VERSION`: (Optional) Version to install. If no version is specified, it will use the latest release version.

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

### Update

Update your RISC Zero installation.

```sh
# Update to latest versions of all components
rzup update
```

_Note:_ `update` is an alias to `install`.

### Check

Check for available updates of installed components.

```sh
rzup check
```

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

The `*` indicates the current default version.

### Uninstall

Remove a specific version of a component.

```sh
rzup uninstall <NAME> <VERSION>
```

Arguments:

- `NAME`: Component name (required)
- `VERSION`: Version to uninstall (required)

### Build

Build a particular component from source.

```sh
rzup build <NAME> <COMMIT-OR-TAG>
```

Right now this command only supports building the Rust toolchain.

Downloads the source code for the given component from GitHub, builds it, installs it, and makes it
the default version.

The resulting version of the component will contain the commit hash.

## Components

rzup manages the following components:

1. **rust**: The RISC Zero Rust toolchain
   - Rust compiler and tools optimized for the RISC Zero zkVM

2. **cpp**: The RISC Zero C++ toolchain
   - The C++ compiler and tools optimized for the RISC Zero zkVM

3. **cargo-risczero**: The RISC Zero Cargo extension
   - Provides cargo subcommands for RISC Zero development

4. **r0vm**: The RISC Zero zkVM
    - Precompiled version of the RISC Zero zkVM

## Configuration

rzup stores its installations in:

- Default: Linux/macOS: `$HOME/.risc0/`
- Custom: Set with the `RISC0_HOME` environment variable

When communicating with GitHub, it tries using authentication. This can be useful to get around
rate-limiting. It attempts to get a token from the `GITHUB_TOKEN` environment variable, then from
~/.config/gh/hosts.yml.
