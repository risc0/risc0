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

use std::net::{Ipv4Addr, SocketAddrV4};
use std::time::Duration;

use risc0_zkvm::DevModeDelay;
use risc0_zkvm_methods::FIB_ELF;

use crate::actors::{protocol::JobStatus, PoolConfig, SimulationConfig};

use super::{protocol::TaskKind, App};

const PROFILE_RTX_5090: DevModeDelay = DevModeDelay {
    prove_segment: Duration::from_millis(800),
    prove_keccak: Duration::from_millis(250),
    lift: Duration::from_millis(150),
    join: Duration::from_millis(250),
    union: Duration::from_millis(250),
    resolve: Duration::from_millis(250),
};

// const PROFILE_L40S: DevModeDelay = DevModeDelay {
//     prove_segment: Duration::from_millis(1600),
//     prove_keccak: Duration::from_millis(350),
//     lift: Duration::from_millis(250),
//     join: Duration::from_millis(350),
//     union: Duration::from_millis(350),
//     resolve: Duration::from_millis(350),
// };

async fn do_test(remote: bool) {
    let task_kinds = vec![
        TaskKind::Execute,
        TaskKind::ProveSegment,
        TaskKind::Lift,
        TaskKind::Join,
    ];

    let storage_root = assert_fs::TempDir::new().unwrap();

    let config = SimulationConfig {
        pools: vec![PoolConfig {
            count: 100,
            profile: PROFILE_RTX_5090,
            task_kinds: task_kinds.clone(),
        }],
    };

    let addr = remote.then_some(SocketAddrV4::new(Ipv4Addr::UNSPECIFIED, 0).into());
    let mut app = App::new(
        /* is_manager */ true,
        task_kinds,
        addr,
        /* api_addr */ None,
        Some(storage_root.to_path_buf()),
        Some(config),
        21,
    )
    .await
    .unwrap();

    const ITERATIONS: u32 = 30_000_000;

    let info = app
        .run_binary(FIB_ELF.to_vec(), u32::to_le_bytes(ITERATIONS).to_vec())
        .await
        .unwrap();

    tracing::info!("{info:#?}");

    assert!(matches!(info.status, JobStatus::Succeeded(_result)));

    app.stop().await;
}

#[test_log::test(tokio::test(flavor = "multi_thread"))]
#[cfg_attr(feature = "disable-dev-mode", ignore)]
async fn basic_local() {
    tracing::info!("basic (local)");

    do_test(/* remote */ false).await
}

#[test_log::test(tokio::test(flavor = "multi_thread"))]
#[cfg_attr(feature = "disable-dev-mode", ignore)]
async fn basic_remote() {
    tracing::info!("basic (remote)");

    do_test(/* remote */ true).await
}
