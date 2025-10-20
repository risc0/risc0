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
//
template <typename C> FDEV void PhysMemReadBlock<C>::set(CTX, PhysMemReadWitness wit, uint32_t cycle) DEV {
  wordAddr.set(ctx, wit.wordAddr);
  prevCycle.set(ctx, wit.prevCycle);
  data.set(ctx, wit.value);
  // Compute cycle diff and make sure it is > 0
  uint32_t cycleDiff = 2 * cycle - wit.prevCycle;
  ctx.tableAdd(256 + 65536 + cycleDiff - 1, 1);
}

template <typename C> FDEV void PhysMemReadBlock<C>::addArguments(CTX, Val<C> cycle) DEV {
  ctx.pull(MemoryArgument<C>(wordAddr.get(), prevCycle.get(), data.low.get(), data.high.get()));
  ctx.push(MemoryArgument<C>(wordAddr.get(), cycle * 2, data.low.get(), data.high.get()));
  ctx.pull(LookupArgument<C>(2, cycle * 2 - prevCycle.get() - 1));
}

template <typename C>
FDEV void PhysMemWriteBlock<C>::set(CTX, PhysMemWriteWitness wit, uint32_t cycle) DEV {
  wordAddr.set(ctx, wit.wordAddr);
  prevCycle.set(ctx, wit.prevCycle);
  prevData.set(ctx, wit.prevValue);
  data.set(ctx, wit.value);
  // Compute cycle diff and make sure it is > 0
  uint32_t cycleDiff = 2 * cycle + 1 - wit.prevCycle;
  ctx.tableAdd(256 + 65536 + cycleDiff - 1, 1);
}

template <typename C> FDEV void PhysMemWriteBlock<C>::addArguments(CTX, Val<C> cycle) DEV {
  ctx.pull(
      MemoryArgument<C>(wordAddr.get(), prevCycle.get(), prevData.low.get(), prevData.high.get()));
  ctx.push(MemoryArgument<C>(wordAddr.get(), cycle * 2 + 1, data.low.get(), data.high.get()));
  ctx.pull(LookupArgument<C>(2, cycle * 2 + 1 - prevCycle.get() - 1));
}

template <typename C> FDEV void VirtAddrBlock<C>::set(CTX, VirtAddrWitness wit) DEV {
  vpage.set(ctx, wit.vpage);
  ppage.set(ctx, wit.ppage);
  lowByte.set(ctx, wit.wordOffset & 0xff);
  bit8.set(ctx, (wit.wordOffset >> 8) & 0x1);
  bit9.set(ctx, (wit.wordOffset >> 9) & 0x1);
}

template <typename C> FDEV void VirtMemReadBlock<C>::set(CTX, VirtMemReadWitness wit, uint32_t cycle) DEV {
  addr.set(ctx, wit.addr);
  prevCycle.set(ctx, wit.prevCycle);
  data.set(ctx, wit.value);
  // Compute cycle diff and make sure it is > 0
  uint32_t cycleDiff = 2 * cycle - wit.prevCycle;
  ctx.tableAdd(256 + 65536 + cycleDiff - 1, 1);
}

template <typename C> FDEV void VirtMemReadBlock<C>::addArguments(CTX, Val<C> cycle) DEV {
  ctx.pull(MemoryArgument<C>(addr.getWordAddr(), prevCycle.get(), data.low.get(), data.high.get()));
  ctx.push(MemoryArgument<C>(addr.getWordAddr(), cycle * 2, data.low.get(), data.high.get()));
  ctx.pull(LookupArgument<C>(2, cycle * 2 - prevCycle.get() - 1));
}

template <typename C>
FDEV void VirtMemWriteBlock<C>::set(CTX, VirtMemWriteWitness wit, uint32_t cycle) DEV {
  addr.set(ctx, wit.addr);
  prevCycle.set(ctx, wit.prevCycle);
  prevData.set(ctx, wit.prevValue);
  data.set(ctx, wit.value);
  // Compute cycle diff and make sure it is > 0
  uint32_t cycleDiff = 2 * cycle + 1 - wit.prevCycle;
  ctx.tableAdd(256 + 65536 + cycleDiff - 1, 1);
}

template <typename C> FDEV void VirtMemWriteBlock<C>::addArguments(CTX, Val<C> cycle) DEV {
  ctx.pull(
      MemoryArgument<C>(addr.getWordAddr(), prevCycle.get(), prevData.low.get(), prevData.high.get()));
  ctx.push(MemoryArgument<C>(addr.getWordAddr(), cycle * 2 + 1, data.low.get(), data.high.get()));
  ctx.pull(LookupArgument<C>(2, cycle * 2 + 1 - prevCycle.get() - 1));
}

template <typename C> FDEV void VirtAddrResolveBlock<C>::set(CTX, VirtAddrResolveBlock wit) DEV {
}

template <typename C> FDEV void VirtAddrResolveBlock<C>::verify(CTX) DEV {
}

template <typename C> FDEV void VirtAddrResolveBlock<C>::addArguments(CTX) DEV {
}

