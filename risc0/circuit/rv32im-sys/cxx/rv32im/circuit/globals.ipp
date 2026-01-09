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

template <typename C> FDEV void GlobalsBlock<C>::set(CTX, GlobalsWitness wit) DEV {
  p2Count.set(ctx, wit.p2Count);
  finalCycle.set(ctx, wit.finalCycle);

  // number of cycles is less than 2^25, so ceilDiv is less than 2^22. This
  // means 24 bits is sufficient to store its decomposition.
  uint32_t ceilDiv = (wit.finalCycle + 7) / 8;
  finalCycleCeilDiv.set(ctx, ceilDiv);
  ceilDivLow.set(ctx, ceilDiv & 0xffff);
  ceilDivHigh.set(ctx, (ceilDiv >> 16) & 0xff);
  delta.set(ctx, finalCycleCeilDiv.get() * 8 - wit.finalCycle);
  deltaTimes32.set(ctx, delta.get() * 32);

  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    rootIn[i].set(ctx, wit.rootIn[i]);
    GLOBAL_SET(rootIn[i], wit.rootIn[i]);
    rootOut[i].set(ctx, wit.rootOut[i]);
    GLOBAL_SET(rootOut[i], wit.rootOut[i]);
    povwNonce[i].low.set(ctx, wit.povwNonce[i] & 0xffff);
    GLOBAL_SET(povwNonce[i].low, wit.povwNonce[i] & 0xffff);
    povwNonce[i].high.set(ctx, wit.povwNonce[i] >> 16);
    GLOBAL_SET(povwNonce[i].high, wit.povwNonce[i] >> 16);
  }
}

template <typename C> FDEV void GlobalsBlock<C>::verify(CTX) DEV {
  // Make sure we are on the first row
  EQ(ctx.getX(), 1);

  // Verify finalCycleCeilDiv is the next multiple of 8 greater than finalCycle.
  // Note that delta must be in [0, 7] since both it and itself times 32 fit in
  // 8 bits. Furthermore, finalCycleCeilDiv must fit in 24 bits, which prevents
  // extraneous solutions due to field wraparound.
  EQ(finalCycle.get() + delta.get(), finalCycleCeilDiv.get() * 8);
  EQ(finalCycleCeilDiv.get(), ceilDivLow.get() + ceilDivHigh.get() * 65536);
  EQ(deltaTimes32.get(), delta.get() * 32);

  // Verify globals match columns
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    EQ(rootIn[i].get(), GLOBAL_GET(rootIn[i]));
    EQ(rootOut[i].get(), GLOBAL_GET(rootOut[i]));
    EQ(povwNonce[i].low.get(), GLOBAL_GET(povwNonce[i].low));
    EQ(povwNonce[i].high.get(), GLOBAL_GET(povwNonce[i].high));
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
