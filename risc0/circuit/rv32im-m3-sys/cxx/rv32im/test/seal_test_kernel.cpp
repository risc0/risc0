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

#include <stdint.h>
#include <sys/errno.h>

#include "rv32im/base/constants.h"

inline void terminate(uint32_t val) {
  register uintptr_t a0 asm("a0") = 0;
  register uintptr_t a1 asm("a1") = val;
  register uintptr_t a7 asm("a7") = 0;
  asm volatile("ecall\n"
               :                  // no outputs
               : "r"(a0), "r"(a1), "r"(a7) // inputs
               :                  // no clobbers
  );
}

extern "C" void start() {
  uint32_t* inAddr = reinterpret_cast<uint32_t*>(OUTPUT_ADDR);
  uint32_t* outAddr = reinterpret_cast<uint32_t*>(OUTPUT_ADDR);
  for (size_t i = 0; i < 8; i++) {
    outAddr[i] = inAddr[i] + i;
  }
  terminate(17);
}
