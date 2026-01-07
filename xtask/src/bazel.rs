// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{
    fs::File,
    io::{BufRead as _, BufReader},
    path::{Path, PathBuf},
    process::{Command, Stdio, exit},
};

use clap::Parser;
use flate2::{Compression, write::GzEncoder};
use liblzma::read::XzEncoder;
use tar::Builder;

const XZ_COMPRESS_LEVEL: u32 = 6;

#[derive(Parser)]
pub struct Bazel;

impl Bazel {
    pub fn run(&self) {
        Self::bootstrap_rust_verifier();
        Self::bootstrap_zkr();
        Self::bootstrap_riscv_guest_tests();
    }

    fn bootstrap_rust_verifier() {
        let pwd = std::env::current_dir().unwrap();
        let dst_dir = pwd.join("risc0/circuit/rv32im/src/zirgen");
        let bazel_root = Path::new("risc0/circuit/rv32im-sys/cxx");
        let mut command = Command::new("bazelisk");
        let status = command
            .args(["run", "//compiler/bootstrap", "--"])
            .arg(dst_dir)
            .current_dir(bazel_root)
            .status()
            .unwrap();
        assert!(status.success(), "bazelisk run //compiler/bootstrap failed");
    }

    fn bootstrap_zkr() {
        let bazel_root = Path::new("risc0/circuit/rv32im-sys/cxx");
        let mut command = Command::new("bazelisk");
        command
            .args(["build", "//compiler/bootstrap:zkr"])
            .current_dir(bazel_root)
            .stdout(Stdio::inherit())
            .stderr(Stdio::piped());
        let mut child = command.spawn().expect("Unable to run bazelisk");
        let child_out = BufReader::new(child.stderr.take().unwrap());

        let mut srcs = vec![];
        for line in child_out.lines() {
            let line = line.unwrap();
            eprintln!("{line}");
            if !line.starts_with("  bazel-bin/") {
                continue;
            }

            let path = PathBuf::from(&line[2..]);
            println!("path: {}", path.display());
            srcs.push(bazel_root.join(path));
        }
        let status = child.wait().expect("Unable to wait for bazel");
        if !status.success() {
            eprintln!("Bazel did not return success.");
            exit(status.code().unwrap());
        }

        // copy
        // bazel-bin/compiler/bootstrap/lift_rv32im_m3_12.zkr
        // into
        // risc0/circuit/recursion/src
        let pwd = std::env::current_dir().unwrap();
        let dst_dir = pwd.join("risc0/circuit/recursion/src/prove");
        for src_path in srcs {
            let file_name = src_path.file_name().unwrap().to_owned();
            let src_data = File::open(&src_path).unwrap();
            let mut src_xz = XzEncoder::new(src_data, XZ_COMPRESS_LEVEL);

            // Avoid using `std::fs::copy` because bazel creates files with r/o permissions.
            // We create a new file with r/w permissions and .copy the contents instead.
            let mut dst_path = dst_dir.join(file_name);
            dst_path.set_extension("zkr.xz");
            let mut dst_file = File::create(&dst_path).unwrap();
            std::io::copy(&mut src_xz, &mut dst_file).unwrap();
        }
    }

    fn bootstrap_riscv_guest_tests() {
        let bazel_root = Path::new("risc0/circuit/rv32im-sys/cxx");

        // First, build the riscv_test_guest_bins target
        let mut build_cmd = Command::new("bazelisk");
        build_cmd
            .args(["build", "//rv32im/rvtest-guest:riscv_test_guest_bins"])
            .current_dir(bazel_root)
            .stdout(Stdio::inherit())
            .stderr(Stdio::inherit());
        let build_status = build_cmd.status().expect("Unable to run bazelisk");
        if !build_status.success() {
            eprintln!("Bazel build did not return success.");
            exit(build_status.code().unwrap());
        }

        // Query for all labels that are srcs of the filegroup
        let mut query_labels_cmd = Command::new("bazelisk");
        query_labels_cmd
            .args([
                "query",
                "labels(srcs, //rv32im/rvtest-guest:riscv_test_guest_bins)",
            ])
            .current_dir(bazel_root)
            .stdout(Stdio::piped())
            .stderr(Stdio::inherit());
        let labels_output = query_labels_cmd
            .output()
            .expect("Unable to run bazelisk query");
        if !labels_output.status.success() {
            eprintln!("Bazel query did not return success.");
            exit(labels_output.status.code().unwrap());
        }

        // Get file paths for each binary target
        let mut srcs = vec![];
        let labels_stdout =
            String::from_utf8(labels_output.stdout).expect("Invalid UTF-8 in bazel query output");
        for label in labels_stdout.lines() {
            let label = label.trim();
            if label.is_empty() {
                continue;
            }

            let mut query_files_cmd = Command::new("bazelisk");
            query_files_cmd
                .args(["cquery", label, "--output=files"])
                .current_dir(bazel_root)
                .stdout(Stdio::piped())
                .stderr(Stdio::inherit());
            let files_output = query_files_cmd
                .output()
                .expect("Unable to run bazelisk cquery");
            if !files_output.status.success() {
                eprintln!("Bazel cquery did not return success for {}", label);
                continue;
            }

            let files_stdout = String::from_utf8(files_output.stdout)
                .expect("Invalid UTF-8 in bazel cquery output");
            for line in files_stdout.lines() {
                let trimmed = line.trim();
                if trimmed.is_empty() {
                    continue;
                }
                // Bazel outputs absolute paths or paths relative to workspace
                let path = if trimmed.starts_with('/') {
                    PathBuf::from(trimmed)
                } else {
                    bazel_root.join(trimmed)
                };
                if path.exists() && path.is_file() {
                    srcs.push(path);
                }
            }
        }

        // Create a .tgz archive with all the riscv-test binaries
        let pwd = std::env::current_dir().unwrap();
        let dst_dir = pwd.join("risc0/zkos/v1compat/testdata");
        std::fs::create_dir_all(&dst_dir).expect("Failed to create testdata directory");
        let archive_path = dst_dir.join("riscv-tests.tgz");

        // Create the .tgz archive
        let archive_file = File::create(&archive_path).expect("Failed to create archive file");
        let gz_encoder = GzEncoder::new(archive_file, Compression::default());
        let mut tar_builder = Builder::new(gz_encoder);

        for src_path in srcs {
            let file_name = src_path.file_name().unwrap();

            // Avoid using `std::fs::copy` because bazel creates files with r/o permissions.
            // We open the file and append it to the tar archive.
            let mut src_file = File::open(&src_path).expect("Failed to open source file");
            tar_builder
                .append_file(file_name, &mut src_file)
                .expect("Failed to add file to archive");
        }

        tar_builder.finish().expect("Failed to finish archive");
    }
}
