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

#pragma once

/// \file
/// Defines the core finite field data type, Fp, and some free functions on the type.

#include <cstdint>

/// The Fp class is an element of the finite field F_p, where P is the prime number 15*2^27 + 1.
/// Put another way, Fp is basically integer arithmetic modulo P.
///
/// The 'Fp' datatype is the core type of all of the operations done within the zero knowledge
/// proofs, and is smallest 'addressable' datatype, and the base type of which all composite types
/// are built.  In many ways, one can imagine it as the word size of a very strange architecture.
///
/// This specific prime P was chosen to:
/// - Be less than 2^31 so that it fits within a 32 bit word and doesn't overflow on addition.
/// - Otherwise have as large a power of 2 in the factors of P-1 as possible.
///
/// This last property is useful for number theoretical transforms (the fast fourier transform
/// equivalent on finite fields).  See NTT.h for details.
///
/// The Fp class wraps all the standard arithmetic operations to make the finite field elements look
/// basically like ordinary numbers (which they mostly are).
class Fp {
public:
  /// The value of P, the modulus of Fp.
  static constexpr uint32_t P = 15 * (uint32_t(1) << 27) + 1;
  static constexpr uint32_t M = 0x88000001;
  static constexpr uint32_t R2 = 1172168163;
  static constexpr uint32_t INVALID = 0xffffffff;

private:
  // The actual value, always < P.
  uint32_t val;

  // We make 'impls' of the core ops which all the other uses call.  This is done to allow for
  // tweaking of the implementation later, for example switching to montgomery representation or
  // doing inline assembly or some crazy CUDA stuff.

  // Add two numbers
  static __host__ __device__ constexpr uint32_t add(uint32_t a, uint32_t b) {
    uint32_t r = a + b;
    return (r >= P ? r - P : r);
  }

  // Subtract two numbers
  static __host__ __device__ constexpr uint32_t sub(uint32_t a, uint32_t b) {
    uint32_t r = a - b;
    return (r > P ? r + P : r);
  }

  // Multiply two numbers
  static __host__ __device__ constexpr uint32_t mul(uint32_t a, uint32_t b) {
    uint64_t o64 = uint64_t(a) * uint64_t(b);
    uint32_t low = -uint32_t(o64);
    uint32_t red = M * low;
    o64 += uint64_t(red) * uint64_t(P);
    uint32_t ret = o64 >> 32;
    return (ret >= P ? ret - P : ret);
  }

  // Encode / Decode
  static __host__ __device__ constexpr uint32_t encode(uint32_t a) { return mul(R2, a); }

  static __host__ __device__ constexpr uint32_t decode(uint32_t a) { return mul(1, a); }

  // A private constructor that take the 'internal' form.
  __host__ __device__ constexpr Fp(uint32_t val, bool ignore) : val(val) {}

public:
  /// Default constructor, sets value to 0.
  __host__ __device__ constexpr Fp() : val(0) {}

  /// Construct an FP from a uint32_t, wrap if needed
  __host__ __device__ constexpr Fp(uint32_t val) : val(encode(val)) {}

  /// Construct an Fp from an already-encoded raw value
  __host__ __device__ static constexpr Fp fromRaw(uint32_t val) { return Fp(val, true); }

  /// Convert to a uint32_t
  __host__ __device__ constexpr uint32_t asUInt32() const { return decode(val); }

  /// Return the raw underlying word
  __host__ __device__ constexpr uint32_t asRaw() const { return val; }

  /// Get the largest value, basically P - 1.
  __host__ __device__ static constexpr Fp maxVal() { return P - 1; }

  /// Get an 'invalid' Fp value
  __host__ __device__ static constexpr Fp invalid() { return Fp(INVALID, true); }

  __host__ __device__ constexpr inline Fp zeroize() {
    if (val == INVALID) {
      val = 0;
    }
    return *this;
  }

  // Implement all the various overloads
  __host__ __device__ constexpr void operator=(uint32_t rhs) { val = encode(rhs); }

  __host__ __device__ constexpr Fp operator+(Fp rhs) const { return Fp(add(val, rhs.val), true); }

  __host__ __device__ constexpr Fp operator-() const { return Fp(sub(0, val), true); }

  __host__ __device__ constexpr Fp operator-(Fp rhs) const { return Fp(sub(val, rhs.val), true); }

  __host__ __device__ constexpr Fp operator*(Fp rhs) const { return Fp(mul(val, rhs.val), true); }

  __host__ __device__ constexpr Fp operator+=(Fp rhs) {
    val = add(val, rhs.val);
    return *this;
  }

  __host__ __device__ constexpr Fp operator-=(Fp rhs) {
    val = sub(val, rhs.val);
    return *this;
  }

  __host__ __device__ constexpr Fp operator*=(Fp rhs) {
    val = mul(val, rhs.val);
    return *this;
  }

  __host__ __device__ constexpr bool operator==(Fp rhs) const { return val == rhs.val; }

  __host__ __device__ constexpr bool operator!=(Fp rhs) const { return val != rhs.val; }

  __host__ __device__ constexpr bool operator<(Fp rhs) const {
    return decode(val) < decode(rhs.val);
  }

  __host__ __device__ constexpr bool operator<=(Fp rhs) const {
    return decode(val) <= decode(rhs.val);
  }

  __host__ __device__ constexpr bool operator>(Fp rhs) const {
    return decode(val) > decode(rhs.val);
  }

  __host__ __device__ constexpr bool operator>=(Fp rhs) const {
    return decode(val) >= decode(rhs.val);
  }

  // Post-inc/dec
  __host__ __device__ constexpr Fp operator++(int) {
    Fp r = *this;
    val = add(val, encode(1));
    return r;
  }

  __host__ __device__ constexpr Fp operator--(int) {
    Fp r = *this;
    val = sub(val, encode(1));
    return r;
  }

  // Pre-inc/dec
  __host__ __device__ constexpr Fp operator++() {
    val = add(val, encode(1));
    return *this;
  }

  __host__ __device__ constexpr Fp operator--() {
    val = sub(val, encode(1));
    return *this;
  }
};

/// Raise a value to a power
__host__ __device__ constexpr inline Fp pow(Fp x, size_t n) {
  Fp tot = 1;
  while (n != 0) {
    if (n % 2 == 1) {
      tot *= x;
    }
    n = n / 2;
    x *= x;
  }
  return tot;
}

/// Compute the multiplicative inverse of x, or `1/x` in finite field terms.  Since `x^(P-1) == 1
/// (mod P)` for any x != 0 (as a consequence of Fermat's little theorem), it follows that `x *
/// x^(P-2) == 1 (mod P)` for x != 0.  That is, `x^(P-2)` is the multiplicative inverse of x.
/// Computed this way, the 'inverse' of zero comes out as zero, which is convenient in many cases,
/// so we leave it.
__host__ __device__ constexpr inline Fp inv(Fp x) {
  return pow(x, Fp::P - 2);
}
