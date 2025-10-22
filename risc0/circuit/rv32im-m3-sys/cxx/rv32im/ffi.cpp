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

using namespace risc0;
using namespace risc0::rv32im;

extern "C" {

struct RustPage {
  uint32_t addr;
  const uint32_t* data;
};

struct RustDigestEntry {
  uint32_t idx;
  Digest digest;
};

struct RustSlicePage {
  const RustPage* ptr;
  size_t len;
};

struct RustSliceDigestEntry {
  const RustDigestEntry* ptr;
  size_t len;
};

struct RustSliceByte {
  const uint8_t* ptr;
  size_t len;
};

struct RustSliceWord {
  const uint32_t* ptr;
  size_t len;
};

struct RustSliceReadRecord {
  const RustSliceByte* ptr;
  size_t len;
};

struct RustMemoryImage {
  RustSlicePage pages;
  RustSliceDigestEntry digests;
};

struct RustSegment {
  RustMemoryImage image;
  RustSliceReadRecord reads;
  RustSliceWord writes;
  // pub claim: Rv32imV2Claim,
  // pub suspend_cycle: u32,
  // pub paging_cycles: u32,
  // pub segment_threshold: u32,
  // pub po2: u32,
  // pub index: u64,
  // pub povw_nonce: Option<PovwNonce>,
};

} // extern "C"

namespace {

class ReplayHostIO : public HostIO {
public:
  void loadSegment(const RustSegment* segment) {
    reads.clear();
    writes.clear();

    for (size_t i = 0; i < segment->reads.len; i++) {
      const RustSliceByte& slice = segment->reads.ptr[i];
      reads.emplace_back(std::vector(slice.ptr, slice.ptr + slice.len));
    }

    writes.insert(writes.end(), segment->writes.ptr, segment->writes.ptr + segment->writes.len);

    curRead = 0;
    curWrite = 0;
  }

public:
  uint32_t onWrite(uint32_t fd, const uint8_t* data, uint32_t size) override {
    size_t bytes = writes[curWrite++];
    LOG(2, "onWrite: " << bytes << " bytes");
    return bytes;
  }

  uint32_t onRead(uint32_t fd, uint8_t* data, uint32_t size) override {
    auto& record = reads[curRead++];
    if (size < record.size()) {
      throw std::runtime_error("Read record too big");
    }
    LOG(2, "onRead: " << record.size() << " bytes");
    std::memcpy(data, record.data(), record.size());
    return record.size();
  }

private:
  std::vector<std::vector<uint8_t>> reads;
  std::vector<uint32_t> writes;
  size_t curRead = 0;
  size_t curWrite = 0;
};

} // namespace

extern "C" {

struct ProverContext {
  Rv32imProver prover;
  MemoryImage image;
  ReplayHostIO io;
  std::vector<Fp> transcript;

  ProverContext(IHalPtr hal, size_t po2) : prover(hal, po2) {}
};

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
    // ctx->image.dumpZeros();
    for (size_t i = 0; i < segment->image.pages.len; i++) {
      const RustPage& page = segment->image.pages.ptr[i];
      auto data = std::make_shared<Page>();
      std::memcpy(data->data(), page.data, PAGE_SIZE_BYTES);
      ctx->image.setPageRaw(page.addr, data);
    }
    for (size_t i = 0; i < segment->image.digests.len; i++) {
      const RustDigestEntry& entry = segment->image.digests.ptr[i];
      ctx->image.setDigestRaw(entry.idx, entry.digest);
    }
    // ctx->image.dump();
    ctx->io.loadSegment(segment);
  } catch (const std::exception& err) {
    LOG(0, "ERROR: " << err.what());
    return strdup(err.what());
  } catch (...) {
    LOG(0, "UNKNOWN ERROR");
    return strdup("Generic exception");
  }
  return nullptr;
}

const char* risc0_circuit_rv32im_m3_preflight(ProverContext* ctx) {
  try {
    ctx->prover.preflight(ctx->image, ctx->io);
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
    writeIop.write(RV32IM_SEAL_VERSION);
    uint32_t po2 = ctx->prover.po2();
    // LOG(0, "po2: " << po2);
    writeIop.write(po2);
    ctx->prover.prove(writeIop);
    ctx->transcript = writeIop.getTranscript();

    ReadIop readIop(ctx->transcript.data(), ctx->transcript.size());
    uint32_t readVersion = readIop.readU32(); // skip past version
    uint32_t readPo2 = readIop.readU32();     // skip past po2
    LOG(2, "version: " << readVersion << ", po2: " << readPo2);
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
