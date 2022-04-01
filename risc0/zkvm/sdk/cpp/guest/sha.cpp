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

static size_t computePaddedSize(size_t len) {
  // Computed padded size for data of size 'len' which is equal to:
  // len + 1 (terminating byte) + sizeof(uint64_t) rounded up to nearest multiple of 64.
  // To round to nearest 64, we add 63 and then mask away the low 6 bits.
  return (len + 1 + sizeof(uint64_t) + 63) & 0xffffffc0;
}

static volatile ShaDescriptor* curDescriptor;

static DigestPtr compress(const void* data, size_t total) {
  // Now, we need to allocate a new output digest to compute into
  Digest* digest = new Digest;
  // Set up the next descriptor
  curDescriptor->typeAndCount = total / 64;
  curDescriptor->idx = 0;
  curDescriptor->source = reinterpret_cast<uint32_t>(data);
  curDescriptor->digest = reinterpret_cast<uint32_t>(digest);
  // Write the descriptor to the oracle for processing
  *GPIO_SHA() = curDescriptor;
  // Jump to the next descriptor;
  curDescriptor++;
  // Return the result
  return digest;
}

SHA256::SHA256(size_t reserve) : key(nullptr) {
  storage.reserve(computePaddedSize(reserve));
}

SHA256::SHA256(KeyPtr key, size_t reserve) : key(key), tweakVal(0) {
  // We follow the basic protocol described in:
  // “Sandwich” Is Indeed Secure: How to Authenticate a Message with Just One Hashing
  // Yasuda, K. (n.d.).
  // Lecture Notes in Computer Science, 355–369. doi:10.1007/978-3-540-73458-1_26
  //
  // This paper describes a more efficient method than that of RFC 2841 which
  // still has proper security proofs.
  //
  // At a high level, we hash (and pad):
  // K || 0^p || M || 1 || 0^n || K
  // where p = 512 - |K| and n = 512 − (|M| mod 512) − 1
  //
  // Basically, the idea is that we 0 pad K to make it fill a full block, and
  // then we pad the message so that it also fill a full block, and finally add
  // the key + normal padding in the last block.

  // We need to reserved 2 full blocks (initial key, finally key) + room for
  // message + 1 byte (0x80)
  storage.reserve(3 * 64 + reserve / 64);
  // We write the initial block
  storage.resize(64);
  uint32_t* dataPtr = reinterpret_cast<uint32_t*>(storage.data());
  for (size_t i = 0; i < 4; i++) {
    dataPtr[i] = key->data[i];
  }
  for (size_t i = 4; i < 16; i++) {
    dataPtr[i] = 0;
  }
}

void SHA256::update(const void* data, size_t len) {
  const uint8_t* dataPtr = static_cast<const uint8_t*>(data);
  storage.insert(storage.end(), dataPtr, dataPtr + len);
}

DigestPtr SHA256::finalize() {
  if (key) {
    // Get current storage size
    size_t curSize = storage.size();
    // Resize up to the next block size that has room for 1 more byte
    storage.resize(64 * ((curSize / 64) + 1));
    // Add the one bit on the end of the message.
    // 0 padding is done by resize
    storage[curSize] = 0x80;
    // Append key + tweak
    update(*key);
    update(tweakVal);
  }
  size_t len = storage.size();
  size_t total = computePaddedSize(len);
  // Resize to padded len.
  storage.resize(total);
  // Get a local copy of the buffer pointer
  uint8_t* data = storage.data();
  // Add terminating byte
  data[len] = 0x80;
  // Memset all but last 4 bytes to zeros (we only support len < 2^32)
  memset(data + len + 1, 0, total - len - 5);
  // Write size in bits as little endian
  size_t bits = len * 8;
  uint32_t* trailer = reinterpret_cast<uint32_t*>(data + total - sizeof(uint32_t));
  *trailer = ((bits & 0xff000000U) >> 24) | //
             ((bits & 0x00ff0000U) >> 8) |  //
             ((bits & 0x0000ff00U) << 8) |  //
             ((bits & 0x000000ffU) << 24);
  return compress(data, total);
}

void SHA256::tweak(uint32_t value) {
  // Set the word immediately after key to the tweak value
  reinterpret_cast<uint32_t*>(storage.data())[4] = value;
  tweakVal = value;
}

DigestPtr shaCombine(DigestPtr a, DigestPtr b) {
  Digest* both = new Digest[2];
  both[0] = *a;
  both[1] = *b;
  return compress(both, 64);
}

void initializeSHA256() {
  curDescriptor = reinterpret_cast<volatile ShaDescriptor*>(kMemSHAStart);
}

void finalizeSHA256() {
  curDescriptor->typeAndCount = 0;
}

} // namespace risc0
