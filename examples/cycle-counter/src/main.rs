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

use std::path::PathBuf;

use clap::{Parser, Subcommand};
use cycle_counter::{examples::*, init_logging, run_jobs};

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Cli {
    // CSV output file
    #[arg(long, value_name = "FILE")]
    out: PathBuf,

    #[command(subcommand)]
    command: Command,
}

#[derive(Eq, PartialEq, Subcommand)]
enum Command {
    All,
    Bevy,
    Chess,
    DigitalSignature,
    Ecdsa,
    HelloWorld,
    Json,
    PasswordChecker,
    Prorata,
    Sha,
    SmartcoreMl,
    Waldo,
    Wasm,
    Wordle,
}

fn main() {
    init_logging();

    let cli = Cli::parse();

    if cli.command == Command::All || cli.command == Command::Bevy {
        run_jobs::<bevy::Job>(&cli.out);
    }

    if cli.command == Command::All || cli.command == Command::Chess {
        run_jobs::<chess::Job>(&cli.out);
    }

    if cli.command == Command::All || cli.command == Command::DigitalSignature {
        run_jobs::<digital_signature::Job>(&cli.out);
    }

    if cli.command == Command::All || cli.command == Command::Ecdsa {
        run_jobs::<ecdsa::Job>(&cli.out);
    }

    if cli.command == Command::All || cli.command == Command::HelloWorld {
        run_jobs::<hello_world::Job>(&cli.out);
    }

    if cli.command == Command::All || cli.command == Command::Json {
        run_jobs::<json::Job>(&cli.out);
    }

    if cli.command == Command::All || cli.command == Command::PasswordChecker {
        run_jobs::<password_checker::Job>(&cli.out);
    }

    if cli.command == Command::All || cli.command == Command::Prorata {
        run_jobs::<prorata::Job>(&cli.out);
    }

    if cli.command == Command::All || cli.command == Command::Sha {
        run_jobs::<sha::Job>(&cli.out);
    }

    if cli.command == Command::All || cli.command == Command::SmartcoreMl {
        run_jobs::<smartcore_ml::Job>(&cli.out);
    }

    if cli.command == Command::All || cli.command == Command::Waldo {
        run_jobs::<waldo::Job>(&cli.out);
    }

    if cli.command == Command::All || cli.command == Command::Wasm {
        run_jobs::<wasm::Job>(&cli.out);
    }

    if cli.command == Command::All || cli.command == Command::Wordle {
        run_jobs::<wordle::Job>(&cli.out);
    }
}
