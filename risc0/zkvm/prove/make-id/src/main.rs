use clap::Parser;

use risc0_zkvm_sys::{make_method_id_from_elf, MethodId, METHOD_ID_LEN};

const DEFAULT_LIMIT: usize = 20;
const MAX_LIMIT: usize = 24;

/// Generates a MethodID for a given RISC-V ELF binary.
#[derive(Parser)]
#[clap(about, version, author)]
struct Args {
    /// The ELF file to compute a MethodID from.
    elf: String,

    /// The resulting MethodID file.
    out: String,

    /// Limit the number of hash table entries to compute.
    #[clap(short, long, default_value_t = DEFAULT_LIMIT)]
    limit: usize,
}

fn main() {
    let args = Args::parse();

    let method_id = make_method_id_from_elf(&args.elf).unwrap();
}
