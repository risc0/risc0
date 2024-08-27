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

use std::{
    hint::black_box,
    path::PathBuf,
    time::{Duration, Instant},
};

use ::serde::Serialize;
use anyhow::Result;
use clap::ValueEnum;
use risc0_zkp::MAX_CYCLES_PO2;
use risc0_zkvm::{
    ApiClient, Asset, AssetRequest, ExecutorEnv, ExecutorEnvBuilder, ProveInfo, ProverOpts,
    ReceiptClaim, ReceiptKind, SegmentInfo, SessionInfo, SuccinctReceipt, VerifierContext,
    RECURSION_PO2,
};
use serde_with::{serde_as, DurationSeconds};
use tabled::{settings::Style, Table, Tabled};

/// `cargo risczero datasheet`
#[derive(clap::Parser)]
#[non_exhaustive]
pub struct Datasheet {
    /// Filter which benchmarks to run.
    #[arg(name = "BENCHMARKS")]
    pub filter: Vec<Benchmark>,

    /// Path to the RISC Zero server.
    #[arg(long, value_name = "PATH", env = "RISC0_SERVER_PATH")]
    pub r0vm: Option<PathBuf>,

    /// Path to the JSON results file.
    #[arg(long, value_name = "PATH")]
    pub json: Option<PathBuf>,

    /// Max size for composite runs.
    #[arg(long, default_value_t = 20, value_parser = parse_po2)]
    pub max_po2: u32,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, ValueEnum)]
#[non_exhaustive]
#[clap(rename_all = "snake_case")]
pub enum Benchmark {
    Execute,
    Rv32im,
    Lift,
    Join,
    Succinct,
    IdentityP254,
}

/// Pre-compiled program that simply loops `count: u32` times (read from stdin).
const LOOP_ELF: &[u8] = include_bytes!("loop.bin");

/// Powers-of-two for cycles, paired with the number of loop iterations used to
/// achieve that many cycles.
const CYCLES_PO2_ITERS: &[(u32, u32)] = &[
    (15, 1),               // 15, 32K
    (16, 1024 * 8),        // 16, 64K
    (17, 1024 * 32),       // 17, 128K
    (18, 1024 * 64),       // 18, 256K
    (19, 1024 * 128),      // 19, 512K
    (20, 1024 * 256),      // 20, 1M
    (21, 1024 * 256 * 3),  // 21, 2M
    (22, 1024 * 256 * 7),  // 22, 4M
    (23, 1024 * 256 * 15), // 23, 8M
    (24, 1024 * 256 * 31), // 24, 16M
];

const MIN_CYCLES_PO2: u32 = CYCLES_PO2_ITERS[0].0;

fn parse_po2(s: &str) -> Result<u32, String> {
    let po2 = s.parse().map_err(|_| format!("`{s}` must be an integer"))?;

    if (MIN_CYCLES_PO2..=MAX_CYCLES_PO2 as u32).contains(&po2) {
        Ok(po2)
    } else {
        Err(format!(
            "po2 must be in range: {MIN_CYCLES_PO2}-{MAX_CYCLES_PO2}"
        ))
    }
}

impl Datasheet {
    /// Returns which benchmarks the user has chosen to run.
    ///
    /// Each benchmark is provided at most once in enum case order.
    fn benchmarks(&self) -> impl Iterator<Item = Benchmark> + '_ {
        Benchmark::value_variants()
            .iter()
            .filter(|benchmark| self.filter.is_empty() || self.filter.contains(benchmark))
            .copied()
    }

    /// Creates a connection to the zkVM server (`r0vm` executable).
    ///
    /// The path is provided by `--r0vm`, `$RISC0_SERVER_PATH`, or searching
    /// `$PATH`.
    fn connect_to_server(&self) -> Result<ApiClient> {
        if let Some(server_path) = &self.r0vm {
            ApiClient::new_sub_process(server_path)
        } else {
            ApiClient::from_env()
        }
    }

    pub fn run(&self) -> Result<()> {
        let client = self.connect_to_server()?;

        // Run warmup prior to proving to ensure GPU kernels are compiled and
        // ready to use.
        println!("warmup");
        _ = black_box(util::prove(
            &client,
            &util::loop_env(0)?,
            LOOP_ELF,
            &ProverOpts::all_po2s().with_receipt_kind(ReceiptKind::Succinct),
        )?);

        let mut data = Vec::new();

        for benchmark in self.benchmarks() {
            match benchmark {
                Benchmark::Rv32im => {
                    for hashfn in ["sha-256", "poseidon2"] {
                        for &(po2, iters) in CYCLES_PO2_ITERS
                            .iter()
                            .filter(|(po2, _)| *po2 <= self.max_po2)
                        {
                            data.push(benches::rv32im(&client, hashfn, iters, po2)?);
                        }
                    }
                }

                Benchmark::Execute => data.push(benches::execute(&client, 128 * 1024)?),
                Benchmark::Succinct => data.push(benches::succinct(&client, 64 * 1024)?),
                Benchmark::Lift => data.push(benches::lift(&client)?),
                Benchmark::Join => data.push(benches::join(&client)?),
                Benchmark::IdentityP254 => data.push(benches::identity_p254(&client)?),
            }
        }

        // Emit results to stdout as pretty table.
        println!("{}", Table::new(&data).with(Style::modern()));

        // Emit results to path as JSON if requested.
        if let Some(json_path) = &self.json {
            let json = serde_json::to_string_pretty(&data)?;

            if let Some(json_dir) = json_path.parent() {
                std::fs::create_dir_all(json_dir)?;
            }

            std::fs::write(json_path, json)?;
        }

        Ok(())
    }
}

// TODO: Emit RAM use.
#[serde_as]
#[derive(Debug, Serialize, Tabled)]
struct BenchmarkData {
    name: &'static str,
    hashfn: String,

    /// Cycles per second.
    #[tabled(display_with = "display::hertz")]
    throughput: f64,

    #[serde_as(as = "DurationSeconds")]
    #[tabled(display_with = "display::duration")]
    duration: Duration,

    /// Either user execution cycle count or the total cycle count.
    ///
    /// When this is the total cycle count, it includes overhead associated with
    /// continuations and padding up to the nearest power of 2.
    #[tabled(display_with = "display::cycles")]
    cycles: u64,

    #[tabled(display_with = "display::bytes")]
    seal: u64,
}

mod util {
    use super::*;

    pub fn execute(client: &ApiClient, env: &ExecutorEnv, elf: &[u8]) -> Result<SessionInfo> {
        execute_with_segments(client, env, elf, |_, _| Ok(()))
    }

    pub fn execute_with_segments<F>(
        client: &ApiClient,
        env: &ExecutorEnv,
        elf: &[u8],
        segment_callback: F,
    ) -> Result<SessionInfo>
    where
        F: FnMut(SegmentInfo, Asset) -> Result<()>,
    {
        let binary = Asset::Inline(elf.to_vec().into());
        let segments_out = AssetRequest::Inline;
        client.execute(env, binary, segments_out, segment_callback)
    }

    pub fn prove(
        client: &ApiClient,
        env: &ExecutorEnv,
        elf: &[u8],
        opts: &ProverOpts,
    ) -> Result<ProveInfo> {
        let image_id = risc0_zkvm::compute_image_id(elf)?;
        let binary = risc0_zkvm::Asset::Inline(elf.to_vec().into());
        let prove_info = client.prove(env, opts, binary)?;

        let ctx = VerifierContext::all_po2s();
        if opts.prove_guest_errors {
            prove_info.receipt.verify_integrity_with_context(&ctx)?;
        } else {
            prove_info.receipt.verify_with_context(&ctx, image_id)?;
        }

        Ok(prove_info)
    }

    pub fn loop_env<'a>(iters: u32) -> Result<ExecutorEnv<'a>> {
        loop_env_builder(iters).build()
    }

    pub fn loop_env_builder<'a>(iters: u32) -> ExecutorEnvBuilder<'a> {
        let mut builder = ExecutorEnvBuilder::default();
        builder.write_slice(&iters.to_le_bytes());
        builder
    }
}

/// Benchmark implementations.
mod benches {
    use risc0_zkvm::InnerReceipt;

    use super::*;

    const RECURSION_CYCLES: u64 = 1 << RECURSION_PO2;

    pub fn execute(client: &ApiClient, iters: u32) -> Result<BenchmarkData> {
        println!("execute: {iters}");

        let env = util::loop_env(iters)?;
        let (session, duration) = try_time(|| util::execute(client, &env, LOOP_ELF))?;

        // NOTE: We use user cycles as the total because there is no proving.
        let cycles = session.cycles();

        Ok(BenchmarkData {
            name: "execute",
            hashfn: "N/A".into(),
            throughput: cycles as f64 / duration.as_secs_f64(),
            duration,
            cycles,
            seal: 0,
        })
    }

    pub fn rv32im(client: &ApiClient, hashfn: &str, iters: u32, po2: u32) -> Result<BenchmarkData> {
        let expected_cycles = 1u64 << po2;
        println!("rv32im ({hashfn}): {expected_cycles}");

        let opts = ProverOpts::all_po2s().with_hashfn(hashfn.to_string());
        let env = util::loop_env_builder(iters)
            .segment_limit_po2(po2)
            .build()?;

        let (info, duration) = try_time(|| util::prove(client, &env, LOOP_ELF, &opts))?;

        let cycles = info.stats.total_cycles;
        assert_eq!(
            cycles, expected_cycles,
            "Incorrect cycle count for po2={po2}"
        );

        Ok(BenchmarkData {
            name: "rv32im",
            hashfn: hashfn.into(),
            seal: info.receipt.inner.composite()?.seal_size() as u64,
            throughput: cycles as f64 / duration.as_secs_f64(),
            duration,
            cycles,
        })
    }

    pub fn succinct(client: &ApiClient, iters: u32) -> Result<BenchmarkData> {
        println!("succinct: {iters}");

        let opts = ProverOpts::all_po2s().with_receipt_kind(ReceiptKind::Succinct);
        let env = util::loop_env(iters)?;
        let (info, duration) = try_time(|| util::prove(client, &env, LOOP_ELF, &opts))?;

        let cycles = info.stats.total_cycles;

        Ok(BenchmarkData {
            name: "succinct",
            hashfn: opts.hashfn,
            seal: info.receipt.inner.succinct()?.seal_size() as u64,
            throughput: cycles as f64 / duration.as_secs_f64(),
            duration,
            cycles,
        })
    }

    pub fn lift(client: &ApiClient) -> Result<BenchmarkData> {
        println!("lift");

        let env = util::loop_env(0)?;
        let opts = ProverOpts::all_po2s();

        let segment: Asset = {
            let mut segment_count = 0;
            let mut segment = None::<Asset>;

            util::execute_with_segments(client, &env, LOOP_ELF, |_, next_segment| {
                segment_count += 1;
                segment = Some(next_segment);
                Ok(())
            })?;

            assert_eq!(segment_count, 1);
            segment.unwrap()
        };

        let receipt = client.prove_segment(&opts, segment, AssetRequest::Inline)?;

        let (receipt, duration) =
            try_time(|| client.lift(&opts, receipt.try_into()?, AssetRequest::Inline))?;

        let cycles = RECURSION_CYCLES;

        Ok(BenchmarkData {
            name: "lift",
            hashfn: opts.hashfn,
            seal: receipt.seal_size() as u64,
            throughput: cycles as f64 / duration.as_secs_f64(),
            duration,
            cycles,
        })
    }

    pub fn join(client: &ApiClient) -> Result<BenchmarkData> {
        println!("join");

        // NOTE: Using too few iters results in error "segment limit too small
        // for instruction".
        let (po2, iters) = CYCLES_PO2_ITERS[1];

        let opts = ProverOpts::all_po2s();
        let env = util::loop_env_builder(iters)
            .segment_limit_po2(po2 - 1)
            .build()?;

        let prove_segment = |segment| -> Result<SuccinctReceipt<ReceiptClaim>> {
            let receipt = client.prove_segment(&opts, segment, AssetRequest::Inline)?;
            client.lift(&opts, receipt.try_into()?, AssetRequest::Inline)
        };

        let [left_segment, right_segment]: [Asset; 2] = {
            let mut segments = Vec::new();
            util::execute_with_segments(client, &env, LOOP_ELF, |_, segment| {
                segments.push(segment);
                Ok(())
            })?;

            assert!(segments.len() >= 2);
            let mut segments = segments.into_iter();
            [segments.next().unwrap(), segments.next().unwrap()]
        };

        let left_receipt = prove_segment(left_segment)?;
        let right_receipt = prove_segment(right_segment)?;

        let (receipt, duration) = try_time(|| {
            client.join(
                &opts,
                left_receipt.try_into()?,
                right_receipt.try_into()?,
                AssetRequest::Inline,
            )
        })?;

        let cycles = RECURSION_CYCLES;

        Ok(BenchmarkData {
            name: "join",
            hashfn: opts.hashfn,
            throughput: cycles as f64 / duration.as_secs_f64(),
            seal: receipt.seal_size() as u64,
            cycles,
            duration,
        })
    }

    pub fn identity_p254(client: &ApiClient) -> Result<BenchmarkData> {
        println!("identity_p254");

        let opts = ProverOpts::all_po2s().with_receipt_kind(ReceiptKind::Succinct);
        let info = util::prove(client, &util::loop_env(0)?, LOOP_ELF, &opts)?;

        let InnerReceipt::Succinct(receipt) = info.receipt.inner else {
            unreachable!();
        };

        let (receipt, duration) =
            try_time(|| client.identity_p254(&opts, receipt.try_into()?, AssetRequest::Inline))?;

        let cycles = RECURSION_CYCLES;
        let throughput = cycles as f64 / duration.as_secs_f64();

        Ok(BenchmarkData {
            name: "identity_p254",
            hashfn: opts.hashfn,
            seal: receipt.seal_size() as u64,
            throughput,
            cycles,
            duration,
        })
    }

    /// Measures the duration for executing `operation` once.
    fn time<T>(mut operation: impl FnOnce() -> T) -> (T, Duration) {
        // Make inputs opaque to the optimizer.
        operation = black_box(operation);

        let start = Instant::now();
        let mut output = operation();
        let duration = start.elapsed();

        // Make optimizer believe output is used.
        output = black_box(output);

        (output, duration)
    }

    /// Measures the duration for executing a fallible `operation` once.
    fn try_time<T>(operation: impl FnOnce() -> Result<T>) -> Result<(T, Duration)> {
        let (result, duration) = time(operation);
        Ok((result?, duration))
    }
}

/// Utilities to make data human-readable for displaying in a table.
mod display {
    use human_repr::*;

    use super::*;

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
