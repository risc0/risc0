// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{fs, path::PathBuf, process::Command};

fn cpp_toolchain() -> PathBuf {
    let rzup = rzup::Rzup::new().unwrap();
    let Some((version, path)) = rzup
        .get_default_version(&rzup::Component::CppToolchain)
        .unwrap()
    else {
        panic!("Risc Zero C++ toolchain not found. Try running `rzup install cpp`");
    };
    println!("Using C++ toolchain version {version}");
    path
}

fn rust_toolchain() -> PathBuf {
    let rzup = rzup::Rzup::new().unwrap();
    let Some((version, path)) = rzup
        .get_default_version(&rzup::Component::RustToolchain)
        .unwrap()
    else {
        panic!("Risc Zero Rust toolchain not found. Try running `rzup install rust`");
    };
    println!("Using Rust toolchain version {version}");
    path
}

fn main() {
    if std::env::var("RISC0_SKIP_BUILD").is_ok() {
        return;
    }

    let gcc_path = cpp_toolchain().join("bin/riscv32-unknown-elf-gcc");

    let guest_dir = fs::canonicalize(env!("CARGO_MANIFEST_DIR"))
        .unwrap()
        // Go back a directory from `./host`
        .parent()
        .unwrap()
        // Use guest directory.
        .join("guest");

    println!("cargo:rerun-if-changed={}", guest_dir.display());

    // Build static lib of platform to link against.
    let cargo = rust_toolchain().join("bin/cargo");
    Command::new(cargo)
        .args([
            "rustc",
            "-p",
            "zkvm-platform",
            "--target",
            "riscv32im-risc0-zkvm-elf",
            "--lib",
            "--crate-type",
            "staticlib",
            "--release",
        ])
        .arg("--target-dir")
        .arg(guest_dir.join("out").join("platform"))
        .status()
        .unwrap();

    // Build the C code using gcc
    Command::new(gcc_path)
        .arg("-nostartfiles")
        .arg(guest_dir.join("main.c"))
        .arg("-o")
        .arg(guest_dir.join("out").join("main"))
        .arg(format!(
            "-L{}",
            guest_dir
                .join("out")
                .join("platform")
                .join("riscv32im-risc0-zkvm-elf")
                .join("release")
                .display()
        ))
        .arg("-lzkvm_platform")
        .arg("-T")
        .arg(guest_dir.join("riscv32im-risc0-zkvm-elf.ld"))
        .status()
        .unwrap();
}
