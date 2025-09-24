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

#pragma once

#include <cstdint>
#include <cstdlib>
#include <string>

namespace risc0 {

// A digest (still in uint32_t parts for easy rolling up in merkle trees).
struct Digest {
  uint32_t words[8];
  // The 'zero' digest, sort of the nullptr of digests.
  static Digest zero() { return {{0, 0, 0, 0, 0, 0, 0, 0}}; }

  int cmp(Digest rhs) const {
    for (size_t i = 0; i < 8; i++) {
      if (words[i] != rhs.words[i]) {
        return words[i] < rhs.words[i] ? -1 : 1;
      }
    }
    return 0;
  }
  bool operator==(Digest rhs) const { return cmp(rhs) == 0; }
  bool operator!=(Digest rhs) const { return cmp(rhs) != 0; }
};

inline std::string hexDigest(const Digest& digest) {
  const char* hexdigits = "0123456789abcdef";
  std::string r(64, 0);
  for (size_t i = 0; i < 8; i++) {
    uint32_t word = digest.words[i];
    for (size_t j = 0; j < 4; j++) {
      uint8_t byte = word >> 24;
      r[i * 8 + (3 - j) * 2] = hexdigits[byte >> 4];
      r[i * 8 + (3 - j) * 2 + 1] = hexdigits[byte & 0xf];
      word <<= 8;
    }
  }
  return r;
}

// StreamType could be a std stream or a LLVM stream.
template <typename StreamType> inline StreamType& operator<<(StreamType& os, const Digest& x) {
  os << hexDigest(x);
  return os;
}

} // namespace risc0
