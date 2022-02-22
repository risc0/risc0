#pragma once

#include "risc0/core/key.h"
#include "risc0/zkp/core/sha256.h"
#include "risc0/zkp/prove/step/step.h"
#include "risc0/zkp/verify/code_id.h"

#include <memory>
#include <vector>

namespace risc0 {

struct Proof {
  BufferU32 core;
  Buffer message;

  // Verify proof based on elf file
  void verify(const std::string& filename) const;
};

class Prover {
public:
  Prover(const std::string& elfPath);
  ~Prover();

  // Allows access to key store to get/set keys
  KeyStore& getKeyStore();

  void addInput(const void* ptr, size_t size);
  template <typename T> void addInput(const T& obj) { return addInput(&obj, sizeof(T)); }

  size_t getNumOutputs();

  const void* getOutput(size_t idx, size_t size);

  template <typename T> const T& getOutput(size_t idx) {
    return *static_cast<const T*>(getOutput(idx, sizeof(T)));
  }

  Proof run();

private:
  struct Impl;
  std::unique_ptr<Impl> impl;
};

} // namespace risc0
