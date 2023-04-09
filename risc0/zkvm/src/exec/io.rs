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

//! TODO

use anyhow::Result;
use risc0_zkvm_platform::memory::SYSTEM;
use risc0_zkvm_platform::WORD_SIZE;

/// A host-side implementation of a system call.
pub trait Syscall {
    /// Invokes the system call.
    fn syscall(
        &self,
        syscall: &str,
        ctx: &dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)>;
}

/// Access to memory and machine state for syscalls.
pub trait SyscallContext {
    /// Returns the current cycle being executed.
    fn get_cycle(&self) -> usize;

    /// Loads the value of the given register, e.g. REG_A0.
    fn load_register(&mut self, num: usize) -> u32 {
        self.load_u32((SYSTEM.start() + num * WORD_SIZE) as u32)
    }

    /// Loads bytes from the given region of memory.
    fn load_region(&mut self, addr: u32, size: u32) -> Vec<u8> {
        let mut region = Vec::new();
        for addr in addr..addr + size {
            region.push(self.load_u8(addr));
        }
        region
    }

    /// Loads an individual word from memory.
    fn load_u32(&mut self, addr: u32) -> u32;

    /// Loads an individual byte from memory.
    fn load_u8(&mut self, addr: u32) -> u8;

    /// Loads a null-terminated string from memory.
    fn load_string(&mut self, mut addr: u32) -> Result<String> {
        let mut s: Vec<u8> = Vec::new();
        loop {
            let b = self.load_u8(addr);
            if b == 0 {
                break;
            }
            s.push(b);
            addr += 1;
        }
        String::from_utf8(s).map_err(anyhow::Error::msg)
    }
}
