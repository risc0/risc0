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
struct CpuStateArgument {
  FDEV CpuStateArgument() = default;
  FDEV CpuStateArgument(Val<C> cycle, Val<C> pcLow, Val<C> pcHigh, Val<C> mm, Val<C> iCache) 
    : cycle(cycle), pcLow(pcLow), pcHigh(pcHigh), mm(mm), iCache(iCache) {}
  FDEV CpuStateArgument(Val<C> cycle, ValU32<C> pc, Val<C> mm, Val<C> iCache) 
    : cycle(cycle), pcLow(pc.low), pcHigh(pc.high), mm(mm), iCache(iCache) {}

  Val<C> cycle;
  Val<C> pcLow;
  Val<C> pcHigh;
  Val<C> mm;
  Val<C> iCache;
};

template<typename C>
struct BigIntCpuStateArgument {
  FDEV BigIntCpuStateArgument() = default;
  FDEV BigIntCpuStateArgument(Val<C> cycle, Val<C> pcWord, Val<C> mm) 
    : cycle(cycle), pcWord(pcWord), mm(mm) {}

  Val<C> cycle;
  Val<C> pcWord;
  Val<C> mm;
};

