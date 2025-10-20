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
  uint32_t val = 0;
  uint32_t onRead(uint32_t fd, uint8_t* buf, uint32_t len) override {
    if (len != 4) {
      throw std::runtime_error("Expecting a read of a single word");
    }
    // Set buf to 5
    reinterpret_cast<uint32_t*>(buf)[0] = 5;
    return 4;
  };
  uint32_t onWrite(uint32_t fd, const uint8_t* buf, uint32_t len) override {
    if (len != 4) {
      throw std::runtime_error("Expecting a write of a single word");
    }
    val = reinterpret_cast<const uint32_t*>(buf)[0];
    return len;
  }
};

int main() {
  TestIO io;
  runTestBinary("rv32im/test/linux_kernel", "rv32im/test/linux_guest", io, 13);
  if (io.val != 100) {
    throw std::runtime_error("Write of val didn't produce correct output");
  }
  return 0;
}
