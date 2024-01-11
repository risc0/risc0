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
#include "fpext.h"

#include <cstdint>
#include <exception>
#include <string>

using Callback =
    bool(void*, const char*, const char*, const risc0::Fp*, size_t, risc0::Fp*, size_t);

struct risc0_string {
  std::string str;
};

struct risc0_error {
  risc0_string* msg;
};

extern "C" const char* risc0_circuit_recursion_string_ptr(risc0_string* str);

extern "C" void risc0_circuit_recursion_string_free(risc0_string* str);

template <typename T, typename F> T ffi_wrap(risc0_error* err, T val, F fn) {
  try {
    err->msg = nullptr;
    return fn();
  } catch (const std::exception& ex) {
    err->msg = new risc0_string{ex.what()};
    return val;
  }
}

namespace risc0::circuit::recursion {

using HostBridge = void(void*, const char*, const char*, const Fp*, size_t, Fp*, size_t);

Fp step_compute_accum(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args);
Fp step_verify_accum(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args);
Fp step_exec(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args);
Fp step_verify_bytes(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args);
Fp step_verify_mem(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args);

FpExt poly_fp(size_t cycle, size_t steps, FpExt* poly_mix, Fp** args);

} // namespace risc0::circuit::recursion
