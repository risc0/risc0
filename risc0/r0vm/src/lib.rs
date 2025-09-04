// Copyright 2025 RISC Zero, Inc.
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

mod actors;
mod api;

use std::fs::File;
use std::os::unix::io::FromRawFd;
use std::{io, net::SocketAddr, path::PathBuf, rc::Rc};

use clap::{Args, Parser, ValueEnum};
use risc0_circuit_rv32im::execute::Segment;
use risc0_zkvm::{
    ApiServer, ExecutorEnv, ExecutorImpl, ProverOpts, ProverServer, VerifierContext,
    compute_image_id, compute_kernel_id, get_prover_server,
};
use tracing_subscriber::EnvFilter;

/// Runs a RISC-V ELF binary within the RISC Zero ZKVM.
#[derive(Parser)]
#[command(about, version, author)]
struct Cli {
    #[command(flatten)]
    mode: Mode,

    /// Receipt output file.
    #[arg(long)]
    receipt: Option<PathBuf>,

    /// The hash function to use to produce a proof.
    #[arg(long, value_enum, default_value_t = HashFn::Poseidon2)]
    hashfn: HashFn,

    /// Whether to prove executions ending in error status.
    //
    // When false, only prove execution sessions that end in a successful
    // [ExitCode] (i.e. `Halted(0)` or `Paused(0)`. When set to true, any
    // completed execution session will be proven, including indicated
    // errors (e.g. `Halted(1)`) and sessions ending in `Fault`.
    #[arg(long)]
    prove_guest_errors: bool,

    /// File to read initial input from.
    ///
    /// Reads input from stdin if an initial input file is not provided.
    #[arg(long)]
    initial_input: Option<PathBuf>,

    /// Display verbose output.
    #[arg(short, long, action = clap::ArgAction::Count)]
    verbose: u8,

    /// Add environment variables in the form of NAME=value.
    #[arg(long, action = clap::ArgAction::Append)]
    env: Vec<String>,

    /// Write "pprof" protobuf output of the guest's run to this file.
    /// You can use google's pprof (<https://github.com/google/pprof>)
    /// to read it.
    #[arg(long, env = "RISC0_PPROF_OUT")]
    pprof_out: Option<PathBuf>,

    /// The receipt kind produced by the r0vm prover
    #[arg(long, value_enum, default_value_t = ReceiptKind::Composite)]
    receipt_kind: ReceiptKind,

    /// Compute the image_id for the specified ELF
    #[arg(long)]
    id: bool,

    /// Compute the kernel image ID for the specified binary.
    #[arg(long, conflicts_with = "id")]
    kernel_id: bool,

    #[arg(long)]
    with_debugger: bool,

    /// The address to connect to or listen on.
    #[arg(long)]
    addr: Option<SocketAddr>,

    #[arg(long)]
    api: Option<SocketAddr>,

    #[arg(long)]
    storage: Option<PathBuf>,

    #[arg(long)]
    po2: Option<u32>,

    /// Number of GPUs to use.
    #[arg(long)]
    num_gpus: Option<usize>,
}

#[derive(Args)]
#[group(required = true)]
struct Mode {
    #[arg(long)]
    rpc: bool,

    /// Connect to given actor allocator RPC port and print status as JSON
    #[arg(long)]
    actor_status: Option<String>,

    #[arg(long)]
    port: Option<u16>,

    /// The ELF to execute
    #[arg(long)]
    elf: Option<PathBuf>,

    /// The image to execute
    #[arg(long)]
    image: Option<PathBuf>,

    /// Prove a pre-recorded segment.
    #[arg(long)]
    segment: Option<PathBuf>,

    #[arg(long)]
    config: Option<PathBuf>,
}

#[derive(Copy, Clone, PartialEq, Eq, PartialOrd, Ord, ValueEnum)]
enum HashFn {
    #[value(name = "sha-256")]
    Sha256,
    #[value(name = "poseidon2")]
    Poseidon2,
}

#[derive(Clone, PartialEq, ValueEnum)]
enum ReceiptKind {
    #[value(name = "composite")]
    Composite,
    #[value(name = "succinct")]
    Succinct,
    #[value(name = "groth16")]
    Groth16,
}

pub fn main() {
    let mut cli_args = std::env::args().collect::<Vec<_>>();
    let mut guest_args = Vec::new();

    // Find the "--" separator and split arguments
    if let Some(dash_dash_pos) = cli_args.iter().position(|arg| arg == "--") {
        guest_args = cli_args.split_off(dash_dash_pos + 1);
        cli_args.pop(); // Remove the "--" itself
    }

    let args = Cli::parse_from(cli_args);

    if args.mode.config.is_some() {
        self::actors::async_main(args.mode.config).unwrap();
        return;
    }

    if args.mode.rpc {
        self::actors::rpc_main(args.num_gpus).unwrap();
        return;
    }

    if let Some(host) = args.mode.actor_status {
        self::actors::status_main(host).unwrap();
        return;
    }

    init_logging();

    if args.num_gpus.is_some_and(|v| v != 1) {
        eprintln!("num_gpus > 1 or 0 for current mode unsupported.");
        return;
    }

    if args.id {
        let blob = std::fs::read(args.mode.elf.unwrap()).unwrap();
        let image_id = compute_image_id(&blob).unwrap();
        println!("{image_id}");
        return;
    }
    if args.kernel_id {
        let blob = std::fs::read(args.mode.elf.unwrap()).unwrap();
        let image_id = compute_kernel_id(&blob).unwrap();
        println!("{image_id}");
        return;
    }

    if let Some(port) = args.mode.port {
        run_server(port);
        return;
    }

    if let Some(path) = args.mode.segment {
        let bytes = std::fs::read(path).unwrap();
        let segment = Segment::decode(&bytes).unwrap();
        segment.execute().unwrap();
        return;
    }

    let env = {
        let mut builder = ExecutorEnv::builder();

        // Add guest arguments if any were provided after "--"
        if !guest_args.is_empty() {
            builder.args(&guest_args);
        }

        for var in args.env.iter() {
            let (name, value) = var
                .split_once('=')
                .expect("Environment variables should be of the form NAME=value");
            builder.env_var(name, value);
        }

        if let Some(input) = args.initial_input.as_ref() {
            builder.stdin(std::fs::File::open(input).unwrap());
        } else {
            builder.stdin(io::stdin());
        }
        // use fd 3 for p9 reading, and 4 for p9 writing
        unsafe {
            builder.read_fd(3, io::BufReader::new(File::from_raw_fd(3)));
            builder.write_fd(4, io::BufWriter::new(File::from_raw_fd(4)));
        }

        if let Some(pprof_out) = args.pprof_out.as_ref() {
            builder.enable_profiler(pprof_out);
        }

        builder.build().unwrap()
    };

    // TODO(povw): Add PoVW here.
    let session = {
        let mut exec = if let Some(ref elf_path) = args.mode.elf {
            let elf_contents = std::fs::read(elf_path).unwrap();
            ExecutorImpl::from_elf(env, &elf_contents).unwrap()
        } else if let Some(ref image_path) = args.mode.image {
            let image_contents = std::fs::read(image_path).unwrap();
            let image = bincode::deserialize(&image_contents).unwrap();
            ExecutorImpl::new(env, image).unwrap()
        } else {
            unreachable!()
        };
        if args.with_debugger {
            exec.run_with_debugger().unwrap();
            return;
        } else {
            exec.run().unwrap()
        }
    };

    let prover = args.get_prover();
    let ctx = VerifierContext::default();
    let receipt = prover.prove_session(&ctx, &session).unwrap().receipt;

    let receipt_data = bincode::serialize(&receipt).unwrap();
    let receipt_bytes = bytemuck::cast_slice(&receipt_data);
    if let Some(receipt_file) = args.receipt.as_ref() {
        std::fs::write(receipt_file, receipt_bytes).expect("Unable to write receipt file");
        if args.verbose > 0 {
            eprintln!(
                "Wrote {} bytes of receipt to {}",
                receipt_data.len(),
                receipt_file.display()
            );
        }
    }
}

impl Cli {
    fn get_prover(&self) -> Rc<dyn ProverServer> {
        let hashfn = match self.hashfn {
            HashFn::Sha256 => "sha-256",
            HashFn::Poseidon2 => "poseidon2",
        };
        let opts = ProverOpts::default()
            .with_hashfn(hashfn.to_string())
            .with_prove_guest_errors(self.prove_guest_errors)
            .with_receipt_kind(match self.receipt_kind {
                ReceiptKind::Composite => risc0_zkvm::ReceiptKind::Composite,
                ReceiptKind::Succinct => risc0_zkvm::ReceiptKind::Succinct,
                ReceiptKind::Groth16 => risc0_zkvm::ReceiptKind::Groth16,
            });
        get_prover_server(&opts).unwrap()
    }
}

fn run_server(port: u16) {
    let addr = format!("127.0.0.1:{port}");
    let server = ApiServer::new_tcp(addr);
    server.run().unwrap()
}

fn init_logging() {
    tracing_subscriber::fmt()
        .with_env_filter(EnvFilter::from_default_env())
        .with_writer(std::io::stderr)
        .init();
}
