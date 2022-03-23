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

pub(crate) const GPIO_SHA: *mut *const SHADescriptor = 0x001C_0000 as _;
pub(crate) const GPIO_WRITE: *mut *const IoDescriptor = 0x001C_0004 as _;
pub(crate) const GPIO_COMMIT: *mut *const IoDescriptor = 0x001C_0008 as _;
pub(crate) const GPIO_FAULT: *mut *const FaultDescriptor = 0x001C_000C as _;
pub(crate) const GPIO_LOG: *mut *const LogDescriptor = 0x001C_0010 as _;

pub(crate) const GPIO_DESC_IO: *mut IoDescriptor = 0x001D_0000 as _;
pub(crate) const GPIO_DESC_LOG: *mut LogDescriptor = 0x001D_0000 as _;
pub(crate) const GPIO_DESC_FAULT: *mut FaultDescriptor = 0x001D_0000 as _;

#[repr(C)]
pub(crate) struct IoDescriptor {
    pub size: usize,
    pub addr: usize,
}

#[repr(C)]
pub(crate) struct FaultDescriptor {
    pub addr: usize,
}

#[repr(C)]
pub(crate) struct LogDescriptor {
    pub addr: usize,
}

#[repr(C)]
pub(crate) struct SHADescriptor {
    pub type_count: usize,
    pub idx: usize,
    pub source: usize,
    pub digest: usize,
}
