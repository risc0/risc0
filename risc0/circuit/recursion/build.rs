// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

fn main() {
    #[cfg(feature = "prove")]
    download_zkr();
}

#[cfg(feature = "prove")]
fn download_zkr() {
    use std::{
        env, fs,
        path::{Path, PathBuf},
        str::FromStr,
    };

    use downloader::{Download, DownloadSummary, Downloader, verify};
    use sha2::{Digest, Sha256};

    const FILENAME: &str = "recursion_zkr.zip";
    const SRC_PATH: &str = "src/recursion_zkr.zip";
    // NOTE: This can be calculated with:
    // shasum -a256 risc0/circuit/recursion/src/recursion_zkr.zip
    const SHA256_HASH: &str = "81b25917a407f04006502cf8b4884ff90821a6247e71792cff58612efee6860c";

    fn check_sha2(path: &Path) -> bool {
        let data = fs::read(path).unwrap();
        hex::encode(Sha256::digest(data)) == SHA256_HASH
    }

    println!("cargo:rerun-if-env-changed=RECURSION_SRC_PATH");

    let src_path = env::var("RECURSION_SRC_PATH").unwrap_or(SRC_PATH.to_string());
    let src_path = PathBuf::from_str(src_path.as_str()).unwrap();
    let out_dir = env::var("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir);
    let out_path = out_dir.join(FILENAME);

    if env::var("DOCS_RS").is_ok() && !out_path.exists() {
        fs::write(&out_path, b"").unwrap();
        return;
    }

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
