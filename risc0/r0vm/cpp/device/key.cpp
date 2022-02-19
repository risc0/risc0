#include "risc0/r0vm/cpp/device/risc0.h"

namespace risc0 {

Key::Key(const Key& a, const Key& b) {
  for (size_t i = 0; i < 4; i++) {
    data[i] = a.data[i] ^ b.data[i];
  }
}

DigestPtr Key::commit() const {
  return shaDigest(*this);
}

} // namespace risc0
