// Copyright 2025 RISC Zero, Inc.
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
