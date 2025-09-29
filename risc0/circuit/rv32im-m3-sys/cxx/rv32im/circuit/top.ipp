// Copyright 2025 RISC Zero, Inc.
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

template<typename C>
FDEV void AccumTop<C>::setPhase1(CTX, MDEV Top<C>* top, ValExt<C> z) DEV {
  Val<C> isBigInt =
    top->select.major.bits[size_t(BlockType::BigInt) / MINOR_SPLIT_SIZE].get() * 
    top->select.minor.bits[size_t(BlockType::BigInt) % MINOR_SPLIT_SIZE].get();

  if (isBigInt == Val<C>(1)) {
    polyOp.set(ctx, top->mux.BigInt.data[0].polyOp.get().asUInt32());
    ValExt<C> tot;
    ValExt<C> cur(1);
    for (size_t i = 0; i < 16; i++) {
      tot += cur * top->mux.BigInt.data[0].bytes[i].get();
      cur *= z;
      local.set(ctx, tot);
    }
  } else {
    polyOp.set(ctx, uint32_t(PolyOp::NOP));
    local.set(ctx, ValExt<C>(0));
  }
  if (isSimple()) {
    poly.set(ctx, ValExt<C>(0));
    term.set(ctx, ValExt<C>(1));
    total.set(ctx, ValExt<C>(0));
  }
}

template<typename C>
FDEV bool AccumTop<C>::isSimple() DEV {
  uint32_t polyOpVal = polyOp.get().asUInt32();
  return (polyOpVal == uint32_t(PolyOp::NOP) || polyOpVal == uint32_t(PolyOp::EQZ));
}

template<typename C>
FDEV void AccumTop<C>::setPhase2(CTX, MDEV Top<C>* top, MDEV AccumTop<C>* prev, ValExt<C> z16, ValExt<C> neg) DEV {
  auto polyOpVal = PolyOp(polyOp.get().asUInt32());
  ValExt<C> newPoly = prev->poly.get() + local.get();
  switch(polyOpVal) {
    case PolyOp::NOP:
    case PolyOp::EQZ:
      break;
    case PolyOp::SHIFT:
      poly.set(ctx, newPoly * z16);
      term.set(ctx, prev->term.get());
      total.set(ctx, prev->total.get());
      break;
    case PolyOp::SET_TERM:
      poly.set(ctx, ValExt<C>(0));
      term.set(ctx, newPoly); 
      total.set(ctx, prev->total.get()); 
      break;
    case PolyOp::ADD_TOTAL: {
        Val<C> coeff = top->mux.BigInt.data[0].getCoeff() - Val<C>(4);
        poly.set(ctx, ValExt<C>(0));
        term.set(ctx, ValExt<C>(1)); 
        total.set(ctx, prev->total.get() + prev->term.get() * newPoly * coeff); 
      } 
      break;
    case PolyOp::CARRY_1:
      poly.set(ctx, prev->poly.get() + (local.get() - neg) * Val<C>(16384));
      term.set(ctx, prev->term.get());
      total.set(ctx, prev->total.get());
      break;
    case PolyOp::CARRY_2:
      poly.set(ctx, prev->poly.get() + local.get() * Val<C>(256));
      term.set(ctx, prev->term.get());
      total.set(ctx, prev->total.get());
      break;
  }
}

template<typename C>
FDEV void AccumTop<C>::verify(CTX, MDEV Top<C>* top, MDEV AccumTop<C>* prev, ValExt<C> z) DEV {
  // First, we verify phase 1
  Val<C> isBigInt =
    top->select.major.bits[size_t(BlockType::BigInt) / MINOR_SPLIT_SIZE].get() * 
    top->select.minor.bits[size_t(BlockType::BigInt) % MINOR_SPLIT_SIZE].get();
  Val<C> polyOpGoal = isBigInt * top->mux.BigInt.data[0].polyOp.get();
  // Verify polyOp
  EQ(polyOp.get(), polyOpGoal);
  ValExt<C> cur(1);
  ValExt<C> localGoal;
  ValExt<C> neg;
  for (size_t i = 0; i < 16; i++) {
    localGoal += cur * top->mux.BigInt.data[0].bytes[i].get();
    neg += cur * Val<C>(128);
    cur *= z;
  }
  ValExt<C> z16 = cur;
  localGoal = localGoal * isBigInt;
  // Verify local
  ctx.eqz(localGoal - local.get());
  // Now, we verify phase 2 by computing all conditions and multiply by selector bit
  // This is ugly because we don't really have muxing here
  // First we compute some common values
  ValExt<C> newPoly = prev->poly.get() + local.get();
  Val<C> coeff = top->mux.BigInt.data[0].getCoeff() - Val<C>(4);
  // Now go over branches
#define XEQ(op, lhs, rhs) ctx.eqz(((lhs) - (rhs)) * polyOp.bits[uint32_t(op)].get());
  // PolyOp::NOP
  XEQ(PolyOp::NOP, poly.get(), ValExt<C>(0));
  XEQ(PolyOp::NOP, term.get(), ValExt<C>(1));
  XEQ(PolyOp::NOP, total.get(), ValExt<C>(0));
  // PolyOp::SHIFT
  XEQ(PolyOp::SHIFT, poly.get(), newPoly * z16);
  XEQ(PolyOp::SHIFT, term.get(), prev->term.get());
  XEQ(PolyOp::SHIFT, total.get(), prev->total.get());
  // PolyOp::SET_TERM:
  XEQ(PolyOp::SET_TERM, poly.get(), ValExt<C>(0));
  XEQ(PolyOp::SET_TERM, term.get(), newPoly); 
  XEQ(PolyOp::SET_TERM, total.get(), prev->total.get()); 
  // PolyOp::ADD_TOTAL
  XEQ(PolyOp::ADD_TOTAL, poly.get(), ValExt<C>(0));
  XEQ(PolyOp::ADD_TOTAL, term.get(), ValExt<C>(1)); 
  XEQ(PolyOp::ADD_TOTAL, total.get(), prev->total.get() + prev->term.get() * newPoly * coeff); 
  // PolyOp::CARRY_1
  XEQ(PolyOp::CARRY_1, poly.get(), prev->poly.get() + (local.get() - neg) * Val<C>(16384));
  XEQ(PolyOp::CARRY_1, term.get(), prev->term.get());
  XEQ(PolyOp::CARRY_1, total.get(), prev->total.get());
  // PolyOp::CARRY_2
  XEQ(PolyOp::CARRY_2, poly.get(), prev->poly.get() + local.get() * Val<C>(256));
  XEQ(PolyOp::CARRY_2, term.get(), prev->term.get());
  XEQ(PolyOp::CARRY_2, total.get(), prev->total.get());
  // PolyOp::EQZ
  XEQ(PolyOp::EQZ, poly.get(), ValExt<C>(0));
  XEQ(PolyOp::EQZ, term.get(), ValExt<C>(1));
  XEQ(PolyOp::EQZ, total.get(), ValExt<C>(0));
  XEQ(PolyOp::EQZ, prev->total.get(), newPoly * (ValExt<C>(256) - z));
#undef XEQ
}
