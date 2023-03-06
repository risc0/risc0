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
//! [with_slice_io_handler](crate::prove::ProverOpts::with_slice_io_handler),
//! and [with_raw_io_handler](crate::prove::ProverOpts::with_raw_io_handler) can
//! be used to enable the handlers provided in this module.

use core::{cell::RefCell, marker::PhantomData, mem::take};
use std::ops::DerefMut;

use bytemuck::Pod;
use risc0_zkvm_platform::WORD_SIZE;

/// An IO handler that returns arbitrary data to the guest.  On the
/// guest side, use env::send_slice, env::recv_slice, or
/// end::send_recv_slice.
///
/// When activated as a RawIoHandler, the RawIoHandler expects two
/// calls.  The first call returns (nelem, _) indicating how many
/// elements are to be sent back to the guest, and the second call
/// actually returns the elements after the guest allocates space.
pub trait SliceIoHandler {
    /// Type for data received from guest
    type FromGuest: Pod;
    /// Type for data sent to guest
    type ToGuest: Pod;
    /// Host side IO handling
    ///
    /// Whatever data the guest sent is received by this function in
    /// `from_guest`, and this function is to return the data the host is
    /// sending to the guest.
    fn handle_io(&self, from_guest: &[Self::FromGuest]) -> Vec<Self::ToGuest>;
}

/// An IO handler that returns raw data to a SYS_IO invocation from the guest.
/// In addition to filling the buffer provided by the guest, it can
/// return two words to be returned in the a0 and a1 registers.
///
/// Users may find SliceIoHandler more friendly to use.
pub trait RawIoHandler {
    /// Host side IO handling
    ///
    /// Whatever data the guest sent is received by this function in
    /// `from_guest`, and the data the host is sending is written in `to_guest`.
    /// This returns the words in the guest's `a0` and `a1` registers.
    fn handle_raw_io(&self, from_guest: &[u8], to_guest: &mut [u32]) -> (u32, u32);
}

/// Generates a RawIoHandler from a simple slice function
pub fn handler_from_fn<T: Pod, U: Pod, F: Fn(&[T]) -> Vec<U>>(f: F) -> impl RawIoHandler {
    handler_from_slice_handler(FnWrapper {
        f,
        phantom: PhantomData,
    })
}

/// Wraps a SliceIoHandler and makes it available as a RawIoHandler.
pub fn handler_from_slice_handler(handler: impl SliceIoHandler) -> impl RawIoHandler {
    SliceIoWrapper {
        handler,
        stored_result: RefCell::new(None),
    }
}

// Wraps a SliceIoHandler and exposes it as a RawIoHandler.
//
// SliceIoWrapper is always invoked from the guest in pairs; the first
// call sends data to the host and receives the length of the reply.
// The second call actually transfers the data from the host to the
// guest once the guest allocates a buffer.
struct SliceIoWrapper<H: SliceIoHandler> {
    stored_result: RefCell<Option<Vec<H::ToGuest>>>,
    handler: H,
}

impl<H: SliceIoHandler> RawIoHandler for SliceIoWrapper<H> {
    fn handle_raw_io(&self, from_guest: &[u8], to_guest: &mut [u32]) -> (u32, u32) {
        let mut stored_result = self.stored_result.borrow_mut();
        match take(stored_result.deref_mut()) {
            None => {
                // First call of pair.  Send the data from the guest to the SliceIoHandler
                // and save what it returns.
                assert_eq!(to_guest.len(), 0);
                let from_guest: &[H::FromGuest] = bytemuck::cast_slice(from_guest);
                let result = self.handler.handle_io(from_guest);
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

struct FnWrapper<T: Pod, U: Pod, F: Fn(&[T]) -> Vec<U>> {
    f: F,
    phantom: PhantomData<(T, U)>,
}

impl<T: Pod, U: Pod, F: Fn(&[T]) -> Vec<U>> SliceIoHandler for FnWrapper<T, U, F> {
    type FromGuest = T;
    type ToGuest = U;

    fn handle_io(&self, from_guest: &[Self::FromGuest]) -> Vec<Self::ToGuest> {
        (self.f)(from_guest)
    }
}
