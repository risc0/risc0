// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{collections::HashMap, env};

use risc0_build::{DockerOptionsBuilder, GuestOptionsBuilder, embed_methods_with_options};

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    if env::var("CARGO_CFG_TARGET_OS").unwrap().contains("zkvm") {
        // Guest shouldn't recursively depend on itself.
        return;
    }

    let mut guest_opts = GuestOptionsBuilder::default();

    if env::var("RISC0_USE_DOCKER").is_ok() {
        guest_opts.use_docker(
            DockerOptionsBuilder::default()
                .root_dir("../../..")
                .build()
                .unwrap(),
        );
    }

    let map = HashMap::from([
        ("risc0-zkvm-methods-guest", guest_opts.build().unwrap()),
        (
            "risc0-zkvm-methods-std",
            GuestOptionsBuilder::default()
                .features(vec![
                    "test_feature1".to_string(),
                    "test_feature2".to_string(),
                ])
                .build()
                .unwrap(),
        ),
        (
            "risc0-zkvm-methods-std-ext",
            GuestOptionsBuilder::default().build().unwrap(),
        ),
        ("risc0-zkvm-methods-cpp-crates", guest_opts.build().unwrap()),
    ]);

    embed_methods_with_options(map);

    println!("cargo:rerun-if-env-changed=RISC0_USE_DOCKER");
}
