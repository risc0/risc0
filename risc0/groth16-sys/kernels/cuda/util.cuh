#pragma once

#include <cstdint>
#include <iostream>
#include <sstream>

// for mult method
#include "msm/pippenger.hpp"

#include "chacha.cuh"

class groth16_params {
private:
  static constexpr const char* pcoeffs_file = "/preprocessed_coeffs.bin";
  static constexpr const char* fres_file = "/fuzzed_msm_results.bin";
  static constexpr const char* graph_dir = "/parallel-graph/";

  std::string pcoeffs_path, fres_path, graph_path;

public:
  groth16_params(const char* pdir)
      : pcoeffs_path(std::string(pdir) + pcoeffs_file)
      , fres_path(std::string(pdir) + fres_file)
      , graph_path(std::string(pdir) + graph_dir) {}

  const std::string& get_pcoeffs_path() { return pcoeffs_path; }
  const std::string& get_fres_path() { return fres_path; }
  const std::string& get_graph_path() { return graph_path; }
};

template <int ROUNDS, class field_t>
__global__ __launch_bounds__(1024) void chacha_generate_random_scalars(field_t* output,
                                                                       const chacha_state state,
                                                                       size_t output_block_count) {
  union state_and_field {
    chacha_state state;
    field_t v[2];
  };

  const int len = 8;

  size_t tid = blockIdx.x * (size_t)blockDim.x + threadIdx.x;
  uint32_t laneid = tid % WARP_SZ;

  for (size_t i = tid; i < output_block_count; i += (size_t)gridDim.x * blockDim.x) {
    size_t wid = i / WARP_SZ;
    size_t idx = laneid + wid * sizeof(chacha_state);

    state_and_field s = state_and_field{state};

    chacha_mix<ROUNDS>(s.state, i);

    s.v[0][len - 1] &= 0x1FFFFFFFu;
    s.v[1][len - 1] &= 0x1FFFFFFFu;

    output[idx] = s.v[0];
    output[idx + WARP_SZ] = s.v[1];
  }
}

gpu_ptr_t<fr_t> generate_random_scalars(const gpu_t& gpu, size_t n) {
  static const uint8_t key[32] = {0};
  static const uint8_t nonce[12] = {0};

  size_t size_bytes = n * sizeof(fr_t);
  // ceil
  size_t block_count = (size_bytes + 64 - 1) / 64;

  gpu_ptr_t<fr_t> random_scalars((fr_t*)gpu.Dmalloc(block_count * 64));
  chacha_state state = initialize_chacha_state<uint32_t>(key, nonce);

  chacha_generate_random_scalars<8>
      <<<gpu.sm_count(), 1024, 0, gpu>>>(&random_scalars[0], state, block_count);

  return random_scalars;
}

__global__ __launch_bounds__(1024) void coeff_wise_mul_and_sub(fr_t* inout,
                                                               const fr_t* in1,
                                                               const fr_t* in2,
                                                               uint32_t lg_domain_size) {
  size_t tid = threadIdx.x + (size_t)blockIdx.x * blockDim.x;

  size_t domain_size = (size_t)1 << lg_domain_size;

  for (size_t i = tid; i < domain_size; i += (size_t)gridDim.x * blockDim.x) {
    fr_t v1 = inout[i], v2 = in1[i], v3 = in2[i];
    v1 *= v2;
    v1 -= v3;
    inout[i] = v1;
  }
}

__global__ __launch_bounds__(1024) void coeff_wise_mul(fr_t* out,
                                                       const fr_t* in1,
                                                       const fr_t* in2,
                                                       uint32_t lg_domain_size) {
  size_t tid = threadIdx.x + (size_t)blockIdx.x * blockDim.x;

  size_t domain_size = (size_t)1 << lg_domain_size;

  for (size_t i = tid; i < domain_size; i += (size_t)gridDim.x * blockDim.x) {
    fr_t v1 = in1[i], v2 = in2[i];
    v1 *= v2;
    out[i] = v1;
  }
}

__global__ __launch_bounds__(1024) void coeff_wise_add(fr_t inout[], const fr_t in[], size_t n) {
  size_t tid = threadIdx.x + (size_t)blockIdx.x * blockDim.x;

  for (size_t i = tid; i < n; i += (size_t)gridDim.x * blockDim.x) {
    fr_t res = inout[i], val = in[i];
    res += val;
    inout[i] = res;
  }
}

template <class point_t, class affine_t>
static void mult(point_t& ret, const affine_t& point, const fr_t& fr, size_t top = fr_t::nbits) {
#ifndef __CUDA_ARCH__
  fr_t::pow_t scalar;
  fr.to_scalar(scalar);

  mult(ret, point, scalar, top);
#endif
}
