// Copyright 2025 RISC Zero, Inc.
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


#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Size of a zkVM memory page.
 */
#define PAGE_SIZE 1024

#define GUEST_MIN_MEM 16384

#define GUEST_MAX_MEM 3221225472

/**
 * Top of stack; stack grows down from this location.
 */
#define STACK_TOP 2098176

/**
 * Program (text followed by data and then bss) gets loaded in
 * starting at this location.  HEAP begins right afterwards.
 */
#define TEXT_START 2099200

#define DIGEST_WORDS 8

#define DIGEST_BYTES (WORD_SIZE * DIGEST_WORDS)

#define KECCACK_STATE_BYTES 200

#define KECCACK_STATE_WORDS (200 / WORD_SIZE)

#define KECCACK_STATE_DWORDS (200 / 8)

/**
 * Number of words in each cycle received using the SOFTWARE ecall
 */
#define IO_CHUNK_WORDS 4

#define MAX_BUF_BYTES (4 * 1024)

#define MAX_BUF_WORDS (MAX_BUF_BYTES / WORD_SIZE)

#define MAX_SHA_COMPRESS_BLOCKS 1000

#define HALT 0

#define INPUT 1

#define SOFTWARE 2

#define SHA 3

#define BIGINT 4

#define USER 5

#define BIGINT2 6

#define TERMINATE 0

#define PAUSE 1

#define SPLIT 2

#define REG_ZERO 0

#define REG_RA 1

#define REG_SP 2

#define REG_GP 3

#define REG_TP 4

#define REG_T0 5

#define REG_T1 6

#define REG_T2 7

#define REG_S0 8

#define REG_FP 8

#define REG_S1 9

#define REG_A0 10

#define REG_A1 11

#define REG_A2 12

#define REG_A3 13

#define REG_A4 14

#define REG_A5 15

#define REG_A6 16

#define REG_A7 17

#define REG_S2 18

#define REG_S3 19

#define REG_S4 20

#define REG_S5 21

#define REG_S6 22

#define REG_S7 23

#define REG_S8 24

#define REG_S9 25

#define REG_S10 26

#define REG_S11 27

#define REG_T3 28

#define REG_T4 29

#define REG_T5 30

#define REG_T6 31

#define REG_MAX 32

#define KECCAK_PERMUTE 0

#define KECCAK_PROVE 1

#define OP_MULTIPLY 0

/**
 * BigInt width, in bits, handled by the BigInt accelerator circuit.
 */
#define WIDTH_BITS 256

/**
 * BigInt width, in bytes, handled by the BigInt accelerator circuit.
 */
#define WIDTH_BYTES (WIDTH_BITS / 8)



#define STDIN 0

#define STDOUT 1

#define STDERR 2

#define JOURNAL 3

/**
 * Wrapper around [`BufferKindUser`].
 *
 * It handles data buffering and implements the slice-based traits.
 */
typedef struct CoreWrapper_CtVariableCoreWrapper_Sha256VarCore_Impl_____U32__OidSha256 CoreWrapper_CtVariableCoreWrapper_Sha256VarCore_Impl_____U32__OidSha256;

/**
 * SHA-256 implementation cross-compatible with `sha2::Sha256`.
 */
typedef struct CoreWrapper_CtVariableCoreWrapper_Sha256VarCore_Impl_____U32__OidSha256 Sha256_Impl;

/**
 * C wrapper for guest sha256 implementation.
 *
 * This is used in the guest to generate any sha256
 * hash, but also to accumulate the Sha256 state of all data written to journal through
 * [commit].
 *
 * Initialize with [init_sha256], and can retrieve the final hash through [sha256_finalize],
 * or pass it into [zkvm_exit] to exit the program.
 */
typedef struct sha256_state {
  Sha256_Impl *inner;
} sha256_state;

/**
 * Digest represents the results of a hashing function.  It is always 256 bits
 * of storage although depending on the hash it may have additional structure
 * (for example Poseidon's output is actually composed of field elements).  The
 * storage is in u32's in part to simplify alignment requirements, especially
 * in the zkVM.
 */
typedef uint32_t Digest[DIGEST_WORDS];

#if defined(DEFINE_ZKVM)
void init_allocator(void);
#endif

struct sha256_state *init_sha256(void);

/**
 * Update the sha256 state with the bytes passed in.
 *
 * # Safety
 * This is safe assuming that pointers have not been manually modified, and len does not go past
 * the buffer of the data in memory.
 */
void sha256_update(struct sha256_state *hasher, const uint8_t *data, uint32_t len);

/**
 * Finalize the hasher, returning an allocated digest of the output hash.
 *
 * Note: This digest is leaked, as the zkvm currently uses a bump allocator so it does not need to
 * be freed. If switching allocator, should implement a free method for [Digest].
 *
 * # Safety
 * Assumes [sha256_state] has not been freed previously.
 */
Digest *sha256_finalize(struct sha256_state *hasher);

/**
 * Free allocations from [sha256_state].
 *
 * # Safety
 * This assumes the state has not already been freed or manually modified.
 */
void sha256_free(struct sha256_state *hasher);

/**
 * Exit the zkvm, using the [sha256_state].
 *
 * # Safety
 * Assumes hasher has not been freed.
 */
void env_exit(struct sha256_state *hasher, uint8_t exit_code);

/**
 * Write data to the journal, updating the sha256 state accumulation with that data.
 *
 * # Safety
 * This is safe assuming that pointers have not been manually modified, and len does not go past
 * the buffer of the data in memory.
 */
void env_commit(struct sha256_state *hasher, const uint8_t *bytes_ptr, uint32_t len);

/**
 * Reads `len` bytes into buffer from the host.
 *
 * # Safety
 * Assumes that the buffer has at least `len` bytes allocated.
 */
uintptr_t env_read(uint8_t *bytes_ptr, uint32_t len);

#if (defined(DEFINE_SYSCALLS) && !defined(DEFINE_ZKVM))
/**
 * # Safety
 *
 * This function should be safe to call, but clippy complains if it is not marked as `unsafe`.
 */
uint8_t *sys_alloc_aligned(uintptr_t bytes, uintptr_t align);
#endif

#if (defined(DEFINE_SYSCALLS) && defined(DEFINE_ZKVM))
/**
 * # Safety
 *
 * This function should be safe to call, but clippy complains if it is not marked as `unsafe`.
 */
uint8_t *sys_alloc_aligned(uintptr_t bytes, uintptr_t align);
#endif

#if (defined(DEFINE_SYSCALLS) && defined(DEFINE_ZKVM))
/**
 * # Safety
 *
 * This function should be safe to call, but clippy complains if it is not marked as `unsafe`.
 */
uint8_t *sys_alloc_aligned(uintptr_t bytes, uintptr_t align);
#endif

#if defined(DEFINE_SYSCALLS)
/**
 * Send a ReceiptClaim digest to the host to request verification.
 *
 * A cooperative prover will only return if there is a verifying proof
 * associated with that claim digest, and will always return a result code
 * of 0 to register a0. The caller must encode the claim_digest into a
 * public assumptions list for inclusion in the guest output.
 *
 * # Safety
 *
 * `claim_digest` must be aligned and dereferenceable.
 * `control_root` must be aligned and dereferenceable.
 */
void sys_verify_integrity(const uint32_t (*claim_digest)[DIGEST_WORDS],
                          const uint32_t (*control_root)[DIGEST_WORDS]);
#endif

#if defined(DEFINE_SYSCALLS)
/**
 * TODO: Send a ReceiptClaim digest to the host to request verification. Meant for proofs that use union.
 *
 * # Safety
 *
 * `claim_digest` must be aligned and dereferenceable.
 * `control_root` must be aligned and dereferenceable.
 */
void sys_verify_integrity2(const uint32_t (*claim_digest)[DIGEST_WORDS],
                           const uint32_t (*control_root)[DIGEST_WORDS]);
#endif

#if !defined(DEFINE_SYSCALLS)
extern uint8_t *sys_alloc_aligned(uintptr_t nwords, uintptr_t align);
#endif

#if defined(DEFINE_SYSCALLS)
/**
 * `sys_fork()` creates a new process by duplicating the calling process. The
 * new process is referred to as the child process. The calling process is
 * referred to as the parent process.
 *
 * The child process and the parent process run in separate memory spaces. At
 * the time of `sys_fork()` both memory spaces have the same content.
 *
 * # Return Value
 *
 * On success, the PID of the child process (1) is returned in the parent, and
 * 0 is returned in the child. On failure, -1 is returned in the parent, no
 * child process is created.
 */
int32_t sys_fork(void);
#endif

#if defined(DEFINE_SYSCALLS)
/**
 * `sys_pipe()` creates a pipe, a unidirectional data channel that can be used
 * for interprocess communication. The pointer `pipefd` is used to return two
 * file descriptors referring to the ends of the pipe. `pipefd[0]` refers to
 * the read end of the pipe. `pipefd[1]` refers to the write end of the pipe.
 * Data written to the write end of the pipe is buffered by the host until it
 * is read from the read end of the pipe.
 *
 * # Return Value
 *
 * On success, zero is returned.  On error, -1 is returned, and `pipefd` is
 * left unchanged.
 *
 * # Safety
 *
 * `pipefd` must be aligned, dereferenceable, and have capacity for 2 u32
 * values.
 */
int32_t sys_pipe(uint32_t *pipefd);
#endif

#if defined(DEFINE_SYSCALLS)
/**
 * `sys_exit()` causes normal process termination.
 *
 * Currently the `status` is unused and ignored.
 */
void sys_exit(int32_t status);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float acosf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float acoshf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double acosh(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double acos(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float asinf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float asinhf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double asinh(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double asin(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float atan2f(float y, float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double atan2(double y, double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float atanf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float atanhf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double atanh(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double atan(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float cbrtf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double cbrt(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float ceilf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double ceil(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float copysignf(float x, float y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double copysign(double x, double y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float cosf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float coshf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double cosh(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double cos(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float erfcf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double erfc(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float erff(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double erf(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float exp10f(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double exp10(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float exp2f(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double exp2(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float expf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float expm1f(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double expm1(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double exp(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float fabsf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double fabs(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float fdimf(float x, float y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double fdim(double x, double y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float floorf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double floor(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float fmaf(float x, float y, float z);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double fma(double x, double y, double z);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float fmaxf(float x, float y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double fmax(double x, double y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float fminf(float x, float y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double fmin(double x, double y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float fmodf(float x, float y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double fmod(double x, double y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float hypotf(float x, float y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double hypot(double x, double y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
int32_t ilogbf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
int32_t ilogb(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float j0f(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double j0(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float j1f(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double j1(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float jnf(int32_t n, float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double jn(int32_t n, double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float ldexpf(float x, int32_t n);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double ldexp(double x, int32_t n);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double lgamma(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float log10f(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double log10(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float log1pf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double log1p(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float log2f(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double log2(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float logf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double log(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float nextafterf(float x, float y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double nextafter(double x, double y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float powf(float x, float y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double pow(double x, double y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float remainderf(float x, float y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double remainder(double x, double y);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float roundf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double round(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float scalbnf(float x, int32_t n);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double scalbn(double x, int32_t n);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float sinf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float sinhf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double sinh(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double sin(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float sqrtf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double sqrt(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float tanf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float tanhf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double tanh(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double tan(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float tgammaf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double tgamma(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float truncf(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double trunc(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float y0f(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double y0(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float y1f(float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double y1(double x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
float ynf(int32_t n, float x);
#endif

#if (defined(DEFINE_LIBM) && defined(DEFINE_ZKVM))
double yn(int32_t n, double x);
#endif

#if (defined(DEFINE_ZKVM) && defined(DEFINE_ENTRYPOINT))
void __start(void);
#endif
