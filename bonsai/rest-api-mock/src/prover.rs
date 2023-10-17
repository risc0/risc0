// Copyright 2023 RISC Zero, Inc.
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

use std::{
    fmt,
    sync::{Arc, RwLock},
};

use anyhow::Context;
use risc0_zkvm::{
    ExecutorEnv, ExecutorImpl, InnerReceipt, MemoryImage, Program, Receipt, GUEST_MAX_MEM,
    PAGE_SIZE,
};
use tokio::sync::mpsc;

use crate::{error::Error, state::BonsaiState};

#[derive(Debug, Clone)]
pub(crate) struct Task {
    pub session_id: String,
    pub image_id: String,
    pub input_id: String,
}

#[derive(Debug)]
pub(crate) enum ProverMessage {
    RunSession(Task),
}

impl fmt::Display for ProverMessage {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            ProverMessage::RunSession(task) => {
                write!(f, "ProverMessage::RunSession: {{ task: {:?} }}", task)
            }
        }
    }
}

#[derive(Clone)]
pub(crate) struct ProverHandle {
    pub sender: mpsc::Sender<ProverMessage>,
}

impl ProverHandle {
    pub(crate) async fn execute(&self, task: Task) {
        let msg = ProverMessage::RunSession(task);

        if (self.sender.send(msg).await).is_err() {
            tracing::info!("receiver dropped");
            assert!(self.sender.is_closed());
        }
    }
}

const ELF_MAGIC: [u8; 4] = [0x7f, 0x45, 0x4c, 0x46];

pub(crate) struct Prover {
    pub(crate) receiver: mpsc::Receiver<ProverMessage>,
    pub(crate) storage: Arc<RwLock<BonsaiState>>,
}

impl Prover {
    pub(crate) fn new(
        receiver: mpsc::Receiver<ProverMessage>,
        storage: Arc<RwLock<BonsaiState>>,
    ) -> Self {
        Prover { receiver, storage }
    }

    pub async fn handle_message(&mut self, msg: &ProverMessage) -> Result<(), Error> {
        match msg {
            ProverMessage::RunSession(task) => {
                tracing::info!("Running task...");
                let image = self.get_image(task).await?;
                let input = self.get_input(task).await?;
                let mem_img = image.as_slice();
                let mem_img = if mem_img[0..ELF_MAGIC.len()] == ELF_MAGIC {
                    tracing::info!("Loading guest image from ELF binary");
                    let program = Program::load_elf(mem_img, GUEST_MAX_MEM as u32)?;
                    MemoryImage::new(&program, PAGE_SIZE as u32)?
                } else {
                    bincode::deserialize(mem_img).context("failed to decode memory image")?
                };

                let env = ExecutorEnv::builder()
                    .write_slice(&input)
                    .session_limit(None)
                    .segment_limit_po2(20)
                    .build()
                    .map_err(|e| {
                        anyhow::anyhow!("failed to build executor environment: {:?}", e)
                    })?;
                let mut exec = ExecutorImpl::new(env, mem_img)?;
                let session = exec
                    .run()
                    .context("Executor failed to generate a successful session")?;

                let receipt = Receipt {
                    inner: InnerReceipt::Fake,
                    journal: session.journal,
                };
                let receipt_bytes = bincode::serialize(&receipt)?;
                self.storage
                    .write()?
                    .put_receipt(task.session_id.clone(), receipt_bytes);
                self.storage
                    .write()?
                    .put_session(task.session_id.clone(), "SUCCEEDED".to_string());
            }
        }

        Ok(())
    }

    pub(crate) async fn run(&mut self) -> Result<(), Error> {
        while let Some(msg) = self.receiver.recv().await {
            tracing::info!("Receiver: {}", &msg);
            match self.handle_message(&msg).await {
                Ok(_) => tracing::info!("Task done!"),
                Err(err) => {
                    match &msg {
                        ProverMessage::RunSession(task) => self
                            .storage
                            .write()?
                            .put_session(task.session_id.clone(), "FAILED".to_string()),
                    };
                    tracing::error!("Task {} failed! - {:?}", msg, err)
                }
            }
        }
        Ok(())
    }

    async fn get_image(&self, task: &Task) -> Result<Vec<u8>, Error> {
        Ok(self
            .storage
            .read()?
            .get_image(&task.image_id)
            .ok_or_else(|| anyhow::anyhow!("Failed to get image for ID: {:?}", task.image_id))?)
    }

    async fn get_input(&self, task: &Task) -> Result<Vec<u8>, Error> {
        Ok(self
            .storage
            .read()?
            .get_input(&task.input_id)
            .ok_or_else(|| anyhow::anyhow!("Failed to get input for ID: {:?}", task.input_id))?)
    }
}
