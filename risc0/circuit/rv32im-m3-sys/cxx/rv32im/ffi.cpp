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

#include "rv32im/ffi.h"

#include "hal/hal.h"
#include "prove/rv32im.h"
#include "verify/rv32im.h"

#include <cstdint>
#include <cstring>
#include <exception>
#include <string.h>

extern "C" {

using namespace risc0;
using namespace risc0::rv32im;

struct ProverContext {
  Rv32imProver prover;
  MemoryImage image;
  std::vector<Fp> transcript;

  ProverContext(IHalPtr hal, size_t po2) : prover(hal, po2) {}
};

struct RustPage {
  uint32_t addr;
  const uint32_t* data;
};

struct RustSlicePage {
  const RustPage* ptr;
  size_t len;
};

struct RustMemoryImage {
  RustSlicePage pages;
};

struct RustSegment {
  RustMemoryImage image;
  // pub claim: Rv32imV2Claim,
  // pub read_record: Vec<Vec<u8>>,
  // pub write_record: Vec<u32>,
  // pub suspend_cycle: u32,
  // pub paging_cycles: u32,
  // pub segment_threshold: u32,
  // pub po2: u32,
  // pub index: u64,
  // pub povw_nonce: Option<PovwNonce>,
};

void risc0_circuit_rv32im_m3_set_log_level(unsigned level) {
  setLogLevel(level);
}

ProverContext* risc0_circuit_rv32im_m3_prover_new_cpu(size_t po2) {
  IHalPtr hal = getCpuHal();
  return new ProverContext(hal, po2);
}

ProverContext* risc0_circuit_rv32im_m3_prover_new_cuda(size_t po2) {
  IHalPtr hal = getGpuHal();
  return new ProverContext(hal, po2);
}

void risc0_circuit_rv32im_m3_prover_free(ProverContext* ctx) {
  delete ctx;
}

RustSliceFp risc0_circuit_rv32im_m3_prover_transcript(ProverContext* ctx) {
  return RustSliceFp{ctx->transcript.data(), ctx->transcript.size()};
}

const char* risc0_circuit_rv32im_m3_load_segment(ProverContext* ctx, const RustSegment* segment) {
  try {
    ctx->image = MemoryImage::zeros();
    for (size_t i = 0; i < segment->image.pages.len; i++) {
      const RustPage& page = segment->image.pages.ptr[i];
      auto data = std::make_shared<Page>();
      std::memcpy(data->data(), page.data, PAGE_SIZE_BYTES);
      ctx->image.setPage(page.addr, data);
    }
  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}

const char* risc0_circuit_rv32im_m3_preflight(ProverContext* ctx) {
  try {
    NullHostIO io;
    ctx->prover.preflight(ctx->image, io);
  } catch (const std::exception& err) {
    LOG(0, "ERROR: " << err.what());
    return strdup(err.what());
  } catch (...) {
    LOG(0, "UNKNOWN ERROR");
    return strdup("Generic exception");
  }
  return nullptr;
}

const char* risc0_circuit_rv32im_m3_prove(ProverContext* ctx) {
  try {
    WriteIop writeIop;
    ctx->prover.prove(writeIop);
    ctx->transcript = writeIop.getTranscript();

    ReadIop readIop(ctx->transcript.data(), ctx->transcript.size());
    verifyRv32im(readIop, ctx->prover.po2());
    readIop.done();
  } catch (const std::exception& err) {
    LOG(0, "ERROR: " << err.what());
    return strdup(err.what());
  } catch (...) {
    LOG(0, "UNKNOWN ERROR");
    return strdup("Generic exception");
  }
  LOG(1, "Completed successfuly");
  return nullptr;
}

} // extern "C"
