// This code is automatically generated

mod poly_ext;
mod poly_fp;
mod step_accum;
mod step_exec;
mod step_verify;
mod taps;

use risc0_zkp::{
    adapter::{CircuitInfo, TapsProvider},
    taps::TapSet,
};

pub struct CircuitImpl {
    taps: TapSet,
}

impl CircuitImpl {
    pub fn new() -> Self {
        CircuitImpl {
            taps: TapSet::new(taps::TAPS),
        }
    }
}

impl TapsProvider for CircuitImpl {
    fn get_taps(&self) -> &TapSet {
        &self.taps
    }
}

impl CircuitInfo for CircuitImpl {
    #[rustfmt::skip]
    fn output_size(&self) -> usize {
        18
    }

    #[rustfmt::skip]
    fn mix_size(&self) -> usize {
        20
    }
}
