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

#pragma once

#if defined(CUDA)

struct RowInfo {
  uint8_t rowType;
  uint8_t blockCount;
  uint16_t padding;
  uint32_t auxOffset;
};

#define FDEV __device__
#define DEV /**/
#define MDEV /**/
#define MTHR /**/
#define CONSTANT constexpr

#include <array>

template<typename T, size_t N>
using array = std::array<T, N>;

#define ATOMIC_U32 uint32_t
__device__ inline void ATOMIC_ADD(uint32_t& data, uint32_t toAdd) { atomicAdd(&data, toAdd); }
__device__ inline uint32_t ATOMIC_GET(uint32_t& data) { return data; }

#define LOG(...) /**/

#elif defined(METAL)

struct RowInfo {
  RowInfo() = default;
  RowInfo(uint8_t rowType, uint8_t blockCount, uint32_t auxOffset)
      : rowType(rowType), blockCount(blockCount), auxOffset(auxOffset) {}
  uint8_t rowType;
  uint8_t blockCount;
  uint16_t padding = 0;
  uint32_t auxOffset;
};

#define FDEV /**/
#define DEV device
#define MDEV device
#define MTHR thread
#define CONSTANT constexpr constant

using namespace metal;

#include <metal_atomic>

#define ATOMIC_U32 atomic_uint
inline void ATOMIC_ADD(atomic_uint device& data, uint32_t toAdd) { atomic_fetch_add_explicit(&data, toAdd, memory_order_relaxed); }
inline uint32_t ATOMIC_GET(atomic_uint device& data) { return atomic_load_explicit(&data, memory_order_relaxed); }

#define LOG(...) /**/

#else

#define FDEV /**/
#define DEV /**/
#define MDEV /**/
#define MTHR /**/
#define CONSTANT constexpr

#include "zkp/fp.h"
#include "zkp/fpext.h"
#include <array>
#include <atomic>

template<typename T, size_t N>
using array = std::array<T, N>;

using risc0::Fp;
using risc0::FpExt;

#include "core/log.h"

#define ATOMIC_U32 std::atomic<uint32_t>
inline void ATOMIC_ADD(ATOMIC_U32& data, uint32_t toAdd) { data.fetch_add(toAdd, std::memory_order_relaxed); }
inline uint32_t ATOMIC_GET(ATOMIC_U32& data) { return data.load(std::memory_order_relaxed); }

#endif
