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

#include "risc0/r0vm/cpp/device/key.h"
#include "risc0/r0vm/cpp/device/sha.h"

namespace risc0 {

/// @brief The Environment provides access to host I/O.
/// @headerfile "risc0/r0vm/cpp/device/env.h"
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
  /// @tparam T The type to cast the resulting buffer to.
  /// @return A constant reference of type @c T.
  template <typename T> const T& read() { return *reinterpret_cast<const T*>(read(sizeof(T))); }

  /// @brief Writes data to the host.
  ///
  /// @param data A buffer containing data to send to the host.
  /// @param size The size of the buffer, in bytes.
  void write(const void* data, size_t size);

  /// @brief Writes data to the host.
  ///
  /// @tparam T
  /// @param obj
  template <typename T> void write(const T& obj) { write(&obj, sizeof(T)); }

  /// @brief Writes data to the host.
  ///
  /// @tparam T
  /// @param obj
  template <typename T> void write(const T* obj) { write(obj, sizeof(T)); }

  /// @brief Writes a buffer to the official proof output.
  ///
  /// @param data
  /// @param size
  void commit(const void* data, size_t size);

  /// @brief Writes an object to the official proof output.
  ///
  /// @tparam T
  /// @param obj
  template <typename T> void commit(const T& obj) { commit(&obj, sizeof(T)); }

  /// @brief Writes an object to the official proof output.
  ///
  /// @tparam T
  /// @param obj
  template <typename T> void commit(const T* obj) { commit(obj, sizeof(T)); }

  /// @brief Gets/creates a key in the host key store.
  ///
  /// @param name
  /// @param mode
  KeyPtr getKey(const char* name, KeyMode mode);

private:
  friend void _risc0_main(uint32_t* result);

  Env(uint32_t* result);
  ~Env();

private:
  SHA256 message;
  uint32_t* result;
  uint32_t commits;
};

/// @private
void _risc0_main(uint32_t* result);

} // namespace risc0

/// The main entrypoint to the proof program.
///
/// @param env
extern "C" void risc0_main(risc0::Env* env);
