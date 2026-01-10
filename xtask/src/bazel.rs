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
    fs::{File, Permissions},
    io::{BufRead as _, BufReader},
    os::unix::fs::PermissionsExt,
    path::{Path, PathBuf},
    process::{Command, Stdio},
};

use clap::Parser;
use liblzma::read::XzEncoder;

const XZ_COMPRESS_LEVEL: u32 = 6;

#[derive(Parser)]
pub struct Bazel;

impl Bazel {
    pub fn run(&self) {
        Self::bootstrap_rust_verifier();
        Self::bootstrap_zkr();
        Self::bootstrap_riscv_tests();
        Self::bootstrap_softfloat();
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
        let srcs = Self::bazel("//compiler/bootstrap:zkr");

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

    fn bootstrap_riscv_tests() {
        let srcs = Self::bazel("//rv32im/rvtest:riscv-tests");
        let pwd = std::env::current_dir().unwrap();
        let dst_dir = pwd.join("risc0/zkvm/src/host/server/testdata");
        for src_path in srcs {
            let file_name = src_path.file_name().unwrap();
            let mut src_data = File::open(&src_path).unwrap();
            let dst_path = dst_dir.join(file_name);
            let mut dst_file = File::create(&dst_path).unwrap();
            std::io::copy(&mut src_data, &mut dst_file).unwrap();
        }
    }

    fn bootstrap_softfloat() {
        // Build the softfloat library directly to get the archive output
        let srcs = Self::bazel("//rv32im/softfloat:softfloat");
        let pwd = std::env::current_dir().unwrap();
        let dst_dir = pwd.join("risc0/zkos/common/softfloat-sys");
        std::fs::create_dir_all(&dst_dir).expect("Failed to create softfloat-sys directory");

        // Find the libsoftfloat.a file in the build outputs
        for src_path in srcs {
            let file_name = src_path.file_name().unwrap();
            if file_name == "libsoftfloat.a"
                || file_name.to_string_lossy().ends_with("libsoftfloat.a")
            {
                let dst_path = dst_dir.join("libsoftfloat.a");
                // Use std::fs::copy which handles read-only source files better
                std::fs::copy(&src_path, &dst_path).unwrap_or_else(|e| {
                    panic!(
                        "Failed to copy {} to {}: {}",
                        src_path.display(),
                        dst_path.display(),
                        e
                    )
                });
                // Make the file user-writable (rw-rw-r--)
                std::fs::set_permissions(&dst_path, Permissions::from_mode(0o664)).unwrap_or_else(
                    |e| panic!("Failed to set permissions on {}: {}", dst_path.display(), e),
                );
                return;
            }
        }
        panic!("Could not find libsoftfloat.a in Bazel build outputs");
    }

    fn bazel(target: &str) -> Vec<PathBuf> {
        let bazel_root = Path::new("risc0/circuit/rv32im-sys/cxx");
        let mut command = Command::new("bazelisk");
        command
            .args(["build", target])
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
        assert!(status.success(), "`bazelisk build {target}` failed");

        assert!(
            !srcs.is_empty(),
            "No artifacts found from Bazel target: {target}"
        );

        srcs
    }
}
