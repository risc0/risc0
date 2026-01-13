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

template <typename C> FDEV void RegU8<C>::set(CTX, Val<C> in) DEV {
  inner.set(ctx, in);
  uint32_t val = in.asUInt32();
  // This shouldn't happen, but make sure we don't corrupt memory
  if (val >= 256) {
    LOG(0, "ILLEGAL SET OF REGU8: " << val);
    val = 0;
  }
  ctx.tableAdd(val, 1);
}

template <typename C> FDEV Val<C> RegU8<C>::get() DEV {
  return inner.get();
}

template <typename C> FDEV void RegU8<C>::addArguments(CTX) DEV {
  ctx.pull(LookupArgument<C>(0, inner.get()));
}

template <typename C> FDEV void RegU16<C>::set(CTX, Val<C> in) DEV {
  inner.set(ctx, in);
  uint32_t val = in.asUInt32();
  // This shouldn't happen, but make sure we don't corrupt memory
  if (val >= 65536) {
    LOG(0, "ILLEGAL SET OF REGU16: " << val);
    val = 0;
  }
  ctx.tableAdd(256 + val, 1);
}

template <typename C> FDEV Val<C> RegU16<C>::get() DEV {
  return inner.get();
}

template <typename C> FDEV void RegU16<C>::addArguments(CTX) DEV {
  ctx.pull(LookupArgument<C>(1, inner.get()));
}

template <typename C> FDEV void MakeTableBlock<C>::set(CTX, MakeTableWitness wit) DEV {
  table.set(ctx, wit.table);
  start.set(ctx, wit.start);
}

template <typename C> FDEV void MakeTableBlock<C>::finalize(CTX) DEV {
  uint32_t theTable = table.get().asUInt32();
  uint32_t pos = start.get().asUInt32();
  if (theTable > 0) {
    pos += 256;
  }
  if (theTable > 1) {
    pos += 65536;
  }
  for (size_t i = 0; i < 16; i++) {
    useCount[i].set(ctx, ctx.tableGet(pos + i));
  }
}

#define TABLE_ARGUMENT(ctx, ta) PICUS_ARGUMENT(ctx, {}, ({ctx.get(ta.table), ctx.get(ta.start)}))

template <typename C> FDEV void MakeTableBlock<C>::verify(CTX) DEV {}

template <typename C> FDEV void MakeTableBlock<C>::addArguments(CTX) DEV {
  MakeTableArgument<C> ta(table.get(), start.get());
  ctx.pull(ta);
  TABLE_ARGUMENT(ctx, ta);
  ctx.push(MakeTableArgument<C>(table.get(), start.get() + 16));

  for (size_t i = 0; i < 16; i++) {
    PICUS_INPUT(ctx, useCount[i]);
    ctx.addArgument(useCount[i].get(), LookupArgument<C>(table.get(), start.get() + i));
  }
}
