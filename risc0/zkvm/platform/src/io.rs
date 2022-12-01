// Copyright 2022 RISC Zero, Inc.
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

// Standard ZKVM channels; must match zkvm/platform/io.h.
pub const SENDRECV_CHANNEL_INITIAL_INPUT: u32 = 0;
pub const SENDRECV_CHANNEL_STDOUT: u32 = 1;
pub const SENDRECV_CHANNEL_STDERR: u32 = 2;

#[repr(C)]
pub struct SliceDescriptor {
    pub size: u32,
    pub addr: u32,
}

impl SliceDescriptor {
    pub fn new<T>(slice: &[T]) -> Self {
        let size = slice.len() * core::mem::size_of::<T>();
        Self {
            size: size as u32,
            addr: slice.as_ptr() as u32,
        }
    }
}
