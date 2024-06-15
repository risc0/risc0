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

#[cfg(feature = "experimental")]
mod runtime {
    use std::{env, fs, io, path::Path};

    use risc0_build::build_rust_runtime;
    use zip::{write::SimpleFileOptions, CompressionMethod, ZipWriter};

    pub fn build_and_zip_runtime() {
        // Build the risc0-zkvm-platform.a file and place it in a zip archive for
        // inclusion in the cargo-risczero binary.
        let out_dir_env = env::var_os("OUT_DIR").unwrap();
        let out_dir = Path::new(&out_dir_env); // $ROOT/target/$profile/build/$crate/out

        let rust_runtime = build_rust_runtime();
        let f = fs::File::create(out_dir.join("cargo-risczero.zip")).unwrap();
        let mut zip = ZipWriter::new(f);
        let options = SimpleFileOptions::default().compression_method(CompressionMethod::Stored);

        zip.start_file("risc0-zkvm-platform.a", options).unwrap();
        let mut runtime_in = fs::File::open(rust_runtime).unwrap();
        io::copy(&mut runtime_in, &mut zip).unwrap();
        zip.finish().unwrap();
    }
}

fn main() {
    #[cfg(feature = "experimental")]
    {
        tracing_subscriber::fmt()
            .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
            .init();
        runtime::build_and_zip_runtime();
    }
}
