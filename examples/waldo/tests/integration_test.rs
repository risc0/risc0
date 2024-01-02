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

#[test]
fn test_waldo() {
    let feature = if cfg!(feature = "metal") {
        "metal"
    } else if cfg!(feature = "cuda") {
        "cuda"
    } else {
        "default"
    };

    Command::new("cargo")
        .args([
            "run",
            "--release",
            "--features",
            feature,
            "--bin",
            "prove",
            "--",
            "--i",
            "waldo.webp",
            "-x",
            "1150",
            "-y",
            "291",
            "----width 58",
            "--height",
            "70",
            "-m",
            "waldo_mask.png",
        ])
        .output()
        .expect("failed to run Waldo prove");

    Command::new("cargo")
        .args([
            "run",
            "--release",
            "--features",
            feature,
            "--bin",
            "verify",
            "--",
            "--i",
            "waldo.webp",
            "-r",
            "receipt.bin",
        ])
        .output()
        .expect("failed to run Waldo verify");
}
