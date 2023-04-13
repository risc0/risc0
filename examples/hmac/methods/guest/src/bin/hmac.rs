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

#![no_main]

use risc0_zkvm::guest::env;
use risc0_zkvm::sha::{sha, Sha};

risc0_zkvm::guest::entry!(main);

pub const SHA_DIGEST_BYTES: usize = 64;
const SHA_KEY_BYTES: usize = 64;

pub fn main() {
    let key: String = env::read();
    let message: String = env::read();

    // set constants for HMAC
    let inner_pad_byte: u8 = 0x36;
    let outer_pad_byte: u8 = 0x5c;
    let key_pad_byte:   u8 = 0x00;

    let auth_key: &mut [u8; SHA_KEY_BYTES] = &mut [key_pad_byte; SHA_KEY_BYTES];

    // if the key is longer than the hasher's block length, it should be truncated using the hasher
    if key.len() > SHA_KEY_BYTES {
        // derive new authentication from provided key
        // sha1_ctx.update(key);
        let sha = sha().hash_bytes(&key.as_bytes());

        // assign derived authentication key
        auth_key[..SHA_DIGEST_BYTES].copy_from_slice(&*sha.as_bytes());
    } else {
        auth_key[..key.len()].copy_from_slice(key.as_bytes());
    }

    // generate padding arrays
    let mut inner_padding: [u8; SHA_KEY_BYTES] = [inner_pad_byte; SHA_KEY_BYTES];
    let mut outer_padding: [u8; SHA_KEY_BYTES] = [outer_pad_byte; SHA_KEY_BYTES];

    for offset in 0..auth_key.len() {
        inner_padding[offset] ^= auth_key[offset];
        outer_padding[offset] ^= auth_key[offset];
    }

    let inner_hash = sha().hash_bytes(&[
        &inner_padding,
        message.as_bytes()
    ].concat()[..]);

    let mac = sha().hash_bytes(&[
        &outer_padding,
        &*inner_hash.as_bytes()
    ].concat()[..]);

    env::commit(&*mac);
}
