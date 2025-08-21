// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use crate::types::{profile::Profile, profile_settings::ProfileSettings};

pub(crate) fn profile_with_settings(args: (impl ToString, ProfileSettings)) -> Profile {
    Profile::new(args.0.to_string(), args.1, None).unwrap()
}
