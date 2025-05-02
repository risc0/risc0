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

use std::{
    io::{Read, Write},
    net::TcpStream,
};

use bytes::{Buf, BufMut, Bytes};
use risc0_zkvm::{DeserializeOwned, Segment};
use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
pub(crate) enum TaskKind {
    Execute,
    ProveSegment,
    Lift,
    Join,
}

#[derive(Serialize, Deserialize)]
pub(crate) enum TaskManagerMessage {
    GetTask(TaskKind),
    Segment(Segment),
    Executed,
    Lifted,
    Joined,
    Bye,
}

#[derive(Serialize, Deserialize)]
pub(crate) enum Task {
    Execute(ExecuteTask),
    ProveSegment(Segment),
    Lift,
    Join,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct ExecuteTask {
    pub binary: Vec<u8>,
    pub input: Vec<u8>,
}

pub(crate) trait Message: Serialize + DeserializeOwned {
    fn read<R: Read>(mut reader: R) -> Self {
        let mut header = [0; 4];
        reader.read_exact(&mut header).unwrap();
        let len = u32::from_le_bytes(header) as usize;
        let mut body = vec![0; len];
        reader.read_exact(&mut body).unwrap();
        bincode::deserialize(&body).unwrap()
    }

    fn write<W: Write>(&self, mut writer: W) {
        let len = bincode::serialized_size(self).unwrap() as u32;
        writer.write_all(&len.to_le_bytes());
        let body = bincode::serialize(self).unwrap();
        writer.write_all(&body).unwrap();
    }
}

impl Message for TaskManagerMessage {}
impl Message for Task {}
