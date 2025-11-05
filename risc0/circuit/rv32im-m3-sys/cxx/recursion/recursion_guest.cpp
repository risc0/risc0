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

#include <unistd.h>
#include "verify/read_iop.h"
#include "verify/rv32im.h"

using namespace risc0;

// Bump allocator
char* heap = reinterpret_cast<char*>(0x10000000);
void* operator new(std::size_t size) noexcept {
  void* ret = heap;
  heap += size;
  return ret;
}

void operator delete(void* ptr) noexcept {}
void operator delete(void* ptr, std::size_t size) noexcept {}

void std::__throw_length_error(char const*) { exit(1); }
void std::__throw_bad_function_call() { exit(1); }
void std::__throw_bad_array_new_length() { exit(1); }
void std::__throw_bad_alloc() { exit(1); }

// Primitive logging
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
  write(level, log.start(), log.size()); \
} while(0)

void blockRead(char* buf, uint32_t totSize) {
  while (totSize > 0) {
    uint32_t toRead = totSize > 16*1024 ? 16*1024 : totSize;
    uint32_t ret = read(0, buf, toRead);
    buf += ret;
    totSize -= ret;
  }
}

int main() {
  LOG(0, "Hello Guest");
  uint32_t len = 0;
  read(0, &len, sizeof(uint32_t));
  Fp* transcript = reinterpret_cast<Fp*>(heap);
  heap += sizeof(uint32_t) * len;
  LOG(0, "Read transcript, size = " << len);
  blockRead(reinterpret_cast<char*>(transcript), len * sizeof(Fp));
  LOG(0, "Constructing IOP");
  ReadIop iop(transcript, len);
  LOG(0, "Here we go!");
  verifyRv32im(iop, 12);
  return 0;
}
