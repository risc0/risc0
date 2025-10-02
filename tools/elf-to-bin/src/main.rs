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
use risc0_binfmt::{ByteAddr, MemoryImage, Program, ProgramBinary};
use std::path::PathBuf;

pub const USER_START_ADDR: ByteAddr = ByteAddr(0x0001_0000);

#[derive(Parser)]
#[command(name = "elf-to-bin")]
#[command(
    about = "A simple tool to combine a guest ELF with a kernel ELF into a .bin file, or create a MemoryImage from just a kernel ELF"
)]
struct Args {
    /// Path to the guest ELF file (optional)
    #[arg(short, long)]
    interp_elf: Option<PathBuf>,

    #[arg(short, long)]
    guest_elf: Option<PathBuf>,

    /// Path to the kernel ELF file
    #[arg(short, long)]
    kernel_elf: PathBuf,

    /// Output path for the combined .bin file
    #[arg(short, long)]
    output: PathBuf,
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args = Args::parse();

    // Read the kernel ELF
    let kernel_elf = std::fs::read(&args.kernel_elf).map_err(|e| {
        format!(
            "Failed to read kernel ELF from {:?}: {}",
            args.kernel_elf, e
        )
    })?;

    let bin_data = if let Some(interp_elf_path) = &args.interp_elf {
        if let Some(guest_elf_path) = &args.guest_elf {
            let kernel_elf = std::fs::read(&args.kernel_elf).map_err(|e| {
                format!(
                    "Failed to read kernel ELF from {:?}: {}",
                    args.kernel_elf, e
                )
            })?;
            let kernel_program = Program::load_elf(&kernel_elf, u32::MAX)
                .map_err(|e| format!("Failed to load kernel ELF: {}", e))?;
            let interp_elf = std::fs::read(interp_elf_path).map_err(|e| {
                format!("Failed to read guest ELF from {:?}: {}", interp_elf_path, e)
            })?;
            let guest_elf = std::fs::read(guest_elf_path).map_err(|e| {
                format!("Failed to read guest ELF from {:?}: {}", guest_elf_path, e)
            })?;

            let elf = Program::load_elf_dyn(&guest_elf, u32::MAX, &interp_elf).map_err(|e| {
                format!("Failed to read guest ELF from {:?}: {}", guest_elf_path, e)
            })?;
            let memory_image = MemoryImage::new_dyn(elf, kernel_program);
            bincode::serialize(&memory_image)
                .map_err(|e| format!("Failed to serialize MemoryImage: {}", e))?
        } else {
            panic!("Guest ELF path is required");
        }
    } else if let Some(guest_elf_path) = &args.guest_elf {
        let guest_elf = std::fs::read(guest_elf_path)
            .map_err(|e| format!("Failed to read guest ELF from {:?}: {}", guest_elf_path, e))?;

        // Create the combined binary
        let binary = ProgramBinary::new(&guest_elf, &kernel_elf);
        binary.encode()
    } else {
        // Create MemoryImage from kernel ELF only
        let mut kernel_program = Program::load_elf(&kernel_elf, u32::MAX)
            .map_err(|e| format!("Failed to load kernel ELF: {}", e))?;
        kernel_program.write_u32(USER_START_ADDR.0, 0);

        let memory_image = MemoryImage::new_kernel(kernel_program);
        // Serialize the MemoryImage
        bincode::serialize(&memory_image)
            .map_err(|e| format!("Failed to serialize MemoryImage: {}", e))?
    };

    // Write the output file
    std::fs::write(&args.output, &bin_data)
        .map_err(|e| format!("Failed to write output to {:?}: {}", args.output, e))?;

    if let Some(guest_elf_path) = &args.guest_elf {
        println!(
            "Successfully created {:?} from guest ELF {:?} and kernel ELF {:?}",
            args.output, guest_elf_path, args.kernel_elf
        );
    } else {
        println!(
            "Successfully created {:?} from kernel ELF {:?} (MemoryImage)",
            args.output, args.kernel_elf
        );
    }
    println!("Output size: {} bytes", bin_data.len());

    Ok(())
}
