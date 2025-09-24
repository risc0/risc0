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

#define UNIT_WITNESS(x) \
struct Unit ## x ## Witness { \
  uint32_t count; \
  uint32_t opts; \
  uint32_t a; \
  uint32_t b; \
  uint32_t out0; \
  uint32_t out1; \
};

// Not a real unit, used as a generic unit type in fast_emu
UNIT_WITNESS(Base)

UNIT_WITNESS(AddSub)
UNIT_WITNESS(Bit)
UNIT_WITNESS(Lt)
UNIT_WITNESS(Mul)
UNIT_WITNESS(Div)
UNIT_WITNESS(Shift)

