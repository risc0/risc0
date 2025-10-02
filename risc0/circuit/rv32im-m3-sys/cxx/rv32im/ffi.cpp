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

#include "hal/hal.h"
#include "prove/rv32im.h"
#include "verify/rv32im.h"

#include <cstdint>
#include <exception>
#include <string.h>

extern "C" {

using namespace risc0;
using namespace risc0::rv32im;

struct RawProver {
  Rv32imProver prover;
  std::vector<Fp> transcript;

  RawProver(IHalPtr hal, size_t po2) : prover(hal, po2) {}
};

struct RawSlice {
  const Fp* ptr;
  size_t len;
};

RawProver* risc0_circuit_rv32im_m3_prover_new_cpu(size_t po2) {
  IHalPtr hal = getCpuHal();
  return new RawProver(hal, po2);
}

RawProver* risc0_circuit_rv32im_m3_prover_new_cuda(size_t po2) {
  IHalPtr hal = getGpuHal();
  return new RawProver(hal, po2);
}

void risc0_circuit_rv32im_m3_prover_free(RawProver* raw) {
  delete raw;
}

RawSlice risc0_circuit_rv32im_m3_prover_transcript(RawProver* raw) {
  return RawSlice{raw->transcript.data(), raw->transcript.size()};
}

const char*
risc0_circuit_rv32im_m3_preflight(RawProver* raw, const uint8_t* elf_ptr, size_t elf_len) {
  try {
    LOG(0, "Loading elf");
    ArrayRef<uint8_t> elf(elf_ptr, elf_len);
    MemoryImage image = MemoryImage::fromRawElfBytes(elf);

    NullHostIO io;
    raw->prover.preflight(image, io);
  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}

const char* risc0_circuit_rv32im_m3_prove(RawProver* raw) {
  try {
    WriteIop writeIop;
    raw->prover.prove(writeIop);
    raw->transcript = writeIop.getTranscript();

    ReadIop readIop(raw->transcript.data(), raw->transcript.size());
    verifyRv32im(readIop, raw->prover.po2());
    readIop.done();
  } catch (const std::exception& err) {
    LOG(0, "ERROR: " << err.what());
    return strdup(err.what());
  } catch (...) {
    LOG(0, "UNKNOWN ERROR");
    return strdup("Generic exception");
  }
  LOG(0, "Completed successfuly");
  return nullptr;
}

} // extern "C"
