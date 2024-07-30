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

#include "cuda.h"
#include "fp.h"
#include "fpext.h"
#include "kernels.h"

using namespace risc0::circuit::recursion;

extern "C" {

const char* risc0_circuit_recursion_cuda_step_compute_accum(
    const Fp* ctrl, const Fp* data, const Fp* mix, FpExt* wom, uint32_t steps, uint32_t count) {
  return launchKernel(step_compute_accum, count, 0, ctrl, data, mix, wom, steps, count);
}

const char* risc0_circuit_recursion_cuda_step_verify_accum(const Fp* ctrl,
                                                           const Fp* data,
                                                           const Fp* mix,
                                                           FpExt* wom,
                                                           Fp* accum,
                                                           uint32_t steps,
                                                           uint32_t count) {
  return launchKernel(step_verify_accum, count, 0, ctrl, data, mix, wom, accum, steps, count);
}

} // extern "C"
