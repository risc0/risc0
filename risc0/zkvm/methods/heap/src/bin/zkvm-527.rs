// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::guest::env;

thread_local! {
    pub static MY_STATIC_VAR: StaticVar = StaticVar::new();
}

struct StaticVar {
    pub value: String,
}

impl StaticVar {
    pub fn new() -> Self {
        env::log("new");
        Self {
            value: "xxx".to_string(),
        }
    }
}

fn main() {
    env::log("main");
    MY_STATIC_VAR.with(|x| println!("{}", x.value));
}
