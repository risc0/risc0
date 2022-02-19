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
typedef struct risc0_proof risc0_proof;

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

risc0_prover* risc0_prover_new(risc0_error* err, const char* elf_path);

void risc0_prover_free(risc0_error* err, risc0_prover* ptr);

void risc0_prover_add_input(risc0_error* err, risc0_prover* ptr, const uint8_t* buf, size_t len);

size_t risc0_prover_get_num_outputs(risc0_error* err, risc0_prover* ptr);

const void* risc0_prover_get_output(risc0_error* err, risc0_prover* ptr, size_t idx, size_t len);

risc0_proof* risc0_prover_run(risc0_error* err, risc0_prover* ptr);

//
// Proof
//

void risc0_proof_verify(risc0_error* err, const risc0_proof* ptr);

const uint32_t* risc0_proof_get_core_buf(risc0_error* err, const risc0_proof* ptr);

size_t risc0_proof_get_core_len(risc0_error* err, const risc0_proof* ptr);

const void* risc0_proof_get_message_buf(risc0_error* err, const risc0_proof* ptr);

size_t risc0_proof_get_message_len(risc0_error* err, const risc0_proof* ptr);

void risc0_proof_free(risc0_error* err, const risc0_proof* ptr);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
