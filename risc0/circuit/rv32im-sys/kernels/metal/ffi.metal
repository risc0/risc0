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

#include "kernels.h"

kernel void k_step_exec(device void* ctx,
                        const device uint32_t& steps,
                        uint32_t cycle [[thread_position_in_grid]],
                        device Fp* arg0,
                        device Fp* arg1,
                        device Fp* arg2,
                        device Fp* arg3,
                        device Fp* arg4) {
  // step_exec(ctx, steps, cycle, arg0, arg1, arg2, arg3, arg4);
}

kernel void k_step_verify_mem(device void* ctx,
                        const device uint32_t& steps,
                        uint32_t cycle [[thread_position_in_grid]],
                        device Fp* arg0,
                        device Fp* arg1,
                        device Fp* arg2,
                        device Fp* arg3,
                        device Fp* arg4) {
  // step_verify_mem(ctx, steps, cycle, arg0, arg1, arg2, arg3, arg4);
}

kernel void k_step_verify_bytes(device void* ctx,
                        const device uint32_t& steps,
                        uint32_t cycle [[thread_position_in_grid]],
                        device Fp* arg0,
                        device Fp* arg1,
                        device Fp* arg2,
                        device Fp* arg3,
                        device Fp* arg4) {
  // step_verify_bytes(ctx, steps, cycle, arg0, arg1, arg2, arg3, arg4);
}

kernel void k_step_compute_accum(device void* ctx,
                                 const device uint32_t& steps,
                                 uint32_t cycle [[thread_position_in_grid]],
                                 device Fp* arg0,
                                 device Fp* arg1,
                                 device Fp* arg2,
                                 device Fp* arg3,
                                 device Fp* arg4) {
  step_compute_accum(ctx, steps, cycle, arg0, arg1, arg2, arg3, arg4);
}

kernel void k_step_verify_accum(device void* ctx,
                                const device uint32_t& steps,
                                uint32_t cycle [[thread_position_in_grid]],
                                device Fp* arg0,
                                device Fp* arg1,
                                device Fp* arg2,
                                device Fp* arg3,
                                device Fp* arg4) {
  step_verify_accum(ctx, steps, cycle, arg0, arg1, arg2, arg3, arg4);
}
