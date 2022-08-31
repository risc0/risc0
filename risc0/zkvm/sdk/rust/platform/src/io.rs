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

// These must match the values in zkvm/platform/io.h.  See that file
// for documentation on these GPIO ports.
use core::{marker::PhantomData, mem};

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
        if cfg!(target_os = "zkvm") {
            self.addr as _
        } else {
            // If we're not on zkvm, don't make it easy to get a
            // pointer to a GPIO port since it'll point off to the
            // middle of nowhere.
            unimplemented!()
        }
    }

    pub const fn addr(&self) -> u32 {
        self.addr
    }
}

pub const GPIO_SHA: Gpio<*const SHADescriptor> = Gpio::new(0x01F0_0000);
pub const GPIO_COMMIT: Gpio<*const IoDescriptor> = Gpio::new(0x01F0_0004);
pub const GPIO_FAULT: Gpio<*const u8> = Gpio::new(0x01F0_0008);
pub const GPIO_LOG: Gpio<*const IoDescriptor> = Gpio::new(0x01F0_000C);
pub const GPIO_GETKEY: Gpio<*const GetKeyDescriptor> = Gpio::new(0x01F0_0010);

pub const GPIO_SENDRECV_CHANNEL: Gpio<u32> = Gpio::new(0x01F0_0014);
pub const GPIO_SENDRECV_SIZE: Gpio<usize> = Gpio::new(0x01F0_0018);
pub const GPIO_SENDRECV_ADDR: Gpio<*const u8> = Gpio::new(0x01F0_001C);

pub const GPIO_CYCLECOUNT: Gpio<u32> = Gpio::new(0x01F00020);

pub const GPIO_INSECURESHACOMPRESS: Gpio<*const InsecureShaCompressDescriptor> =
    Gpio::new(0x01F00024);
pub const GPIO_INSECURESHAHASH: Gpio<*const InsecureShaHashDescriptor> = Gpio::new(0x01F00028);

pub const GPIO_COMPUTE_POLY: Gpio<*const ComputePolyDescriptor> = Gpio::new(0x01F0002C);

pub mod addr {
    pub const GPIO_SHA: u32 = super::GPIO_SHA.addr();
    pub const GPIO_COMMIT: u32 = super::GPIO_COMMIT.addr();
    pub const GPIO_FAULT: u32 = super::GPIO_FAULT.addr();
    pub const GPIO_LOG: u32 = super::GPIO_LOG.addr();
    pub const GPIO_GETKEY: u32 = super::GPIO_GETKEY.addr();

    pub const GPIO_SENDRECV_CHANNEL: u32 = super::GPIO_SENDRECV_CHANNEL.addr();
    pub const GPIO_SENDRECV_SIZE: u32 = super::GPIO_SENDRECV_SIZE.addr();
    pub const GPIO_SENDRECV_ADDR: u32 = super::GPIO_SENDRECV_ADDR.addr();

    pub const GPIO_CYCLECOUNT: u32 = super::GPIO_CYCLECOUNT.addr();

    pub const GPIO_INSECURESHACOMPRESS: u32 = super::GPIO_INSECURESHACOMPRESS.addr();
    pub const GPIO_INSECURESHAHASH: u32 = super::GPIO_INSECURESHAHASH.addr();

    pub const GPIO_COMPUTE_POLY: u32 = super::GPIO_COMPUTE_POLY.addr();
}

#[repr(C)]
pub struct IoDescriptor {
    pub size: u32,
    pub addr: u32,
}

#[repr(C)]
pub struct SHADescriptor {
    pub type_count: u32,
    pub idx: u32,
    pub source: u32,
    pub digest: u32,
}

#[repr(C)]
pub struct GetKeyDescriptor {
    pub name: u32,
    pub addr: u32,
    pub mode: u32,
}

#[repr(C)]
pub struct InsecureShaCompressDescriptor {
    pub state: u32,
    pub block_half1: u32,
    pub block_half2: u32,
}

#[repr(C)]
pub struct InsecureShaHashDescriptor {
    pub state: u32,
    pub start: u32,
    pub len: u32,
}

#[repr(C)]
pub struct SliceDescriptor {
    pub size: u32,
    pub addr: u32,
}

#[repr(C)]
pub struct ComputePolyDescriptor {
    pub eval_u: SliceDescriptor,
    pub poly_mix: u32,
    pub out: SliceDescriptor,
    pub mix: SliceDescriptor,
}

// Standard ZKVM channels; must match zkvm/platform/io.h.
pub const SENDRECV_CHANNEL_INITIAL_INPUT: u32 = 0;
pub const SENDRECV_CHANNEL_STDOUT: u32 = 1;
pub const SENDRECV_CHANNEL_STDERR: u32 = 2;

impl SliceDescriptor {
    pub fn new<T>(slice: &[T]) -> Self {
        let size = slice.len() * mem::size_of::<T>();
        Self {
            size: size as u32,
            addr: slice.as_ptr() as u32,
        }
    }
}
