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

#include <array>
#include <cstddef>
#include <vector>

namespace risc0::circuit::recursion {

std::array<Fp, 4>
extern_womRead(void* ctx, size_t cycle, const char* extra, std::array<Fp, 1> args);

void extern_womWrite(void* ctx, size_t cycle, const char* extra, std::array<Fp, 5> args);

void extern_plonkWrite_wom(void* ctx, size_t cycle, const char* extra, std::array<Fp, 5> args);

std::array<Fp, 5>
extern_plonkRead_wom(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args);

void extern_plonkWriteAccum_wom(void* ctx, size_t cycle, const char* extra, std::array<Fp, 4> args);

std::array<Fp, 4>
extern_plonkReadAccum_wom(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args);

void extern_readIOPHeader(void* ctx, size_t cycle, const char* extra, std::array<Fp, 2> args);

std::array<Fp, 4>
extern_readIOPBody(void* ctx, size_t cycle, const char* extra, std::array<Fp, 3> args);

std::array<Fp, 16>
extern_readCoefficients(void* ctx, size_t cycle, const char* extra, std::array<Fp, 0> args);

void extern_log(void* ctx, size_t cycle, const char* extra, std::vector<Fp> args);

} // namespace risc0::circuit::recursion
