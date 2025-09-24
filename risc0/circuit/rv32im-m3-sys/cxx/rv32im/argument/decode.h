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
struct DecodeArgument {
  Val<C> iCacheCycle;
  Val<C> pcLow;
  Val<C> pcHigh;
  Val<C> newPcLow;
  Val<C> newPcHigh;
  Val<C> rs1;
  Val<C> rs2;
  Val<C> rd;
  Val<C> immLow;
  Val<C> immHigh;
  Val<C> options;
};
