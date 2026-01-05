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

struct PreflightContext;
struct ProverContext;
struct RustSegment;
struct SegmentContext;

struct RustSliceFp {
  const risc0::Fp* ptr;
  size_t len;
};

namespace risc0 {
struct RowInfo;
}

const char* risc0_circuit_rv32im_m3_last_error() noexcept;
void risc0_circuit_rv32im_m3_clear_last_error() noexcept;

void risc0_circuit_rv32im_m3_segment_free(SegmentContext* ctx);
void risc0_circuit_rv32im_m3_preflight_free(PreflightContext* ctx);
void risc0_circuit_rv32im_m3_prover_free(ProverContext* ctx);

SegmentContext* risc0_circuit_rv32im_m3_segment_new(const RustSegment* segment);
PreflightContext* risc0_circuit_rv32im_m3_segment_preflight(SegmentContext* sctx, size_t po2);

size_t risc0_circuit_rv32im_m3_preflight_is_final(PreflightContext* ctx);

const risc0::RowInfo* risc0_circuit_rv32im_m3_preflight_row_info(PreflightContext* ctx);
size_t risc0_circuit_rv32im_m3_preflight_row_info_size(PreflightContext* ctx);

const uint32_t* risc0_circuit_rv32im_m3_preflight_aux(PreflightContext* ctx);
size_t risc0_circuit_rv32im_m3_preflight_aux_size(PreflightContext* ctx);

ProverContext* risc0_circuit_rv32im_m3_prover_new_cpu(size_t po2);
ProverContext* risc0_circuit_rv32im_m3_prover_new_cuda(size_t po2);

void risc0_circuit_rv32im_m3_prove(ProverContext* ctx,
                                   const risc0::RowInfo* rowInfo,
                                   size_t rowInfoSize,
                                   const uint32_t* aux,
                                   size_t auxSize);

RustSliceFp risc0_circuit_rv32im_m3_prover_transcript(ProverContext* ctx);

} // extern "C"
