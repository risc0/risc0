// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use clap::Parser;
use risc0_bigint2_methods::RSA_ELF;
use risc0_zkvm::{ExecutorEnv, default_prover};

#[derive(Parser)]
struct Args {
    /// Enable puffin
    #[arg(long, short)]
    puffin: bool,
}

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    let args = Args::parse();

    if args.puffin {
        puffin::set_scopes_on(true);
        let server_addr = format!("0.0.0.0:{}", puffin_http::DEFAULT_PORT);
        println!("Puffin server: {server_addr}");
        let _puffin_server = puffin_http::Server::new(&server_addr).unwrap();

        println!("Press enter to start");
        let mut buf = String::new();
        std::io::stdin().read_line(&mut buf).unwrap();
        println!("proving rsa...");
    }

    let env = ExecutorEnv::builder().build().unwrap();
    let prover = default_prover();
    prover.prove(env, RSA_ELF).unwrap();

    if args.puffin {
        puffin::GlobalProfiler::lock().new_frame();
    }
}
