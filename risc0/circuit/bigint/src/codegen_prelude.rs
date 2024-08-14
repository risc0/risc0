// Copyright (c) 2024 RISC Zero, Inc.
//
// All rights reserved.

pub use crate::byte_poly::BytePoly;
pub use crate::BigIntContext;
pub use crate::{BigIntProgram, WitnessInfo};
pub use anyhow::Result;
use tracing::trace;

pub fn def(
    ctx: &mut BigIntContext,
    coeffs: usize,
    label: usize,
    is_public: usize,
) -> Result<BytePoly> {
    let val = BytePoly::from_biguint(ctx.in_values[label].clone(), coeffs);
    if is_public > 0 {
        ctx.public_witness.push(val.clone())
    } else {
        ctx.private_witness.push(val.clone())
    }
    trace!(
        "def({label}, {}) -> {val:?}",
        ["private", "public"][is_public]
    );
    Ok(val)
}

pub fn nondet_quot(
    ctx: &mut BigIntContext,
    lhs: &BytePoly,
    rhs: &BytePoly,
    coeffs: usize,
) -> Result<BytePoly> {
    let out = lhs.nondet_quot(rhs, coeffs);
    trace!("quot: {out}");
    ctx.private_witness.push(out.clone());
    Ok(out)
}

pub fn nondet_rem(
    ctx: &mut BigIntContext,
    lhs: &BytePoly,
    rhs: &BytePoly,
    coeffs: usize,
) -> Result<BytePoly> {
    let out = lhs.nondet_rem(rhs, coeffs);
    trace!("rem: {out}");
    ctx.private_witness.push(out.clone());
    Ok(out)
}

pub fn add(lhs: &BytePoly, rhs: &BytePoly) -> Result<BytePoly> {
    let out = lhs + rhs;
    trace!("add: {out}");
    Ok(out)
}

pub fn sub(lhs: &BytePoly, rhs: &BytePoly) -> Result<BytePoly> {
    let out = lhs - rhs;
    trace!("sub: {out}");
    Ok(out)
}

pub fn mul(lhs: &BytePoly, rhs: &BytePoly) -> Result<BytePoly> {
    let out = lhs * rhs;
    trace!("mul: {out}");
    Ok(out)
}

pub fn eqz(
    ctx: &mut BigIntContext,
    val: &BytePoly,
    carry_offset: usize,
    carry_bytes: usize,
) -> Result<()> {
    trace!("eqz({val:?}, {carry_offset}, {carry_bytes}");
    let evaluated = val.eval_constraint(carry_offset, carry_bytes);
    ctx.private_witness.extend(evaluated);
    Ok(())
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

// #[macro_export] defines macros in the top level of the crate.
// Re-import them here so they're in local scope.
pub use crate::{bigint_program_info, bigint_program_list, bigint_witness_info};
