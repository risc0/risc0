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
        "async-channel" | "async-executor" | "async-io" | "blocking" | "concurrent-queue"
        | "crossbeam-deque" | "crossbeam-epoch" | "crossbeam-queue" | "rayon" | "rayon-core"
        | "redox_users" | "vsdb" | "vsdbsled" => {
            // NOTE: the crate 'crossbeam-utils'|'crossbeam-channel'|'crossbeam' itself
            // still fails to build because you can't crates-io patch itself
            profile.crossbeam_patch = true;
        }
        "criterion" => {
            profile.crossbeam_patch = true;
            profile.std = true;
        }
        // Just need 'std' block:
        "anyhow" | "cargo_metadata" | "clap" | "crypto-bigint" | "csv" | "env_logger"
        | "ethers-core" | "h2" | "headers" | "hex" | "hyper" | "hyper-timeout" | "k256"
        | "md-5" | "multimap" | "openssl" | "rand" | "revm" | "revm-primitives" | "serde"
        | "serde_bytes" | "serde_cbor" | "serde_json" | "serde_urlencoded" | "serde_with"
        | "serde_yaml" | "sha-1" | "sha1" | "sha2" | "sha3" | "string_cache" | "tinytemplate"
        | "toml" | "tower" | "tracing" | "tracing-core" | "tracing-futures" | "tracing-log"
        | "tracing-serde" | "tracing-subscriber" | "tungstenite" => profile.std = true,
        _ => profile.customized = false,
    }
    profile
}
