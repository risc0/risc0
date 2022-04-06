use crate::fp::{Fp};
use crate::poly_op::{PolyOp};
use lazy_static::lazy_static;

// This file is machine generated.

#define SIZES
#include "risc0/zkvm/circuit/step.cpp.inc"
#undef SIZES
const RISC0_FP4S : usize = NUM_FP4S;
const RISC0_CONS : usize = NUM_CONS;

lazy_static !{
  static ref RISC0_POLY_OPS : Vec<PolyOp> = vec ![
#define CHECK_EVAL
#define do_const(ov, vv) PolyOp::Const{out : ov, val : Fp::from(vv as u32)},
#define do_get(ov, x, y, z, iv) PolyOp::Get{out : ov, idx : iv},
#define do_get_global(ov, iv) PolyOp::Get{out : ov, idx : iv},
#define do_begin(ov) PolyOp::Begin{out : ov},
#define do_assert_zero(ov, nv, vv, loc) PolyOp::AssertZero{out : ov, orig : nv, val : vv},
#define do_combine(ov, nv, cv, iv, loc) PolyOp::Combine{out : ov, orig : nv, cond : cv, inner : iv},
#define do_add(ov, av, bv) PolyOp::Add{out : ov, a : av, b : bv},
#define do_sub(ov, av, bv) PolyOp::Sub{out : ov, a : av, b : bv},
#define do_mul(ov, av, bv) PolyOp::Mul{out : ov, a : av, b : bv},
#define do_result(vv) PolyOp::Result{val : vv},
#include "risc0/zkvm/circuit/step.cpp.inc"
  ];
}
