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

#include "risc0/zkp/core/poly.h"

#include "risc0/core/log.h"

#include <vector>

namespace risc0 {

Fp4 polyEval(const Fp4* coeffs, size_t size, Fp4 val) {
  Fp4 tot;
  Fp4 mul(1, 0, 0, 0);
  for (size_t i = 0; i < size; i++) {
    tot += mul * coeffs[i];
    mul *= val;
  }
  return tot;
}

Fp4 polyDivide(Fp4* p, size_t size, Fp4 z) {
  Fp4 cur;
  for (size_t i = size; i-- > 0;) {
    Fp4 next = z * cur + p[i];
    p[i] = cur;
    cur = next;
  }
  return cur;
}

void polyInterpolate(Fp4* out, const Fp4* x, const Fp4* fx, size_t size) {
  // Special case the very easy ones
  if (size == 1) {
    out[0] = fx[0];
    return;
  }
  if (size == 2) {
    out[1] = (fx[1] - fx[0]) * inv(x[1] - x[0]);
    out[0] = fx[0] - out[1] * x[0];
    return;
  }
  // Compute ft = product of (x - x_i) for all i
  std::vector<Fp4> ft(size + 1);
  ft[0] = Fp4(1, 0, 0, 0);
  for (size_t i = 0; i < size; i++) {
    for (size_t j = i + 1; j-- > 0;) {
      ft[j + 1] += ft[j];
      ft[j] *= -x[i];
    }
  }
  // Clear output
  for (size_t i = 0; i < size; i++) {
    out[i] = Fp4();
  }
  for (size_t i = 0; i < size; i++) {
    // Compute fr = ft / (x - x_i)
    std::vector<Fp4> fr = ft;
    polyDivide(fr.data(), fr.size(), x[i]);
    // Evaluate at x[i]
    Fp4 fr_xi = polyEval(fr.data(), fr.size(), x[i]);
    // Compute multiplier (fx[i] / fr_xi)
    Fp4 mul = fx[i] * inv(fr_xi);
    // Multiply into output
    for (size_t j = 0; j < size; j++) {
      out[j] += mul * fr[j];
    }
  }
}

} // namespace risc0
