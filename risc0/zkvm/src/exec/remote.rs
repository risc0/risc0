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

/// This module implements the [RemoteExecutor]. The remote executor runs the
/// guest programs by using a remote proving service.
use ::bonsai_sdk::{alpha as bonsai_sdk, alpha::SdkErr};
use anyhow::Result;

use super::Executor;
use crate::{receipt::ExitCode, ExecutorEnv, MemoryImage, Session};

pub struct RemoteExecutor<'a> {
    env: ExecutorEnv<'a>,
    image: MemoryImage,
}

impl<'a> RemoteExecutor<'a> {
    pub fn new(env: ExecutorEnv<'a>, image: MemoryImage) -> Self {
        Self { env, image }
    }
}

impl<'a> Executor for RemoteExecutor<'a> {
    fn run(&mut self) -> Result<Session> {
        let client = bonsai_sdk::Client::from_env()?;

        // upload the image
        let image_id = hex::encode(self.image.compute_id());
        let image = bincode::serialize(&self.image)?;

        // ImageIdExists indicates that this image has already been uploaded to bonsai.
        // If this is the case, simply move on to uploading the input.
        match client.upload_img(&image_id, image) {
            Ok(()) => (),
            Err(SdkErr::ImageIdExists) => (),
            Err(err) => return Err(err.into()),
        }

        // upload input data
        let input_id = client.upload_input(self.env.input.clone())?;

        // While this is the executor, we want to start a session on the bonsai prover.
        // By doing so, we can return a session ID so that the prover can use it to
        // retrieve the receipt.
        let session = client.create_session(image_id, input_id)?;
        Ok(Session::new_with_id(
            Vec::new(),
            Vec::new(),
            ExitCode::Halted(0),
            Some(session.uuid),
        ))
    }
}
