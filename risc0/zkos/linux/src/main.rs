// Copyright 2025 RISC Zero, Inc.
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

#![cfg_attr(target_arch = "riscv32", no_std)]
#![cfg_attr(target_arch = "riscv32", no_main)]

// Enable alloc crate for heap allocations
#[cfg(target_arch = "riscv32")]
extern crate alloc;

#[cfg(not(target_arch = "riscv32"))]
fn main() {}

#[macro_use]
mod kernel;
mod allocator;
mod atomic_emul;
mod compressed_emul;
mod constants;
mod host_calls;
mod linux_abi;
mod linux_abi_fs;
mod linux_abi_misc;
mod linux_abi_privileged;
mod linux_abi_sockets;
mod p9;
mod p9_zkvm;
mod softfloat;

// Set up the global allocator
#[cfg(target_arch = "riscv32")]
#[global_allocator]
static GLOBAL_ALLOCATOR: allocator::KernelAllocator = allocator::KernelAllocator;

// Make init_kernel_allocator available to assembly code
#[cfg(target_arch = "riscv32")]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn init_kernel_allocator() {
    unsafe {
        allocator::init_kernel_allocator();
    }
}
