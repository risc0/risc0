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

namespace risc0 {

// These must match the values in zkvm/sdk/rust/platform/src/io.rs
constexpr size_t kGPIO_SHA = 0x01F00000;
constexpr size_t kGPIO_Commit = 0x01F00004;
constexpr size_t kGPIO_Fault = 0x01F00008;
constexpr size_t kGPIO_Log = 0x01F0000C;
constexpr size_t kGPIO_GetKey = 0x01F00010;

constexpr size_t kGPIO_SendRecvChannel = 0x01F00014;
constexpr size_t kGPIO_SendRecvSize = 0x01F00018;
constexpr size_t kGPIO_SendRecvAddr = 0x01F0001C;

// Standard ZKVM channels; must match zkvm/sdk/rust/platform/src/io.rs.

// Request the initial input to the guest.
constexpr uint32_t kSendRecvChannel_InitialInput = 0;
// Write bytes to standard output
constexpr uint32_t kSendRecvChannel_Stdout = 1;
// Write bytes to standard error
constexpr uint32_t kSendRecvChannel_Stderr = 2;

// To invoke accelerated SHA, the guest writes ShaDescriptor structs
// in sequence to the "SHA" memory region.  Once the ShaDescriptor has
// been written, it writes a pointer to the written ShaDescriptor
// structure to kGPIO_SHA.
//
// The guest writes a single "0" word (in what would be the
// "typeAndCount" field of the next ShaDescriptor structure) after all
// the ShaDescriptor structures in the SHA region before exiting.
//
// Upon exit, the guest's ZKP Sha implementation looks through the
// ShaDescriptor space and verifies all SHAs that were computed during
// the run.  Due to this, any memory regions that have been used to
// calculate a SHA must not be modified after the SHA has been
// computed.
struct ShaDescriptor {
  // Number of 64-byte chunks of SHA data to process
  uint32_t typeAndCount;

  // Per jbruestle, this for future use with merkle paths.
  uint32_t idx;

  // Address of first byte of SHA data to process
  uint32_t source;

  // Output address to write SHA digest to; this memory must be uninitialized, and must not be
  // modified afterwards.
  uint32_t digest;
};

inline volatile ShaDescriptor* volatile* GPIO_SHA() {
  return reinterpret_cast<volatile ShaDescriptor* volatile*>(kGPIO_SHA);
}

// To commit to output data, the guest fills in IoDescriptor structure
// with the size and address of the buffer to write, and then writes
// its address to kGPIO_Commit.

struct IoDescriptor {
  uint32_t size;
  uint32_t addr;
};

inline volatile IoDescriptor* volatile* GPIO_Commit() {
  return reinterpret_cast<volatile IoDescriptor* volatile*>(kGPIO_Commit);
}

// To execute general IO, the guest first ensures GPIO_SendRecvChannel
// is filled with the application-defined channel number and GPIO_SendRecvSize
// with the number of bytes in the message.
//
// The guest then writes the address of the first byte of the message to
// sned to GPIO_SendRecvAddr; when this write is performed, the host
// passes the given message to the host application layer.
//
// Once the application layer has completed processing the given message,
// it supplies a sequence of bytes as a reply (which may be length 0).
//
// The host will then write this result into the guest's Input memory
// region as a word indicating the numbre of bytes in the reply,
// followed by the contents of the reply padded to the next word.
//
inline uint32_t volatile* GPIO_SendRecvChannel() {
  return reinterpret_cast<uint32_t volatile*>(kGPIO_SendRecvChannel);
}

inline uint32_t volatile* GPIO_SendRecvSize() {
  return reinterpret_cast<uint32_t volatile*>(kGPIO_SendRecvSize);
}

inline const void* volatile* GPIO_SendRecvAddr() {
  return reinterpret_cast<const void* volatile*>(kGPIO_SendRecvAddr);
}

// To raise a fatal error, the guest writes the address of a
// null-terminated string describing the fatal error to GPIO_Fault.
inline const char* volatile* GPIO_Fault() {
  return reinterpret_cast<const char* volatile*>(kGPIO_Fault);
}

// To log an informative message, the guest writes the address of
// a null-terminated string containing the log message to GPIO_Log.
inline const char* volatile* GPIO_Log() {
  return reinterpret_cast<const char* volatile*>(kGPIO_Log);
}

// TODO(nils) Document GetKey.
struct GetKeyDescriptor {
  uint32_t name;
  uint32_t addr;
  uint32_t mode;
};

inline volatile GetKeyDescriptor* volatile* GPIO_GetKey() {
  return reinterpret_cast<volatile GetKeyDescriptor* volatile*>(kGPIO_GetKey);
}

} // namespace risc0
