// Copyright 2024 RISC Zero, Inc.
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
#![deny(rustdoc::broken_intra_doc_links)]
#![cfg_attr(docsrs, feature(doc_cfg, doc_auto_cfg))]

//! The recursion VM is a non-Turing-complete virtual machine (VM)
//! optimized for algebraic constraint checking. In particular, it is
//! well-tuned for verifying STARKs.
//!
//! The recursion VM runs "recursion programs", which define the
//! functionality it will implement.  As examples, the [lift], [join],
//! and [resolve] programs are used by the risc0 ZkVM to compress a
//! collection of STARK receipts for a composition into a single
//! succinct receipt.
//!
//! This is a low-level interface; users should prefer to use the
//! `risc0_zkvm` crate.

extern crate alloc;

#[cfg(feature = "prove")]
pub mod prove;

pub mod merkle;
