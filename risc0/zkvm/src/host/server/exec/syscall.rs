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

use std::{cell::RefCell, cmp::min, collections::HashMap, rc::Rc, str::from_utf8};

use anyhow::{anyhow, bail, Result};
use bytes::Bytes;
use risc0_zkvm_platform::{
    fileno,
    syscall::{
        nr::{
            SYS_ARGC, SYS_ARGV, SYS_CYCLE_COUNT, SYS_GETENV, SYS_LOG, SYS_PANIC, SYS_RANDOM,
            SYS_READ, SYS_VERIFY, SYS_VERIFY_INTEGRITY, SYS_VERIFY_RECEIPT, SYS_WRITE,
        },
        reg_abi::{REG_A3, REG_A4, REG_A5},
        SyscallName, DIGEST_BYTES, DIGEST_WORDS,
    },
    WORD_SIZE,
};

use crate::{
    host::{
        client::{
            env::{Assumptions, ExecutorEnv},
            posix_io::PosixIo,
            slice_io::SliceIo,
        },
        receipt::ReceiptWithImageId,
    },
    sha::{Digest, Digestible},
    Assumption, MaybePruned, PrunedValueError, ReceiptClaim,
};

/// A host-side implementation of a system call.
pub trait Syscall {
    /// Invokes the system call.
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)>;
}

/// Access to memory and machine state for syscalls.
pub trait SyscallContext {
    /// Returns the current cycle being executed.
    fn get_cycle(&self) -> usize;

    /// Loads the value of the given register, e.g. REG_A0.
    fn load_register(&mut self, idx: usize) -> u32;

    /// Loads an individual byte from memory.
    fn load_u8(&mut self, addr: u32) -> Result<u8>;

    /// Loads bytes from the given region of memory.
    fn load_region(&mut self, addr: u32, size: u32) -> Result<Vec<u8>> {
        let mut region = Vec::new();
        for addr in addr..addr + size {
            region.push(self.load_u8(addr)?);
        }
        Ok(region)
    }
}

#[derive(Clone)]
pub(crate) struct SyscallTable<'a> {
    pub(crate) inner: HashMap<String, Rc<RefCell<dyn Syscall + 'a>>>,
}

impl<'a> SyscallTable<'a> {
    pub fn new(env: &ExecutorEnv<'a>) -> Self {
        let mut this = Self {
            inner: HashMap::new(),
        };

        let sys_verify = SysVerify::new(env.assumptions.clone());

        let posix_io = env.posix_io.clone();
        this.with_syscall(SYS_CYCLE_COUNT, SysCycleCount)
            .with_syscall(SYS_LOG, posix_io.clone())
            .with_syscall(SYS_PANIC, SysPanic)
            .with_syscall(SYS_RANDOM, SysRandom)
            .with_syscall(SYS_GETENV, SysGetenv(env.env_vars.clone()))
            .with_syscall(SYS_READ, posix_io.clone())
            .with_syscall(SYS_WRITE, posix_io)
            .with_syscall(SYS_VERIFY, sys_verify.clone())
            .with_syscall(SYS_VERIFY_INTEGRITY, sys_verify.clone())
            .with_syscall(SYS_VERIFY_RECEIPT, sys_verify)
            .with_syscall(SYS_ARGC, Args(env.args.clone()))
            .with_syscall(SYS_ARGV, Args(env.args.clone()));
        for (syscall, handler) in env.slice_io.borrow().inner.iter() {
            let handler = SysSliceIo::new(handler.clone());
            this.inner
                .insert(syscall.clone(), Rc::new(RefCell::new(handler)));
        }

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

pub(crate) struct SysCycleCount;
impl Syscall for SysCycleCount {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        _to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        Ok((ctx.get_cycle() as u32, 0))
    }
}

pub(crate) struct SysGetenv(pub HashMap<String, String>);
impl Syscall for SysGetenv {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let buf_ptr = ctx.load_register(REG_A3);
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        let msg = from_utf8(&from_guest)?;

        match self.0.get(msg) {
            None => Ok((u32::MAX, 0)),
            Some(val) => {
                let nbytes = min(to_guest.len() * WORD_SIZE, val.as_bytes().len());
                let to_guest_u8s: &mut [u8] = bytemuck::cast_slice_mut(to_guest);
                to_guest_u8s[0..nbytes].clone_from_slice(&val.as_bytes()[0..nbytes]);
                Ok((val.as_bytes().len() as u32, 0))
            }
        }
    }
}

pub(crate) struct SysPanic;
impl Syscall for SysPanic {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        _to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let buf_ptr = ctx.load_register(REG_A3);
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        let msg = from_utf8(&from_guest)?;
        bail!("Guest panicked: {msg}");
    }
}

pub(crate) struct SysRandom;
impl Syscall for SysRandom {
    fn syscall(
        &mut self,
        _syscall: &str,
        _ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        tracing::debug!("SYS_RANDOM: {}", to_guest.len());
        let mut rand_buf = vec![0u8; to_guest.len() * WORD_SIZE];
        getrandom::getrandom(rand_buf.as_mut_slice())?;
        bytemuck::cast_slice_mut(to_guest).clone_from_slice(rand_buf.as_slice());
        Ok((0, 0))
    }
}

#[derive(Clone)]
pub(crate) struct SysVerify {
    pub(crate) assumptions: Rc<RefCell<Assumptions>>,
}

impl SysVerify {
    pub(crate) fn new(assumptions: Rc<RefCell<Assumptions>>) -> Self {
        Self { assumptions }
    }

    fn sys_verify_integrity(&mut self, from_guest: Vec<u8>) -> Result<(u32, u32)> {
        let claim_digest: Digest = from_guest
            .try_into()
            .map_err(|vec| anyhow!("failed to convert to [u8; DIGEST_BYTES]: {vec:?}"))?;

        tracing::debug!("SYS_VERIFY_INTEGRITY: {}", hex::encode(&claim_digest));

        // Iterate over the list looking for a matching assumption.
        let mut assumption: Option<Assumption> = None;
        for cached_assumption in self.assumptions.borrow().cached.iter() {
            if cached_assumption.get_claim()?.digest() == claim_digest {
                assumption = Some(cached_assumption.clone());
                break;
            }
        }

        let Some(assumption) = assumption else {
            return Err(anyhow!(
                "sys_verify_integrity: failed to resolve claim digest: {claim_digest}"
            ));
        };

        // Mark the assumption as accessed, pushing it to the head of the list, and return the success code.
        self.assumptions.borrow_mut().accessed.insert(0, assumption);
        return Ok((0, 0));
    }

    fn sys_verify(&mut self, mut from_guest: Vec<u8>, to_guest: &mut [u32]) -> Result<(u32, u32)> {
        if from_guest.len() != DIGEST_BYTES * 2 {
            bail!(
                "sys_verify call with input of length {} bytes; expected {}",
                from_guest.len(),
                DIGEST_BYTES * 2
            );
        }
        if to_guest.len() != DIGEST_WORDS + 1 {
            bail!(
                "sys_verify call with output of length {} words; expected {}",
                to_guest.len(),
                DIGEST_WORDS + 1
            );
        }

        let journal_digest: Digest = from_guest
            .split_off(DIGEST_BYTES)
            .try_into()
            .map_err(|vec| anyhow!("failed to convert to [u8; DIGEST_BYTES]: {vec:?}"))?;
        let image_id: Digest = from_guest
            .try_into()
            .map_err(|vec| anyhow!("failed to convert to [u8; DIGEST_BYTES]: {vec:?}"))?;

        tracing::debug!(
            "SYS_VERIFY: {}, {}",
            hex::encode(&image_id),
            hex::encode(&journal_digest)
        );

        // Iterate over the list looking for a matching assumption. If found, return the
        // post state digest and system exit code.
        let mut assumption: Option<Assumption> = None;
        for cached_assumption in self.assumptions.borrow().cached.iter() {
            let assumption_claim = cached_assumption.get_claim()?;
            let cmp_result = Self::sys_verify_cmp(&assumption_claim, &image_id, &journal_digest);
            let (post_state_digest, sys_exit_code) = match cmp_result {
                Ok(None) => continue,
                // If the required values to compare were pruned, go the next assumption.
                Err(e) => {
                    tracing::debug!(
                        "sys_verify: pruned values in assumption prevented comparison: {e} : {assumption_claim:?}"
                    );
                    continue;
                }
                Ok(Some(out)) => out,
            };

            // Write the post_state_digest to the guest buffer as a result.
            to_guest[..DIGEST_WORDS].copy_from_slice(post_state_digest.as_words());
            to_guest[DIGEST_WORDS] = sys_exit_code;
            assumption = Some(cached_assumption.clone());
            break;
        }

        let Some(assumption) = assumption else {
            return Err(anyhow!(
                "sys_verify_integrity: failed to resolve journal_digest and image_id: {journal_digest}, {image_id}"
            ));
        };

        // Mark the assumption as accessed, pushing it to the head of the list, and return the success code.
        self.assumptions.borrow_mut().accessed.insert(0, assumption);
        return Ok((0, 0));
    }

    fn sys_verify_receipt(
        &mut self,
        from_guest: Vec<u8>,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let ReceiptWithImageId { receipt, image_id } = crate::serde::from_slice(&from_guest)?;
        match receipt.verify(image_id) {
            Ok(()) => {
                let claim = receipt.inner.get_claim()?;
                to_guest[..DIGEST_WORDS].copy_from_slice(claim.post.digest().as_words());
                to_guest[DIGEST_WORDS] = claim.exit_code.into_pair().0;

                let mut assumption: Option<Assumption> = None;
                let claim_digest = claim.digest();
                // If we already have an assumption for this receipt, find it. Otherwise, create one.
                for cached_assumption in self.assumptions.borrow().cached.iter() {
                    if cached_assumption.get_claim()?.digest() == claim_digest {
                        assumption = Some(cached_assumption.clone());
                        break;
                    }
                }
                let assumption = if let Some(assumption) = assumption {
                    assumption
                } else {
                    Assumption::Proven(receipt)
                };

                // In either case, push the assumption to the head of the list, and return the success code.
                self.assumptions.borrow_mut().accessed.insert(0, assumption);
                Ok((0, 0))
            }
            Err(_) => Ok((u32::MAX, 0)),
        }
    }

    /// Check whether the claim satisfies the requirements to return for sys_verify.
    fn sys_verify_cmp(
        claim: &MaybePruned<ReceiptClaim>,
        image_id: &Digest,
        journal_digest: &Digest,
    ) -> Result<Option<(Digest, u32)>, PrunedValueError> {
        let assumption_journal_digest = claim
            .as_value()?
            .output
            .as_value()?
            .as_ref()
            .map(|output| output.journal.digest())
            .unwrap_or(Digest::ZERO);
        let assumption_image_id = claim.as_value()?.pre.digest();

        if &assumption_journal_digest != journal_digest || &assumption_image_id != image_id {
            return Ok(None);
        }

        // Check that the exit code is either Halted(0) or Paused(0).
        if !claim.as_value()?.exit_code.is_ok() {
            tracing::debug!("sys_verify: ignoring matching claim with error exit code: {claim:?}");
            return Ok(None);
        };

        // Check that the assumption has no assumptions.
        let assumption_assumptions_digest = claim
            .as_value()?
            .output
            .as_value()?
            .as_ref()
            .map(|output| output.assumptions.digest())
            .unwrap_or(Digest::ZERO);

        if assumption_assumptions_digest != Digest::ZERO {
            tracing::debug!(
                "sys_verify: ignoring matching claim with non-empty assumptions: {claim:?}"
            );
            return Ok(None);
        }

        // Return the post state digest and exit code.
        Ok(Some((
            claim.as_value()?.post.digest(),
            claim.as_value()?.exit_code.into_pair().0,
        )))
    }
}

impl Syscall for SysVerify {
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let from_guest_ptr = ctx.load_register(REG_A3);
        let from_guest_len = ctx.load_register(REG_A4);
        let from_guest: Vec<u8> = ctx.load_region(from_guest_ptr, from_guest_len)?;

        if syscall == SYS_VERIFY.as_str() {
            self.sys_verify(from_guest, to_guest)
        } else if syscall == SYS_VERIFY_INTEGRITY.as_str() {
            self.sys_verify_integrity(from_guest)
        } else if syscall == SYS_VERIFY_RECEIPT.as_str() {
            self.sys_verify_receipt(from_guest, to_guest)
        } else {
            bail!("SysVerify received unrecognized syscall: {syscall}")
        }
    }
}

#[derive(Clone)]
pub(crate) struct Args(pub Vec<String>);

impl Syscall for Args {
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        if syscall == SYS_ARGC.as_str() {
            Ok((self.0.len().try_into()?, 0))
        } else if syscall == SYS_ARGV.as_str() {
            // Get the arg or return an error if out of bounds.
            let arg_index = ctx.load_register(REG_A3);
            let arg_val = self.0.get(arg_index as usize).ok_or_else(|| {
                anyhow!(
                    "guest requested index {arg_index} from argv of len {}",
                    self.0.len()
                )
            })?;

            let nbytes = min(to_guest.len() * WORD_SIZE, arg_val.as_bytes().len());
            let to_guest_u8s: &mut [u8] = bytemuck::cast_slice_mut(to_guest);
            to_guest_u8s[0..nbytes].clone_from_slice(&arg_val.as_bytes()[0..nbytes]);
            Ok((arg_val.as_bytes().len() as u32, 0))
        } else {
            bail!("Unknown syscall {syscall}")
        }
    }
}

/// A wrapper around a SliceIo that exposes it as a Syscall handler.
pub struct SysSliceIo<'a> {
    handler: Rc<RefCell<dyn SliceIo + 'a>>,
    stored_result: RefCell<Option<Bytes>>,
}

impl<'a> SysSliceIo<'a> {
    /// Wraps the given [SliceIo] into a [SysSliceIo].
    pub fn new(handler: Rc<RefCell<dyn SliceIo + 'a>>) -> Self {
        Self {
            handler,
            stored_result: RefCell::new(None),
        }
    }
}

/// An implementation of a [Syscall] for a [SliceIo].
///
/// When activated as a SyscallHandler, the SyscallHandler expects two
/// calls. The first call returns (nelem, _) indicating how many
/// elements are to be sent back to the guest, and the second call
/// actually returns the elements after the guest allocates space.
impl<'a> Syscall for SysSliceIo<'a> {
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let mut stored_result = self.stored_result.borrow_mut();
        let buf_ptr = ctx.load_register(REG_A3);
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        Ok(match stored_result.take() {
            None => {
                // First call of pair. Send the data from the guest to the SliceIo
                // and save what it returns.
                assert_eq!(to_guest.len(), 0);
                let mut handler = self.handler.borrow_mut();
                let result = handler.handle_io(syscall, from_guest.into())?;
                let len = result.len() as u32;
                *stored_result = Some(result);
                (len, 0)
            }
            Some(stored) => {
                // Second call of pair. We already have data to send
                // to the guest; send it to the buffer that the guest
                // allocated.
                let to_guest_bytes: &mut [u8] = bytemuck::cast_slice_mut(to_guest);
                assert!(stored.len() <= to_guest_bytes.len());
                assert!(stored.len() + WORD_SIZE > to_guest_bytes.len());
                to_guest_bytes[..stored.len()].clone_from_slice(&stored);
                (0, 0)
            }
        })
    }
}

impl<'a> Syscall for PosixIo<'a> {
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        // TODO: Is there a way to use "match" here instead of if statements?
        if syscall == SYS_READ.as_str() {
            self.sys_read(ctx, to_guest)
        } else if syscall == SYS_WRITE.as_str() {
            self.sys_write(ctx)
        } else if syscall == SYS_LOG.as_str() {
            self.sys_log(ctx)
        } else {
            bail!("Unknown syscall {syscall}")
        }
    }
}

impl<'a> Syscall for Rc<RefCell<PosixIo<'a>>> {
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        self.borrow_mut().syscall(syscall, ctx, to_guest)
    }
}

impl<'a> PosixIo<'a> {
    fn sys_read(
        &mut self,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let fd = ctx.load_register(REG_A3);
        let nbytes = ctx.load_register(REG_A4) as usize;

        tracing::trace!(
            "sys_read(fd: {fd}, nbytes: {nbytes}, into: {} bytes)",
            to_guest.len() * WORD_SIZE
        );

        assert!(
            nbytes >= to_guest.len() * WORD_SIZE,
            "Word-aligned read buffer must be fully filled"
        );

        let reader = self
            .read_fds
            .get_mut(&fd)
            .ok_or(anyhow!("Bad read file descriptor {fd}"))?;

        // So that we don't have to deal with short reads, keep
        // reading until we get EOF or fill the buffer.
        let read_all = |mut buf: &mut [u8]| -> Result<usize> {
            let mut tot_nread = 0;
            while !buf.is_empty() {
                let nread = reader.borrow_mut().read(buf)?;
                if nread == 0 {
                    break;
                }
                tot_nread += nread;
                (_, buf) = buf.split_at_mut(nread);
            }
            Ok(tot_nread)
        };

        let to_guest_u8 = bytemuck::cast_slice_mut(to_guest);
        let nread_main = read_all(to_guest_u8)?;

        tracing::trace!("read: {nread_main}, requested: {}", to_guest_u8.len());

        // It's possible that there's an unaligned word at the end
        let unaligned_end = if nbytes - nread_main <= WORD_SIZE {
            nbytes - nread_main
        } else {
            // We encountered an EOF. There's nothing left to read
            0
        };

        // Fill unaligned word out.
        let mut to_guest_end: [u8; WORD_SIZE] = [0; WORD_SIZE];
        let nread_end = read_all(&mut to_guest_end[0..unaligned_end])?;

        Ok((
            (nread_main + nread_end) as u32,
            u32::from_le_bytes(to_guest_end),
        ))
    }

    fn sys_write(&mut self, ctx: &mut dyn SyscallContext) -> Result<(u32, u32)> {
        let fd = ctx.load_register(REG_A3);
        let buf_ptr = ctx.load_register(REG_A4);
        let buf_len = ctx.load_register(REG_A5);
        let from_guest_bytes = ctx.load_region(buf_ptr, buf_len)?;
        let writer = self
            .write_fds
            .get_mut(&fd)
            .ok_or(anyhow!("Bad write file descriptor {fd}"))?;

        tracing::trace!("sys_write(fd: {fd}, bytes: {buf_len})");

        writer.borrow_mut().write_all(from_guest_bytes.as_slice())?;
        Ok((0, 0))
    }

    fn sys_log(&mut self, ctx: &mut dyn SyscallContext) -> Result<(u32, u32)> {
        let buf_ptr = ctx.load_register(REG_A3);
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        // write to stdout, but be sure to point it to where the file descriptor is pointing
        let writer = self
            .write_fds
            .get_mut(&fileno::STDOUT)
            .ok_or(anyhow!("Bad write file descriptor {}", &fileno::STDOUT))?;

        tracing::debug!("sys_log({buf_len} bytes)");

        let msg = format!("R0VM[{}] ", ctx.get_cycle().to_string());
        writer
            .borrow_mut()
            .write_all(&[msg.as_bytes(), &from_guest, b"\n"].concat())?;
        Ok((0, 0))
    }
}

// SysCycleCount:
//     ctx.get_cycle()

// SysGetenv:
//     let buf_ptr = ctx.load_register(REG_A3);
//     let buf_len = ctx.load_register(REG_A4);
//     let from_guest = ctx.load_region(buf_ptr, buf_len)?;

// SysPanic:
//     let buf_ptr = ctx.load_register(REG_A3);
//     let buf_len = ctx.load_register(REG_A4);
//     let from_guest = ctx.load_region(buf_ptr, buf_len)?;

// SysRandom:
//     write to_guest

// SysVerify:
//     let from_guest_ptr = ctx.load_register(REG_A3);
//     let from_guest_len = ctx.load_register(REG_A4);
//     let from_guest: Vec<u8> = ctx.load_region(from_guest_ptr, from_guest_len)?;

// SysArgs:
//     let arg_index = ctx.load_register(REG_A3);

// SysSliceIo:
//     let buf_ptr = ctx.load_register(REG_A3);
//     let buf_len = ctx.load_register(REG_A4);
//     let from_guest = ctx.load_region(buf_ptr, buf_len)?;

// PosixIo/sys_read:
//     let fd = ctx.load_register(REG_A3);
//     let nbytes = ctx.load_register(REG_A4) as usize;

// PosixIo/sys_write:
//     let fd = ctx.load_register(REG_A3);
//     let buf_ptr = ctx.load_register(REG_A4);
//     let buf_len = ctx.load_register(REG_A5);
//     let from_guest_bytes = ctx.load_region(buf_ptr, buf_len)?;

// PosixIo/sys_log:
//     let buf_ptr = ctx.load_register(REG_A3);
//     let buf_len = ctx.load_register(REG_A4);
//     let from_guest = ctx.load_region(buf_ptr, buf_len)?;
