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
#include "supra/fp.h"

#include "kernels.h"

using namespace risc0::circuit::recursion;

extern "C" {

const char* risc0_circuit_recursion_cuda_eval_check(Fp* check,
                                                    const Fp* ctrl,
                                                    const Fp* data,
                                                    const Fp* accum,
                                                    const Fp* mix,
                                                    const Fp* out,
                                                    const Fp& rou,
                                                    uint32_t po2,
                                                    uint32_t domain,
                                                    const FpExt* poly_mix_pows) {
  cudaMemcpyToSymbol(poly_mix, poly_mix_pows, sizeof(poly_mix));
  return launchKernel(eval_check, domain, 0, check, ctrl, data, accum, mix, out, rou, po2, domain);
}

} // extern "C"
