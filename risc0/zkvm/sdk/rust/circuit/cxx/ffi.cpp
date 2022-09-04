// Copyright 2022 Risc0, Inc.
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

#include <cstdint>
#include <stdexcept>

using namespace risc0;

extern "C" const char* risc0_circuit_string_ptr(risc0_string* str) {
  return str->str.c_str();
}

extern "C" void risc0_circuit_string_free(risc0_string* str) {
  delete str;
}

struct BridgeContext {
  void* ctx;
  Callback* callback;
};

void bridgeCallback(void* ctx,
                    const char* name,
                    const char* extra,
                    Fp* args_ptr,
                    size_t args_len,
                    Fp* result_ptr,
                    size_t result_len) {
  bool ok = false;
  BridgeContext* bridgeCtx = reinterpret_cast<BridgeContext*>(ctx);
  bridgeCtx->callback(bridgeCtx->ctx, name, extra, args_ptr, args_len, ok, result_ptr, result_len);
  if (!ok) {
    throw std::runtime_error("Host callback failure");
  }
}

extern "C" uint32_t risc0_circuit_rv32im_step_accum(risc0_error* err,
                                                    void* ctx,
                                                    Callback callback,
                                                    size_t steps,
                                                    size_t cycle,
                                                    Fp** args_ptr,
                                                    size_t /*args_len*/) {
  return ffi_wrap<uint32_t>(err, 0, [&] {
    BridgeContext bridgeCtx{ctx, callback};
    return circuit::rv32im::step_accum(&bridgeCtx, bridgeCallback, steps, cycle, args_ptr).asRaw();
  });
}

extern "C" uint32_t risc0_circuit_rv32im_step_exec(risc0_error* err,
                                                   void* ctx,
                                                   Callback callback,
                                                   size_t steps,
                                                   size_t cycle,
                                                   Fp** args_ptr,
                                                   size_t /*args_len*/) {
  return ffi_wrap<uint32_t>(err, 0, [&] {
    BridgeContext bridgeCtx{ctx, callback};
    return circuit::rv32im::step_exec(&bridgeCtx, bridgeCallback, steps, cycle, args_ptr).asRaw();
  });
}

extern "C" uint32_t risc0_circuit_rv32im_step_verify(risc0_error* err,
                                                     void* ctx,
                                                     Callback callback,
                                                     size_t steps,
                                                     size_t cycle,
                                                     Fp** args_ptr,
                                                     size_t /*args_len*/) {
  return ffi_wrap<uint32_t>(err, 0, [&] {
    BridgeContext bridgeCtx{ctx, callback};
    return circuit::rv32im::step_verify(&bridgeCtx, bridgeCallback, steps, cycle, args_ptr).asRaw();
  });
}
