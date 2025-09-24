// Copyright 2025 RISC Zero, Inc.
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

#include "zkp/fpext.h"

namespace risc0 {

inline uint32_t bitReverse(uint32_t x) {
  x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
  x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
  x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
  x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
  return ((x >> 16) | (x << 16));
}

void multiBitReverse(Fp* io, size_t size, size_t count = 1);
void multiBitReverse(FpExt* io, size_t size, size_t count = 1);
void multiEvaluate(Fp* io, size_t size, size_t count = 1);
void multiEvaluate(FpExt* io, size_t size, size_t count = 1);
void multiInterpolate(Fp* io, size_t size, size_t count = 1);
void multiInterpolate(FpExt* io, size_t size, size_t count = 1);
void multiExpand(Fp* io, size_t sizeIn, size_t sizeOut, size_t count = 1);
void multiShift(Fp* io, size_t size, size_t count = 1);

} // namespace risc0
