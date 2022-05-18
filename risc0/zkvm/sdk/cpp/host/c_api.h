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
// Library
//
void risc0_init();

//
// Prover
//

risc0_prover* risc0_prover_new(risc0_error* err, const char* elf_path, const char* method_id_path);

void risc0_prover_free(risc0_error* err, risc0_prover* ptr);

void risc0_prover_add_input(risc0_error* err, risc0_prover* ptr, const uint8_t* buf, size_t len);

size_t risc0_prover_get_num_outputs(risc0_error* err, risc0_prover* ptr);

const void* risc0_prover_get_output(risc0_error* err, risc0_prover* ptr, size_t idx, size_t len);

risc0_receipt* risc0_prover_run(risc0_error* err, risc0_prover* ptr);

//
// Proof
//

void risc0_receipt_verify(risc0_error* err, const char* method_id_path, const risc0_receipt* ptr);

const uint32_t* risc0_receipt_get_seal_buf(risc0_error* err, const risc0_receipt* ptr);

size_t risc0_receipt_get_seal_len(risc0_error* err, const risc0_receipt* ptr);

const void* risc0_receipt_get_journal_buf(risc0_error* err, const risc0_receipt* ptr);

size_t risc0_receipt_get_journal_len(risc0_error* err, const risc0_receipt* ptr);

void risc0_receipt_free(risc0_error* err, const risc0_receipt* ptr);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
