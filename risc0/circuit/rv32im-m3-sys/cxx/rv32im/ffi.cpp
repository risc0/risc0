// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "hal/hal.h"
#include "prove/rv32im.h"
#include "verify/rv32im.h"

#include <cstdint>
#include <exception>
#include <string.h>

extern "C" {

using namespace risc0;
using namespace risc0::rv32im;

const char* risc0_circuit_rv32im_m3_prove(const uint8_t* elf_ptr, size_t elf_len) {
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
  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}

} // extern "C"
