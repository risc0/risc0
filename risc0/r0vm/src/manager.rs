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

use core::task;
use std::{
    collections::BTreeMap,
    io::Read as _,
    net::{Shutdown, SocketAddr, TcpListener, TcpStream},
    str::FromStr,
    sync::mpsc::{channel, Receiver, Sender},
    thread::{self, JoinHandle},
};

use bytes::{Buf, BufMut, Bytes};
use risc0_zkvm::Segment;

use crate::{
    protocol::{Message as _, Task, TaskManagerMessage},
    Cli,
};

pub(crate) fn main(args: Cli) {
    let addr = args
        .addr
        .unwrap_or(SocketAddr::from_str("[::]:9000").unwrap());

    let listener = TcpListener::bind(addr).unwrap();
    println!("manager: {}", listener.local_addr().unwrap());

    let (task_mgr, join_handle) = TaskManager::new();

    for stream in listener.incoming() {
        let task_mgr = task_mgr.clone();
        match stream {
            Ok(stream) => {
                thread::spawn(move || {
                    handle_client(stream, task_mgr);
                });
            }
            Err(err) => eprintln!("Connection failed: {err}"),
        }
    }

    join_handle.join().unwrap();
}

fn handle_client(mut stream: TcpStream, task_mgr: TaskManager) {
    println!("Connection from: {}", stream.peer_addr().unwrap());
    // let (client, join_handle) = Client::new(stream);
    loop {
        let msg = TaskManagerMessage::read(&stream);
        if let TaskManagerMessage::Bye = msg {
            break;
        }
        task_mgr.on_message(msg);
    }
    stream.shutdown(Shutdown::Both).unwrap();
}

struct TaskManagerActor {
    rx: Receiver<TaskManagerMessage>,
    tasks: BTreeMap<u32, u32>,
}

impl TaskManagerActor {
    pub fn new(rx: Receiver<TaskManagerMessage>) -> Self {
        Self {
            rx,
            tasks: BTreeMap::new(),
        }
    }

    pub fn run(&mut self) {
        while let Ok(msg) = self.rx.recv() {
            if !self.on_message(msg) {
                break;
            }
        }
    }

    fn on_message(&mut self, msg: TaskManagerMessage) -> bool {
        match msg {
            TaskManagerMessage::GetTask(kind) => {
                println!("GetTask: {kind:?}");
                true
            }
            TaskManagerMessage::Segment(ref segment) => true,
            TaskManagerMessage::Bye => true,
            TaskManagerMessage::Executed => todo!(),
            TaskManagerMessage::Lifted => todo!(),
            TaskManagerMessage::Joined => todo!(),
        }
    }
}

#[derive(Clone)]
struct TaskManager {
    tx: Sender<TaskManagerMessage>,
}

impl TaskManager {
    pub fn new() -> (Self, JoinHandle<()>) {
        let (tx, rx) = channel();
        let mut task_mgr = TaskManagerActor::new(rx);
        let handle = std::thread::spawn(move || {
            task_mgr.run();
        });
        (Self { tx }, handle)
    }

    pub fn on_message(&self, msg: TaskManagerMessage) {
        self.tx.send(msg).unwrap();
    }
}

struct ClientActor {
    rx: Receiver<Task>,
    stream: TcpStream,
}

impl ClientActor {
    pub fn new(rx: Receiver<Task>, stream: TcpStream) -> Self {
        Self { rx, stream }
    }

    pub fn run(&mut self) {
        while let Ok(msg) = self.rx.recv() {
            msg.write(&self.stream);
        }
    }
}

#[derive(Clone)]
struct Client {
    tx: Sender<Task>,
}

impl Client {
    pub fn new(stream: TcpStream) -> (Self, JoinHandle<()>) {
        let (tx, rx) = channel();
        let mut client = ClientActor::new(rx, stream);
        let handle = std::thread::spawn(move || {
            client.run();
        });
        (Self { tx }, handle)
    }

    pub fn on_message(&self, msg: Task) {
        self.tx.send(msg).unwrap();
    }
}
