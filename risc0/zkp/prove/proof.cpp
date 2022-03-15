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

#include "risc0/zkp/prove/proof.h"

#include "risc0/core/log.h"
#include "risc0/zkp/core/sha256_cpu.h"
#include "risc0/zkp/prove/code_id.h"
#include "risc0/zkp/prove/prove.h"
#include "risc0/zkp/verify/verify.h"

#include <sstream>

namespace risc0 {

void Proof::verify(const std::string& filename) const {
  CodeID code;
  LOG(1, "Reading code id from " << filename + ".id");
  code = readCodeID(filename + ".id");
  risc0::verify(code, core.data(), core.size());
  if (message.size() != core[8]) {
    std::stringstream ss;
    ss << "Proof::verify> Message size (" << message.size() << ") does not match proof core ("
       << core[8] << ")";
    throw std::runtime_error(ss.str());
  }
  if (message.size() > 32) {
    ShaDigest digest = shaHash(message.data(), message.size());
    if (memcmp(&digest, core.data(), sizeof(ShaDigest)) != 0) {
      throw std::runtime_error("Proof message/core root mismatch");
    }
  } else {
    if (memcmp(message.data(), core.data(), message.size()) != 0) {
      throw std::runtime_error("Proof message/core root mismatch");
    }
  }
}

struct Prover::Impl : public IoHandler {
  Impl(const std::string& elfPath) : elfPath(elfPath), idxInput(0) {}

  virtual ~Impl() {}

  const void* onRead(size_t size) override {
    LOG(1, "IoHandler::onRead> " << size);
    if (idxInput == inputs.size()) {
      throw std::runtime_error("onRead: Attempting to read too many inputs");
    }
    const auto& buf = inputs.at(idxInput++);
    if (size != buf.size()) {
      std::stringstream ss;
      ss << "Prover::onRead> Size mismatch: expected (" << size << ") != actual (" << buf.size()
         << ")";
      throw std::runtime_error(ss.str());
    }
    return buf.data();
  }

  void onWrite(const Buffer& buf) override {
    LOG(1, "IoHandler::onWrite> " << buf.size());
    outputs.emplace_back(buf);
  }

  KeyStore& getKeyStore() override { return keyStore; }

  std::string elfPath;
  size_t idxInput;
  KeyStore keyStore;
  std::vector<Buffer> inputs;
  std::vector<Buffer> outputs;
};

Prover::Prover(const std::string& elfPath) : impl(new Impl(elfPath)) {}

Prover::~Prover() {}

KeyStore& Prover::getKeyStore() {
  return impl->getKeyStore();
}

void Prover::addInput(const void* ptr, size_t size) {
  const uint8_t* ptrU8 = static_cast<const uint8_t*>(ptr);
  impl->inputs.emplace_back(ptrU8, ptrU8 + size);
  LOG(1, "Adding input, size = " << size);
}

size_t Prover::getNumOutputs() {
  return impl->outputs.size();
}

const void* Prover::getOutput(size_t idx, size_t size) {
  const auto& buf = impl->outputs.at(idx);
  if (size != buf.size())
    throw std::runtime_error("getOutput: Size mismatch");
  return buf.data();
}

Proof Prover::run() {
  // Set the memory handlers to call back to the impl
  MemoryHandler handler(impl.get());
  // Generate the actual proof
  BufferU32 core = prove(impl->elfPath.c_str(), handler);
  // Attach the full version of the output message + construct proof object
  Buffer message = impl->outputs.at(getNumOutputs() - 1);
  Proof proof{core, message};
  // Verify proof to make sure it works
  proof.verify(impl->elfPath);
  return proof;
}

} // namespace risc0
