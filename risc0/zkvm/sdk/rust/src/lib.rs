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

#![cfg_attr(not(feature = "std"), no_std)]
#![cfg_attr(target_arch = "riscv32", feature(alloc_error_handler))]
#![cfg_attr(target_arch = "riscv32", feature(new_uninit))]

extern crate alloc;

#[cfg(not(any(target_arch = "riscv32", feature = "bazel")))]
pub mod build;
pub mod core;
#[cfg(feature = "prove")]
pub mod elf;
#[cfg(target_arch = "riscv32")]
pub mod guest;
#[cfg(all(not(target_arch = "riscv32"), feature = "std"))]
pub mod host;
pub mod platform;
pub mod serde;
