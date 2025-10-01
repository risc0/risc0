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

#define FEATURE_BABY_BEAR 1
#include <ff/baby_bear.hpp>
#include <ntt/ntt.cuh>

extern "C" RustError::by_value sppark_init() {
  uint32_t lg_domain_size = 1;
  uint32_t domain_size = 1U << lg_domain_size;

  std::vector<fr_t> inout{domain_size};
  inout[0] = fr_t(1);
  inout[1] = fr_t(1);

  const gpu_t& gpu = select_gpu();

  try {
    CUDA_OK(cudaDeviceSynchronize());

    NTT::Base(gpu,
              &inout[0],
              lg_domain_size,
              NTT::InputOutputOrder::NR,
              NTT::Direction::forward,
              NTT::Type::standard);
    gpu.sync();
  } catch (const cuda_error& e) {
    gpu.sync();
    return RustError{e.code(), e.what()};
  } catch (...) {
    return RustError(cudaErrorUnknown, "Generic exception");
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value sppark_batch_expand(
    fr_t* d_out, fr_t* d_in, uint32_t lg_domain_size, uint32_t lg_blowup, uint32_t poly_count) {
  if (lg_domain_size == 0)
    return RustError{cudaSuccess};

  uint32_t domain_size = 1U << lg_domain_size;
  uint32_t ext_domain_size = domain_size << lg_blowup;

  const gpu_t& gpu = select_gpu();

  try {
    CUDA_OK(cudaDeviceSynchronize());

    for (size_t c = 0; c < poly_count; c++) {
      NTT::LDE_expand(
          gpu, &d_out[c * ext_domain_size], &d_in[c * domain_size], lg_domain_size, lg_blowup);
    }

    gpu.sync();
  } catch (const cuda_error& e) {
    gpu.sync();
    return RustError{e.code(), e.what()};
  } catch (...) {
    return RustError(cudaErrorUnknown, "Generic exception");
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value
sppark_batch_NTT(fr_t* d_inout, uint32_t lg_domain_size, uint32_t poly_count) {
  if (lg_domain_size == 0)
    return RustError{cudaSuccess};

  uint32_t domain_size = 1U << lg_domain_size;

  const gpu_t& gpu = select_gpu();

  try {
    CUDA_OK(cudaDeviceSynchronize());

    for (size_t c = 0; c < poly_count; c++) {
      NTT::Base_dev_ptr(gpu,
                        &d_inout[c * domain_size],
                        lg_domain_size,
                        NTT::InputOutputOrder::RN,
                        NTT::Direction::forward,
                        NTT::Type::standard);
    }

    gpu.sync();
  } catch (const cuda_error& e) {
    gpu.sync();
    return RustError{e.code(), e.what()};
  } catch (...) {
    return RustError(cudaErrorUnknown, "Generic exception");
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value
sppark_batch_iNTT(fr_t* d_inout, uint32_t lg_domain_size, uint32_t poly_count) {
  if (lg_domain_size == 0)
    return RustError{cudaSuccess};

  uint32_t domain_size = 1U << lg_domain_size;

  const gpu_t& gpu = select_gpu();

  try {
    CUDA_OK(cudaDeviceSynchronize());

    for (size_t c = 0; c < poly_count; c++) {
      NTT::Base_dev_ptr(gpu,
                        &d_inout[c * domain_size],
                        lg_domain_size,
                        NTT::InputOutputOrder::NR,
                        NTT::Direction::inverse,
                        NTT::Type::standard);
    }

    gpu.sync();
  } catch (const cuda_error& e) {
    gpu.sync();
    return RustError{e.code(), e.what()};
  } catch (...) {
    return RustError(cudaErrorUnknown, "Generic exception");
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value
sppark_batch_zk_shift(fr_t* d_inout, uint32_t lg_domain_size, uint32_t poly_count) {
  if (lg_domain_size == 0)
    return RustError{cudaSuccess};

  uint32_t domain_size = 1U << lg_domain_size;

  const gpu_t& gpu = select_gpu();

  try {
    CUDA_OK(cudaDeviceSynchronize());

    for (size_t c = 0; c < poly_count; c++) {
      NTT::LDE_powers(gpu, &d_inout[c * domain_size], lg_domain_size);
    }

    gpu.sync();
  } catch (const cuda_error& e) {
    gpu.sync();
    return RustError{e.code(), e.what()};
  } catch (...) {
    return RustError(cudaErrorUnknown, "Generic exception");
  }

  return RustError{cudaSuccess};
}
