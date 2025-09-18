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

#include <ff/baby_bear.hpp>

static __device__ bb31_t pow(bb31_t b, int e) {
  return b ^ (unsigned int)e;
}

static __device__ bb31_t inv(bb31_t a) {
  return a.reciprocal();
}

typedef bb31_t Fp;
typedef bb31_4_t Fp4;
typedef bb31_4_t FpExt;
