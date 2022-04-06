#define accum() RegisterGroup::Accum
#define code() RegisterGroup::Code
#define data() RegisterGroup::Data

// This file is machine generated.

use lazy_static::lazy_static;
use crate::taps::{Register, RegisterGroup, Taps, Combo};

lazy_static !{
  static ref RISCV_TAPS : Taps = {Taps{
    registers : vec ![
#define TAPS
#define offset_begin(base, off) Register{ group: base(), offset: off, back: vec![
#define tap(base, off, back) back,
#define offset_end(base, off, combo) ], combo_id: combo                                            \
  }                                                                                                \
  ,
#include "risc0/zkvm/circuit/step.cpp.inc"
  ],
    combos : vec ![
#undef TAPS
#define COMBOS
#define combo_begin(id) Combo { back: vec![
#define tap(back) back,
#define combo_end(id) ],                                                                           \
  }                                                                                                \
  ,
#include "risc0/zkvm/circuit/step.cpp.inc"
  ],
  }};
}
#undef TAPS
