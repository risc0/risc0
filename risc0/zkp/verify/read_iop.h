#pragma once

#include "risc0/core/util.h"
#include "risc0/zkp/core/fp4.h"
#include "risc0/zkp/core/sha_rng.h"

#include <vector>

namespace risc0 {

class ReadIOP {
public:
  // Intialize a IOP reader with a proof
  ReadIOP(const uint32_t* proof, size_t size) : proof(proof), size(size) {}
  // Reads 'unverified' data from the proof (typically verified later via a commitment)
  void read(uint32_t* out, size_t readSize) {
    REQUIRE(size >= readSize);
    std::copy(proof, proof + readSize, out);
    proof += readSize;
    size -= readSize;
  }
  void read(Fp* data, size_t count) { read(reinterpret_cast<uint32_t*>(data), count); }
  void read(Fp4* data, size_t count) { read(reinterpret_cast<uint32_t*>(data), count * 4); }
  void read(ShaDigest* data, size_t count) {
    read(reinterpret_cast<uint32_t*>(data), count * sizeof(ShaDigest) / sizeof(uint32_t));
  }
  // Apply a commitment to the RNG state
  void commit(const ShaDigest& message) { rng.mix(message); }
  // Get the psudeorandom challenge at this point in the protocol
  uint32_t generate() { return rng.generate(); }
  // Verify the proof was complete consumed
  void verifyComplete() { REQUIRE(size == 0); }

private:
  const uint32_t* proof;
  size_t size;
  ShaRng rng;
};

} // namespace risc0
