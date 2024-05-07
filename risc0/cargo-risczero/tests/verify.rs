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

use assert_cmd::prelude::*;
use predicates::str::{contains, is_empty, is_match};
use predicates::Predicate;
use rstest::*;
use std::env;
use std::ffi::OsStr;
use std::process::Command;

const RECEIPT: &str = "tests/data/receipt.bin";

#[rstest]
#[case(
    // Valid receipt
    RECEIPT,
    "979e6a3e0611115750ae8a92b674c2e0fb0cb1b3d006c7326b30ec9c7e748542",
    is_match("^✅ Receipt is valid!\n$").unwrap(),
    is_empty(),
    0
)]
#[case(
    // Invalid image id
    RECEIPT,
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
    is_match("Receipt verification failed.*error.*=.*image_id mismatch").unwrap(),
    contains("❌ Receipt is not valid\nError: image_id mismatch\n"),
    1
)]
#[case(
    // Inexistent receipt
    "inexistent.bin",
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
    is_empty(),
    contains("Error: No such file or directory (os error 2)\n"),
    1
)]
fn test_verify(
    #[case] receipt: impl AsRef<OsStr>,
    #[case] image_id: impl AsRef<OsStr>,
    #[case] stdout: impl Predicate<str>,
    #[case] stderr: impl Predicate<str>,
    #[case] code: i32,
) {
    Command::cargo_bin(env!("CARGO_PKG_NAME"))
        .unwrap()
        .arg("risczero")
        .arg("verify")
        .arg(image_id)
        .arg("--path")
        .arg(receipt)
        .assert()
        .code(code)
        .stdout(stdout)
        .stderr(stderr);
}
