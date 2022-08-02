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

// These must match the values in zkvm/platform/io.h.  See this file
// for documentation on these GPIO ports.

pub struct Gpio<T> {
    addr: u32,
    _marker: PhantomData<T>,
}

impl<T> Gpio<T> {
    pub const fn new(addr: u32) -> Self {
        Self {
            addr,
            _marker: PhantomData,
        }
    }

    pub const fn as_ptr(&self) -> *mut T {
        self.addr as _
    }

    pub const fn addr(&self) -> u32 {
        self.addr
    }
}

pub const GPIO_SHA: Gpio<*const SHADescriptor> = Gpio::new(0x01F0_0000);
pub const GPIO_COMMIT: Gpio<*const IoDescriptor> = Gpio::new(0x01F0_0004);
pub const GPIO_FAULT: Gpio<*const u8> = Gpio::new(0x01F0_0008);
pub const GPIO_LOG: Gpio<*const u8> = Gpio::new(0x01F0_000C);
pub const GPIO_GETKEY: Gpio<*const GetKeyDescriptor> = Gpio::new(0x01F0_0010);

pub const GPIO_SENDRECV_CHANNEL: Gpio<u32> = Gpio::new(0x01F0_0014);
pub const GPIO_SENDRECV_SIZE: Gpio<usize> = Gpio::new(0x01F0_0018);
pub const GPIO_SENDRECV_ADDR: Gpio<*const u8> = Gpio::new(0x01F0_001C);

pub mod addr {
    pub const GPIO_SHA: u32 = super::GPIO_SHA.addr();
    pub const GPIO_COMMIT: u32 = super::GPIO_COMMIT.addr();
    pub const GPIO_FAULT: u32 = super::GPIO_FAULT.addr();
    pub const GPIO_LOG: u32 = super::GPIO_LOG.addr();
    pub const GPIO_GETKEY: u32 = super::GPIO_GETKEY.addr();

    pub const GPIO_SENDRECV_CHANNEL: u32 = super::GPIO_SENDRECV_CHANNEL.addr();
    pub const GPIO_SENDRECV_SIZE: u32 = super::GPIO_SENDRECV_SIZE.addr();
    pub const GPIO_SENDRECV_ADDR: u32 = super::GPIO_SENDRECV_ADDR.addr();
}

#[repr(C)]
pub struct IoDescriptor {
    pub size: usize,
    pub addr: usize,
}

#[repr(C)]
pub struct SHADescriptor {
    pub type_count: usize,
    pub idx: usize,
    pub source: usize,
    pub digest: usize,
}

#[repr(C)]
pub struct GetKeyDescriptor {
    pub name: u32,
    pub addr: u32,
    pub mode: u32,
}

// Standard ZKVM channels; must match zkvm/platform/io.h.
pub const SENDRECV_CHANNEL_INITIAL_INPUT: u32 = 0;
pub const SENDRECV_CHANNEL_STDOUT: u32 = 1;
pub const SENDRECV_CHANNEL_STDERR: u32 = 2;

#[cfg(target_os = "zkvm")]
mod guest {
    use crate::{memory, WORD_SIZE};
    use core::cell::UnsafeCell;

    // Current offset in number of words from the INPUT memory region that
    // we're reading,
    static mut READ_PTR: UnsafeCell<usize> = UnsafeCell::new(0);

    /// Interacts with the host.  'channel' specifies the ZKVM channel to
    /// use, and 'buf' provides the data to tsend to the host.
    ///
    /// The returned tuple contains a slice of 32-bit words from the host,
    /// and a size in bytes of the returned data.  The size in bytes might
    /// not match the length of the returned slice * WORD_SIZE in the case
    /// that the returned buffer does not fall on a word boundry.
    pub fn host_sendrecv(channel: u32, buf: &[u8]) -> (&'static [u32], usize) {
        // SAFETY: Single threaded, so it's ok to borrow READ_PTR while in this routine.
        let read_ptr: &mut usize = unsafe { &mut *READ_PTR.get() };

        // Tell the host to execute the sendrecv.
        unsafe {
            super::GPIO_SENDRECV_CHANNEL
                .as_ptr()
                .write_volatile(channel);
            super::GPIO_SENDRECV_SIZE.as_ptr().write_volatile(buf.len());
            super::GPIO_SENDRECV_ADDR
                .as_ptr()
                .write_volatile(buf.as_ptr());
        }

        // Receive
        let read_start: *const u32 = memory::INPUT.start() as _;
        let response_nbytes = unsafe { read_start.add(*read_ptr).read_volatile() } as usize;
        *read_ptr += 1;
        let response_nwords = (response_nbytes + WORD_SIZE - 1) / WORD_SIZE;

        assert!(*read_ptr + response_nwords < memory::INPUT.len_words());
        // SAFETY: This region is in the INPUT region and we just did a bounds check.
        let response_data =
            unsafe { core::slice::from_raw_parts(read_start.add(*read_ptr), response_nwords) };
        *read_ptr += response_nwords;

        (response_data, response_nbytes)
    }
}

#[cfg(not(target_os = "zkvm"))]
mod guest {
    pub fn host_sendrecv(_channel: u32, _buf: &[u8]) -> (&'static [u32], usize) {
        unimplemented!()
    }
}

use core::marker::PhantomData;

pub use guest::*;
