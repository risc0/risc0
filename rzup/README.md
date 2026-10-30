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

### Default

Set the default version of a component. The version must already be installed.

```sh
rzup default <NAME> <VERSION>
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

Components published with `rzup publish` (currently `risc0-groth16`) are downloaded from
`https://artifacts.risczero.net`. Set `RZUP_DOWNLOAD_URL` to download them from somewhere else, for
example a staging copy of the bucket; the component manifest is signature-checked wherever it comes
from.

### publish

rzup downloads components from both GitHub releases and the artifacts bucket. The publish command
is for uploading new components to the bucket.

It stores the components under `rzup/components/<component-name>/` in the bucket.

#### create-artifact

To publish an artifact as a component, first an artifact must be created. A valid artifact is just a
.tar.xz file.

To create an artifact, `publish create-artifact` can be used like
```bash
rzup publish create-artifact --input <directory-path> --output <output>.tar.xz
```

This command creates a .tar.xz file but uses parallel compression and displays a progress bar. This
command doesn't have to be used, but is provided for convenience.

#### upload

To upload an artifact to the bucket as a component, `publish upload` can be used like
```bash
rzup publish upload (--target-agnostic|--target <target-triple>) <component-name> <version> <artifact>.tar.xz
```

This command needs these environment variables:

- `RZUP_PUBLISH_URL`: the S3 API URL of the bucket, including the bucket name, for example
  `https://<account-id>.r2.cloudflarestorage.com/risc0-artifacts`. Uploads cannot go through the
  download hostname.
- `AWS_ACCESS_KEY_ID` and `AWS_SECRET_ACCESS_KEY`: an S3 API token for that bucket. Requests are
  signed with SigV4 and region `auto`.
- `RZUP_PUBLISH_KEY`: the PEM-encoded private key that signs the component manifest.

It reads the current manifest from the download URL (`RZUP_DOWNLOAD_URL`), uploads the artifact,
and uploads the updated, signed manifest. To rehearse against a scratch bucket, point both URLs at
it.

If `--target-agnostic` flag is given, the artifact will be used for all targets, otherwise `--target
<target-triple>` must be used to mark which target the artifact should be used for (e.g.
aarch64-apple-darwin, or x86_64-unknown-linux-gnu)

Uploads are signed with the private key in `RZUP_PUBLISH_KEY`; rzup verifies manifests with the
matching public key built into it.

#### set-latest
The published component metadata includes information about what component version is the latest
version. (This is the version that rzup will download by default.) To update what this version is,
the `set-latest` command can be used.

```bash
rzup publish set-latest <component> 1.2.3
```
