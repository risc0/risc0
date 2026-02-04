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

use std::{
    hint::black_box,
    path::PathBuf,
    sync::LazyLock,
    time::{Duration, Instant},
};

use clap::{Parser, Subcommand};
use enum_iterator::Sequence;
use risc0_bigint2_methods::ECDSA_ELF as BIGINT2_ELF;
use risc0_binfmt::ProgramBinary;
use risc0_circuit_rv32im::execute::DEFAULT_SEGMENT_LIMIT_PO2;
use risc0_zkos_v1compat::V1COMPAT_ELF;
use risc0_zkp::{MAX_CYCLES_PO2, hal::tracker};
use risc0_zkvm::{
    ExecutorEnv, ExecutorImpl, ProverOpts, RECURSION_PO2, ReceiptKind, Segment, Session,
    SimpleSegmentRef, VerifierContext, get_prover_server,
};
use serde::Serialize;
use serde_with::{DurationNanoSeconds, serde_as};
use tabled::{Table, Tabled, settings::Style};

/// Powers-of-two for cycles, paired with the number of loop iterations used to
/// achieve that many cycles.
const CYCLES_PO2_ITERS: &[(u32, u32)] = &[
    (15, 1024 * 16),
    (16, 1024 * 64),
    (17, 1024 * 128),
    (18, 1024 * 192),
    (19, 1024 * 512),
    (20, 1024 * 1024),
    (21, 1024 * 1024 * 2),
    (22, 1024 * 1024 * 4),
    (23, 1024 * 1024 * 16),
    (24, 1024 * 1024 * 32),
];

const MIN_CYCLES_PO2: usize = CYCLES_PO2_ITERS[0].0 as usize;

/// The number of iterations of the LOOP_ELF needed to fill up a po2=20 segment.
const ITERATIONS_FULL_PO2_20_SEGMENT: usize = 1024 * 494 + 785;

/// Pre-compiled program that simply loops `count: u32` times (read from stdin).
static LOOP_ELF: LazyLock<Vec<u8>> = LazyLock::new(|| {
    const LOOP_ELF: &[u8] = include_bytes!("loop.bin");
    ProgramBinary::new(LOOP_ELF, V1COMPAT_ELF).encode()
});

#[serde_as]
#[derive(Debug, Default, Serialize, Tabled)]
struct PerformanceData {
    name: String,

    #[tabled(display = "display::str")]
    hashfn: Option<String>,

    /// Iterations per second.
    #[tabled(display = "display::hertz")]
    instruction_throughput: Option<f64>,

    /// Rows per second.
    #[tabled(display = "display::hertz")]
    row_throughput: Option<f64>,

    #[serde_as(as = "DurationNanoSeconds")]
    #[tabled(display = "display::duration")]
    duration: Duration,

    /// riscv instructions
    #[tabled(display = "display::n")]
    instruction_count: Option<u64>,

    /// Rows
    #[tabled(display = "display::n")]
    row_count: Option<u64>,

    #[tabled(display = "display::bytes")]
    ram: Option<u64>,

    #[tabled(display = "display::bytes")]
    seal: Option<u64>,
}

#[derive(Parser)]
struct Args {
    #[command(subcommand)]
    command: Option<Command>,

    /// Output result to a JSON file.
    #[arg(long, short)]
    json: Option<PathBuf>,

    /// Select max size for composite runs
    #[arg(long, default_value_t = 20, value_parser = po2_in_range)]
    max_po2: usize,
}

fn po2_in_range(s: &str) -> Result<usize, String> {
    let po2: usize = s.parse().map_err(|_| format!("`{s}` must be an integer"))?;
    if (MIN_CYCLES_PO2..=MAX_CYCLES_PO2).contains(&po2) {
        Ok(po2)
    } else {
        Err(format!(
            "po2 must be in range: {MIN_CYCLES_PO2}-{MAX_CYCLES_PO2}",
        ))
    }
}

fn execute_elf(env: ExecutorEnv, elf: &[u8]) -> anyhow::Result<Session> {
    ExecutorImpl::from_elf(env, elf)
        .unwrap()
        .run_with_callback(|segment| Ok(Box::new(SimpleSegmentRef::new(segment))))
}

#[derive(Eq, PartialEq, Subcommand, Sequence)]
enum Command {
    Execute,
    Composite,
    Lift,
    Join,
    Succinct,
    Identity,
    #[cfg(any(feature = "docker", feature = "cuda"))]
    StarkToSnark,
    #[cfg(any(feature = "docker", feature = "cuda"))]
    Groth16,
    #[command(name = "bigint2")]
    BigInt2,
}

#[derive(Default)]
struct Datasheet {
    results: Vec<PerformanceData>,
}

impl Datasheet {
    pub fn run(&mut self, args: Args) {
        self.warmup();

        if let Some(ref cmd) = args.command {
            self.run_cmd(cmd, &args);
        } else {
            for cmd in enum_iterator::all::<Command>() {
                self.run_cmd(&cmd, &args);
            }
        }

        let mut table = Table::new(&self.results);
        table.with(Style::modern());
        println!("{table}");

        if let Some(path) = args.json {
            if let Some(parent) = path.parent() {
                std::fs::create_dir_all(parent).unwrap();
            }
            let json = serde_json::to_string_pretty(&self.results).unwrap();
            std::fs::write(path, json).unwrap();
        }
    }

    fn run_cmd(&mut self, cmd: &Command, args: &Args) {
        match cmd {
            Command::Execute => self.execute(),
            Command::Composite => self.composite(args),
            Command::Lift => self.lift(),
            Command::Join => self.join(),
            Command::Succinct => self.succinct(),
            Command::Identity => self.identity_p254(),
            #[cfg(any(feature = "docker", feature = "cuda"))]
            Command::StarkToSnark => self.shrink_wrap(),
            #[cfg(any(feature = "docker", feature = "cuda"))]
            Command::Groth16 => self.groth16(),
            Command::BigInt2 => self.bigint2(),
        }
    }

    fn execute(&mut self) {
        let env = ExecutorEnv::builder()
            .write_slice(&ITERATIONS_FULL_PO2_20_SEGMENT.to_le_bytes())
            .build()
            .unwrap();

        let start = Instant::now();
        let session = execute_elf(env, &LOOP_ELF).unwrap();
        let duration = start.elapsed();

        // We want to ensure that we're using a full single segment for this benchmark.
        assert_eq!(
            session.segments.len(),
            1,
            "{} didn't fit in po2={DEFAULT_SEGMENT_LIMIT_PO2}",
            session.row_count
        );

        let instruction_throughput = (session.insn_count as f64) / duration.as_secs_f64();
        self.results.push(PerformanceData {
            name: "execute".into(),
            instruction_count: Some(session.insn_count),
            row_count: Some(session.row_count),
            duration,
            instruction_throughput: Some(instruction_throughput),
            ..Default::default()
        });
    }

    fn composite(&mut self, args: &Args) {
        let hashfn = "poseidon2";
        let opts = ProverOpts::all_po2s().with_hashfn(hashfn.to_string());
        let prover = get_prover_server(&opts).unwrap();

        for (po2, iterations) in CYCLES_PO2_ITERS
            .iter()
            .take(args.max_po2 - MIN_CYCLES_PO2 + 1)
        {
            let expected = 1 << po2;
            println!("rv32im/{hashfn}: {expected}");

            let env = ExecutorEnv::builder()
                .segment_limit_po2(args.max_po2 as u32)
                .write_slice(&iterations.to_le_bytes())
                .build()
                .unwrap();

            tracker().lock().unwrap().reset();

            let start = Instant::now();
            let info = black_box(prover.prove(env, &LOOP_ELF).unwrap());
            let duration = start.elapsed();

            let ram = tracker().lock().unwrap().peak as u64;
            assert_eq!(
                info.stats.row_count, expected,
                "actual vs expected for po2={po2}"
            );
            let instruction_throughput = (info.stats.insn_count as f64) / duration.as_secs_f64();
            let row_throughput = (info.stats.row_count as f64) / duration.as_secs_f64();
            let seal = info.receipt.inner.composite().unwrap().seal_size() as u64;

            self.results.push(PerformanceData {
                name: "rv32im".into(),
                hashfn: Some(hashfn.into()),
                row_count: Some(info.stats.row_count),
                instruction_count: Some(info.stats.insn_count),
                duration,
                ram: Some(ram),
                seal: Some(seal),
                row_throughput: Some(row_throughput),
                instruction_throughput: Some(instruction_throughput),
            });
        }
    }

    fn lift(&mut self) {
        println!("lift");

        let opts = ProverOpts::all_po2s();
        let ctx = VerifierContext::default();
        let prover = get_prover_server(&opts).unwrap();

        let env = ExecutorEnv::builder()
            .write_slice(&0u32.to_le_bytes())
            .build()
            .unwrap();

        let session = execute_elf(env, &LOOP_ELF).unwrap();
        let segment = session.segments[0].resolve().unwrap();
        let receipt = prover.prove_segment(&ctx, &segment).unwrap();

        tracker().lock().unwrap().reset();

        let start = Instant::now();
        let receipt = black_box(prover.lift(&receipt).unwrap());
        let duration = start.elapsed();

        let ram = tracker().lock().unwrap().peak as u64;
        let row_count = 1 << RECURSION_PO2;
        let row_throughput = (row_count as f64) / duration.as_secs_f64();
        let seal = receipt.seal_size() as u64;

        self.results.push(PerformanceData {
            name: "lift".into(),
            hashfn: Some(opts.hashfn),
            row_count: Some(row_count),
            duration,
            ram: Some(ram),
            seal: Some(seal),
            row_throughput: Some(row_throughput),
            ..Default::default()
        });
    }

    fn join(&mut self) {
        println!("join");

        let opts = ProverOpts::all_po2s();
        let ctx = VerifierContext::default();
        let prover = get_prover_server(&opts).unwrap();

        let (po2, iters) = CYCLES_PO2_ITERS[0];

        let env = ExecutorEnv::builder()
            .write_slice(&iters.to_le_bytes())
            .segment_limit_po2(po2 - 1)
            .build()
            .unwrap();
        let session = execute_elf(env, &LOOP_ELF).unwrap();
        assert!(session.segments.len() >= 2, "rows: {}", session.row_count);

        let receipt = prover.prove_session(&ctx, &session).unwrap().receipt;
        let composite = receipt.inner.composite().unwrap();
        let left = prover.lift(&composite.segments[0]).unwrap();
        let right = prover.lift(&composite.segments[1]).unwrap();

        tracker().lock().unwrap().reset();

        let start = Instant::now();
        let receipt = black_box(prover.join(&left, &right).unwrap());
        let duration = start.elapsed();

        let ram = tracker().lock().unwrap().peak as u64;
        let row_count = 1 << RECURSION_PO2;
        let row_throughput = (row_count as f64) / duration.as_secs_f64();
        let seal = receipt.seal_size() as u64;

        self.results.push(PerformanceData {
            name: "join".into(),
            hashfn: Some(opts.hashfn),
            row_count: Some(row_count),
            duration,
            ram: Some(ram),
            seal: Some(seal),
            row_throughput: Some(row_throughput),
            ..Default::default()
        });
    }

    fn succinct(&mut self) {
        println!("succinct");

        let opts = ProverOpts::all_po2s().with_receipt_kind(ReceiptKind::Succinct);
        let prover = get_prover_server(&opts).unwrap();

        let iterations: u32 = 64 * 1024;
        let env = ExecutorEnv::builder()
            .write_slice(&iterations.to_le_bytes())
            .build()
            .unwrap();

        tracker().lock().unwrap().reset();

        let start = Instant::now();
        let info = prover.prove(env, &LOOP_ELF).unwrap();
        let duration = start.elapsed();

        let ram = tracker().lock().unwrap().peak as u64;
        let row_throughput = (info.stats.row_count as f64) / duration.as_secs_f64();
        let seal = info.receipt.inner.succinct().unwrap().seal_size() as u64;

        self.results.push(PerformanceData {
            name: "succinct".into(),
            hashfn: Some(opts.hashfn),
            row_count: Some(info.stats.row_count),
            duration,
            ram: Some(ram),
            seal: Some(seal),
            row_throughput: Some(row_throughput),
            ..Default::default()
        });
    }

    fn identity_p254(&mut self) {
        println!("identity_p254");

        let opts = ProverOpts::all_po2s().with_receipt_kind(ReceiptKind::Succinct);
        let prover = get_prover_server(&opts).unwrap();

        let env = ExecutorEnv::builder()
            .write_slice(&0u32.to_le_bytes())
            .build()
            .unwrap();

        let info = prover.prove(env, &LOOP_ELF).unwrap();
        let succinct_receipt = info.receipt.inner.succinct().unwrap();

        tracker().lock().unwrap().reset();

        let start = Instant::now();
        let receipt = black_box(risc0_zkvm::recursion::identity_p254(succinct_receipt).unwrap());
        let duration = start.elapsed();

        let ram = tracker().lock().unwrap().peak as u64;
        let row_count = 1 << RECURSION_PO2;
        let row_throughput = (row_count as f64) / duration.as_secs_f64();
        let seal = receipt.seal_size() as u64;

        self.results.push(PerformanceData {
            name: "identity_p254".into(),
            hashfn: Some(opts.hashfn),
            row_count: Some(row_count),
            duration,
            ram: Some(ram),
            seal: Some(seal),
            row_throughput: Some(row_throughput),
            ..Default::default()
        });
    }

    #[cfg(any(feature = "docker", feature = "cuda"))]
    fn shrink_wrap(&mut self) {
        println!("shrink_wrap");

        let opts = ProverOpts::all_po2s().with_receipt_kind(ReceiptKind::Succinct);
        let prover = get_prover_server(&opts).unwrap();

        let env = ExecutorEnv::builder()
            .write_slice(&0u32.to_le_bytes())
            .build()
            .unwrap();

        let info = prover.prove(env, &LOOP_ELF).unwrap();
        let succinct_receipt = info.receipt.inner.succinct().unwrap();
        let receipt = risc0_zkvm::recursion::identity_p254(succinct_receipt).unwrap();
        let seal_bytes = receipt.get_seal_bytes();

        let start = Instant::now();
        let seal = black_box(risc0_groth16::prove::shrink_wrap(&seal_bytes).unwrap());
        let duration = start.elapsed();

        let row_count = 1 << RECURSION_PO2;
        let row_throughput = (row_count as f64) / duration.as_secs_f64();
        let encoded = bincode::serialize(&seal).unwrap();

        self.results.push(PerformanceData {
            name: "shrink_wrap".into(),
            hashfn: Some(opts.hashfn),
            row_count: Some(row_count),
            duration,
            seal: Some(encoded.len() as u64),
            row_throughput: Some(row_throughput),
            ..Default::default()
        });
    }

    #[cfg(any(feature = "docker", feature = "cuda"))]
    fn groth16(&mut self) {
        println!("groth16");

        let opts = ProverOpts::all_po2s().with_receipt_kind(ReceiptKind::Groth16);
        let prover = get_prover_server(&opts).unwrap();

        let iterations: u32 = 64 * 1024;
        let env = ExecutorEnv::builder()
            .write_slice(&iterations.to_le_bytes())
            .build()
            .unwrap();

        tracker().lock().unwrap().reset();

        let start = Instant::now();
        let info = prover.prove(env, &LOOP_ELF).unwrap();
        let duration = start.elapsed();

        let ram = tracker().lock().unwrap().peak as u64;
        let row_throughput = (info.stats.row_count as f64) / duration.as_secs_f64();
        let seal = info.receipt.inner.groth16().unwrap().seal_size() as u64;

        self.results.push(PerformanceData {
            name: "groth16".into(),
            hashfn: Some(opts.hashfn),
            row_count: Some(info.stats.row_count),
            duration,
            ram: Some(ram),
            seal: Some(seal),
            row_throughput: Some(row_throughput),
            ..Default::default()
        });
    }

    fn bigint2_execute(&mut self) -> Session {
        println!("bigint2_execute");

        let env = ExecutorEnv::builder().build().unwrap();

        let start = Instant::now();
        let session = execute_elf(env, BIGINT2_ELF).unwrap();
        let duration = start.elapsed();

        let instruction_throughput = (session.insn_count as f64) / duration.as_secs_f64();
        self.results.push(PerformanceData {
            name: "bigint2_execute".into(),
            instruction_count: Some(session.insn_count),
            row_count: Some(session.row_count),
            duration,
            instruction_throughput: Some(instruction_throughput),
            ..Default::default()
        });

        session
    }

    fn bigint2_prove_segment(&mut self, session: &Session, segment: &Segment) {
        println!("bigint2_prove_segment");

        let opts = ProverOpts::default();
        let prover = get_prover_server(&opts).unwrap();
        let vctx = VerifierContext::default();

        tracker().lock().unwrap().reset();

        let start = Instant::now();
        prover.prove_segment(&vctx, segment).unwrap();

        let duration = start.elapsed();
        let ram = tracker().lock().unwrap().peak as u64;

        let row_throughput = (session.row_count as f64) / duration.as_secs_f64();
        let instruction_throughput = (session.insn_count as f64) / duration.as_secs_f64();
        self.results.push(PerformanceData {
            name: "bigint2_prove_segment".into(),
            hashfn: Some(opts.hashfn),
            row_count: Some(session.row_count),
            instruction_count: Some(session.insn_count),
            duration,
            ram: Some(ram),
            row_throughput: Some(row_throughput),
            instruction_throughput: Some(instruction_throughput),
            ..Default::default()
        });
    }

    fn bigint2(&mut self) {
        let session = self.bigint2_execute();
        let segment = session.segments[0].resolve().unwrap();
        self.bigint2_prove_segment(&session, &segment);
    }

    fn warmup(&self) {
        println!("warmup");

        #[cfg(gpu_accel)]
        {
            let opts = ProverOpts::all_po2s().with_receipt_kind(ReceiptKind::Succinct);
            let prover = get_prover_server(&opts).unwrap();

            let env = ExecutorEnv::builder()
                .write_slice(&0u32.to_le_bytes())
                .build()
                .unwrap();
            prover.prove(env, &LOOP_ELF).unwrap();
        }

        let env = ExecutorEnv::builder()
            .write_slice(&ITERATIONS_FULL_PO2_20_SEGMENT.to_le_bytes())
            .build()
            .unwrap();
        execute_elf(env, &LOOP_ELF).unwrap();
    }
}

#[cfg_attr(gpu_accel, gpu_guard::gpu_guard)]
fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    Datasheet::default().run(Args::parse());
}

/// Utilities to make data human-readable for displaying in a table.
mod display {
    use std::time::Duration;

    use human_repr::{HumanCount, HumanDuration};

    pub fn bytes(bytes: &Option<u64>) -> String {
        if let Some(bytes) = bytes {
            bytes.human_count_bytes().to_string()
        } else {
            "N/A".into()
        }
    }

    pub fn n(count: &Option<u64>) -> String {
        if let Some(count) = count {
            count.human_count_bare().to_string()
        } else {
            "N/A".into()
        }
    }

    pub fn str(s: &Option<String>) -> String {
        s.clone().unwrap_or("N/A".into())
    }

    pub fn duration(duration: &Duration) -> String {
        duration.human_duration().to_string()
    }

    pub fn hertz(hertz: &Option<f64>) -> String {
        if let Some(hertz) = hertz {
            hertz.human_count("Hz").to_string()
        } else {
            "N/A".into()
        }
    }
}
