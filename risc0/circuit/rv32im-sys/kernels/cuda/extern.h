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

__device__ void extern_isTrap(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void extern_setUserMode(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void extern_halt(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void extern_trace(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void extern_log(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void extern_getMajor(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void extern_getMinor(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void extern_divide(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void
extern_bigintQuotient(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void extern_pageInfo(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void extern_ramWrite(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void extern_ramRead(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void
extern_plonkWrite_ram(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void
extern_plonkWrite_bytes(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void
extern_plonkRead_ram(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void
extern_plonkRead_bytes(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void extern_syscallInit(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void extern_syscallBody(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void extern_syscallFini(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void
extern_plonkWriteAccum_ram(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void
extern_plonkWriteAccum_bytes(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void
extern_plonkReadAccum_ram(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);

__device__ void
extern_plonkReadAccum_bytes(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs);
