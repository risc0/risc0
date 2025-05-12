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

use kameo::prelude::*;
use tokio::task::JoinSet;

use super::{
    factory::FactoryActor,
    job::JobActor,
    protocol::{ProofReply, ProofRequest},
};

#[derive(Actor)]
pub(crate) struct ManagerActor {
    factory: ActorRef<FactoryActor>,
    join_set: JoinSet<()>,
}

impl ManagerActor {
    pub fn new(factory: ActorRef<FactoryActor>) -> Self {
        Self {
            factory,
            join_set: JoinSet::new(),
        }
    }
}

impl Message<ProofRequest> for ManagerActor {
    type Reply = DelegatedReply<ProofReply>;

    async fn handle(
        &mut self,
        msg: ProofRequest,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let (delegated_reply, mut reply_sender) = ctx.reply_sender();
        let factory = self.factory.clone();

        self.join_set.spawn(async move {
            let job = kameo::spawn(JobActor::new(factory));
            let reply = job.ask(msg).await.unwrap();
            job.wait_for_stop().await;
            reply_sender.take().unwrap().send(reply);
        });

        delegated_reply
    }
}
