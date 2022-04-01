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

/// @file env.h
/// @brief The Environment class.

#pragma once

#include <cstddef>
#include <cstdint>

#include "risc0/core/archive.h"
#include "risc0/zkvm/sdk/cpp/guest/key.h"
#include "risc0/zkvm/sdk/cpp/guest/sha.h"

namespace risc0 {

/// @brief The Environment provides access to host I/O.
/// @headerfile "risc0/zkvm/sdk/cpp/guest/env.h"
///
/// Details.
///
class Env {
public:
  /// @brief Reads data from the host.
  ///
  /// Returns a pointer to the resulting buffer.
  /// The resulting buffer is word aligned and at least @c size bytes.
  ///
  /// @param size The size of the buffer to read, in bytes.
  /// @return A pointer to the resulting buffer.
  void* read(size_t size);

  /// @brief Reads data from the host.
  ///
  /// @tparam T The type to deserialize data from the host as.
  /// @return An object with type @c T.
  template <typename T> T read() {
    BufferStreamReader stream(read_ptr);
    ArchiveReader reader(stream);
    T obj;
    reader.transfer(obj);
    read_ptr = stream.ptr;
    return obj;
  }

  /// @brief Writes data to the host.
  ///
  /// @param data A buffer containing data to send to the host.
  /// @param size The size of the buffer, in bytes.
  void write(const void* data, size_t size);

  /// @brief Writes data to the host.
  ///
  /// @tparam T The type of object to write to the host.
  /// @param obj The object to serialize and write to the host.
  template <typename T> void write(const T& obj) {
    uint32_t* start = write_ptr;
    BufferStreamWriter stream(write_ptr);
    ArchiveWriter writer(stream);
    writer.transfer(obj);
    size_t size = (stream.ptr - start) * sizeof(uint32_t);
    write(start, size);
    write_ptr = stream.ptr;
  }

  /// @brief Writes data to the host.
  ///
  /// @tparam T The type of object to write to the host.
  /// @param obj The object to serialize and write to the host.
  template <typename T> void write(const T* obj) { write(*obj); }

  /// @brief Writes data to the official proof output.
  ///
  /// @param data
  /// @param size
  void commit(const void* data, size_t size);

  /// @brief Writes data to the official proof output.
  ///
  /// @tparam T The type of object to write to the host.
  /// @param obj The object to serialize and write to the host.
  template <typename T> void commit(const T& obj) {
    uint32_t* start = write_ptr;
    BufferStreamWriter stream(write_ptr);
    ArchiveWriter writer(stream);
    writer.transfer(obj);
    size_t size = (stream.ptr - start) * sizeof(uint32_t);
    commit(start, size);
    write_ptr = stream.ptr;
  }

  /// @brief Writes data to the official proof output.
  ///
  /// @tparam T The type of object to write to the host.
  /// @param obj The object to serialize and write to the host.
  template <typename T> void commit(const T* obj) { commit(*obj); }

  /// @brief Gets or creates a key in from the host keystore.
  ///
  /// @param name
  /// @param mode
  KeyPtr getKey(const char* name, KeyMode mode);

  /// @brief Print a message to the debug console.
  ///
  /// @param msg The message to print.
  void print(const char* msg);

private:
  friend void _risc0_main(uint32_t* result);

  Env(uint32_t* result);
  ~Env();

private:
  SHA256 message;
  uint32_t* result;
  uint32_t* read_ptr;
  uint32_t* write_ptr;
  uint32_t* commit_ptr;
};

/// @private
void _risc0_main(uint32_t* result);

} // namespace risc0

/// The main entrypoint to the proof program.
///
/// @param env
extern "C" void risc0_main(risc0::Env* env);
