// Copyright 2023 RISC Zero, Inc.
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

use risc0_build::{embed_methods_with_options, GuestOptions};

fn main() {
    env_logger::init();

    if env::var("CARGO_CFG_TARGET_OS").unwrap().contains("zkvm") {
        // Guest shouldn't recursively depend on itself.
        return;
    }

    let map = HashMap::from([
        ("risc0-zkvm-methods-guest", GuestOptions::default()),
        (
            "risc0-zkvm-methods-std",
            GuestOptions {
                features: vec!["test_feature1".to_string(), "test_feature2".to_string()],
            },
        ),
    ]);

    embed_methods_with_options(map);
}
