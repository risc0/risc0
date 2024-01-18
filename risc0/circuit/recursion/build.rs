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

use sha2::Digest;
use std::env;

fn main() {
    if env::var("CARGO_FEATURE_CUDA").is_ok() {
        let cuda_bin = env::var("DEP_RISC0_CIRCUIT_RECURSION_SYS_CUDA_KERNEL").expect(
            "CARGO_FEATURE_CUDA is defined, but DEP_RISC0_CIRCUIT_RECURSION_SYS_CUDA_KERNEL is not",
        );
        println!("cargo:rustc-env=RECURSION_CUDA_PATH={cuda_bin}");
    }

    if env::var("CARGO_FEATURE_METAL").is_ok() {
        let metal_bin = env::var("DEP_RISC0_CIRCUIT_RECURSION_SYS_METAL_KERNEL").expect(
            "CARGO_FEATURE_METAL is defined, but DEP_RISC0_CIRCUIT_RECURSION_SYS_METAL_KERNEL is not",
        );
        println!("cargo:rustc-env=RECURSION_METAL_PATH={metal_bin}");
    }

    #[cfg(feature = "prove")]
    download_zkr();
}

#[cfg(feature = "prove")]
fn download_zkr() {
    use std::{
        num::ParseIntError,
        path::{Path, PathBuf},
        str::FromStr,
    };

    use downloader::{verify, Download, DownloadSummary, Downloader};

    const FILENAME: &str = "recursion_zkr.zip";
    const SRC_PATH: &str = "src/recursion_zkr.zip";
    const SHA256_HASH: &str = "af7843e15818ef2ebd04fb455caeb42aaa3b70582f519a040adb870318797990";

    let src_path = env::var("RECURSION_SRC_PATH").unwrap_or(SRC_PATH.to_string());
    let src_path = PathBuf::from_str(src_path.as_str()).unwrap();
    let out_dir = env::var("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir);
    let out_path = out_dir.join(FILENAME);

    if std::fs::metadata(&out_path).is_ok() {
        let data = std::fs::read(&out_path).unwrap();
        if sha2::Sha256::digest(data).to_vec() == decode_hex(SHA256_HASH).unwrap() {
            return;
        } else {
            std::fs::remove_file(&out_path).unwrap();
        }
    }

    if std::fs::metadata(&src_path).is_ok() {
        let data = std::fs::read(&src_path).unwrap();
        if sha2::Sha256::digest(data).to_vec() == decode_hex(SHA256_HASH).unwrap() {
            std::fs::copy(&src_path, &out_path).unwrap();
            return;
        }
    }

    fn decode_hex(s: &str) -> Result<Vec<u8>, ParseIntError> {
        (0..s.len())
            .step_by(2)
            .map(|i| u8::from_str_radix(&s[i..i + 2], 16))
            .collect()
    }
    let mut downloader = Downloader::builder()
        .download_folder(out_dir)
        .build()
        .unwrap();
    let url = format!("https://risc0-artifacts.s3.us-west-2.amazonaws.com/zkr/{SHA256_HASH}.zip");
    eprintln!("Downloading {url}");
    let dl = Download::new(&url)
        .file_name(&PathBuf::from_str(FILENAME).unwrap())
        .verify(verify::with_digest::<sha2::Sha256>(
            decode_hex(SHA256_HASH).unwrap(),
        ));
    let results = downloader.download(&[dl]).unwrap();
    for result in results {
        let summary: DownloadSummary = result.unwrap();
        eprintln!("{summary}");
    }
}
