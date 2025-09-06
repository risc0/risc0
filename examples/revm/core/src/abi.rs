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

use sha3::{Digest, Keccak256};

fn keccak256(data: &[u8]) -> [u8; 32] {
    let mut hasher = Keccak256::new();
    hasher.update(data);
    hasher.finalize().into()
}

fn encode_int256(value: i64) -> Vec<u8> {
    let mut result = vec![0u8; 32];
    if value < 0 {
        for byte in result.iter_mut() {
            *byte = 0xFF;
        }
    }
    let bytes = value.to_be_bytes();
    for (i, &byte) in bytes.iter().enumerate() {
        result[24 + i] = byte;
    }
    result
}

pub fn abi_encode(function_signature: &str, value: i64) -> Vec<u8> {
    let signature_hash = keccak256(function_signature.as_bytes());
    let selector = &signature_hash[..4];
    
    let argument = encode_int256(value);
    let mut calldata = Vec::from(selector);
    calldata.extend(argument);
    
    calldata
}