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

use std::{fs, path::Path};

use clap::Parser;

#[derive(Parser)]
pub struct BootstrapKernelBuilds;

impl BootstrapKernelBuilds {
    fn write_manifest(root: impl AsRef<Path>, exts: &[&str]) {
        let mut lines = vec![];
        for entry in walkdir::WalkDir::new(root.as_ref()) {
            let entry = entry.unwrap();
            let path = entry.path();

            let Some(ext) = path.extension() else {
                continue;
            };
            let Some(ext_str) = ext.to_str() else {
                continue;
            };

            if exts.iter().any(|search| search == &ext_str) {
                let path = path.strip_prefix(root.as_ref()).unwrap();
                lines.push(path.to_str().unwrap().to_string());
            }
        }

        lines.sort();
        fs::write(
            root.as_ref().join("kernel_build.manifest"),
            lines.join("\n"),
        )
        .unwrap();
    }

    pub fn run(&self) {
        let c_and_kernels = ["cpp", "h", "hpp", "cuh", "cu", "metal", "ipp", "inc"];
        Self::write_manifest("risc0/circuit/rv32im-sys/", &c_and_kernels);
        Self::write_manifest("risc0/circuit/recursion-sys/kernels", &c_and_kernels);
        Self::write_manifest("risc0/circuit/keccak-sys/kernels", &c_and_kernels);
        Self::write_manifest("risc0/groth16-sys/kernels", &c_and_kernels);
        Self::write_manifest("risc0/sys/", &c_and_kernels);
    }
}
