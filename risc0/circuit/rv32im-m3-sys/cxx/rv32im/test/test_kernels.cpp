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

#include "core/log.h"
#include "rv32im/test/test_prove.h"

#include <string>
#include <iostream>

using namespace risc0;

class TestIO : public rv32im::HostIO {
public:
  std::string out;
  uint32_t onRead(uint32_t fd, uint8_t* buf, uint32_t len) override {
    for (size_t i = 0; i < len; i++) {
      buf[i] = i;
    }
    return len;
  };
  uint32_t onWrite(uint32_t fd, const uint8_t* buf, uint32_t len) override {
    out = std::string(reinterpret_cast<const char*>(buf), len);
    return 5;
  }
};

int main() {
  if (const char* level = std::getenv("RISC0_LOG")) {
    risc0::setLogLevel(std::atoi(level));
  }
  TestIO io;
  runTestBinary("rv32im/test/test_bigint_kernel", io, 13);
  runTestBinary("rv32im/test/test_io_kernel", io, 13);
  if (io.out != "Hello World") {
    throw std::runtime_error("BAD");
  }
  return 0;
}
