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

template <typename C> FDEV void PageInNodeBlock<C>::set(CTX, PageInNodeWitness wit) DEV {
  index.set(ctx, wit.index);
  SET_ARR(node, wit.node, CELLS_DIGEST);
  SET_ARR(left, wit.left, CELLS_DIGEST);
  SET_ARR(right, wit.right, CELLS_DIGEST);
}

template <typename C> FDEV void PageInNodeBlock<C>::addArguments(CTX) DEV {
  PageInArgument<C> piNode;
  piNode.index = index.get();
  GET_ARR(piNode.node, node, CELLS_DIGEST);
  ctx.pull(piNode);
  piNode.index = Val<C>(2) * index.get();
  GET_ARR(piNode.node, left, CELLS_DIGEST);
  ctx.push(piNode);
  piNode.index = Val<C>(2) * index.get() + 1;
  GET_ARR(piNode.node, right, CELLS_DIGEST);
  ctx.push(piNode);
  P2CallArgument<C> call;
  call.isFinal = 1;
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    call.in[i] = 0;
    call.data[i] = right[i].get();
    call.data[CELLS_DIGEST + i] = left[i].get();
    call.out[i] = node[i].get();
  }
  ctx.pull(call);
}

template <typename C> FDEV void PageInPartBlock<C>::set(CTX, PageInPartWitness wit) DEV {
  uint32_t part = (wit.addr / MPAGE_PART_SIZE) % NUM_PARTS;
  addr.set(ctx, wit.addr);
  partNum.set(ctx, part);
  SET_ARR(in, wit.in, CELLS_DIGEST);
  SET_ARR(out, wit.out, CELLS_DIGEST);
  for (size_t i = 0; i < MPAGE_PART_SIZE; i++) {
    data[i].set(ctx, wit.data[i]);
  }
  lastPart.set(ctx, NUM_PARTS - 1 - part);
}

template <typename C> FDEV void PageInPartBlock<C>::addArguments(CTX) DEV {
  Val<C> addrVal = addr.get();
  for (size_t i = 0; i < MPAGE_PART_SIZE; i++) {
    ctx.push(MemoryArgument<C>(addrVal + i, 0, data[i].low.get(), data[i].high.get()));
  }
  PageInPartArgument<C> pip;
  pip.addr = addrVal;
  pip.partNum = partNum.get();
  GET_ARR(pip.node, in, CELLS_DIGEST);
  ctx.pull(pip);
  pip.addr = addrVal + MPAGE_PART_SIZE;
  pip.partNum = partNum.get() + 1;
  GET_ARR(pip.node, out, CELLS_DIGEST);
  ctx.push(pip);
  P2CallArgument<C> call;
  call.isFinal = lastPart.isZero.get();
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    call.in[i] = in[i].get();
    call.data[2 * i] = Val<C>(943718400) * data[i].low.get();
    call.data[2 * i + 1] = Val<C>(943718400) * data[i].high.get();
    call.out[i] = out[i].get();
  }
  ctx.pull(call);
}

template <typename C> FDEV void PageInPageBlock<C>::set(CTX, PageInPageWitness wit) DEV {
  addr.set(ctx, wit.addr);
  SET_ARR(node, wit.node, CELLS_DIGEST);
}

template <typename C> FDEV void PageInPageBlock<C>::addArguments(CTX) DEV {
  PageInArgument<C> pi;
  pi.index = addr.get() * inv(Fp(uint32_t(MPAGE_SIZE_WORDS))) + MEMORY_SIZE_MPAGES;
  GET_ARR(pi.node, node, CELLS_DIGEST);
  ctx.pull(pi);
  PageInPartArgument<C> pip;
  pip.addr = addr.get();
  pip.partNum = 0;
  ctx.push(pip);
  pip.addr = addr.get() + MPAGE_SIZE_WORDS;
  pip.partNum = NUM_PARTS;
  GET_ARR(pip.node, node, CELLS_DIGEST);
  ctx.pull(pip);
}

template <typename C> FDEV void PageOutNodeBlock<C>::set(CTX, PageOutNodeWitness wit) DEV {
  index.set(ctx, wit.index);
  SET_ARR(node, wit.node, CELLS_DIGEST);
  SET_ARR(left, wit.left, CELLS_DIGEST);
  SET_ARR(right, wit.right, CELLS_DIGEST);
}

template <typename C> FDEV void PageOutNodeBlock<C>::addArguments(CTX) DEV {
  PageOutArgument<C> piNode;
  piNode.index = index.get();
  GET_ARR(piNode.node, node, CELLS_DIGEST);
  ctx.push(piNode);
  piNode.index = Val<C>(2) * index.get();
  GET_ARR(piNode.node, left, CELLS_DIGEST);
  ctx.pull(piNode);
  piNode.index = Val<C>(2) * index.get() + 1;
  GET_ARR(piNode.node, right, CELLS_DIGEST);
  ctx.pull(piNode);
  P2CallArgument<C> call;
  call.isFinal = 1;
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    call.in[i] = 0;
    call.data[i] = right[i].get();
    call.data[CELLS_DIGEST + i] = left[i].get();
    call.out[i] = node[i].get();
  }
  ctx.pull(call);
}

template <typename C> FDEV void PageOutPartBlock<C>::set(CTX, PageOutPartWitness wit) DEV {
  uint32_t part = (wit.addr / MPAGE_PART_SIZE) % NUM_PARTS;
  addr.set(ctx, wit.addr);
  partNum.set(ctx, part);
  SET_ARR(in, wit.in, CELLS_DIGEST);
  SET_ARR(out, wit.out, CELLS_DIGEST);
  for (size_t i = 0; i < MPAGE_PART_SIZE; i++) {
    data[i].set(ctx, wit.data[i]);
    cycle[i].set(ctx, wit.cycle[i]);
  }
  lastPart.set(ctx, NUM_PARTS - 1 - part);
}

template <typename C> FDEV void PageOutPartBlock<C>::addArguments(CTX) DEV {
  Val<C> addrVal = addr.get();
  for (size_t i = 0; i < MPAGE_PART_SIZE; i++) {
    ctx.pull(MemoryArgument<C>(addrVal + i, cycle[i].get(), data[i].low.get(), data[i].high.get()));
  }
  PageOutPartArgument<C> pop;
  pop.addr = addrVal;
  pop.partNum = partNum.get();
  GET_ARR(pop.node, in, CELLS_DIGEST);
  ctx.pull(pop);
  pop.addr = addrVal + MPAGE_PART_SIZE;
  pop.partNum = partNum.get() + 1;
  GET_ARR(pop.node, out, CELLS_DIGEST);
  ctx.push(pop);
  P2CallArgument<C> call;
  call.isFinal = lastPart.isZero.get();
  for (size_t i = 0; i < CELLS_DIGEST; i++) {
    call.in[i] = in[i].get();
    call.data[2 * i] = Val<C>(943718400) * data[i].low.get();
    call.data[2 * i + 1] = Val<C>(943718400) * data[i].high.get();
    call.out[i] = out[i].get();
  }
  ctx.pull(call);
}

template <typename C> FDEV void PageOutPageBlock<C>::set(CTX, PageOutPageWitness wit) DEV {
  addr.set(ctx, wit.addr);
  SET_ARR(node, wit.node, CELLS_DIGEST);
}

template <typename C> FDEV void PageOutPageBlock<C>::addArguments(CTX) DEV {
  PageOutArgument<C> po;
  po.index = addr.get() * inv(Fp(uint32_t(MPAGE_SIZE_WORDS))) + MEMORY_SIZE_MPAGES;
  GET_ARR(po.node, node, CELLS_DIGEST);
  ctx.push(po);
  PageOutPartArgument<C> pop;
  pop.addr = addr.get();
  pop.partNum = 0;
  ctx.push(pop);
  pop.addr = addr.get() + MPAGE_SIZE_WORDS;
  pop.partNum = NUM_PARTS;
  GET_ARR(pop.node, node, CELLS_DIGEST);
  ctx.pull(pop);
}

template <typename C> FDEV void PageUncleBlock<C>::set(CTX, PageUncleWitness wit) DEV {
  index.set(ctx, wit.index);
  SET_ARR(node, wit.node, CELLS_DIGEST);
}

template <typename C> FDEV void PageUncleBlock<C>::addArguments(CTX) DEV {
  PageInArgument<C> pi;
  pi.index = index.get();
  GET_ARR(pi.node, node, CELLS_DIGEST);
  ctx.pull(pi);
  PageOutArgument<C> po;
  po.index = index.get();
  GET_ARR(po.node, node, CELLS_DIGEST);
  ctx.push(po);
}
