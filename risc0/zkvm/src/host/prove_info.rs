// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! Struct containing information about a prover's execution including the receipt.

use enum_map::{Enum, EnumMap};
use serde::{Deserialize, Serialize};

use alloc::vec::Vec;
use core::{fmt, time::Duration};

use crate::{Receipt, ReceiptClaim, WorkClaim, receipt::GenericReceipt};
use risc0_circuit_rv32im::{EcallKind, EcallMetric};

#[derive(Clone, Debug, Enum, Serialize, Deserialize)]
#[non_exhaustive]
pub enum SyscallKind {
    Keccak,
    ProveKeccak,
    Read,
    VerifyIntegrity,
    VerifyIntegrity2,
    Write,
}

#[derive(Clone, Debug, Default, Serialize, Deserialize)]
#[non_exhaustive]
pub struct SyscallMetric {
    pub count: u64,
    pub size: u64,
}

/// Information returned by the prover including receipt as well as other information useful for debugging
#[derive(Clone, Debug, Serialize, Deserialize)]
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
#[derive(Clone, Default, Debug, Serialize, Deserialize)]
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

    /// ecall metrics grouped by kind.
    pub ecall_metrics: EnumMap<EcallKind, Option<EcallMetric>>,

    /// syscall metrics grouped by kind.
    pub syscall_metrics: EnumMap<SyscallKind, Option<SyscallMetric>>,

    /// Execution elapsed time.
    pub execution_time: Option<Duration>,
}

impl SessionStats {
    /// Logs session information at info level if `RISC0_INFO` environment variable is set.
    #[cfg(feature = "std")]
    pub fn log_if_risc0_info_set(&self) {
        if std::env::var_os("RISC0_INFO").is_some() {
            for line in self.to_string().lines() {
                tracing::info!("{line}");
            }
        }
    }
}

impl fmt::Display for SessionStats {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let pct = |cycles: u64| cycles as f64 / self.total_cycles as f64 * 100.0;

        if let Some(execution_time) = self.execution_time {
            writeln!(f, "execution time: {execution_time:?}")?;
        }
        writeln!(f, "number of segments: {}", self.segments)?;
        writeln!(f, "{} total cycles", self.total_cycles)?;
        writeln!(
            f,
            "{} user cycles ({:.2}%)",
            self.user_cycles,
            pct(self.user_cycles)
        )?;
        writeln!(
            f,
            "{} paging cycles ({:.2}%)",
            self.paging_cycles,
            pct(self.paging_cycles)
        )?;
        writeln!(
            f,
            "{} reserved cycles ({:.2}%)",
            self.reserved_cycles,
            pct(self.reserved_cycles)
        )?;

        writeln!(f, "ecalls")?;
        let mut ecall_metrics: Vec<_> = self
            .ecall_metrics
            .iter()
            .filter_map(|(k, v)| v.as_ref().map(|v| (k, v)))
            .collect();
        ecall_metrics.sort_by(|a, b| a.1.cycles.cmp(&b.1.cycles));
        for (name, metric) in ecall_metrics.iter().rev() {
            writeln!(
                f,
                "\t{} {name:?} calls, {} cycles, ({:.2}%)",
                metric.count,
                metric.cycles,
                pct(metric.cycles)
            )?;
        }

        writeln!(f, "syscalls")?;
        let mut syscall_metrics: Vec<_> = self
            .syscall_metrics
            .iter()
            .filter_map(|(k, v)| v.as_ref().map(|v| (k, v)))
            .collect();
        syscall_metrics.sort_by(|a, b| a.1.count.cmp(&b.1.count));
        for (name, metric) in syscall_metrics.iter().rev() {
            writeln!(f, "\t{} {name:?} calls", metric.count)?;
        }

        Ok(())
    }
}
