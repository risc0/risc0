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
//
template <typename C>
FDEV void PhysMemReadBlock<C>::set(CTX, PhysMemReadWitness wit, uint32_t cycle) DEV {
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
