#![no_main]
// If you want to try std support, also update the guest Cargo.toml file
// #![no_std]  // std support is experimental

use prorata_core::{allocate_for_csv, QueryResult};
use risc0_zkvm::guest::env;
use rust_decimal::Decimal;

risc0_zkvm::guest::entry!(main);

pub fn main() {
    // load the amount, recipients, and target user from the environment
    let amount: Decimal = env::read();
    let recipients_csv: Vec<u8> = env::read();
    let query: String = env::read();

    // use allocate_for() to compute the allocation for the requested recipient
    let result: QueryResult = allocate_for_csv(amount, recipients_csv, &query);

    // commit the allocation and query to the journal
    env::commit(&result);
}
