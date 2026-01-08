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

template <typename C> FDEV void ReadByteBlock<C>::set(CTX, ReadByteWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  lowBit0.set(ctx, wit.lowBits % 2);
  lowBit1.set(ctx, wit.lowBits / 2);
  io.set(ctx, wit.io, wit.cycle);
  uint32_t theShort = (wit.io.prevValue >> ((wit.lowBits / 2) * 16)) & 0xffff;
  lowByte.set(ctx, theShort & 0xff);
  highByte.set(ctx, theShort >> 8);
  newByte.set(ctx, (wit.io.value >> (wit.lowBits * 8)) & 0xff);
  is3.set(ctx, wit.lowBits == 3);
  sizeMinus1.set(ctx, wit.size - 1);
}

template <typename C> FDEV void ReadByteBlock<C>::verify(CTX) DEV {
  Val<C> lb1 = lowBit1.get();
  // Verify we don't change non-selected short
  EQ(lb1 * io.prevData.low.get() + (Val<C>(1) - lb1) * io.prevData.high.get(),
     lb1 * io.data.low.get() + (Val<C>(1) - lb1) * io.data.high.get());
  // Get original + modified short
  Val<C> origShort = lb1 * io.prevData.high.get() + (Val<C>(1) - lb1) * io.prevData.low.get();
  Val<C> newShort = lb1 * io.data.high.get() + (Val<C>(1) - lb1) * io.data.low.get();
  // Verify split into byte of original data is correct
  EQ(origShort, lowByte.get() + highByte.get() * 256);
  // Verify newShort is updated version of old data
  Val<C> lb0 = lowBit0.get();
  Val<C> newB0 = lb0 * lowByte.get() + (Val<C>(1) - lb0) * newByte.get();
  Val<C> newB1 = lb0 * newByte.get() + (Val<C>(1) - lb0) * highByte.get();
  EQ(newShort, newB0 + newB1 * 256);
  // Verify is3 is correct
  EQ(is3.get(), lb0 * lb1);
}

template <typename C> FDEV void ReadByteBlock<C>::addArguments(CTX) DEV {
  Val<C> newAddr = io.wordAddr.get() + is3.get();
  Val<C> low3 = lowBit0.get() + lowBit1.get() * 2;
  Val<C> newLow3 = Val<C>(1) + low3 - is3.get() * 4;
  // Read + write state
  ctx.pull(ReadStateArgument<C>(cycle.get(), io.wordAddr.get(), low3, sizeMinus1.get() + 1));
  ctx.push(ReadStateArgument<C>(cycle.get() + 1, newAddr, newLow3, sizeMinus1.get()));
}

template <typename C> FDEV void ReadWordBlock<C>::set(CTX, ReadWordWitness wit) DEV {
  cycle.set(ctx, wit.cycle);
  sizeMinus4.set(ctx, wit.size - 4);
  io.set(ctx, wit.io, wit.cycle);
}

template <typename C> FDEV void ReadWordBlock<C>::verify(CTX) DEV {
  // NOTHING TO DO
}

template <typename C> FDEV void ReadWordBlock<C>::addArguments(CTX) DEV {
  ctx.pull(ReadStateArgument<C>(cycle.get(), io.wordAddr.get(), 0, sizeMinus4.get() + 4));
  ctx.push(ReadStateArgument<C>(cycle.get() + 1, io.wordAddr.get() + 1, 0, sizeMinus4.get()));
}
