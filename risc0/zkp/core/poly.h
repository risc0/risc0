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
