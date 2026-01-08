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

#define GLOBAL_SET_U32(member, val)                                                                \
  GLOBAL_SET(member.low, val.low);                                                                 \
  GLOBAL_SET(member.high, val.high)

#define GLOBAL_CHECK_U32(member, val)                                                              \
  EQ(GLOBAL_GET(member.low), val.low);                                                             \
  EQ(GLOBAL_GET(member.high), val.high)

#define VERIFY_DECODE                                                                              \
  DecodeArgument<C> arg;                                                                           \
  arg.iCacheCycle = fetch.iCacheCycle.get();                                                       \
  arg.pcLow = fetch.pc.low.get();                                                                  \
  arg.pcLow = fetch.pc.high.get();                                                                 \
  arg.newPcLow = fetch.nextPc.low.get();                                                           \
  arg.newPcLow = fetch.nextPc.high.get();                                                          \
  arg.rs1 = 0;                                                                                     \
  arg.rs2 = 0;                                                                                     \
  arg.rd = 0;                                                                                      \
  arg.immLow = 0;                                                                                  \
  arg.immHigh = 0;                                                                                 \
  arg.options = Val<C>(uint32_t(INST_ECALL));                                                      \
  ctx.pull(arg);

template <typename C> FDEV void EcallTerminateBlock<C>::set(CTX, EcallTerminateWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  readA7.set(ctx, wit.a7, wit.cycle);
  readA0.set(ctx, wit.a0, wit.cycle);
  readA1.set(ctx, wit.a1, wit.cycle);
  GLOBAL_SET(isTerminate, 1);
  GLOBAL_SET_U32(termA0, readA0.data.get());
  GLOBAL_SET_U32(termA1, readA1.data.get());
  for (size_t i = 0; i < 8; i++) {
    readOutput[i].set(ctx, wit.output[i], wit.cycle);
    GLOBAL_SET_U32(out[i], readOutput[i].data.get());
  }
}

template <typename C> FDEV void EcallTerminateBlock<C>::verify(CTX) DEV {
  // Make sure A7 = HOST_ECALL_TERMINATE
  EQ(readA7.wordAddr.get(), MACHINE_REGS_WORD + REG_A7);
  EQ(readA7.data.low.get(), HOST_ECALL_TERMINATE);
  EQ(readA7.data.high.get(), 0);
  EQ(readA0.wordAddr.get(), MACHINE_REGS_WORD + REG_A0);
  EQ(readA1.wordAddr.get(), MACHINE_REGS_WORD + REG_A1);
  EQ(GLOBAL_GET(isTerminate), 1);
  GLOBAL_CHECK_U32(termA0, readA0.data.get());
  GLOBAL_CHECK_U32(termA1, readA1.data.get());
  for (size_t i = 0; i < 8; i++) {
    EQ(readOutput[i].wordAddr.get(), OUTPUT_WORD + i);
    GLOBAL_CHECK_U32(out[i], readOutput[i].data.get());
  }
}

template <typename C> FDEV void EcallTerminateBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, 0, 0, 0, 0));
  VERIFY_DECODE
  uint32_t maxAddr = 0x40000000;
  for (size_t i = 0; i < 8; i++) {
    ctx.pull(MemoryArgument<C>(
        maxAddr + i, 0, GLOBAL_GET(povwNonce[i].low), GLOBAL_GET(povwNonce[i].high)));
  }
}

template <typename C> FDEV void EcallReadBlock<C>::set(CTX, EcallReadWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  finalCycle.set(ctx, wit.finalCycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  readA7.set(ctx, wit.a7, wit.cycle);
  readA1.set(ctx, wit.a1, wit.cycle);
  readA2.set(ctx, wit.a2, wit.cycle);
  writeA0.set(ctx, wit.a0, wit.cycle);
  decomp.set(ctx, wit.a1.value);
  verifyRet.set(ctx, wit.a2.value - wit.a0.value);
  uint32_t finalAddr = wit.a1.value + wit.a0.value;
  finalAddrWord.set(ctx, finalAddr / 4);
  finalAddrBits.set(ctx, finalAddr % 4);
}

template <typename C> FDEV void EcallReadBlock<C>::verify(CTX) DEV {
  // Make sure A7 = HOST_ECALL_READ
  EQ(readA7.wordAddr.get(), MACHINE_REGS_WORD + REG_A7);
  EQ(readA7.data.low.get(), HOST_ECALL_READ);
  EQ(readA7.data.high.get(), 0);
  // Verify address of A1, A2, and A0
  EQ(readA1.wordAddr.get(), MACHINE_REGS_WORD + REG_A1);
  EQ(readA2.wordAddr.get(), MACHINE_REGS_WORD + REG_A2);
  EQ(writeA0.wordAddr.get(), MACHINE_REGS_WORD + REG_A0);
  // Make sure len + ret < 64k
  EQ(readA2.data.high.get(), 0);
  EQ(writeA0.data.high.get(), 0);
  // Make sure ret <= len
  EQ(verifyRet.get(), readA2.data.low.get() - writeA0.data.low.get());
}

template <typename C> FDEV void EcallReadBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> finalCycleVal = finalCycle.get();
  Val<C> addrWord = decomp.wordAddr(readA1.data.get());
  Val<C> lowBits = decomp.low0.get() + decomp.low1.get() * 2;
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  ctx.push(ReadStateArgument<C>(cycleVal + 1, addrWord, lowBits, writeA0.data.low.get()));
  ctx.pull(ReadStateArgument<C>(finalCycleVal, finalAddrWord.get(), finalAddrBits.get(), 0));
  ctx.push(CpuStateArgument<C>(
      finalCycleVal + 1, fetch.nextPc.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  VERIFY_DECODE
}

template <typename C> FDEV void EcallWriteBlock<C>::set(CTX, EcallWriteWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  readA7.set(ctx, wit.a7, wit.cycle);
  readA2.set(ctx, wit.a2, wit.cycle);
  writeA0.set(ctx, wit.a0, wit.cycle);
  verifyRet.set(ctx, wit.a2.value - wit.a0.value);
}

template <typename C> FDEV void EcallWriteBlock<C>::verify(CTX) DEV {
  // Make sure A7 = HOST_ECALL_READ
  EQ(readA7.wordAddr.get(), MACHINE_REGS_WORD + REG_A7);
  EQ(readA7.data.low.get(), HOST_ECALL_WRITE);
  EQ(readA7.data.high.get(), 0);
  // Verify address of A2, and A0
  EQ(readA2.wordAddr.get(), MACHINE_REGS_WORD + REG_A2);
  EQ(writeA0.wordAddr.get(), MACHINE_REGS_WORD + REG_A0);
  // Make sure len + ret < 64k
  EQ(readA2.data.high.get(), 0);
  EQ(writeA0.data.high.get(), 0);
  // Make sure ret <= len
  EQ(verifyRet.get(), readA2.data.low.get() - writeA0.data.low.get());
}

template <typename C> FDEV void EcallWriteBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  ctx.push(
      CpuStateArgument<C>(cycleVal + 1, fetch.nextPc.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  VERIFY_DECODE
}

template <typename C> FDEV void P2StepBlock<C>::set(CTX, P2StepWitness wit) DEV {
  cycle.set(ctx, wit.state.cycle);
  isElem.set(ctx, wit.state.isElem);
  isCheck.set(ctx, wit.state.isCheck);
  count.set(ctx, wit.state.count);
  countOne.set(ctx, wit.state.count - 1);
  inWordAddr.set(ctx, wit.state.inWordAddr);
  outWordAddr.set(ctx, wit.state.outWordAddr);
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    uint32_t i2 = i + CELLS_DIGEST;
    stateIn[i].set(ctx, wit.stateIn[i]);
    stateOut[i].set(ctx, wit.stateOut[i]);
    dataIn[i].set(ctx, wit.dataIn[i], wit.state.cycle);
    dataIn[i2].set(ctx, wit.dataIn[i2], wit.state.cycle);
    dataOut[i].set(ctx, wit.dataOut[i], wit.state.cycle);
    if (wit.state.isElem) {
      inValues[i].set(ctx, wit.dataIn[i].value);
      inValues[i2].set(ctx, wit.dataIn[i2].value);
    } else {
      uint32_t word = wit.dataIn[i].value;
      inValues[2 * i].set(ctx, word & 0xffff);
      inValues[2 * i + 1].set(ctx, word >> 16);
    }
  }
}

template <typename C> FDEV void P2StepBlock<C>::verify(CTX) DEV {
  Val<C> verifyCheck = countOne.isZero.get() * isCheck.get();
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    uint32_t i2 = i + CELLS_DIGEST;
    EQ(dataIn[i].wordAddr.get(), inWordAddr.get() + i);
    EQ(dataIn[i2].wordAddr.get(), cond<C>(isElem.get(), inWordAddr.get() + i2, P2_ZEROS_WORD + i));
    EQ(dataOut[i].wordAddr.get(),
       cond<C>(countOne.isZero.get(), outWordAddr.get() + i, P2_TRASH_WORD + i));
    EQZ(verifyCheck * (dataOut[i].prevData.low.get() - dataOut[i].data.low.get()));
    EQZ(verifyCheck * (dataOut[i].prevData.high.get() - dataOut[i].data.high.get()));
    // Relate inValues to dataIn
    EQZ(isElem.get() * (inValues[i].get() - dataIn[i].data.flat()));
    EQZ(isElem.get() * (inValues[i2].get() - dataIn[i2].data.flat()));
    EQZ((Val<C>(1) - isElem.get()) * (inValues[2 * i].get() - dataIn[i].data.low.get()));
    EQZ((Val<C>(1) - isElem.get()) * (inValues[2 * i + 1].get() - dataIn[i].data.high.get()));
  }
}

template <typename C> FDEV void P2StepBlock<C>::addArguments(CTX) DEV {
  Val<C> countBits = count.get() + isElem.get() * 0x20000 + isCheck.get() * 0x10000;
  P2StepArgument<C> p2Arg;
  p2Arg.cycle = cycle.get();
  p2Arg.countBits = countBits;
  p2Arg.inWordAddr = inWordAddr.get();
  p2Arg.outWordAddr = outWordAddr.get();
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    p2Arg.state[i] = stateIn[i].get();
  }
  ctx.pull(p2Arg);
  p2Arg.cycle += 1;
  p2Arg.countBits = countBits - 1;
  p2Arg.inWordAddr += isElem.get() * CELLS_DIGEST + CELLS_DIGEST;
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    p2Arg.state[i] = stateOut[i].get();
  }
  ctx.push(p2Arg);
  P2CallArgument<C> call;
  call.isFinal = 1;
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    uint32_t i2 = i + CELLS_DIGEST;
    call.in[i] = stateIn[i].get();
    call.data[i] = inValues[i].get();
    call.data[i2] = inValues[i2].get();
    call.out[i] = dataOut[i].data.high.get() * 0x10000 + dataOut[i].data.low.get();
  }
  ctx.pull(call);
  call.isFinal = 0;
  for (size_t i = 0; i < 8; i++) {
    call.out[i] = stateOut[i].get();
  }
  ctx.pull(call);
}

template <typename C> FDEV void EcallP2Block<C>::set(CTX, EcallP2Witness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  readA0.set(ctx, wit.a0, wit.cycle);
  readA1.set(ctx, wit.a1, wit.cycle);
  readA2.set(ctx, wit.a2, wit.cycle);
  readA3.set(ctx, wit.a3, wit.cycle);
  readA7.set(ctx, wit.a7, wit.cycle);
  decompState.set(ctx, wit.a0.value);
  decompIn.set(ctx, wit.a1.value);
  decompOut.set(ctx, wit.a2.value);
  bool isElemBool = (wit.a3.value & PFLAG_IS_ELEM) != 0;
  isElem.set(ctx, isElemBool);
  isCheck.set(ctx, (wit.a3.value & PFLAG_CHECK_OUT) != 0);
  iszState.set(ctx, wit.a0.value / 4);
  stateInWordAddr.set(ctx, wit.a0.value ? wit.a0.value / 4 : P2_ZEROS_WORD);
  stateOutWordAddr.set(ctx, wit.a0.value ? wit.a0.value / 4 : P2_TRASH_WORD);
  uint32_t count = wit.a3.value & 0xffff;
  inWordAddrFinal.set(ctx, wit.a1.value / 4 + count * (isElemBool ? 16 : 8));
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    stateIn[i].set(ctx, wit.stateIn[i], wit.cycle);
    stateOut[i].set(ctx, wit.stateOut[i], 1 + wit.cycle + count);
  }
}

template <typename C> FDEV void EcallP2Block<C>::verify(CTX) DEV {
  // Make sure A7 = HOST_ECALL_POSEIDON2
  EQ(readA7.wordAddr.get(), MACHINE_REGS_WORD + REG_A7);
  EQ(readA7.data.low.get(), HOST_ECALL_POSEIDON2);
  EQ(readA7.data.high.get(), 0);
  // Verify other register addressed
  EQ(readA0.wordAddr.get(), MACHINE_REGS_WORD + REG_A0);
  EQ(readA1.wordAddr.get(), MACHINE_REGS_WORD + REG_A1);
  EQ(readA2.wordAddr.get(), MACHINE_REGS_WORD + REG_A2);
  EQ(readA3.wordAddr.get(), MACHINE_REGS_WORD + REG_A3);
  Val<C> stateWordAddr = decompState.wordAddr(readA0.data.get());
  EQ(stateInWordAddr.get(), cond<C>(iszState.isZero.get(), P2_ZEROS_WORD, stateWordAddr));
  EQ(stateOutWordAddr.get(), cond<C>(iszState.isZero.get(), P2_TRASH_WORD, stateWordAddr));
  // Verify bits
  EQ(readA3.data.high.get(), isElem.get() * 0x8000 + isCheck.get() * 0x4000);
  // Verify load + store addresses
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    EQ(stateIn[i].wordAddr.get(), stateInWordAddr.get() + i);
    EQ(stateOut[i].wordAddr.get(), stateOutWordAddr.get() + i);
  }
  Val<C> count = readA3.data.low.get();
  EQ(inWordAddrFinal.get(),
     decompIn.wordAddr(readA1.data.get()) + count * cond<C>(isElem.get(), 16, 8));
}

template <typename C> FDEV void EcallP2Block<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> count = readA3.data.low.get();
  Val<C> bits = readA3.data.high.get() * 4;
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  P2StepArgument<C> p2Arg;
  p2Arg.cycle = cycleVal + 1;
  p2Arg.countBits = count + bits;
  p2Arg.inWordAddr = decompIn.wordAddr(readA1.data.get());
  p2Arg.outWordAddr = decompOut.wordAddr(readA2.data.get());
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    p2Arg.state[i] = stateIn[i].data.flat();
  }
  ctx.push(p2Arg);
  p2Arg.cycle += count;
  p2Arg.countBits = bits;
  p2Arg.inWordAddr = inWordAddrFinal.get();
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    p2Arg.state[i] = stateOut[i].data.flat();
  }
  ctx.pull(p2Arg);
  ctx.push(CpuStateArgument<C>(
      cycleVal + count + 2, fetch.nextPc.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  VERIFY_DECODE
}

template <typename C> FDEV void EcallBigIntBlock<C>::set(CTX, EcallBigIntWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  readA7.set(ctx, wit.a7, wit.cycle);
  readT0.set(ctx, wit.t0, wit.cycle);
  readT2.set(ctx, wit.t2, wit.cycle);
  cycleCount.set(ctx, wit.count);
  mm.set(ctx, wit.t0.value);
  pcDecomp.set(ctx, wit.t2.value);
  pcVerify.set(ctx, wit.t2.value, wit.t0.value * MODE_MACHINE);
}

template <typename C> FDEV void EcallBigIntBlock<C>::verify(CTX) DEV {
  // Make sure A7 = HOST_ECALL_BIGINT
  EQ(readA7.wordAddr.get(), MACHINE_REGS_WORD + REG_A7);
  EQ(readA7.data.low.get(), HOST_ECALL_BIGINT);
  EQ(readA7.data.high.get(), 0);
  // Verify address of T0 + T2
  EQ(readT0.wordAddr.get(), MACHINE_REGS_WORD + REG_T0);
  EQ(readT2.wordAddr.get(), MACHINE_REGS_WORD + REG_T2);
  // Make sure T0 is a valid mm
  EQ(readT0.data.low.get(), mm.get());
  EQ(readT0.data.high.get(), 0);
  // Make sure new PC is aligned
  EQZ(pcDecomp.low0.get() + pcDecomp.low1.get());
}

template <typename C> FDEV void EcallBigIntBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> countVal = cycleCount.get();
  Val<C> biPc = pcDecomp.wordAddr(readT2.data.get());
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  ctx.push(BigIntCpuStateArgument<C>(cycleVal + 1, biPc, mm.get()));
  ctx.pull(BigIntCpuStateArgument<C>(cycleVal + countVal + 1, biPc + countVal, mm.get()));
  ctx.push(CpuStateArgument<C>(
      cycleVal + countVal + 2, fetch.nextPc.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  VERIFY_DECODE
}
