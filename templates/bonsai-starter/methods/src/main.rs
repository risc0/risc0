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

use std::{io, io::Write};

use bonsai_starter_methods::GUEST_BINARY_LIST;
use clap::Parser;
use risc0_zkvm::{Executor, ExecutorEnv};

/// Runs the RISC-V ELF binary.
#[derive(Parser)]
#[clap(about, version, author)]
struct Args {
    /// The name of the guest binary
    guest_binary: String,

    /// The input to provide to the guest binary
    input: Option<String>,
}

pub fn main() {
    // Parse arguments
    let args = Args::parse();
    // Search list for requested binary name
    let potential_guest_image_id: [u8; 32] =
        match hex::decode(args.guest_binary.to_lowercase().trim_start_matches("0x")) {
            Ok(byte_vector) => byte_vector.try_into().unwrap_or([0u8; 32]),
            Err(_) => [0u8; 32],
        };
    let (_, (elf, image_id)) = GUEST_BINARY_LIST
        .into_iter()
        .find(|(binary_name, (_, image_id))| {
            binary_name == &args.guest_binary.to_uppercase()
                || bytemuck::cast::<[u32; 8], [u8; 32]>(*image_id) == potential_guest_image_id
        })
        .expect("Unknown guest binary");
    // Execute or return image id
    let output_bytes = match &args.input {
        Some(input) => {
            let input = hex::decode(&input[2..]).unwrap();
            let env = ExecutorEnv::builder().add_input(&input).build();
            let mut exec = Executor::from_elf(env, elf).unwrap();
            let session = exec.run().unwrap();
            session.journal
        }
        None => Vec::from(bytemuck::cast::<[u32; 8], [u8; 32]>(image_id)),
    };
    let output = hex::encode(&output_bytes);
    print!("{output}");
    io::stdout().flush().unwrap();
}
