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

#include "fp.h"

void step_exec(device void* ctx,
               uint32_t steps,
               uint32_t cycle,
               device Fp* arg0,
               device Fp* arg1,
               device Fp* arg2,
               device Fp* arg3,
               device Fp* arg4);

void step_verify_mem(device void* ctx,
                     uint32_t steps,
                     uint32_t cycle,
                     device Fp* arg0,
                     device Fp* arg1,
                     device Fp* arg2,
                     device Fp* arg3,
                     device Fp* arg4);

void step_verify_bytes(device void* ctx,
                       uint32_t steps,
                       uint32_t cycle,
                       device Fp* arg0,
                       device Fp* arg1,
                       device Fp* arg2,
                       device Fp* arg3,
                       device Fp* arg4);

void step_compute_accum(device void* ctx,
                        uint32_t steps,
                        uint32_t cycle,
                        device Fp* arg0,
                        device Fp* arg1,
                        device Fp* arg2,
                        device Fp* arg3,
                        device Fp* arg4);

void step_verify_accum(device void* ctx,
                       uint32_t steps,
                       uint32_t cycle,
                       device Fp* arg0,
                       device Fp* arg1,
                       device Fp* arg2,
                       device Fp* arg3,
                       device Fp* arg4);
