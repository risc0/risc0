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

#include "fp.h"

#include <assert.h>

constexpr size_t kBitWidth = 256;
constexpr size_t kByteWidth = kBitWidth / 8;

inline __device__ uint64_t this_min(uint64_t lhs, uint64_t rhs) {
  if (rhs < lhs) {
    return rhs;
  }
  return lhs;
}

inline __device__ void
extern_bigintQuotient(void* ctx, size_t cycle, const char* extra, Fp* args, Fp* outs) {
  // Division of two little-endian positive byte-limbed bigints. a = q * b + r.
  // Assumes a and b are both normalized with limbs in range [0, 255].
  // Asserts if the quotient overflows kByteWidth. Overflows will not happen if the
  // numberator, a, is the result of a multiplication of two numbers less than the denomintor.
  // The BigInt arithmetic circuit does not accept larger quotients.
  // Returns only the quotient value q as the BigInt circuit does not use the r value.

  constexpr size_t aSize = kByteWidth * 2 + 1;
  uint64_t a[aSize];
  for (size_t i = 0; i < kByteWidth * 2; i++) {
    a[i] = args[i].asUInt32();
  }
  a[kByteWidth * 2] = 0;

  constexpr size_t bSize = kByteWidth + 1;
  uint64_t b[bSize];
  for (size_t i = 0; i < kByteWidth; i++) {
    b[i] = args[kByteWidth * 2 + i].asUInt32();
  }
  b[kByteWidth] = 0;

  for (size_t i = 0; i < kByteWidth; i++) {
    outs[i] = 0;
  }

  // This is a variant of school-book multiplication.
  // Reference the Handbook of Elliptic and Hyper-elliptic Cryptography alg. 10.5.1

  // Determine n, the width of the denominator, and check for a denominator of zero.
  size_t n = kByteWidth;
  while (n > 0 && b[n - 1] == 0) {
    n--;
  }
  if (n == 0) {
    // Divide by zero is strictly undefined, but the BigInt multiplier circuit uses a modulus of
    // zero as a special case to support "checked multiply" of up to 256-bits.
    // Return zero here to facilitate this.
    return;
  }

  // TODO(victor): Not an important case. But we should likely handle it anyway.
  assert(n > 1 && "bigint quotient: denominator must be at least 9 bits");
  size_t m = aSize - n - 1;

  // Shift (i.e. multiply by two) the inputs a and b until the leading bit of b is 1.
  // Note that shifting both numerator and denominator has no effect on the quotient.
  uint64_t dBits = 0;
  while ((b[n - 1] & (0x80 >> dBits)) == 0) {
    dBits++;
  }
  uint64_t carry = 0;
  for (size_t i = 0; i < n; i++) {
    uint64_t tmp = (b[i] << dBits) + carry;
    b[i] = tmp & 0xFF;
    carry = tmp >> 8;
  }
  assert(carry == 0 && "implementation error: final carry in input shift");
  for (size_t i = 0; i < aSize - 1; i++) {
    uint64_t tmp = (a[i] << dBits) + carry;
    a[i] = tmp & 0xFF;
    carry = tmp >> 8;
  }
  a[aSize - 1] = carry;

  for (size_t i = m;; i--) {
    // Approximate how many multiples of b can be subtracted. May overestimate by up to one.
    uint64_t qApprox = this_min(((a[i + n] << 8) + a[i + n - 1]) / b[n - 1], 255);
    while ((qApprox * ((b[n - 1] << 8) + b[n - 2])) >
           ((a[i + n] << 16) + (a[i + n - 1] << 8) + a[i + n - 2])) {
      qApprox--;
    }

    // Subtract multiples of the denominator from a.
    uint64_t borrow = 0;
    for (size_t j = 0; j <= n; j++) {
      uint64_t sub = qApprox * b[j] + borrow;
      if (a[i + j] < (sub & 0xFF)) {
        a[i + j] += 0x100 - (sub & 0xFF);
        borrow = (sub >> 8) + 1;
      } else {
        a[i + j] -= sub & 0xFF;
        borrow = sub >> 8;
      }
    }
    if (borrow > 0) {
      // Oops, went negative. Add back one multiple of b.
      qApprox--;
      uint64_t carry = 0;
      for (size_t j = 0; j <= n; j++) {
        uint64_t tmp = a[i + j] + b[j] + carry;
        a[i + j] = tmp & 0xFF;
        carry = tmp >> 8;
      }
      // Adding back one multiple of b should go from negative back to positive.
      assert(borrow - carry == 0 && "implementation error: underflow in bigint division");
    }

    if (i < kByteWidth) {
      outs[i] = qApprox;
    } else {
      assert(qApprox == 0 && "bigint quotient: quotient exceeds allowed size");
    }

    if (i == 0) {
      break;
    }
  }
}
