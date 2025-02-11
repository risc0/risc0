// Copyright 2025 RISC Zero, Inc.
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
