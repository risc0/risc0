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

#![no_std]

extern crate alloc;

use alloc::{boxed::Box, vec, vec::Vec};

use ethabi::{ethereum_types::U256, ParamType, Token};
use risc0_zkvm::guest::env;

pub trait InputStream {
    fn read_slice(&mut self, slice: &mut [u8]);
}

impl InputStream for () {
    fn read_slice(&mut self, slice: &mut [u8]) {
        env::read_slice(slice);
    }
}

impl InputStream for Vec<u8> {
    fn read_slice(&mut self, slice: &mut [u8]) {
        let n = slice.len();
        slice.copy_from_slice(&self[..n]);
        self.drain(..n);
    }
}

pub struct EthABIReader {
    reader: Box<dyn InputStream>,
}

impl Default for EthABIReader {
    fn default() -> Self {
        EthABIReader {
            reader: Box::new(()),
        }
    }
}

impl EthABIReader {
    pub fn new(reader: Box<dyn InputStream>) -> Self {
        EthABIReader { reader }
    }
    pub fn read_abi_encoded_input(
        &mut self,
        types: &[ParamType],
        buffer: &mut Vec<u8>,
        mut relative_offset: usize,
        base_offset: usize,
    ) -> usize {
        for abi_type in types {
            relative_offset = self.read_abi_type(abi_type, buffer, relative_offset, base_offset);
        }
        relative_offset
    }

    fn read_abi_type(
        &mut self,
        abi_type: &ParamType,
        buffer: &mut Vec<u8>,
        relative_offset: usize,
        base_offset: usize,
    ) -> usize {
        match abi_type {
            ParamType::Bytes | ParamType::String => {
                // Read the offset bytes
                let relative_item_tail_offset =
                    self.read_usize(buffer, relative_offset, base_offset);
                // Read the item bytes
                let byte_length =
                    32 + self.read_usize(buffer, relative_item_tail_offset, base_offset);
                self.buffer_until(
                    buffer,
                    base_offset + relative_item_tail_offset + byte_length,
                );
            }
            ParamType::Array(t) => {
                // Read the offset bytes
                let relative_item_tail_offset =
                    self.read_usize(buffer, relative_offset, base_offset);
                // Read the item count
                let item_count = self.read_usize(buffer, relative_item_tail_offset, base_offset);
                let array_base_offset = base_offset + relative_item_tail_offset + 32;
                let mut item_offset = 0;
                for _ in 0..item_count {
                    item_offset = self.read_abi_type(t, buffer, item_offset, array_base_offset);
                }
            }
            ParamType::FixedArray(t, item_count) => {
                let is_dynamic_type = t.is_dynamic();

                let (array_base_offset, mut item_offset) = if is_dynamic_type {
                    // Read the offset bytes
                    (
                        base_offset + self.read_usize(buffer, relative_offset, base_offset),
                        0,
                    )
                } else {
                    // Use current offset
                    (base_offset, relative_offset)
                };
                for _ in 0..*item_count {
                    item_offset = self.read_abi_type(t, buffer, item_offset, array_base_offset);
                }

                if !is_dynamic_type {
                    return item_offset;
                }
            }
            ParamType::Tuple(vt) => {
                let is_dynamic_type = abi_type.is_dynamic();

                let (array_base_offset, mut item_offset) = if is_dynamic_type {
                    // Read the offset bytes
                    (
                        base_offset + self.read_usize(buffer, relative_offset, base_offset),
                        0,
                    )
                } else {
                    // Use current offset
                    (base_offset, relative_offset)
                };

                for abi_type in vt {
                    item_offset =
                        self.read_abi_type(abi_type, buffer, item_offset, array_base_offset);
                }

                if !is_dynamic_type {
                    return item_offset;
                }
            }
            _ => {
                // Read uint256 worth of bytes into the buffer
                self.buffer_until(buffer, base_offset + relative_offset + 32);
            }
        };
        // Return the next offset to process
        relative_offset + 32
    }

    fn buffer_until(&mut self, buffer: &mut Vec<u8>, length: usize) {
        if length > buffer.len() {
            let slice_size = length - buffer.len();
            let mut extra_input = vec![0u8; slice_size];
            self.reader.read_slice(&mut extra_input);
            // env::read_slice(&mut extra_input);
            buffer.append(&mut extra_input);
        }
    }

    fn read_usize(
        &mut self,
        buffer: &mut Vec<u8>,
        relative_offset: usize,
        base_offset: usize,
    ) -> usize {
        // Derive u256 aligned indices
        let usize_start = base_offset + relative_offset;
        let usize_end = usize_start + 32;
        // Ensure the offset bytes are loaded into the buffer
        self.buffer_until(buffer, usize_end);
        // Read the offset value
        U256::from(&buffer[usize_start..usize_end]).as_usize()
    }
}

pub fn decode_eth_abi_input(types: &[ParamType]) -> Result<Vec<Token>, ethabi::Error> {
    ethabi::decode(types, &read_eth_abi_input(types))
}

pub fn decode_whole_eth_abi_input(types: &[ParamType]) -> Result<Vec<Token>, ethabi::Error> {
    ethabi::decode_whole(types, &read_eth_abi_input(types))
}

fn read_eth_abi_input(types: &[ParamType]) -> Vec<u8> {
    let mut reader = EthABIReader::default();
    let mut input = Vec::new();
    reader.read_abi_encoded_input(types, &mut input, 0, 0);
    input
}
