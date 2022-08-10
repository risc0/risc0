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

#pragma once

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#else
#include <stddef.h>
#include <stdint.h>
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//
// Core API
//

typedef struct risc0_string risc0_string;
typedef struct risc0_prover risc0_prover;
typedef struct risc0_receipt risc0_receipt;
typedef struct risc0_method_id risc0_method_id;
typedef struct risc0_u8buffer risc0_u8buffer;

//
// Error
//

typedef struct {
  risc0_string* msg;
} risc0_error;

//
// String
//

const char* risc0_string_ptr(risc0_string* str);

void risc0_string_free(risc0_string* str);

//
// U8buffer

risc0_u8buffer* risc0_u8buffer_new(const uint8_t* bytes, size_t len);

//
// Library
//
void risc0_init();

//
// MethodId
//

risc0_method_id*
risc0_method_id_compute(risc0_error* err, const uint8_t* bytes, size_t len, uint32_t limit);

risc0_method_id* risc0_method_id_load(risc0_error* err, const uint8_t* bytes, size_t len);

const void* risc0_method_id_get_buf(risc0_error* err, risc0_method_id* ptr, uint32_t* len);

void risc0_method_id_free(risc0_error* err, const risc0_method_id* ptr);

//
// Prover
//

risc0_prover* risc0_prover_new(risc0_error* err,
                               const uint8_t* elf_bytes,
                               const size_t elf_len,
                               const uint8_t* method_id_buf,
                               const size_t method_id_len);

void risc0_prover_free(risc0_error* err, risc0_prover* ptr);

void risc0_prover_add_input(risc0_error* err, risc0_prover* ptr, const uint8_t* buf, size_t len);

size_t risc0_prover_get_num_outputs(risc0_error* err, risc0_prover* ptr);

const void* risc0_prover_get_output_buf(risc0_error* err, const risc0_prover* ptr);

size_t risc0_prover_get_output_len(risc0_error* err, const risc0_prover* ptr);

risc0_receipt* risc0_prover_run(risc0_error* err, risc0_prover* ptr);

void risc0_prover_set_skip_seal(risc0_error* err, risc0_prover* ptr, bool skip_seal);

void risc0_prover_set_sendrecv_handler(
    risc0_error* err,
    risc0_prover* ptr,
    uint32_t channel_id,
    risc0_u8buffer* (*callback)(uint32_t channel_id, const uint8_t* buf, size_t len, void* cbdata),
    void* cbdata);

//
// Receipt
//

risc0_receipt* risc0_receipt_new(risc0_error* err,
                                 const uint8_t* journal,
                                 const size_t journal_len,
                                 const uint32_t* seal,
                                 const size_t seal_len);

void risc0_receipt_verify(risc0_error* err,
                          const risc0_receipt* ptr,
                          const uint8_t* method_id_buf,
                          const size_t method_id_len);

const uint32_t* risc0_receipt_get_seal_buf(risc0_error* err, const risc0_receipt* ptr);

size_t risc0_receipt_get_seal_len(risc0_error* err, const risc0_receipt* ptr);

const void* risc0_receipt_get_journal_buf(risc0_error* err, const risc0_receipt* ptr);

size_t risc0_receipt_get_journal_len(risc0_error* err, const risc0_receipt* ptr);

void risc0_receipt_free(risc0_error* err, const risc0_receipt* ptr);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
