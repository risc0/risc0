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

#include <algorithm>
#include <array>
#include <stdexcept>
#include <vector>

using namespace risc0;

namespace risc0::circuit::rv32im {

constexpr size_t kBitWidth = 256;
constexpr size_t kByteWidth = kBitWidth / 8;

std::array<Fp, 32> extern_bigintQuotient(void* /*ctx*/,
                                         size_t /*cycle*/,
                                         const char* /*extra*/,
                                         std::array<Fp, 96> args) {
  // Division of two little-endian positive byte-limbed bigints. a = q * b + r.
  // Assumes a and b are both normalized with limbs in range [0, 255].
  // Throws if the quotient overflows kByteWidth. Overflows will not happen if the
  // numberator, a, is the result of a multiplication of two numbers less than the denomintor.
  // The BigInt arithmetic circuit does not accept larger quotients.
  // Returns only the quotient value q as the BigInt circuit does not use the r value.

  std::vector<uint64_t> a;
  std::transform(args.cbegin(), args.cbegin() + kByteWidth * 2, std::back_inserter(a), [](Fp x) {
    return x.asUInt32();
  });
  a.emplace_back(0);

  std::vector<uint64_t> b;
  std::transform(args.cbegin() + kByteWidth * 2, args.cend(), std::back_inserter(b), [](Fp x) {
    return x.asUInt32();
  });
  b.emplace_back(0);

  std::array<Fp, 32> q;

  // This is a variant of school-book multiplication.
  // Reference the Handbook of Elliptic and Hyper-elliptic Cryptography alg. 10.5.1

  // Determine n, the width of the denominator, and check for a denominator of zero.
  size_t n = kByteWidth;
  while (n > 0 && b.at(n - 1) == 0) {
    n--;
  }
  if (n == 0) {
    // Divide by zero is strictly undefined, but the BigInt multiplier circuit uses a modulus of
    // zero as a special case to support "checked multiply" of up to 256-bits.
    // Return zero here to facilitate this.
    return q;
  }
  if (n < 2) {
    // TODO(victor): Not an important case. But we should likely handle it anyway.
    throw std::runtime_error("bigint quotient: denominator must be at least 9 bits");
  }
  size_t m = a.size() - n - 1;

  // Shift (i.e. multiply by two) the inputs a and b until the leading bit of b is 1.
  // Note that shifting both numerator and denominator has no effect on the quotient.
  uint64_t dBits = 0;
  while ((b.at(n - 1) & (0x80 >> dBits)) == 0) {
    dBits++;
  }
  uint64_t carry = 0;
  for (size_t i = 0; i < n; i++) {
    uint64_t tmp = (b.at(i) << dBits) + carry;
    b.at(i) = tmp & 0xFF;
    carry = tmp >> 8;
  }
  if (carry != 0) {
    throw std::runtime_error("implementation error: final carry in input shift");
  }
  for (size_t i = 0; i < a.size() - 1; i++) {
    uint64_t tmp = (a.at(i) << dBits) + carry;
    a.at(i) = tmp & 0xFF;
    carry = tmp >> 8;
  }
  a.at(a.size() - 1) = carry;

  for (size_t i = m;; i--) {
    // Approximate how many multiples of b can be subtracted. May overestimate by up to one.
    uint64_t qApprox =
        std::min<uint64_t>(((a.at(i + n) << 8) + a.at(i + n - 1)) / b.at(n - 1), 255);
    while ((qApprox * ((b.at(n - 1) << 8) + b.at(n - 2))) >
           ((a.at(i + n) << 16) + (a.at(i + n - 1) << 8) + a.at(i + n - 2))) {
      qApprox--;
    }

    // Subtract multiples of the denominator from a.
    uint64_t borrow = 0;
    for (size_t j = 0; j <= n; j++) {
      uint64_t sub = qApprox * b.at(j) + borrow;
      if (a.at(i + j) < (sub & 0xFF)) {
        a.at(i + j) += 0x100 - (sub & 0xFF);
        borrow = (sub >> 8) + 1;
      } else {
        a.at(i + j) -= sub & 0xFF;
        borrow = sub >> 8;
      }
    }
    if (borrow > 0) {
      // Oops, went negative. Add back one multiple of b.
      qApprox--;
      uint64_t carry = 0;
      for (size_t j = 0; j <= n; j++) {
        uint64_t tmp = a.at(i + j) + b.at(j) + carry;
        a.at(i + j) = tmp & 0xFF;
        carry = tmp >> 8;
      }
      // Adding back one multiple of b should go from negative back to positive.
      if (borrow - carry != 0) {
        throw std::runtime_error("implementation error: underflow in bigint division");
      }
    }

    if (i < q.size()) {
      q.at(i) = qApprox;
    } else if (qApprox != 0) {
      throw std::runtime_error("bigint quotient: quotient exceeds allowed size");
    }

    if (i == 0) {
      break;
    }
  }
  return q;
}

} // namespace risc0::circuit::rv32im
