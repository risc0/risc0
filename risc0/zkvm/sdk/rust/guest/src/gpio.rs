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
pub(crate) const GPIO_SHA: *mut *const SHADescriptor = 0x001C_0000 as _;
pub(crate) const GPIO_COMMIT: *mut *const IoDescriptor = 0x001C_0004 as _;
pub(crate) const GPIO_FAULT: *mut *const u8 = 0x001C_0008 as _;
pub(crate) const GPIO_LOG: *mut *const u8 = 0x001C_000C as _;
pub(crate) const GPIO_GETKEY: *mut *const GetKeyDescriptor = 0x001C_0010 as _;

pub(crate) const GPIO_SENDRECV_CHANNEL: *mut u32 = 0x001C_0014 as _;
pub(crate) const GPIO_SENDRECV_SIZE: *mut usize = 0x001C_0018 as _;
pub(crate) const GPIO_SENDRECV_ADDR: *mut *const u8 = 0x001C_001C as _;

#[repr(C)]
pub(crate) struct IoDescriptor {
    pub size: usize,
    pub addr: usize,
}

#[repr(C)]
pub(crate) struct SHADescriptor {
    pub type_count: usize,
    pub idx: usize,
    pub source: usize,
    pub digest: usize,
}

#[repr(C)]
pub(crate) struct GetKeyDescriptor {
    pub name: u32,
    pub addr: u32,
    pub mode: u32,
}

// Standard ZKVM channels; must match zkvm/platform/io.h.
pub(crate) const SENDRECV_CHANNEL_INITIAL_INPUT: u32 = 0;
pub(crate) const SENDRECV_CHANNEL_STDOUT: u32 = 1;
