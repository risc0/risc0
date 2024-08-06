// Copyright 2024 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

pub static RZUP_HELP: &str = r"Discussion:
    rzup installs RISC Zero toolchains and extensions from the official
    release channels, enabling you to easily switch between different
    versions and keep them updated.

    If you are new to RISC Zero, consider visitng our documentation
    to learn more.";

pub static SHOW_HELP: &str = r"Discussion:
    Shows the name of the active extension, and toolchains.

    If there are multiple toolchains installed then all installed
    toolchains are listed as well.";

pub static UPDATE_HELP: &str = r"Discussion:
    With no toolchain or extension specified, the `update` command
    updates each of the installed toolchains from the release channels.

    If given a toolchain or extension argument then `update` updates
    that, the same as `rzup extension/toolchain install`.";

pub static INSTALL_HELP: &str = r"Discussion:
    With no toolchain or extension specified, the `install` command
    installs the default RISC Zero installation from the release channels.

    If given a toolchain or extension argument then `install` installs the
    specified toolchain or extension.";

pub static DEFAULT_HELP: &str = r"Discussion:
    Sets the default (active) toolchain to the specified toolchain.

    `default` uses Rustup and symlinks to set the toolchain to known toolchain
    paths.";

pub static R0VM_HELP: &str = r"Discussion:
    The `cargo-risczero` command manages the `cargo-risczero` utility.
    You can list, install, use, and uninstall `cargo-risczero`.";

pub static CHECK_HELP: &str = r"Discussion:
    The `check` command checks if there are any updates available for the active
    RISC Zero toolchains and extensions. It compares the active installed versions
    with the latest available versions from the release channels and informs you if
    updates are needed.

    For more information on your installed toolchains or extensions, consider running
    `rzup toolchain list` or `rzup extension list`.";

pub static TOOLCHAIN_HELP: &str = r"Discussion:
    The `toolchain` command allows you to manage RISC Zero toolchains. You can list
    installed toolchains, install new toolchains, uninstall existing ones, or build
    toolchains from source.

    For more information on each subcommand, you can use `--help` with the specific
    subcommand.";
