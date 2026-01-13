// Copyright 2026 RISC Zero, Inc.
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

  // Read a scalar value from the IOP.
  uint32_t readU32();

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
