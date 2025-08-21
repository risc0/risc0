// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! Creates RISC Zero ImageIDs from ELF files.
//!
//! A simple command line tool for creating ImageIDs from RISC-V ELF files.
//! It is intended for basic, low-level use cases.
//! In particular, users looking to create ImageIDs for Rust code are advised
//! to instead use the [`risc0-build`](https://crates.io/crates/risc0-build) crate.
//! Visit our [RISC Zero Rust Starter
//! repository](https://github.com/risc0/risc0-rust-starter) for help getting
//! started.

use clap::Parser;
use risc0_binfmt::ProgramBinary;

/// Generates an ImageID for a given RISC-V user ELF and kernel ELF binary.
#[derive(Parser)]
#[command(about, version, author)]
struct Args {
    /// The user ELF to compute an ImageID from.
    user_elf: String,

    /// The kernel ELF to compute an ImageID from.
    kernel_elf: String,

    /// The resulting ImageID file.
    out: String,
}

fn main() {
    let args = Args::parse();
    let user_elf = std::fs::read(args.user_elf).unwrap();
    let kernel_elf = std::fs::read(args.kernel_elf).unwrap();
    let image_id = ProgramBinary::new(&user_elf, &kernel_elf)
        .compute_image_id()
        .unwrap();
    std::fs::write(args.out, image_id.as_bytes()).unwrap();
}
