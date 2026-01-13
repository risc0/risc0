// Copyright 2026 RISC Zero, Inc.
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

#pragma once

#include "rv32im/emu/image.h"
#include "rv32im/emu/trace.h"

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

bool emulate(Trace& trace, MemoryImage& image, HostIO& io, size_t rowCount, uint32_t endCycle);

} // namespace risc0::rv32im
