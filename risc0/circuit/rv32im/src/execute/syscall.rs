// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use anyhow::Result;

use risc0_binfmt::ByteAddr;

/// A host-side implementation of a system call.
pub trait Syscall {
    /// Reads from the host.
    fn host_read(&self, ctx: &mut dyn SyscallContext, fd: u32, buf: &mut [u8]) -> Result<u32>;

    /// Writes to the host.
    fn host_write(&self, ctx: &mut dyn SyscallContext, fd: u32, buf: &[u8]) -> Result<u32>;
}

/// Access to memory and machine state for syscalls.
pub trait SyscallContext {
    /// Loads the value of the given register, e.g. REG_A0.
    fn peek_register(&mut self, idx: usize) -> Result<u32>;

    /// Loads an individual word from memory.
    fn peek_u32(&mut self, addr: ByteAddr) -> Result<u32>;

    /// Loads an individual byte from memory.
    fn peek_u8(&mut self, addr: ByteAddr) -> Result<u8>;

    /// Loads bytes from the given region of memory.
    ///
    /// A region may span multiple pages.
    fn peek_region(&mut self, addr: ByteAddr, size: usize) -> Result<Vec<u8>>;

    /// Load a page from memory at the specified page index.
    ///
    /// This is used by sys_fork in order to build a copy-on-write page cache to
    /// inherit pages from the parent process.
    fn peek_page(&mut self, page_idx: u32) -> Result<Vec<u8>>;

    /// Returns the current cycle count.
    fn get_cycle(&self) -> u64;

    /// Returns the current program counter.
    fn get_pc(&self) -> u32;
}
