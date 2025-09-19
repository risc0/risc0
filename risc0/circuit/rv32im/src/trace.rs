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

extern crate alloc;

use alloc::vec::Vec;

use anyhow::Result;
use derive_more::Debug;
use serde::{Deserialize, Serialize};

/// An event traced from the running VM.
#[derive(Clone, Debug, Eq, Ord, PartialEq, PartialOrd, Serialize, Deserialize)]
#[non_exhaustive]
pub enum TraceEvent {
    /// An instruction has started at the given program counter
    InstructionStart {
        /// Cycle number since startup
        cycle: u64,

        /// Program counter of the instruction being executed
        #[debug("{pc:#010x}")]
        pc: u32,

        /// Encoded instruction being executed.
        #[debug("{pc:#010x}")]
        insn: u32,
    },

    /// A register has been set
    RegisterSet {
        /// Register ID (0-16)
        idx: usize,

        /// New value in the register
        #[debug("{value:#010x}")]
        value: u32,
    },

    /// A memory location has been written
    MemorySet {
        /// Address of memory that's been written
        #[debug("{addr:#010x}")]
        addr: u32,

        /// Data that's been written
        #[debug("{region:#04x?}")]
        region: Vec<u8>,
    },

    /// A page is read for the first time in a segment
    PageIn { cycles: u64 },

    /// A page has been written to for the first time in a segment
    PageOut { cycles: u64 },
}

/// A callback used to collect [TraceEvent]s.
pub trait TraceCallback {
    fn trace_callback(&mut self, event: TraceEvent) -> Result<()>;
}

impl<F: FnMut(TraceEvent) -> Result<()>> TraceCallback for F {
    fn trace_callback(&mut self, event: TraceEvent) -> Result<()> {
        self(event)
    }
}
