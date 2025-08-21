// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#[cfg(any(feature = "client", feature = "prove"))]
pub(crate) mod api;
#[cfg(feature = "client")]
pub(crate) mod client;
#[cfg(any(feature = "client", feature = "prove"))]
mod protos;
pub(crate) mod prove_info;
pub mod recursion;
#[cfg(feature = "client")]
pub(crate) mod rpc;
#[cfg(feature = "prove")]
pub(crate) mod server;
