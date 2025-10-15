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

inline void mret() {
  asm("mret\n");
}

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

inline uint32_t host_read(uint32_t fd, uint32_t buf, uint32_t len) {
  register uintptr_t a0 asm("a0") = fd;
  register uintptr_t a1 asm("a1") = buf;
  register uintptr_t a2 asm("a2") = len;
  register uintptr_t a7 asm("a7") = 1;
  asm volatile("ecall\n"
               : "+r"(a0)                           // outputs
               : "r"(a0), "r"(a1), "r"(a2), "r"(a7) // inputs
               :                                    // no clobbers
  );
  return a0;
}

inline uint32_t host_write(uint32_t fd, uint32_t buf, uint32_t len) {
  register uintptr_t a0 asm("a0") = fd;
  register uintptr_t a1 asm("a1") = buf;
  register uintptr_t a2 asm("a2") = len;
  register uintptr_t a7 asm("a7") = 2;
  asm volatile("ecall\n"
               : "+r"(a0)                           // outputs
               : "r"(a0), "r"(a1), "r"(a2), "r"(a7) // inputs
               :                                    // no clobbers
  );
  return a0;
}

inline void do_poseidon2(uint32_t state, uint32_t bufIn, uint32_t bufOut, uint32_t countAndBits) {
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
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"

// Helpers to access user registers
inline uint32_t get_ureg(uint32_t reg) {
  return (reinterpret_cast<uint32_t*>(USER_REGS_ADDR))[reg];
}

inline void set_ureg(uint32_t reg, uint32_t val) {
  (reinterpret_cast<uint32_t*>(USER_REGS_ADDR))[reg] = val;
}

#pragma GCC diagnostic pop

// Implement system calls

inline uint32_t sys_exit(uint32_t code) {
  terminate(code);
  return 0;
}

inline uint32_t sys_read(uint32_t fd, uint32_t buf, uint32_t len) {
  if (fd != 0) {
    return -EBADF;
  }
  if (buf + len < buf) {
    return -EINVAL;
  }
  if (buf < USER_START_ADDR || buf + len >= USER_END_ADDR) {
    return -EFAULT;
  }
  return host_read(0, buf, len);
}

inline uint32_t sys_write(uint32_t fd, uint32_t buf, uint32_t len) {
  if (fd != 1) {
    return -EBADF;
  }
  if (buf + len < buf) {
    return -EINVAL;
  }
  if (buf < USER_START_ADDR || buf + len >= USER_END_ADDR) {
    return -EFAULT;
  }
  return host_write(1, buf, len);
}

// Define system call list
// Format: SyscallEntry(number, name, # of args)
// clang-format off
#define SYS_CALL_LIST \
  SyscallEntry(63, read, 3) \
  SyscallEntry(64, write, 3) \
  SyscallEntry(93, exit, 1) // clang-format on

// Make wrappers for syscalls with various numbers of arguments
#define SYSCALL_WRAP_1(name)                                                                       \
  void sys_##name##_wrap() {                                                                       \
    set_ureg(REG_A0, sys_##name(get_ureg(REG_A0)));                                                \
    mret();                                                                                        \
  }

#define SYSCALL_WRAP_2(name)                                                                       \
  void sys_##name##_wrap() {                                                                       \
    set_ureg(REG_A0, sys_##name(get_ureg(REG_A0), get_ureg(REG_A1)));                              \
    mret();                                                                                        \
  }

#define SYSCALL_WRAP_3(name)                                                                       \
  void sys_##name##_wrap() {                                                                       \
    set_ureg(REG_A0, sys_##name(get_ureg(REG_A0), get_ureg(REG_A1), get_ureg(REG_A2)));            \
    mret();                                                                                        \
  }

// Wrap all the syscalls
#define SyscallEntry(id, name, args) SYSCALL_WRAP_##args(name)
SYS_CALL_LIST
#undef SyscallEntry

uint32_t syscallTable[512];

extern "C" void ecall_dispatch() {
  uint32_t idx = get_ureg(REG_A7);
  register uintptr_t t0 asm("t0") = syscallTable[idx];
  asm volatile("jr t0\n"
               :         // no outputs
               : "r"(t0) // inputs
               :         // no clobbers
  );
}

extern "C" void start() {
  // Set up user stack
  set_ureg(REG_SP, 0xbffffffc);
  // Set up syscall dispatch table
  uint32_t* dispatchAddr = reinterpret_cast<uint32_t*>(ECALL_DISPATCH_ADDR);
  *dispatchAddr = reinterpret_cast<uint32_t>(ecall_dispatch);
#define SyscallEntry(id, name, args)                                                               \
  syscallTable[id] = reinterpret_cast<uint32_t>(sys_##name##_wrap);
  SYS_CALL_LIST
#undef SyscallEntry
  // Jump into userland
  mret();
}
