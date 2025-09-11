// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{env, fs::File, path::Path};

fn main() {
    const RECEIPTS: &str = "src/receipts.rs";

    let out_dir = env::var_os("OUT_DIR").unwrap();
    let path = Path::new(&out_dir).join("lib.rs");

    if File::open(RECEIPTS).is_ok() {
        let content = std::fs::read(RECEIPTS).unwrap();
        std::fs::write(path, content).unwrap();
    } else {
        std::fs::write(
            path,
            r##"
pub const FIB_ID: [u32; 8] = [0, 0, 0, 0, 0, 0, 0, 0];
pub const FIB_RECEIPT: &[u8] = &[];
                "##,
        )
        .unwrap();
    }
    println!("cargo:rerun-if-changed={RECEIPTS}");
}
