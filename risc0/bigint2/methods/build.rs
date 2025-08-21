// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::collections::HashMap;

use risc0_build::GuestOptionsBuilder;

fn main() {
    println!("cargo:rerun-if-env-changed=NUM_BIGINT_DIG");

    let features = if std::env::var("NUM_BIGINT_DIG").is_ok() {
        vec!["num-bigint-dig".to_string()]
    } else {
        vec!["num-bigint".to_string()]
    };

    let map = HashMap::from([(
        "risc0-bigint2-guest",
        GuestOptionsBuilder::default()
            .features(features)
            .build()
            .unwrap(),
    )]);

    risc0_build::embed_methods_with_options(map);
}
