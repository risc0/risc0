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
    io::Read,
    net::{SocketAddr, TcpStream},
    str::FromStr,
};

use risc0_zkvm::{ExecutorEnv, ExecutorImpl, NullSegmentRef, Segment};

use crate::{
    protocol::{ExecuteTask, Message, Task, TaskKind, TaskManagerMessage},
    Cli,
};

pub(crate) fn main(args: Cli) {
    let addr = args
        .addr
        .unwrap_or(SocketAddr::from_str("127.0.0.1:9000").unwrap());
    println!("worker: {addr}");

    let mut worker = Worker::connect(addr);
    worker.run();
}

struct Worker {
    stream: TcpStream,
}

impl Worker {
    pub fn connect(addr: SocketAddr) -> Self {
        let stream = TcpStream::connect(addr).unwrap();
        Self { stream }
    }

    pub fn run(&mut self) {
        loop {
            let msg = TaskManagerMessage::GetTask(TaskKind::Execute);
            msg.write(&self.stream);

            let msg = Task::read(&self.stream);
            match msg {
                Task::Execute(task) => self.execute(task),
                Task::ProveSegment(segment) => todo!(),
                Task::Lift => todo!(),
                Task::Join => todo!(),
            }
        }
    }

    fn execute(&mut self, task: ExecuteTask) {
        let env = ExecutorEnv::builder()
            .write_slice(&task.input)
            .build()
            .unwrap();
        let mut exec = ExecutorImpl::from_elf(env, &task.binary).unwrap();
        let session = exec
            .run_with_callback(|segment| {
                let msg = TaskManagerMessage::Segment(segment);
                msg.write(&self.stream);
                Ok(Box::new(NullSegmentRef {}))
            })
            .unwrap();
    }

    fn prove_segment(&mut self, segment: Segment) {}
}
