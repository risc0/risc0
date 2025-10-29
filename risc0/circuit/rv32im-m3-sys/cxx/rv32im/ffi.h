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

#include "zkp/fp.h"

#include <cstddef>
#include <cstdint>

extern "C" {

struct ProverContext;

struct RustSegment;

struct RustSliceFp {
  const risc0::Fp* ptr;
  size_t len;
};

ProverContext* risc0_circuit_rv32im_m3_prover_new_cpu(size_t po2);

ProverContext* risc0_circuit_rv32im_m3_prover_new_cuda(size_t po2);

void risc0_circuit_rv32im_m3_prover_free(ProverContext* ctx);

RustSliceFp risc0_circuit_rv32im_m3_prover_transcript(ProverContext* ctx);

const char* risc0_circuit_rv32im_m3_load_segment(ProverContext* ctx, const RustSegment* segment);

const char* risc0_circuit_rv32im_m3_preflight(ProverContext* ctx, uint32_t* isDone);

const char* risc0_circuit_rv32im_m3_prove(ProverContext* ctx);

} // extern "C"
