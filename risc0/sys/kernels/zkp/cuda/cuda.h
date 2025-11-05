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

#pragma once

#include <cstdint>
#include <cstring>
#include <cuda_runtime.h>
#include <stdexcept>

template <typename... Types> inline std::string fmt(const char* fmt, Types... args) {
  size_t len = std::snprintf(nullptr, 0, fmt, args...);
  std::string ret(++len, '\0');
  std::snprintf(&ret.front(), len, fmt, args...);
  ret.resize(--len);
  return ret;
}

#define CUDA_OK(expr)                                                                              \
  do {                                                                                             \
    cudaError_t code = expr;                                                                       \
    if (code != cudaSuccess) {                                                                     \
      auto file = std::strstr(__FILE__, "sppark");                                                 \
      auto msg = fmt("%s@%s:%d failed: \"%s\"",                                                    \
                     #expr,                                                                        \
                     file ? file : __FILE__,                                                       \
                     __LINE__,                                                                     \
                     cudaGetErrorString(code));                                                    \
      throw std::runtime_error{msg};                                                               \
    }                                                                                              \
  } while (0)

struct LaunchConfig {
  dim3 grid;
  dim3 block;
  size_t shared;

  LaunchConfig(dim3 grid, dim3 block, size_t shared = 0)
      : grid(grid), block(block), shared(shared) {}
  LaunchConfig(int grid, int block, size_t shared = 0) : grid(grid), block(block), shared(shared) {}
};

inline LaunchConfig getSimpleConfig(uint32_t count) {
  int device;
  CUDA_OK(cudaGetDevice(&device));

  int maxThreads;
  CUDA_OK(cudaDeviceGetAttribute(&maxThreads, cudaDevAttrMaxThreadsPerBlock, device));

  int block = maxThreads / 4;
  int grid = (count + block - 1) / block;
  return LaunchConfig{grid, block, 0};
}

template <typename... ExpTypes, typename... ActTypes>
const char* launchKernel(void (*kernel)(ExpTypes...),
                         cudaStream_t stream,
                         uint32_t count,
                         uint32_t shared_size,
                         ActTypes&&... args) {
  try {
    LaunchConfig cfg = getSimpleConfig(count);
    cudaLaunchConfig_t config;
    config.attrs = nullptr;
    config.numAttrs = 0;
    config.gridDim = cfg.grid;
    config.blockDim = cfg.block;
    config.dynamicSmemBytes = shared_size;
    config.stream = stream;
    CUDA_OK(cudaLaunchKernelEx(&config, kernel, std::forward<ActTypes>(args)...));
    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const std::exception& err) {
    return strdup(err.what());
  } catch (...) {
    return strdup("Generic exception");
  }
  return nullptr;
}
