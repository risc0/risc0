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

#include <array>
#include <vector>

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-variable"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

namespace risc0::circuit::rv32im {

Fp extern_isTrap(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args);

void extern_setUserMode(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args);

void extern_halt(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args);

void extern_trace(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args);

Fp extern_getMajor(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args);

Fp extern_getMinor(void* ctx, size_t cycle, const char* extra, std::array<Fp, 4> args);

std::array<Fp, 8> extern_divide(void* ctx, size_t cycle, const char* extra, std::array<Fp, 9> args);

std::array<Fp, 32>
extern_bigintQuotient(void* ctx, size_t cycle, const char* extra, std::array<Fp, 96> args);

std::array<Fp, 3>
extern_pageInfo(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args);

void extern_ramWrite(void* ctx, size_t cycle, const char* extra, std::array<Fp, 6> args);

std::array<Fp, 4>
extern_ramRead(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args);

void extern_plonkWrite_ram(void* ctx, size_t cycle, const char* extra, std::array<Fp, 7> args);

void extern_plonkWrite_bytes(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args);

std::array<Fp, 7>
extern_plonkRead_ram(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args);

std::array<Fp, 2>
extern_plonkRead_bytes(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args);

void extern_log(void* ctx, size_t cycle, const char* extra, std::vector<Fp> args);

void extern_syscallInit(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args);

std::array<Fp, 4>
extern_syscallBody(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args);

std::array<Fp, 8>
extern_syscallFini(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args);

void extern_plonkWriteAccum_ram(void* ctx, size_t cycle, const char* extra, std::array<Fp, 4> args);

void extern_plonkWriteAccum_bytes(void* ctx,
                                  size_t cycle,
                                  const char* extra,
                                  std::array<Fp, 4> args);

std::array<Fp, 4>
extern_plonkReadAccum_ram(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args);

std::array<Fp, 4>
extern_plonkReadAccum_bytes(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args);

} // namespace risc0::circuit::rv32im
