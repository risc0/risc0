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

inline void die() {
  asm("unimp\n");
}

// Implement machine mode ECALLS

inline void terminate(uint32_t val) {
  register uintptr_t a0 asm("a0") = val;
  register uintptr_t a7 asm("a7") = 0;
  asm volatile("ecall\n"
               :                  // no outputs
               : "r"(a0), "r"(a7) // inputs
               :                  // no clobbers
  );
}

constexpr size_t count = 10000000;

extern "C" void start() {
  uint32_t p0 = 1;
  uint32_t p1 = 1;
  for (uint32_t i = 0; i < count; i++) {
    uint32_t tmp = p1;
    p1 = p0 + p1;
    p0 = tmp;
  }
  terminate(p0);
}
