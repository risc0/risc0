// Copyright 2026 RISC Zero, Inc.
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

use std::{fmt::Write as _, fs::File, io::Read as _, path::Path};

use liblzma::write::XzEncoder;

const XZ_COMPRESS_LEVEL: u32 = 3;

const TAR_XZ_PATH: &str = "src/zkrs.tar.xz";

fn main() {
    check_lfs_pointer();
    check_zkr_size();
    build_zkr_table();
}

/// The crates.io upload limit is 10mb. Give ourselves 20k of overhead for other files cargo adds.
const UPLOAD_LIMIT: u64 = (10 * 1024 * 1024) - 20 * 1024;

const SOURCE_FILES: [&str; 3] = ["build.rs", "src/lib.rs", "Cargo.toml"];

fn source_files_size() -> u64 {
    SOURCE_FILES
        .into_iter()
        .map(|f| std::fs::File::open(f).unwrap().metadata().unwrap().len())
        .sum()
}

/// A checkout without git-lfs (including a cargo git dependency) holds a
/// pointer file in place of the tarball.
fn check_lfs_pointer() {
    let mut prefix = [0u8; 32];
    let len = File::open(TAR_XZ_PATH).unwrap().read(&mut prefix).unwrap();
    if prefix[..len].starts_with(b"version https://git-lfs") {
        panic!(
            "{TAR_XZ_PATH} is a git-lfs pointer, not the tarball. \
             Run `git lfs pull`, or depend on this crate from crates.io."
        );
    }
}

fn check_zkr_size() {
    let total_bytes = std::fs::metadata(TAR_XZ_PATH).unwrap().len() + source_files_size();

    if total_bytes > UPLOAD_LIMIT {
        panic!("ZKRs are too big for uploading to crates.io ({total_bytes} > {UPLOAD_LIMIT})");
    }
}

fn build_zkr_table() {
    let mut tar = tar::Archive::new(liblzma::read::XzDecoder::new_parallel(
        std::fs::File::open(TAR_XZ_PATH).unwrap(),
    ));
    println!("cargo:rerun-if-changed={TAR_XZ_PATH}");

    let out_dir_str = std::env::var_os("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir_str);
    let mut output = String::new();

    writeln!(
        &mut output,
        "pub static ZKRS: phf::Map<&'static str, (&'static [u8], usize)> = phf::phf_map! {{"
    )
    .unwrap();

    std::thread::scope(|scope| {
        for entry in tar.entries().unwrap() {
            let mut entry = entry.unwrap();
            let entry_path = entry.path().unwrap();
            let str_name = entry_path
                .file_name()
                .unwrap()
                .to_str()
                .unwrap()
                .to_string();
            let size = entry.size();
            writeln!(
                &mut output,
                "\"{str_name}\" => (include_bytes!(concat!(env!(\"OUT_DIR\"), \"/{str_name}.xz\")), {size}),"
            )
            .unwrap();

            let mut entry_data = vec![];
            entry.read_to_end(&mut entry_data).unwrap();

            scope.spawn(move || {
                let mut encoder = XzEncoder::new(
                    File::create(out_dir.join(format!("{str_name}.xz"))).unwrap(),
                    XZ_COMPRESS_LEVEL,
                );
                std::io::copy(&mut &entry_data[..], &mut encoder).unwrap();
                encoder.finish().unwrap();
            });
        }
    });

    writeln!(&mut output, "}};").unwrap();

    std::fs::write(out_dir.join("zkr_table.rs"), &output).unwrap();
}
