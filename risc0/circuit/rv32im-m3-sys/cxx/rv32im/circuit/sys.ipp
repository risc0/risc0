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
// WITHOUT WARRANTIES OR condITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

template <typename C> FDEV void InstResumeBlock<C>::set(CTX, InstResumeWitness wit) DEV {
  readV2Compat.set(ctx, wit.v2Compat, 1);
  readPc.set(ctx, wit.pc, 1);
  readMode.set(ctx, wit.mode, 1);
  writeVersion.set(ctx, wit.version, 1);
}

template <typename C> FDEV void InstResumeBlock<C>::verify(CTX) DEV {
  // Verify V2 compat is set correctly
  EQZ(readV2Compat.data.high.get());
  AssertBit<C>(ctx, readV2Compat.data.low.get());
  EQ(GLOBAL_GET(v2Compat), Val<C>(1) - readV2Compat.data.low.get());
  // Verify mm is one of the valid options
  EQZ(readMode.data.high.get());
  Val<C> mode = readMode.data.low.get() * cond<C>(GLOBAL_GET(v2Compat), MODE_MACHINE, 1);
  EQZ((mode - MODE_USER) * (mode - MODE_SUPERVISOR) * (mode - MODE_MACHINE));
  // Verify we loaded from the right addresses
  EQ(readV2Compat.wordAddr.get(), CSR_WORD(MNOV2COMPAT));
  EQ(readPc.wordAddr.get(), cond<C>(GLOBAL_GET(v2Compat), V2_COMPAT_SPC, CSR_WORD(MSPC)));
  EQ(readMode.wordAddr.get(), cond<C>(GLOBAL_GET(v2Compat), V2_COMPAT_SMODE, CSR_WORD(MSMODE)));
}

template <typename C> FDEV void InstResumeBlock<C>::addArguments(CTX) DEV {
  ctx.pull(CpuStateArgument<C>(1, 0, 0, 0, 1));
  ValU32<C> pc = readPc.data.get();
  Val<C> mode = readMode.data.low.get() * cond<C>(GLOBAL_GET(v2Compat), MODE_MACHINE, 1);
  ctx.push(CpuStateArgument<C>(2, pc, mode, 1));
}

template <typename C> FDEV void InstSuspendBlock<C>::set(CTX, InstSuspendWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  iCacheCycle.set(ctx, wit.iCacheCycle);
  writePc.set(ctx, wit.pc, wit.cycle);
  writeMode.set(ctx, wit.mode, wit.cycle);
  GLOBAL_SET(isTerminate, 0);
}

template <typename C> FDEV void InstSuspendBlock<C>::verify(CTX) DEV {
  // Verify terminate
  EQ(GLOBAL_GET(isTerminate), 0);
  // Verify we stored to the right values
  EQZ(writeMode.data.high.get());
  // Verify we stored to the right addresses
  EQ(writePc.wordAddr.get(), cond<C>(GLOBAL_GET(v2Compat), V2_COMPAT_SPC, CSR_WORD(MSPC)));
  EQ(writeMode.wordAddr.get(), cond<C>(GLOBAL_GET(v2Compat), V2_COMPAT_SMODE, CSR_WORD(MSMODE)));
}

template <typename C> FDEV void InstSuspendBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  ValU32<C> pc = writePc.data.get();
  Val<C> mode = writeMode.data.low.get() * cond<C>(GLOBAL_GET(v2Compat), MODE_MACHINE, 1);
  ctx.pull(CpuStateArgument<C>(cycleVal, pc, mode, iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, 0, 0, 0, 0));
}

template <typename C> FDEV void InstEcallBlock<C>::set(CTX, InstEcallWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  writeSavePc.set(ctx, wit.savePc, wit.cycle);
  readDispatch.set(ctx, wit.dispatch, wit.cycle);
}

template <typename C> FDEV void InstEcallBlock<C>::verify(CTX) DEV {
  // Make sure next PC is being saved
  EQ(fetch.pc.low.get(), writeSavePc.data.low.get());
  EQ(fetch.pc.high.get(), writeSavePc.data.high.get());
  // Make sure address constants are right
  Val<C> mepcWord = cond<C>(GLOBAL_GET(v2Compat), V2_COMPAT_MEPC, CSR_WORD(MEPC));
  Val<C> mtvecWord = cond<C>(GLOBAL_GET(v2Compat), V2_COMPAT_ECALL_DISPATCH, CSR_WORD(MTVEC));
  EQ(writeSavePc.wordAddr.get(), mepcWord);
  EQ(readDispatch.wordAddr.get(), mtvecWord);
}

template <typename C> FDEV void InstEcallBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  // Move from mode = USER to mode = MACHINE
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), MODE_USER, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(
      cycleVal + 1, readDispatch.data.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  // Verify decoding
  DecodeArgument<C> arg;
  arg.iCacheCycle = fetch.iCacheCycle.get();
  arg.pcLow = fetch.pc.low.get();
  arg.pcLow = fetch.pc.high.get();
  arg.newPcLow = fetch.nextPc.low.get();
  arg.newPcLow = fetch.nextPc.high.get();
  arg.rs1 = 0;
  arg.rs2 = 0;
  arg.rd = 0;
  arg.immLow = 0;
  arg.immHigh = 0;
  arg.options = Val<C>(uint32_t(INST_ECALL));
  ctx.pull(arg);
}

template <typename C> FDEV void InstTrapBlock<C>::set(CTX, InstTrapWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  iCacheCycle.set(ctx, wit.iCacheCycle);
  writeMEPC.set(ctx, wit.MEPC, wit.cycle);
  writeMPREVMODE.set(ctx, wit.MPREVMODE, wit.cycle);
  readMNONDETTRAP.set(ctx, wit.MNONDETTRAP, wit.cycle);
}

template <typename C> FDEV void InstTrapBlock<C>::verify(CTX) DEV {
  // Verify addresses
  EQ(writeMEPC.wordAddr.get(), CSR_WORD(MEPC));
  EQ(writeMPREVMODE.wordAddr.get(), CSR_WORD(MPREVMODE));
  EQ(readMNONDETTRAP.wordAddr.get(), CSR_WORD(MNONDETTRAP));
  // Make sure mode is not currently machine mode
  EQZ(writeMPREVMODE.data.high.get());
  Val<C> oldMode = writeMPREVMODE.data.low.get();
  EQZ((oldMode - MODE_USER) * (oldMode - MODE_SUPERVISOR));
}

template <typename C> FDEV void InstTrapBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> oldMode = writeMPREVMODE.data.low.get();
  ctx.pull(CpuStateArgument<C>(cycleVal, writeMEPC.data.get(), oldMode, iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(
      cycleVal + 1, readMNONDETTRAP.data.get(), MODE_MACHINE, iCacheCycle.get()));
}

template <typename C> FDEV void InstMretBlock<C>::set(CTX, InstMretWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  readPc.set(ctx, wit.readPc, wit.cycle);
  toAdd.set(ctx, GLOBAL_GET(v2Compat).asUInt32() * 4);
  sumPc.set(ctx, wit.readPc.value, GLOBAL_GET(v2Compat).asUInt32() * 4);
}

template <typename C> FDEV void InstMretBlock<C>::verify(CTX) DEV {
  // Make sure address constants is right
  Val<C> mepcWord = cond<C>(GLOBAL_GET(v2Compat), V2_COMPAT_MEPC, CSR_WORD(MEPC));
  EQ(toAdd.get(), GLOBAL_GET(v2Compat) * 4);
  EQ(readPc.wordAddr.get(), mepcWord);
}

template <typename C> FDEV void InstMretBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  // Move from mode = MACHINE to mode = USER
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), MODE_MACHINE, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, sumPc.get(), MODE_USER, fetch.iCacheCycle.get()));
  // Verify decoding
  DecodeArgument<C> arg;
  arg.iCacheCycle = fetch.iCacheCycle.get();
  arg.pcLow = fetch.pc.low.get();
  arg.pcLow = fetch.pc.high.get();
  arg.newPcLow = fetch.nextPc.low.get();
  arg.newPcLow = fetch.nextPc.high.get();
  arg.rs1 = 0;
  arg.rs2 = 2;
  arg.rd = 0;
  arg.immLow = 770;
  arg.immHigh = 0;
  arg.options = Val<C>(uint32_t(INST_MRET));
  ctx.pull(arg);
}
