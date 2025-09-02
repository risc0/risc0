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

use revm_core::config::EvmConfig;
use revm_core::execute_evm_bytecode;
use revm_methods::REVM_GUEST_ID;

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    // Load EVM configuration
    let config = EvmConfig::default();

    println!(
        "Executing EVM bytecode {} with function signature {} and input {}",
        hex::encode(config.get_bytecode_owned()),
        config.get_function_signature(),
        config.get_input()
    );

    // Execute the bytecode inside the zkVM
    let (receipt, return_value) = execute_evm_bytecode(config);

    // Here is where one would send 'receipt' over the network...

    // Verify receipt, panic if it's wrong
    receipt.verify(REVM_GUEST_ID).expect(
        "Code you have proven should successfully verify; did you specify the correct image ID?",
    );

    println!(
        "✓ Receipt verified! EVM bytecode returned: {:02x?}",
        return_value
    );
}
