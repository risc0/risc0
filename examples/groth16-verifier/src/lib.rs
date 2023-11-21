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

use anyhow::Result;
use bonsai_sdk::alpha as bonsai_sdk;
use byteorder::{BigEndian, WriteBytesExt};
use hello_world_methods::{MULTIPLY_ELF, MULTIPLY_ID};
use risc0_zkvm::{
    default_prover, groth16::Groth16Seal, serde::to_vec, ExecutorEnv, Groth16Receipt, MemoryImage,
    Program, Receipt, GUEST_MAX_MEM, PAGE_SIZE,
};
use std::time::Duration;

// Run Bonsai for the hello world example
pub fn run_bonsai(input_data: Vec<u8>) -> Result<Receipt> {
    let client = bonsai_sdk::Client::from_env(risc0_zkvm::VERSION)?;

    // create the memoryImg, upload it and return the imageId
    let img_id = {
        let program = Program::load_elf(MULTIPLY_ELF, GUEST_MAX_MEM as u32)?;
        let image = MemoryImage::new(&program, PAGE_SIZE as u32)?;
        let image_id = hex::encode(image.compute_id());
        let image = bincode::serialize(&image).expect("Failed to serialize memory img");
        client.upload_img(&image_id, image)?;
        image_id
    };

    // Prepare input data and upload it.
    let input_data = to_vec(&input_data).unwrap();
    let input_data = bytemuck::cast_slice(&input_data).to_vec();
    let input_id = client.upload_input(input_data)?;

    // Start a session running the prover
    let session = client.create_session(img_id, input_id)?;
    loop {
        let res = session.status(&client)?;
        if res.status == "RUNNING" {
            eprintln!(
                "Current status: {} - state: {} - continue polling...",
                res.status,
                res.state.unwrap_or_default()
            );
            std::thread::sleep(Duration::from_secs(15));
            continue;
        }
        if res.status == "SUCCEEDED" {
            // Download the receipt, containing the output
            let receipt_url = res
                .receipt_url
                .expect("API error, missing receipt on completed session");

            let receipt_buf = client.download(&receipt_url)?;
            let receipt: Receipt = bincode::deserialize(&receipt_buf)?;
            receipt
                .verify(MULTIPLY_ID)
                .expect("Receipt verification failed");
        } else {
            panic!(
                "Workflow exited: {} - | err: {}",
                res.status,
                res.error_msg.unwrap_or_default()
            );
        }

        break;
    }

    run_stark2snark(session.uuid)
}

// Generate a snark receipt from Bonsai
pub fn run_stark2snark(session_id: String) -> Result<Receipt> {
    let client = bonsai_sdk::Client::from_env(risc0_zkvm::VERSION)?;

    let snark_session = client.create_snark(session_id)?;
    eprintln!("Created snark session: {}", snark_session.uuid);
    loop {
        let res = snark_session.status(&client)?;
        match res.status.as_str() {
            "RUNNING" => {
                eprintln!("Current status: {} - continue polling...", res.status,);
                std::thread::sleep(Duration::from_secs(15));
                continue;
            }
            "SUCCEEDED" => {
                break {
                    let snark_receipt: Receipt = bincode::deserialize(&res.output.unwrap())?;
                    eprintln!("Snark proof!: {snark_receipt:?}");
                    Ok(snark_receipt)
                };
            }
            _ => {
                panic!(
                    "Workflow exited: {} err: {}",
                    res.status,
                    res.error_msg.unwrap_or_default()
                );
            }
        }
    }
}

// Mock a Groth16Receipt as received from Bonsai
pub fn run_bonsai_mock() -> Receipt {
    let groth16_seal = Groth16Seal {
        a: vec![
            vec![
                26u8, 63, 155, 211, 133, 192, 185, 234, 51, 172, 152, 49, 113, 248, 13, 45, 155,
                140, 75, 98, 171, 225, 72, 44, 133, 246, 88, 199, 37, 103, 28, 56,
            ],
            vec![
                22u8, 46, 102, 79, 175, 35, 89, 153, 55, 78, 200, 143, 26, 196, 209, 62, 247, 200,
                136, 247, 101, 65, 101, 157, 59, 33, 20, 91, 191, 43, 246, 84,
            ],
        ],
        b: vec![
            vec![
                vec![
                    20u8, 0, 192, 47, 211, 1, 254, 55, 118, 229, 52, 232, 89, 161, 51, 100, 224,
                    242, 246, 5, 106, 190, 188, 113, 187, 230, 100, 7, 255, 70, 192, 153,
                ],
                vec![
                    9u8, 206, 194, 232, 36, 249, 103, 125, 57, 1, 189, 209, 245, 133, 230, 79, 219,
                    98, 176, 253, 221, 160, 20, 78, 189, 142, 46, 52, 171, 1, 162, 203,
                ],
            ],
            vec![
                vec![
                    32u8, 70, 252, 38, 183, 118, 240, 156, 230, 16, 28, 10, 122, 111, 184, 65, 239,
                    158, 193, 102, 94, 156, 5, 56, 24, 236, 174, 103, 160, 172, 89, 109,
                ],
                vec![
                    4u8, 151, 70, 37, 225, 160, 65, 7, 230, 206, 172, 247, 41, 192, 58, 149, 244,
                    201, 31, 171, 7, 137, 232, 107, 29, 143, 227, 49, 96, 29, 198, 35,
                ],
            ],
        ],
        c: vec![
            vec![
                20u8, 112, 216, 216, 113, 186, 224, 139, 117, 16, 31, 102, 238, 29, 76, 150, 58,
                216, 254, 75, 147, 172, 89, 147, 216, 138, 41, 130, 172, 106, 148, 8,
            ],
            vec![
                23u8, 250, 144, 90, 188, 98, 158, 62, 214, 76, 108, 236, 158, 31, 125, 183, 20,
                200, 101, 254, 212, 15, 32, 174, 120, 230, 219, 15, 71, 206, 189, 55,
            ],
        ],
    };

    let env = ExecutorEnv::builder()
        .write(&17u64)
        .unwrap()
        .write(&23u64)
        .unwrap()
        .build()
        .unwrap();

    let receipt = default_prover().prove_elf(env, MULTIPLY_ELF).unwrap();

    let groth16_receipt = Receipt::new(
        risc0_zkvm::InnerReceipt::Groth16(Groth16Receipt {
            seal: groth16_seal.to_vec(),
            meta: receipt.get_metadata().unwrap(),
        }),
        receipt.journal.bytes,
    );
    groth16_receipt
}

pub fn u64s_to_vec(a: u64, b: u64) -> Vec<u8> {
    let mut wtr = vec![];
    wtr.write_u64::<BigEndian>(a).unwrap();
    wtr.write_u64::<BigEndian>(b).unwrap();
    wtr
}
