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

#pragma once

#include "risc0/core/util.h"
#include "risc0/zkp/core/fp4.h"
#include "risc0/zkp/core/sha_rng.h"

#include <vector>

namespace risc0 {

class ReadIOP {
public:
  // Intialize a IOP reader with a proof
  ReadIOP(const uint32_t* proof, size_t size) : proof(proof), size(size) {}
  // Reads 'unverified' data from the proof (typically verified later via a commitment)
  void read(uint32_t* out, size_t readSize) {
    REQUIRE(size >= readSize);
    std::copy(proof, proof + readSize, out);
    proof += readSize;
    size -= readSize;
  }
  void read(Fp* data, size_t count) {
    std::vector<uint32_t> no_cast(count);
    read(no_cast.data(), count);
    for (size_t i = 0; i < count; i++) {
      data[i] = Fp(no_cast[i]);
    }
  }
  void read(Fp4* data, size_t count) { read(reinterpret_cast<Fp*>(data), count * 4); }
  void read(ShaDigest* data, size_t count) {
    read(reinterpret_cast<uint32_t*>(data), count * sizeof(ShaDigest) / sizeof(uint32_t));
  }
  // Apply a commitment to the RNG state
  void commit(const ShaDigest& message) { rng.mix(message); }
  // Get the psudeorandom challenge at this point in the protocol
  uint32_t generate() { return rng.generate(); }
  // Verify the proof was complete consumed
  void verifyComplete() { REQUIRE(size == 0); }

private:
  const uint32_t* proof;
  size_t size;
  ShaRng rng;
};

} // namespace risc0
