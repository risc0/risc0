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

use kameo::Reply;
use risc0_zkvm::{Journal, Segment};
use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
pub(crate) enum TaskKind {
    Execute,
    ProveSegment,
    Lift,
    Join,
}

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct TaskRequest(pub TaskKind);

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct ExecuteTaskRequest;

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct ExecuteTask {
    pub binary: Vec<u8>,
    pub input: Vec<u8>,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct SegmentReady(pub Segment);

#[derive(Serialize, Deserialize)]
pub(crate) struct SessionWrapper {
    pub(crate) segment_count: usize,
    pub(crate) user_cycles: u64,
    pub(crate) total_cycles: u64,
    pub(crate) journal: Option<Journal>,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct SessionDone(pub SessionWrapper);
