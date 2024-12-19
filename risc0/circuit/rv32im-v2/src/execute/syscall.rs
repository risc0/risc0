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

/// A host-side implementation of a system call.
pub trait Syscall {
    /// Reads from the host.
    fn host_read(&self, fd: u32, buf: &mut [u8]) -> Result<u32>;

    /// Writes to the host.
    fn host_write(&self, fd: u32, buf: &[u8]) -> Result<u32>;
}
