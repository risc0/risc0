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
#![no_std]

use risc0_zkvm::guest::env;
use risc0_zkvm::sha::{Impl, Sha256};
use digital_signature_core::{SignMessageCommit, SigningRequest};

risc0_zkvm::guest::entry!(main);

pub fn main() {
    let request: SigningRequest = env::read();
    env::commit(&SignMessageCommit {
        identity: *Impl::hash_bytes(&request.passphrase.pass),
        msg: request.msg,
    });
}
