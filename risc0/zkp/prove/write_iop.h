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

#include "risc0/zkp/core/sha_rng.h"

#include <vector>

namespace risc0 {

class WriteIOP {
public:
  // Begin a new empty proof
  WriteIOP() = default;
  // Called by the prover to write some data.  This data is not cryptographically verifiable on it's
  // own, but is typically commited via a later hash which includes it.
  void write(const uint32_t* data, size_t count) { proof.insert(proof.end(), data, data + count); }
  // Versions for various other data types
  void write(const Fp* data, size_t count) {
    std::vector<uint32_t> no_cast(count);
    for (size_t i = 0; i < count; i++) {
      no_cast[i] = (data[i].asUInt32());
    }
    write(no_cast.data(), count);
  }
  void write(const Fp4* data, size_t count) { write(reinterpret_cast<const Fp*>(data), count * 4); }
  void write(const ShaDigest* data, size_t count) {
    write(reinterpret_cast<const uint32_t*>(data), count * sizeof(ShaDigest) / sizeof(uint32_t));
  }
  // Called by the prover to commit to some hash (usually data written earlier or a Merkle root)
  void commit(const ShaDigest& message) { rng.mix(message); }
  // Called to get a psudorandom challenge value. Since the PRNG is cyptogrpahially strong, and
  // since the source data for the PRNG includes all values commited to earlier, it is
  // computationally infeasble for the prover to control this value, and by the random oracle model
  // can be viewed as effectively equivilent to random data.
  uint32_t generate() { return rng.generate(); }
  // Get the final proof at the end of the protocol
  std::vector<uint32_t> getProof() const { return proof; }

private:
  // The proof being generated
  std::vector<uint32_t> proof;
  // The cryptographic mixer
  ShaRng rng;
};

} // namespace risc0
