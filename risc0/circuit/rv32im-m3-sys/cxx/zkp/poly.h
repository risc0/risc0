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

#include <vector>

#include "fpext.h"

namespace risc0 {

FpExt polyEval(const std::vector<FpExt>& coeffs, Fp x);
FpExt polyEval(const std::vector<FpExt>& coeffs, FpExt x);

std::vector<FpExt> polyInterpolate(const std::vector<FpExt>& xs, const std::vector<FpExt>& fxs);

// Divides a polynomail f(x) represented by 'coeffs' by (x - z), returns remainder
FpExt polyDivide(FpExt* coeffs, size_t deg, FpExt z);

}  // namespace risc0
