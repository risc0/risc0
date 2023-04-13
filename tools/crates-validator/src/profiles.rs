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

use crate::CrateProfile;

pub const SKIP_CRATES: &[&str] = &[
    "miow", // Windows specific crate that depends on `windows-sys`
    "windows-sys",
    "redox_syscall", // Tools for redox OS, not supported
];

pub fn lookup_crate(crate_name: &str, mut profile: CrateProfile) -> CrateProfile {
    profile.customized = true;
    match crate_name {
        "lazy_static" => {
            profile.std = true;
            profile.import_str = Some(
                "use lazy_static::lazy_static;\nlazy_static! {\n\tstatic ref EXAMPLE: u8 = 42;\n}"
                    .to_string(),
            );
            profile.custom_main = Some("assert_eq!(*EXAMPLE, 42);".to_string());
            profile.run_prover = true;
        }
        // Requires CFLAGS for native code
        "ring" => {
            profile.inject_cc_flags = true;
        }
        "zip" => {
            profile.std = true;
            profile.inject_cc_flags = true;
        }
        "crossbeam-epoch" | "crossbeam-deque" | "rayon" | "rayon-core" | "crossbeam-queue"
        | "concurrent-queue" | "vsdb" | "vsdbsled" | "redox_users" | "async-channel"
        | "async-io" | "async-executor" | "blocking" => {
            // NOTE: the crate 'crossbeam-utils'|'crossbeam-channel'|'crossbeam' itself
            // still fails to build because you can't crates-io patch itself
            profile.crossbeam_patch = true;
        }
        "criterion" => {
            profile.crossbeam_patch = true;
            profile.std = true;
        }
        // Just need 'std' block:
        "rand" | "serde" | "serde_json" | "anyhow" | "hyper" | "tracing-log"
        | "tracing-subscriber" | "sha-1" | "serde_urlencoded" | "hex" | "h2" | "tracing-core"
        | "toml" | "tracing" | "tracing-futures" | "sha2" | "sha1" | "serde_yaml" | "csv"
        | "multimap" | "tower" | "serde_cbor" | "md-5" | "tinytemplate" | "cargo_metadata"
        | "serde_bytes" | "tungstenite" | "tracing-serde" | "sha3" | "string_cache"
        | "serde_with" | "headers" | "hyper-timeout" => profile.std = true,
        _ => profile.customized = false,
    }
    profile
}
