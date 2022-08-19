// A basic fibonacci circuit for use in testing

// This code is automatically generated

mod poly_ext;
mod poly_fp;
mod step_accum;
mod step_exec;
mod step_verify;
mod taps;

use crate::{
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
        1
    }

    #[rustfmt::skip]
    fn mix_size(&self) -> usize {
        1
    }
}

#[cfg(test)]
mod test {
    use super::taps;
    use crate::taps::{TapSet, TapSetOwned};

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
