// Copyright 2022 RISC Zero, Inc.
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

#include <cstdint>
#include <stdexcept>
#include <windows.h>

#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#endif

uint32_t get_random_u32() {
  uint32_t tmp;
  NTSTATUS status = BCryptGenRandom(
      nullptr, reinterpret_cast<PUCHAR>(&tmp), sizeof(tmp), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
  if (status != STATUS_SUCCESS) {
    throw std::runtime_error("Unable to read from RNG device");
  }
  return tmp;
}
