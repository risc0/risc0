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

#[cfg(feature = "analyze")]
mod analyze {
    use anyhow::{anyhow, Result};
    use byteorder::{LittleEndian, ReadBytesExt as _};
    use num_derive::FromPrimitive;
    use num_traits::FromPrimitive;

    use std::collections::HashSet;
    use std::io::Read;

    const PAGE_BYTES: usize = 1024;
    const WORD_SIZE: usize = 4;
    const PAGE_WORDS: usize = PAGE_BYTES / WORD_SIZE;

    const POSEIDON_PAGING: u32 = 1;
    const POSEIDON_LOAD_IN: u32 = 2;
    const POSEIDON_DO_OUT: u32 = 1;
    const POSEIDON_EXTERNAL: u32 = 8;
    const POSEIDON_BLOCK_WORDS: u32 = 8;
    const POSEIDON_INTERNAL: u32 = 1;
    const POSEIDON_PAGE_ROUNDS: u32 = PAGE_WORDS as u32 / POSEIDON_BLOCK_WORDS;
    const PAGE_CYCLES: u32 = POSEIDON_PAGING + 10 * POSEIDON_PAGE_ROUNDS + POSEIDON_DO_OUT;

    const NODE_CYCLES: u32 = POSEIDON_PAGING
        + POSEIDON_LOAD_IN
        + POSEIDON_EXTERNAL
        + POSEIDON_INTERNAL
        + POSEIDON_DO_OUT;

    #[derive(Debug)]
    struct Type {
        pub coeffs: u64,
        _max_pos: u64,
        _max_neg: u64,
        _min_bits: u64,
    }

    #[derive(Debug)]
    struct Input {
        _label: u64,
        _bit_width: u32,
        _min_bits: u16,
        _is_public: bool,
    }

    #[derive(Debug, FromPrimitive)]
    enum OpCode {
        Const = 0x2, // unary: constant index
        Load = 0x3,  // unary: constant index
        Store = 0x4, // unary: constant index
        Add = 0x8,   // binary
        Sub = 0x9,   // binary
        Mul = 0xA,   // binary
        Rem = 0xB,   // binary
        Quo = 0xC,   // binary
        Inv = 0xE,   // binary
    }

    #[derive(Debug)]
    struct Op {
        pub code: OpCode,
        pub result_type: usize,
        pub a: usize,
        #[allow(dead_code)]
        pub b: usize,
    }

    struct Program {
        pub inputs: Vec<Input>,
        pub types: Vec<Type>,
        pub constants: Vec<u64>,
        pub ops: Vec<Op>,
    }

    impl Op {
        pub fn arena(&self) -> u32 {
            (self.a >> 16) as u32
        }

        pub fn offset(&self) -> u32 {
            (self.a & 0xffff) as u32
        }

        pub fn decode<R: Read>(stream: &mut R) -> Result<Self> {
            let bits = stream.read_u64::<LittleEndian>()?;
            let opcode = FromPrimitive::from_u32((bits & 0x0F) as u32);
            Ok(Self {
                code: opcode.ok_or_else(|| anyhow!("Invalid BigInt2 bytecode"))?,
                result_type: ((bits >> 4) & 0x0FFF) as usize,
                a: ((bits >> 16) & 0x00FFFFFF) as usize,
                b: ((bits >> 40) & 0x00FFFFFF) as usize,
            })
        }
    }

    impl Input {
        pub fn decode<R: Read>(stream: &mut R) -> Result<Self> {
            Ok(Self {
                _label: stream.read_u64::<LittleEndian>()?,
                _bit_width: stream.read_u32::<LittleEndian>()?,
                _min_bits: stream.read_u16::<LittleEndian>()?,
                _is_public: stream.read_u16::<LittleEndian>()? != 0,
            })
        }
    }

    impl Type {
        pub fn decode<R: Read>(stream: &mut R) -> Result<Self> {
            Ok(Self {
                coeffs: stream.read_u64::<LittleEndian>()?,
                _max_pos: stream.read_u64::<LittleEndian>()?,
                _max_neg: stream.read_u64::<LittleEndian>()?,
                _min_bits: stream.read_u64::<LittleEndian>()?,
            })
        }
    }

    struct IoCounter {
        cycles: u32,
        loaded_arenas: HashSet<u32>,
        dirty_arenas: HashSet<u32>,
    }

    impl IoCounter {
        fn new() -> Self {
            Self {
                cycles: 0,
                loaded_arenas: HashSet::new(),
                dirty_arenas: HashSet::new(),
            }
        }

        fn track_load_arena(&mut self, arena: u32, offset: u32, count: u32) {
            let mut page_in = false;

            if !self.loaded_arenas.contains(&arena) {
                // arena could span 2 pages
                // load could go all the way up the tree
                self.cycles += PAGE_CYCLES * 2;
                self.cycles += 21 * NODE_CYCLES * 2;
                page_in = true;
            }

            self.loaded_arenas.insert(arena);

            println!("load_arena({arena}, {offset}, {count}), page_in = {page_in}");
        }

        fn track_store_arena(&mut self, arena: u32, offset: u32, count: u32) {
            self.cycles += PAGE_CYCLES;
            self.cycles += 22 * NODE_CYCLES * 2;

            let mut page_out = false;

            if !self.loaded_arenas.contains(&arena) {
                // arena could span 2 pages
                // load could go all the way up the tree
                self.cycles += PAGE_CYCLES * 2;
                self.cycles += 21 * NODE_CYCLES * 2;
            }

            self.loaded_arenas.insert(arena);

            if !self.dirty_arenas.contains(&arena) {
                // arena could span 2 pages
                // load could go all the way up the tree
                self.cycles += PAGE_CYCLES * 2;
                self.cycles += 21 * NODE_CYCLES * 2;

                page_out = true;
            }

            self.dirty_arenas.insert(arena);

            println!("store_arena({arena}, {offset}, {count}), page_out = {page_out}");
        }

        fn track_load(&mut self, size: u32) {
            println!("load({size})");
            if size > 0 {
                self.cycles += PAGE_CYCLES;
                self.cycles += 22 * NODE_CYCLES * 2;
            }
        }
    }

    impl Program {
        pub fn decode<R: Read>(stream: &mut R) -> Result<Self> {
            // Read the header. Validate magic number and version.
            let mut magic = [0u8; 4];
            stream.read_exact(&mut magic)?;
            assert_eq!(magic, [0x62, 0x69, 0x62, 0x63]);

            let version = stream.read_u32::<LittleEndian>()?;
            assert_eq!(version, 1);

            let num_inputs = stream.read_u32::<LittleEndian>()? as usize;
            let num_types = stream.read_u32::<LittleEndian>()? as usize;
            let num_constants = stream.read_u32::<LittleEndian>()? as usize;
            let num_ops = stream.read_u32::<LittleEndian>()? as usize;

            // Allocate storage for the program sections, then read each one.
            let mut result = Self {
                inputs: Vec::with_capacity(num_inputs),
                types: Vec::with_capacity(num_types),
                constants: Vec::with_capacity(num_constants),
                ops: Vec::with_capacity(num_ops),
            };
            for _ in 0..num_inputs {
                result.inputs.push(Input::decode(stream)?);
            }
            for _ in 0..num_types {
                result.types.push(Type::decode(stream)?);
            }
            for _ in 0..num_constants {
                result.constants.push(stream.read_u64::<LittleEndian>()?);
            }
            for _ in 0..num_ops {
                result.ops.push(Op::decode(stream)?);
            }
            Ok(result)
        }

        pub fn eval(&self, io: &mut IoCounter) -> Result<()> {
            for op in &self.ops {
                match op.code {
                    OpCode::Load => {
                        let typ = &self.types[op.result_type];
                        let count = typ.coeffs.next_multiple_of(16) as u32;
                        io.track_load_arena(op.arena(), op.offset(), count);
                    }
                    OpCode::Store => {
                        let typ = &self.types[op.result_type];
                        let count = typ.coeffs.next_multiple_of(16) as u32;
                        io.track_store_arena(op.arena(), op.offset(), count);
                    }
                    _ => {}
                }
            }
            Ok(())
        }
    }

    pub fn main(path: &str) -> Result<()> {
        let bytes = std::fs::read(path)?;
        let mut io = IoCounter::new();

        let mut cursor = &bytes[..];

        let nondet_program_size = (&mut cursor).read_u32::<LittleEndian>()? as usize * WORD_SIZE;
        let verify_program_size = (&mut cursor).read_u32::<LittleEndian>()? as usize * WORD_SIZE;
        let consts_size = (&mut cursor).read_u32::<LittleEndian>()? as usize * WORD_SIZE;
        let _temp_size = (&mut cursor).read_u32::<LittleEndian>()? as usize;
        println!("program_size = {nondet_program_size}");

        let mut nondet_program_bytes = &cursor[..nondet_program_size];
        io.track_load(nondet_program_size as u32);

        let program = Program::decode(&mut nondet_program_bytes)?;
        program.eval(&mut io)?;

        io.track_load(verify_program_size as u32);
        io.track_load(consts_size as u32);

        println!("paging cycles = {}", io.cycles);
        println!("verify cycles = {verify_program_size}");
        println!("total = {}", io.cycles as usize + verify_program_size);

        Ok(())
    }
}

#[cfg(feature = "analyze")]
pub fn main() -> anyhow::Result<()> {
    let path = std::env::args()
        .nth(1)
        .expect("expected path to bigint program");
    analyze::main(&path)
}

#[cfg(not(feature = "analyze"))]
pub fn main() {
    panic!("compile with feature \"analyze\"");
}
