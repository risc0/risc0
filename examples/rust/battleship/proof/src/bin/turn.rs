// Copyright 2022 Risc0, Inc.
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

use risc0::{env, sha};

use battleship_proof::RoundParams;

risc0::entry!(main);

pub fn main() {
    let params: RoundParams = env::read();
    let result = params.process();
    env::write(&result);
    env::commit_digest(&sha::digest(params.state));
    env::commit_digest(&sha::digest(result.state));
    env::commit(&params.shot);
    env::commit(&result.hit);
}
