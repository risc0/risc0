#![no_main]
// If you want to try std support, also update the guest Cargo.toml file
// #![no_std]  // std support is experimental

use prorata_core::{allocate_for_csv, AllocationQuery, AllocationQueryResult};
use risc0_zkvm::guest::env;
use rust_decimal::Decimal;

risc0_zkvm::guest::entry!(main);

pub fn main() {
    // load the amount, recipients, and target user from the environment
    let query: AllocationQuery = env::read();

    // use allocate_for() to compute the allocation for the requested target
    // recipient
    let result: AllocationQueryResult =
        allocate_for_csv(query.amount, query.recipients_csv, &query.target);

    // commit the allocation and query to the journal
    env::commit(&result);
}
