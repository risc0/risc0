#[macro_use]
extern crate bencher;

use bencher::Bencher;

use core::convert::TryFrom;
use risc0_zkvm_verify::{MethodID, Receipt};
use std::{fs, vec::Vec};

fn receipt(bench: &mut Bencher) {
    let data: Vec<u8> = fs::read("src/simple_receipt.receipt").unwrap();
    let as_u32: Vec<u32> = data
        .chunks(4)
        .map(|bytes| u32::from_le_bytes(<[u8; 4]>::try_from(bytes).unwrap()))
        .collect();
    let receipt: Receipt = risc0_zkvm_serde::from_slice(&as_u32).unwrap();

    let method_id =
        &MethodID::try_from(fs::read("src/simple_receipt.id").unwrap().as_slice()).unwrap();
    bench.iter(|| {
        receipt.verify(method_id);
    })
}

benchmark_group!(benches, receipt);
benchmark_main!(benches);
