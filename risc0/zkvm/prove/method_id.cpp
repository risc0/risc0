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
#include <iterator>
#include <map>

#include "risc0/core/elf.h"
#include "risc0/zkp/prove/poly_group.h"
#include "risc0/zkvm/prove/step.h"

namespace risc0 {

MethodId loadMethodId(const std::string& path) {
  std::ifstream file(path, std::ios::binary);
  file.exceptions(std::ios_base::badbit);
  std::istreambuf_iterator<char> it(file);
  std::vector<uint8_t> bytes(it, std::istreambuf_iterator<char>());
  return makeMethodId(bytes.data(), bytes.size());
}

MethodId makeMethodId(const uint8_t* bytes, size_t len) {
  MethodId ret;
  if (len % sizeof(ShaDigest)) {
    throw std::length_error("Invalid MethodId size");
  }

  size_t count = len / sizeof(ShaDigest);
  for (size_t i = 0; i < count; i++, bytes += sizeof(ShaDigest)) {
    ShaDigest digest;
    std::memcpy(digest.words, bytes, sizeof(ShaDigest));
    ret.push_back(digest);
  }

  return ret;
}

MethodId makeMethodId(const std::string& elfPath, size_t limit) {
  std::map<uint32_t, uint32_t> image;
  uint32_t startAddr = loadElf(elfPath, kMemSize, image);

  // Start with an empty return value
  MethodId ret;

  // Make the digest for each level
  size_t count = std::min(limit, kMaxCodeDigestCount);
  for (size_t i = 0; i < count; i++) {
    size_t cycles = kMinCycles * (1 << i);
    if (cycles < image.size() + 3 + kZkCycles) {
      // Can't even fit the program in this cycle size, just set to zero
      ret.push_back(ShaDigest::zero());
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
    ret.push_back(codeGroup.getMerkle().getRoot());
  }
  return ret;
}

} // namespace risc0
