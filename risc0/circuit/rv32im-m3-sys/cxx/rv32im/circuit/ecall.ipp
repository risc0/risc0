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

#define GLOBAL_OFFSET(member)                                                                      \
  (reinterpret_cast<MDEV Fp*>(&reinterpret_cast<MDEV Globals*>(0x10000)->member) -                 \
   reinterpret_cast<MDEV Fp*>(0x10000))
#define GLOBAL_GET(member) ctx.globalGet(GLOBAL_OFFSET(member))
#define GLOBAL_SET(member, val) ctx.globalSet(GLOBAL_OFFSET(member), (val))

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
  fetch.set(ctx, wit.fetch);
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
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), 1, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, 0, 0, 0, 0));
  VERIFY_DECODE
}

template <typename C> FDEV void EcallReadBlock<C>::set(CTX, EcallReadWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  finalCycle.set(ctx, wit.finalCycle);
  fetch.set(ctx, wit.fetch);
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
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), 1, fetch.iCacheCycle.get()));
  ctx.push(ReadStateArgument<C>(cycleVal + 1, addrWord, lowBits, writeA0.data.low.get()));
  ctx.pull(ReadStateArgument<C>(finalCycleVal, finalAddrWord.get(), finalAddrBits.get(), 0));
  ctx.push(CpuStateArgument<C>(finalCycleVal + 1, fetch.nextPc.get(), 1, fetch.iCacheCycle.get()));
  VERIFY_DECODE
}

template <typename C> FDEV void EcallWriteBlock<C>::set(CTX, EcallWriteWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch);
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
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), 1, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, fetch.nextPc.get(), 1, fetch.iCacheCycle.get()));
  VERIFY_DECODE
}

template <typename C> FDEV void EcallBigIntBlock<C>::set(CTX, EcallBigIntWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch);
  readA7.set(ctx, wit.a7, wit.cycle);
  readT0.set(ctx, wit.t0, wit.cycle);
  readT2.set(ctx, wit.t2, wit.cycle);
  cycleCount.set(ctx, wit.count);
  mm.set(ctx, wit.t0.value);
  pcDecomp.set(ctx, wit.t2.value);
  pcVerify.set(ctx, wit.t2.value, wit.t0.value);
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
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), 1, fetch.iCacheCycle.get()));
  ctx.push(BigIntCpuStateArgument<C>(cycleVal + 1, biPc, mm.get()));
  ctx.pull(BigIntCpuStateArgument<C>(cycleVal + countVal + 1, biPc + countVal, mm.get()));
  ctx.push(
      CpuStateArgument<C>(cycleVal + countVal + 2, fetch.nextPc.get(), 1, fetch.iCacheCycle.get()));
  VERIFY_DECODE
}
