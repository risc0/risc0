// Copyright 2026 RISC Zero, Inc.
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

//! Core RISC Zero functionality shared across multiple crates
//!
//! This crate contains fundamental code that multiple RISC Zero crates rely on,
//! most notably representing finite field elements and enabling finite field
//! arithmetic.

#![cfg_attr(not(feature = "std"), no_std)]
#![deny(missing_docs)]
#![deny(rustdoc::broken_intra_doc_links)]
#![cfg_attr(docsrs, feature(doc_cfg))]

extern crate alloc;

pub mod field;
#[cfg(feature = "perf")]
pub mod perf;
