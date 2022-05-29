// Copyright 2022 Risc0, Inc.
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

#include "risc0/zkvm/prove/method_id.h"

#include <fstream>
#include <map>

#include "risc0/core/elf.h"
#include "risc0/zkp/prove/poly_group.h"
#include "risc0/zkvm/prove/step.h"

namespace risc0 {

MethodID::MethodID(const MethodDigests& digests) : _digests(digests) {}

MethodID MethodID::fromElf(const std::string& path) {
  // Load the ELF file into an image
  std::map<uint32_t, uint32_t> image;
  uint32_t startAddr = loadElf(path, kMemSize, image);

  // Start with an empty return value
  MethodDigests digests;

  // Make the digest for each level
  for (size_t i = 0; i < kCodeDigestCount; i++) {
    size_t cycles = kMinCycles * (1 << i);
    if (cycles < image.size() + 3 + kZkCycles) {
      // Can't even fit the program in this cycle size, just set to zero
      digests[i] = ShaDigest::zero();
      continue;
    }
    // Make a vector + set it up with the elf data
    std::vector<Fp> code(cycles * kCodeSize);
    setupCode(code.data(), cycles, startAddr, image);
    // Copy into accel buffer
    auto coeffs = AccelSlice<Fp>::copy(code);
    // Do interpolate + shift
    batchInterpolateNTT(coeffs, kCodeSize);
    zkShiftAccel(coeffs, kCodeSize);
    // Make the poly-group + extract the root
    PolyGroup codeGroup(coeffs, kCodeSize, cycles);
    digests[i] = codeGroup.getMerkle().getRoot();
  }
  return MethodID(digests);
}

MethodID MethodID::fromBytes(const std::array<std::uint8_t, digestBytes>& bytes) {
  MethodDigests digests;
  std::memcpy(&digests, &bytes, digestBytes);
  return MethodID(digests);
}

MethodID MethodID::fromBytes(const uint8_t* bytes) {
  std::array<std::uint8_t, digestBytes> sized;
  std::memcpy(&sized, &bytes, digestBytes);
  return MethodID::fromBytes(sized);
}

std::array<uint8_t, digestBytes> MethodID::toBytes() const {
  std::array<std::uint8_t, digestBytes> bytes;
  std::memcpy(&bytes, &_digests, digestBytes);
  return bytes;
}

std::unique_ptr<MethodID> method_id_from_elf(const std::string& path) {
  return std::make_unique<MethodID>(MethodID::fromElf(path));
}
std::unique_ptr<MethodID> method_id_from_bytes(const std::array<uint8_t, digestBytes>& bytes) {
  return std::make_unique<MethodID>(MethodID::fromBytes(bytes));
}

} // namespace risc0
