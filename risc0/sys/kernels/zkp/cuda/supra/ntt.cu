#include <ff/baby_bear.hpp>

#include <ntt/ntt.cuh>  // For NTT::Base, NTT::LDE_expand, NTT::Base_dev_ptr (upstream sppark)

// Include ntt_kernels.cu before ntt_lde.cuh to ensure template definitions are visible
#include "ntt_kernels.cu"
#include "ntt_lde.cuh"  // For NTTLDE::LDE_powers (local implementation)

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
sppark_batch_zk_shift(fr_t* d_inout, uint32_t lg_domain_size, uint32_t poly_count, uint32_t beta_u32, uint32_t factor) {
  if (lg_domain_size == 0)
    return RustError{cudaSuccess};

  uint32_t batch_size = 4;
  uint32_t batch_num = poly_count / batch_size;
  uint32_t tail = poly_count % batch_size;

  uint32_t domain_size = 1U << lg_domain_size;
  fr_t beta = fr_t(beta_u32);
  const gpu_t& gpu = select_gpu();

  try {
    CUDA_OK(cudaDeviceSynchronize());

    for (size_t c = 0; c < batch_num; c++) {
        uint32_t fac = factor;
      NTTLDE::LDE_shift(gpu, &d_inout[domain_size * c * batch_size], lg_domain_size, beta, fac, batch_size);
    }
    if (tail>0) {
        uint32_t fac = factor;
      NTTLDE::LDE_shift(gpu, &d_inout[domain_size * batch_num * batch_size], lg_domain_size, beta, fac, tail);
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
sppark_batch_zk_shift_outplace(fr_t* d_in, fr_t* d_out, uint32_t lg_domain_size,
                               uint32_t poly_count, uint32_t beta_u32, uint32_t factor) {
  if (lg_domain_size == 0)
    return RustError{cudaSuccess};

  uint32_t batch_size = 4;
  uint32_t batch_num = poly_count / batch_size;
  uint32_t tail = poly_count % batch_size;

  uint32_t domain_size = 1U << lg_domain_size;
  fr_t beta = fr_t(beta_u32);

  uint32_t base_idx;
  const gpu_t& gpu = select_gpu();

  try {
    CUDA_OK(cudaDeviceSynchronize());

    for (size_t c = 0; c < batch_num; c++) {
      uint32_t fac = factor;
      base_idx = domain_size * c * batch_size;
      NTTLDE::LDE_shift_outplace(gpu, &d_in[base_idx], &d_out[base_idx], lg_domain_size, beta, fac, batch_size);
    }

    if (tail>0) {
      uint32_t fac = factor;
      base_idx = domain_size * batch_num * batch_size;
      NTTLDE::LDE_shift_outplace(gpu, &d_in[base_idx], &d_out[base_idx], lg_domain_size, beta, fac, tail);
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
sppark_batch_coeffs_bitrev(fr_t* d_inout, uint32_t lg_domain_size, uint32_t poly_count) {
  if (lg_domain_size == 0)
    return RustError{cudaSuccess};

  uint32_t base_idx;
  uint32_t domain_size = 1U << lg_domain_size;
  const gpu_t& gpu = select_gpu();

  try {
    CUDA_OK(cudaDeviceSynchronize());

    for (size_t c = 0; c < poly_count; c++) {
      base_idx = domain_size * c;
      NTTLDE::LDE_coeffs_bitrev(gpu, &d_inout[base_idx], lg_domain_size);
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