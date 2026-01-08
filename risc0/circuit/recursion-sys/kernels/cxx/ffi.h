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

#include "fp.h"
#include "fpext.h"

#include <cstddef>

namespace risc0::circuit::recursion {

Fp step_exec(void* ctx, size_t steps, size_t cycle, Fp** args);
Fp step_verify_mem(void* ctx, size_t steps, size_t cycle, Fp** args);
Fp step_compute_accum(void* ctx, size_t steps, size_t cycle, Fp** args);
Fp step_verify_accum(void* ctx, size_t steps, size_t cycle, Fp** args);

FpExt poly_fp(size_t cycle, size_t steps, FpExt* poly_mix, Fp** args);

} // namespace risc0::circuit::recursion
