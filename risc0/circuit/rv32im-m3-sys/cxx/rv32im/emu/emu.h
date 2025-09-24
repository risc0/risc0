// Copyright 2025 RISC Zero, Inc.
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

#include "rv32im/emu/trace.h"
#include "rv32im/emu/image.h"

namespace risc0::rv32im {

class HostIO {
public:
  // Guest is writing to host, host can return any number <= size
  virtual uint32_t onWrite(uint32_t fd, const uint8_t* data, uint32_t size) = 0;
  // Guest is reading from host, host should fill data with up to size
  // bytes and turn actual amount read.
  virtual uint32_t onRead(uint32_t fd, uint8_t* data, uint32_t size) = 0;
};

// Always returns 0
class NullHostIO : public HostIO {
public:
  uint32_t onWrite(uint32_t fd, const uint8_t* data, uint32_t size) override { return 0; }
  uint32_t onRead(uint32_t fd, uint8_t* data, uint32_t size) override { return 0; }
};

bool emulate(Trace& trace, MemoryImage& image, HostIO& io, size_t count);

}  // namespace risc0::rv32im
