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
        path::{Path, PathBuf},
        str::FromStr,
    };

    use downloader::{verify, Download, DownloadSummary, Downloader};

    const SRC_PATH: &str = "src/recursion_zkr.zip";
    const GIT_COMMIT: &str = "505295b963c97db2afffe58f4b0cb4721e396b90";

    let src_path = PathBuf::from_str(SRC_PATH).unwrap();
    let out_dir = env::var("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir);
    if std::fs::metadata(&src_path).is_ok() {
        let tgt_path = out_dir.join("recursion_zkr.zip");
        std::fs::copy(&src_path, &tgt_path).unwrap();
    } else {
        fn decode_hex(s: &str) -> Result<Vec<u8>, std::num::ParseIntError> {
            (0..s.len())
                .step_by(2)
                .map(|i| u8::from_str_radix(&s[i..i + 2], 16))
                .collect()
        }
        let mut downloader = Downloader::builder()
            .download_folder(out_dir)
            .build()
            .unwrap();
        let url = format!("https://github.com/risc0/risc0/raw/{GIT_COMMIT}/risc0/circuit/recursion/src/recursion_zkr.zip");
        eprintln!("Downloading {url}");
        let dl = Download::new(&url).verify(verify::with_digest::<sha2::Sha256>(
            decode_hex("a01d63a6d87cd914fff6f70477565905e824a8108052199e4f432b381f7e7567").unwrap(),
        ));
        let results = downloader.download(&[dl]).unwrap();
        for result in results {
            let summary: DownloadSummary = result.unwrap();
            eprintln!("{summary}");
        }
    }
}
