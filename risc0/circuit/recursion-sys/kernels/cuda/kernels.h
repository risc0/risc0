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

#include <cstdint>

namespace risc0::circuit::recursion {

extern __constant__ FpExt poly_mix[158];

__global__ void step_compute_accum(
    const Fp* ctrl, const Fp* data, const Fp* mix, FpExt* wom, uint32_t steps, uint32_t count);

__global__ void step_verify_accum(const Fp* ctrl,
                                  const Fp* data,
                                  const Fp* mix,
                                  FpExt* wom,
                                  Fp* accum,
                                  uint32_t steps,
                                  uint32_t count);

__global__ void eval_check(Fp* check,
                           const Fp* ctrl,
                           const Fp* data,
                           const Fp* accum,
                           const Fp* mix,
                           const Fp* out,
                           const Fp rou,
                           uint32_t po2,
                           uint32_t domain);

} // namespace risc0::circuit::recursion
