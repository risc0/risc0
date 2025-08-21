// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use c_kzg::KzgSettings;
use std::env;
use std::path::Path;

fn main() {
    let out_dir_env = env::var_os("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir_env);
    let kzg_raw_path = out_dir.join("kzg_settings_raw.bin");
    let kzg_trusted_setup = Path::new("./trusted_setup.txt");
    let kzg_settings = KzgSettings::load_trusted_setup_file(kzg_trusted_setup).unwrap();
    let kzg_setup_data = kzg_settings.to_bytes().to_vec();
    std::fs::write(&kzg_raw_path, kzg_setup_data).unwrap();
    unsafe {
        env::set_var("KZG_FILE_PATH", kzg_raw_path.to_string_lossy().to_string());
    }

    risc0_build::embed_methods();
}
