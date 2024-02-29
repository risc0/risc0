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

use std::fmt;

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
pub struct RamArgumentRow {
    #[dbg(fmt = "0x{:08x}")]
    addr: u32,
    cyclop: Cyclop,
    #[dbg(fmt = "0x{:08x}")]
    word: u32,
}

#[derive(Default)]
pub struct RamArgument {
    queue: SegQueue<RamArgumentRow>,
    sorted: Vec<RamArgumentRow>,
    idx: usize,
}

// Argument for bytes.
//
// Rows each have 2 byte elements, each of which is in [0, 256). We construct
// these into a short, [0, 256*256), and count how many of each row occurs.
pub struct BytesArgument {
    counts: Box<[u32; 256 * 256]>,
    read_pos: usize,
}

impl RamArgument {
    pub fn write(&self, args: &[BabyBearElem]) {
        let addr: u32 = args[0].into();
        let cycle: u32 = args[1].into();
        let mem_op: u32 = args[2].into();
        let cyclop = Cyclop::new(cycle, mem_op);
        let word = Quad(args[3], args[4], args[5], args[6]).into();
        let row = RamArgumentRow { addr, cyclop, word };
        // tracing::debug!("arg_write(ram): {row:?}");
        self.queue.push(row);
    }

    pub fn sort(&mut self) {
        while !self.queue.is_empty() {
            self.sorted.push(self.queue.pop().unwrap());
        }
        self.sorted.sort();
    }

    pub fn read(&mut self, out: &mut [BabyBearElem]) {
        let idx = self.idx;
        self.idx += 1;
        // let idx = self.idx.fetch_add(1, Ordering::Relaxed);
        let row = self.sorted.get(idx).unwrap();
        // tracing::debug!("arg_read(ram): {row:?}");
        out[0] = row.addr.into();
        out[1] = row.cyclop.cycle().into();
        out[2] = row.cyclop.mem_op().into();
        Quad(out[3], out[4], out[5], out[6]) = row.word.into();
    }
}

impl BytesArgument {
    pub fn new() -> Self {
        BytesArgument {
            counts: Box::new([0; 256 * 256]),
            read_pos: 0,
        }
    }

    pub fn write(&mut self, args: &[BabyBearElem]) {
        let idx: u32 = Twin(args[0], args[1]).into();
        // tracing::debug!("arg_write(bytes): {idx}");
        self.counts[idx as usize] += 1;
    }

    pub fn sort(&mut self) {
        // BytesArgument is already sorted.
    }

    pub fn read(&mut self, outs: &mut [BabyBearElem]) {
        while self.counts[self.read_pos] == 0 {
            self.read_pos += 1;
        }
        // tracing::debug!("arg_read(bytes): {}", self.read_pos);
        let read_pos = self.read_pos as u32;
        self.counts[self.read_pos] -= 1;
        Twin(outs[0], outs[1]) = read_pos.into();
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
