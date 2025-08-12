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

use risc0_build::{embed_methods_with_options, GuestOptionsBuilder};

const VMLINUZ_ELF: &[u8] = include_bytes!("../elfs/vmlinuz.elf");

fn main() {
    if cfg!(feature = "risc0-linux") {
        embed_methods_with_options(
            [(
                "risc0-zkos-linux-guests-hello",
                GuestOptionsBuilder::default()
                    .toolchain("risc0-linux")
                    .target("riscv32im-unknown-linux-musl")
                    .kernel(VMLINUZ_ELF)
                    .build()
                    .unwrap(),
            )]
            .into(),
        );
    }
}
