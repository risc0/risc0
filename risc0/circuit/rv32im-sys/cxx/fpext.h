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

#pragma once

/// \file
/// Defines FpExt, a finite field F_p^5, based on Fp via the irreducable polynomial x^5 + 2.

#include "fp.h"

namespace risc0 {

static constexpr size_t EXT_SIZE = 5;

/// Intstances of FpExt are elements of a finite field F_p^5.  They are
/// represented as elements of F_p[X] / (X^5 + 2). This large finite field is
/// used when the security of operations depends on the size of the field. The
/// field extension `FpExt` has `Fp` as a subfield, so operations on elements of
/// each are compatible.
struct FpExt {
  /// The elements of FpExt, elems[0] + elems[1]*X + elems[2]*X^2 + elems[3]*x^4 + elems[4]*x^5
  Fp elems[EXT_SIZE];

  /// Default constructor makes the zero elements
  constexpr FpExt() {}

  /// Initialize from uint32_t
  explicit constexpr FpExt(uint32_t x) {
    elems[0] = x;
    elems[1] = 0;
    elems[2] = 0;
    elems[3] = 0;
    elems[4] = 0;
  }

  /// Convert from Fp to FpExt.
  explicit constexpr FpExt(Fp x) {
    elems[0] = x;
    elems[1] = 0;
    elems[2] = 0;
    elems[3] = 0;
    elems[4] = 0;
  }

  /// Explicitly construct an FpExt from parts
  constexpr FpExt(Fp a, Fp b, Fp c, Fp d, Fp e) {
    elems[0] = a;
    elems[1] = b;
    elems[2] = c;
    elems[3] = d;
    elems[4] = e;
  }

  /// Get an 'invalid' FpExt value
  static constexpr inline FpExt invalid() {
    return FpExt(Fp::invalid(), Fp::invalid(), Fp::invalid(), Fp::invalid(), Fp::invalid());
  }

  // Implement the addition/subtraction overloads
  constexpr FpExt operator+=(FpExt rhs) {
    for (uint32_t i = 0; i < EXT_SIZE; i++) {
      elems[i] += rhs.elems[i];
    }
    return *this;
  }

  constexpr FpExt operator-=(FpExt rhs) {
    for (uint32_t i = 0; i < EXT_SIZE; i++) {
      elems[i] -= rhs.elems[i];
    }
    return *this;
  }

  constexpr FpExt operator+(FpExt rhs) const {
    FpExt result = *this;
    result += rhs;
    return result;
  }

  constexpr FpExt operator-(FpExt rhs) const {
    FpExt result = *this;
    result -= rhs;
    return result;
  }

  constexpr FpExt operator-() const { return FpExt() - *this; }

  // Implement the simple multiplication case by the subfield Fp
  // Fp * FpExt is done as a free function due to C++'s operator overloading rules.
  constexpr FpExt operator*=(Fp rhs) {
    for (uint32_t i = 0; i < EXT_SIZE; i++) {
      elems[i] *= rhs;
    }
    return *this;
  }

  constexpr FpExt operator*(Fp rhs) const {
    FpExt result = *this;
    result *= rhs;
    return result;
  }

  constexpr FpExt operator*(FpExt rhs) const;
  //   {
  // // Rename the element arrays to something small for readability
  // #define a elems
  // #define b rhs.elems
  //     Fp c[2 * 4 + 1];
  //     for (size_t i = 0; i < 4 + 1; i++) {
  //       for (size_t j = 0; j < 4 + 1; j++) {
  //         c[i + j] += a[i] * b[j];
  //       }
  //     }
  //     return FpExt(c[0] - c[5] * 2, c[1] - c[6] * 2, c[2] - c[7] * 2, c[3] - c[8] * 2, c[4]);
  // #undef a
  // #undef b
  //   }

  constexpr FpExt operator*=(FpExt rhs) {
    *this = *this * rhs;
    return *this;
  }

  // Equality
  constexpr bool operator==(FpExt rhs) const {
    for (uint32_t i = 0; i < EXT_SIZE; i++) {
      if (elems[i] != rhs.elems[i]) {
        return false;
      }
    }
    return true;
  }

  constexpr bool operator!=(FpExt rhs) const { return !(*this == rhs); }

  constexpr Fp constPart() const { return elems[0]; }
};

/// Overload for case where LHS is Fp (RHS case is handled as a method)
constexpr inline FpExt operator*(Fp a, FpExt b) {
  return b * a;
}

/// Raise an FpExt to a power
constexpr inline FpExt pow(FpExt x, size_t n) {
  FpExt tot(1);
  while (n != 0) {
    if (n % 2 == 1) {
      tot *= x;
    }
    n = n / 2;
    x *= x;
  }
  return tot;
}

} // namespace risc0
