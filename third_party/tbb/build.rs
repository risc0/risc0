use std::{
    env,
    fs::{self, File},
    io,
    path::{Path, PathBuf},
};

use cxx_build::CFG;
use flate2::read::GzDecoder;
use glob::glob;
use sha2::{Digest, Sha256};
use tar::Archive;

const URL: &str = "https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.5.0.tar.gz";
const SHA256: &str = "e5b57537c741400cf6134b428fc1689a649d7d38d9bb9c1b6d64f092ea28178a";
const PREFIX: &str = "oneTBB-2021.5.0";

fn main() {
    let mut response = reqwest::blocking::get(URL).unwrap();
    let tmp_dir = tempfile::tempdir().unwrap();
    let filename = URL.split('/').last().unwrap();
    let tmp_path = tmp_dir.path().join(filename);
    let mut tmp_file = File::create(&tmp_path).unwrap();

    response.copy_to(&mut tmp_file).unwrap();

    let mut tmp_file = File::open(&tmp_path).unwrap();

    let mut hasher = Sha256::new();
    let _ = io::copy(&mut tmp_file, &mut hasher).unwrap();
    let hash = hasher.finalize();
    let hex_hash = base16ct::lower::encode_string(&hash);
    assert_eq!(hex_hash, SHA256);

    let out_dir = env::var("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir);
    let tar_path = out_dir.join(filename);

    fs::rename(&tmp_path, &tar_path).unwrap();
    println!("Downloaded: {}", tar_path.display());

    let tar_gz = File::open(tar_path).unwrap();
    let tar = GzDecoder::new(tar_gz);
    let mut archive = Archive::new(tar);
    archive.unpack(out_dir).unwrap();

    let src_dir = out_dir.join(PREFIX);
    let inc_dir = src_dir.join("include");
    let srcs: Vec<PathBuf> = glob(&format!("{}/src/tbb/*.cpp", src_dir.display()))
        .unwrap()
        .map(|x| x.unwrap())
        .collect();

    CFG.exported_header_dirs = vec![&inc_dir];

    cxx_build::bridge("src/lib.rs")
        .files(srcs)
        .include(inc_dir)
        .define("__TBB_BUILD", None)
        // MSVC flags
        .flag_if_supported("/std:c++17")
        // GCC/Clang flags
        .flag_if_supported("-w")
        .flag_if_supported("-std=c++17")
        .warnings(false)
        .compile("tbb");
}
