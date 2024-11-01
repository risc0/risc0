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

use num_traits::FromPrimitive;
use std::io::{Error, Read, Seek};

use super::bibc;

fn read_u16<R: Read + Seek>(stream: &mut R) -> Result<u16, Error> {
    let mut bytes = [0u8; 2];
    stream.read_exact(&mut bytes)?;
    Ok(u16::from_le_bytes(bytes))
}

fn read_u32<R: Read + Seek>(stream: &mut R) -> Result<u32, Error> {
    let mut bytes = [0u8; 4];
    stream.read_exact(&mut bytes)?;
    Ok(u32::from_le_bytes(bytes))
}

fn read_u64<R: Read + Seek>(stream: &mut R) -> Result<u64, Error> {
    let mut bytes = [0u8; 8];
    stream.read_exact(&mut bytes)?;
    Ok(u64::from_le_bytes(bytes))
}

fn read_input<R: Read + Seek>(mut stream: &mut R) -> Result<bibc::Input, Error> {
    let ret = bibc::Input {
        label: read_u64(&mut stream)?,
        bit_width: read_u32(&mut stream)?,
        min_bits: read_u16(&mut stream)?,
        is_public: read_u16(&mut stream)? != 0,
    };
    Ok(ret)
}

fn read_type<R: Read + Seek>(mut stream: &mut R) -> Result<bibc::Type, Error> {
    let ret = bibc::Type {
        coeffs: read_u64(&mut stream)?,
        max_pos: read_u64(&mut stream)?,
        max_neg: read_u64(&mut stream)?,
        min_bits: read_u64(&mut stream)?,
    };
    Ok(ret)
}

fn read_op<R: Read + Seek>(mut stream: &mut R) -> Result<bibc::Op, Error> {
    let bits = read_u64(&mut stream)?;
    let opcode = FromPrimitive::from_u32((bits & 0x0F) as u32);
    assert!(opcode.is_some());
    let ret = bibc::Op {
        code: opcode.unwrap(),
        result_type: ((bits >> 4) & 0x0FFF) as usize,
        operand_a: ((bits >> 16) & 0x00FFFFFF) as usize,
        operand_b: ((bits >> 40) & 0x00FFFFFF) as usize,
    };
    Ok(ret)
}

pub fn read_program<R: Read + Seek>(mut stream: &mut R) -> Result<bibc::Program, Error> {
    // Read the header. Validate magic number and version.
    let mut magic = [0u8; 4];
    stream.read_exact(&mut magic)?;
    assert!(magic == [0x62, 0x69, 0x62, 0x63]);
    let version = read_u32(&mut stream)?;
    assert!(version == 1);
    let num_inputs = read_u32(&mut stream)? as usize;
    let num_types = read_u32(&mut stream)? as usize;
    let num_constants = read_u32(&mut stream)? as usize;
    let num_ops = read_u32(&mut stream)? as usize;
    // Allocate storage for the program sections, then read each one.
    let mut result = bibc::Program {
        inputs: Vec::<bibc::Input>::with_capacity(num_inputs),
        types: Vec::<bibc::Type>::with_capacity(num_types),
        constants: Vec::<u64>::with_capacity(num_constants),
        ops: Vec::<bibc::Op>::with_capacity(num_ops),
    };
    for _ in 0..num_inputs {
        result.inputs.push(read_input(&mut stream)?);
    }
    for _ in 0..num_types {
        result.types.push(read_type(&mut stream)?);
    }
    for _ in 0..num_constants {
        result.constants.push(read_u64(&mut stream)?);
    }
    for _ in 0..num_ops {
        result.ops.push(read_op(&mut stream)?);
    }
    Ok(result)
}
