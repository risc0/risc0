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

#include "rv32im/base/paging.h"

struct PageInNodeWitness {
  uint32_t index;
  FpDigest node;
  FpDigest left;
  FpDigest right;
};

struct PageInPartWitness {
  FpDigest in;
  FpDigest out;
  uint32_t addr;
  uint32_t data[PAGE_PART_SIZE];
};

struct PageInPageWitness {
  uint32_t addr;
  FpDigest node;
};

struct PageOutNodeWitness {
  uint32_t index;
  FpDigest node;
  FpDigest left;
  FpDigest right;
};

struct PageOutPartWitness {
  FpDigest in;
  FpDigest out;
  uint32_t addr;
  uint32_t data[PAGE_PART_SIZE];
  uint32_t cycle[PAGE_PART_SIZE];
};

struct PageOutPageWitness {
  uint32_t addr;
  FpDigest node;
};

struct PageUncleWitness {
  uint32_t index;
  FpDigest node;
};
