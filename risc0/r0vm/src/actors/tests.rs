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

use std::{
    net::{Ipv4Addr, SocketAddrV4},
    time::Duration,
};

use assert_matches::assert_matches;
use risc0_zkvm::DevModeDelay;
use risc0_zkvm_methods::FIB_ELF;

use super::{
    App,
    config::{AppConfig, ExecutorConfig, ManagerConfig, StorageConfig, VERSION},
    protocol::{JobStatus, ProofRequest, ShrinkWrapKind, ShrinkWrapRequest, TaskKind},
};

const PROFILE_RTX_5090: DevModeDelay = DevModeDelay {
    prove_segment_core: Duration::from_millis(500),
    segment_preflight: Duration::from_millis(300),
    prove_keccak: Duration::from_millis(250),
    lift: Duration::from_millis(150),
    join: Duration::from_millis(250),
    union: Duration::from_millis(250),
    resolve: Duration::from_millis(250),
    shrink_wrap_groth16: Duration::from_millis(3_760),
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
        TaskKind::ProveSegment,
        TaskKind::Lift,
        TaskKind::Join,
        TaskKind::ShrinkWrap,
    ];

    let storage_root = assert_fs::TempDir::new().unwrap();

    let po2 = Some(21);
    let addr = remote.then_some(SocketAddrV4::new(Ipv4Addr::UNSPECIFIED, 0).into());
    let mut app = App::new(
        AppConfig {
            version: VERSION,
            api: None,
            manager: Some(ManagerConfig { listen: addr }),
            executor: Some(ExecutorConfig {
                manager: None,
                count: 1,
            }),
            prover: Some(vec![crate::actors::config::ProverConfig {
                manager: None,
                count: Some(100),
                subscribe: task_kinds.clone(),
                simulate: Some(PROFILE_RTX_5090),
            }]),
            storage: Some(StorageConfig {
                path: storage_root.to_path_buf(),
            }),
            telemetry: None,
        },
        /*enable_logging=*/ false,
    )
    .await
    .unwrap();

    const ITERATIONS: u32 = 300000;

    let request = ProofRequest {
        binary: FIB_ELF.to_vec(),
        input: u32::to_le_bytes(ITERATIONS).to_vec(),
        assumptions: vec![],
        segment_limit_po2: po2,
        execute_only: false,
    };

    let info = app.proof_request(request).await.unwrap();

    tracing::info!("xproof_request result = {info:#?}");

    let result = assert_matches!(info.status, JobStatus::Succeeded(r) => r);

    let request = ShrinkWrapRequest {
        kind: ShrinkWrapKind::Groth16,
        receipt: (*result.receipt.unwrap()).clone(),
    };

    let info = app.shrink_wrap_request(request).await.unwrap();

    tracing::info!("shrink_wrap_request result = {info:#?}");

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
