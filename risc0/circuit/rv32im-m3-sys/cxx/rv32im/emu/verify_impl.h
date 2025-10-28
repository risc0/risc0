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

#include <array>
#include <map>

#define IN_VERIFY 1

#include "rv32im/circuit/circuit.ipp"

namespace NAMESPACE {

constexpr size_t NUM_ROWS = (1 << NUM_ROWS_PO2);

inline const char* getArgumentTypeName(ArgumentType type) {
  switch (type) {
#define ARGUMENT_TYPE(name)                                                                        \
  case ArgumentType::name:                                                                         \
    return #name;
    ARGUMENT_TYPES
#undef ARGUMENT_TYPE
  default:
    return "***UNKNOWN***";
  };
}

struct Context {
  using ValImpl = Fp;
  using ValExtImpl = FpExt;

  struct RegImpl {
    Fp get() { return data[0]; }
    template <typename T> void applyInner(Context& ctx) {}
    void verify(Context& ctx) {}
    void addArguments(Context& ctx) {}
    Fp data[NUM_ROWS];
  };
  using ArgCountRegImpl = RegImpl;

  std::map<std::vector<Fp>, Fp> args;
  const Fp* globals;
  Fp isValid;
  Fp x;
  inline void eqz(Fp val) {
    if (val != 0) {
      LOG(0, "Invalid eqz, val = " << val);
      throw std::runtime_error("Invalid eqz");
    }
  }
  inline void eqz(FpExt val) {
    if (val != FpExt(0)) {
      LOG(0, "Invalid eqz, val = " << val);
      throw std::runtime_error("Invalid eqz");
    }
  }
  template <typename T> inline void fpAddArgument(Fp count, const T& argument) {
    std::vector<Fp> all;
    all.push_back(Fp(uint32_t(GetArgumentType<T>::value)));
    for (size_t i = 0; i < sizeof(T) / sizeof(Fp); i++) {
      all.push_back(reinterpret_cast<const Fp*>(&argument)[i]);
    }
    args[all] += count;
  }

  template <typename T> inline void push(const T& argument) { fpAddArgument(isValid, argument); }
  template <typename T> inline void pull(const T& argument) {
    fpAddArgument(isValid * -Fp(1), argument);
  }
  template <typename T> inline void addArgument(Fp count, const T& argument) {
    fpAddArgument(count, argument);
  }
  inline Fp globalGet(uint32_t offset) { return globals[offset]; }
  inline Fp getX() { return x; }

  inline void checkArgs() {
    size_t count = 0;
    for (const auto& kvp : args) {
      if (count == 10)
        break;
      if (kvp.second == 0)
        continue;
      LOG(0,
          "Unmatched argument, type = "
              << getArgumentTypeName(static_cast<ArgumentType>(kvp.first[0].asUInt32()))
              << ", error = " << kvp.second);
      for (size_t i = 1; i < kvp.first.size(); i++) {
        LOG(0, "  " << kvp.first[i]);
      }
      count++;
    }
    if (count != 0) {
      throw std::runtime_error("Invalid arguments");
    }
  }
};

struct BothFwd {
  template <typename T, typename... Args>
  static void apply(Context& ctx, const char*, T& obj, Args... args) {
    BothFwd::apply(ctx, obj, args...);
  }

  template <typename T, typename... Args> static void apply(Context& ctx, T& obj, Args... args) {
    obj.template applyInner<BothFwd>(ctx, args...);
    obj.verify(ctx, args...);
    obj.addArguments(ctx, args...);
  }

  template <typename T, size_t N, typename... Args>
  static void apply(Context& ctx, T (&t)[N], Args... args) {
    for (size_t i = 0; i < N; ++i) {
      BothFwd::apply(ctx, t[i], args...);
    }
  }
};

} // namespace NAMESPACE

namespace risc0 {

using namespace NAMESPACE;

void FUNCNAME(const Fp* dataConst, const Fp* globals, Fp rou) {
  using RegImpl = Context::RegImpl;
  Context ctx;
  ctx.globals = globals;
  for (size_t row = 0; row < NUM_ROWS; row++) {
    ctx.x = pow(rou, row);
    Fp* data = const_cast<Fp*>(dataConst) + row;
    size_t idxMajor = reinterpret_cast<OneHot<Context, MAJOR_SPLIT_SIZE>*>(data)->get().asUInt32();
    data += MAJOR_SPLIT_SIZE * NUM_ROWS;
    size_t idxMinor = reinterpret_cast<OneHot<Context, MINOR_SPLIT_SIZE>*>(data)->get().asUInt32();
    data += MINOR_SPLIT_SIZE * NUM_ROWS;
    size_t idx = idxMajor * MINOR_SPLIT_SIZE + idxMinor;
    BlockType type = static_cast<BlockType>(idx);
    switch (type) {
#define BLOCK_TYPE(name, count)                                                                    \
  case BlockType::name: {                                                                          \
    RegImpl* isValidRegs = reinterpret_cast<RegImpl*>(data);                                       \
    data += count * NUM_ROWS;                                                                      \
    name##Block<Context>* typedBlock = reinterpret_cast<name##Block<Context>*>(data);              \
    LOG(2, "Block type: " << #name);                                                               \
    for (size_t i = 0; i < count; i++) {                                                           \
      ctx.isValid = isValidRegs[i].get();                                                          \
      BothFwd::apply(ctx, typedBlock[i]);                                                          \
    }                                                                                              \
  } break;
      BLOCK_TYPES
#undef BLOCK_TYPE
    case BlockType::Empty:
      break;
    }
  }
  ctx.checkArgs();
}

} // namespace risc0
