#pragma once

#include "risc0/zkp/core/fp4.h"

namespace risc0 {

// Evaluate a polynomial
Fp4 polyEval(const Fp4* coeffs, size_t size, Fp4 val);

// In-place polynomial division: Take the coefficients in P, and divide by (X - z) for some z,
// return the remainder.
Fp4 polyDivide(Fp4* p, size_t size, Fp4 z);

// General purpose polynomial interpolation.  Given the goal value f(x) at a set of evalation points
// x, compute coefficients
void polyInterpolate(Fp4* out, const Fp4* x, const Fp4* fx, size_t size);

} // namespace risc0
