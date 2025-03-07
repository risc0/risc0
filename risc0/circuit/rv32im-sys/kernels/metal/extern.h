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

void extern_halt(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_trace(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_log(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_getMajor(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_getMinor(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_divide(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_bigintQuotient(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_pageInfo(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_ramWrite(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_ramRead(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_plonkWrite_ram(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_plonkWrite_bytes(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_plonkRead_ram(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_plonkRead_bytes(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_syscallInit(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_syscallBody(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_syscallFini(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_plonkWriteAccum_ram(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_plonkWriteAccum_bytes(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_plonkReadAccum_ram(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);

void extern_plonkReadAccum_bytes(
    device void* ctx, uint32_t cycle, const constant char* extra, Fp args[96], Fp outs[32]);
