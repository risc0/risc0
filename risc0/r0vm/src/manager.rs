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

use std::{collections::BTreeMap, error::Error as StdError, path::Path};

use kameo::prelude::*;

use crate::{
    protocol::{ExecuteTask, ExecuteTaskRequest, SegmentReady, SessionDone},
    Cli,
};

pub(crate) async fn main(args: &Cli, path: &Path) -> Result<(), Box<dyn StdError>> {
    let addr = "/ip4/0.0.0.0/udp/9000/quic-v1".parse()?;
    println!("addr: {addr}");

    ActorSwarm::bootstrap()?.listen_on(addr).await?;

    let binary = std::fs::read(path).unwrap();

    let task_mgr = kameo::spawn(TaskManagerActor::new(binary));
    task_mgr.register("task_mgr").await?;

    task_mgr.wait_for_stop().await;

    Ok(())
}

#[derive(Actor, RemoteActor)]
pub(crate) struct TaskManagerActor {
    binary: Vec<u8>,
    tasks: BTreeMap<u32, u32>,
}

impl TaskManagerActor {
    pub fn new(binary: Vec<u8>) -> Self {
        Self {
            binary,
            tasks: BTreeMap::new(),
        }
    }
}

#[remote_message("4e3fe8bd-9bcf-4315-bd7b-37440a81d323")]
impl Message<ExecuteTaskRequest> for TaskManagerActor {
    type Reply = ExecuteTask;

    async fn handle(
        &mut self,
        msg: ExecuteTaskRequest,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        ExecuteTask {
            binary: self.binary.clone(),
            input: vec![],
        }
    }
}

#[remote_message("8557f8c6-b117-4077-95d8-3ce979ba1b4e")]
impl Message<SegmentReady> for TaskManagerActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: SegmentReady,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        tracing::info!("Got segment: {}", msg.0.index);
    }
}

#[remote_message("92ede8bb-7428-498f-99ca-805f763bfcab")]
impl Message<SessionDone> for TaskManagerActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: SessionDone,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        tracing::info!("Session done");
        ctx.actor_ref().stop_gracefully().await.unwrap();
    }
}
