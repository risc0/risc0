/// @file sha.h
/// @brief Cryptographic hashing - SHA256

#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "risc0/r0vm/cpp/device/key.h"

namespace risc0 {

class Env;
class PRNG;

/// A structure representing a SHA256 digest.
struct Digest {
  /// @private
  uint32_t words[8];
};

/// @brief Implementation of the SHA256 cryptographic hashing function.
class SHA256 {
  friend class Env;
  friend class PRNG;

public:
  /// Allocate a sha computation buffer. Because the SHA acceleration mechanism checks values at the
  /// end of execution, data to sha must be copied into an intermediate buffer and retained.
  /// `reserve` allows the specification of the expected size of total data to avoid reallocation
  /// and copying.
  SHA256(size_t reserve = 0);

  /// Same as above, but make the digest be a MAC keyed on the key.
  SHA256(KeyPtr key, size_t reserve = 0);

  /// Add more data to SHA
  void update(const void* data, size_t len);

  /// Templated helper for PODs
  template <typename T> void update(const T& data) { update(&data, sizeof(T)); }

  /// Compute the digest of all the data added.
  /// Return a pointer to digest whose value will survive the destruction of this object
  DigestPtr finalize();

private:
  // Private mechanism to 'tweak' the key so we can resue the MAC method on the same
  // key for multiple purposes without causing coliding macs (i.e. use in PRNG, etc).
  void tweak(uint32_t value);

private:
  KeyPtr key;
  uint32_t tweakVal;
  std::vector<uint8_t> storage;
};

/// Helper function for one shot SHA256
inline DigestPtr shaDigest(const void* data, size_t len) {
  SHA256 sha(len);
  sha.update(data, len);
  return sha.finalize();
}

/// Templated helper for one shot digest of PODs
template <typename T> DigestPtr shaDigest(const T& data) {
  return shaDigest(&data, sizeof(T));
}

/// Helper function for one shot MACs
inline DigestPtr shaMAC(KeyPtr key, const void* data, size_t len) {
  SHA256 sha(key, len);
  sha.update(data, len);
  return sha.finalize();
}

/// Templated helper for one shot MAC of PODs
template <typename T> DigestPtr shaMAC(KeyPtr key, const T& data) {
  return shaMAC(key, &data, sizeof(T));
}

/// Special version for Merkle tree or other uses: Combine two digests into one with
/// no padding.
DigestPtr shaCombine(DigestPtr a, DigestPtr b);

} // namespace risc0
