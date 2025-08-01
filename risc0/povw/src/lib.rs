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

//! Proof of Verifiable Work (PoVW) implementation.
//!
//! This crate provides Merkle tree-based data structures for tracking and proving work
//! completed during ZK proof generation. The main components include:
//!
//! - [`WorkSet`]: Top-level container for multiple work logs
//! - [`WorkLog`]: Collection of jobs within a single prover's work log
//! - [`Job`]: Representation of a range of used nonces in a job (i.e. a single continuation)
//! - [`Bitmap`]: 256-bit bitmap for efficient nonce tracking
//!
//! The implementation uses Merkle trees to enable efficient proofs of inclusion and
//! non-inclusion for nonces, supporting the PoVW system's requirement to prevent
//! double-counting of work.

#![deny(rustdoc::broken_intra_doc_links)]
#![deny(missing_docs)]
#![cfg_attr(docsrs, feature(doc_cfg, doc_auto_cfg))]

mod consts;
mod error;
/// Log Builder guest program types, for verifying PoVW log updates.
pub mod guest;
/// Prover functionality, for running the work log builder.
#[cfg(feature = "prover")]
pub mod prover;
mod tree;

pub use error::Error;
pub use tree::{
    Bitmap, Job, Merkleized, MerkleizedIndex, Opening, SubtreeOpening, WorkLog, WorkSet,
};
