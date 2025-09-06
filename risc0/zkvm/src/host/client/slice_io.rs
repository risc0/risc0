// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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

impl SliceIo for FnWrapper<'_> {
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

impl SliceIo for Rc<RefCell<dyn SliceIo + '_>> {
    fn handle_io(&mut self, syscall: &str, from_guest: Bytes) -> Result<Bytes> {
        self.borrow_mut().handle_io(syscall, from_guest)
    }
}
