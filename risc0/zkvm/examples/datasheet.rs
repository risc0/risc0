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
use risc0_circuit_rv32im::{
    MAX_INSN_CYCLES,
    execute::{DEFAULT_SEGMENT_LIMIT_PO2, RESERVED_CYCLES},
};
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
    (14, 1),               // 14, 16K
    (15, 1024 * 8),        // 15, 32K
    (16, 1024 * 16),       // 16, 64K
    (17, 1024 * 32),       // 17, 128K
    (18, 1024 * 96),       // 18, 256K
    (19, 1024 * 128),      // 19, 512K
    (20, 1024 * 256),      // 20, 1M
    (21, 1024 * 256 * 3),  // 21, 2M
    (22, 1024 * 256 * 7),  // 22, 4M
    (23, 1024 * 256 * 15), // 23, 8M
    (24, 1024 * 256 * 31), // 24, 16M
];

const MIN_CYCLES_PO2: usize = CYCLES_PO2_ITERS[0].0 as usize;

/// The number of iterations of the LOOP_ELF needed to fill up a po2=20 segment.
const ITERATIONS_FULL_PO2_20_SEGMENT: usize = 1024 * 495 + 790;

/// The maximum number of cycles in a segment that can be reserved (for fitting the
/// potential next instruction and for lookup table + control when proving)
const RESERVED_CYCLES_MAX: usize = RESERVED_CYCLES + MAX_INSN_CYCLES;

/// Pre-compiled program that simply loops `count: u32` times (read from stdin).
static LOOP_ELF: LazyLock<Vec<u8>> = LazyLock::new(|| {
    const LOOP_ELF: &[u8] = include_bytes!("loop.bin");
    ProgramBinary::new(LOOP_ELF, V1COMPAT_ELF).encode()
});

#[serde_as]
#[derive(Debug, Serialize, Tabled)]
struct PerformanceData {
    name: String,
    hashfn: String,

    /// Cycles per second.
    #[tabled(display = "display::hertz")]
    throughput: f64,

    #[serde_as(as = "DurationNanoSeconds")]
    #[tabled(display = "display::duration")]
    duration: Duration,

    /// Either user execution cycle count or the total cycle count.
    ///
    /// When this is the total cycle count, it includes overhead associated with
    /// continuations and padding up to the nearest power of 2.
    #[tabled(display = "display::cycles")]
    cycles: u64,

    #[tabled(display = "display::bytes")]
    ram: u64,

    #[tabled(display = "display::bytes")]
    seal: u64,
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
    ZethShapella30,
    ZethShapella50,
    ZethShapella100,
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
            Command::ZethShapella30 => self.shapella30(),
            Command::ZethShapella50 => self.shapella50(),
            Command::ZethShapella100 => self.shapella100(),
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
            session.total_cycles
        );
        assert!(
            session.reserved_cycles as usize <= RESERVED_CYCLES_MAX,
            "more room in the segment ({} <= {})",
            session.reserved_cycles,
            RESERVED_CYCLES_MAX
        );

        let throughput = (session.user_cycles as f64) / duration.as_secs_f64();
        self.results.push(PerformanceData {
            name: "execute".into(),
            hashfn: "N/A".into(),
            cycles: session.user_cycles,
            duration,
            ram: 0,
            seal: 0,
            throughput,
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
            assert_eq!(info.stats.total_cycles, expected, "actual vs expected");
            let throughput = (info.stats.total_cycles as f64) / duration.as_secs_f64();
            let seal = info.receipt.inner.composite().unwrap().seal_size() as u64;

            self.results.push(PerformanceData {
                name: "rv32im".into(),
                hashfn: hashfn.into(),
                cycles: info.stats.total_cycles,
                duration,
                ram,
                seal,
                throughput,
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
        let cycles = 1 << RECURSION_PO2;
        let throughput = (cycles as f64) / duration.as_secs_f64();
        let seal = receipt.seal_size() as u64;

        self.results.push(PerformanceData {
            name: "lift".into(),
            hashfn: opts.hashfn,
            cycles,
            duration,
            ram,
            seal,
            throughput,
        });
    }

    fn join(&mut self) {
        println!("join");

        let opts = ProverOpts::all_po2s();
        let ctx = VerifierContext::default();
        let prover = get_prover_server(&opts).unwrap();

        let (po2, iters) = CYCLES_PO2_ITERS[1];

        let env = ExecutorEnv::builder()
            .write_slice(&iters.to_le_bytes())
            .segment_limit_po2(po2 - 1)
            .build()
            .unwrap();
        let session = execute_elf(env, &LOOP_ELF).unwrap();
        assert!(
            session.segments.len() >= 2,
            "cycles: {}",
            session.total_cycles
        );

        let receipt = prover.prove_session(&ctx, &session).unwrap().receipt;
        let composite = receipt.inner.composite().unwrap();
        let left = prover.lift(&composite.segments[0]).unwrap();
        let right = prover.lift(&composite.segments[1]).unwrap();

        tracker().lock().unwrap().reset();

        let start = Instant::now();
        let receipt = black_box(prover.join(&left, &right).unwrap());
        let duration = start.elapsed();

        let ram = tracker().lock().unwrap().peak as u64;
        let cycles = 1 << RECURSION_PO2;
        let throughput = (cycles as f64) / duration.as_secs_f64();
        let seal = receipt.seal_size() as u64;

        self.results.push(PerformanceData {
            name: "join".into(),
            hashfn: opts.hashfn,
            cycles,
            duration,
            ram,
            seal,
            throughput,
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
        let throughput = (info.stats.total_cycles as f64) / duration.as_secs_f64();
        let seal = info.receipt.inner.succinct().unwrap().seal_size() as u64;

        self.results.push(PerformanceData {
            name: "succinct".into(),
            hashfn: opts.hashfn,
            cycles: info.stats.total_cycles,
            duration,
            ram,
            seal,
            throughput,
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
        let cycles = 1 << RECURSION_PO2;
        let throughput = (cycles as f64) / duration.as_secs_f64();
        let seal = receipt.seal_size() as u64;

        self.results.push(PerformanceData {
            name: "identity_p254".into(),
            hashfn: opts.hashfn,
            cycles,
            duration,
            ram,
            seal,
            throughput,
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

        let cycles = 1 << RECURSION_PO2;
        let throughput = (cycles as f64) / duration.as_secs_f64();
        let encoded = bincode::serialize(&seal).unwrap();

        self.results.push(PerformanceData {
            name: "shrink_wrap".into(),
            hashfn: opts.hashfn,
            cycles,
            duration,
            ram: 0,
            seal: encoded.len() as u64,
            throughput,
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
        let throughput = (info.stats.total_cycles as f64) / duration.as_secs_f64();
        let seal = info.receipt.inner.groth16().unwrap().seal_size() as u64;

        self.results.push(PerformanceData {
            name: "groth16".into(),
            hashfn: opts.hashfn,
            cycles: info.stats.total_cycles,
            duration,
            ram,
            seal,
            throughput,
        });
    }

    fn bigint2_execute(&mut self) -> Session {
        println!("bigint2_execute");

        let env = ExecutorEnv::builder().build().unwrap();

        let start = Instant::now();
        let session = execute_elf(env, BIGINT2_ELF).unwrap();
        let duration = start.elapsed();

        let throughput = (session.user_cycles as f64) / duration.as_secs_f64();
        self.results.push(PerformanceData {
            name: "bigint2_execute".into(),
            hashfn: "N/A".into(),
            cycles: session.user_cycles,
            duration,
            ram: 0,
            seal: 0,
            throughput,
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

        let throughput = (session.total_cycles as f64) / duration.as_secs_f64();
        self.results.push(PerformanceData {
            name: "bigint2_prove_segment".into(),
            hashfn: opts.hashfn,
            cycles: session.total_cycles,
            duration,
            ram,
            seal: 0,
            throughput,
        });
    }

    fn bigint2(&mut self) {
        let session = self.bigint2_execute();
        let segment = session.segments[0].resolve().unwrap();
        self.bigint2_prove_segment(&session, &segment);
    }

    fn shapella_segment(&mut self, name: &str, bytes: &[u8]) {
        // "shapella" is the name of ethereum block 17034870
        // this test runs one segment of a zeth run on that block
        println!("{name}");
        let segment = risc0_circuit_rv32im::execute::Segment::decode(bytes).unwrap();

        let start = Instant::now();
        segment.execute().unwrap();
        let duration = start.elapsed();

        let total_cycles = segment.suspend_cycle;
        let throughput = (total_cycles as f64) / duration.as_secs_f64();
        self.results.push(PerformanceData {
            name: name.into(),
            hashfn: "N/A".into(),
            cycles: total_cycles.into(),
            duration,
            ram: 0,
            seal: 0,
            throughput,
        });
    }

    fn shapella30(&mut self) {
        let bytes: &[u8] = include_bytes!("shapella-30.bin");
        self.shapella_segment("zeth_shapella_30", bytes);
    }

    fn shapella50(&mut self) {
        let bytes: &[u8] = include_bytes!("shapella-50.bin");
        self.shapella_segment("zeth_shapella_50", bytes);
    }

    fn shapella100(&mut self) {
        let bytes: &[u8] = include_bytes!("shapella-100.bin");
        self.shapella_segment("zeth_shapella_100", bytes);
    }

    fn warmup(&self) {
        println!("warmup");

        #[cfg(any(feature = "cuda", feature = "metal"))]
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

    pub fn bytes(bytes: &u64) -> String {
        if *bytes == 0 {
            return "N/A".into();
        }
        bytes.human_count_bytes().to_string()
    }

    pub fn cycles(cycles: &u64) -> String {
        cycles.human_count_bare().to_string()
    }

    pub fn duration(duration: &Duration) -> String {
        duration.human_duration().to_string()
    }

    pub fn hertz(hertz: &f64) -> String {
        hertz.human_count("Hz").to_string()
    }
}
