// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include "core/log.h"
#include "rv32im/test/test_prove.h"

#include <iostream>
#include <string>

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

void runTestBinary(const std::string& kernel, rv32im::HostIO& io, size_t po2) {
  std::map<uint32_t, uint32_t> words;
  rv32im::loadKernel(words, kernel);
  auto image = rv32im::MemoryImage::fromWords(words);
  runTest(image, io, po2);
}

int main() {
  TestIO io;
  runTestBinary("rv32im/test/test_bigint_kernel", io, 13);
  runTestBinary("rv32im/test/test_io_kernel", io, 13);
  if (io.out != "Hello World") {
    throw std::runtime_error("BAD");
  }
  return 0;
}
