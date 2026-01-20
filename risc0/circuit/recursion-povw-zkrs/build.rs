// Copyright 2026 RISC Zero, Inc.
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

fn main() {
    generate_zkr_table();
}

/// The crates.io upload limit is 10mb. Give ourselves 4k of overhead for other files cargo adds.
const UPLOAD_LIMIT: u64 = (10 * 1024 * 1024) - 4 * 1024;

const SOURCE_FILES: [&str; 3] = ["build.rs", "src/lib.rs", "Cargo.toml"];

fn source_files_size() -> u64 {
    SOURCE_FILES
        .into_iter()
        .map(|f| std::fs::File::open(f).unwrap().metadata().unwrap().len())
        .sum()
}

fn generate_zkr_table() {
    use std::fmt::Write as _;
    use std::path::Path;

    use liblzma::read::XzDecoder;

    let mut output = String::new();

    writeln!(&mut output, "pub const ZKRS: &[(&[u8], usize, &str)] = &[").unwrap();

    let mut total_bytes = 0;

    for po2 in 12..=24 {
        let zkr_name = format!("lift_rv32im_m3_povw_{po2}.zkr");
        let zkr_path = Path::new("src")
            .join(format!("{zkr_name}.xz"))
            .canonicalize()
            .unwrap();
        println!("cargo:rerun-if-changed={}", zkr_path.display());

        let f = std::fs::File::open(&zkr_path).unwrap();
        total_bytes += f.metadata().unwrap().len();
        let mut decoder = XzDecoder::new(f);
        std::io::copy(&mut decoder, &mut std::io::sink()).unwrap();
        let size = decoder.total_out();

        writeln!(
            &mut output,
            "(include_bytes!(\"{}\"), {size}, \"{zkr_name}\"),",
            zkr_path.display()
        )
        .unwrap();
    }

    total_bytes += source_files_size();

    if total_bytes > UPLOAD_LIMIT {
        panic!("ZKRs are too big for uploading to crates.io ({total_bytes} > {UPLOAD_LIMIT})");
    }

    writeln!(&mut output, "];").unwrap();

    let out_dir = std::env::var_os("OUT_DIR").unwrap();
    std::fs::write(Path::new(&out_dir).join("zkr_table.rs"), &output).unwrap();
}
