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

use anyhow::Result;
use bytes::Bytes;
use std::{cell::RefCell, rc::Rc};

use risc0_circuit_rv32im::prove::emu::addr::ByteAddr;
use risc0_zkvm_platform::{
    syscall::reg_abi::{REG_A3, REG_A4},
    WORD_SIZE,
};

use crate::host::client::slice_io::SliceIo;

use super::{Syscall, SyscallContext};

/// A wrapper around a SliceIo that exposes it as a Syscall handler.
pub struct SysSliceIo<'a> {
    handler: Rc<RefCell<dyn SliceIo + 'a>>,
    stored_result: RefCell<Option<Bytes>>,
}

impl<'a> SysSliceIo<'a> {
    /// Wraps the given [SliceIo] into a [SysSliceIo].
    pub fn new(handler: Rc<RefCell<dyn SliceIo + 'a>>) -> Self {
        Self {
            handler,
            stored_result: RefCell::new(None),
        }
    }
}

/// An implementation of a [Syscall] for a [SliceIo].
///
/// When activated as a SyscallHandler, the SyscallHandler expects two
/// calls. The first call returns (nelem, _) indicating how many
/// elements are to be sent back to the guest, and the second call
/// actually returns the elements after the guest allocates space.
impl Syscall for SysSliceIo<'_> {
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let mut stored_result = self.stored_result.borrow_mut();
        let buf_ptr = ByteAddr(ctx.load_register(REG_A3));
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        Ok(match stored_result.take() {
            None => {
                // First call of pair. Send the data from the guest to the SliceIo
                // and save what it returns.
                assert_eq!(to_guest.len(), 0);
                let mut handler = self.handler.borrow_mut();
                let result = handler.handle_io(syscall, from_guest.into())?;
                let len = result.len() as u32;
                *stored_result = Some(result);
                (len, 0)
            }
            Some(stored) => {
                // Second call of pair. We already have data to send
                // to the guest; send it to the buffer that the guest
                // allocated.
                let to_guest_bytes: &mut [u8] = bytemuck::cast_slice_mut(to_guest);
                assert!(stored.len() <= to_guest_bytes.len());
                assert!(stored.len() + WORD_SIZE > to_guest_bytes.len());
                to_guest_bytes[..stored.len()].clone_from_slice(&stored);
                (0, 0)
            }
        })
    }
}
