// Copyright 2024 RISC Zero, Inc.
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

/// EVM bytecode configuration
pub struct EvmConfig {
    /// Simple EVM bytecode that stores a value and returns it
    /// PUSH1 0x42 PUSH1 0x00 MSTORE PUSH1 0x20 PUSH1 0x00 RETURN
    pub bytecode: Vec<u8>,
}

impl Default for EvmConfig {
    fn default() -> Self {
        Self {
            bytecode: hex::decode("604260005260206000f3").unwrap(),
        }
    }
}

impl EvmConfig {
    /// Create a new EVM config with custom bytecode
    pub fn new(bytecode_hex: &str) -> Result<Self, hex::FromHexError> {
        let bytecode = hex::decode(bytecode_hex)?;
        Ok(Self { bytecode })
    }
    
    /// Get the bytecode as a reference
    pub fn get_bytecode(&self) -> &[u8] {
        &self.bytecode
    }
    
    /// Get the bytecode as owned Vec
    pub fn get_bytecode_owned(&self) -> Vec<u8> {
        self.bytecode.clone()
    }
}
