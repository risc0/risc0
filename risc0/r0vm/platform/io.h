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

constexpr size_t kGPIO_SHA = 0x001C0000;
constexpr size_t kGPIO_Write = 0x001C0004;
constexpr size_t kGPIO_Commit = 0x001C0008;
constexpr size_t kGPIO_Fault = 0x001C000C;
constexpr size_t kGPIO_Log = 0x001C0010;
constexpr size_t kGPIO_GetKey = 0x001C0014;

struct ShaDescriptor;

struct IoDescriptor {
  uint32_t size;
  uint32_t addr;
};

struct FaultDescriptor {
  uint32_t addr;
};

struct LogDescriptor {
  uint32_t addr;
};

struct GetKeyDescriptor {
  uint32_t name;
  uint32_t addr;
  uint32_t mode;
};

inline volatile ShaDescriptor* volatile* GPIO_SHA() {
  return reinterpret_cast<volatile ShaDescriptor* volatile*>(kGPIO_SHA);
}

inline volatile IoDescriptor* volatile* GPIO_Write() {
  return reinterpret_cast<volatile IoDescriptor* volatile*>(kGPIO_Write);
}

inline volatile IoDescriptor* volatile* GPIO_Commit() {
  return reinterpret_cast<volatile IoDescriptor* volatile*>(kGPIO_Commit);
}

inline volatile FaultDescriptor* volatile* GPIO_Fault() {
  return reinterpret_cast<volatile FaultDescriptor* volatile*>(kGPIO_Fault);
}

inline volatile LogDescriptor* volatile* GPIO_Log() {
  return reinterpret_cast<volatile LogDescriptor* volatile*>(kGPIO_Log);
}

inline volatile GetKeyDescriptor* volatile* GPIO_GetKey() {
  return reinterpret_cast<volatile GetKeyDescriptor* volatile*>(kGPIO_GetKey);
}

} // namespace risc0
