// Copyright 2023 RISC Zero, Inc.
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
        // Copy fib ID and receipt binary files to the out directory to be used also.
        for &file in ["src/fib_id.bin", "src/fib_receipt.bin"].iter() {
            if let Ok(_) = File::open(file) {
                let in_file_path = Path::new(file);
                let out_file_path = Path::new(&out_dir).join(in_file_path.file_name().unwrap());
                std::fs::copy(in_file_path, out_file_path).unwrap();
            }
        }

        let content = std::fs::read(RECEIPTS).unwrap();
        std::fs::write(path, content).unwrap();
    } else {
        std::fs::write(
            path,
            r##"
pub const FIB_ID: [u8; 32] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
pub const FIB_RECEIPT: &[u8] = &[];
                "##,
        )
        .unwrap();
    }
    println!("cargo:rerun-if-changed={RECEIPTS}");
}
