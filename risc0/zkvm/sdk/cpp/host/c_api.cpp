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

#include "risc0/zkvm/sdk/cpp/host/c_api.h"

#include <memory>

#include "risc0/core/log.h"
#include "risc0/zkp/verify/verify.h"
#include "risc0/zkvm/prove/method_id.h"
#include "risc0/zkvm/sdk/cpp/host/receipt.h"

extern "C" {

struct risc0_string {
  std::string str;
};

} // extern "C"

template <typename F> void ffi_wrap_void(risc0_error* err, F fn) {
  try {
    err->msg = nullptr;
    fn();
  } catch (const std::exception& ex) {
    err->msg = new risc0_string{ex.what()};
  } catch (...) {
    err->msg = new risc0_string{"C++ exception"};
  }
}

template <typename T, typename F> T ffi_wrap(risc0_error* err, T val, F fn) {
  try {
    err->msg = nullptr;
    return fn();
  } catch (const std::exception& ex) {
    err->msg = new risc0_string{ex.what()};
    return val;
  } catch (...) {
    err->msg = new risc0_string{"C++ exception"};
    return val;
  }
}

extern "C" {

struct risc0_method_id {
  risc0::MethodId raw;
};

struct risc0_prover {
  std::unique_ptr<risc0::Prover> prover;
};

struct risc0_receipt {
  risc0::Receipt receipt;
};

void risc0_init() {
  if (const char* level = std::getenv("RISC0_LOG")) {
    risc0::setLogLevel(std::atoi(level));
  }
}

const char* risc0_string_ptr(risc0_string* str) {
  return str->str.c_str();
}

void risc0_string_free(risc0_string* str) {
  risc0_error err;
  ffi_wrap_void(&err, [&] { delete str; });
}

risc0_method_id*
risc0_method_id_compute(risc0_error* err, const uint8_t* bytes, size_t len, uint32_t limit) {
  return ffi_wrap<risc0_method_id*>(err, nullptr, [&] {
    std::vector<uint8_t> elfContents(bytes, bytes + len);
    return new risc0_method_id{risc0::computeMethodId(elfContents, limit)};
  });
}

const void* risc0_method_id_get_buf(risc0_error* err, risc0_method_id* ptr, uint32_t* len) {
  return ffi_wrap<const void*>(err, nullptr, [&] {
    *len = ptr->raw.size() * sizeof(risc0::ShaDigest);
    return ptr->raw.data();
  });
}

void risc0_method_id_free(risc0_error* err, const risc0_method_id* ptr) {
  ffi_wrap_void(err, [&] { delete ptr; });
}

risc0_prover* risc0_prover_new(risc0_error* err,
                               const uint8_t* elf_bytes,
                               const size_t elf_len,
                               const uint8_t* method_id_buf,
                               const size_t method_id_len) {
  return ffi_wrap<risc0_prover*>(err, nullptr, [&] {
    risc0::MethodId methodId = risc0::loadMethodId(method_id_buf, method_id_len);
    return new risc0_prover{std::make_unique<risc0::Prover>(elf_bytes, elf_len, methodId)};
  });
}

void risc0_prover_free(risc0_error* err, risc0_prover* ptr) {
  ffi_wrap_void(err, [&] { delete ptr; });
}

void risc0_prover_add_input(risc0_error* err, risc0_prover* ptr, const uint8_t* buf, size_t len) {
  ffi_wrap_void(err, [&] { ptr->prover->writeInput(buf, len); });
}

const void* risc0_prover_get_output_buf(risc0_error* err, const risc0_prover* ptr) {
  return ffi_wrap<const void*>(err, nullptr, [&] { return ptr->prover->getOutput().data(); });
}

size_t risc0_prover_get_output_len(risc0_error* err, const risc0_prover* ptr) {
  return ffi_wrap(err, 0, [&] { return ptr->prover->getOutput().size(); });
}

risc0_receipt* risc0_prover_run(risc0_error* err, risc0_prover* ptr) {
  return ffi_wrap<risc0_receipt*>(err, nullptr, [&] {
    risc0::Receipt receipt = ptr->prover->run();
    return new risc0_receipt{receipt};
  });
}

risc0_receipt* risc0_receipt_new(risc0_error* err,
                                 const uint8_t* journal,
                                 const size_t journal_len,
                                 const uint32_t* seal,
                                 const size_t seal_len) {
  return ffi_wrap<risc0_receipt*>(err, nullptr, [&] {
    risc0::Receipt receipt{risc0::BufferU8{journal, journal + journal_len},
                           risc0::BufferU32{seal, seal + seal_len}};
    return new risc0_receipt{receipt};
  });
}

void risc0_receipt_verify(risc0_error* err,
                          const risc0_receipt* ptr,
                          const uint8_t* method_id_buf,
                          const size_t method_id_len) {
  ffi_wrap_void(err,
                [&] { ptr->receipt.verify(risc0::loadMethodId(method_id_buf, method_id_len)); });
}

const uint32_t* risc0_receipt_get_seal_buf(risc0_error* err, const risc0_receipt* ptr) {
  return ffi_wrap<const uint32_t*>(err, nullptr, [&] { return ptr->receipt.seal.data(); });
}

size_t risc0_receipt_get_seal_len(risc0_error* err, const risc0_receipt* ptr) {
  return ffi_wrap(err, 0, [&] { return ptr->receipt.seal.size(); });
}

const void* risc0_receipt_get_journal_buf(risc0_error* err, const risc0_receipt* ptr) {
  return ffi_wrap<const void*>(err, nullptr, [&] { return ptr->receipt.journal.data(); });
}

size_t risc0_receipt_get_journal_len(risc0_error* err, const risc0_receipt* ptr) {
  return ffi_wrap(err, 0, [&] { return ptr->receipt.journal.size(); });
}

void risc0_receipt_free(risc0_error* err, const risc0_receipt* ptr) {
  ffi_wrap_void(err, [&] { delete ptr; });
}

} // extern "C"
