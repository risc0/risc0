// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "core/log.h"
#include "zkp/fp.h"
#include "zkp/fpext.h"

#include <array>
#include <atomic>

using risc0::Fp;
using risc0::FpExt;
using Val = Fp;
using ValExt = FpExt;
using std::array;

#include "hal/hal.h"
using risc0::RowInfo;

#define CONSTANT constexpr
#define CTX Context& ctx
#define DEV /**/
#define FDEV /**/
#define MDEV /**/
#define ATOMIC_U32 std::atomic<uint32_t>
inline void ATOMIC_ADD(ATOMIC_U32& data, uint32_t toAdd) { data.fetch_add(toAdd, std::memory_order_relaxed); }
inline uint32_t ATOMIC_GET(ATOMIC_U32& data) { return data.load(std::memory_order_relaxed); }

x
