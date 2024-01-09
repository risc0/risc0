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
