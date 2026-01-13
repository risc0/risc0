// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#pragma once

#include <vector>

#include "fpext.h"

namespace risc0 {

FpExt polyEval(const std::vector<FpExt>& coeffs, Fp x);
FpExt polyEval(const std::vector<FpExt>& coeffs, FpExt x);

std::vector<FpExt> polyInterpolate(const std::vector<FpExt>& xs, const std::vector<FpExt>& fxs);

// Divides a polynomail f(x) represented by 'coeffs' by (x - z), returns
// remainder
FpExt polyDivide(FpExt* coeffs, size_t deg, FpExt z);

} // namespace risc0
