// Copyright 2022 Risc0, Inc.
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

#![cfg_attr(not(feature = "std"), no_std)]

#[cfg(feature = "cpp")]
mod cpp;
#[cfg(feature = "cpp")]
mod ffi;
mod info;
mod poly_ext;
mod poly_fp;
mod taps;

use risc0_zkp::{adapter::TapsProvider, taps::TapSet};

pub struct CircuitImpl;

impl CircuitImpl {
    pub const fn new() -> Self {
        CircuitImpl
    }
}

impl TapsProvider for CircuitImpl {
    fn get_taps(&self) -> &'static TapSet<'static> {
        taps::TAPSET
    }
}

#[cfg(test)]
mod test {
    use risc0_zkp::{
        adapter::{CircuitStepContext, CircuitStepExec, CustomStep},
        core::fp::Fp,
        taps::{TapSet, TapSetOwned},
    };

    use super::taps;
    use crate::CircuitImpl;

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

    struct CustomStepMock {}

    impl CustomStep for CustomStepMock {
        fn call(
            &mut self,
            name: &str,
            extra: &str,
            args: &[Fp],
            outs: &mut [Fp],
        ) -> anyhow::Result<()> {
            println!("name: {name}, extra: {extra}, args: {args:?}");
            outs[0] = Fp::new(2);
            Ok(())
        }
    }

    #[test]
    fn step_exec() {
        let circuit = CircuitImpl::new();
        let mut custom = CustomStepMock {};
        let ctx = CircuitStepContext { size: 0, cycle: 0 };
        let mut args0 = vec![Fp::default(); 20];
        let mut args2 = vec![Fp::default(); 20];
        let args: &mut [&mut [Fp]] = &mut [&mut args0, &mut [], &mut args2, &mut [], &mut []];
        circuit.step_exec(&ctx, &mut custom, args).unwrap();
    }
}
