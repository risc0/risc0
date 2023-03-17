// Copyright 2023 RISC Zero, Inc.
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
/// Defines Fp4, a finite field F_p^4, based on Fp via the irreducable polynomial x^4 - 11.

#include "fp.h"

namespace risc0 {

// Defines instead of constexpr to appease CUDAs limitations around constants.
// undef'd at the end of this file.
#define BETA Fp(11)
#define NBETA Fp(Fp::P - 11)

/// Intstances of Fp4 are element of a finite field F_p^4.  They are represented as elements of
/// F_p[X] / (X^4 - 11). Basically, this is a 'big' finite field (about 2^128 elements), which is
/// used when the security of various operations depends on the size of the field.  It has the field
/// Fp as a subfield, which means operations by the two are compatable, which is important.  The
/// irreducible polynomial was choosen to be the simpilest possible one, x^4 - B, where 11 is the
/// smallest B which makes the polynomial irreducable.
struct Fp4 {
  /// The elements of Fp4, elems[0] + elems[1]*X + elems[2]*X^2 + elems[3]*x^4
  Fp elems[4];

  /// Default constructor makes the zero elements
  constexpr Fp4() {}

  /// Initialize from uint32_t
  explicit constexpr Fp4(uint32_t x) {
    elems[0] = x;
    elems[1] = 0;
    elems[2] = 0;
    elems[3] = 0;
  }

  /// Convert from Fp to Fp4.
  explicit constexpr Fp4(Fp x) {
    elems[0] = x;
    elems[1] = 0;
    elems[2] = 0;
    elems[3] = 0;
  }

  /// Explicitly construct an Fp4 from parts
  constexpr Fp4(Fp a, Fp b, Fp c, Fp d) {
    elems[0] = a;
    elems[1] = b;
    elems[2] = c;
    elems[3] = d;
  }

  /// Get an 'invalid' Fp4 value
  static constexpr inline Fp4 invalid() {
    return Fp4(Fp::invalid(), Fp::invalid(), Fp::invalid(), Fp::invalid());
  }

  // Implement the addition/subtraction overloads
  constexpr Fp4 operator+=(Fp4 rhs) {
    for (uint32_t i = 0; i < 4; i++) {
      elems[i] += rhs.elems[i];
    }
    return *this;
  }

  constexpr Fp4 operator-=(Fp4 rhs) {
    for (uint32_t i = 0; i < 4; i++) {
      elems[i] -= rhs.elems[i];
    }
    return *this;
  }

  constexpr Fp4 operator+(Fp4 rhs) const {
    Fp4 result = *this;
    result += rhs;
    return result;
  }

  constexpr Fp4 operator-(Fp4 rhs) const {
    Fp4 result = *this;
    result -= rhs;
    return result;
  }

  constexpr Fp4 operator-() const { return Fp4() - *this; }

  // Implement the simple multiplication case by the subfield Fp
  // Fp * Fp4 is done as a free function due to C++'s operator overloading rules.
  constexpr Fp4 operator*=(Fp rhs) {
    for (uint32_t i = 0; i < 4; i++) {
      elems[i] *= rhs;
    }
    return *this;
  }

  constexpr Fp4 operator*(Fp rhs) const {
    Fp4 result = *this;
    result *= rhs;
    return result;
  }

  // Now we get to the interesting case of multiplication.  Basically, multiply out the polynomial
  // representations, and then reduce module x^4 - B, which means powers >= 4 get shifted back 4 and
  // multiplied by -beta.  We could write this as a double loops with some if's and hope it gets
  // unrolled properly, but it'a small enough to just hand write.
  constexpr Fp4 operator*(Fp4 rhs) const {
    // Rename the element arrays to something small for readability
#define a elems
#define b rhs.elems
    return Fp4(a[0] * b[0] + NBETA * (a[1] * b[3] + a[2] * b[2] + a[3] * b[1]),
               a[0] * b[1] + a[1] * b[0] + NBETA * (a[2] * b[3] + a[3] * b[2]),
               a[0] * b[2] + a[1] * b[1] + a[2] * b[0] + NBETA * (a[3] * b[3]),
               a[0] * b[3] + a[1] * b[2] + a[2] * b[1] + a[3] * b[0]);
#undef a
#undef b
  }
  constexpr Fp4 operator*=(Fp4 rhs) {
    *this = *this * rhs;
    return *this;
  }

  // Equality
  constexpr bool operator==(Fp4 rhs) const {
    for (uint32_t i = 0; i < 4; i++) {
      if (elems[i] != rhs.elems[i]) {
        return false;
      }
    }
    return true;
  }

  constexpr bool operator!=(Fp4 rhs) const { return !(*this == rhs); }

  constexpr Fp constPart() const { return elems[0]; }
};

/// Overload for case where LHS is Fp (RHS case is handled as a method)
constexpr inline Fp4 operator*(Fp a, Fp4 b) {
  return b * a;
}

/// Raise an Fp4 to a power
constexpr inline Fp4 pow(Fp4 x, size_t n) {
  Fp4 tot(1);
  while (n != 0) {
    if (n % 2 == 1) {
      tot *= x;
    }
    n = n / 2;
    x *= x;
  }
  return tot;
}

/// Compute the multiplicative inverse of an Fp4.
constexpr inline Fp4 inv(Fp4 in) {
#define a in.elems
  // Compute the multiplicative inverse by basicly looking at Fp4 as a composite field and using the
  // same basic methods used to invert complex numbers.  We imagine that initially we have a
  // numerator of 1, and an denominator of a. i.e out = 1 / a; We set a' to be a with the first and
  // third components negated.  We then multiply the numerator and the denominator by a', producing
  // out = a' / (a * a'). By construction (a * a') has 0's in it's first and third elements.  We
  // call this number, 'b' and compute it as follows.
  Fp b0 = a[0] * a[0] + BETA * (a[1] * (a[3] + a[3]) - a[2] * a[2]);
  Fp b2 = a[0] * (a[2] + a[2]) - a[1] * a[1] + BETA * (a[3] * a[3]);
  // Now, we make b' by inverting b2.  When we muliply both sizes by b', we get out = (a' * b') /
  // (b * b').  But by construcion b * b' is in fact an element of Fp, call it c.
  Fp c = b0 * b0 + BETA * b2 * b2;
  // But we can now invert C direcly, and multiply by a'*b', out = a'*b'*inv(c)
  Fp ic = inv(c);
  // Note: if c == 0 (really should only happen if in == 0), our 'safe' version of inverse results
  // in ic == 0, and thus out = 0, so we have the same 'safe' behavior for Fp4.  Oh, and since we
  // want to multiply everything by ic, it's slightly faster to premultiply the two parts of b by ic
  // (2 multiplies instead of 4)
  b0 *= ic;
  b2 *= ic;
  return Fp4(a[0] * b0 + BETA * a[2] * b2,
             -a[1] * b0 + NBETA * a[3] * b2,
             -a[0] * b2 + a[2] * b0,
             a[1] * b2 - a[3] * b0);
#undef a
}

#undef BETA
#undef NBETA

} // namespace risc0
