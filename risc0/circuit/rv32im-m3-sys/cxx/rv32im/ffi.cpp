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
#include <string.h>

extern "C" {

using namespace risc0;
using namespace risc0::rv32im;

struct ProofResult {
  bool isError;
  uint32_t* data;
  uint8_t* error;
  size_t len;

  ProofResult(const std::vector<Fp>& vdata) 
      : isError(false)
      , data(new uint32_t[vdata.size()])
      , error(nullptr)
      , len(vdata.size()) {
    memcpy(data, vdata.data(), len * sizeof(uint32_t));
  }
  ProofResult(const std::string& err)
      : isError(true)
      , data(nullptr)
      , error(new uint8_t[err.size()])
      , len(err.size()) {
    memcpy(error, err.data(), len);
  }
  ~ProofResult() {
    delete[] data;
    delete[] error;
  }
};

ProofResult* risc0_circuit_rv32im_m3_prove(const uint8_t* elf_ptr, size_t elf_len) {
  try {
    size_t po2 = 14;

    IHalPtr hal = getGpuHal();
    Rv32imProver prover(hal, po2);

    LOG(0, "Loading elf");
    ArrayRef<uint8_t> elf(elf_ptr, elf_len);
    MemoryImage image = MemoryImage::fromRawElfBytes(elf);

    NullHostIO io;
    prover.preflight(image, io);

    WriteIop writeIop;
    prover.prove(writeIop);
    std::vector<Fp> transcript = writeIop.getTranscript();

    ReadIop readIop(transcript.data(), transcript.size());
    verifyRv32im(readIop, po2);
    readIop.done();

    return new ProofResult(transcript);
  } catch (const std::exception& err) {
    LOG(0, "ERROR: " << err.what());
    return new ProofResult(err.what());
  } catch (...) {
    LOG(0, "UNKNOWN ERROR");
    return new ProofResult("Generic exception");
  }
  // unreachable
  return nullptr;
}

void proof_dealloc(ProofResult* result) {
  delete result;
}

} // extern "C"
