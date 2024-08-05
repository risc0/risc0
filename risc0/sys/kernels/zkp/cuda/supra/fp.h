// Copyright 2024 RISC Zero, Inc.
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

#include <ff/baby_bear.hpp>

static __device__ bb31_t pow(bb31_t b, int e) {
  return b ^ (unsigned int)e;
}

static __device__ bb31_t inv(bb31_t a) {
  return a.reciprocal();
}

typedef bb31_t Fp;
typedef bb31_4_t Fp4;
typedef bb31_4_t FpExt;
