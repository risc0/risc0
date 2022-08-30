// Copyright 2022 Risc0, Inc.
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

use core::cell::UnsafeCell;

use crate::{
    io::{GPIO_SENDRECV_ADDR, GPIO_SENDRECV_CHANNEL, GPIO_SENDRECV_SIZE},
    memory, WORD_SIZE,
};

// Current offset in number of words from the INPUT memory region that
// we're reading,
static mut READ_PTR: UnsafeCell<usize> = UnsafeCell::new(memory::INPUT.start());

/// Reads a fixed-length message from the host, with the size
/// specified in number of words.  Normally this would be called in
/// response to a GPIO request of some sort.  Callers should always
/// call this as soon as possible after the GPIO request in order to
/// avoid desynchronization.
pub fn host_recv(nwords: usize) -> &'static [u32] {
    // SAFETY: We're single threaded, so it's ok to borrow READ_PTR while in this
    // routine.
    let read_ptr: &mut usize = unsafe { &mut *READ_PTR.get() };
    let read_start = *read_ptr;
    let read_end = read_ptr.checked_add(nwords * WORD_SIZE).unwrap();
    if read_end > memory::INPUT.end() {
        panic!("host_recv overran input buffer with {nwords} word read");
    }
    *read_ptr = read_end;

    // SAFETY: This region is in the INPUT region and we just did a bounds check.
    unsafe { core::slice::from_raw_parts(read_start as *const u32, nwords) }
}

/// Interacts with the host.  'channel' specifies the ZKVM channel to
/// use, and 'buf' provides the data to tsend to the host.
///
/// The returned tuple contains a slice of 32-bit words from the host,
/// and a size in bytes of the returned data.  The size in bytes might
/// not match the length of the returned slice * WORD_SIZE in the case
/// that the returned buffer does not fall on a word boundry.
pub fn host_sendrecv(channel: u32, buf: &[u8]) -> (&'static [u32], usize) {
    // Tell the host to send us some data.
    unsafe {
        GPIO_SENDRECV_CHANNEL.as_ptr().write_volatile(channel);
        GPIO_SENDRECV_SIZE.as_ptr().write_volatile(buf.len());
        GPIO_SENDRECV_ADDR.as_ptr().write_volatile(buf.as_ptr());
    }

    let response_nbytes = match host_recv(1) {
        &[nbytes] => nbytes,
        _ => unreachable!(),
    } as usize;

    let response_nwords = (response_nbytes + WORD_SIZE - 1) / WORD_SIZE;

    (host_recv(response_nwords), response_nbytes)
}
