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

use std::{sync::Arc, time::Duration};

use serde::{Deserialize, Serialize};

use crate::{AssumptionReceipt, Journal, Receipt};

/// TODO
#[derive(Serialize, Deserialize)]
pub struct ProofRequest {
    /// TODO
    pub binary: Vec<u8>,

    /// TODO
    pub input: Vec<u8>,

    /// TODO
    pub assumptions: Vec<AssumptionReceipt>,

    /// TODO
    pub segment_limit_po2: Option<u32>,
}

/// TODO
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct JobInfo {
    /// TODO
    pub status: JobStatus,

    /// TODO
    pub elapsed_time: Duration,
}

/// TODO
#[derive(Clone, Debug, Serialize, Deserialize)]
pub enum JobStatus {
    /// TODO
    Running(String),

    /// TODO
    Succeeded(ProofResult),

    /// TODO
    Failed(TaskError),

    /// TODO
    TimedOut,

    /// TODO
    Aborted,
}

/// TODO
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct ProofResult {
    /// TODO
    pub session: Arc<Session>,

    /// TODO
    pub receipt: Arc<Receipt>,
}

/// TODO
#[derive(Debug, Serialize, Deserialize)]
pub struct Session {
    /// TODO
    pub segment_count: usize,

    /// TODO
    pub user_cycles: u64,

    /// TODO
    pub total_cycles: u64,

    /// TODO
    pub journal: Option<Journal>,

    /// TODO
    pub assumptions: Vec<Arc<AssumptionReceipt>>,
}

/// TODO
#[derive(Clone, Debug, Serialize, Deserialize)]
pub enum TaskError {
    /// TODO
    Generic(String),
}

impl JobStatus {
    /// TODO
    pub fn bonsai_status(&self) -> &str {
        match self {
            JobStatus::Running(_) => "RUNNING",
            JobStatus::Succeeded(_) => "SUCCEEDED",
            JobStatus::Failed(_) => "FAILED",
            JobStatus::TimedOut => "TIMED_OUT",
            JobStatus::Aborted => "ABORTED",
        }
    }
}

impl From<anyhow::Error> for TaskError {
    fn from(value: anyhow::Error) -> Self {
        Self::Generic(value.to_string())
    }
}
