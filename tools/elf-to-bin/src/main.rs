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

use clap::Parser;
use risc0_binfmt::ProgramBinary;
use std::path::PathBuf;

#[derive(Parser)]
#[command(name = "elf-to-bin")]
#[command(about = "A simple tool to combine a guest ELF with a kernel ELF into a .bin file")]
struct Args {
    /// Path to the guest ELF file
    #[arg(short, long)]
    guest_elf: PathBuf,

    /// Path to the kernel ELF file
    #[arg(short, long)]
    kernel_elf: PathBuf,

    /// Output path for the combined .bin file
    #[arg(short, long)]
    output: PathBuf,
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args = Args::parse();

    // Read the guest ELF
    let guest_elf = std::fs::read(&args.guest_elf)
        .map_err(|e| format!("Failed to read guest ELF from {:?}: {}", args.guest_elf, e))?;

    // Read the kernel ELF
    let kernel_elf = std::fs::read(&args.kernel_elf).map_err(|e| {
        format!(
            "Failed to read kernel ELF from {:?}: {}",
            args.kernel_elf, e
        )
    })?;

    // Create the combined binary
    let binary = ProgramBinary::new(&guest_elf, &kernel_elf);
    let bin_data = binary.encode();

    // Write the output file
    std::fs::write(&args.output, &bin_data)
        .map_err(|e| format!("Failed to write output to {:?}: {}", args.output, e))?;

    println!(
        "Successfully created {:?} from guest ELF {:?} and kernel ELF {:?}",
        args.output, args.guest_elf, args.kernel_elf
    );
    println!("Output size: {} bytes", bin_data.len());

    Ok(())
}
