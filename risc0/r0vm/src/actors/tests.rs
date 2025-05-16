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

use risc0_zkvm_methods::{FIB_ELF, FIB_ID};

use crate::actors::protocol::JobStatus;

use super::{protocol::TaskKind, App};

#[test_log::test(tokio::test(flavor = "multi_thread"))]
async fn basic() {
    tracing::info!("basic");

    let task_kinds = vec![
        TaskKind::Execute,
        TaskKind::ProveSegment,
        TaskKind::Lift,
        TaskKind::Join,
    ];

    let mut app = App::new(true, task_kinds, None, None, true).await.unwrap();

    const ITERATIONS: u32 = 300_000;

    let info = app
        .run_binary(FIB_ELF.to_vec(), u32::to_le_bytes(ITERATIONS).to_vec())
        .await
        .unwrap();

    let JobStatus::Succeeded(result) = info.status else {
        panic!("Invalid status");
    };

    result.receipt.verify(FIB_ID).unwrap();

    app.stop().await;
}
