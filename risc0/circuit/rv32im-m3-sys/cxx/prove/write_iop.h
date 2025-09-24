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

#pragma once

#include "zkp/rng.h"

#include <vector>

namespace risc0 {

class WriteIop {
public:
  // Initialize from a transcript
  WriteIop() = default;

  // Write from the prover
  void write(const Fp* buf, size_t size);

  // Write from the prover
  void write(const FpExt* buf, size_t size);

  // Write from the prover
  void write(const Digest* buf, size_t size);

  // Get final transcript
  const std::vector<Fp>& getTranscript();

  // Commit + mix
  void commit(const Digest& digest);

  // Generate a psuedorandom field element
  Fp rngFp();

  // Generate a psuedorandom extension field element
  FpExt rngFpExt();

  // Generate cryptographically uniform psuedorandom bits
  size_t rngBits(size_t bits);

private:
  std::vector<Fp> transcript;
  Rng rng;
};

} // namespace risc0
