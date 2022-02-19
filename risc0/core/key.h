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
  uint32_t data[4];
};

using KeyStore = std::map<std::string, Key>;

} // namespace risc0
