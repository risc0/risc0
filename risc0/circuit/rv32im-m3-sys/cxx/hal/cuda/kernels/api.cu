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

#include <ff/baby_bear.hpp>

#include <util/gpu_t.cuh>
#include <util/rusterror.h>

#include <polynomial/div_by_x_minus_z.cuh>

#include <thrust/execution_policy.h>
#include <thrust/scan.h>

extern "C" void prefix_sum(fr_t* buf, uint32_t count) {
  thrust::inclusive_scan(thrust::device, buf, buf + count, buf);
}

extern "C" RustError::by_value
rv32im_m3_poly_divide(fr4_t d_inout[/*len*/], size_t len, fr4_t* remainder, fr4_t pow) {
  const gpu_t& gpu = select_gpu();
  try {
    div_by_x_minus_z<true>(d_inout, len, pow, gpu);
    gpu.DtoH(remainder, &d_inout[len - 1], 1);
    gpu.sync();
  } catch (const cuda_error& e) {
    gpu.sync();
    return RustError{e.code(), e.what()};
  }

  return RustError{cudaSuccess};
}
