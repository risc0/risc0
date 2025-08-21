// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::guest::env;

fn main() {
    let x: u32 = if std::env::var("ALL_FORKS") == Ok(String::from("1")) {
        1
    } else {
        0
    };

    risc0_zkvm::guest::env::commit(&x);

    let iterations: u32 = env::read();
    for _ in 0..iterations {
        env::log("alloc");
        let tmp = vec![0; 10 * 1024];
        println!("{:#?}", tmp.as_ptr());
    }
}
