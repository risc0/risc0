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
    process::{Command, Stdio},
};

use clap::Parser;
use liblzma::write::XzEncoder;

const XZ_COMPRESS_LEVEL: u32 = 9;

#[derive(Parser)]
pub struct Bazel;

impl Bazel {
    pub fn run(&self) {
        Self::bootstrap_rust_verifier();
        Self::bootstrap_zkr();
        Self::bootstrap_riscv_tests();
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

    fn create_tar_xz<'a>(tar_xz_parent: PathBuf, files: impl Iterator<Item = &'a PathBuf>) {
        let mut f = tar::Builder::new(XzEncoder::new(
            File::create(tar_xz_parent.join("zkrs.tar.xz")).unwrap(),
            XZ_COMPRESS_LEVEL,
        ));
        for file in files {
            f.append_path_with_name(file, file.file_name().unwrap())
                .unwrap();
        }
        f.into_inner().unwrap().finish().unwrap();
    }

    fn bootstrap_zkr() {
        let zkrs = Self::bazel("//compiler/bootstrap:zkr");

        let pwd = std::env::current_dir().unwrap();

        let normal_zkrs = zkrs
            .iter()
            .filter(|f| !f.display().to_string().contains("povw"));
        let povw_zkrs = zkrs
            .iter()
            .filter(|f| f.display().to_string().contains("povw"));

        Self::create_tar_xz(pwd.join("risc0/circuit/recursion-zkrs/src"), normal_zkrs);
        Self::create_tar_xz(pwd.join("risc0/circuit/recursion-povw-zkrs/src"), povw_zkrs);
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
