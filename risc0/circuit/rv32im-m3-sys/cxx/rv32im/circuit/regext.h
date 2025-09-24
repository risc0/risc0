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

#pragma once

#include "rv32im/base/base.h"

template<typename C>
struct RegExt {
  CONSTANT static char NAME[] = "RegExt";

  Reg<C> elems[4];

  template<typename T>
  FDEV void applyInner(CTX) DEV {
    T::apply(ctx, elems);
  }

  FDEV void set(CTX, ValExt<C> val) DEV {
    for (size_t i = 0; i < 4; i++) {
      elems[i].set(ctx, val.elem(i));
    }
  }
  FDEV ValExt<C> get() DEV {
    return ValExt<C>(elems[0].get(), elems[1].get(), elems[2].get(), elems[3].get());
  }
  FDEV inline void finalize(CTX) DEV {}
  FDEV void verify(CTX) DEV {}
  FDEV void addArguments(CTX) DEV {}
};
