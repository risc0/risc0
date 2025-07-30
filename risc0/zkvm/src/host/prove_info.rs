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

//! Struct containing information about a prover's execution including the receipt.

use serde::{Deserialize, Serialize};

use crate::{receipt::GenericReceipt, Receipt, ReceiptClaim, WorkClaim};

/// Information returned by the prover including receipt as well as other information useful for debugging
#[derive(Debug, Serialize, Deserialize)]
#[non_exhaustive]
pub struct ProveInfo {
    /// receipt from the computation
    pub receipt: Receipt,

    /// stats about cycle counts of the execution
    pub stats: SessionStats,

    /// Work claim receipt proving the work completed in the process of producing the proof.
    ///
    /// This receipt will be produced by provers that support Proof of Verifiable Work when a
    /// [`PovwJobId`][risc0_binfmt::PovwJobId] is provided in the [`ExecutorEnv`][crate::ExecutorEnv].
    /// This receipt provides a proof of work completed for this job, and can be combined into a
    /// work log using the [Log Builder guest][risc0-povw].
    ///
    /// Note that this receipt will not be provided if the [`ProverOpts`][crate::ProverOpts] has a
    /// compression level of [`ReceiptKind::Composite`][crate::ReceiptKind]. A
    /// [`CompositeReceipt`][crate::CompositeReceipt] can be used to produce a work receipt by
    /// using [`ProverServer::composite_to_succinct_povw`][crate::ProverServer].
    pub work_receipt: Option<GenericReceipt<WorkClaim<ReceiptClaim>>>,
}

/// Struct containing information about a prover's cycle count after running the guest program
#[derive(Debug, Serialize, Deserialize)]
#[non_exhaustive]
pub struct SessionStats {
    /// Count of segments in this proof request
    pub segments: usize,

    /// Total cycles run within guest
    pub total_cycles: u64,

    /// User cycles run within guest
    pub user_cycles: u64,

    /// Paging cycles run within guest
    pub paging_cycles: u64,

    /// Reserved cycles run within guest
    pub reserved_cycles: u64,
}
