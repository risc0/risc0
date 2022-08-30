extern crate alloc;
use alloc::vec::Vec;

use serde::{Deserialize, Serialize};

// Benchmark support structures for communication between host and guest.
#[derive(Serialize, Deserialize, Debug, Clone)]
pub enum BenchmarkSpec {
    SimpleLoop,
    RawSha {
        buf: Vec<u32>,
    },
    Memcpy {
        src: Vec<u8>,
        src_align: usize,
        dst_align: usize,
    },
    Memset {
        len: usize,
    },
}

#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct SpecWithIters(pub BenchmarkSpec, pub u64);
