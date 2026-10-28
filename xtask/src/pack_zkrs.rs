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

use std::{
    fs::File,
    path::{Path, PathBuf},
};

use clap::Parser;
use liblzma::write::XzEncoder;

const XZ_COMPRESS_LEVEL: u32 = 9;

/// Pack a directory of recursion programs (zkrs) into the zkrs crates.
///
/// Lifts go to `risc0-circuit-recursion-zkrs` and everything else to
/// `risc0-circuit-recursion-control-zkrs`, each as one `src/zkrs.tar.xz`.
#[derive(Parser)]
pub struct PackZkrs {
    /// Directory holding the `.zkr` files, e.g. an unpacked `recursion_zkr.zip`.
    src_dir: PathBuf,
}

impl PackZkrs {
    pub fn run(&self) {
        let mut zkrs: Vec<PathBuf> = std::fs::read_dir(&self.src_dir)
            .unwrap()
            .map(|entry| entry.unwrap().path())
            .filter(|path| path.extension().is_some_and(|ext| ext == "zkr"))
            .collect();
        // Each povw zkr is a near-identical twin of its non-povw zkr. Keeping
        // twins adjacent lets xz find the shared bytes within its dictionary,
        // which roughly halves the size of the lifts tarball.
        zkrs.sort_by_cached_key(|path| {
            let name = file_name(path);
            (name.replace("_povw", ""), name.to_string())
        });

        let (lifts, control): (Vec<_>, Vec<_>) = zkrs
            .iter()
            .partition(|path| file_name(path).starts_with("lift_"));

        let pwd = std::env::current_dir().unwrap();
        create_tar_xz(&pwd.join("risc0/circuit/recursion-zkrs/src"), &lifts);
        create_tar_xz(
            &pwd.join("risc0/circuit/recursion-control-zkrs/src"),
            &control,
        );
    }
}

fn file_name(path: &Path) -> &str {
    path.file_name().unwrap().to_str().unwrap()
}

fn create_tar_xz(tar_xz_parent: &Path, files: &[&PathBuf]) {
    let dst = tar_xz_parent.join("zkrs.tar.xz");
    tracing::info!("Writing {} zkrs to {}", files.len(), dst.display());
    let mut tar = tar::Builder::new(XzEncoder::new(
        File::create(&dst).unwrap(),
        XZ_COMPRESS_LEVEL,
    ));
    for file in files {
        let data = std::fs::read(file).unwrap();
        // Fixed metadata so that packing the same zkrs gives the same bytes.
        let mut header = tar::Header::new_gnu();
        header.set_size(data.len() as u64);
        header.set_mode(0o644);
        header.set_mtime(0);
        header.set_cksum();
        tar.append_data(&mut header, file_name(file), &data[..])
            .unwrap();
    }
    tar.into_inner().unwrap().finish().unwrap();
}
