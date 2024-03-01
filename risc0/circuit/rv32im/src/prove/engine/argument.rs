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

#![allow(unused)]

use std::{
    fmt,
    sync::{
        atomic::{AtomicU32, AtomicUsize, Ordering},
        Mutex,
    },
};

use crossbeam::queue::SegQueue;
use derive_debug::Dbg;
use risc0_zkp::field::baby_bear::BabyBearElem;

use super::{Quad, Twin};

// (cycle << 2) | mem_op
#[derive(Ord, PartialOrd, Eq, PartialEq)]
struct Cyclop(u32);

// Main RAM argument rows have the following 7 elements:
// addr, cycle, isWrite, byte0, byte1, byte2, byte3
#[derive(Dbg, Ord, PartialOrd, Eq, PartialEq)]
struct RamArgumentRow {
    #[dbg(fmt = "0x{:08x}")]
    addr: u32,
    cyclop: Cyclop,
    #[dbg(fmt = "0x{:08x}")]
    word: u32,
}

pub struct RamArgument {
    queue: SegQueue<RamArgumentRow>,
    sorted: Vec<RamArgumentRow>,
    // index: Vec<AtomicUsize>,
    // idx: AtomicUsize,
    idx: usize,
}

impl RamArgument {
    pub fn new(steps: usize) -> Self {
        // let index = (0..steps).map(|_| AtomicUsize::new(0)).collect();
        Self {
            queue: SegQueue::default(),
            sorted: Vec::default(),
            // index,
            // idx: AtomicUsize::new(0),
            idx: 0,
        }
    }

    pub fn write(&self, cycle: usize, args: &[BabyBearElem]) {
        let addr: u32 = args[0].into();
        let mem_cycle: u32 = args[1].into();
        let mem_op: u32 = args[2].into();
        let cyclop = Cyclop::new(mem_cycle, mem_op);
        let word = Quad(args[3], args[4], args[5], args[6]).into();
        let row = RamArgumentRow { addr, cyclop, word };
        // tracing::debug!("[{cycle}] arg_write(ram): {row:?}");
        self.queue.push(row);
        // self.index
        //     .get(cycle)
        //     .unwrap()
        //     .fetch_add(1, Ordering::SeqCst);
    }

    pub fn sort(&mut self) {
        while !self.queue.is_empty() {
            self.sorted.push(self.queue.pop().unwrap());
        }
        self.sorted.sort();

        // let mut pos = 0;
        // for item in self.index.iter_mut() {
        //     let idx = pos;
        //     let count = item.load(Ordering::Relaxed);
        //     pos += count;
        //     item.store(idx, Ordering::Relaxed);
        // }
    }

    pub fn read(&mut self, cycle: usize, out: &mut [BabyBearElem]) {
        // let par_idx = self
        //     .index
        //     .get(cycle)
        //     .unwrap()
        //     .fetch_add(1, Ordering::SeqCst);

        // let idx = self.idx.fetch_add(1, Ordering::SeqCst);
        let idx = self.idx;
        self.idx += 1;

        // assert_eq!(par_idx, idx, "cycle: {cycle}");

        let row = self.sorted.get(idx).unwrap();
        // let row = self.sorted.get(par_idx).unwrap();
        // tracing::debug!("[{cycle}] arg_read(ram): {row:?}");
        out[0] = row.addr.into();
        out[1] = row.cyclop.cycle().into();
        out[2] = row.cyclop.mem_op().into();
        Quad(out[3], out[4], out[5], out[6]) = row.word.into();
    }
}

// Argument for bytes.
//
// Rows each have 2 byte elements, each of which is in [0, 256). We construct
// these into a short, [0, 256*256), and count how many of each row occurs.
pub struct BytesArgument {
    counts: Vec<AtomicU32>,
    index: Vec<AtomicUsize>,
    compact: Vec<u32>,
    // state: Mutex<BytesState>,
}

struct BytesState {
    counts: Box<[u32; 256 * 256]>,
    read_pos: usize,
}

impl BytesArgument {
    pub fn new(steps: usize) -> Self {
        let counts = (0..256 * 256).map(|_| AtomicU32::new(0)).collect();
        let index = (0..steps).map(|_| AtomicUsize::new(0)).collect();
        BytesArgument {
            // state: Mutex::new(BytesState {
            //     counts: Box::new([0; 256 * 256]),
            //     read_pos: 0,
            // }),
            counts,
            index,
            compact: Vec::new(),
        }
    }

    pub fn write(&self, cycle: usize, args: &[BabyBearElem]) {
        let idx: u32 = Twin(args[0], args[1]).into();
        // tracing::debug!("arg_write(bytes): {idx}");
        // self.state.lock().unwrap().counts[idx as usize] += 1;

        self.counts
            .get(idx as usize)
            .unwrap()
            .fetch_add(1, Ordering::Relaxed);
        self.index
            .get(cycle)
            .unwrap()
            .fetch_add(1, Ordering::Relaxed);
    }

    pub fn sort(&mut self) {
        for (byte, count) in self.counts.iter().enumerate() {
            let count = count.load(Ordering::Relaxed);
            if count > 0 {
                for i in (0..count).rev() {
                    self.compact.push(byte as u32);
                }
            }
        }
        tracing::debug!("bytes: {}", self.compact.len());

        let mut pos = 0;
        for item in self.index.iter_mut() {
            let idx = pos;
            let count = item.load(Ordering::Relaxed);
            pos += count;
            item.store(idx, Ordering::Relaxed);
        }
    }

    pub fn read(&self, cycle: usize, outs: &mut [BabyBearElem]) {
        let idx = self
            .index
            .get(cycle)
            .unwrap()
            .fetch_add(1, Ordering::Relaxed);

        let pos = *self.compact.get(idx).unwrap();
        Twin(outs[0], outs[1]) = pos.into();

        // let mut state = self.state.lock().unwrap();

        // while state.counts[state.read_pos] == 0 {
        //     state.read_pos += 1;
        // }
        // tracing::debug!("arg_read(bytes): {}", state.read_pos);
        // let read_pos = state.read_pos as u32;
        // state.counts[read_pos as usize] -= 1;
        // Twin(outs[0], outs[1]) = read_pos.into();

        // assert_eq!(pos, read_pos, "cycle: {cycle}");
    }
}

impl fmt::Debug for Cyclop {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "({}, {})", self.cycle(), self.mem_op())
    }
}

impl Cyclop {
    fn new(cycle: u32, mem_op: u32) -> Self {
        Self((cycle << 2) | mem_op)
    }

    fn cycle(&self) -> u32 {
        self.0 >> 2
    }

    fn mem_op(&self) -> u32 {
        self.0 & 0b11
    }
}
