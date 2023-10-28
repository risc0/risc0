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

use methods::{GUEST_ELF, GUEST_ID};
use risc0_zkvm::{ApiClient, AssetRequest, Binary, ExecutorEnv, InnerReceipt, ProverOpts, Receipt};

fn main() {
    let segment_limit_po2 = 16; // 64k cycles
    let cycles: u32 = 1 << segment_limit_po2;
    let env = ExecutorEnv::builder()
        .write(&cycles)
        .unwrap()
        .segment_limit_po2(segment_limit_po2)
        .build()
        .unwrap();
    let binary = Binary::new_elf_inline(GUEST_ELF.into());

    let client = ApiClient::from_env().unwrap();
    let mut segments = Vec::new();
    let session = client
        .execute(&env, binary, AssetRequest::Inline, |_info, asset| {
            segments.push(asset);
            Ok(())
        })
        .unwrap();

    println!("Segments: {}", segments.len());

    let opts = ProverOpts::default();
    let rollup = segments
        .iter()
        .map(|segment| {
            let receipt = client
                .prove_segment(opts.clone(), segment.clone(), AssetRequest::Inline)
                .unwrap();
            client
                .lift(
                    opts.clone(),
                    receipt.try_into().unwrap(),
                    AssetRequest::Inline,
                )
                .unwrap()
        })
        .reduce(|left, right| {
            client
                .join(
                    opts.clone(),
                    left.try_into().unwrap(),
                    right.try_into().unwrap(),
                    AssetRequest::Inline,
                )
                .unwrap()
        })
        .unwrap();

    // TODO: call verify on this receipt
    client
        .identity_p254(
            opts,
            rollup.clone().try_into().unwrap(),
            AssetRequest::Inline,
        )
        .unwrap();

    let final_receipt = Receipt::new(InnerReceipt::Succinct(rollup), session.journal.bytes.into());
    final_receipt.verify(GUEST_ID).unwrap();
}
