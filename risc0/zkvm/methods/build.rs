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

use std::{collections::HashMap, env};

use risc0_build::{embed_methods_with_options, DockerOptions, GuestOptions};

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    if env::var("CARGO_CFG_TARGET_OS").unwrap().contains("zkvm") {
        // Guest shouldn't recursively depend on itself.
        return;
    }

    let docker_opts = DockerOptions {
        root_dir: Some("../../..".into()),
    };

    let use_docker = if env::var("RISC0_USE_DOCKER").is_ok() {
        Some(docker_opts)
    } else {
        None
    };

    let map = HashMap::from([
        (
            "risc0-zkvm-methods-guest",
            GuestOptions {
                use_docker,
                ..Default::default()
            },
        ),
        (
            "risc0-zkvm-methods-std",
            GuestOptions {
                features: vec!["test_feature1".to_string(), "test_feature2".to_string()],
                ..Default::default()
            },
        ),
    ]);

    embed_methods_with_options(map);

    println!("cargo:rerun-if-env-changed=RISC0_USE_DOCKER");
}
