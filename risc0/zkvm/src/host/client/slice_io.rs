// Copyright 2024 RISC Zero, Inc.
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

use std::{cell::RefCell, collections::BTreeMap, rc::Rc};

use anyhow::Result;
use bytes::Bytes;

/// An I/O handler that returns arbitrary data to the guest.
///
/// On the guest side, use `env::send_recv_slice`.
///
/// When activated as a SyscallHandler, the SyscallHandler expects two
/// calls. The first call returns (nelem, _) indicating how many
/// elements are to be sent back to the guest, and the second call
/// actually returns the elements after the guest allocates space.
pub trait SliceIo {
    /// Host side I/O handling
    ///
    /// Whatever data the guest sent is received by this function in
    /// `from_guest`, and this function is to return the data the host is
    /// sending to the guest.
    fn handle_io(&mut self, syscall: &str, from_guest: Bytes) -> Result<Bytes>;
}

#[derive(Clone, Default)]
pub struct SliceIoTable<'a> {
    pub(crate) inner: BTreeMap<String, Rc<RefCell<dyn SliceIo + 'a>>>,
}

type Callback<'a> = Rc<RefCell<dyn Fn(Bytes) -> Result<Bytes> + 'a>>;

struct FnWrapper<'a> {
    callback: Callback<'a>,
}

pub fn slice_io_from_fn<'a>(
    callback: impl Fn(Bytes) -> Result<Bytes> + 'a,
) -> Rc<RefCell<dyn SliceIo + 'a>> {
    let callback = Rc::new(RefCell::new(callback));
    Rc::new(RefCell::new(FnWrapper { callback }))
}

impl<'a> SliceIo for FnWrapper<'a> {
    fn handle_io(&mut self, _syscall: &str, from_guest: Bytes) -> Result<Bytes> {
        let callback = self.callback.borrow_mut();
        callback(from_guest)
    }
}

impl<'a> SliceIoTable<'a> {
    pub fn with_handler(&mut self, channel: &str, handler: impl SliceIo + 'a) -> &mut Self {
        self.inner
            .insert(channel.to_string(), Rc::new(RefCell::new(handler)));
        self
    }
}

impl<'a> SliceIo for Rc<RefCell<dyn SliceIo + 'a>> {
    fn handle_io(&mut self, syscall: &str, from_guest: Bytes) -> Result<Bytes> {
        self.borrow_mut().handle_io(syscall, from_guest)
    }
}
