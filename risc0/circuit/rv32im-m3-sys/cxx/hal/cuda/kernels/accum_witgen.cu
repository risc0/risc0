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

#include "fp.h"
#include "hal/po2s.h"
#include "hal/cuda/kernels/base.h"

#define PO2(x) \
extern "C" void accum_witgen_cuda_ ## x(Fp* accum, const Fp* data, const Fp* globals, const FpExt* accMix, Fp rou);
PO2S
#undef PO2

extern "C" void accum_witgen_cuda(Fp* accum, const Fp* data, const Fp* globals, const FpExt* accMix, Fp rou, uint32_t numRows) {
  uint32_t po2 = 31 - __builtin_clz(numRows);
  switch(po2) {
#define PO2(x) \
    case x: \
      accum_witgen_cuda_ ## x(accum, data, globals, accMix, rou); \
      break;
PO2S
#undef PO2
  }
}
