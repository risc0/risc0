#pragma once

#include "risc0/zkp/core/sha_rng.h"

#include <vector>

namespace risc0 {

class WriteIOP {
public:
  // Begin a new empty proof
  WriteIOP() = default;
  // Called by the prover to write some data.  This data is not cryptographically verifiable on it's
  // own, but is typically commited via a later hash which includes it.
  void write(const uint32_t* data, size_t count) { proof.insert(proof.end(), data, data + count); }
  // Versions for various other data types
  void write(const Fp* data, size_t count) {
    write(reinterpret_cast<const uint32_t*>(data), count);
  }
  void write(const Fp4* data, size_t count) {
    write(reinterpret_cast<const uint32_t*>(data), count * 4);
  }
  void write(const ShaDigest* data, size_t count) {
    write(reinterpret_cast<const uint32_t*>(data), count * sizeof(ShaDigest) / sizeof(uint32_t));
  }
  // Called by the prover to commit to some hash (usually data written earlier or a Merkle root)
  void commit(const ShaDigest& message) { rng.mix(message); }
  // Called to get a psudorandom challenge value. Since the PRNG is cyptogrpahially strong, and
  // since the source data for the PRNG includes all values commited to earlier, it is
  // computationally infeasble for the prover to control this value, and by the random oracle model
  // can be viewed as effectively equivilent to random data.
  uint32_t generate() { return rng.generate(); }
  // Get the final proof at the end of the protocol
  std::vector<uint32_t> getProof() const { return proof; }

private:
  // The proof being generated
  std::vector<uint32_t> proof;
  // The cryptographic mixer
  ShaRng rng;
};

} // namespace risc0
