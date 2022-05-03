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

pub struct GpioPort<T> {
    pub port: *mut T,
}

impl<T> GpioPort<T> {
    const fn new(addr: usize) -> Self {
        Self {
            port: addr as *mut T,
        }
    }

    pub fn write_volatile(self, val: T) {
        unsafe { self.port.write_volatile(val) }
    }

    pub fn ptr(self) -> *const T {
        self.port.cast()
    }
}

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

pub(crate) const GPIO_SHA: GpioPort<*const SHADescriptor> = GpioPort::new(0x001C_0000);
pub(crate) const GPIO_WRITE: GpioPort<*const IoDescriptor> = GpioPort::new(0x001C_0004);
pub(crate) const GPIO_COMMIT: GpioPort<*const IoDescriptor> = GpioPort::new(0x001C_0008);
pub(crate) const GPIO_FAULT: GpioPort<*const FaultDescriptor> = GpioPort::new(0x001C_000C);
pub(crate) const GPIO_LOG: GpioPort<*const LogDescriptor> = GpioPort::new(0x001C_0010);

pub(crate) const GPIO_DESC_IO: GpioPort<IoDescriptor> = GpioPort::new(0x001D_0000);
pub(crate) const GPIO_DESC_LOG: GpioPort<LogDescriptor> = GpioPort::new(0x001D_0000);
pub(crate) const GPIO_DESC_FAULT: GpioPort<FaultDescriptor> = GpioPort::new(0x001D_0000);
