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

//! Handlers for two-way private I/O between host and guest
//!
//! These handlers can be enabled for a zkVM by setting them when a
//! [crate::prove::Prover] is created using [crate::prove::ProverOpts].
//! Specifically, the [ProverOpts](crate::prove::ProverOpts) functions
//! [with_sendrecv_callback](crate::prove::ProverOpts::with_sendrecv_callback),
//! [with_syscall](crate::prove::ProverOpts::with_syscall),
//! and [with_slice_io](crate::prove::ProverOpts::with_slice_io) can
//! be used to enable the handlers provided in this module.

use core::{cell::RefCell, marker::PhantomData, mem::take};
use std::{collections::BTreeMap, io::BufRead, io::Write, ops::DerefMut, rc::Rc};

use bytemuck::Pod;
use risc0_zkvm_platform::{
    syscall::{
        nr,
        reg_abi::{REG_A3, REG_A4, REG_A5},
    },
    WORD_SIZE,
};

use crate::prove::exec::MemoryState;

/// An IO handler that returns arbitrary data to the guest.  On the
/// guest side, use env::send_slice, env::recv_slice, or
/// end::send_recv_slice.
///
/// When activated as a SyscallHandler, the SyscallHandler expects two
/// calls.  The first call returns (nelem, _) indicating how many
/// elements are to be sent back to the guest, and the second call
/// actually returns the elements after the guest allocates space.
pub trait SliceIo: Sized {
    /// Type for data received from guest
    type FromGuest: Pod;
    /// Type for data sent to guest
    type ToGuest: Pod;
    /// Host side I/O handling
    ///
    /// Whatever data the guest sent is received by this function in
    /// `from_guest`, and this function is to return the data the host is
    /// sending to the guest.

    fn handle_io(&self, syscall: &str, from_guest: &[Self::FromGuest]) -> Vec<Self::ToGuest>;

    /// Makes a Syscall handler for this SliceIo definition.g
    fn to_syscall(self) -> SliceIoSyscall<Self> {
        SliceIoSyscall::new(self)
    }
}

/// A wrapper around a SliceIo that exposes it as a Syscall handler.
pub struct SliceIoSyscall<H: SliceIo> {
    handler: H,
    stored_result: RefCell<Option<Vec<H::ToGuest>>>,
}

/// A host-side implementation of a system call.
pub trait Syscall {
    /// Invokes the system call
    fn syscall(&self, syscall: &str, ctx: &MemoryState, to_guest: &mut [u32]) -> (u32, u32);
}

impl<H: SliceIo> SliceIoSyscall<H> {
    /// Wraps the given SliceIo into a SliceIoSyscall.
    pub fn new(handler: H) -> Self {
        Self {
            handler,
            stored_result: RefCell::new(None),
        }
    }
}

impl<H: SliceIo> Syscall for SliceIoSyscall<H> {
    fn syscall(&self, syscall: &str, ctx: &MemoryState, to_guest: &mut [u32]) -> (u32, u32) {
        let mut stored_result = self.stored_result.borrow_mut();
        let buf_ptr = ctx.load_register(REG_A3);
        let buf_len = ctx.load_register(REG_A4);
        let from_guest_bytes = ctx.load_region(buf_ptr, buf_len);
        let from_guest: &[H::FromGuest] = bytemuck::cast_slice(from_guest_bytes.as_slice());
        match take(stored_result.deref_mut()) {
            None => {
                // First call of pair.  Send the data from the guest to the SliceIo
                // and save what it returns.
                assert_eq!(to_guest.len(), 0);
                let from_guest: &[H::FromGuest] = bytemuck::cast_slice(from_guest);
                let result = self.handler.handle_io(syscall, from_guest);
                let len = result.len();
                *stored_result = Some(result);
                (len as u32, 0)
            }
            Some(stored) => {
                // Second call of pair.  We already have data to send
                // to the guest; send it to the buffer that the guest
                // allocated.
                let stored_bytes: &[u8] = bytemuck::cast_slice(stored.as_slice());
                let to_guest_bytes: &mut [u8] = bytemuck::cast_slice_mut(to_guest);
                if core::mem::size_of::<H::ToGuest>() < WORD_SIZE {
                    assert!(stored_bytes.len() <= to_guest_bytes.len());
                    assert!(stored_bytes.len() + WORD_SIZE > to_guest_bytes.len());
                } else {
                    assert!(to_guest_bytes.len() >= stored_bytes.len());
                }
                to_guest_bytes[..stored_bytes.len()].clone_from_slice(stored_bytes);
                (0, 0)
            }
        }
    }
}

/// Generates a Syscall from a simple slice function
pub fn slice_io_from_fn<T: Pod, U: Pod, F: Fn(&[T]) -> Vec<U>>(f: F) -> impl SliceIo {
    FnWrapper {
        f,
        phantom: PhantomData,
    }
}

struct FnWrapper<T: Pod, U: Pod, F: Fn(&[T]) -> Vec<U>> {
    f: F,
    phantom: PhantomData<(T, U)>,
}

impl<T: Pod, U: Pod, F: Fn(&[T]) -> Vec<U>> SliceIo for FnWrapper<T, U, F> {
    type FromGuest = T;
    type ToGuest = U;

    fn handle_io(&self, _syscall: &str, from_guest: &[Self::FromGuest]) -> Vec<Self::ToGuest> {
        (self.f)(from_guest)
    }
}

/// Posix-style IO
pub(crate) struct PosixIo<'a> {
    read_fds: RefCell<BTreeMap<u32, Rc<RefCell<dyn BufRead + 'a>>>>,
    write_fds: RefCell<BTreeMap<u32, Rc<RefCell<dyn Write + 'a>>>>,
}

impl<'a> PosixIo<'a> {
    pub fn new() -> Self {
        Self {
            read_fds: RefCell::new(BTreeMap::new()),
            write_fds: RefCell::new(BTreeMap::new()),
        }
    }

    pub fn with_read_fd(self, fd: u32, reader: Rc<RefCell<impl BufRead + 'a>>) -> Self {
        self.read_fds.borrow_mut().insert(fd, reader);
        self
    }

    pub fn with_write_fd(self, fd: u32, writer: Rc<RefCell<impl Write + 'a>>) -> Self {
        self.write_fds.borrow_mut().insert(fd, writer);

        self
    }
}

impl<'a> Syscall for PosixIo<'a> {
    fn syscall(&self, syscall: &str, ctx: &MemoryState, to_guest: &mut [u32]) -> (u32, u32) {
        // TODO: Is there a way to use "match" here instead of if statements?
        if syscall == nr::SYS_READ_AVAIL.as_str() {
            let fd = ctx.load_register(REG_A3);
            let mut read_fds = self.read_fds.borrow_mut();
            let reader = read_fds
                .get_mut(&fd)
                .expect(&format!("Bad read file descriptor {fd}"));

            let navail = reader.borrow_mut().fill_buf().unwrap().len() as u32;
            (navail, 0)
        } else if syscall == nr::SYS_READ.as_str() {
            let fd = ctx.load_register(REG_A3);
            let nbytes = ctx.load_register(REG_A4) as usize;

            log::debug!("sys_read, attempting to read {nbytes} bytes from fd {fd}");

            assert!(
                nbytes >= to_guest.len() * WORD_SIZE,
                "Word-aligned read buffer must be fully filled"
            );

            let mut read_fds = self.read_fds.borrow_mut();
            let reader = read_fds
                .get_mut(&fd)
                .expect(&format!("Bad read file descriptor {fd}"));

            let to_guest_u8: &mut [u8] = bytemuck::cast_slice_mut(to_guest);
            let nread_main = reader.borrow_mut().read(to_guest_u8).unwrap();
            assert_eq!(
                nread_main,
                to_guest_u8.len(),
                "Guest requested more data than was available"
            );

            log::debug!(
                "Main read got {nread_main} bytes out of requested {}",
                to_guest_u8.len()
            );
            let unaligned_end = nbytes - nread_main;
            assert!(
                unaligned_end <= WORD_SIZE,
                "{unaligned_end} must be <= {WORD_SIZE}"
            );

            // Fill unaligned word out.
            let mut to_guest_end: [u8; WORD_SIZE] = [0; WORD_SIZE];
            let nread_end = reader
                .borrow_mut()
                .read(&mut to_guest_end[0..unaligned_end])
                .unwrap();

            (
                (nread_main + nread_end) as u32,
                u32::from_le_bytes(to_guest_end),
            )
        } else if syscall == nr::SYS_WRITE.as_str() {
            let fd = ctx.load_register(REG_A3);
            let buf_ptr = ctx.load_register(REG_A4);
            let buf_len = ctx.load_register(REG_A5);
            let from_guest_bytes = ctx.load_region(buf_ptr, buf_len);
            let mut write_fds = self.write_fds.borrow_mut();
            let writer = write_fds
                .get_mut(&fd)
                .expect(&format!("Bad write file descriptor {fd}"));

            log::debug!("Writing {buf_len} bytes to file descriptor {fd}");

            writer
                .borrow_mut()
                .write_all(from_guest_bytes.as_slice())
                .unwrap();
            (0, 0)
        } else {
            panic!("Unknown syscall {syscall}")
        }
    }
}

impl<'a> Syscall for Rc<PosixIo<'a>> {
    fn syscall(&self, syscall: &str, ctx: &MemoryState, to_guest: &mut [u32]) -> (u32, u32) {
        (**self).syscall(syscall, ctx, to_guest)
    }
}

impl<'a> Default for PosixIo<'a> {
    fn default() -> Self {
        Self::new()
    }
}
