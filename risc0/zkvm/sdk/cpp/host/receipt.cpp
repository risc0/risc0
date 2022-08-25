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

#include "risc0/zkvm/sdk/cpp/host/receipt.h"

#include "risc0/core/elf.h"
#include "risc0/core/log.h"
#include "risc0/zkp/core/sha256_cpu.h"
#include "risc0/zkp/prove/prove.h"
#include "risc0/zkp/verify/verify.h"
#include "risc0/zkvm/platform/io.h"
#include "risc0/zkvm/prove/riscv.h"
#include "risc0/zkvm/verify/riscv.h"

#include <fstream>
#include <sstream>
#include <vector>

namespace risc0 {

void Receipt::verify(const MethodId& methodId) const {
  if (methodId.empty()) {
    throw std::runtime_error("Missing method ID");
  }
  if (seal.empty()) {
    throw std::runtime_error("Seal missing or too small");
  }
  std::unique_ptr<VerifyCircuit> circuit = getRiscVVerifyCircuit(methodId);
  risc0::verify(*circuit, seal.data(), seal.size());
  if (journal.size() != seal[8]) {
    std::stringstream ss;
    ss << "Receipt::verify> journal size (" << journal.size() << ") does not match receipt seal ("
       << seal[8] << ")";
    throw std::runtime_error(ss.str());
  }
  if (journal.size() > 32) {
    ShaDigest digest = shaHash(journal.data(), journal.size());
    if (memcmp(&digest, seal.data(), sizeof(ShaDigest)) != 0) {
      throw std::runtime_error("Receipt journal/seal root mismatch");
    }
  } else {
    if (memcmp(journal.data(), seal.data(), journal.size()) != 0) {
      throw std::runtime_error("Receipt journal/seal root mismatch");
    }
  }
}

struct Prover::Impl : public IoHandler {
  Impl(std::vector<uint8_t> elfContents, const MethodId& methodId)
      : elfContents(elfContents)
      , methodId(methodId)
      , outputStream(outputBuffer)
      , commitStream(commitBuffer)
      , inputWriter(inputStream)
      , inputWriterAux(inputStreamAux)
      , outputReader(outputStream)
      , commitReader(commitStream) {
    // Set default handlers:
    setSendRecvHandler(kSendRecvChannel_Stdout, [this](uint32_t, const BufferU8& buf) -> BufferU8 {
      LOG(1, "IoHandler::Stdout> " << buf.size());
      outputBuffer.insert(outputBuffer.end(), buf.begin(), buf.end());
      return BufferU8();
    });
    setSendRecvHandler(kSendRecvChannel_Stderr, [](uint32_t, const BufferU8& buf) -> BufferU8 {
      LOG(1, "IoHandler::Stderr> " << buf.size());
      fwrite(buf.data(), buf.size(), 1, stderr);
      return BufferU8();
    });
    setSendRecvHandler(
        kSendRecvChannel_InitialInput, [this](uint32_t, const BufferU8& buf) -> BufferU8 {
          const uint8_t* byte_ptr = reinterpret_cast<const uint8_t*>(inputStream.vec.data());
          BufferU8 input(byte_ptr, byte_ptr + inputStream.vec.size() * sizeof(uint32_t));
          LOG(1, "IoHandler::InitialInput, " << input.size() << " bytes");
          return input;
        });
    setSendRecvHandler(
        kSendRecvChannel_InitialInputAux, [this](uint32_t, const BufferU8& buf) -> BufferU8 {
          const uint8_t* byte_ptr = reinterpret_cast<const uint8_t*>(inputStreamAux.vec.data());
          BufferU8 input(byte_ptr, byte_ptr + inputStreamAux.vec.size() * sizeof(uint32_t));
          LOG(1, "IoHandler::InitialInputAux, " << input.size() << " bytes");
          return input;
        });
  }

  virtual ~Impl() {}

  void onInit(MemoryState& mem) override { LOG(1, "Prover::onInit>"); }

  void setSendRecvHandler(
      uint32_t channelId,
      const std::function<BufferU8(uint32_t /* channelId*/, const BufferU8&)>& handler) {
    sendRecvHandlers.insert(std::make_pair(channelId, handler));
  }

  BufferU8 onSendRecv(uint32_t channel, const BufferU8& buf) override {
    auto it = sendRecvHandlers.find(channel);
    if (it == sendRecvHandlers.end()) {
      throw(std::runtime_error("Unknown channel " + std::to_string(channel)));
    }
    return it->second(channel, buf);
  }

  void onCommit(const BufferU8& buf) override {
    LOG(1, "IoHandler::onCommit> " << buf.size());
    commitBuffer.insert(commitBuffer.end(), buf.begin(), buf.end());
  }

  KeyStore& getKeyStore() override { return keyStore; }

  std::vector<uint8_t> elfContents;
  MethodId methodId;
  KeyStore keyStore;
  BufferU8 outputBuffer;
  BufferU8 commitBuffer;
  VectorStreamWriter inputStream;
  VectorStreamWriter inputStreamAux;
  CheckedStreamReader outputStream;
  CheckedStreamReader commitStream;
  ArchiveWriter<VectorStreamWriter> inputWriter;
  ArchiveWriter<VectorStreamWriter> inputWriterAux;
  ArchiveReader<CheckedStreamReader> outputReader;
  ArchiveReader<CheckedStreamReader> commitReader;

  std::map<uint32_t /* channel id */,
           std::function<BufferU8(uint32_t /* channelId*/, const BufferU8&)> /* handler */>
      sendRecvHandlers;
};

CheckedStreamReader::CheckedStreamReader(const BufferU8& buffer) : buffer(buffer), cursor(0) {}

uint32_t CheckedStreamReader::read_word() {
  if (cursor + sizeof(uint32_t) > buffer.size()) {
    throw(std::out_of_range("Read out of bounds"));
  }
  uint32_t b1 = buffer[cursor++];
  uint32_t b2 = buffer[cursor++];
  uint32_t b3 = buffer[cursor++];
  uint32_t b4 = buffer[cursor++];
  return b1 | b2 << 8 | b3 << 16 | b4 << 24;
}

uint64_t CheckedStreamReader::read_dword() {
  uint64_t low = read_word();
  uint64_t high = read_word();
  return low | high << 32;
}

void CheckedStreamReader::read_buffer(void* buf, size_t len) {
  size_t end_cursor = align(cursor + len);
  if (end_cursor > buffer.size()) {
    throw(std::out_of_range("Read out of bounds"));
  }
  memcpy(buf, buffer.data(), len);
  cursor = end_cursor;
}

Prover::Prover(const uint8_t* bytes, size_t len, const MethodId& methodId)
    : Prover(std::vector<uint8_t>(bytes, bytes + len), methodId) {}

Prover::Prover(std::vector<uint8_t> elfContents, const MethodId& methodId)
    : impl(new Impl(std::move(elfContents), methodId)) {}

Prover::Prover(const std::string& elfPath, const MethodId& methodId)
    : Prover(loadFile(elfPath), methodId) {}

Prover::~Prover() = default;

KeyStore& Prover::getKeyStore() {
  return impl->getKeyStore();
}

void Prover::setKey(const std::string& name, const Key& key) {
  impl->getKeyStore()[name] = key;
}

const BufferU8& Prover::getOutput() {
  return impl->outputBuffer;
}

const BufferU8& Prover::getCommit() {
  return impl->commitBuffer;
}

ArchiveWriter<VectorStreamWriter>& Prover::getInputWriter() {
  return impl->inputWriter;
}

ArchiveReader<CheckedStreamReader>& Prover::getOutputReader() {
  return impl->outputReader;
}

ArchiveReader<CheckedStreamReader>& Prover::getCommitReader() {
  return impl->commitReader;
}

void Prover::writeInput(const void* ptr, size_t size) {
  LOG(1, "Prover::writeInput> size: " << size);
  const uint8_t* ptr_u8 = static_cast<const uint8_t*>(ptr);
  while (size >= sizeof(uint32_t)) {
    uint32_t word = 0;
    word |= *ptr_u8++;
    word |= *ptr_u8++ << 8;
    word |= *ptr_u8++ << 16;
    word |= *ptr_u8++ << 24;
    LOG(1, "  write_word: " << hex(word));
    impl->inputStream.write_word(word);
    size -= sizeof(uint32_t);
  }

  if (size) {
    LOG(1, "  tail: " << size);
    uint32_t word = 0;
    for (size_t i = 0; i < size; i++) {
      word |= *ptr_u8++ << (8 * i);
    }
    LOG(1, "  write_word: " << hex(word));
    impl->inputStream.write_word(word);
  }
}

void Prover::writeInputAux(const void* ptr, size_t size) {
  LOG(1, "Prover::writeInputAux> size: " << size);
  const uint8_t* ptr_u8 = static_cast<const uint8_t*>(ptr);
  while (size >= sizeof(uint32_t)) {
    uint32_t word = 0;
    word |= *ptr_u8++;
    word |= *ptr_u8++ << 8;
    word |= *ptr_u8++ << 16;
    word |= *ptr_u8++ << 24;
    LOG(1, "  write_word: " << hex(word));
    impl->inputStreamAux.write_word(word);
    size -= sizeof(uint32_t);
  }

  if (size) {
    LOG(1, "  tail: " << size);
    uint32_t word = 0;
    for (size_t i = 0; i < size; i++) {
      word |= *ptr_u8++ << (8 * i);
    }
    LOG(1, "  write_word: " << hex(word));
    impl->inputStreamAux.write_word(word);
  }
}

void Prover::setSendRecvHandler(
    uint32_t channelId,
    const std::function<BufferU8(uint32_t /* channelId*/, const BufferU8&)>& handler) {
  impl->setSendRecvHandler(channelId, handler);
}

Receipt Prover::run() {
  // Set the memory handlers to call back to the impl
  MemoryHandler handler(impl.get());
  // Make the circuit
  std::unique_ptr<ProveCircuit> circuit = getRiscVProveCircuit(impl->elfContents, handler);
  if (skip_seal) {
    risc0::runWithoutSeal(*circuit);
    Receipt receipt{getCommit(), {} /* no seal */};
    return receipt;
  } else {
    BufferU32 seal = prove(*circuit);
    // Attach the full version of the output journal + construct receipt object
    Receipt receipt{getCommit(), seal};
    // Verify receipt to make sure it works
    receipt.verify(impl->methodId);
    return receipt;
  }
}

} // namespace risc0
