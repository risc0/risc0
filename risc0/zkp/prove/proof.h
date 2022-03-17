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

#include "risc0/core/archive.h"
#include "risc0/core/key.h"
#include "risc0/zkp/core/sha256.h"
#include "risc0/zkp/prove/step/step.h"
#include "risc0/zkp/verify/code_id.h"

#include <memory>
#include <vector>

namespace risc0 {

class CheckedStreamReader {
public:
  CheckedStreamReader(const Buffer& buffer);

  uint32_t read_word();
  uint64_t read_dword();
  void read_buffer(void* buf, size_t len);

private:
  uint8_t read_byte();

private:
  const Buffer& buffer;
  size_t cursor;
};

class Prover;

struct Proof {
  friend class Prover;

public:
  BufferU32 core;

public:
  // Verify proof based on elf file
  void verify(const std::string& filename) const;

  template <typename T> T read() const {
    T obj;
    getReader().transfer(obj);
    return obj;
  }

  const Buffer& getMessage() const;

private:
  Proof(const BufferU32& core, const Buffer& message);
  ArchiveReader<CheckedStreamReader>& getReader() const;

private:
  struct Impl;
  std::shared_ptr<Impl> impl;
};

class Prover {
public:
  Prover(const std::string& elfPath);
  ~Prover();

  // Allows access to key store to get/set keys
  KeyStore& getKeyStore();

  void writeInput(const void* ptr, size_t size);

  template <typename T> void writeInput(const T& obj) { getInputWriter().transfer(obj); }

  const Buffer& getOutput();

  const Buffer& getCommit();

  template <typename T> T readOutput() {
    T obj;
    getOutputReader().transfer(obj);
    return obj;
  }

  template <typename T> T readCommit() {
    T obj;
    getCommitReader().transfer(obj);
    return obj;
  }

  Proof run();

private:
  ArchiveWriter<VectorStreamWriter>& getInputWriter();
  ArchiveReader<CheckedStreamReader>& getOutputReader();
  ArchiveReader<CheckedStreamReader>& getCommitReader();

private:
  struct Impl;
  std::unique_ptr<Impl> impl;
};

} // namespace risc0
