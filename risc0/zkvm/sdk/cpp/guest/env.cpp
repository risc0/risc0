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

#include "risc0/zkvm/sdk/cpp/guest/risc0.h"

#include "risc0/zkvm/platform/io.h"
#include "risc0/zkvm/platform/memory.h"

namespace risc0 {

void _risc0_main(uint32_t* result) {
  Env env(result);
  risc0_main(&env);
}

// Extern references to the internal initialization + finalization of the SHA accelerator
extern void initializeSHA256();
extern void finalizeSHA256();

Env::Env(uint32_t* result)
    : message(256 * 1024)
    , result(result)
    , read_ptr(GPIO_InputBase())
    , write_ptr(GPIO_OutputBase())
    , commit_ptr(GPIO_CommitBase()) {
  initializeSHA256();
}

Env::~Env() {
  const uint8_t* data = message.storage.data();
  const size_t len = message.storage.size();
  // Write the full data out to the host
  // write(data, len);
  volatile IoDescriptor io{len, reinterpret_cast<uint32_t>(data)};
  *GPIO_Commit() = &io;
  // If the total proof message is small (<= 32 bytes), return it directly from the proof,
  // otherwise sha it and return the hash.
  if (len <= 32) {
    memcpy(result, data, len);
  } else {
    DigestPtr digest = message.finalize();
    memcpy(result, digest, sizeof(Digest));
  }
  result[8] = len;
  finalizeSHA256();
}

std::pair<void* /* address */, size_t /* length */>
Env::sendRecv(uint32_t channel, const void* addr, size_t len) {
  // Send
  *GPIO_SendRecvChannel() = channel;
  *GPIO_SendRecvSize() = len;
  *GPIO_SendRecvAddr() = addr;

  // Receive
  uint32_t response_len = *read_ptr;
  ++read_ptr;
  void* response_addr = reinterpret_cast<void*>(read_ptr);
  read_ptr += align(response_len) / sizeof(uint32_t);
  return std::make_pair(response_addr, response_len);
}

void Env::write(const void* data, size_t size) {
  sendRecv(kSendRecvChannel_Stdout, data, size);
}

void Env::commit(const void* data, size_t size) {
  write(data, size);
  message.update(data, size);
}

KeyPtr Env::getKey(const char* name, KeyMode mode) {
  // Do malloc to avoid initialization
  KeyPtr ret = reinterpret_cast<Key*>(malloc(sizeof(Key)));
  volatile GetKeyDescriptor getKey{reinterpret_cast<uint32_t>(name),
                                   reinterpret_cast<uint32_t>(ret),
                                   static_cast<uint32_t>(mode)};
  *GPIO_GetKey() = &getKey;
  return ret;
}

void Env::print(const char* msg) {
  *GPIO_Log() = msg;
}

void Env::fetchInitialInput() {
  if (initial_input) {
    // Already fetched.
    return;
  }
  const uint32_t* addr =
      reinterpret_cast<const uint32_t*>(sendRecv(kSendRecvChannel_InitialInput, 0, 0).first);
  initial_input = new Reader(addr);
}

const void* Env::read(size_t size) {
  fetchInitialInput();

  return initial_input->read(size);
}

const void* Reader::read(size_t size) {
  const void* start = read_ptr;
  read_ptr += align(size) / sizeof(uint32_t);
  return start;
}

} // namespace risc0

extern void* __bss_begin;
extern size_t __bss_size;

extern "C" void __start(uint32_t* result) {
  memset(__bss_begin, 0, __bss_size);
  risc0::_risc0_main(result);
}
