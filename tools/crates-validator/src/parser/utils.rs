// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{fmt::Display, fs};

use anyhow::{Context, Result};

pub(crate) fn read_profile(path: impl AsRef<str> + Display) -> Result<String> {
    fs::read_to_string(path.as_ref())
        .with_context(|| format!("Failed to read profile file: {path}",))
}
