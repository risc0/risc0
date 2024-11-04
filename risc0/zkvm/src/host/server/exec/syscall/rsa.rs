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
use num_bigint::BigUint;
use num_traits::ops::bytes::ToBytes;
use risc0_circuit_rv32im::prove::emu::addr::ByteAddr;
use risc0_zkvm_platform::syscall::{
    reg_abi::{REG_A3, REG_A4},
    rsa,
};
use risc0_zkvm_platform::WORD_SIZE;

use super::{Syscall, SyscallContext};

pub(crate) struct SysRSA;
impl Syscall for SysRSA {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        assert!(WORD_SIZE == 4); // The inputs on the other side of this syscall assume u32 words
        tracing::debug!("SYS_RSA");
        // Load inputs into BigUint
        let base_ptr = ByteAddr(ctx.load_register(REG_A3));
        let modulus_ptr = ByteAddr(ctx.load_register(REG_A4));
        let base = ctx.load_region(base_ptr, rsa::WIDTH_BYTES.try_into()?)?;
        let modulus = ctx.load_region(modulus_ptr, rsa::WIDTH_BYTES.try_into()?)?;
        let base = BigUint::from_bytes_le(&base);
        let modulus = BigUint::from_bytes_le(&modulus);
        // Compute result
        let result = base.modpow(&BigUint::from(rsa::RSA_EXPONENT), &modulus);
        // `to_guest` should be exactly WIDTH_BYTES, so get the size right then copy into there
        let mut result = result.to_le_bytes();
        // modpow shouldn't return higher than modulus, which fits in WIDTH_BYTES
        assert!(result.len() <= rsa::WIDTH_BYTES);
        // Must return full width, even if result is smaller
        result.resize(rsa::WIDTH_BYTES, 0);
        bytemuck::cast_slice_mut(to_guest).clone_from_slice(result.as_slice());
        Ok((0, 0))
    }
}
