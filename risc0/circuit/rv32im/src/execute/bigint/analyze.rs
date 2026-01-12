// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use anyhow::Result;
use byteorder::{LittleEndian, ReadBytesExt as _};

use std::collections::HashMap;

use crate::execute::{
    WORD_SIZE,
    bibc::{OpCode, Program},
    pager::{NODE_CYCLES, PAGE_CYCLES},
};

const PAGE_SIZE: u32 = 1024;

/// What is the maximum number of pages an IO of the given size can span?
fn max_pages_for_io(size: u32) -> u32 {
    if size == 0 {
        0
    } else if size == 1 {
        1
    } else {
        let p = size / PAGE_SIZE;
        match size % PAGE_SIZE {
            0 | 1 => 2 + (p - 1),
            _ => 2 + p,
        }
    }
}

#[test]
fn max_pages_for_io_test() {
    assert_eq!(max_pages_for_io(0), 0);
    assert_eq!(max_pages_for_io(1), 1);
    assert_eq!(max_pages_for_io(2), 2);

    assert_eq!(max_pages_for_io(1024), 2);
    assert_eq!(max_pages_for_io(1025), 2);
    assert_eq!(max_pages_for_io(1026), 3);
    assert_eq!(max_pages_for_io(1027), 3);

    assert_eq!(max_pages_for_io(1024 * 2), 3);
    assert_eq!(max_pages_for_io(1024 * 2 + 1), 3);
    assert_eq!(max_pages_for_io(1024 * 2 + 2), 4);
}

// Cost of updating the nodes in the tree all the way up to the root.
const FULL_TREE_NODE_COUNT: u32 = 21 * NODE_CYCLES;

struct IoCounter {
    cycles: u32,
    loaded_arenas: HashMap<u32, u32>,
    dirty_arenas: HashMap<u32, u32>,
}

impl IoCounter {
    fn new() -> Self {
        Self {
            cycles: 0,
            loaded_arenas: HashMap::new(),
            dirty_arenas: HashMap::new(),
        }
    }

    fn track_load_arena(&mut self, arena: u32, offset: u32, count: u32) {
        let mut page_in = false;

        let num_pages = self.loaded_arenas.entry(arena).or_insert(0);

        while *num_pages < max_pages_for_io(offset + count) {
            // load could go all the way up the tree
            self.cycles += PAGE_CYCLES;
            self.cycles += FULL_TREE_NODE_COUNT;
            page_in = true;
            *num_pages += 1;
        }

        println!("load_arena({arena}, {offset}, {count}), page_in = {page_in}");
    }

    fn track_store_arena(&mut self, arena: u32, offset: u32, count: u32) {
        let mut page_out = false;

        let num_pages = self.loaded_arenas.entry(arena).or_insert(0);

        while *num_pages < max_pages_for_io(offset + count) {
            // load could go all the way up the tree
            self.cycles += PAGE_CYCLES;
            self.cycles += FULL_TREE_NODE_COUNT;
            *num_pages += 1;
        }

        let num_pages = self.dirty_arenas.entry(arena).or_insert(0);

        while *num_pages < max_pages_for_io(offset + count) {
            // load could go all the way up the tree
            self.cycles += PAGE_CYCLES;
            self.cycles += FULL_TREE_NODE_COUNT;
            page_out = true;
            *num_pages += 1;
        }

        println!("store_arena({arena}, {offset}, {count}), page_out = {page_out}");
    }

    fn track_load(&mut self, size: u32) {
        println!("load({size})");

        let spans_pages = max_pages_for_io(size);
        self.cycles += PAGE_CYCLES * spans_pages;
        self.cycles += FULL_TREE_NODE_COUNT * spans_pages;
    }
}

fn eval(program: &Program, io: &mut IoCounter) -> Result<()> {
    for op in &program.ops {
        match op.code {
            OpCode::Load => {
                let typ = &program.types[op.result_type];
                let count = typ.coeffs.next_multiple_of(16) as u32;
                io.track_load_arena(op.arena(), op.offset(), count);
            }
            OpCode::Store => {
                let typ = &program.types[op.result_type];
                let count = typ.coeffs.next_multiple_of(16) as u32;
                io.track_store_arena(op.arena(), op.offset(), count);
            }
            _ => {}
        }
    }
    Ok(())
}

/// Partially evaluates the given BigInt program and prints to stdout a worst-case analysis of the
/// paging costs.
pub fn analyze(bytes: &[u8]) -> Result<()> {
    let mut io = IoCounter::new();

    let mut cursor = bytes;

    let nondet_program_size = (&mut cursor).read_u32::<LittleEndian>()? as usize * WORD_SIZE;
    let verify_program_size = (&mut cursor).read_u32::<LittleEndian>()? as usize * WORD_SIZE;
    let consts_size = (&mut cursor).read_u32::<LittleEndian>()? as usize * WORD_SIZE;
    let _temp_size = (&mut cursor).read_u32::<LittleEndian>()? as usize;
    println!("program_size = {nondet_program_size}");

    let mut nondet_program_bytes = &cursor[..nondet_program_size];
    io.track_load(nondet_program_size as u32);

    let program = Program::decode(&mut nondet_program_bytes)?;
    eval(&program, &mut io)?;

    io.track_load(verify_program_size as u32);
    io.track_load(consts_size as u32);

    println!("paging cycles = {}", io.cycles);
    println!("verify cycles = {verify_program_size}");
    println!("total = {}", io.cycles as usize + verify_program_size);

    Ok(())
}
