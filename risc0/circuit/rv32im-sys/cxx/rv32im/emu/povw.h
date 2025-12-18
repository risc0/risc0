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

#pragma once

#include <cstring>

namespace risc0::rv32im {

struct PovwNonce {
private:
  uint32_t inner_data[8];

public:
  PovwNonce(uint32_t povwNonce[8]) {
      memcpy(&inner_data, povwNonce, sizeof(uint32_t) * 8);
  }
  static PovwNonce zero() {
      uint32_t d[8];
      memset(d, 0, sizeof(d));
      return PovwNonce(d);
  }
  inline const uint32_t* data() const { return inner_data; }

};

} // namespace risc0::rv32im
