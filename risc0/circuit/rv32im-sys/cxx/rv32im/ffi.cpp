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
#include "vendor/nvtx3/nvtx3.hpp"
#include "verify/rv32im.h"

#include <cstdint>
#include <cstring>
#include <exception>
#include <string.h>

using namespace risc0;
using namespace risc0::rv32im;

extern "C" {

static thread_local std::string gLastError;

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
  uint32_t suspendCycle;
};

static void setLastError(const char* msg) {
  LOG(0, "ERROR: " << msg);
  gLastError = msg ? msg : "Unknown error";
}

const char* risc0_circuit_rv32im_m3_last_error() noexcept {
  return gLastError.empty() ? nullptr : gLastError.c_str();
}

void risc0_circuit_rv32im_m3_clear_last_error() noexcept {
  gLastError.clear();
}

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
    LOG(3, "onWrite: " << bytes << " bytes");
    return bytes;
  }

  uint32_t onRead(uint32_t fd, uint8_t* data, uint32_t size) override {
    auto& record = reads[curRead++];
    if (size < record.size()) {
      throw std::runtime_error("Read record too big");
    }
    LOG(3, "onRead: " << record.size() << " bytes");
    std::memcpy(data, record.data(), record.size());
    return record.size();
  }

private:
  std::vector<std::vector<uint8_t>> reads;
  std::vector<uint32_t> writes;
  size_t curRead = 0;
  size_t curWrite = 0;
};

template <class F> inline auto tryRet(F&& f) noexcept -> std::invoke_result_t<F> {
  try {
    return f();
  } catch (const std::exception& err) {
    setLastError(err.what());
    return nullptr;
  } catch (...) {
    setLastError("unknown exception");
    return nullptr;
  }
}

template <class F> inline void tryVoid(F&& f) noexcept {
  try {
    f();
  } catch (const std::exception& err) {
    setLastError(err.what());
  } catch (...) {
    setLastError("unknown exception");
  }
}

} // namespace

extern "C" {

struct SegmentContext {
  MemoryImage image;
  ReplayHostIO io;
  uint32_t endCycle;
};

struct PreflightContext {
  PreflightResultsPtr results;
  bool isFinal = false;
};

struct ProverContext {
  Rv32imProver prover;
  std::vector<Fp> transcript;

  ProverContext(IHalPtr hal, size_t po2) : prover(hal, po2) {}
};

void risc0_circuit_rv32im_m3_segment_free(SegmentContext* ctx) {
  delete ctx;
}

void risc0_circuit_rv32im_m3_preflight_free(PreflightContext* ctx) {
  delete ctx;
}

void risc0_circuit_rv32im_m3_prover_free(ProverContext* ctx) {
  delete ctx;
}

SegmentContext* risc0_circuit_rv32im_m3_segment_new(const RustSegment* segment) {
  return tryRet([&] {
    nvtx3::scoped_range range("load_segment");
    SegmentContext* ctx = new SegmentContext{};
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
    ctx->endCycle = segment->suspendCycle;
    LOG(1, "endCycle: " << ctx->endCycle);
    return ctx;
  });
}

PreflightContext* risc0_circuit_rv32im_m3_segment_preflight(SegmentContext* ctx, size_t po2) {
  return tryRet([&] {
    nvtx3::scoped_range range("preflight");
    PreflightContext* ret = new PreflightContext{};
    ret->results = preflight(po2, ctx->image, ctx->io, ctx->endCycle);
    if (ret->results->cycles > ctx->endCycle) {
      throw std::runtime_error("Preflight cycles > requested end cycle");
    }
    LOG(1,
        "endCycle: " << ctx->endCycle << ", retiredCycles: " << ret->results->cycles
                     << ", isFinal: " << ret->results->isFinal);
    ctx->endCycle -= ret->results->cycles;
    if (ret->results->isFinal && ctx->endCycle) {
      throw std::runtime_error("Termination before reaching requested end cycle");
    }
    if (ctx->endCycle == 0) {
      ret->isFinal = true;
    }
    return ret;
  });
}

size_t risc0_circuit_rv32im_m3_preflight_is_final(PreflightContext* ctx) {
  return ctx->isFinal;
}

const RowInfo* risc0_circuit_rv32im_m3_preflight_row_info(PreflightContext* ctx) {
  return ctx->results->rowInfo.data();
}

size_t risc0_circuit_rv32im_m3_preflight_row_info_size(PreflightContext* ctx) {
  return ctx->results->rowInfo.size();
}

const uint32_t* risc0_circuit_rv32im_m3_preflight_aux(PreflightContext* ctx) {
  return ctx->results->aux.data();
}

size_t risc0_circuit_rv32im_m3_preflight_aux_size(PreflightContext* ctx) {
  return ctx->results->aux.size();
}

ProverContext* risc0_circuit_rv32im_m3_prover_new_cpu(size_t po2) {
  return tryRet([&] {
    IHalPtr hal = getCpuHal();
    return new ProverContext(hal, po2);
  });
}

ProverContext* risc0_circuit_rv32im_m3_prover_new_cuda(size_t po2) {
  return tryRet([&] {
    IHalPtr hal = getGpuHal();
    return new ProverContext(hal, po2);
  });
}

void risc0_circuit_rv32im_m3_prove(ProverContext* ctx,
                                   const RowInfo* rowInfo,
                                   size_t rowInfoSize,
                                   const uint32_t* aux,
                                   size_t auxSize) {
  return tryVoid([&] {
    nvtx3::scoped_range range("prove");
    WriteIop writeIop;
    writeIop.write(RV32IM_SEAL_VERSION);
    uint32_t po2 = ctx->prover.po2();
    // LOG(0, "po2: " << po2);
    writeIop.write(po2);
    ctx->prover.prove(writeIop, rowInfo, rowInfoSize, aux, auxSize);
    ctx->transcript = writeIop.getTranscript();

    ReadIop readIop(ctx->transcript.data(), ctx->transcript.size());
    uint32_t readVersion = readIop.readU32(); // skip past version
    uint32_t readPo2 = readIop.readU32();     // skip past po2
    LOG(2, "version: " << readVersion << ", po2: " << readPo2);
    verifyRv32im(readIop, ctx->prover.po2());
    readIop.done();
    LOG(1, "Completed successfuly");
  });
}

RustSliceFp risc0_circuit_rv32im_m3_prover_transcript(ProverContext* ctx) {
  return RustSliceFp{ctx->transcript.data(), ctx->transcript.size()};
}

} // extern "C"
