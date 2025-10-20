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

template <typename C> FDEV void InstResumeBlock<C>::set(CTX, InstResumeWitness wit) DEV {
  readPc.set(ctx, wit.pc, 1);
  readMode.set(ctx, wit.mode, 1);
}

template <typename C> FDEV void InstResumeBlock<C>::verify(CTX) DEV {
  // Verify mm is one of the valid options
  EQZ(readMode.data.high.get());
  Val<C> mode = readMode.data.low.get();
  EQZ((mode - MODE_USER) * (mode - MODE_SUPERVISOR) * (mode - MODE_MACHINE));
  // Verify we loaded from the right addresses
  EQ(readPc.wordAddr.get(), CSR_WORD(MSPC));
  EQ(readMode.wordAddr.get(), CSR_WORD(MSMODE));
}

template <typename C> FDEV void InstResumeBlock<C>::addArguments(CTX) DEV {
  ctx.pull(CpuStateArgument<C>(1, 0, 0, 0, 1));
  ValU32<C> pc = readPc.data.get();
  Val<C> mode = readMode.data.low.get();
  ctx.push(CpuStateArgument<C>(2, pc, mode, 1));
}

template <typename C> FDEV void InstSuspendBlock<C>::set(CTX, InstSuspendWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  iCacheCycle.set(ctx, wit.iCacheCycle);
  writePc.set(ctx, wit.pc, wit.cycle);
  writeMode.set(ctx, wit.mode, wit.cycle);
}

template <typename C> FDEV void InstSuspendBlock<C>::verify(CTX) DEV {
  // Verify we stored to the right addresses
  EQ(writePc.wordAddr.get(), CSR_WORD(MSPC));
  EQ(writeMode.wordAddr.get(), CSR_WORD(MSMODE));
}

template <typename C> FDEV void InstSuspendBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  ValU32<C> pc = writePc.data.get();
  Val<C> mode = writeMode.data.low.get();
  ctx.pull(CpuStateArgument<C>(cycleVal, pc, mode, iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, 0, 0, 0, 0));
}

template <typename C> FDEV void SourceReg<C>::set(CTX, Val<C> wordAddr) DEV {
  // The registers are aligned, % 32 of the word address recovers the register #
  idx.set(ctx, asUInt32(wordAddr) % 32);
}

template <typename C> FDEV void SourceReg<C>::verify(CTX, Val<C> wordAddr, Val<C> mode) DEV {
  // Recompute register address from mode + index, verify it matches
  Val<C> isMM = (mode - MODE_USER) * (mode - MODE_SUPERVISOR) * Val<C>(inv(Fp(6)));
  EQ(cond<C>(isMM, MACHINE_REGS_WORD, USER_REGS_WORD) + idx.get(), wordAddr);
}

template <typename C> FDEV void DestReg<C>::set(CTX, Val<C> wordAddr) DEV {
  // The registers are aligned, % 32 of the word address recovers the register #
  Val<C> idxVal = Val<C>(asUInt32(wordAddr) % 32);
  idx.set(ctx, idxVal);
  // Check for zero to special case writes to zero reg
  isZero.set(ctx, idxVal);
}

template <typename C> FDEV void DestReg<C>::verify(CTX, Val<C> wordAddr, Val<C> mode) DEV {
  // Recompute register address from mode + index, verify it matches
  // If the register is zero, add 64 so we write into empty space past the
  // main register file (i.e. write to zero reg dont change the register)
  Val<C> isMM = (mode - MODE_USER) * (mode - MODE_SUPERVISOR) * Val<C>(inv(Fp(6)));
  EQ(cond<C>(isMM, MACHINE_REGS_WORD, USER_REGS_WORD) + isZero.isZero.get() * 64 + idx.get(),
     wordAddr);
}

template <typename C> FDEV ValU32<C> DualReg<C>::getRS1() DEV {
  return readRs1.data.get();
}

template <typename C> FDEV ValU32<C> DualReg<C>::getRS2() DEV {
  return rs2Data.get();
}

template <typename C>
FDEV void
DualReg<C>::set(CTX, RegMemReadWitness rs1Wit, RegMemReadWitness rs2Wit, uint32_t cycle) DEV {
  rs1Idx.set(ctx, rs1Wit.wordAddr % 32);
  rs2Idx.set(ctx, rs2Wit.wordAddr % 32);
  readRs1.set(ctx, rs1Wit, cycle);
  readRs2.set(ctx, rs2Wit, cycle);
  sameReg.set(ctx, rs1Idx.get() == rs2Idx.get());
  if (sameReg.get() == 1) {
    rs2Data.set(ctx, rs1Wit.value);
  } else {
    rs2Data.set(ctx, rs2Wit.value);
  }
}

template <typename C> FDEV void DualReg<C>::verify(CTX, Val<C> cycle, Val<C> mode) DEV {
  Val<C> isMM = (mode - MODE_USER) * (mode - MODE_SUPERVISOR) * Val<C>(inv(Fp(6)));
  EQ(cond<C>(isMM, MACHINE_REGS_WORD, USER_REGS_WORD) + rs1Idx.get(), readRs1.wordAddr.get());
  EQ(cond<C>(isMM, MACHINE_REGS_WORD, USER_REGS_WORD) + sameReg.get() * 64 + rs2Idx.get(),
     readRs2.wordAddr.get());
  EQZ(sameReg.get() * (rs1Idx.get() - rs2Idx.get()));
  EQ(cond<C>(sameReg.get(), readRs1.data.low.get(), readRs2.data.low.get()), rs2Data.low.get());
  EQ(cond<C>(sameReg.get(), readRs1.data.high.get(), readRs2.data.high.get()), rs2Data.high.get());
}

// Local helper to invoke units
template <typename C>
FDEV static UnitArgument<C>
makeUnit(Val<C> opts, ValU32<C> a, ValU32<C> b, ValU32<C> out0, ValU32<C> out1) {
  UnitArgument<C> arg;
  arg.opts = opts;
  arg.aLow = a.low;
  arg.aHigh = a.high;
  arg.bLow = b.low;
  arg.bHigh = b.high;
  arg.out0Low = out0.low;
  arg.out0High = out0.high;
  arg.out1Low = out1.low;
  arg.out1High = out1.high;
  return arg;
}

template <typename C> FDEV void InstRegBlock<C>::set(CTX, InstRegWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  dr.set(ctx, wit.rs1, wit.rs2, wit.cycle);
  writeRd.set(ctx, wit.rd, wit.cycle);
  rd.set(ctx, wit.rd.wordAddr);
  Option opts(wit.options);
  opts.pop<InstKind>();
  outIdx.set(ctx, uint32_t(opts.pop<OutKind>()));
  optOut.set(ctx, opts.val);
  out0.set(ctx, wit.out0);
  out1.set(ctx, wit.out1);
}

template <typename C> FDEV void InstRegBlock<C>::verify(CTX) DEV {
  ValU32<C> out = cond<C>(outIdx.get(), out1.get(), out0.get());
  EQ(out.low, writeRd.data.low.get());
  EQ(out.high, writeRd.data.high.get());
}

template <typename C> FDEV void InstRegBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> mode = fetch.mode.get();
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), mode, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, fetch.nextPc.get(), mode, fetch.iCacheCycle.get()));
  ctx.pull(makeUnit(optOut.get(), dr.getRS1(), dr.getRS2(), out0.get(), out1.get()));
  DecodeArgument<C> arg;
  arg.iCacheCycle = fetch.iCacheCycle.get();
  arg.pcLow = fetch.pc.low.get();
  arg.pcLow = fetch.pc.high.get();
  arg.newPcLow = fetch.nextPc.low.get();
  arg.newPcLow = fetch.nextPc.high.get();
  arg.rs1 = dr.rs1Idx.get();
  arg.rs2 = dr.rs2Idx.get();
  arg.rd = rd.idx.get();
  arg.immLow = 0;
  arg.immHigh = 0;
  arg.options = Val<C>(OptSize<InstKind>::value) * (Val<C>(2) * optOut.get() + outIdx.get()) +
                Val<C>(uint32_t(INST_REG));
  ctx.pull(arg);
}

template <typename C> FDEV void InstImmBlock<C>::set(CTX, InstImmWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  readRs1.set(ctx, wit.rs1, wit.cycle);
  writeRd.set(ctx, wit.rd, wit.cycle);
  rs1.set(ctx, wit.rs1.wordAddr);
  rs2.set(ctx, wit.rs2);
  rd.set(ctx, wit.rd.wordAddr);
  imm.set(ctx, wit.imm);
  Option opts(wit.options);
  opts.pop<InstKind>();
  outIdx.set(ctx, uint32_t(opts.pop<OutKind>()));
  optOut.set(ctx, opts.val);
  out0.set(ctx, wit.out0);
  out1.set(ctx, wit.out1);
}

template <typename C> FDEV void InstImmBlock<C>::verify(CTX) DEV {
  ValU32<C> out = cond<C>(outIdx.get(), out1.get(), out0.get());
  EQ(out.low, writeRd.data.low.get());
  EQ(out.high, writeRd.data.high.get());
}

template <typename C> FDEV void InstImmBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> mode = fetch.mode.get();
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), mode, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, fetch.nextPc.get(), mode, fetch.iCacheCycle.get()));
  ctx.pull(makeUnit(optOut.get(), readRs1.data.get(), imm.get(), out0.get(), out1.get()));
  DecodeArgument<C> arg;
  arg.iCacheCycle = fetch.iCacheCycle.get();
  arg.pcLow = fetch.pc.low.get();
  arg.pcLow = fetch.pc.high.get();
  arg.newPcLow = fetch.nextPc.low.get();
  arg.newPcLow = fetch.nextPc.high.get();
  arg.rs1 = rs1.idx.get();
  arg.rs2 = rs2.get();
  arg.rd = rd.idx.get();
  arg.immLow = imm.low.get();
  arg.immHigh = imm.high.get();
  arg.options = Val<C>(OptSize<InstKind>::value) * (Val<C>(2) * optOut.get() + outIdx.get()) +
                Val<C>(uint32_t(INST_IMM));
  ctx.pull(arg);
}

template <typename C> FDEV void InstLoadBlock<C>::set(CTX, InstLoadWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  Option opts(wit.options);
  opts.pop<InstKind>();
  opt.set(ctx, opts.val);
  readRs1.set(ctx, wit.rs1, wit.cycle);
  writeRd.set(ctx, wit.rd, wit.cycle);
  rs1.set(ctx, wit.rs1.wordAddr);
  rs2.set(ctx, wit.rs2);
  rd.set(ctx, wit.rd.wordAddr);
  imm.set(ctx, wit.imm);
  computeAddr.set(ctx, wit.rs1.value, wit.imm);
  readAddr.set(ctx, wit.rs1.value + wit.imm);
  checkAddr.set(ctx, wit.rs1.value + wit.imm, wit.fetch.mode);
  readMem.set(ctx, wit.mem, wit.cycle);
  uint32_t valU32 = wit.mem.value;
  uint32_t valU16 = (readAddr.low1.get() == Val<C>(1)) ? (valU32 >> 16) : (valU32 & 0xffff);
  pickShort.set(ctx, valU16);
  b0.set(ctx, valU16 & 0xff);
  b1.set(ctx, valU16 >> 8);
  uint32_t valU8 = (readAddr.low0.get() == Val<C>(1)) ? (valU16 >> 8) : (valU16 & 0xff);
  pickByte.set(ctx, valU8);
  switch (opts.peek<LoadKind>()) {
  case LOAD_LB:
    signBit.set(ctx, valU8 << 24);
    break;
  case LOAD_LH:
    signBit.set(ctx, valU16 << 16);
    break;
  default:
    signBit.set(ctx, 0);
  }
}

template <typename C> FDEV Val<C> InstLoadBlock<C>::getSignBitInput() DEV {
  return (opt.bits[0].get() * pickByte.get() * 256) + (opt.bits[1].get() * pickShort.get());
}

template <typename C> FDEV void InstLoadBlock<C>::verify(CTX) DEV {
  EQ(readAddr.wordAddr(computeAddr.get()), readMem.getWordAddr());
  EQ(pickShort.get(),
     cond<C>(readAddr.low1.get(), readMem.data.high.get(), readMem.data.low.get()));
  EQ(pickShort.get(), b1.get() * 256 + b0.get());
  EQ(pickByte.get(), cond<C>(readAddr.low0.get(), b1.get(), b0.get()));
  EQ(writeRd.data.low.get(),
     opt.bits[0].get() * (signBit.get() * 255 * 256 + pickByte.get()) + // LB
         opt.bits[1].get() * pickShort.get() +                          // LH
         opt.bits[2].get() * readMem.data.low.get() +                   // LW
         opt.bits[3].get() * pickByte.get() +                           // LBU
         opt.bits[4].get() * pickShort.get());                          // LHU
  EQ(writeRd.data.high.get(),
     opt.bits[0].get() * signBit.get() * 65535 +       // LB
         opt.bits[1].get() * signBit.get() * 65535 +   // LH
         opt.bits[2].get() * readMem.data.high.get()); // LW
                                                       // LBU + LHU are zeros
}

template <typename C> FDEV void InstLoadBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> mode = fetch.mode.get();
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), mode, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, fetch.nextPc.get(), mode, fetch.iCacheCycle.get()));
  DecodeArgument<C> arg;
  arg.iCacheCycle = fetch.iCacheCycle.get();
  arg.pcLow = fetch.pc.low.get();
  arg.pcLow = fetch.pc.high.get();
  arg.newPcLow = fetch.nextPc.low.get();
  arg.newPcLow = fetch.nextPc.high.get();
  arg.rs1 = rs1.idx.get();
  arg.rs2 = rs2.get();
  arg.rd = rd.idx.get();
  arg.immLow = imm.low.get();
  arg.immHigh = imm.high.get();
  arg.options = Val<C>(OptSize<InstKind>::value) * (opt.get()) + Val<C>(uint32_t(INST_LOAD));
  ctx.pull(arg);
}

template <typename C> FDEV void InstStoreBlock<C>::set(CTX, InstStoreWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  Option opts(wit.options);
  opts.pop<InstKind>();
  opt.set(ctx, opts.val);
  dr.set(ctx, wit.rs1, wit.rs2, wit.cycle);
  rd.set(ctx, wit.rd);
  imm.set(ctx, wit.imm);
  computeAddr.set(ctx, wit.rs1.value, wit.imm);
  writeAddr.set(ctx, wit.rs1.value + wit.imm);
  checkAddr.set(ctx, wit.rs1.value + wit.imm, wit.fetch.mode);
  writeMem.set(ctx, wit.mem, wit.cycle);
  uint32_t valU32 = wit.mem.prevValue;
  uint32_t valU16 = (writeAddr.low1.get() == Val<C>(1)) ? (valU32 >> 16) : (valU32 & 0xffff);
  pickShort.set(ctx, valU16);
  psB0.set(ctx, valU16 & 0xff);
  psB1.set(ctx, valU16 >> 8);
  uint32_t valU8 = (writeAddr.low0.get() == Val<C>(1)) ? (valU16 >> 8) : (valU16 & 0xff);
  pickByte.set(ctx, valU8);
  lowB0.set(ctx, wit.rs2.value & 0xff);
  lowB1.set(ctx, ((wit.rs2.value) >> 8) & 0xff);
  uint32_t rs2Byte = wit.rs2.value & 0xff;
  if (opts.val == 0 && writeAddr.low0.get() == Val<C>(1)) {
    newShort.set(ctx, (rs2Byte << 8) | (valU16 & 0x00ff));
  } else if (opts.val == 0 && writeAddr.low0.get() == Val<C>(0)) {
    newShort.set(ctx, (valU16 & 0xff00) | (rs2Byte));
  } else {
    newShort.set(ctx, wit.rs2.value & 0xffff);
  }
}

template <typename C> FDEV void InstStoreBlock<C>::verify(CTX) DEV {
  EQ(writeAddr.wordAddr(computeAddr.get()), writeMem.getWordAddr());
  EQ(pickShort.get(),
     cond<C>(writeAddr.low1.get(), writeMem.prevData.high.get(), writeMem.prevData.low.get()));
  EQ(pickShort.get(), psB1.get() * 256 + psB0.get());
  EQ(pickByte.get(), cond<C>(writeAddr.low0.get(), psB1.get(), psB0.get()));
  EQ(dr.getRS2().low, lowB1.get() * 256 + lowB0.get());
  EQ(newShort.get(),
     opt.bits[0].get() * (writeAddr.low0.get()) * (lowB0.get() * 256 + psB0.get()) +
         opt.bits[0].get() * (Val<C>(1) - writeAddr.low0.get()) * (psB1.get() * 256 + lowB0.get()) +
         (opt.bits[1].get() + opt.bits[2].get()) * dr.getRS2().low);
  Val<C> notWord = opt.bits[0].get() + opt.bits[1].get();
  EQ(writeMem.data.low.get(),
     notWord * (writeAddr.low1.get()) * writeMem.prevData.low.get() +
         notWord * (Val<C>(1) - writeAddr.low1.get()) * newShort.get() +
         opt.bits[2].get() * dr.getRS2().low);
  EQ(writeMem.data.high.get(),
     notWord * (writeAddr.low1.get()) * newShort.get() +
         notWord * (Val<C>(1) - writeAddr.low1.get()) * writeMem.prevData.high.get() +
         opt.bits[2].get() * dr.getRS2().high);
}

template <typename C> FDEV void InstStoreBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> mode = fetch.mode.get();
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), mode, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, fetch.nextPc.get(), mode, fetch.iCacheCycle.get()));
  DecodeArgument<C> arg;
  arg.iCacheCycle = fetch.iCacheCycle.get();
  arg.pcLow = fetch.pc.low.get();
  arg.pcLow = fetch.pc.high.get();
  arg.newPcLow = fetch.nextPc.low.get();
  arg.newPcLow = fetch.nextPc.high.get();
  arg.rs1 = dr.rs1Idx.get();
  arg.rs2 = dr.rs2Idx.get();
  arg.rd = rd.get();
  arg.immLow = imm.low.get();
  arg.immHigh = imm.high.get();
  arg.options = Val<C>(OptSize<InstKind>::value) * (opt.get()) + Val<C>(uint32_t(INST_STORE));
  ctx.pull(arg);
}

template <typename C> FDEV void InstBranchBlock<C>::set(CTX, InstBranchWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  dr.set(ctx, wit.rs1, wit.rs2, wit.cycle);
  rd.set(ctx, wit.rd);
  imm.set(ctx, wit.imm);
  Option opts(wit.options);
  opts.pop<InstKind>();
  brnz.set(ctx, uint32_t(opts.pop<BrKind>()));
  outIdx.set(ctx, uint32_t(opts.pop<OutKind>()));
  optOut.set(ctx, opts.val);
  uint32_t out = (outIdx.get() == Val<C>(0)) ? wit.out0 : wit.out1;
  uint32_t outAdd = (out >> 16) + (out & 0xffff);
  isOutZero.set(ctx, Val<C>(outAdd));
  out0.set(ctx, wit.out0);
  out1.set(ctx, wit.out1);
  sumPc.set(ctx, wit.fetch.pc, wit.imm);
  newPc.set(ctx, wit.didBranch ? wit.fetch.pc + wit.imm : wit.fetch.nextPc);
}

template <typename C> FDEV void InstBranchBlock<C>::verify(CTX) DEV {
  Val<C> brnzVal = brnz.get();
  Val<C> isZeroVal = isOutZero.isZero.get();
  Val<C> doBranch = brnzVal * (Val<C>(1) - isZeroVal) + (Val<C>(1) - brnzVal) * isZeroVal;
  ValU32<C> checkNewPc = cond<C>(doBranch, sumPc.get(), fetch.nextPc.get());
  EQ(newPc.low.get(), checkNewPc.low);
  EQ(newPc.high.get(), checkNewPc.high);
}

template <typename C> FDEV void InstBranchBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> mode = fetch.mode.get();
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), mode, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, newPc.get(), mode, fetch.iCacheCycle.get()));
  ctx.pull(makeUnit(optOut.get(), dr.getRS1(), dr.getRS2(), out0.get(), out1.get()));
  DecodeArgument<C> arg;
  arg.iCacheCycle = fetch.iCacheCycle.get();
  arg.pcLow = fetch.pc.low.get();
  arg.pcLow = fetch.pc.high.get();
  arg.newPcLow = fetch.nextPc.low.get();
  arg.newPcLow = fetch.nextPc.high.get();
  arg.rs1 = dr.rs1Idx.get();
  arg.rs2 = dr.rs2Idx.get();
  arg.rd = rd.get();
  arg.immLow = imm.low.get();
  arg.immHigh = imm.high.get();
  Val<C> opt = optOut.get();
  opt = Val<C>(2) * opt + outIdx.get();
  opt = Val<C>(2) * opt + brnz.get();
  opt = Val<C>(OptSize<InstKind>::value) * opt + Val<C>(uint32_t(INST_BRANCH));
  arg.options = opt;
  ctx.pull(arg);
}

template <typename C> FDEV void InstJalBlock<C>::set(CTX, InstJalWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  rs1.set(ctx, wit.rs1);
  rs2.set(ctx, wit.rs2);
  writeRd.set(ctx, wit.rd, wit.cycle);
  rd.set(ctx, wit.rd.wordAddr);
  imm.set(ctx, wit.imm);
  sumPc.set(ctx, wit.fetch.pc, wit.imm);
}

template <typename C> FDEV void InstJalBlock<C>::verify(CTX) DEV {
  EQ(fetch.nextPc.low.get(), writeRd.data.low.get());
  EQ(fetch.nextPc.high.get(), writeRd.data.high.get());
}

template <typename C> FDEV void InstJalBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> mode = fetch.mode.get();
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), mode, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, sumPc.get(), mode, fetch.iCacheCycle.get()));
  DecodeArgument<C> arg;
  arg.iCacheCycle = fetch.iCacheCycle.get();
  arg.pcLow = fetch.pc.low.get();
  arg.pcLow = fetch.pc.high.get();
  arg.newPcLow = fetch.nextPc.low.get();
  arg.newPcLow = fetch.nextPc.high.get();
  arg.rs1 = rs1.get();
  arg.rs2 = rs2.get();
  arg.rd = rd.idx.get();
  arg.immLow = imm.low.get();
  arg.immHigh = imm.high.get();
  arg.options = Val<C>(uint32_t(INST_JAL));
  ctx.pull(arg);
}

template <typename C> FDEV void InstJalrBlock<C>::set(CTX, InstJalrWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  readRs1.set(ctx, wit.rs1, wit.cycle);
  rs1.set(ctx, wit.rs1.wordAddr);
  rs2.set(ctx, wit.rs2);
  writeRd.set(ctx, wit.rd, wit.cycle);
  rd.set(ctx, wit.rd.wordAddr);
  imm.set(ctx, wit.imm);
  sumPc.set(ctx, wit.rs1.value, wit.imm);
}

template <typename C> FDEV void InstJalrBlock<C>::verify(CTX) DEV {
  EQ(fetch.nextPc.low.get(), writeRd.data.low.get());
  EQ(fetch.nextPc.high.get(), writeRd.data.high.get());
}

template <typename C> FDEV void InstJalrBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> mode = fetch.mode.get();
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), mode, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, sumPc.get(), mode, fetch.iCacheCycle.get()));
  DecodeArgument<C> arg;
  arg.iCacheCycle = fetch.iCacheCycle.get();
  arg.pcLow = fetch.pc.low.get();
  arg.pcLow = fetch.pc.high.get();
  arg.newPcLow = fetch.nextPc.low.get();
  arg.newPcLow = fetch.nextPc.high.get();
  arg.rs1 = rs1.idx.get();
  arg.rs2 = rs2.get();
  arg.rd = rd.idx.get();
  arg.immLow = imm.low.get();
  arg.immHigh = imm.high.get();
  arg.options = Val<C>(uint32_t(INST_JALR));
  ctx.pull(arg);
}

template <typename C> FDEV void InstLuiBlock<C>::set(CTX, InstLuiWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  rs1.set(ctx, wit.rs1);
  rs2.set(ctx, wit.rs2);
  writeRd.set(ctx, wit.rd, wit.cycle);
  rd.set(ctx, wit.rd.wordAddr);
}

template <typename C> FDEV void InstLuiBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> mode = fetch.mode.get();
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), mode, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, fetch.nextPc.get(), mode, fetch.iCacheCycle.get()));
  DecodeArgument<C> arg;
  arg.iCacheCycle = fetch.iCacheCycle.get();
  arg.pcLow = fetch.pc.low.get();
  arg.pcLow = fetch.pc.high.get();
  arg.newPcLow = fetch.nextPc.low.get();
  arg.newPcLow = fetch.nextPc.high.get();
  arg.rs1 = rs1.get();
  arg.rs2 = rs2.get();
  arg.rd = rd.idx.get();
  arg.immLow = writeRd.data.low.get();
  arg.immHigh = writeRd.data.high.get();
  arg.options = Val<C>(uint32_t(INST_LUI));
  ctx.pull(arg);
}

template <typename C> FDEV void InstAuipcBlock<C>::set(CTX, InstAuipcWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  rs1.set(ctx, wit.rs1);
  rs2.set(ctx, wit.rs2);
  writeRd.set(ctx, wit.rd, wit.cycle);
  rd.set(ctx, wit.rd.wordAddr);
  imm.set(ctx, wit.imm);
  sumPc.set(ctx, wit.fetch.pc, wit.imm);
}

template <typename C> FDEV void InstAuipcBlock<C>::verify(CTX) DEV {
  EQ(sumPc.low.get(), writeRd.data.low.get());
  EQ(sumPc.high.get(), writeRd.data.high.get());
}

template <typename C> FDEV void InstAuipcBlock<C>::addArguments(CTX) DEV {
  Val<C> cycleVal = cycle.get();
  Val<C> mode = fetch.mode.get();
  ctx.pull(CpuStateArgument<C>(cycleVal, fetch.pc.get(), mode, fetch.iCacheCycle.get()));
  ctx.push(CpuStateArgument<C>(cycleVal + 1, fetch.nextPc.get(), mode, fetch.iCacheCycle.get()));
  DecodeArgument<C> arg;
  arg.iCacheCycle = fetch.iCacheCycle.get();
  arg.pcLow = fetch.pc.low.get();
  arg.pcLow = fetch.pc.high.get();
  arg.newPcLow = fetch.nextPc.low.get();
  arg.newPcLow = fetch.nextPc.high.get();
  arg.rs1 = rs1.get();
  arg.rs2 = rs2.get();
  arg.rd = rd.idx.get();
  arg.immLow = imm.low.get();
  arg.immHigh = imm.high.get();
  arg.options = Val<C>(uint32_t(INST_AUIPC));
  ctx.pull(arg);
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
  EQ(writeSavePc.wordAddr.get(), CSR_WORD(MEPC));
  EQ(readDispatch.wordAddr.get(), CSR_WORD(MTVEC));
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

template <typename C> FDEV void InstMretBlock<C>::set(CTX, InstMretWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  fetch.set(ctx, wit.fetch, wit.cycle);
  readPc.set(ctx, wit.readPc, wit.cycle);
  sumPc.set(ctx, wit.readPc.value, 4);
}

template <typename C> FDEV void InstMretBlock<C>::verify(CTX) DEV {
  // Make sure address constants is right
  EQ(readPc.wordAddr.get(), CSR_WORD(MEPC));
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
