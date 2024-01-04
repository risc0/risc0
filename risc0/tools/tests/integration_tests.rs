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

use std::process::Command;

use assert_cmd::prelude::*;
use tempfile::tempdir;

/// This file contains tests that exercise the tools as if it were run on the
/// commandline.

#[test]
fn run_make_id() {
    let temp_dir = tempdir().unwrap();

    let elf_path = "tests/add";
    let id_path = temp_dir.path().join("add.id");

    let mut make_id_cmd = Command::cargo_bin("make_id").unwrap();
    make_id_cmd.arg(elf_path).arg(id_path);
    make_id_cmd.assert().success();
}
