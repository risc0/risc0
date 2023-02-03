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

use std::default::Default;
use std::{
    fs,
    io::Write,
    path::{Path, PathBuf},
};

use anyhow::Result;
use clap::Parser;
use risc0_zkvm::sha::{Digest, DIGEST_WORDS};
use risc0_zkvm::{prove::profiler::Profiler, Prover, ProverOpts, Receipt};
use risc0_zkvm::{MemoryImage, Program, MEM_SIZE, PAGE_SIZE};

/// Runs a RISC-V ELF binary within the RISC Zero ZKVM.
#[derive(Parser)]
#[clap(about, version, author)]
struct Args {
    /// The ELF file to run
    #[clap(long)]
    elf: PathBuf,

    /// ImageID file; created if needed and it doesn't exist.
    #[clap(long)]
    image_id: Option<PathBuf>,

    /// Receipt output file.
    #[clap(long)]
    receipt: Option<PathBuf>,

    /// EXPERIMENTAL: When enabled, writes the receipt in a format usable by the
    /// "verify" guest method.
    #[clap(long)]
    input_for_verify: bool,

    /// Skip generating the seal in receipt.  This should only be used
    /// for testing.  In this case, performace will be much better but
    /// we will not be able to cryptographically verify the execution.
    #[clap(long)]
    skip_seal: bool,

    /// File to read initial input from.
    #[clap(long)]
    initial_input: Option<PathBuf>,

    /// Display verbose output.
    #[clap(short, long, action = clap::ArgAction::Count)]
    verbose: u8,

    /// Write "pprof" protobuf output of the guest's run to this file.
    /// You can use google's pprof (<https://github.com/google/pprof>)
    /// to read it.
    #[clap(long)]
    pprof_out: Option<PathBuf>,
}

fn read_image_id(verbose: u8, elf_file: &Path, image_id_file: Option<&Path>) -> Option<Digest> {
    let elf_mtime = fs::metadata(elf_file).ok()?.modified().ok()?;
    let id_mtime = fs::metadata(image_id_file.as_ref()?)
        .ok()?
        .modified()
        .ok()?;

    if elf_mtime > id_mtime {
        return None;
    }

    let buf = fs::read(image_id_file?).ok()?;
    let id = Digest::try_from(buf).ok()?;

    if verbose > 0 {
        println!(
            "Successfully read image id from {}",
            image_id_file.unwrap().display()
        );
    }

    Some(id)
}

fn run_prover(
    elf_contents: &[u8],
    image_id: &Digest,
    opts: ProverOpts,
    initial_input: Option<Vec<u8>>,
) -> Result<(Receipt, Vec<u8>)> {
    let mut prover = Prover::new_with_opts(&elf_contents, image_id.clone(), opts).unwrap();
    if let Some(bytes) = initial_input {
        prover.add_input_u8_slice(bytes.as_slice());
    }
    let receipt = prover.run()?;
    let output = prover.get_output_u8_slice();
    Ok((receipt, output.to_vec()))
}

fn encode_receipt(receipt: &Receipt, image_id: &[u8], args: &Args) -> Vec<u8> {
    if args.input_for_verify {
        let mut encoded: Vec<u8> = Vec::new();
        let mut add_input_u32_slice =
            |slice: &[u32]| encoded.write_all(bytemuck::cast_slice(slice)).unwrap();
        add_input_u32_slice(&[receipt.seal.len() as u32]);
        add_input_u32_slice(&receipt.seal);
        add_input_u32_slice(&[(image_id.len() / 4) as u32]);
        encoded.write_all(image_id).unwrap();
        return encoded;
    }

    bytemuck::cast_slice(risc0_zkvm::serde::to_vec(&receipt).unwrap().as_slice()).into()
}

fn main() {
    env_logger::init();

    let args = Args::parse();
    let elf_contents = fs::read(&args.elf).unwrap();

    if args.verbose > 0 {
        eprintln!(
            "Read {} bytes of ELF from {}",
            elf_contents.len(),
            args.elf.display()
        );
    }

    let image_id: Digest = if args.receipt.is_none() || args.skip_seal {
        // No need to generate a image ID since we don't need to
        // generate an actual proof.
        Digest::from([0; DIGEST_WORDS])
    } else {
        read_image_id(
            args.verbose,
            &args.elf,
            args.image_id.as_ref().map(|p| p.as_path()),
        )
        .unwrap_or_else(|| {
            if args.verbose > 0 {
                eprintln!("Computing image id");
            }
            let program = Program::load_elf(&elf_contents, MEM_SIZE as u32).unwrap();
            let image = MemoryImage::new(&program, PAGE_SIZE as u32);
            if let Some(image_id_file) = args.image_id.as_ref() {
                std::fs::write(&image_id_file, image.root.as_bytes()).unwrap();
                if args.verbose > 0 {
                    eprintln!("Saved image id to {}", image_id_file.display());
                }
            }
            image.root
        })
    };

    let opts: ProverOpts =
        ProverOpts::default().with_skip_seal(args.skip_seal || args.receipt.is_none());

    let mut guest_prof: Option<Profiler> = None;

    if args.pprof_out.is_some() {
        guest_prof = Some(Profiler::new(args.elf.to_str().unwrap(), &elf_contents).unwrap());
    }

    let proof = run_prover(
        &elf_contents,
        &image_id,
        if let Some(ref mut profiler) = guest_prof {
            opts.with_trace_callback(profiler.make_trace_callback())
        } else {
            opts
        },
        args.initial_input.as_ref().map(|input| {
            let input_bytes = fs::read(input).unwrap();
            if args.verbose > 0 {
                eprintln!("Supplying {} bytes of initial input", input_bytes.len());
            }
            input_bytes
        }),
    );

    // Now that we're done with the prover, we can collect the guest profiling data.
    if let Some(ref mut profiler) = guest_prof.as_mut() {
        profiler.finalize();
        let report = profiler.encode_to_vec();
        fs::write(args.pprof_out.as_ref().unwrap(), &report)
            .expect("Unable to write profiling output");
    }
    let (receipt, output) = proof.expect("Run failed");

    let receipt_data = encode_receipt(&receipt, image_id.as_bytes(), &args);

    if args.skip_seal || args.receipt.is_none() {
        if args.verbose > 0 {
            eprintln!("Skipping seal generation.");
        }
    } else {
        if args.verbose > 0 {
            eprintln!("Verifying that we executed correctly.");
            receipt.verify(&image_id).unwrap();
        }
    }

    if let Some(receipt_file) = args.receipt.as_ref() {
        fs::write(receipt_file, receipt_data.as_slice()).expect("Unable to write receipt file");
        if args.verbose > 0 {
            eprintln!(
                "Wrote {} bytes of receipt to {}",
                receipt_data.len(),
                receipt_file.display()
            );
        }
    }

    if args.verbose > 0 {
        eprintln!("Writing {} bytes of output to stdout", output.len());
    }
    std::io::stdout().write_all(output.as_slice()).unwrap();
}
