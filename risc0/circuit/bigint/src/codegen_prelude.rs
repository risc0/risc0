// Copyright 2024 RISC Zero, Inc.
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

use tracing::trace;

pub use crate::{byte_poly, BigIntContext, BigIntProgram, WitnessInfo};
pub use anyhow::Result;

pub fn def<const N: usize>(ctx: &mut BigIntContext, label: usize, is_public: usize) -> [i32; N] {
    let val = byte_poly::from_biguint_fixed::<N>(ctx.in_values[label].clone());
    if is_public > 0 {
        ctx.public_witness.push(val.to_vec())
    } else {
        ctx.private_witness.push(val.to_vec())
    }
    trace!(
        "def({label}, {}) -> {}",
        ["private", "public"][is_public],
        byte_poly::dump(val)
    );
    val
}

pub fn nondet_quot<const N: usize>(
    ctx: &mut BigIntContext,
    lhs: impl AsRef<[i32]>,
    rhs: impl AsRef<[i32]>,
) -> [i32; N] {
    let out = byte_poly::nondet_quot_fixed::<N>(lhs.as_ref(), rhs.as_ref());
    trace!("quot: {}", byte_poly::to_biguint(out));
    ctx.private_witness.push(out.to_vec());
    out
}

pub fn nondet_rem<const N: usize>(
    ctx: &mut BigIntContext,
    lhs: impl AsRef<[i32]>,
    rhs: impl AsRef<[i32]>,
) -> [i32; N] {
    let out = byte_poly::nondet_rem_fixed::<N>(lhs.as_ref(), rhs.as_ref());
    trace!("rem: {}", byte_poly::to_biguint(out));
    ctx.private_witness.push(out.to_vec());
    out
}

pub fn nondet_inv<const N: usize>(
    ctx: &mut BigIntContext,
    lhs: impl AsRef<[i32]>,
    rhs: impl AsRef<[i32]>,
) -> [i32; N] {
    let out = byte_poly::nondet_inv_fixed::<N>(lhs.as_ref(), rhs.as_ref());
    trace!("inv: {}", byte_poly::to_biguint(out));
    ctx.private_witness.push(out.to_vec());
    out
}

pub fn eqz(
    ctx: &mut BigIntContext,
    val: impl AsRef<[i32]>,
    carry_offset: usize,
    carry_bytes: usize,
) -> Result<()> {
    trace!(
        "eqz({}, {carry_offset}, {carry_bytes}",
        byte_poly::dump(val.as_ref())
    );
    let evaluated = byte_poly::eval_constraint(val.as_ref(), carry_offset, carry_bytes);
    ctx.private_witness
        .extend(evaluated.into_iter().map(|x| x.to_vec()));
    Ok(())
}

pub fn bigint_make_const<const N: usize>(ctx: &mut BigIntContext, coeffs: [i32; N]) -> [i32; N] {
    ctx.constant_witness.push(coeffs.to_vec());
    coeffs
}

#[macro_export]
macro_rules! bigint_declare_byte_poly {
    {$typename:ident, $n:literal} => {
        type $typename = [i32; $n];
    }
}

#[macro_export]
macro_rules! bigint_program_info {
    ($name: ident, $iters:expr $(, $elems:expr)*) => {
        paste::paste!{
            pub const [<$name:upper _WITNESS_INFO>] : &[WitnessInfo] = &[
                $($elems,)*
            ];
            pub const [<$name:upper>] : BigIntProgram = BigIntProgram{
                name: stringify!($name),
                witness_info: & [<$name:upper _WITNESS_INFO >],
                unconstrained_eval_fn: $name,

                #[cfg(feature = "make_control_ids")]
                control_id: risc0_zkp::core::digest::Digest::ZERO,
                #[cfg(feature = "make_control_ids")]
                control_root: risc0_zkp::core::digest::Digest::ZERO,

                #[cfg(not(feature = "make_control_ids"))]
                control_id: super::control_id::[<$name:upper _CONTROL_ID>],
                #[cfg(not(feature = "make_control_ids"))]
                control_root: super::control_id::[<$name:upper _CONTROL_ROOT>],

                iters: $iters,
            };
        }
    }
}

#[macro_export]
macro_rules! bigint_witness_info {
    ($bits:tt, $label:tt, $public:tt, $min_bits:tt) => {
        WitnessInfo {
            bits: $bits,
            label: $label,
            public: $public,
            min_bits: $min_bits,
        }
    };
}

#[macro_export]
macro_rules! bigint_program_list {
    ($($name:ident),* ) => {
        paste::paste! {
            pub const PROGRAMS : &[&BigIntProgram] = &[
                $(&[< $name:upper >],)*
            ];
        }
    }
}

#[macro_export]
macro_rules! bigint_def {
    ($ctx:tt, $n: literal, $($rest:expr),* ) => {
        def::<$n>($ctx, $($rest,)* )
    }
}

#[macro_export]
macro_rules! bigint_const {
    ($ctx:tt, $($coeff:expr),*) => {
        bigint_make_const($ctx, [ $($coeff,)* ])
    }
}

#[macro_export]
macro_rules! bigint_add {
    ($lhs:expr, $rhs:expr, $n:literal) => {
        $crate::byte_poly::add_fixed::<$n>(&$lhs, &$rhs)
    };
}

#[macro_export]
macro_rules! bigint_sub {
    ($lhs:expr, $rhs:expr, $n:literal) => {
        $crate::byte_poly::sub_fixed::<$n>(&$lhs, &$rhs)
    };
}
#[macro_export]
macro_rules! bigint_mul {
    ($lhs:expr, $rhs:expr, $n:literal) => {
        $crate::byte_poly::mul_fixed::<$n>(&$lhs, &$rhs)
    };
}
#[macro_export]
macro_rules! bigint_nondet_quot {
    ($ctx:tt, $lhs:expr, $rhs:expr, $n:literal) => {
        nondet_quot::<$n>($ctx, &$lhs, &$rhs)
    };
}
#[macro_export]
macro_rules! bigint_nondet_rem {
    ($ctx:tt, $lhs:expr, $rhs:expr, $n:literal) => {
        nondet_rem::<$n>($ctx, &$lhs, &$rhs)
    };
}
#[macro_export]
macro_rules! bigint_nondet_inv {
    ($ctx:tt, $lhs:expr, $rhs:expr, $n:literal) => {
        nondet_inv::<$n>($ctx, &$lhs, &$rhs)
    };
}

// #[macro_export] defines macros in the top level of the crate.
// Re-import them here so they're in local scope.
pub use crate::{
    bigint_add, bigint_const, bigint_declare_byte_poly, bigint_def, bigint_mul, bigint_nondet_inv,
    bigint_nondet_quot, bigint_nondet_rem, bigint_program_info, bigint_program_list, bigint_sub,
    bigint_witness_info,
};
