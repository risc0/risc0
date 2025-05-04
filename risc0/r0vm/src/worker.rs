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

#![allow(unused)]

use std::{error::Error as StdError, time::Duration};

use anyhow::Context as _;
use kameo::{prelude::*, remote::dial_opts::DialOpts};
use risc0_zkvm::{ExecutorEnv, ExecutorImpl, NullSegmentRef, Segment};
use tokio::task::JoinHandle;

use crate::{
    manager::TaskManagerActor,
    protocol::{ExecuteTaskRequest, SegmentReady, SessionDone, SessionWrapper},
    Cli,
};

const CONCURRENT_SEGMENTS: usize = 50; // This peaks around ~4GB

pub(crate) async fn main(args: Cli) -> Result<(), Box<dyn StdError>> {
    ActorSwarm::bootstrap()?
        .dial(
            DialOpts::unknown_peer_id()
                .address("/ip4/127.0.0.1/udp/9000/quic-v1".parse()?)
                .build(),
        )
        .await?;

    tokio::time::sleep(Duration::from_millis(50)).await;

    let task_mgr = RemoteActorRef::<TaskManagerActor>::lookup("task_mgr")
        .await?
        .unwrap();

    let task = task_mgr.ask(&ExecuteTaskRequest).await?;
    println!("ELF: {} bytes", task.binary.len());

    let (segment_tx, mut segment_rx) = tokio::sync::mpsc::channel::<Segment>(CONCURRENT_SEGMENTS);

    let task_mgr_relay = task_mgr.clone();
    let segment_relay = tokio::task::spawn(async move {
        while let Some(segment) = segment_rx.recv().await {
            task_mgr_relay.tell(&SegmentReady(segment)).await.unwrap();
        }
    });

    let result: JoinHandle<anyhow::Result<SessionWrapper>> =
        tokio::task::spawn_blocking(move || {
            let env = ExecutorEnv::builder()
                .write_slice(&task.input)
                .build()
                .unwrap();
            let mut exec = ExecutorImpl::from_elf(env, &task.binary).unwrap();
            let session = exec.run_with_callback(|segment| {
                segment_tx.blocking_send(segment).unwrap();
                Ok(Box::new(NullSegmentRef))
            })?;

            // This will cause the segment_relay loop to terminate.
            drop(segment_tx);

            let session = SessionWrapper {
                segment_count: session.segments.len(),
                user_cycles: session.user_cycles,
                total_cycles: session.total_cycles,
                journal: session.journal,
            };

            Ok(session)
        });

    let session = result
        .await
        .context("Failed to join executor run_with_callback task")?
        .context("execution failed")?;

    segment_relay.await?;

    task_mgr.tell(&SessionDone(session)).await?;

    Ok(())
}
