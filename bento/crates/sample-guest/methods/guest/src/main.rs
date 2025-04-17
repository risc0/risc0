// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

#![no_main]

use risc0_zkvm::{
    guest::{env, memory_barrier},
    serde::to_vec,
};
use sample_guest_common::{IterReq, PANIC_STR};
use tiny_keccak::{Hasher, Keccak};

pub const KECCAK_DEFAULT_PO2: usize = 18;
pub type KeccakState = [u64; 25];

risc0_zkvm::guest::entry!(main);

pub fn main() {
    // 1,           // 16, 64K
    // 4 * 1024,    // 17, 128K
    // 16 * 1024,   // 18, 256K
    // 32 * 1024,   // 19, 512K
    // 64 * 1024,   // 20, 1M
    // 200 * 1024,  // 21, 2M
    // 400 * 1024,  // 22, 4M
    // 900 * 1024,  // 23, 8M
    // 1400 * 1024, // 24, 16M

    // let iters: u64 = 64 * 1024; // 1M

    // NOTE: this is a double decode, but I was able to workout the correct way to .add_input() a raw bincode blob.
    // and ideally the client side library should not need to import risc0_zkvm::serde::to_vec() to publish a input
    let iter_req: IterReq = env::read();

    match iter_req {
        IterReq::Iter(iter) => {
            // Special case to allow us to test failures from within the guest.
            if iter == 0 {
                panic!("{}", PANIC_STR)
            }
            let iters: u64 = iter * 1024;
            println!("HELLO: {}", iter);

            for i in 0..iters {
                memory_barrier(&i);
            }

            env::log("");
            env::commit(&iter);
        }
        IterReq::Composition(iter, image_id) => {
            // composition with single segment
            let value = to_vec(&iter).unwrap();
            let input_data: &[u8] = bytemuck::cast_slice(&value);
            env::verify(image_id, input_data).unwrap();
            env::log("");
            env::commit(&image_id);
        }
        IterReq::CompositionKeccak(val, image_id, run_keccak) => {
            // composition with single segment
            let value = to_vec(&val).unwrap();
            let input_data: &[u8] = bytemuck::cast_slice(&value);
            env::verify(image_id, input_data).unwrap();
            if run_keccak {
                let mut hasher = Keccak::v256();
                let mut output = [0u8; 32];
                hasher.update("Test Hash input".as_bytes());
                hasher.finalize(&mut output);
            }
            env::log("");
            env::commit(&image_id);
        }
        IterReq::DoubleComposition(iter, first_image_id, second_image_id) => {
            // composition with multiple segments
            // Special case to allow us to test failures from within the guest.
            if iter == 0 {
                panic!("{}", PANIC_STR)
            }
            let iters: u64 = iter * 1024;
            println!("HELLO: {}", iter);

            for i in 0..iters {
                memory_barrier(&i);
            }

            // first verify
            let iter_value = to_vec(&iter).unwrap();
            let input_data: &[u8] = bytemuck::cast_slice(&iter_value);
            env::verify(first_image_id, input_data).unwrap();
            env::log("");

            // second verify
            let image_value = to_vec(&first_image_id).unwrap();
            let input_data: &[u8] = bytemuck::cast_slice(&image_value);
            env::verify(second_image_id, input_data).unwrap();
            env::log("");
            env::commit(&second_image_id);
        }
        IterReq::Keccak(data) => {
            let mut hasher = Keccak::v256();
            let mut output = [0u8; 32];
            hasher.update(data.as_bytes());
            hasher.finalize(&mut output);
            env::commit(&output);
        }
        IterReq::KeccakUnion(data) => {
            let cycles = 1 << KECCAK_DEFAULT_PO2;
            let count = cycles / 200 * data;
            let mut state = KeccakState::default();
            for _i in 0..count {
                env::risc0_keccak_update(&mut state);
            }
        }
        IterReq::CompositionKeccakUnion(val, image_id, data) => {
            // setup keccak env
            let cycles = 1 << KECCAK_DEFAULT_PO2;
            let count = cycles / 200 * data;
            let mut state = KeccakState::default();
            for _i in 0..count {
                env::risc0_keccak_update(&mut state);
            }
            // composition with single segment
            let value = to_vec(&val).unwrap();
            let input_data: &[u8] = bytemuck::cast_slice(&value);
            env::verify(image_id, input_data).unwrap();
            env::log("");
            env::commit(&image_id);
        }
    }
}
