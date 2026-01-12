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

#include <stdlib.h>
#include <cstdint>

volatile uint32_t* data = reinterpret_cast<volatile uint32_t*>(0xb0000000);

void check(bool x) {
  if (!x) { exit(1); }
}

int main() {
  // Make sure data is initially 0
  check(data[0] == 0);
  check(data[1] == 0);
  // Do something an unaligned read and make sure we hit a fault
  // Note: I tried to use volative memory accesses, but the compiler is very
  // clever and often notes alignment issues, etc, so asm is just more 
  // straightforward
  asm volatile(
      "li t3, 0xb0000002\n"
      "lw t3, 0(t3)\n"
      : : : "t3");
  check(data[0] == 2);
  check(data[1] == 1);
  // Same but with a write
  asm volatile(
      "li t3, 0xb0000002\n"
      "sw t3, 0(t3)\n"
      : : : "t3");
  check(data[0] == 2);
  check(data[1] == 2);
  // Try to read kernel memory
  asm volatile(
      "li t3, 0xc0000000\n"
      "lw t3, 0(t3)\n"
      : : : "t3");
  check(data[0] == 2);
  check(data[1] == 3);
  // Try to write kernel memory
  asm volatile(
      "li t3, 0xc0000000\n"
      "sw t3, 0(t3)\n"
      : : : "t3");
  check(data[0] == 2);
  check(data[1] == 4);
  // Do an illegal instruction
  asm volatile("unimp\n" :::);
  check(data[0] == 2);
  check(data[1] == 5);
  // Do an mret instruction not in machine mode
  asm volatile("mret\n" :::);
  check(data[0] == 2);
  check(data[1] == 6);
  // Make sure ebreak is not processed as an ecall
  asm volatile("ebreak\n" :::);
  check(data[0] == 2);
  check(data[1] == 7);
  // DO nothing
}
