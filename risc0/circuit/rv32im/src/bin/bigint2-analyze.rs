// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#[cfg(feature = "execute")]
pub fn main() -> anyhow::Result<()> {
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
