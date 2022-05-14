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

#include "risc0/core/rng.h"
#include "risc0/zkp/core/sha256_cpu.h"

#include <gtest/gtest.h>

namespace risc0 {

TEST(Sha256, TestVectors) {
  // Standard test vectors
  ASSERT_EQ(shaHash("abc"),
            ShaDigest({0xba7816bf,
                       0x8f01cfea,
                       0x414140de,
                       0x5dae2223,
                       0xb00361a3,
                       0x96177a9c,
                       0xb410ff61,
                       0xf20015ad}));
  ASSERT_EQ(shaHash(""),
            ShaDigest({0xe3b0c442,
                       0x98fc1c14,
                       0x9afbf4c8,
                       0x996fb924,
                       0x27ae41e4,
                       0x649b934c,
                       0xa495991b,
                       0x7852b855}));
  ASSERT_EQ(shaHash("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"),
            ShaDigest({0x248d6a61,
                       0xd20638b8,
                       0xe5c02693,
                       0x0c3e6039,
                       0xa33ce459,
                       0x64ff2167,
                       0xf6ecedd4,
                       0x19db06c1}));
  ASSERT_EQ(shaHash("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmno"
                    "pqklmnopqrlmnopqrs"
                    "mnopqrstnopqrstu"),
            ShaDigest({0xcf5b16a7,
                       0x78af8380,
                       0x036ce59e,
                       0x7b049237,
                       0x0b249b11,
                       0xe8f07a51,
                       0xafac4503,
                       0x7afee9d1}));
  // Test also the 'hexDigest' bit.
  // Python says:
  // >>> hashlib.sha256("Byzantium").hexdigest()
  // 'f75c763b4a52709ac294fc7bd7cf14dd45718c3d50b36f4732b05b8c6017492a'
  ASSERT_EQ(hexDigest(shaHash("Byzantium")),
            "f75c763b4a52709ac294fc7bd7cf14dd45718c3d50b36f4732b05b8c6017492a");
}

TEST(Sha256, compareFpVsBytes) {
  // Try sizes 0 - 100 for variety
  PsuedoRng rng(2);
  for (size_t i = 0; i < 100; i++) {
    // Make a vector of fp values and their 'stringified' form
    std::vector<Fp> vals(i);
    std::string vstr;
    for (size_t j = 0; j < i; j++) {
      // For each value, pick a random number
      Fp val = Fp::random(rng);
      // Push to the list
      vals[j] = val;
      // Encode in native byte order onto string.
      uint32_t word = val.asUInt32();
      vstr.append(reinterpret_cast<const char*>(&word), sizeof(word));
    }
    ASSERT_EQ(shaHash(vals.data(), vals.size()), shaHash(vstr));
  }
}

} // End namespace risc0
