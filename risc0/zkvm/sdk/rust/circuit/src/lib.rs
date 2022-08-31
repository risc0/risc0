// This code is automatically generated

#![cfg_attr(not(test), no_std)]

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

pub struct CircuitImpl;

impl CircuitImpl {
    pub fn new() -> Self {
        CircuitImpl
    }
}

impl TapsProvider for CircuitImpl {
    fn get_taps(&self) -> &'static TapSet<'static> {
        taps::TAPSET
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

#[cfg(test)]
mod test {
    use risc0_zkp::taps::{TapSet, TapSetOwned};

    use super::taps;

    #[test]
    fn generated_tapset_matches() {
        let cirgen_generated = taps::TAPSET;
        let rs_generated = TapSetOwned::new(taps::TAPS);

        // TapData includes its own PartialEq implementation which
        // skips some fields, so make sure the debug representation of
        // these two structures are identical.
        assert_eq!(
            format!("{:?}", &TapSet::from(&rs_generated)),
            format!("{:?}", cirgen_generated)
        );
    }
}
