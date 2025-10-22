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

template <typename C> FDEV void GlobalsBlock<C>::set(CTX, GlobalsWitness wit) DEV {
  p2Count.set(ctx, wit.p2Count);
  finalCycle.set(ctx, wit.finalCycle);
  finalCycleCeilDiv.set(ctx, (wit.finalCycle + 7) / 8);
  // CeilDiv * 8 must be >= original
  checkRoundedGT.set(ctx, finalCycleCeilDiv.get() * 8 - finalCycle.get());
  // original + 7 must be >= CeilDiv * 8
  checkRoundedLT.set(ctx, finalCycle.get() + 7 - finalCycleCeilDiv.get() * 8);
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    rootIn[i].set(ctx, wit.rootIn[i]);
    GLOBAL_SET(rootIn[i], wit.rootIn[i]);
    rootOut[i].set(ctx, wit.rootOut[i]);
    GLOBAL_SET(rootOut[i], wit.rootOut[i]);
  }
}

template <typename C> FDEV void GlobalsBlock<C>::verify(CTX) DEV {
  // Make sure we are on the first row
  EQ(ctx.getX(), 1);
  // Verify finalCycleCeilDiv
  EQ(checkRoundedGT.get(), finalCycleCeilDiv.get() * 8 - finalCycle.get());
  EQ(checkRoundedLT.get(), finalCycle.get() + 7 - finalCycleCeilDiv.get() * 8);
  // Verify globals match columns
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    EQ(rootIn[i].get(), GLOBAL_GET(rootIn[i]));
    EQ(rootOut[i].get(), GLOBAL_GET(rootOut[i]));
  }
}

template <typename C> FDEV void GlobalsBlock<C>::addArguments(CTX) DEV {
  PageInArgument<C> piNode;
  piNode.index = 1;
  GET_ARR(piNode.node, rootIn, CELLS_DIGEST);
  ctx.push(piNode);
  PageOutArgument<C> poNode;
  poNode.index = 1;
  GET_ARR(poNode.node, rootOut, CELLS_DIGEST);
  ctx.pull(poNode);
  ctx.push(MakeTableArgument<C>(0, 0));
  ctx.pull(MakeTableArgument<C>(0, 256));
  ctx.push(MakeTableArgument<C>(1, 0));
  ctx.pull(MakeTableArgument<C>(1, 65536));
  ctx.push(MakeTableArgument<C>(2, 0));
  ctx.pull(MakeTableArgument<C>(2, finalCycleCeilDiv.get() * 16));
  ctx.push(CpuStateArgument<C>(1, 0, 0, 0, 1));
  ctx.pull(CpuStateArgument<C>(finalCycle.get(), 0, 0, 0, 0));
  ctx.push(P2IdArgument<C>(0));
  ctx.pull(P2IdArgument<C>(p2Count.get()));
}
