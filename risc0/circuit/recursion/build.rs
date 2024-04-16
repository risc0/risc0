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

use std::env;

fn main() {
    if env::var("CARGO_FEATURE_CUDA").is_ok() {
        println!(
            "cargo:rustc-env=RECURSION_CUDA_EVAL_PATH={}",
            env::var("DEP_RISC0_CIRCUIT_RECURSION_SYS_CUDA_EVAL_FATBIN").unwrap()
        );
        println!(
            "cargo:rustc-env=RECURSION_CUDA_STEPS_PATH={}",
            env::var("DEP_RISC0_CIRCUIT_RECURSION_SYS_CUDA_STEPS_FATBIN").unwrap()
        );
    }

    if env::var("CARGO_FEATURE_METAL").is_ok() {
        println!(
            "cargo:rustc-env=RECURSION_METAL_PATH={}",
            env::var("DEP_RISC0_CIRCUIT_RECURSION_SYS_METAL_KERNEL").unwrap()
        );
    }

    #[cfg(feature = "prove")]
    download_zkr();
}

#[cfg(feature = "prove")]
fn download_zkr() {
    use std::{
        fs,
        path::{Path, PathBuf},
        str::FromStr,
    };

    use downloader::{verify, Download, DownloadSummary, Downloader};
    use sha2::{Digest, Sha256};

    const FILENAME: &str = "recursion_zkr.zip";
    const SRC_PATH: &str = "src/recursion_zkr.zip";
    const SHA256_HASH: &str = "3ee890ae3b7c2cf167813fe653ca9b5b8a117bb0a61c1a904f8e6acf62c76251";

    fn check_sha2(path: &Path) -> bool {
        let data = fs::read(path).unwrap();
        hex::encode(Sha256::digest(data)) == SHA256_HASH
    }

    if env::var("DOCS_RS").is_ok() {
        return;
    }

    println!("cargo:rerun-if-env-changed=RECURSION_SRC_PATH");

    let src_path = env::var("RECURSION_SRC_PATH").unwrap_or(SRC_PATH.to_string());
    let src_path = PathBuf::from_str(src_path.as_str()).unwrap();
    let out_dir = env::var("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir);
    let out_path = out_dir.join(FILENAME);

    if out_path.exists() {
        if check_sha2(&out_path) {
            return;
        }
        fs::remove_file(&out_path).unwrap();
    }

    if src_path.exists() && check_sha2(&src_path) {
        fs::copy(&src_path, &out_path).unwrap();
        return;
    }

    let mut downloader = Downloader::builder()
        .download_folder(out_dir)
        .build()
        .unwrap();
    let url = format!("https://risc0-artifacts.s3.us-west-2.amazonaws.com/zkr/{SHA256_HASH}.zip");
    eprintln!("Downloading {url}");
    let dl = Download::new(&url)
        .file_name(&PathBuf::from_str(FILENAME).unwrap())
        .verify(verify::with_digest::<Sha256>(
            hex::decode(SHA256_HASH).unwrap(),
        ));
    let results = downloader.download(&[dl]).unwrap();
    for result in results {
        let summary: DownloadSummary = result.unwrap();
        eprintln!("{summary}");
    }
}
