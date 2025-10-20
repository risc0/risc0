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

template <typename C> FDEV void BigIntBlock<C>::set(CTX, BigIntWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  mm.set(ctx, wit.mm);
  readInst.set(ctx, wit.inst, wit.cycle);
  readBaseReg.set(ctx, wit.baseReg, wit.cycle);
  memOp.set(ctx, (wit.inst.value >> 28) & 0x0f);
  polyOp.set(ctx, (wit.inst.value >> 24) & 0x0f);
  for (size_t i = 0; i < 3; i++) {
    coeffBits[i].set(ctx, (wit.inst.value >> (21 + i)) & 1);
  }
  for (size_t i = 0; i < 5; i++) {
    regBits[i].set(ctx, (wit.inst.value >> (16 + i)) & 1);
  }
  uint32_t offsetVal = wit.inst.value & 0xffff;
  offset.set(ctx, offsetVal);
  offset16High.set(ctx, (offsetVal * 16) >> 16);
  offset16Low.set(ctx, (offsetVal * 16) & 0xffff);
  computeAddr.set(ctx, wit.baseReg.value, offsetVal * 16);
  isLastPage.set(ctx, computeAddr.get().high - 0xbfff);
  wordBase.set(ctx, wit.baseReg.value + offsetVal * 16);
  checkBase.set(ctx, wit.baseReg.value + offsetVal * 16, wit.mm * MODE_MACHINE);
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      bytes[i * 4 + j].set(ctx, (wit.data[i] >> (j * 8)) & 0xff);
    }
    prevCycle[i].set(ctx, wit.prevCycle[i]);
    prevValue[i].set(ctx, wit.prevValue[i]);
    uint32_t memCycle = wit.cycle * 2 + memOp.bits[1].get().asUInt32();
    uint32_t cycleDiff = memCycle - wit.prevCycle[i];
    if (memOp.get() != 2) {
      ctx.tableAdd(256 + 65536 + cycleDiff - 1, 1);
    }
  }
}

template <typename C> FDEV void BigIntBlock<C>::verify(CTX) DEV {
  // Verify instruction decoding
  EQ(readInst.data.high.get(),
     memOp.get() * (1 << 12) + polyOp.get() * (1 << 8) + getCoeff() * (1 << 5) + getReg());
  EQ(readInst.data.low.get(), offset.get());
  // Verify we are reading the right base register
  EQ(readBaseReg.wordAddr.get(), cond<C>(mm.get(), MACHINE_REGS_WORD, USER_REGS_WORD) + getReg());
  // Verify offset16 is 16 * offset
  EQ(offset16High.get() * 65536 + offset16Low.get(), offset.get() * 16);
  // Verify alignment
  EQZ(wordBase.low0.get() + wordBase.low1.get());
  // Disallow the base address to be in the last page of user space in user mode
  EQZ(isLastPage.isZero.get() * (Val<C>(1) - mm.get()));
  // Verify reads are reads
  for (size_t i = 0; i < 4; i++) {
    ValU32<C> word(bytes[i * 4 + 0].get() + bytes[i * 4 + 1].get() * 256,
                   bytes[i * 4 + 2].get() + bytes[i * 4 + 3].get() * 256);
    EQZ(memOp.bits[0].get() * (word.low - prevValue[i].low.get()));
    EQZ(memOp.bits[0].get() * (word.high - prevValue[i].high.get()));
  }
}

template <typename C> FDEV void BigIntBlock<C>::addArguments(CTX) DEV {
  Val<C> doMem = memOp.bits[0].get() + memOp.bits[1].get();
  Val<C> addr = wordBase.wordAddr(computeAddr.get());
  Val<C> cycleVal = cycle.get();
  Val<C> memCycleVal = cycleVal * 2 + memOp.bits[1].get();
  for (size_t i = 0; i < 4; i++) {
    ValU32<C> word(bytes[i * 4 + 0].get() + bytes[i * 4 + 1].get() * 256,
                   bytes[i * 4 + 2].get() + bytes[i * 4 + 3].get() * 256);
    ctx.addArgument(
        -doMem,
        MemoryArgument<C>(
            addr + i, prevCycle[i].get(), prevValue[i].get().low, prevValue[i].get().high));
    ctx.addArgument(doMem, MemoryArgument<C>(addr + i, memCycleVal, word.low, word.high));
    ctx.addArgument(-doMem, LookupArgument<C>(2, memCycleVal - prevCycle[i].get() - 1));
  }
  Val<C> oldPcWord = readInst.wordAddr.get();
  ctx.pull(BigIntCpuStateArgument<C>(cycleVal, oldPcWord, mm.get()));
  ctx.push(BigIntCpuStateArgument<C>(cycleVal + 1, oldPcWord + 1, mm.get()));
}
