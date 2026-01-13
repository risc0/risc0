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

#include "rv32im/argument/cpu_state.h"
#include "rv32im/argument/decode.h"
#include "rv32im/argument/io.h"
#include "rv32im/argument/lookup.h"
#include "rv32im/argument/memory.h"
#include "rv32im/argument/paging.h"
#include "rv32im/argument/poseidon2.h"
#include "rv32im/argument/unit.h"

#define ARGUMENT_TYPES                                                                             \
  ARGUMENT_TYPE(Lookup)                                                                            \
  ARGUMENT_TYPE(MakeTable)                                                                         \
  ARGUMENT_TYPE(CpuState)                                                                          \
  ARGUMENT_TYPE(BigIntCpuState)                                                                    \
  ARGUMENT_TYPE(Decode)                                                                            \
  ARGUMENT_TYPE(Unit)                                                                              \
  ARGUMENT_TYPE(Memory)                                                                            \
  ARGUMENT_TYPE(P2Id)                                                                              \
  ARGUMENT_TYPE(P2State)                                                                           \
  ARGUMENT_TYPE(P2Call)                                                                            \
  ARGUMENT_TYPE(PageIn)                                                                            \
  ARGUMENT_TYPE(PageInPart)                                                                        \
  ARGUMENT_TYPE(PageOut)                                                                           \
  ARGUMENT_TYPE(PageOutPart)                                                                       \
  ARGUMENT_TYPE(P2Step)                                                                            \
  ARGUMENT_TYPE(ReadState)

enum class ArgumentType {
#define ARGUMENT_TYPE(name) name,
  ARGUMENT_TYPES
#undef ARGUMENT_TYPE
};

template <typename T> struct GetArgumentType {};

#define ARGUMENT_TYPE(name)                                                                        \
  template <typename C> struct GetArgumentType<name##Argument<C>> {                                \
    static CONSTANT ArgumentType value = ArgumentType::name;                                       \
  };
ARGUMENT_TYPES
#undef ARGUMENT_TYPE

template <typename T, typename C>
FDEV ValExt<C> flattenArgument(const MTHR T& argument, const MDEV ValExt<C>* mix) {
  ValExt<C> tot;
  Val<C> type = Val<C>(uint32_t(GetArgumentType<T>::value));
  tot += mix[0] * type;
  for (size_t i = 0; i < sizeof(T) / sizeof(Val<C>); i++) {
    tot += ValExt<C>(mix[i + 1]) * reinterpret_cast<const MTHR Val<C>*>(&argument)[i];
  }
  return tot;
}
