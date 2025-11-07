#include "ff/baby_bear.hpp"
#include "ntt/ntt.cuh"

extern "C" RustError::by_value sppark_batch_expand(
    cudaStream_t stream, fr_t* d_out, fr_t* d_in, uint32_t lg_domain_size, uint32_t lg_blowup, uint32_t poly_count) {
  if (lg_domain_size == 0)
    return RustError{cudaSuccess};

  uint32_t domain_size = 1U << lg_domain_size;
  uint32_t ext_domain_size = domain_size << lg_blowup;

  stream_t sppark_stream (stream, 0);

  try {
    for (size_t c = 0; c < poly_count; c++) {
      NTT::LDE_expand(
          sppark_stream, &d_out[c * ext_domain_size], &d_in[c * domain_size], lg_domain_size, lg_blowup);
    }

    sppark_stream.sync();
  } catch (const cuda_error& e) {
    sppark_stream.sync();
    return RustError{e.code(), e.what()};
  } catch (...) {
    return RustError(cudaErrorUnknown, "Generic exception");
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value
sppark_batch_NTT(cudaStream_t stream, fr_t* d_inout, uint32_t lg_domain_size, uint32_t poly_count) {
  if (lg_domain_size == 0)
    return RustError{cudaSuccess};

  uint32_t domain_size = 1U << lg_domain_size;

  stream_t sppark_stream(stream, 0);

  try {
    for (size_t c = 0; c < poly_count; c++) {
      NTT::Base_dev_ptr(sppark_stream,
                        &d_inout[c * domain_size],
                        lg_domain_size,
                        NTT::InputOutputOrder::RN,
                        NTT::Direction::forward,
                        NTT::Type::standard);
    }

    sppark_stream.sync();
  } catch (const cuda_error& e) {
    sppark_stream.sync();
    return RustError{e.code(), e.what()};
  } catch (...) {
    return RustError(cudaErrorUnknown, "Generic exception");
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value
sppark_batch_iNTT(cudaStream_t stream, fr_t* d_inout, uint32_t lg_domain_size, uint32_t poly_count) {
  if (lg_domain_size == 0)
    return RustError{cudaSuccess};

  uint32_t domain_size = 1U << lg_domain_size;

  stream_t sppark_stream(stream, 0);

  try {
    for (size_t c = 0; c < poly_count; c++) {
      NTT::Base_dev_ptr(sppark_stream,
                        &d_inout[c * domain_size],
                        lg_domain_size,
                        NTT::InputOutputOrder::NR,
                        NTT::Direction::inverse,
                        NTT::Type::standard);
    }

    sppark_stream.sync();
  } catch (const cuda_error& e) {
    sppark_stream.sync();
    return RustError{e.code(), e.what()};
  } catch (...) {
    return RustError(cudaErrorUnknown, "Generic exception");
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value
sppark_batch_zk_shift(cudaStream_t stream, fr_t* d_inout, uint32_t lg_domain_size, uint32_t poly_count) {
  if (lg_domain_size == 0)
    return RustError{cudaSuccess};

  uint32_t domain_size = 1U << lg_domain_size;

  stream_t sppark_stream(stream, 0);

  try {
    for (size_t c = 0; c < poly_count; c++) {
      NTT::LDE_powers(sppark_stream, &d_inout[c * domain_size], lg_domain_size);
    }

    sppark_stream.sync();
  } catch (const cuda_error& e) {
    sppark_stream.sync();
    return RustError{e.code(), e.what()};
  } catch (...) {
    return RustError(cudaErrorUnknown, "Generic exception");
  }

  return RustError{cudaSuccess};
}
