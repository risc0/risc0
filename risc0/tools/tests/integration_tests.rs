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

use std::process::Command;

use assert_cmd::prelude::*;
use risc0_zkos_v1compat::V1COMPAT_ELF;
use tempfile::tempdir;

/// This file contains tests that exercise the tools as if it were run on the
/// commandline.

#[test]
fn run_make_id() {
    let temp_dir = tempdir().unwrap();

    let user_elf_path = "tests/add";
    let id_path = temp_dir.path().join("add.id");
    let kernel_elf_path = temp_dir.path().join("v1compat.elf");
    std::fs::write(&kernel_elf_path, V1COMPAT_ELF).unwrap();

    let mut make_id_cmd = Command::cargo_bin("make_id").unwrap();
    make_id_cmd
        .arg(user_elf_path)
        .arg(kernel_elf_path)
        .arg(id_path);
    make_id_cmd.assert().success();
}
