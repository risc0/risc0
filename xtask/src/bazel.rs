// Copyright 2025 RISC Zero, Inc.
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
use liblzma::read::XzEncoder;

const XZ_COMPRESS_LEVEL: u32 = 6;

#[derive(Parser)]
pub struct Bazel;

impl Bazel {
    pub fn run(&self) {
        Self::bootstrap_rust_verifier();
        Self::bootstrap_zkr();
    }

    fn bootstrap_rust_verifier() {
        let pwd = std::env::current_dir().unwrap();
        let dst_dir = pwd.join("risc0/circuit/rv32im-m3/src/zirgen");
        let bazel_root = Path::new("risc0/circuit/rv32im-m3-sys/cxx");
        let mut command = Command::new("bazelisk");
        command
            .args(["run", "//compiler/bootstrap", "--"])
            .arg(dst_dir)
            .current_dir(bazel_root);
    }

    fn bootstrap_zkr() {
        let bazel_root = Path::new("risc0/circuit/rv32im-m3-sys/cxx");
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
}
