// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT
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

#include "fp.h"
#include "fpext.h"

#include <cstdint>
#include <cstdio>
#include <exception>
#include <string.h>

using namespace risc0;

namespace risc0::circuit::rv32im_v2 {

FpExt poly_fp(size_t cycle, size_t steps, FpExt* poly_mix, Fp** args);

} // namespace risc0::circuit::rv32im_v2

extern "C" const char* risc0_circuit_rv32im_cpu_poly_fp(
    size_t cycle, size_t steps, FpExt* poly_mix, Fp** args, FpExt* result) {
  try {
    *result = circuit::rv32im_v2::poly_fp(cycle, steps, poly_mix, args);
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}
