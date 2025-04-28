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

use anyhow::Result;

#[cfg(feature = "execute")]
pub fn main() -> Result<()> {
    let path = std::env::args()
        .nth(1)
        .expect("expected path to bigint program");
    let bytes = std::fs::read(path)?;
    risc0_circuit_rv32im::execute::bigint_analyze(&bytes)
}

#[cfg(not(feature = "execute"))]
pub fn main() {
    panic!("not compiled with \"execute\" or \"prove\" feature");
}
