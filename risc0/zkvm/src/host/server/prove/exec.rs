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

use core::cmp;
use std::collections::{BTreeMap, BTreeSet, VecDeque};

use anyhow::{anyhow, Result};
use lazy_regex::{regex, Captures};
use risc0_binfmt::MemoryImage;
use risc0_core::field::{
    baby_bear::{BabyBear, BabyBearElem as Elem},
    Elem as _,
};
use risc0_zkp::adapter::CircuitStepHandler;
use risc0_zkvm_platform::{
    memory::SYSTEM,
    syscall::{
        bigint, ecall, halt,
        reg_abi::{REG_A0, REG_T0},
    },
    WORD_SIZE,
};

use super::plonk;
use crate::{
    host::server::{
        opcode::{MajorType, OpCode},
        session::PageFaults,
    },
    Segment,
};

type Quad = (Elem, Elem, Elem, Elem);

#[allow(dead_code)]
#[derive(Copy, Clone, Debug)]
enum MemoryOp {
    PageIo,
    Read,
    Write,
}

impl MemoryOp {
    fn as_u32(&self) -> u32 {
        *self as u32
    }
}

pub struct MemoryState {
    pub ram: MemoryImage,

    // Plonk tables for sorting plonks in proper order
    pub ram_plonk: plonk::RamPlonk,
    pub bytes_plonk: plonk::BytesPlonk,

    // Plonk accumulations for compute_accum and verify_accum phases
    pub plonk_accum: BTreeMap<String, plonk::PlonkAccum<BabyBear>>,
}

impl MemoryState {
    pub(crate) fn new(image: MemoryImage) -> Self {
        Self {
            ram: image,
            ram_plonk: plonk::RamPlonk::new(),
            bytes_plonk: plonk::BytesPlonk::new(),
            plonk_accum: BTreeMap::new(),
        }
    }

    #[track_caller]
    fn load_u32(&self, addr: u32) -> u32 {
        // log::debug!("load_u32: 0x{addr:08X}");
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned load");
        let mut bytes = [0u8; WORD_SIZE];
        self.ram.load_region_in_page(addr, &mut bytes);
        u32::from_le_bytes(bytes)
    }

    fn load_register(&self, idx: usize) -> u32 {
        self.load_u32(get_register_addr(idx))
    }

    #[track_caller]
    fn store_u8(&mut self, addr: u32, value: u8) {
        // log::debug!("store_u8: 0x{addr:08X} <= 0x{value:08X}");
        self.ram.store_region_in_page(addr, &[value]);
    }

    #[track_caller]
    fn store_region(&mut self, addr: u32, slice: &[u8]) {
        // log::trace!("store_region: 0x{addr:08X} <= {} bytes", slice.len());
        for (i, byte) in slice.iter().enumerate() {
            self.store_u8(addr + i as u32, *byte);
        }
    }

    #[track_caller]
    fn store_u32(&mut self, addr: u32, value: u32) {
        // log::debug!("store_u32: 0x{addr:08X} <= 0x{value:08X}");
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned store");
        self.store_region(addr, &value.to_le_bytes());
    }
}

fn get_register_addr(idx: usize) -> u32 {
    (SYSTEM.start() + idx * WORD_SIZE) as u32
}

fn split_word8(value: u32) -> Quad {
    (
        Elem::new(value & 0xff),
        Elem::new(value >> 8 & 0xff),
        Elem::new(value >> 16 & 0xff),
        Elem::new(value >> 24 & 0xff),
    )
}

fn merge_word8((x0, x1, x2, x3): Quad) -> u32 {
    let x0: u32 = x0.into();
    let x1: u32 = x1.into();
    let x2: u32 = x2.into();
    let x3: u32 = x3.into();
    x0 | x1 << 8 | x2 << 16 | x3 << 24
}

pub struct MachineContext {
    memory: MemoryState,
    faults: PageFaults,
    syscall_out_data: VecDeque<u32>,
    syscall_out_regs: VecDeque<(u32, u32)>,

    is_halted: bool,

    // When the machine is in a flushing state, no new dirty pages will be recorded and the
    // next dirty page will be reported in a 'pageInfo' extern.
    is_flushing: bool,

    // This is just for diagnostics: tracks which words have been paged in.
    resident_words: BTreeSet<u32>,

    split_insn: Option<u32>,

    insn_counter: u32,
}

impl CircuitStepHandler<Elem> for MachineContext {
    fn call(
        &mut self,
        cycle: usize,
        name: &str,
        extra: &str,
        args: &[Elem],
        outs: &mut [Elem],
    ) -> Result<()> {
        match name {
            "halt" => {
                self.halt(cycle, args[0], args[1]);
                Ok(())
            }
            "trace" => Ok(()),
            "getMajor" => {
                outs[0] = self.get_major(args[0], args[1])?;
                Ok(())
            }
            "getMinor" => {
                let insn = merge_word8((args[0], args[1], args[2], args[3]));
                let opcode = OpCode::decode(insn, 0)?;
                outs[0] = opcode.minor.into();
                Ok(())
            }
            "divide" => {
                (
                    (outs[0], outs[1], outs[2], outs[3]),
                    (outs[4], outs[5], outs[6], outs[7]),
                ) = self.divide(
                    (args[0], args[1], args[2], args[3]),
                    (args[4], args[5], args[6], args[7]),
                    args[8],
                );
                Ok(())
            }
            "bigintQuotient" => {
                let (a, b) = args.split_at(bigint::WIDTH_BYTES * 2);
                let q = self.bigint_quotient(a.try_into()?, b.try_into()?)?;
                outs.copy_from_slice(&q[..]);
                Ok(())
            }
            "pageInfo" => {
                (outs[0], outs[1], outs[2]) = self.page_info(cycle);
                Ok(())
            }
            "ramWrite" => {
                self.ram_write(args[0], (args[1], args[2], args[3], args[4]), args[5])?;
                Ok(())
            }
            "ramRead" => {
                (outs[0], outs[1], outs[2], outs[3]) = self.ram_read(cycle, args[0], args[1]);
                Ok(())
            }
            "plonkWrite" => {
                self.plonk_write(extra, args);
                Ok(())
            }
            "plonkRead" => {
                self.plonk_read(extra, outs);
                Ok(())
            }
            "plonkWriteAccum" => {
                self.plonk_write_accum(extra, args);
                Ok(())
            }
            "plonkReadAccum" => {
                self.plonk_read_accum(extra, outs);
                Ok(())
            }
            "log" => {
                self.log(extra, args);
                Ok(())
            }
            "syscallInit" => Ok(()),
            "syscallBody" => {
                (outs[0], outs[1], outs[2], outs[3]) = split_word8(self.syscall_body()?);
                Ok(())
            }
            "syscallFini" => {
                let (a0, a1) = self.syscall_fini()?;
                (outs[0], outs[1], outs[2], outs[3]) = split_word8(a0);
                (outs[4], outs[5], outs[6], outs[7]) = split_word8(a1);
                Ok(())
            }
            _ => unimplemented!("Unsupported extern: {name}"),
        }
    }

    #[tracing::instrument(skip(self))]
    fn sort(&mut self, _: &str) {
        self.memory.ram_plonk.sort();
        self.memory.bytes_plonk.sort();
    }
}

impl MachineContext {
    pub fn new(segment: &Segment) -> Self {
        let syscall_out_data: Vec<u32> = segment
            .syscalls
            .iter()
            .flat_map(|syscall| syscall.to_guest.clone())
            .collect();
        let syscall_out_regs: Vec<(u32, u32)> = segment
            .syscalls
            .iter()
            .map(|syscall| syscall.regs)
            .collect();
        MachineContext {
            memory: MemoryState::new(segment.pre_image.clone()),
            faults: segment.faults.clone(),
            syscall_out_data: VecDeque::from(syscall_out_data),
            syscall_out_regs: VecDeque::from(syscall_out_regs),
            is_halted: false,
            is_flushing: false,
            resident_words: BTreeSet::new(),
            split_insn: segment.split_insn,
            insn_counter: 0,
        }
    }

    fn halt(&mut self, cycle: usize, exit_code: Elem, pc: Elem) {
        if !self.is_halted {
            let exit_code = exit_code.into();
            let pc: u32 = pc.into();
            match exit_code {
                halt::TERMINATE => {
                    log::info!("HALT[{cycle}]> pc: 0x{pc:08x}");
                }
                halt::PAUSE => {
                    log::info!("PAUSE[{cycle}]> pc: 0x{pc:08x}");
                    self.is_flushing = true;
                }
                halt::SPLIT => {
                    log::info!("SPLIT[{cycle}]> pc: 0x{pc:08x}");
                }
                _ => unimplemented!("Unsupported exit_code: {exit_code}"),
            }
            self.is_halted = true;
        }
    }

    fn get_major(&mut self, cycle: Elem, pc: Elem) -> Result<Elem> {
        let cycle: u32 = cycle.into();
        let pc: u32 = pc.into();
        let insn = self.memory.load_u32(pc);
        let opcode = OpCode::decode(insn, pc)?;

        if opcode.major == MajorType::ECall {
            let minor = self.memory.load_register(REG_T0);
            if minor == ecall::HALT {
                let mode = self.memory.load_register(REG_A0);
                if mode == halt::PAUSE {
                    log::debug!("sys_pause[{cycle}]> pc: 0x{pc:08x}");
                    if self.faults.writes.is_empty() {
                        self.is_flushing = false;
                    } else {
                        self.is_flushing = true;
                    }
                }
            }
        }

        if let Some(split_insn) = self.split_insn {
            if self.insn_counter == split_insn && !self.is_flushing {
                log::info!("FLUSH[{}]> pc: 0x{pc:08x}", self.insn_counter);
                self.is_flushing = true;
            }
        }

        if !self.faults.reads.is_empty() {
            return Ok(MajorType::PageFault.as_u32().into());
        }

        if self.is_flushing {
            return Ok(MajorType::PageFault.as_u32().into());
        }

        log::trace!(
            "[{}] pc: 0x{:08x}, insn: 0x{:08x} => {:?}",
            cycle,
            pc,
            insn,
            opcode
        );
        self.insn_counter += 1;

        Ok(opcode.major.as_u32().into())
    }

    fn page_info(&mut self, cycle: usize) -> (Elem, Elem, Elem) {
        if let Some(page_idx) = self.faults.reads.pop_last() {
            log::debug!("[{cycle}] page_read: 0x{page_idx:08x}");
            return (Elem::ONE, page_idx.into(), Elem::ZERO);
        }

        if self.is_flushing {
            if let Some(page_idx) = self.faults.writes.pop_first() {
                log::debug!("[{cycle}] page_write: 0x{page_idx:08x}");
                return (Elem::ZERO, page_idx.into(), Elem::ZERO);
            }
        }

        (Elem::ZERO, Elem::ZERO, Elem::ONE)
    }

    fn divide(&self, numer: Quad, denom: Quad, sign: Elem) -> (Quad, Quad) {
        let mut numer = merge_word8(numer);
        let mut denom = merge_word8(denom);
        let sign: u32 = sign.into();
        // log::debug!("divide: [{sign}] {numer} / {denom}");
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
        // log::debug!("  quot: {quot}, rem: {rem}");
        (split_word8(quot), split_word8(rem))
    }

    /// Division of two positive byte-limbed bigints. a = q * b + r.
    ///
    /// Assumes a and b are both normalized with limbs in range [0, 255].
    /// Returns q as an array of BabyBearElems. (Drops r).
    ///     When the denominator is zero, returns zero to facilitate use of the
    ///     BigInt modular multiply circuit as an unreduced "checked
    ///     multiply" circuit.
    /// Returns an error when:
    /// * Input denominator b is 0.
    /// * Input denominator b is less than 9 bits.
    /// * Quotient result q is greater than [bigint::WIDTH_BYTES] limbs. This
    ///   will occur if the numerator `a` is the result of a multiplication of
    ///   values `x` and `y` such that `floor(x * y / b) >=
    ///   2^bigint::WIDTH_BITS`. If x and/or y is less than b (i.e. the modulus
    ///   in bigint modular multiply) this constrain will be satisfied.
    fn bigint_quotient(
        &self,
        a_elems: &[Elem; bigint::WIDTH_BYTES * 2],
        b_elems: &[Elem; bigint::WIDTH_BYTES],
    ) -> Result<[Elem; bigint::WIDTH_BYTES]> {
        // This is a variant of school-book multiplication.
        // Reference the Handbook of Elliptic and Hyper-elliptic Cryptography alg.
        // 10.5.1

        // Setup working buffers of u64 elements. We use u64 values here because this
        // implementation does a lot of non-field opperations and so we need to take the
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
            return Ok([Elem::ZERO; bigint::WIDTH_BYTES]);
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
        Ok(q_elems)
    }

    fn log(&mut self, msg: &str, args: &[Elem]) {
        if log::max_level() < log::LevelFilter::Trace {
            // Don't bother to format it if we're not even logging.
            return;
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
        log::trace!("{}", formatted);
    }

    fn ram_read(&mut self, cycle: usize, addr: Elem, op: Elem) -> Quad {
        let addr: u32 = addr.into();
        let op: u32 = op.into();
        let info = &self.memory.ram.info;
        if op == MemoryOp::PageIo.as_u32() {
            self.resident_words.insert(addr);
        } else if !self.resident_words.contains(&addr) {
            let addr = addr * WORD_SIZE as u32;
            let page_idx = info.get_page_index(addr);
            let entry_addr = info.get_page_entry_addr(page_idx);
            log::debug!("[{cycle}] ram_read: 0x{addr:08x}, op: {op:?}, entry_addr: 0x{entry_addr:08x}, page_idx: {page_idx}");
            panic!("Memory read before page in: 0x{addr:08x}");
        }

        let addr = addr * WORD_SIZE as u32;
        let word = self.memory.load_u32(addr);
        // log::debug!("ram_read: 0x{addr:08X} -> 0x{word:08X}");
        split_word8(word)
    }

    fn ram_write(&mut self, addr: Elem, data: Quad, op: Elem) -> Result<()> {
        let addr: u32 = addr.into();
        let op: u32 = op.into();
        if op == MemoryOp::PageIo.as_u32() {
            self.resident_words.insert(addr);
        } else {
            assert!(
                self.resident_words.contains(&addr),
                "Memory write before page in: 0x{addr:08x}"
            );
        }

        let data = merge_word8(data);
        let addr = addr * WORD_SIZE as u32;
        // log::debug!("ram_write> 0x{:08X} <= 0x{:08X}", addr, data);
        self.memory.store_u32(addr, data);

        Ok(())
    }

    fn plonk_read(&mut self, name: &str, outs: &mut [Elem]) {
        match name {
            "ram" => self.memory.ram_plonk.read(outs.try_into().unwrap()),
            "bytes" => self.memory.bytes_plonk.read(outs.try_into().unwrap()),
            _ => panic!("Unknown plonk type {name}"),
        }
    }

    fn plonk_write(&mut self, name: &str, args: &[Elem]) {
        match name {
            "ram" => self.memory.ram_plonk.write(args.try_into().unwrap()),
            "bytes" => self.memory.bytes_plonk.write(args.try_into().unwrap()),
            _ => panic!("Unknown plonk type {name}"),
        }
    }

    fn plonk_read_accum(&mut self, name: &str, outs: &mut [Elem]) {
        if let Some(entry) = self.memory.plonk_accum.get_mut(name) {
            entry.read(outs)
        } else {
            panic!("Unknown plonk accum {}", name);
        }
    }

    fn plonk_write_accum(&mut self, name: &str, args: &[Elem]) {
        if let Some(entry) = self.memory.plonk_accum.get_mut(name) {
            entry.write(args);
        } else {
            let mut accum = plonk::PlonkAccum::new();
            accum.write(args);
            self.memory.plonk_accum.insert(name.to_string(), accum);
        }
    }

    fn syscall_body(&mut self) -> Result<u32> {
        Ok(self.syscall_out_data.pop_front().unwrap_or_default())
    }

    fn syscall_fini(&mut self) -> Result<(u32, u32)> {
        let syscall_out_regs = self
            .syscall_out_regs
            .pop_front()
            .ok_or(anyhow!("Invalid syscall records"))?;
        log::trace!("syscall_fini: {:?}", syscall_out_regs);
        Ok(syscall_out_regs)
    }
}
