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

#include <cstdint>

__device__ void step_exec(
    void* ctx, uint32_t steps, uint32_t cycle, Fp* arg0, Fp* arg1, Fp* arg2, Fp* arg3, Fp* arg4);

__device__ void step_verify_mem(
    void* ctx, uint32_t steps, uint32_t cycle, Fp* arg0, Fp* arg1, Fp* arg2, Fp* arg3, Fp* arg4);

__device__ void step_compute_accum(
    void* ctx, uint32_t steps, uint32_t cycle, Fp* arg0, Fp* arg1, Fp* arg2, Fp* arg3, Fp* arg4);

__device__ void step_verify_accum(
    void* ctx, uint32_t steps, uint32_t cycle, Fp* arg0, Fp* arg1, Fp* arg2, Fp* arg3, Fp* arg4);
