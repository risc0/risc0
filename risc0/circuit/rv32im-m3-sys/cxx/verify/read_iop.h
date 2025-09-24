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

namespace risc0 {

class ReadIop {
public:
  // Initialize from a transcript
  ReadIop(const Fp* buf, uint32_t size);

  // Read from the prover
  void read(Fp* buf, size_t size);

  // Read from the prover
  void read(FpExt* buf, size_t size);

  // Read from the prover
  void read(Digest* buf, size_t size);

  // Verify we have fully read transcript
  void done();

  // Commit + mix
  void commit(const Digest& digest);

  // Generate a psuedorandom field element
  Fp rngFp();

  // Generate a psuedorandom extension field element
  FpExt rngFpExt();

  // Generate cryptographically uniform psuedorandom bits
  size_t rngBits(size_t bits);

private:
  const Fp* buf;
  size_t size;
  size_t offset;
  Rng rng;
};

} // namespace risc0
