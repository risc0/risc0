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

//! Handlers for two-way private I/O between host and guest.

mod args;
mod cycle_count;
// mod fork;
mod getenv;
mod keccak;
mod log;
mod panic;
mod pipe;
mod posix_io;
mod random;
mod verify;
mod verify2;

use std::{
    cell::RefCell,
    collections::HashMap,
    rc::Rc,
    sync::{Arc, Mutex},
};

use anyhow::{Result, anyhow};
use enum_map::EnumMap;
use risc0_binfmt::ByteAddr;
use risc0_zkp::core::digest::Digest;
use risc0_zkvm_platform::syscall::{
    DIGEST_BYTES, SyscallName,
    nr::{
        SYS_ARGC, SYS_ARGV, SYS_CYCLE_COUNT, SYS_GETENV, SYS_KECCAK, SYS_LOG, SYS_PANIC, SYS_PIPE,
        SYS_RANDOM, SYS_READ, SYS_VERIFY_INTEGRITY, SYS_VERIFY_INTEGRITY2, SYS_WRITE,
    },
};

use crate::{
    Assumption, AssumptionReceipt, ExecutorEnv,
    host::{
        client::{
            env::{AssumptionReceipts, CoprocessorCallbackRef, ProveKeccakRequest},
            posix_io::PosixIo,
        },
        prove_info::{SyscallKind, SyscallMetric},
    },
};

use self::{
    args::SysArgs, cycle_count::SysCycleCount, getenv::SysGetenv, keccak::SysKeccak, log::SysLog,
    panic::SysPanic, pipe::SysPipe, posix_io::SysRead, posix_io::SysWrite, random::SysRandom,
    verify::SysVerify, verify2::SysVerify2,
};

/// A host-side implementation of a system call.
pub(crate) trait Syscall {
    /// Invokes the system call.
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)>;
}

/// Access to memory and machine state for syscalls.
#[allow(dead_code)]
pub(crate) trait SyscallContext<'a> {
    /// Returns the current program counter.
    fn get_pc(&self) -> u32;

    /// Returns the current cycle being executed.
    fn get_cycle(&self) -> u64;

    /// Loads the value of the given register, e.g. REG_A0.
    fn load_register(&mut self, idx: usize) -> u32;

    /// Loads an individual byte from memory.
    fn load_u8(&mut self, addr: ByteAddr) -> Result<u8>;

    /// Loads an individual word from memory.
    fn load_u32(&mut self, addr: ByteAddr) -> Result<u32>;

    /// Loads bytes from the given region of memory. A region may span multiple pages.
    fn load_region(&mut self, addr: ByteAddr, size: u32) -> Result<Vec<u8>> {
        let mut region = Vec::new();
        for i in 0..size {
            region.push(self.load_u8(addr + i)?);
        }
        Ok(region)
    }

    /// Loads a digest from the address in the specified register.
    fn load_digest_from_register(&mut self, idx: usize) -> Result<Digest> {
        let addr = ByteAddr(self.load_register(idx));
        self.load_region(addr, DIGEST_BYTES as u32)?
            .try_into()
            .map_err(|vec| anyhow!("invalid digest: {vec:?}"))
    }

    /// Load a page from memory at the specified page index.
    fn load_page(&mut self, page_idx: u32) -> Result<Vec<u8>>;

    /// Access the syscall table.
    fn syscall_table(&self) -> &SyscallTable<'a>;
}

pub(crate) type AssumptionUsage = Vec<(Assumption, AssumptionReceipt)>;

#[derive(Clone)]
pub(crate) struct SyscallTable<'a> {
    pub(crate) inner: HashMap<String, Rc<RefCell<dyn Syscall + 'a>>>,
    pub(crate) posix_io: Rc<RefCell<PosixIo<'a>>>,
    pub(crate) assumptions: Rc<RefCell<AssumptionReceipts>>,
    pub(crate) assumptions_used: Arc<Mutex<AssumptionUsage>>,
    pub(crate) mmr_assumptions: Rc<RefCell<Vec<AssumptionReceipt>>>,
    pub(crate) coprocessor: Option<CoprocessorCallbackRef<'a>>,
    pub(crate) pending_keccaks: Rc<RefCell<Vec<ProveKeccakRequest>>>,
    pub(crate) metrics: Rc<RefCell<EnumMap<SyscallKind, SyscallMetric>>>,
}

impl<'a> SyscallTable<'a> {
    pub fn new(env: &ExecutorEnv<'a>) -> Self {
        Self {
            inner: Default::default(),
            posix_io: env.posix_io.clone(),
            assumptions: env.assumptions.clone(),
            assumptions_used: Default::default(),
            mmr_assumptions: Default::default(),
            coprocessor: env.coprocessor.clone(),
            pending_keccaks: Default::default(),
            metrics: Default::default(),
        }
    }

    pub fn from_env(env: &ExecutorEnv<'a>) -> Self {
        let mut this = Self::new(env);
        this.with_syscall(SYS_ARGC, SysArgs(env.args.clone()))
            .with_syscall(SYS_ARGV, SysArgs(env.args.clone()))
            .with_syscall(SYS_CYCLE_COUNT, SysCycleCount)
            // .with_syscall(SYS_FORK, SysFork)
            .with_syscall(SYS_GETENV, SysGetenv(env.env_vars.clone()))
            .with_syscall(SYS_KECCAK, SysKeccak::new(env.keccak_max_po2))
            .with_syscall(SYS_LOG, SysLog)
            .with_syscall(SYS_PANIC, SysPanic)
            .with_syscall(SYS_PIPE, SysPipe::default())
            .with_syscall(SYS_RANDOM, SysRandom)
            .with_syscall(SYS_READ, SysRead)
            .with_syscall(SYS_VERIFY_INTEGRITY, SysVerify)
            .with_syscall(SYS_VERIFY_INTEGRITY2, SysVerify2)
            .with_syscall(SYS_WRITE, SysWrite);
        this
    }

    pub(crate) fn with_syscall(
        &mut self,
        syscall: SyscallName,
        handler: impl Syscall + 'a,
    ) -> &mut Self {
        self.inner
            .insert(syscall.as_str().to_string(), Rc::new(RefCell::new(handler)));
        self
    }

    pub(crate) fn get_syscall(&self, name: &str) -> Option<&Rc<RefCell<(dyn Syscall + 'a)>>> {
        self.inner.get(name)
    }
}

impl AssumptionReceipts {
    pub(crate) fn find_assumption(
        &self,
        claim_digest: &Digest,
        control_root: &Digest,
    ) -> Result<Option<(Assumption, AssumptionReceipt)>> {
        use anyhow::Context;

        for assumption_receipt in self.0.iter() {
            let cached_claim_digest = assumption_receipt
                .claim_digest()
                .context("failed to access claim digest on cached assumption")?;

            if cached_claim_digest != *claim_digest {
                tracing::debug!("receipt with claim {cached_claim_digest} does not match");
                continue;
            }

            // If the control root supplied by the guest is not zero, then they are requesting a
            // specific set of recursion programs be used to resolve the assumption. Check that the
            // given receipt can indeed resolve the assumption.
            // NOTE: We currently only support using Succinct receipts here.
            if *control_root != Digest::ZERO {
                let Some(cached_control_root) = (match assumption_receipt {
                    AssumptionReceipt::Proven(receipt) => receipt
                        .succinct()
                        .ok()
                        .map(|r| r.control_root())
                        .transpose()?,
                    AssumptionReceipt::Unresolved(unresolved) => Some(unresolved.control_root),
                }) else {
                    // Elevate to warning because this really is likely an error.
                    tracing::warn!(
                        "receipt with claim {cached_claim_digest} is not a succinct receipt"
                    );
                    continue;
                };
                if cached_control_root != *control_root {
                    // Elevate to warning because this really is likely an error.
                    tracing::warn!(
                        "receipt with claim {cached_claim_digest} has control root {cached_control_root}; guest requested {control_root}"
                    );
                    continue;
                }
            }

            return Ok(Some((
                Assumption {
                    claim: *claim_digest,
                    control_root: *control_root,
                },
                assumption_receipt.clone(),
            )));
        }

        Ok(None)
    }
}
