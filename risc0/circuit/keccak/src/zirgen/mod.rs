// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

pub(crate) mod info;
pub(crate) mod poly_ext;
pub(crate) mod taps;

use risc0_zkp::{
    adapter::{CircuitCoreDef, TapsProvider},
    field::baby_bear::BabyBear,
    taps::TapSet,
};

pub(crate) struct CircuitImpl;

#[allow(unused)]
#[allow(non_camel_case_types)]
#[allow(non_snake_case)]
pub(crate) mod circuit {
    use risc0_zkp::layout::Reg;

    macro_rules! set_field {
        ($field:ident) => {
            paste::paste! {
                pub type CircuitField = risc0_core::field::[<$field:snake>]::$field;
                pub type Val = <CircuitField as risc0_core::field::Field>::Elem;
                pub type ExtVal = <CircuitField as risc0_core::field::Field>::ExtElem;
                pub type MixState = risc0_zkp::adapter::MixState<ExtVal>;
                pub type PolyMix = ExtVal;
            }
        };
    }

    macro_rules! define_buffer_list {
        (
            all: [ $( $name:ident ,)* ],
            rows: [ $( $rows_name:ident ,)* ],
            taps: [ $( $taps_name:ident ,)* ],
            globals: [ $( $globals_name:ident ,)* ],
        ) => {};
    }

    macro_rules! define_tap_buffer {
        ($name:ident, $size:literal, $reg_group_id:literal) => {
            paste::paste! {
                pub const [< REGCOUNT_ $name:upper >] : usize = $size;
                pub const [< REGISTER_GROUP_ $name:upper >] : usize = $reg_group_id;
            }
        };
    }

    macro_rules! define_global_buffer {
        ($name:ident, $size:literal) => {
            paste::paste! {
                pub const [< REGCOUNT_ $name:upper >] : usize = $size;
            }
        };
    }

    macro_rules! define_buffer {
        ($name:ident, $size:literal) => {
            paste::paste! {
                pub const [< REGCOUNT_ $name:upper >] : usize = $size;
            }
        };
    }

    include! {"types.rs.inc"}
    include! {"defs.rs.inc"}
    include! {"layout.rs.inc"}
}

impl CircuitCoreDef<BabyBear> for CircuitImpl {}

impl TapsProvider for CircuitImpl {
    fn get_taps(&self) -> &'static TapSet<'static> {
        self::taps::TAPSET
    }
}
