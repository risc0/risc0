#pragma once

#include "risc0/zkp/core/fp.h"
#include "risc0/zkp/core/fp4.h"

// CPU only base implementations of NTT based evaluation + interpolation (i.e. fwd NTT and rev NTT).
// We generally leave the coefficients bit-reversed (since this saves a lot of time) and provide an
// explicit bit reverse function if the user needs it (pretty much we mostly use it for testing).
// By bit reversed, we means that for P(x) = sum_i c_i * x^i, coefficient c_i will be in the array
// at location c_i = coeffArray[bit_rev(i)].

namespace risc0 {

// A 32-bit bit reversal
inline constexpr uint32_t bitReverse(uint32_t x) {
  x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
  x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
  x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
  x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
  return ((x >> 16) | (x << 16));
}

// Given a polynomial P(x), and a root of unity g, such that g^size = 1, g^x !=
// 1, 0 < x < size, we take as input io[i] = P(g^i).  We then compute the
// coefficients of the polynomial (i.e.  interpolate).  This is done in  place
// (i.e. the coefficient values are places in io).  The coefficients are
// returned in bit-reversed order.
void interpolateNTT(Fp* io, size_t size);
void interpolateNTT(Fp4* io, size_t size);

// Given coefficents of a polynomial (in bit-reversed order), and a root of
// unity g, such that g^size = 1, g^x != 1, 0 < x < size evaluate P at the Nth
// roots of unity i.e. io[i] = f(g^i) where g^N = 1 (and g^x != 1, 0 < x < N).
// If expandBits != 0, we presume the coefficients have been 'expanded' and thus
// we can skip steps.
void evaluateNTT(Fp* io, size_t size, size_t expandBits = 0);
void evaluateNTT(Fp4* io, size_t size, size_t expandBits = 0);

// Perform a bit-reversal on a buffer, i.e. io[i] <-> io[bitReverse(i)], where the
// low N = log2(size) bits are considered.
void bitReverse(Fp* io, size_t size);
void bitReverse(Fp4* io, size_t size);

// Expand from in -> out, by a factor F=(1 << expandBits), out[j] = in[j//F]. This
// basically preps bit reversed coefficients for evaluation over a larger domain.
void expand(Fp* out, const Fp* in, size_t sizeIn, size_t expandBits);
void expand(Fp4* out, const Fp4* in, size_t sizeIn, size_t expandBits);

} // End namespace risc0
