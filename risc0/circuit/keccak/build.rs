// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#[cfg(feature = "prove")]
fn generate_zkr_table() {
    use std::fmt::Write as _;
    use std::path::Path;

    use liblzma::read::XzDecoder;

    let mut output = String::new();

    writeln!(&mut output, "const ZKRS: &[(&[u8], usize)] = &[").unwrap();

    // Pre-calculate the sizes of these to help make decoding faster later. This is a bit
    // quick-and-dirty, probably better to invent some way for zirgen bootstrap to save this
    // information.
    for po2 in 14..=18 {
        let zkr_name = format!("keccak_lift_{po2}.zkr.xz");
        let zkr_path = std::fs::canonicalize(Path::new("src/prove").join(&zkr_name)).unwrap();
        println!("cargo:rerun-if-changed={}", zkr_path.display());
        let mut decoder = XzDecoder::new(std::fs::File::open(&zkr_path).unwrap());
        std::io::copy(&mut decoder, &mut std::io::sink()).unwrap();
        let size = decoder.total_out();
        writeln!(
            &mut output,
            "(include_bytes!(\"{}\"), {size}),",
            zkr_path.display()
        )
        .unwrap();
    }
    writeln!(&mut output, "];").unwrap();

    let out_dir = std::env::var_os("OUT_DIR").unwrap();
    std::fs::write(Path::new(&out_dir).join("zkr_table.rs"), &output).unwrap();
}

fn main() {
    #[cfg(feature = "prove")]
    generate_zkr_table();
}
