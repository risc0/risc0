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

#include "risc0/core/rng.h"

#include <map>

namespace risc0 {

struct Key {
  // Generates a new cryptographically random key
  Key() {
    for (size_t i = 0; i < 4; i++) {
      data[i] = CryptoRng::shared().generate();
    }
  }

  bool operator==(const Key& rhs) const {
    for (size_t i = 0; i < 4; i++) {
      if (data[i] != rhs.data[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Key& rhs) { return !(*this == rhs); }

  template <typename Archive> void transfer(Archive& ar) {
    for (uint32_t& word : data) {
      ar.transfer(word);
    }
  }

  uint32_t data[4];
};

using KeyStore = std::map<std::string, Key>;

} // namespace risc0
