// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{
    fs,
    process::{Command, Stdio},
};

use clap::{Parser, ValueEnum};
use regex::Regex;
use risc0_core::field::baby_bear::Elem;
use tempfile::tempdir;

// Set the user chosen constants

// The baby bear prime
const FIELD: usize = 15 * (1 << 27) + 1;

// 16 for rate, 8 for capacity
const CELLS: usize = 24;

// The goal security level
const SECURITY: usize = 128;

// # of bits in FIELD
const NUM_BITS: usize = 31;

// Smallest allowed alpha for Baby Bear
const ALPHA: usize = 7;

// A structure to hold all computed constants to eventually be exported
struct ComputedConstants {
    rounds_full: usize,             // The number of full rounds, always 8 in practice
    rounds_partial: usize,          // The number of partial rounds, computed based on security
    round_constants: Vec<Elem>,     // Additive round constants
    mds: Vec<Elem>,                 // mds matrix constants
    partial_comp_matrix: Vec<Elem>, // Computed compressed matrix for partial rounds
    partial_comp_offset: Vec<Elem>, // Computed compressed offsets for partial rounds
}

impl ComputedConstants {
    fn new() -> Self {
        ComputedConstants {
            rounds_full: 0,
            rounds_partial: 0,
            round_constants: Vec::<Elem>::new(),
            mds: Vec::<Elem>::new(),
            partial_comp_matrix: Vec::<Elem>::new(),
            partial_comp_offset: Vec::<Elem>::new(),
        }
    }
}

// A function to turn a string of hex constants into a vector of Elems
fn to_elems(input_string: &str) -> Vec<Elem> {
    let mut out = Vec::<Elem>::new();
    for part in input_string.split(',') {
        let tidy_part: String = part
            .chars()
            .filter(|c| "0123456789abcdef".contains(*c))
            .collect();
        let num = u32::from_str_radix(&tidy_part, 16).expect("failed to parse hex number into u32");
        assert!(num < (FIELD as u32));
        out.push(Elem::new(num));
    }
    out
}

// The code that parses the textual output from sage into the constants
fn extract_from_sage(consts: &mut ComputedConstants, stdout: &str) {
    // Split stdout into lines
    let out_lines: Vec<&str> = stdout.split('\n').collect();

    // Match the first line and extract the computed values
    let regex = Regex::new("n=31, t=24, alpha=7, M=128, R_F=([0-9]+), R_P=([0-9]+)").unwrap();
    let cap = regex.captures(out_lines[0]).unwrap();
    consts.rounds_full = cap[1].parse::<usize>().unwrap();
    consts.rounds_partial = cap[2].parse::<usize>().unwrap();

    // Grab the two constants we care about
    consts.round_constants = to_elems(out_lines[5]);
    consts.mds = to_elems(out_lines[17]);
    assert!(consts.round_constants.len() == (consts.rounds_full + consts.rounds_partial) * CELLS);
    assert!(consts.mds.len() == CELLS * CELLS);
}

// Run the upstream 'official' sage code and get the output
fn run_sage() -> String {
    // Make a temporary directory
    let temp_dir = tempdir().unwrap();

    // Checkout the 'official' sagemath code
    tracing::info!("Checking out hadeshash repo");
    let status = Command::new("git")
        .current_dir(temp_dir.path())
        .arg("clone")
        .arg("https://extgit.iaik.tugraz.at/krypto/hadeshash.git")
        .stdout(Stdio::null())
        .stderr(Stdio::null())
        .status()
        .unwrap();
    assert!(status.success());

    // Get the directory the checkout is in
    let sage_dir = temp_dir.path().join("hadeshash");
    fs::create_dir_all(&sage_dir).unwrap();

    // Move the correct commit
    tracing::info!("Setting commit");
    let status = Command::new("git")
        .current_dir(&sage_dir)
        .arg("checkout")
        .arg("b5434fd2b2785926dd1dd386efbef167da57c064")
        .stdout(Stdio::null())
        .stderr(Stdio::null())
        .status()
        .unwrap();
    assert!(status.success());

    // Get the directory the code is in
    let code_dir = sage_dir.join("code");
    fs::create_dir_all(&code_dir).unwrap();

    // Run sage math with the right parameters
    tracing::info!("Running some math, please wait about 2 minutes");
    let sage_child = Command::new("sage")
        .current_dir(code_dir)
        .arg("generate_params_poseidon.sage")
        .arg("1") // Flag to use GF(p)
        .arg("0") // Flag to use box x^alpha
        .arg(NUM_BITS.to_string()) // Field size in bits
        .arg(CELLS.to_string()) // Number of cells
        .arg(ALPHA.to_string()) // Alpha
        .arg(SECURITY.to_string()) // Desired security level
        .arg(format!("{FIELD:x}")) // P in hex i.e. 15*2^27 + 1
        .stdout(Stdio::piped()) // Pipe output
        .spawn()
        .expect("Failed to spawn Sage process. Is Sage installed?");

    // Convert the output to a bunch of lines
    let sage_output = sage_child.wait_with_output().unwrap();
    assert!(sage_output.status.success());
    std::str::from_utf8(&sage_output.stdout)
        .unwrap()
        .to_string()
}

// Precompute multipliers and offsets for the partial rounds
fn compute_partial_compression(consts: &mut ComputedConstants) {
    // We make a matrix of size (CELLS + rounds_partial) x (CELLS + rounds_partial +
    // 1) which allows us to combine the linear operations of round constants +
    // mds values. As we go, we track for each 'cell' the linear effect of all
    // input cells and all sboxes up until this point.
    let row_size = CELLS + consts.rounds_partial;
    let rounds_partial = consts.rounds_partial;
    let rounds_half_full = consts.rounds_full / 2;
    let round_constants = &consts.round_constants;
    let mds = &consts.mds;
    let mut final_matrix = vec![Elem::new(0); row_size * row_size];
    let mut final_offset = vec![Elem::new(0); row_size];

    // Initially, each cell is identity
    let mut cur_matrix = vec![Elem::new(0); CELLS * row_size];
    for i in 0..CELLS {
        cur_matrix[i * row_size + i] = Elem::new(1);
    }
    // Initially, offset is 0
    let mut cur_offset = [Elem::new(0); CELLS];

    // Now, time to do all the rounds
    for round in 0..rounds_partial {
        // Add the constants to the current offset
        for i in 0..CELLS {
            cur_offset[i] += round_constants[(rounds_half_full + round) * CELLS + i];
        }
        // Write data for this round's sbox based on CELL 0
        final_offset[CELLS + round] = cur_offset[0];
        for i in 0..row_size {
            final_matrix[(CELLS + round) * row_size + i] = cur_matrix[i];
        }
        // Now, replace the 0th row so it is purely determined by rounds box
        for (i, cur) in cur_matrix.iter_mut().enumerate().take(row_size) {
            *cur = if i == CELLS + round {
                Elem::new(1)
            } else {
                Elem::new(0)
            };
        }
        cur_offset[0] = Elem::new(0);
        // Now, do the mds multiply.
        let old_matrix = cur_matrix.clone();
        let old_offset = cur_offset;
        for i in 0..CELLS {
            for j in 0..row_size {
                let mut tot = Elem::new(0);
                for k in 0..CELLS {
                    tot += mds[i * CELLS + k] * old_matrix[k * row_size + j];
                }
                cur_matrix[i * row_size + j] = tot;
            }
        }
        for i in 0..CELLS {
            let mut tot = Elem::new(0);
            for j in 0..CELLS {
                tot += mds[i * CELLS + j] * old_offset[j];
            }
            cur_offset[i] = tot;
        }
    }
    // Write out final state
    for i in 0..CELLS {
        final_offset[i] = cur_offset[i];
        for j in 0..row_size {
            final_matrix[i * row_size + j] = cur_matrix[i * row_size + j];
        }
    }
    consts.partial_comp_matrix = final_matrix;
    consts.partial_comp_offset = final_offset;
}

trait LanguageExporter {
    // Define overloadable implementations
    fn header();

    fn export_constant(name: &str, value: usize);

    fn export_array(name: &str, value: &[Elem]);

    // Define main entry point that calls above overloads
    fn export(consts: &ComputedConstants) {
        Self::header();
        Self::export_constant("CELLS", CELLS);
        Self::export_constant("ALPHA", ALPHA);
        Self::export_constant("ROUNDS_FULL", consts.rounds_full);
        Self::export_constant("ROUNDS_HALF_FULL", consts.rounds_full / 2);
        Self::export_constant("ROUNDS_PARTIAL", consts.rounds_partial);
        Self::export_array("ROUND_CONSTANTS", &consts.round_constants);
        Self::export_array("MDS", &consts.mds);
        Self::export_array("PARTIAL_COMP_MATRIX", &consts.partial_comp_matrix);
        Self::export_array("PARTIAL_COMP_OFFSET", &consts.partial_comp_offset);
    }
}

struct RustLanguageExporter;

impl LanguageExporter for RustLanguageExporter {
    fn header() {
        const RUST_HEADER: &str = r#"// Copyright 2025 RISC Zero, Inc.
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

// This file is automatically generated by:
// cargo xtask bootstrap-poseidon rust

use risc0_core::field::baby_bear::Elem;

macro_rules! baby_bear_array {
    [$($x:literal),* $(,)?] => {
        [$(Elem::new($x)),* ]
    }
}

"#;

        print!("{RUST_HEADER}");
    }

    fn export_constant(name: &str, value: usize) {
        println!("pub const {name}: usize = {value};");
    }

    fn export_array(name: &str, elems: &[Elem]) {
        println!();
        println!("pub const {name}: &[Elem] = &baby_bear_array![");
        for line in elems.chunks(8) {
            print!("   ");
            for elem in line {
                print!(" 0x{:08x},", elem.as_u32())
            }
            println!();
        }
        println!("];");
    }
}

struct CppLanguageExporter;

impl LanguageExporter for CppLanguageExporter {
    fn header() {
        const CPP_HEADER: &str = r#"// Copyright 2025 RISC Zero, Inc.
//
// All rights reserved.

// This file is automatically generated by:
// cargo xtask bootstrap-poseidon cpp

"#;

        print!("{CPP_HEADER}");
    }

    fn export_constant(name: &str, value: usize) {
        println!("constexpr size_t {name} = {value};");
    }

    fn export_array(name: &str, elems: &[Elem]) {
        println!();
        println!("constexpr uint64_t {}[{}] = {{", name, elems.len());
        for line in elems.chunks(8) {
            print!("   ");
            for elem in line {
                print!(" 0x{:08x},", elem.as_u32())
            }
            println!();
        }
        println!("}};");
    }
}

#[derive(Copy, Clone, PartialEq, Eq, PartialOrd, Ord, ValueEnum)]
enum Lang {
    Cpp,
    Rust,
}

#[derive(Parser)]
pub struct BootstrapPoseidon {
    /// The language to output to
    lang: Lang,
}

impl BootstrapPoseidon {
    pub fn run(&self) {
        let mut consts = ComputedConstants::new();
        let sage_str = run_sage();
        extract_from_sage(&mut consts, &sage_str);
        compute_partial_compression(&mut consts);
        match self.lang {
            Lang::Cpp => CppLanguageExporter::export(&consts),
            Lang::Rust => RustLanguageExporter::export(&consts),
        }
    }
}
