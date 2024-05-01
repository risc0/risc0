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

use std::collections::{BTreeMap, VecDeque};

use anyhow::Result;
use lazy_regex::{regex, Captures};
use rayon::prelude::*;
use risc0_circuit_recursion::{CircuitImpl, Externs};
use risc0_zkp::{
    adapter::{CircuitInfo, CircuitStep, CircuitStepContext, CircuitStepHandler},
    field::{
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
        Elem, ExtElem,
    },
    hal::cpu::SyncSlice,
    prove::executor::Executor,
    ZK_CYCLES,
};

use super::{plonk, Program, CIRCUIT, RECURSION_PO2};

pub struct MachineContext {
    // Contents of the write-only memory
    wom: Vec<BabyBearExtElem>,

    // Plonk table for sorting plonk elements in proper order
    wom_plonk: plonk::WomPlonk,

    // Plonk accumulations for compute_accum and verify_accum phases
    plonk_accum: plonk::PlonkAccum<BabyBear>,

    iop_input: VecDeque<u32>,
    cur_iop_body: VecDeque<Vec<BabyBearElem>>,

    pub iop_reads: BTreeMap<usize, Vec<BabyBearExtElem>>,
}

impl MachineContext {
    pub fn new(iop_input: VecDeque<u32>) -> Self {
        MachineContext {
            wom: Vec::new(),
            iop_input,
            cur_iop_body: VecDeque::new(),
            plonk_accum: plonk::PlonkAccum::new(),
            wom_plonk: plonk::WomPlonk::new(),
            iop_reads: BTreeMap::new(),
        }
    }

    fn plonk_read(&mut self, name: &str, outs: &mut [BabyBearElem]) {
        match name {
            "wom" => self.wom_plonk.read(outs.try_into().unwrap()),
            _ => panic!("Unknown plonk type {name}"),
        }
    }

    fn plonk_write(&mut self, name: &str, args: &[BabyBearElem]) {
        match name {
            "wom" => self.wom_plonk.write(args.try_into().unwrap()),
            _ => panic!("Unknown plonk type {name}"),
        }
    }

    fn plonk_read_accum(&mut self, name: &str, outs: &mut [BabyBearElem]) {
        assert_eq!(name, "wom");
        self.plonk_accum.read(outs)
    }

    fn plonk_write_accum(&mut self, name: &str, args: &[BabyBearElem]) {
        assert_eq!(name, "wom");
        self.plonk_accum.write(args);
    }

    fn log(&mut self, msg: &str, args: &[BabyBearElem]) {
        // Don't bother to format it if we're not even logging.
        if tracing::level_filters::LevelFilter::current()
            .eq(&tracing::level_filters::LevelFilter::OFF)
        {
            return;
        }

        // "msg" is given to us in C++-style formatting, so interpret it.
        let re = regex!("%([0-9]*)([xudwe%])");
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
                "x" => format!("{:0width$x}", next_arg()),
                "d" => format!("{:width$}", next_arg() as i32),
                "%" => "%".to_string(),
                "w" | "e" => {
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
        tracing::trace!("{}", formatted);
    }
}

impl risc0_circuit_recursion::Externs for MachineContext {
    fn wom_write(&mut self, addr: BabyBearElem, val: BabyBearExtElem) {
        let addr = u32::from(addr) as usize;

        // assert_eq!(addr, self.wom.len());
        if self.wom.len() <= addr {
            self.wom.resize(addr + 1, BabyBearExtElem::ZERO);
        }
        let mem_contents = &mut self.wom[addr];
        if *mem_contents != BabyBearExtElem::ZERO && *mem_contents != val {
            panic!("Wom {addr} overwritten with {val:?} from {mem_contents:?}");
        }
        self.wom[addr] = val;
    }

    fn wom_read(&self, addr: BabyBearElem) -> BabyBearExtElem {
        self.wom[u32::from(addr) as usize]
    }

    fn read_iop_header(&mut self, count: BabyBearElem, k_and_flip_flag: BabyBearElem) {
        let count = u32::from(count) as usize;
        let kf = u32::from(k_and_flip_flag);
        let k = kf as usize / 2;
        let flip: bool = (kf & 1) == 1;

        assert!(self.cur_iop_body.is_empty());
        if k != 2 {
            let arr: Vec<u32> = self.iop_input.drain(..k * count).collect();
            for i in 0..count {
                let poly: Vec<BabyBearElem> = (0..k)
                    .map(|j| {
                        BabyBearElem::new_raw(if flip {
                            arr[i * k + j]
                        } else {
                            arr[j * count + i]
                        })
                    })
                    .collect();
                self.cur_iop_body.push_back(poly);
            }
        } else {
            self.cur_iop_body
                .extend(self.iop_input.drain(..count).map(|elem| {
                    Vec::from([
                        BabyBearElem::from(elem & 0xffff),
                        BabyBearElem::from(elem >> 16),
                    ])
                }));
        }
    }

    fn read_iop_body(&mut self, do_mont: BabyBearElem) -> BabyBearExtElem {
        let mut front = self.cur_iop_body.pop_front().unwrap();
        front.resize(4, BabyBearElem::from(0u32));
        if do_mont != BabyBearElem::ZERO {
            for elem in front.iter_mut().take(4) {
                *elem *= BabyBearElem::from(268435454u32);
            }
        }
        BabyBearExtElem::from_subelems(front)
    }
}

impl CircuitStepHandler<BabyBearElem> for MachineContext {
    fn call(
        &mut self,
        _cycle: usize,
        name: &str,
        extra: &str,
        args: &[BabyBearElem],
        outs: &mut [BabyBearElem],
    ) -> Result<()> {
        match name {
            "readIOPHeader" => {
                self.read_iop_header(args[0], args[1]);
                Ok(())
            }
            "readIOPBody" => {
                outs.clone_from_slice(self.read_iop_body(args[2]).subelems());
                Ok(())
            }
            "womRead" => {
                outs.clone_from_slice(self.wom_read(args[0]).subelems());
                Ok(())
            }
            "womWrite" => {
                let val = BabyBearExtElem::from_subelems(args[1..5].iter().cloned());
                self.wom_write(args[0], val);
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
            _ => unimplemented!("Unsupported extern: {name}"),
        }
    }

    #[tracing::instrument(skip(self))]
    fn sort(&mut self, _: &str) {
        self.wom_plonk.sort();
    }
}

pub struct RecursionExecutor<'a> {
    zkr: &'a Program,
    pub executor: Executor<BabyBear, CircuitImpl, MachineContext>,
    split_points: Vec<usize>,
}

impl<'a> RecursionExecutor<'a> {
    pub fn new(
        circuit: &'static CircuitImpl,
        zkr: &'a Program,
        machine: MachineContext,
        split_points: Vec<usize>,
    ) -> Self {
        let io = vec![BabyBearElem::INVALID; CircuitImpl::OUTPUT_SIZE];
        let po2 = RECURSION_PO2;
        let executor = Executor::new(circuit, machine, po2, &io);
        Self {
            zkr,
            executor,
            split_points,
        }
    }

    #[tracing::instrument(skip_all)]
    pub fn run(&mut self) -> Result<usize> {
        let used_cycles = self.zkr.code_rows();
        tracing::trace!(
            "Starting recursion code of length {}/{}",
            used_cycles,
            self.executor.steps
        );
        assert!(used_cycles < self.executor.steps);

        tracing::info_span!("step_exec").in_scope(|| -> Result<()> {
            let code = self.executor.code.as_slice_sync();
            let io = self.executor.io.as_slice_sync();
            let data = self.executor.data.as_slice_sync();
            let args = &[code, io, data];

            let wom_plonk_elems: Vec<Vec<[BabyBearElem; 5]>> = self
                .split_points
                .as_slice()
                .par_iter()
                .panic_fuse()
                .cloned()
                .zip((self.split_points[1..]).par_iter().cloned())
                .fold(
                    || {
                        ParallelHandler::new(
                            self.zkr,
                            args,
                            self.executor.steps,
                            self.executor.handler.wom.as_slice(),
                            &self.executor.handler.iop_reads,
                        )
                    },
                    |handler, (start, end)| handler.run_chunk(start, end),
                )
                .map(|handler| handler.into_wom_plonks())
                .collect();
            // TODO: Ugh, there has to be a better way to get at the handler.
            for elem in wom_plonk_elems.into_iter().flatten() {
                self.executor
                    .handler
                    .call(0, "plonkWrite", "wom", elem.as_slice(), &mut [])?;
            }
            Ok(())
        })?;
        self.executor.cycle = self.executor.steps - ZK_CYCLES;
        self.executor.halted = true;
        self.executor.finalize();
        Ok(self.executor.steps)
    }
}

struct ParallelHandler<'a> {
    program: &'a Program,
    tot_cycles: usize,
    args: &'a [SyncSlice<'a, BabyBearElem>],
    wom: &'a [BabyBearExtElem],
    plonk_queue: Vec<[BabyBearElem; 5]>,
    iop_reads: &'a BTreeMap<usize, Vec<BabyBearExtElem>>,
    cur_iop_body: Option<&'a [BabyBearExtElem]>,
}

impl<'a> ParallelHandler<'a> {
    fn new(
        program: &'a Program,
        args: &'a [SyncSlice<'a, BabyBearElem>],
        tot_cycles: usize,
        wom: &'a [BabyBearExtElem],
        iop_reads: &'a BTreeMap<usize, Vec<BabyBearExtElem>>,
    ) -> Self {
        ParallelHandler {
            program,
            tot_cycles,
            args,
            wom,
            iop_reads,

            plonk_queue: Vec::new(),
            cur_iop_body: None,
        }
    }

    fn into_wom_plonks(self) -> Vec<[BabyBearElem; 5]> {
        self.plonk_queue
    }

    fn run_chunk(mut self, begin: usize, end: usize) -> Self {
        // fill in code buffer
        for row in begin..end {
            if row >= self.program.code_rows() {
                break;
            }
            for idx in 0..self.program.code_size {
                self.args[0].set(
                    idx * self.tot_cycles + row,
                    self.program.code[row * self.program.code_size + idx],
                );
            }
        }

        // Run the step
        let args = self.args;
        for row in begin..end {
            self.cur_iop_body = None;
            let ctx = CircuitStepContext {
                size: 1 << RECURSION_PO2,
                cycle: row,
            };
            CIRCUIT.step_exec(&ctx, &mut self, args).unwrap();
        }
        self
    }

    fn log(&mut self, msg: &str, args: &[BabyBearElem]) {
        // Don't bother to format it if we're not even logging.
        if tracing::level_filters::LevelFilter::current()
            .eq(&tracing::level_filters::LevelFilter::OFF)
        {
            return;
        }

        // "msg" is given to us in C++-style formatting, so interpret it.
        let re = regex!("%([0-9]*)([xudwe%])");
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
                "x" => format!("{:0width$x}", next_arg()),
                "d" => format!("{:width$}", next_arg() as i32),
                "%" => "%".to_string(),
                "w" | "e" => {
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
        tracing::trace!("{}", formatted);
    }
}

impl<'a> CircuitStepHandler<BabyBearElem> for ParallelHandler<'a> {
    fn sort(&mut self, _: &str) {
        todo!()
    }

    fn call(
        &mut self,
        cycle: usize,
        name: &str,
        extra: &str,
        args: &[BabyBearElem],
        outs: &mut [BabyBearElem],
    ) -> Result<()> {
        match name {
            "log" => {
                self.log(extra, args);
                Ok(())
            }
            "womWrite" => {
                // let addr = u32::from(args[0]) as usize;
                // let val = BabyBearExtElem::from_subelems(args[1..5].into_iter().cloned());
                // let goal = self.wom[addr];
                // tracing::debug!("Cycle = {}, addr = {}, attempting to write = {:?}, should write
                // = {:?}", cycle, addr, val, goal);
                // TODO, but harmless
                Ok(())
            }
            "plonkWrite" => {
                self.plonk_queue.push(args.try_into().unwrap());
                Ok(())
            }
            "womRead" => {
                outs.clone_from_slice(self.wom[u32::from(args[0]) as usize].subelems());
                Ok(())
            }
            "readIOPHeader" => {
                // Nothing to do here; we've already precomputed.
                Ok(())
            }
            "readIOPBody" => {
                if self.cur_iop_body.is_none() {
                    self.cur_iop_body = Some(self.iop_reads.get(&cycle).unwrap().as_slice());
                }
                let cur_body = self.cur_iop_body.unwrap();
                outs.clone_from_slice(cur_body[0].subelems());
                self.cur_iop_body = Some(&cur_body[1..]);
                Ok(())
            }
            _ => panic!("Unimplemented extern {name}"),
        }
    }
}
