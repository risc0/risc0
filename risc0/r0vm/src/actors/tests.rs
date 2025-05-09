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

use kameo::{actor::RemoteActorRef, remote::ActorSwarm};
use risc0_zkvm_methods::FIB_ELF;

use crate::actors::{
    factory::FactoryActor,
    manager::TaskManagerActor,
    protocol::{ProofRequest, TaskKind},
    worker::Worker,
};

#[test_log::test(tokio::test(flavor = "multi_thread"))]
async fn basic() {
    tracing::info!("basic");

    ActorSwarm::bootstrap().unwrap();

    let factory = kameo::spawn(FactoryActor::new());
    factory.register("factory").await.unwrap();

    let task_mgr = kameo::spawn(TaskManagerActor::new(factory.clone()));

    let factory_ref = RemoteActorRef::<FactoryActor>::lookup("factory")
        .await
        .unwrap()
        .unwrap();

    let task_kinds = vec![
        TaskKind::Execute,
        TaskKind::ProveSegment,
        TaskKind::Lift,
        TaskKind::Join,
    ];
    let mut worker = Worker::new(factory_ref, task_kinds);
    worker.start();

    const ITERATIONS: u32 = 300_000;
    task_mgr
        .tell(ProofRequest {
            binary: FIB_ELF.to_vec(),
            input: u32::to_le_bytes(ITERATIONS).to_vec(),
        })
        .await
        .unwrap();
    task_mgr.wait_for_stop().await;
    tracing::info!("task_mgr stopped");

    tracing::info!("waiting on worker");
    worker.stop().await;
    tracing::info!("worker stopped");

    factory.stop_gracefully().await.unwrap();
    tracing::info!("waiting on factory");
    factory.wait_for_stop().await;
    tracing::info!("factory stopped");
}
