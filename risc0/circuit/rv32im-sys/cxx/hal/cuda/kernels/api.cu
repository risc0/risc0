// Copyright 2026 RISC Zero, Inc.
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

extern "C" void prefix_sum(cudaStream_t stream, fr_t* buf, uint32_t count) {
  thrust::inclusive_scan(thrust::cuda::par.on(stream), buf, buf + count, buf);
}

extern "C" RustError::by_value rv32im_poly_divide(
    cudaStream_t stream, fr4_t d_inout[/*len*/], size_t len, fr4_t* remainder, fr4_t pow) {
  stream_t sppark_stream(stream, 0);
  try {
    div_by_x_minus_z<true>(d_inout, len, pow, sppark_stream);
    sppark_stream.DtoH(remainder, &d_inout[len - 1], 1);
    sppark_stream.sync();
  } catch (const cuda_error& e) {
    sppark_stream.sync();
    return RustError{e.code(), e.what()};
  }

  return RustError{cudaSuccess};
}
