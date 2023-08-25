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

pub(crate) mod client;
pub(crate) mod server;

use std::{
    cell::RefCell,
    io::{Read, Write},
    rc::Rc,
};

use anyhow::{anyhow, Result};
use protobuf::Message;

#[derive(Clone)]
struct Channel<'a> {
    reader: Rc<RefCell<dyn Read + 'a>>,
    writer: Rc<RefCell<dyn Write + 'a>>,
}

impl<'a> Channel<'a> {
    fn new(reader: impl Read + 'a, writer: impl Write + 'a) -> Self {
        Self {
            reader: Rc::new(RefCell::new(reader)),
            writer: Rc::new(RefCell::new(writer)),
        }
    }

    fn recv<T: Default + Message>(&mut self) -> Result<T> {
        let mut reader = self.reader.borrow_mut();
        Ok(T::parse_from_reader(&mut *reader)?)
    }

    fn send<T: Message>(&mut self, msg: T) -> Result<()> {
        let mut writer = self.writer.borrow_mut();
        Ok(msg.write_to_writer(&mut *writer)?)
    }
}

fn malformed_err() -> anyhow::Error {
    anyhow!("Malformed error")
}
