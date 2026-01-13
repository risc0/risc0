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

// Set the selected bit to 1, zero all others
template <typename C, size_t N> FDEV void OneHot<C, N>::set(CTX, uint32_t val) DEV {
  for (uint32_t i = 0; i < N; i++) {
    bits[i].set(ctx, i == val ? 1 : 0);
  }
}

// Recover the original value by multiplying each bit by a constant
template <typename C, size_t N> FDEV Val<C> OneHot<C, N>::get() DEV {
  Val<C> tot = 0;
  for (uint32_t i = 0; i < N; i++) {
    tot += bits[i].get() * Val<C>(i);
  }
  return tot;
}

// In addition to being bits, they must sum to 1
template <typename C, size_t N> FDEV void OneHot<C, N>::verify(CTX) DEV {
  Val<C> sum = 0;
  for (uint32_t i = 0; i < N; i++) {
    sum += bits[i].get();
  }
  EQ(sum, 1);
}

template <typename C, size_t N, size_t M> FDEV void TwoHot<C, N, M>::set(CTX, uint32_t val) DEV {
  major.set(ctx, val / M);
  minor.set(ctx, val % M);
}

template <typename C, size_t N, size_t M> FDEV Val<C> TwoHot<C, N, M>::get() DEV {
  return major.get() * M + minor.get();
}

template <typename C, size_t N, size_t M> FDEV Val<C> TwoHot<C, N, M>::at(uint32_t offset) DEV {
  return major.bits[offset / M].get() * minor.bits[offset % M].get();
}
