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

use std::{
    cmp,
    sync::atomic::{AtomicUsize, Ordering},
};

use anyhow::{anyhow, bail, ensure, Result};
use lazy_regex::{regex, Captures};
use rayon::prelude::*;
use risc0_zkp::{
    adapter::CircuitStepContext,
    field::{
        baby_bear::{BabyBearElem, Elem},
        Elem as _,
    },
    hal::cpu::SyncSlice,
};
use risc0_zkvm_platform::syscall::bigint;

use super::{
    argument::{BytesArgument, RamArgument},
    Quad,
};
use crate::{
    prove::{
        emu::{
            addr::{ByteAddr, WordAddr},
            mux::{Major, TopMux},
            preflight::{Back, PreflightCycle, PreflightStage, PreflightTrace},
        },
        hal::cpp::ParallelCircuitStepHandler,
    },
    CIRCUIT,
};

struct Injector<'a> {
    steps: usize,
    cycle: usize,
    data: &'a SyncSlice<'a, BabyBearElem>,
}

pub struct MachineContext {
    trace: PreflightTrace,

    // Tables for sorting arguments in proper order
    ram_arg: RamArgument,
    bytes_arg: BytesArgument,
}

impl<'a> Injector<'a> {
    fn new(steps: usize, cycle: usize, data: &'a SyncSlice<'a, BabyBearElem>) -> Self {
        Self { steps, cycle, data }
    }

    fn get_idx(&self, reg: usize) -> usize {
        reg * self.steps + self.cycle - 1
    }

    fn set_pc(&self, pc: ByteAddr) {
        let pc = pc + 4u32;
        let bytes = pc.0.to_le_bytes();
        let bot2 = bytes[3] & 0b11;
        let top2 = bytes[3] >> 2 & 0b11;
        self.data.set(self.get_idx(6), (bytes[0] as u32).into()); // body->pc.bytes[0]
        self.data.set(self.get_idx(7), (bytes[1] as u32).into()); // body->pc.bytes[1]
        self.data.set(self.get_idx(8), (bytes[2] as u32).into()); // body->pc.bytes[2]
        self.data.set(self.get_idx(70), (bot2 as u32).into()); // body->pc.twits[0]
        self.data.set(self.get_idx(71), (top2 as u32).into()); // body->pc.twits[1]
    }

    fn set_next_major(&self, major: Major) {
        self.data.set(self.get_idx(99), major.as_u32().into()); // body->nextMajor
    }

    fn set_halt(&self, sys_exit_code: u8, user_exit_code: u8, write_addr: WordAddr) {
        self.data.set(self.get_idx(108), 0u32.into()); // body->majorSelect->at(MajorType::kECall): 8
        self.data.set(self.get_idx(112), 0u32.into()); // body->majorSelect->at(MajorType::kPageFault): 12
        self.data.set(self.get_idx(115), 1u32.into()); // body->majorSelect->at(MajorType::kHalt): 15
        self.data
            .set(self.get_idx(116), (sys_exit_code as u32).into()); // HaltCycle::sysExitCode
        self.data
            .set(self.get_idx(117), (user_exit_code as u32).into()); // HaltCycle::userExitCode
        self.data.set(self.get_idx(118), write_addr.0.into()); // HaltCycle::writeAddr
    }
}

impl MachineContext {
    pub fn new(steps: usize, trace: PreflightTrace) -> Self {
        Self {
            trace,
            ram_arg: RamArgument::new(steps),
            bytes_arg: BytesArgument::new(steps),
        }
    }

    pub fn is_exec_par_safe(&self, cycle: usize) -> bool {
        let cur_cycle = self.get_cycle(cycle);
        let is_safe = cur_cycle.back.is_some();
        // tracing::debug!("is_exec_par_safe: {cycle} <= {is_safe}");
        is_safe
    }

    pub fn inject_exec_backs(&self, steps: usize, cycle: usize, data: &SyncSlice<BabyBearElem>) {
        let cur_cycle = self.get_cycle(cycle);
        if let Some(back) = &cur_cycle.back {
            let injector = Injector::new(steps, cycle, data);
            match back {
                Back::Null => (),
                Back::Body { pc } => {
                    injector.set_pc(*pc);
                    injector.set_next_major(Major::MuxSize);
                }
                Back::Halt {
                    pc,
                    sys_exit_code,
                    user_exit_code,
                    write_addr,
                } => {
                    injector.set_pc(*pc);
                    injector.set_halt(*sys_exit_code, *user_exit_code, *write_addr);
                    injector.set_next_major(Major::Halt);
                }
            }
        }
    }

    #[tracing::instrument(skip_all)]
    pub fn sort(&mut self, name: &str) {
        match name {
            "ram" => self.ram_arg.sort(),
            "bytes" => self.bytes_arg.sort(),
            _ => unimplemented!("Unknown argument type {name}"),
        };
    }

    pub fn step_exec(
        &self,
        steps: usize,
        cycle: usize,
        args: &[SyncSlice<BabyBearElem>],
    ) -> Result<BabyBearElem> {
        // let cur_cycle = self.get_cycle(cycle);
        // tracing::debug!("[{cycle}] {:?}", cur_cycle);
        let ctx = CircuitStepContext { size: steps, cycle };
        CIRCUIT.par_step_exec(&ctx, self, args)
    }

    fn next_step_exec(
        &self,
        steps: usize,
        last_cycle: usize,
        cycle: usize,
        args: &[SyncSlice<BabyBearElem>],
        counts: Option<&[AtomicUsize]>,
    ) {
        if cycle == 0 || self.is_exec_par_safe(cycle) {
            // tracing::debug!("step_exec: {cycle}");
            self.step_exec(steps, cycle, args).unwrap();

            let mut seq_cycle = cycle + 1;
            while seq_cycle < last_cycle && !self.is_exec_par_safe(seq_cycle) {
                self.step_exec(steps, seq_cycle, args).unwrap();
                seq_cycle += 1;
            }

            if let Some(counts) = counts {
                let cycles = seq_cycle - cycle;
                counts[cycles].fetch_add(1, Ordering::SeqCst);
            }
        }
    }

    pub fn rev_step_exec(&self, steps: usize, last_cycle: usize, args: &[SyncSlice<BabyBearElem>]) {
        (0..last_cycle).rev().for_each(|cycle| {
            self.next_step_exec(steps, last_cycle, cycle, args, None);
        });
    }

    pub fn par_step_exec(&self, steps: usize, last_cycle: usize, args: &[SyncSlice<BabyBearElem>]) {
        let counts: Vec<_> = (0..last_cycle).map(|_| AtomicUsize::new(0)).collect();

        (0..last_cycle).into_par_iter().for_each(|cycle| {
            self.next_step_exec(steps, last_cycle, cycle, args, Some(&counts));
        });

        for (cycles, count) in counts.iter().enumerate() {
            let count = count.load(Ordering::Relaxed);
            if count > 0 {
                tracing::debug!("cycles: {cycles} -> {count}");
            }
        }
    }

    pub fn step_verify_mem(
        &self,
        steps: usize,
        cycle: usize,
        args: &[SyncSlice<BabyBearElem>],
    ) -> Result<BabyBearElem> {
        // let cur_cycle = self.get_cycle(cycle);
        // tracing::debug!("[{cycle}] {cur_cycle:?}");
        let ctx = CircuitStepContext { size: steps, cycle };
        CIRCUIT.par_step_verify_mem(&ctx, self, args)
    }

    fn is_verify_mem_par_safe(&self, cycle: usize) -> bool {
        let cur_cycle = self.get_cycle(cycle);
        let is_safe = match cur_cycle.mux {
            TopMux::BytesInit => false,
            TopMux::BytesSetup => false,
            TopMux::RamInit => false,
            TopMux::RamLoad => false,
            TopMux::Reset => false,
            TopMux::Body(Major::VerifyAnd, _) => false,
            TopMux::Body(Major::VerifyDivide, _) => false,
            TopMux::Body(Major::PageFault, _) => false,
            TopMux::Body(Major::Halt, _) => false,
            TopMux::Body(_, _) => true,
            TopMux::RamFini => false,
            TopMux::BytesFini => false,
        };
        // tracing::debug!("is_verify_mem_par_safe: {cycle} <= {is_safe}");
        is_safe
    }

    pub fn inject_verify_mem_backs(
        &self,
        steps: usize,
        cycle: usize,
        data: SyncSlice<BabyBearElem>,
    ) {
        if self.is_verify_mem_par_safe(cycle) {
            self.ram_arg.inject_backs(steps, cycle, data);
        }
    }

    pub fn par_step_verify_mem(
        &self,
        steps: usize,
        last_cycle: usize,
        args: &[SyncSlice<BabyBearElem>],
    ) {
        let counts: Vec<_> = (0..last_cycle).map(|_| AtomicUsize::new(0)).collect();

        (0..last_cycle).into_par_iter().for_each(|cycle| {
            if cycle == 0 || self.is_verify_mem_par_safe(cycle) {
                // tracing::trace!("step_verify_mem({cycle})");
                self.step_verify_mem(steps, cycle, args).unwrap();

                let mut seq_cycle = cycle + 1;
                while seq_cycle < last_cycle && !self.is_verify_mem_par_safe(seq_cycle) {
                    self.step_verify_mem(steps, seq_cycle, args).unwrap();
                    seq_cycle += 1;
                }

                let cycles = seq_cycle - cycle;
                counts.get(cycles).unwrap().fetch_add(1, Ordering::SeqCst);
            }
        });

        for (cycles, count) in counts.iter().enumerate() {
            let count = count.load(Ordering::Relaxed);
            if count > 0 {
                tracing::debug!("cycles: {cycles} -> {count}");
            }
        }
    }

    pub fn step_verify_bytes(
        &self,
        steps: usize,
        cycle: usize,
        args: &[SyncSlice<BabyBearElem>],
    ) -> Result<BabyBearElem> {
        let ctx = CircuitStepContext { size: steps, cycle };
        CIRCUIT.par_step_verify_bytes(&ctx, self, args)
    }
}

impl ParallelCircuitStepHandler<Elem> for MachineContext {
    fn call(
        &self,
        cycle: usize,
        name: &str,
        extra: &str,
        args: &[Elem],
        outs: &mut [Elem],
    ) -> anyhow::Result<()> {
        // tracing::trace!("[{cycle}] call({name})");
        match name {
            "halt" => Ok(()),
            "trace" => Ok(()),
            "getMajor" => self.get_major(cycle, outs),
            "getMinor" => self.get_minor(cycle, outs),
            "divide" => self.divide(args, outs),
            "bigintQuotient" => self.bigint_quotient(args, outs),
            "pageInfo" => self.page_info(cycle, outs),
            "ramWrite" => self.ram_write(cycle, args),
            "ramRead" => self.ram_read(cycle, args, outs),
            "plonkWrite" => self.arg_write(cycle, extra, args),
            "plonkRead" => self.arg_read(cycle, extra, outs),
            "log" => self.log(extra, args),
            "syscallInit" => Ok(()),
            "syscallBody" => self.syscall_body(cycle, outs),
            "syscallFini" => self.syscall_fini(cycle, outs),
            _ => unimplemented!("Unsupported extern: {name}"),
        }
    }
}

impl MachineContext {
    fn arg_read(&self, cycle: usize, name: &str, outs: &mut [Elem]) -> Result<()> {
        // tracing::debug!("[{cycle}] arg_read({name})");
        match name {
            "ram" => self.ram_arg.read(cycle, outs.try_into().unwrap()),
            "bytes" => self.bytes_arg.read(cycle, outs.try_into().unwrap()),
            _ => unimplemented!("Unknown argument type {name}"),
        }
        Ok(())
    }

    fn arg_write(&self, cycle: usize, name: &str, args: &[Elem]) -> Result<()> {
        // tracing::debug!("[{cycle}] arg_write({name})");
        match name {
            "ram" => self.ram_arg.write(cycle, args.try_into().unwrap()),
            "bytes" => self.bytes_arg.write(cycle, args.try_into().unwrap()),
            _ => unimplemented!("Unknown argument type {name}"),
        }
        Ok(())
    }
}

impl MachineContext {
    fn get_stage_offset(&self, cycle: usize) -> (&PreflightStage, usize) {
        if cycle < self.trace.pre.cycles.len() {
            (&self.trace.pre, 0)
        } else {
            (&self.trace.body, self.trace.pre.cycles.len())
        }
    }

    fn get_cycle(&self, cycle: usize) -> &PreflightCycle {
        let (stage, offset) = self.get_stage_offset(cycle);
        &stage.cycles[cycle - offset]
    }

    fn get_major(&self, cycle: usize, outs: &mut [Elem]) -> Result<()> {
        let cur_cycle = self.get_cycle(cycle);
        let (major, _) = cur_cycle.mux.as_body()?;
        // tracing::trace!("[{cycle}] get_major: {major:?}");
        outs[0] = major.as_u32().into();
        Ok(())
    }

    fn get_minor(&self, cycle: usize, outs: &mut [Elem]) -> Result<()> {
        let cur_cycle = self.get_cycle(cycle);
        let (_, minor) = cur_cycle.mux.as_body()?;
        tracing::trace!("[{cycle}] get_minor: {minor:?}");
        outs[0] = minor.into();
        Ok(())
    }

    fn ram_read(&self, cycle: usize, args: &[Elem], outs: &mut [Elem]) -> Result<()> {
        let addr: u32 = args[0].into();
        // let op: u32 = args[1].into();

        let (stage, offset) = self.get_stage_offset(cycle);
        let cycle_idx = cycle - offset;
        let stage_cycles = stage.cycles.len();
        let cur_cycle = stage
            .cycles
            .get(cycle_idx)
            .ok_or_else(|| anyhow!("[{cycle}] Preflight trace truncated: {stage_cycles}"))?;

        let mem_idx = cur_cycle.mem_idx.fetch_add(1, Ordering::Relaxed);

        let txn = &stage.txns[mem_idx];
        let txn_cycle = txn.cycle + offset;
        if txn_cycle != cycle {
            bail!("[{cycle}] Mismatched memory txn cycle. Recorded:{txn_cycle} != Circuit:{cycle}, {cur_cycle:?}, {txn:?}",);
        }

        if txn.addr != WordAddr(addr) {
            bail!(
                "[{cycle}] Mismatched memory txn addr. Recorded:{:?} != Circuit:{:?}, {cur_cycle:?}, {txn:?}",
                txn.addr,
                WordAddr(addr)
            );
        }

        // tracing::trace!(
        //     "[{cycle}] {:?} ram_read(0x{addr:08x}, {op}): {txn:?}",
        //     cur_cycle.mux
        // );

        Quad(outs[0], outs[1], outs[2], outs[3]) = txn.data.into();
        Ok(())
    }

    fn ram_write(&self, _cycle: usize, _args: &[Elem]) -> Result<()> {
        // let addr: u32 = args[0].into();
        // let data: u32 = Quad(args[1], args[2], args[3], args[4]).into();
        // let op: u32 = args[5].into();
        // tracing::trace!(
        //     "[{cycle}] {:?} ram_write(0x{addr:08x}, 0x{data:08x}, {op})",
        //     self.get_cycle(cycle).mux
        // );
        Ok(())
    }

    fn page_info(&self, cycle: usize, outs: &mut [Elem]) -> Result<()> {
        let (stage, offset) = self.get_stage_offset(cycle);
        let cur_cycle = &stage.cycles[cycle - offset];
        let extra_idx = cur_cycle.extra_idx.load(Ordering::Relaxed);
        let is_read = stage.extras[extra_idx + 0];
        let page_idx = stage.extras[extra_idx + 1];
        let is_done = stage.extras[extra_idx + 2];
        // tracing::debug!("[{cycle}] page_info: ({is_read}, 0x{page_idx:05x}, {is_done})");
        (outs[0], outs[1], outs[2]) = (is_read.into(), page_idx.into(), is_done.into());
        Ok(())
    }

    fn divide(&self, args: &[Elem], outs: &mut [Elem]) -> Result<()> {
        let mut numer: u32 = Quad(args[0], args[1], args[2], args[3]).into();
        let mut denom: u32 = Quad(args[4], args[5], args[6], args[7]).into();
        let sign: u32 = args[8].into();
        // tracing::debug!("divide: [{sign}] {numer} / {denom}");
        let ones_comp = (sign == 2) as u32;
        let neg_numer = sign != 0 && (numer as i32) < 0;
        let neg_denom = sign == 1 && (denom as i32) < 0;
        if neg_numer {
            numer = (!numer).overflowing_add(1 - ones_comp).0;
        }
        if neg_denom {
            denom = (!denom).overflowing_add(1 - ones_comp).0;
        }
        let (mut quot, mut rem) = if denom == 0 {
            (0xffffffff, numer)
        } else {
            (numer / denom, numer % denom)
        };
        let quot_neg_out =
            (neg_numer as u32 ^ neg_denom as u32) - ((denom == 0) as u32 * neg_numer as u32);
        if quot_neg_out != 0 {
            quot = (!quot).overflowing_add(1 - ones_comp).0;
        }
        if neg_numer {
            rem = (!rem).overflowing_add(1 - ones_comp).0;
        }
        // tracing::debug!("  quot: {quot}, rem: {rem}");
        Quad(outs[0], outs[1], outs[2], outs[3]) = quot.into();
        Quad(outs[4], outs[5], outs[6], outs[7]) = rem.into();
        Ok(())
    }

    // Division of two positive byte-limbed bigints. a = q * b + r.
    //
    // Assumes a and b are both normalized with limbs in range [0, 255].
    // Returns q as an array of BabyBearElems. (Drops r).
    //     When the denominator is zero, returns zero to facilitate use of the
    //     BigInt modular multiply circuit as an unreduced "checked
    //     multiply" circuit.
    // Returns an error when:
    // * Input denominator b is 0.
    // * Input denominator b is less than 9 bits.
    // * Quotient result q is greater than [bigint::WIDTH_BYTES] limbs. This
    //   will occur if the numerator `a` is the result of a multiplication of
    //   values `x` and `y` such that `floor(x * y / b) >=
    //   2^bigint::WIDTH_BITS`. If x and/or y is less than b (i.e. the modulus
    //   in bigint modular multiply) this constrain will be satisfied.
    fn bigint_quotient(&self, args: &[Elem], outs: &mut [Elem]) -> Result<()> {
        let (a_elems, b_elems) = args.split_at(bigint::WIDTH_BYTES * 2);

        // This is a variant of school-book multiplication.
        // Reference the Handbook of Elliptic and Hyper-elliptic Cryptography alg.
        // 10.5.1

        // Setup working buffers of u64 elements. We use u64 values here because this
        // implementation does a lot of non-field operations and so we need to take the
        // inputs out of Montgomery form.
        let mut a = [0u64; bigint::WIDTH_BYTES * 2 + 1];
        for (i, ai) in a_elems.iter().copied().enumerate() {
            a[i] = u64::from(ai)
        }
        let mut b = [0u64; bigint::WIDTH_BYTES + 1];
        for (i, bi) in b_elems.iter().copied().enumerate() {
            b[i] = u64::from(bi)
        }
        let mut q = [0u64; bigint::WIDTH_BYTES];

        // Verify that the inputs are well-formed as byte-limbed BigInts.
        // This would indicate a problem with the circuit, so we panic here.
        for ai in a.iter().copied() {
            if ai > 255 {
                panic!("bigint quotient: input a is not well-formed");
            }
        }
        for bi in b.iter().copied() {
            if bi > 255 {
                panic!("bigint quotient: input b is not well-formed");
            }
        }

        // Determine n, the width of the denominator, and check for divide by zero.
        let mut n = bigint::WIDTH_BYTES;
        while n > 0 && b[n - 1] == 0 {
            n -= 1;
        }
        if n == 0 {
            // Divide by zero is strictly undefined, but the BigInt multiplier circuit uses
            // a modulus of zero as a special case to support "checked multiply"
            // of up to 256-bits. Return zero here to facilitate this.
            outs.copy_from_slice(&[Elem::ZERO; bigint::WIDTH_BYTES]);
            return Ok(());
        }
        if n < 2 {
            // FIXME: This routine should be updated to lift this restriction.
            anyhow::bail!("bigint quotient: denominator must be at least 9 bits");
        }
        let m = a.len() - n - 1;

        // Shift (i.e. multiply by two) the inputs until the leading bit is 1.
        let mut shift_bits = 0u64;
        while (b[n - 1] & (0x80 >> shift_bits)) == 0 {
            shift_bits += 1;
        }
        let mut carry = 0u64;
        for x in b.iter_mut().take(n) {
            let tmp = (*x << shift_bits) + carry;
            *x = tmp & 0xFF;
            carry = tmp >> 8;
        }
        if carry != 0 {
            panic!("bigint quotient: final carry in input shift");
        }
        for i in 0..(a.len() - 1) {
            let tmp = (a[i] << shift_bits) + carry;
            a[i] = tmp & 0xFF;
            carry = tmp >> 8;
        }
        a[a.len() - 1] = carry;

        for i in (0..=m).rev() {
            // Approximate how many multiples of b can be subtracted. May overestimate by up
            // to one.
            let mut q_approx = cmp::min(((a[i + n] << 8) + a[i + n - 1]) / b[n - 1], 255);
            while (q_approx * ((b[n - 1] << 8) + b[n - 2]))
                > ((a[i + n] << 16) + (a[i + n - 1] << 8) + a[i + n - 2])
            {
                q_approx -= 1;
            }

            // Subtract from `a` multiples of the denominator.
            let mut borrow = 0u64;
            for j in 0..=n {
                let sub = q_approx * b[j] + borrow;
                if a[i + j] < (sub & 0xFF) {
                    a[i + j] += 0x100 - (sub & 0xFF);
                    borrow = (sub >> 8) + 1;
                } else {
                    a[i + j] -= sub & 0xFF;
                    borrow = sub >> 8;
                }
            }
            if borrow > 0 {
                // Oops, went negative. Add back one multiple of b.
                q_approx -= 1;
                let mut carry = 0u64;
                for j in 0..=n {
                    let tmp = a[i + j] + b[j] + carry;
                    a[i + j] = tmp & 0xFF;
                    carry = tmp >> 8;
                }
                // Adding back one multiple of b should go from negative back to positive.
                if borrow - carry != 0 {
                    panic!("bigint quotient: underflow in bigint division");
                }
            }

            if i < q.len() {
                q[i] = q_approx;
            } else if q_approx != 0 {
                anyhow::bail!("bigint quotient: quotient exceeds allowed size");
            }
        }

        // Write q into output array, converting back to field representation.
        let mut q_elems = [Elem::ZERO; bigint::WIDTH_BYTES];
        for i in 0..bigint::WIDTH_BYTES {
            q_elems[i] = q[i].into();
        }
        outs.copy_from_slice(&q_elems);
        Ok(())
    }

    fn log(&self, msg: &str, args: &[Elem]) -> Result<()> {
        // Don't bother to format it if we're not even logging.
        if tracing::level_filters::LevelFilter::current()
            .eq(&tracing::level_filters::LevelFilter::OFF)
        {
            return Ok(());
        }

        // "msg" is given to us in C++-style formatting, so interpret it.
        let re = regex!("%([0-9]*)([xudw%])");
        let mut args_left = args;
        let mut next_arg = || {
            if args_left.is_empty() {
                panic!("Log arg mismatch, msg {msg}");
            }
            let arg: u32 = args_left[0].into();
            args_left = &args_left[1..];
            arg
        };
        let formatted = re.replace_all(msg, |captures: &Captures| {
            let width = captures
                .get(1)
                .map_or(0, |x| x.as_str().parse::<usize>().unwrap_or(0));
            let format = captures.get(2).map_or("", |x| x.as_str());
            match format {
                "u" => format!("{:width$}", next_arg()),
                "x" => {
                    let width = width.saturating_sub(2);
                    format!("0x{:0width$x}", next_arg())
                }
                "d" => format!("{:width$}", next_arg() as i32),
                "%" => "%".to_string(),
                "w" => {
                    let nexts = [next_arg(), next_arg(), next_arg(), next_arg()];
                    if nexts.iter().all(|v| *v <= 255) {
                        format!(
                            "0x{:08X}",
                            nexts[0] | (nexts[1] << 8) | (nexts[2] << 16) | (nexts[3] << 24)
                        )
                    } else {
                        format!(
                            "0x{:X}, 0x{:X}, 0x{:X}, 0x{:X}",
                            nexts[0], nexts[1], nexts[2], nexts[3]
                        )
                    }
                }
                _ => panic!("Unhandled printf format specification '{format}'"),
            }
        });
        assert_eq!(
            args_left.len(),
            0,
            "Args missing formatting: {:?} in {msg}",
            args_left
        );
        tracing::trace!("{}", formatted); // here
        Ok(())
    }

    fn syscall_body(&self, cycle: usize, outs: &mut [Elem]) -> Result<()> {
        let (stage, offset) = self.get_stage_offset(cycle);
        let cur_cycle = &stage.cycles[cycle - offset];
        ensure!(cur_cycle.mux == TopMux::Body(Major::ECallCopyIn, 0));
        let extra_idx = cur_cycle.extra_idx.fetch_add(1, Ordering::Relaxed);
        let word = stage.extras[extra_idx];
        // tracing::debug!("[{cycle}] syscall_body(0x{word:08x}), {cur_cycle:?}");
        Quad(outs[0], outs[1], outs[2], outs[3]) = word.into();
        Ok(())
    }

    fn syscall_fini(&self, cycle: usize, outs: &mut [Elem]) -> Result<()> {
        let (stage, offset) = self.get_stage_offset(cycle);
        let cur_cycle = &stage.cycles[cycle - offset];
        ensure!(cur_cycle.mux == TopMux::Body(Major::ECallCopyIn, 1));
        let extra_idx = cur_cycle.extra_idx.load(Ordering::Relaxed);
        let a0 = stage.extras[extra_idx + 0];
        let a1 = stage.extras[extra_idx + 1];
        // tracing::debug!("[{cycle}] syscall_fini(0x{a0:08x}, 0x{a1:08x}), {cur_cycle:?}");
        Quad(outs[0], outs[1], outs[2], outs[3]) = a0.into();
        Quad(outs[4], outs[5], outs[6], outs[7]) = a1.into();
        Ok(())
    }
}
