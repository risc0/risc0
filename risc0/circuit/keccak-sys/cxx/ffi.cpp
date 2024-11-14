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

#include "ffi.h"
#include "fp.h"
#include "fpext.h"

#include <cstdint>
#include <stdexcept>

using namespace risc0;

extern "C" const char* risc0_circuit_keccak_string_ptr(risc0_string* str) {
  return str->str.c_str();
}

extern "C" void risc0_circuit_keccak_string_free(risc0_string* str) {
  delete str;
}

struct BridgeContext {
  void* ctx;
  Callback* callback;
};

static void bridgeCallback(void* ctx,
                           const char* name,
                           const char* extra,
                           const Fp* args_ptr,
                           size_t args_len,
                           Fp* outs_ptr,
                           size_t outs_len) {
  BridgeContext* bridgeCtx = reinterpret_cast<BridgeContext*>(ctx);
  if (!bridgeCtx->callback(bridgeCtx->ctx, name, extra, args_ptr, args_len, outs_ptr, outs_len)) {
    throw std::runtime_error("Host callback failure");
  }
}

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
#endif

extern "C" FpExt
risc0_circuit_keccak_poly_fp(size_t cycle, size_t steps, FpExt* poly_mix, Fp** args) {
  return circuit::keccak::poly_fp(cycle, steps, poly_mix, args);
}
