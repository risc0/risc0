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

#define CPU_STATE_ARGUMENT(ctx, arg)                                                               \
  PICUS_ARGUMENT(ctx,                                                                              \
                 ({}),                                                                             \
                 ({ctx.get(arg.cycle),                                                             \
                   ctx.get(arg.pcLow),                                                             \
                   ctx.get(arg.pcHigh),                                                            \
                   ctx.get(arg.mm),                                                                \
                   ctx.get(arg.iCache)}))

// The actual "reading" happens via ReadByteBlock and ReadWordBlock. If the read
// state argument is balanced, then the pulled values are determined by the
// pushes from those blocks.
#define READ_STATE_ARGUMENT(ctx, arg)                                                              \
  PICUS_ARGUMENT(                                                                                  \
      ctx,                                                                                         \
      {},                                                                                          \
      ({ctx.get(arg.cycle), ctx.get(arg.addrWord), ctx.get(arg.addrLowBits), ctx.get(arg.size)}))

#define BIGINT_STATE_ARGUMENT(ctx, init, fini)                                                     \
  PICUS_ARGUMENT(ctx,                                                                              \
                 ({ctx.get(init.cycle), ctx.get(init.pcWord), ctx.get(init.mm)}),                  \
                 ({ctx.get(fini.cycle), ctx.get(fini.pcWord), ctx.get(fini.mm)}))

#define DECODE_ARGUMENT(ctx, arg)                                                                  \
  PICUS_ARGUMENT(ctx,                                                                              \
                 ({ctx.get(arg.iCacheCycle), ctx.get(arg.pcLow), ctx.get(arg.pcHigh)}),            \
                 ({ctx.get(arg.newPcLow), ctx.get(arg.newPcHigh)}))

#define P2_CALL_ARGUMENT(ctx, arg) \
  PICUS_ARGUMENT(ctx, \
                 ({ctx.get(call.isFinal), UNPACK_DIGEST(ctx, call.in), UNPACK_RATE(ctx, call.data)}), \
                 ({UNPACK_DIGEST(ctx, call.out)}))

#define P2_STEP_ARGUMENT(ctx, arg) \
  PICUS_INPUT(ctx, arg.cycle); \
  PICUS_INPUT(ctx, arg.countBits); \
  PICUS_INPUT(ctx, arg.inWordAddr); \
  PICUS_INPUT(ctx, arg.outWordAddr); \
  PICUS_INPUT(ctx, arg.state)

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
  arg.pcHigh = fetch.pc.high.get();                                                                \
  arg.newPcLow = fetch.nextPc.low.get();                                                           \
  arg.newPcHigh = fetch.nextPc.high.get();                                                         \
  arg.rs1 = 0;                                                                                     \
  arg.rs2 = 0;                                                                                     \
  arg.rd = 0;                                                                                      \
  arg.immLow = 0;                                                                                  \
  arg.immHigh = 0;                                                                                 \
  arg.options = Val<C>(uint32_t(INST_ECALL));                                                      \
  ctx.pull(arg);                                                                                   \
  DECODE_ARGUMENT(ctx, arg);

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
  // Must be in machine mode
  EQ(fetch.mode.get(), Val<C>(MODE_MACHINE));

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
  CpuStateArgument<C> cpuState(cycleVal, fetch.pc.get(), MODE_MACHINE, fetch.iCacheCycle.get());
  ctx.pull(cpuState);
  ctx.push(CpuStateArgument<C>(cycleVal + 1, 0, 0, 0, 0));
  CPU_STATE_ARGUMENT(ctx, cpuState);

  VERIFY_DECODE
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
  // A1 holds the address to read data into, A2 holds the requested length to
  // read, and the actual length read is written to A0. The data read (and
  // therefore its length as well) is input from the host.
  PICUS_INPUT(ctx, writeA0.data.low);

  // Must be in machine mode
  EQ(fetch.mode.get(), Val<C>(MODE_MACHINE));

  // Make sure A7 = HOST_ECALL_READ
  EQ(readA7.wordAddr.get(), MACHINE_REGS_WORD + REG_A7);
  EQ(readA7.data.low.get(), HOST_ECALL_READ);
  EQ(readA7.data.high.get(), 0);
  // Verify address of A1, A2, and A0
  EQ(readA1.wordAddr.get(), MACHINE_REGS_WORD + REG_A1);
  EQ(readA2.wordAddr.get(), MACHINE_REGS_WORD + REG_A2);
  EQ(writeA0.wordAddr.get(), MACHINE_REGS_WORD + REG_A0);
  // Make sure len and ret < 64k
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
  CpuStateArgument<C> cpuState(cycleVal, fetch.pc.get(), MODE_MACHINE, fetch.iCacheCycle.get());
  ctx.pull(cpuState);
  CPU_STATE_ARGUMENT(ctx, cpuState);

  ReadStateArgument<C> readState(finalCycleVal, finalAddrWord.get(), finalAddrBits.get(), 0);
  ctx.push(ReadStateArgument<C>(cycleVal + 1, addrWord, lowBits, writeA0.data.low.get()));
  ctx.pull(readState);
  READ_STATE_ARGUMENT(ctx, readState);

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
  // A1 holds the address to write data into, A2 holds the requested length to
  // write, and the actual length written is returned to A0. The amount written
  // is intentionally nondeterministic.
  PICUS_INPUT(ctx, writeA0.data.low);

  // Must be in machine mode
  EQ(fetch.mode.get(), Val<C>(MODE_MACHINE));

  // Make sure A7 = HOST_ECALL_WRITE
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
  CpuStateArgument<C> cpuState(cycleVal, fetch.pc.get(), MODE_MACHINE, fetch.iCacheCycle.get());
  ctx.pull(cpuState);
  ctx.push(
      CpuStateArgument<C>(cycleVal + 1, fetch.nextPc.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  CPU_STATE_ARGUMENT(ctx, cpuState);
  VERIFY_DECODE
}

template <typename C> FDEV void P2StepBlock<C>::set(CTX, P2StepWitness wit) DEV {
  cycle.set(ctx, wit.state.cycle);
  isElem.set(ctx, wit.state.isElem);
  isCheck.set(ctx, wit.state.isCheck);
  count.set(ctx, wit.state.count);
  countOne.set(ctx, wit.state.count - 1);
  verifyCheck.set(ctx, wit.state.isCheck && wit.state.count == 1);
  inWordAddr.set(ctx, wit.state.inWordAddr);
  outWordAddr.set(ctx, wit.state.outWordAddr);
  writeWordAddr.set(ctx, wit.state.count == 1 ? wit.state.outWordAddr : P2_TRASH_WORD);
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    uint32_t i2 = i + CELLS_DIGEST;
    stateIn[i].set(ctx, wit.stateIn[i]);
    stateOut[i].set(ctx, wit.stateOut[i]);
    dataIn[i].set(ctx, wit.dataIn[i], wit.state.cycle);
    dataIn[i2].set(ctx, wit.dataIn[i2], wit.state.cycle);
    dataOut[i].set(ctx, wit.dataOut[i]);
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
  EQ(verifyCheck.get(), countOne.isZero.get() * isCheck.get());
  EQ(writeWordAddr.get(), cond<C>(countOne.isZero.get(), outWordAddr.get(), P2_TRASH_WORD));
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    uint32_t i2 = i + CELLS_DIGEST;
    EQ(dataIn[i].wordAddr.get(), inWordAddr.get() + i);
    EQ(dataIn[i2].wordAddr.get(), cond<C>(isElem.get(), inWordAddr.get() + i2, P2_ZEROS_WORD + i));
    // Relate inValues to dataIn
    EQZ(isElem.get() * (inValues[i].get() - dataIn[i].data.flat()));
    EQZ(isElem.get() * (inValues[i2].get() - dataIn[i2].data.flat()));
    EQZ((Val<C>(1) - isElem.get()) * (inValues[2 * i].get() - dataIn[i].data.low.get()));
    EQZ((Val<C>(1) - isElem.get()) * (inValues[2 * i + 1].get() - dataIn[i].data.high.get()));
  }
}

template <typename C> FDEV void P2StepBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> countBits = count.get() + isElem.get() * 0x20000 + isCheck.get() * 0x10000;
  P2StepArgument<C> p2Arg;
  p2Arg.cycle = cycleVal;
  p2Arg.countBits = countBits;
  p2Arg.inWordAddr = inWordAddr.get();
  p2Arg.outWordAddr = outWordAddr.get();
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    p2Arg.state[i] = stateIn[i].get();
  }
  ctx.pull(p2Arg);
  P2_STEP_ARGUMENT(ctx, p2Arg);
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
    call.out[i] = dataOut[i].get();
  }
  ctx.pull(call);
  P2_CALL_ARGUMENT(ctx, call);
  call.isFinal = 0;
  for (size_t i = 0; i < 8; i++) {
    call.out[i] = stateOut[i].get();
  }
  ctx.pull(call);
  P2_CALL_ARGUMENT(ctx, call);

  // Offload writing into memory to DigestWriteBlock
  DigestWriteArgument<C> dwArg;
  dwArg.wordAddr = writeWordAddr.get();
  dwArg.cycle = cycleVal;
  dwArg.verifyCheck = verifyCheck.get();
  GET_ARR(dwArg.digest, dataOut, CELLS_DIGEST);
  ctx.push(dwArg);
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
    stateOut[i].set(ctx, wit.stateOut[i]);
  }
}

template <typename C> FDEV void EcallP2Block<C>::verify(CTX) DEV {
  // Must be in machine mode
  EQ(fetch.mode.get(), Val<C>(MODE_MACHINE));

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
  // Verify load addresses
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    EQ(stateIn[i].wordAddr.get(), stateInWordAddr.get() + i);
  }
  Val<C> count = readA3.data.low.get();
  EQ(inWordAddrFinal.get(),
     decompIn.wordAddr(readA1.data.get()) + count * cond<C>(isElem.get(), 16, 8));
}

template <typename C> FDEV void EcallP2Block<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> count = readA3.data.low.get();
  Val<C> bits = readA3.data.high.get() * 4;
  CpuStateArgument<C> cpuState(cycleVal, fetch.pc.get(), MODE_MACHINE, fetch.iCacheCycle.get());
  ctx.pull(cpuState);
  ctx.push(CpuStateArgument<C>(
      cycleVal + count + 2, fetch.nextPc.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  CPU_STATE_ARGUMENT(ctx, cpuState);

  // Delegate Poseidon2 computation to P2StepBlock
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
    p2Arg.state[i] = stateOut[i].get();
  }
  ctx.pull(p2Arg);
  PICUS_ARGUMENT(ctx,
                 ({ctx.get(p2Arg.cycle),
                   ctx.get(p2Arg.countBits),
                   ctx.get(p2Arg.inWordAddr),
                   ctx.get(p2Arg.outWordAddr),
                   ctx.get(stateIn[0].data.flat()),
                   ctx.get(stateIn[1].data.flat()),
                   ctx.get(stateIn[2].data.flat()),
                   ctx.get(stateIn[3].data.flat()),
                   ctx.get(stateIn[4].data.flat()),
                   ctx.get(stateIn[5].data.flat()),
                   ctx.get(stateIn[6].data.flat()),
                   ctx.get(stateIn[7].data.flat())}),
                 ({UNPACK_DIGEST(ctx, p2Arg.state)}));

  DigestWriteArgument<C> dwArg;
  dwArg.wordAddr = stateOutWordAddr.get();
  dwArg.cycle = cycleVal + 1 + readA3.data.low.get();
  dwArg.verifyCheck = Val<C>(0);
  GET_ARR(dwArg.digest, stateOut, CELLS_DIGEST);
  ctx.push(dwArg);

  VERIFY_DECODE
}

template <typename C> FDEV void FpWrite<C>::set(CTX, PhysMemWriteWitness wit, uint32_t cycle) DEV {
  write.set(ctx, wit, cycle);
  uint32_t high = wit.value >> 16;
  uint32_t low = wit.value & 0xffff;
  pHighMinusHigh.set(ctx, 0x7800 - high);
  ctx.tableAdd(256 + high, 1);
  ctx.tableAdd(256 + low, 1);
  ctx.tableAdd(256 + (0x7800 - high), 1);
}

template <typename C>
FDEV void FpWrite<C>::verify(CTX, Val<C> cycle, Val<C> wordAddr, Val<C> fp) DEV {
  PICUS_BEGIN_OUTLINE(cycle, wordAddr, fp)
  // Write is to the correct address
  EQ(write.wordAddr.get(), wordAddr);

  // The u32 we write to memory must be a decomposition of the field element
  EQ(write.data.flat(), fp);

  // The u32 we write must be normalized. Since p = 0x78000001, it suffices to
  // check the following:
  //  * data.high is between 0 and 0x7800 (inclusive), checked by:
  //    * data.high is a U16
  //    * (0x7800 - data.high) is also a U16
  //  * data.low is a U16
  //  * if data.high = 0x7800, then data.low = 0
  EQZ(pHighMinusHigh.isZero.get() * write.data.low.get());
  PICUS_END_OUTLINE
}

template <typename C>
FDEV void FpWrite<C>::addArguments(CTX, Val<C> cycle, Val<C> wordAddr, Val<C> fp) DEV {
  Val<C> high = write.data.high.get();
  Val<C> low = write.data.low.get();
  assertU16(ctx, high);
  assertU16(ctx, low);
  assertU16(ctx, Val<C>(0x7800) - high);
}

template <typename C> FDEV void DigestWriteBlock<C>::set(CTX, DigestWriteWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  wordAddr.set(ctx, wit.stateOut[0].wordAddr);
  verifyCheck.set(ctx, wit.verifyCheck);
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    digest[i].set(ctx, wit.stateOut[i].value);
    writes[i].set(ctx, wit.stateOut[i], wit.cycle);
  }
}

template <typename C> FDEV void DigestWriteBlock<C>::verify(CTX) DEV {
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    EQZ(verifyCheck.get() * (writes[i].write.prevData.low.get() - writes[i].write.data.low.get()));
    EQZ(verifyCheck.get() * (writes[i].write.prevData.high.get() - writes[i].write.data.high.get()));
  }
}

#define DIGEST_WRITE_ARGUMENT(ctx, arg)                                                            \
  PICUS_INPUT(ctx, arg.wordAddr);                                                                  \
  PICUS_INPUT(ctx, arg.cycle);                                                                     \
  PICUS_INPUT(ctx, arg.verifyCheck);                                                               \
  PICUS_INPUT(ctx, arg.digest)

template <typename C> FDEV void DigestWriteBlock<C>::addArguments(CTX) DEV {
  // The data to write and where to write it are inputs
  DigestWriteArgument<C> dwArg;
  dwArg.wordAddr = wordAddr.get();
  dwArg.cycle = cycle.get();
  dwArg.verifyCheck = verifyCheck.get();
  GET_ARR(dwArg.digest, digest, CELLS_DIGEST);
  ctx.pull(dwArg);
  DIGEST_WRITE_ARGUMENT(ctx, dwArg);
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
  // Must be in machine mode
  EQ(fetch.mode.get(), Val<C>(MODE_MACHINE));

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
  CpuStateArgument<C> cpuState(cycleVal, fetch.pc.get(), MODE_MACHINE, fetch.iCacheCycle.get());
  ctx.pull(cpuState);
  CPU_STATE_ARGUMENT(ctx, cpuState);

  BigIntCpuStateArgument<C> initialBigIntState(cycleVal + 1, biPc, mm.get());
  BigIntCpuStateArgument<C> finalBigIntState(cycleVal + countVal + 1, biPc + countVal, mm.get());
  ctx.push(initialBigIntState);
  ctx.pull(finalBigIntState);
  BIGINT_STATE_ARGUMENT(ctx, initialBigIntState, finalBigIntState);

  ctx.push(CpuStateArgument<C>(
      cycleVal + countVal + 2, fetch.nextPc.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  VERIFY_DECODE
}

#undef BIGINT_STATE_ARGUMENT
#undef CPU_STATE_ARGUMENT
#undef DECODE_ARGUMENT
#undef READ_STATE_ARGUMENT
#undef P2_CALL_ARGUMENT
#undef P2_STEP_ARGUMENT
