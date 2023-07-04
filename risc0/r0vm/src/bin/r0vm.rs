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

use std::{fs, path::PathBuf};

use clap::Parser;
use risc0_zkvm::{serde::to_vec, Executor, ExecutorEnv};

/// Runs a RISC-V ELF binary within the RISC Zero ZKVM.
#[derive(Parser)]
#[clap(about, version, author)]
struct Args {
    /// The ELF file to run
    #[clap(long)]
    elf: PathBuf,

    /// Receipt output file.
    #[clap(long)]
    receipt: Option<PathBuf>,

    /// File to read initial input from.
    #[clap(long)]
    initial_input: Option<PathBuf>,

    /// Display verbose output.
    #[clap(short, long, action = clap::ArgAction::Count)]
    verbose: u8,

    /// Add environment vairables in the form of NAME=value.
    #[clap(long, action = clap::ArgAction::Append)]
    env: Vec<String>,

    /// Write "pprof" protobuf output of the guest's run to this file.
    /// You can use google's pprof (<https://github.com/google/pprof>)
    /// to read it.
    #[cfg(feature = "profiler")]
    #[clap(long)]
    pprof_out: Option<PathBuf>,
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

    #[cfg(feature = "profiler")]
    let mut guest_prof: Option<risc0_zkvm::Profiler> = None;
    #[cfg(feature = "profiler")]
    if args.pprof_out.is_some() {
        guest_prof =
            Some(risc0_zkvm::Profiler::new(args.elf.to_str().unwrap(), &elf_contents).unwrap());
    }

    let session = {
        let mut builder = ExecutorEnv::builder();

        for var in args.env.iter() {
            let (name, value) = var
                .split_once('=')
                .expect("Environment variables should be of the form NAME=value");
            builder.env_var(name, value);
        }

        if let Some(input) = args.initial_input.as_ref() {
            builder.stdin(fs::File::open(input).unwrap());
        }

        #[cfg(feature = "profiler")]
        if let Some(ref mut profiler) = guest_prof {
            builder.trace_callback(profiler.make_trace_callback());
        }

        let env = builder.build().unwrap();
        let mut exec = Executor::from_elf(env, &elf_contents).unwrap();
        exec.run().unwrap()
    };

    // Now that we're done with the prover, we can collect the guest profiling data.
    #[cfg(feature = "profiler")]
    if let Some(ref mut profiler) = guest_prof.as_mut() {
        profiler.finalize();
        let report = profiler.encode_to_vec();
        fs::write(args.pprof_out.as_ref().unwrap(), &report)
            .expect("Unable to write profiling output");
    }

    let receipt = session.prove().unwrap();

    let receipt_data = to_vec(&receipt).unwrap();
    let receipt_bytes = bytemuck::cast_slice(&receipt_data);
    if let Some(receipt_file) = args.receipt.as_ref() {
        fs::write(receipt_file, receipt_bytes).expect("Unable to write receipt file");
        if args.verbose > 0 {
            eprintln!(
                "Wrote {} bytes of receipt to {}",
                receipt_data.len(),
                receipt_file.display()
            );
        }
    }
}
