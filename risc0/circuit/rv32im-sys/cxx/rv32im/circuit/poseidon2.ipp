// Copyright 2026 RISC Zero, Inc.
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

FDEV CONSTANT Fp INT_ROUND_CONSTANTS[21] = {
    0x1DA78EC2, 0x730B0924, 0x3EB56CF3, 0x5BD93073, 0x37204C97, 0x51642D89, 0x66E943E8,
    0x1A3E72DE, 0x70BEB1E9, 0x30FF3B3F, 0x4240D1C4, 0x12647B8D, 0x65D86965, 0x49EF4D7C,
    0x47785697, 0x46B3969F, 0x5C7B7A0E, 0x7078FC60, 0x4F22D482, 0x482A9AEE, 0x6BEB839D};

FDEV CONSTANT Fp EXT_ROUND_CONSTANTS[8 * CELLS] = {
    0x0FA20C37, 0x0795BB97, 0x12C60B9C, 0x0EABD88E, 0x096485CA, 0x07093527, 0x1B1D4E50, 0x30A01ACE,
    0x3BD86F5A, 0x69AF7C28, 0x3F94775F, 0x731560E8, 0x465A0ECD, 0x574EF807, 0x62FD4870, 0x52CCFE44,
    0x14772B14, 0x4DEDF371, 0x260ACD7C, 0x1F51DC58, 0x75125532, 0x686A4D7B, 0x54BAC179, 0x31947706,
    0x29799D3B, 0x6E01AE90, 0x203A7A64, 0x4F7E25BE, 0x72503F77, 0x45BD3B69, 0x769BD6B4, 0x5A867F08,
    0x4FDBA082, 0x251C4318, 0x28F06201, 0x6788C43A, 0x4C6D6A99, 0x357784A8, 0x2ABAF051, 0x770F7DE6,
    0x1794B784, 0x4796C57A, 0x724B7A10, 0x449989A7, 0x64935CF1, 0x59E14AAC, 0x0E620BB8, 0x3AF5A33B,
    0x4465CC0E, 0x019DF68F, 0x4AF8D068, 0x08784F82, 0x0CEFDEAE, 0x6337A467, 0x32FA7A16, 0x486F62D6,
    0x386A7480, 0x20F17C4A, 0x54E50DA8, 0x2012CF03, 0x5FE52950, 0x09AFB6CD, 0x2523044E, 0x5C54D0EF,
    0x71C01F3C, 0x60B2C4FB, 0x4050B379, 0x5E6A70A5, 0x418543F5, 0x71DEBE56, 0x1AAD2994, 0x3368A483,
    0x07A86F3A, 0x5EA43FF1, 0x2443780E, 0x4CE444F7, 0x146F9882, 0x3132B089, 0x197EA856, 0x667030C3,
    0x2317D5DC, 0x0C2C48A7, 0x56B2DF66, 0x67BD81E9, 0x4FCDFB19, 0x4BAAEF32, 0x0328D30A, 0x6235760D,
    0x12432912, 0x0A49E258, 0x030E1B70, 0x48CAEB03, 0x49E4D9E9, 0x1051B5C6, 0x6A36DBBE, 0x4CFF27A5,
    0x032959AD, 0x2B18AF6A, 0x55D3DC8C, 0x43BD26C8, 0x0C41595F, 0x7048D2E2, 0x00DB8983, 0x2AF563D7,
    0x6E84758F, 0x611D64E1, 0x1F9977E2, 0x64163A0A, 0x5C5FC27B, 0x02E22561, 0x3A2D75DB, 0x1BA7B71A,
    0x34343F64, 0x7406B35D, 0x19DF8299, 0x6FF4480A, 0x514A81C8, 0x57AB52CE, 0x6AD69F52, 0x3E0C0E0D,
    0x48126114, 0x2A9D62CC, 0x17441F23, 0x485762BB, 0x2F218674, 0x06FDC64A, 0x0861B7F2, 0x3B36EEE6,
    0x70A11040, 0x04B31737, 0x3722A872, 0x2A351C63, 0x623560DC, 0x62584AB2, 0x382C7C04, 0x3BF9EDC7,
    0x0E38FE51, 0x376F3B10, 0x5381E178, 0x3AFC61C7, 0x5C1BCB4D, 0x6643CE1F, 0x2D0AF1C1, 0x08F583CC,
    0x5D6FF60F, 0x6324C1E5, 0x74412FB7, 0x70C0192E, 0x0B72F141, 0x4067A111, 0x57388C4F, 0x351009EC,
    0x0974C159, 0x539A58B3, 0x038C0CFF, 0x476C0392, 0x3F7BC15F, 0x4491DD2C, 0x4D1FEF55, 0x04936AE3,
    0x58214DD4, 0x683C6AAD, 0x1B42F16B, 0x6DC79135, 0x2D4E71EC, 0x3E2946EA, 0x59DCE8DB, 0x6CEE892A,
    0x47F07350, 0x7106CE93, 0x3BD4A7A9, 0x2BFE636A, 0x430011E9, 0x001CD66A, 0x307FAF5B, 0x0D9EF3FE,
    0x6D40043A, 0x2E8F470C, 0x1B6865E8, 0x0C0E6C01, 0x4D41981F, 0x423B9D3D, 0x410408CC, 0x263F0884,
    0x5311BBD0, 0x4DAE58D8, 0x30401CEA, 0x09AFA575, 0x4B3D5B42, 0x63AC0B37, 0x5FE5BB14, 0x5244E9D4,
};

FDEV CONSTANT Fp M_INT_DIAG_HZN[CELLS] = {
    0x409133f0, 0x1667a8a1, 0x06a6c7b6, 0x6f53160e, 0x273b11d1, 0x03176c5d, 0x72f9bbf9, 0x73ceba91,
    0x5cdef81d, 0x01393285, 0x46daee06, 0x065d7ba6, 0x52d72d6f, 0x05dd05e0, 0x3bab4b63, 0x6ada3842,
    0x2fc5fbec, 0x770d61b0, 0x5715aae9, 0x03ef0e90, 0x75b6c770, 0x242adf5f, 0x00d0ca4c, 0x36c0e388};

template <typename C> inline FDEV array<Val<C>, 4> multiply4x4(array<Val<C>, 4> in) {
  Val<C> circ_factor_2 = 2;
  Val<C> circ_factor_4 = 4;
  Val<C> t0 = in[0] + in[1];
  Val<C> t1 = in[2] + in[3];
  Val<C> t2 = circ_factor_2 * in[1] + t1;
  Val<C> t3 = circ_factor_2 * in[3] + t0;
  Val<C> t4 = circ_factor_4 * t1 + t3;
  Val<C> t5 = circ_factor_4 * t0 + t2;
  Val<C> t6 = t3 + t5;
  Val<C> t7 = t2 + t4;
  return {t6, t5, t7, t4};
}

template <typename C> inline FDEV void multiplyByMExt(ValCells<C> in) {
  // Optimized method for multiplication by M_EXT.
  // See appendix B of Poseidon2 paper for additional details.
  ValCells<C> out;
  for (size_t i = 0; i < CELLS; i++) {
    out[i] = 0;
  }
  array<Val<C>, 4> tmpSums;
  for (size_t i = 0; i < CELLS / 4; i++) {
    array<Val<C>, 4> chunk{in[4 * i], in[4 * i + 1], in[4 * i + 2], in[4 * i + 3]};
    chunk = multiply4x4<C>(chunk);
    for (size_t j = 0; j < 4; j++) {
      tmpSums[j] += chunk[j];
      out[4 * i + j] += chunk[j];
    }
  }
  for (size_t i = 0; i < CELLS; i++) {
    in[i] = out[i] + tmpSums[i % 4];
  }
}

template <typename C> FDEV void P2ExtRoundBlock<C>::set(CTX, P2ExtRoundWitness wit) DEV {
  id.set(ctx, wit.id);
  round.set(ctx, wit.round);
  ValCells<C> cells;
  for (size_t i = 0; i < CELLS; i++) {
    Val<C> cur = wit.cells[i];
    inputs[i].set(ctx, cur);
    cur += EXT_ROUND_CONSTANTS[wit.round * CELLS + i];
    Val<C> cur3 = cur * cur * cur;
    sBoxTmp[i].set(ctx, cur3);
    cells[i] = cur3 * cur3 * cur;
  }
  multiplyByMExt<C>(cells);
  for (size_t i = 0; i < CELLS; i++) {
    outputs[i].set(ctx, cells[i]);
  }
}

template <typename C> FDEV void P2ExtRoundBlock<C>::verify(CTX) DEV {
  ValCells<C> cells;
  for (size_t i = 0; i < CELLS; i++) {
    Val<C> cur = inputs[i].get();
    for (size_t r = 0; r < 8; r++) {
      cur += Val<C>(EXT_ROUND_CONSTANTS[r * CELLS + i]) * round.bits[r].get();
    }
    Val<C> computedCur3 = cur * cur * cur;
    Val<C> cur3 = sBoxTmp[i].get();
    ctx.eqz(computedCur3 - cur3);
    cells[i] = cur3 * cur3 * cur;
  }
  multiplyByMExt<C>(cells);
  for (size_t i = 0; i < CELLS; i++) {
    ctx.eqz(cells[i] - outputs[i].get());
  }
}

template <typename C> FDEV void P2ExtRoundBlock<C>::addArguments(CTX) DEV {
  Val<C> idVal = id.get();
  Val<C> roundVal = round.get();
  Val<C> nextRound = 0;
  for (int i = 0; i < 8; i++) {
    if (i == 3) {
      nextRound += Val<C>(9) * round.bits[i].get();
    } else {
      nextRound += Val<C>(i + 1) * round.bits[i].get();
    }
  }

  P2StateArgument<C> state;
  state.id = idVal;
  state.round = roundVal;
  GET_ARR(state.state, inputs, CELLS);
  ctx.pull(state);
  state.round = nextRound;
  GET_ARR(state.state, outputs, CELLS);
  ctx.push(state);
}

template <typename C> inline FDEV void multiplyByMInt(CTX, ValCells<C> in) {
  PICUS_SYNTHESIZE_COMPONENT_BEGIN("multiplyByMInt")

  // Exploit the fact that off-diagonal entries of M_INT are all 1.
  Val<C> sum = 0;
  for (size_t i = 0; i < CELLS; i++) {
    sum += in[i];
  }
  for (size_t i = 0; i < CELLS; i++) {
    in[i] = sum + Val<C>(M_INT_DIAG_HZN[i]) * in[i];
  }

  PICUS_SYNTHESIZE_COMPONENT_END(
      "multiplyByMInt", llvm::ArrayRef(in, CELLS), [&](mlir::Value result) {
        auto loc = ctx.builder.getUnknownLoc();
        for (size_t i = 0; i < CELLS; i++) {
          mlir::Value idx = ctx.builder.template create<zirgen::Zll::ConstOp>(loc, i);
          in[i].value = ctx.builder.template create<zirgen::ZStruct::SubscriptOp>(loc, result, idx);
        }
      })
}

template <typename C> FDEV void P2IntRoundsBlock<C>::set(CTX, P2IntRoundsWitness wit) DEV {
  id.set(ctx, wit.id);
  ValCells<C> cells;
  for (size_t i = 0; i < CELLS; i++) {
    cells[i] = wit.cells[i];
    inputs[i].set(ctx, cells[i]);
  }
  for (size_t i = 0; i < ROUNDS_PARTIAL; i++) {
    Val<C> cur = cells[0] + INT_ROUND_CONSTANTS[i];
    Val<C> cur3 = cur * cur * cur;
    sBoxT1[i].set(ctx, cur3);
    Val<C> cur7 = cur3 * cur3 * cur;
    sBoxT2[i].set(ctx, cur7);
    cells[0] = cur7;
    multiplyByMInt<C>(ctx, cells);
  }
  for (size_t i = 0; i < CELLS; i++) {
    outputs[i].set(ctx, cells[i]);
  }
}

template <typename C> FDEV void P2IntRoundsBlock<C>::verify(CTX) DEV {
  Val<C> cells[CELLS];
  for (size_t i = 0; i < CELLS; i++) {
    cells[i] = inputs[i].get();
  }
  for (size_t i = 0; i < ROUNDS_PARTIAL; i++) {
    Val<C> cur = cells[0] + INT_ROUND_CONSTANTS[i];
    Val<C> cur3 = cur * cur * cur;
    EQ(sBoxT1[i].get(), cur3);
    cur3 = sBoxT1[i].get();
    Val<C> cur7 = cur3 * cur3 * cur;
    EQ(sBoxT2[i].get(), cur7);
    cells[0] = sBoxT2[i].get();
    multiplyByMInt<C>(ctx, cells);
  }
  for (size_t i = 0; i < CELLS; i++) {
    EQ(outputs[i].get(), cells[i]);
  }
}

template <typename C> FDEV void P2IntRoundsBlock<C>::addArguments(CTX) DEV {
  PICUS_INPUT(ctx, id);
  PICUS_INPUT(ctx, inputs);

  Val<C> idVal = id.get();
  P2StateArgument<C> state;
  state.id = idVal;
  state.round = 9;
  GET_ARR(state.state, inputs, CELLS);
  ctx.pull(state);
  state.round = 4;
  GET_ARR(state.state, outputs, CELLS);
  ctx.push(state);
}

template <typename C> FDEV void P2BlockBlock<C>::set(CTX, P2BlockWitness wit) DEV {
  id.set(ctx, wit.id);
  outUseCount.set(ctx, wit.outUseCount);
  contUseCount.set(ctx, wit.contUseCount);
  for (size_t i = 0; i < CELLS; i++) {
    inputs[i].set(ctx, wit.in[i]);
    outputs[i].set(ctx, wit.out[i]);
  }
}

template <typename C> FDEV void P2BlockBlock<C>::addArguments(CTX) DEV {
  Val<C> idVal = id.get();
  ctx.pull(P2IdArgument<C>(idVal));
  ctx.push(P2IdArgument<C>(idVal + 1));
  P2CallArgument<C> callArg;
  callArg.isFinal = 1;
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    callArg.in[i] = inputs[CELLS_RATE + i].get();
  }
  GET_ARR(callArg.data, inputs, CELLS_RATE);
  GET_ARR(callArg.out, outputs, CELLS_DIGEST);
  ctx.addArgument(outUseCount.get(), callArg);
  callArg.isFinal = 0;
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    callArg.out[i] = outputs[CELLS_RATE + i].get();
  }
  ctx.addArgument(contUseCount.get(), callArg);
  ValCells<C> in;
  for (size_t i = 0; i < CELLS; i++) {
    in[i] = inputs[i].get();
  }
  multiplyByMExt<C>(in);
  P2StateArgument<C> state;
  state.id = idVal;
  state.round = 0;
  for (size_t i = 0; i < CELLS; i++) {
    state.state[i] = in[i];
  }
  ctx.push(state);
  state.round = 8;
  GET_ARR(state.state, outputs, CELLS);
  ctx.pull(state);
}
