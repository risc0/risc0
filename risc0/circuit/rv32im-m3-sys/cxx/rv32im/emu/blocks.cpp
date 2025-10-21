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

#include "rv32im/emu/blocks.h"

#include "core/util.h"
#include "rv32im/circuit/circuit.ipp"

namespace risc0::rv32im {

namespace {

struct ArgCountContext {
  using ValImpl = Fp;
  using ValExtImpl = FpExt;
  struct RegImpl {
    Fp get() { return 0; }
    template <typename T> void applyInner(ArgCountContext& ctx) {}
    void addArguments(ArgCountContext& ctx) {}
    Fp data;
  };
  using ArgCountRegImpl = RegImpl;
  size_t argCount = 0;

  template <typename T> inline void push(T argument) { argCount++; }
  template <typename T> inline void pull(T argument) { argCount++; }
  template <typename T> inline void addArgument(Fp count, T argument) { argCount++; }
  inline Fp globalGet(uint32_t offset) { return 0; }
};

struct AddArgsFwd {
  template <typename T, typename... Args>
  static void apply(ArgCountContext& ctx, T& obj, Args... args) {
    obj.template applyInner<AddArgsFwd>(ctx, args...);
    obj.addArguments(ctx, args...);
  }

  template <typename T, size_t N> static void apply(ArgCountContext& ctx, T (&t)[N]) {
    for (size_t i = 0; i < N; i++) {
      AddArgsFwd::apply(ctx, t[i]);
    }
  }
};

} // namespace

size_t computeMaxWitPerRow(bool tune) {
  size_t ret = 0;
#define BLOCK_TYPE(name, count)                                                                    \
  {                                                                                                \
    size_t witSize = sizeof(name##Witness) / sizeof(Fp);                                           \
    size_t tot = count * witSize;                                                                  \
    if (tune) {                                                                                    \
      LOG(2,                                                                                       \
          "  Block type: " << #name << ": size = " << witSize << ", count = " << count             \
                           << ", tot = " << tot);                                                  \
    }                                                                                              \
    ret = std::max(ret, tot);                                                                      \
  }
  BLOCK_TYPES
#undef BLOCK_TYPE
  return ret;
}

size_t computeMaxDataPerRow(bool tune) {
  size_t ret = 0;
  size_t base = MAJOR_SPLIT_SIZE + MINOR_SPLIT_SIZE;
#define BLOCK_TYPE(name, count)                                                                    \
  {                                                                                                \
    size_t blockSize = sizeof(name##Block<ArgCountContext>) / sizeof(Fp);                          \
    size_t tot = base + count + count * blockSize;                                                 \
    if (tune) {                                                                                    \
      LOG(2,                                                                                       \
          "  Block type: " << #name << ":size = " << blockSize << ", count = " << count            \
                           << ", tot = " << tot);                                                  \
    }                                                                                              \
    ret = std::max(ret, tot);                                                                      \
  }
  BLOCK_TYPES
#undef BLOCK_TYPE
  return ret;
}

size_t computeMaxAccumPerRow(bool tune) {
  size_t ret = 0;
#define BLOCK_TYPE(name, count)                                                                    \
  {                                                                                                \
    ArgCountContext ctx;                                                                           \
    name##Block<ArgCountContext> block;                                                            \
    AddArgsFwd::apply(ctx, block);                                                                 \
    size_t tot = count * ctx.argCount;                                                             \
    if (tune) {                                                                                    \
      LOG(2,                                                                                       \
          "  Block type: " << #name << ": args = " << ctx.argCount << ", count = " << count        \
                           << ", tot = " << tot);                                                  \
    }                                                                                              \
    ret = std::max(ret, tot);                                                                      \
  }
  BLOCK_TYPES
#undef BLOCK_TYPE
  return 4 + ceilDiv(ret, 2) * 4;
}

size_t computeAccumTopSize() {
  return sizeof(AccumTop<ArgCountContext>) / sizeof(Fp);
}

} // namespace risc0::rv32im
