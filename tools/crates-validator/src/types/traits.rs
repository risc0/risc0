// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use serde_valid::validation::Errors as ValidationErrors;

use super::aliases::GroupedProfiles;

pub trait Group {
    fn group(self) -> GroupedProfiles;
}

pub trait Merge {
    fn merge(self, other: Self) -> Self;
}

pub trait Reduce {
    fn reduce(self) -> Self;
}

pub trait Exclude {
    fn exclude(self, other: Self) -> Self;
}

pub trait GetVersions {
    fn get_versions(&self) -> Vec<semver::Version>;
}

pub trait IsValid {
    fn is_valid(&self) -> Result<(), ValidationErrors>;
}
