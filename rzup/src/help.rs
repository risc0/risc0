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
    rzup installs The RISC Zero zero-knowledge virtual-machine and
    its tooling from the official release channels, enabling you to
    easily switch toolchains and extension versions and keep them
    updated.";

pub static INSTALL_HELP: &str = r"Discussion:
    Installs the latest version of RISC Zero Rust toolchain and
    the cargo-risczero extension.

    This command is hidden by default and meant to bootstrap new
    installations.";

pub static SHOW_HELP: &str = r"Discussion:
    Shows the name of the active RISC Zero toolchain, extension,
    and the version of zkVM's `rustc`.

    If there are multiple toolchains installed then all installed
    toolchains are listed as well.";

pub static UPDATE_HELP: &str = r"Discussion:
    Checks RISC Zero release channels for updates and applies the
    updates for both toolchains and extensions.";

pub static SHOW_ACTIVE_TOOLCHAIN_HELP: &str = r"Discussion:
    Shows the name of the active RISC Zero toolchain.

    This is useful for figuring out the active RISC Zero toolchain.
    The toolchain is aliased as 'risc0' in the rustup toolchains.";
