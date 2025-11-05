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

inline uint32_t hostRead(uint32_t fd, char* buf, uint32_t len) {
  register uintptr_t a0 asm("a0") = fd;
  register uintptr_t a1 asm("a1") = reinterpret_cast<uint32_t>(buf);
  register uintptr_t a2 asm("a2") = len;
  register uintptr_t a7 asm("a7") = 1;
  asm volatile("ecall\n"
               : "+r"(a0)                           // outputs
               : "r"(a0), "r"(a1), "r"(a2), "r"(a7) // inputs
               :                                    // no clobbers
  );
  return a0;
}

inline uint32_t hostWrite(uint32_t fd, const char* buf, uint32_t len) {
  register uintptr_t a0 asm("a0") = fd;
  register uintptr_t a1 asm("a1") = reinterpret_cast<uint32_t>(buf);
  register uintptr_t a2 asm("a2") = len;
  register uintptr_t a7 asm("a7") = 2;
  asm volatile("ecall\n"
               : "+r"(a0)                           // outputs
               : "r"(a0), "r"(a1), "r"(a2), "r"(a7) // inputs
               :                                    // no clobbers
  );
  return a0;
}

inline uint32_t sys_poseidon(uint32_t state, uint32_t bufIn, uint32_t bufOut, uint32_t countAndBits) {
  register uintptr_t a0 asm("a0") = state;
  register uintptr_t a1 asm("a1") = bufIn;
  register uintptr_t a2 asm("a2") = bufOut;
  register uintptr_t a3 asm("a3") = countAndBits;
  register uintptr_t a7 asm("a7") = 3;
  asm volatile("ecall\n"
               :                                             // no outputs
               : "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a7) // inputs
               :                                             // no clobbers
  );
  return 0;
}

#define AT(x) (reinterpret_cast<uint32_t*>(x))
#define CSR(x) AT(CSR_BASE_ADDR)[CSR_ ## x]
#define UREG(x) AT(USER_REGS_ADDR)[REG_ ## x]

// Very primitive logging system
struct LogHelper {
  char* buf;
  LogHelper() {
    buf = reinterpret_cast<char*>(0xf1000000);
  }
  LogHelper& operator<<(const char* str) {
    while(*str) {
      *buf++ = *str++;
    }
    return *this;
  }
  LogHelper& operator<<(uint32_t val) {
    for (size_t i = 8; i-->0; ) {
      *buf++ = "0123456789abcdef"[(val >> (4 * i)) & 0xf];
    }
    return *this;
  }
  char* start() { return reinterpret_cast<char*>(0xf1000000); }
  uint32_t size() { return buf - reinterpret_cast<char*>(0xf1000000); }

};

#define LOG(level, ...) do { \
  LogHelper log; \
  log << __VA_ARGS__; \
  hostWrite(level, log.start(), log.size()); \
} while(0)

#define FATAL(...) do { \
  LOG(0, __VA_ARGS__); \
  die(); \
} while(0)


// Implement system calls


inline uint32_t sys_read(uint32_t fd, uint32_t buf, uint32_t len) {
  if (fd != 0) {
    return -EBADF;
  }
  return hostRead(0, reinterpret_cast<char*>(buf), len);
}

inline uint32_t sys_write(uint32_t fd, uint32_t buf, uint32_t len) {
  return hostWrite(fd, reinterpret_cast<const char*>(buf), len);
}

inline uint32_t sys_exit(uint32_t code) {
  LOG(0, "Exit: code = " << code);
  terminate(code);
  return 0;
}

#define sys1(name) UREG(A0) = sys_ ## name(UREG(A0)); break
#define sys2(name) UREG(A0) = sys_ ## name(UREG(A0), UREG(A1)); break
#define sys3(name) UREG(A0) = sys_ ## name(UREG(A0), UREG(A1), UREG(A2)); break
#define sys4(name) UREG(A0) = sys_ ## name(UREG(A0), UREG(A1), UREG(A2), UREG(A3)); break

extern "C" void onTrap() {
  uint32_t idx = UREG(A7);
  switch(idx) {
    case 3: sys4(poseidon);
    case 0x3f: sys3(read);
    case 0x40: sys3(write);
    case 0x5d: sys1(exit);
    default:
      LOG(0, "Unknown syscall: " << idx);
      die();
  }
}

extern "C" void _trapEntry();

extern "C" void start() {
  hostWrite(0, "Kernel Starting", 15);
  // Set up user stack
  UREG(SP) =  0xbffffffc;
  // Set up syscall dispatch table
  uint32_t* dispatchAddr = reinterpret_cast<uint32_t*>(V2_COMPAT_ECALL_DISPATCH * 4);
  *dispatchAddr = reinterpret_cast<uint32_t>(_trapEntry);
  // Jump into userland
  asm volatile("mret\n" : : :);
}
