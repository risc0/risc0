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

    const SRC_PATH: &str = "src/recursion_zkr.zip";
    const SHA256_HASH: &str = "566c10a9254d7ac185fd6bb807714bfb6852f2ee4241bc6478409444239fab46";

    let src_path = PathBuf::from_str(SRC_PATH).unwrap();
    let out_dir = env::var("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir);
    if std::fs::metadata(&src_path).is_ok() {
        let tgt_path = out_dir.join("recursion_zkr.zip");
        std::fs::copy(&src_path, &tgt_path).unwrap();
    } else {
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
        let url =
            format!("https://risc0-artifacts.s3.us-west-2.amazonaws.com/zkr/{SHA256_HASH}.zip");
        eprintln!("Downloading {url}");
        let dl = Download::new(&url).verify(verify::with_digest::<sha2::Sha256>(
            decode_hex(SHA256_HASH).unwrap(),
        ));
        let results = downloader.download(&[dl]).unwrap();
        for result in results {
            let summary: DownloadSummary = result.unwrap();
            eprintln!("{summary}");
        }
    }
}
