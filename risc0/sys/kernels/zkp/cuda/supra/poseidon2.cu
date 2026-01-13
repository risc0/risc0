#include <ff/baby_bear.hpp>
#include <util/gpu_t.cuh>
#include <util/rusterror.h>

#include "poseidon2.cuh"

extern "C" RustError::by_value
sppark_poseidon2_fold(cudaStream_t stream, poseidon_out_t* d_out, const poseidon_in_t* d_in, size_t num_hashes) {
  size_t block_size = num_hashes < 256 ? num_hashes : 256;
  size_t num_blocks = num_hashes < 256 ? 1 : num_hashes / 256;

  try {
    _poseidon2_fold<<<num_blocks, block_size, 0, stream>>>(d_out, d_in, num_hashes);

    CUDA_OK(cudaGetLastError());

    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const cuda_error& e) {
    CUDA_OK(cudaStreamSynchronize(stream));
    return RustError{e.code(), e.what()};
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value
sppark_poseidon2_rows(cudaStream_t stream, poseidon_out_t* d_out, const fr_t* d_in, uint32_t count, uint32_t col_size) {
  size_t block_size = count < 256 ? count : 256;
  size_t num_blocks = (count + block_size - 1) / block_size;

  try {
    _poseidon2_rows<<<num_blocks, block_size, 0, stream>>>(d_out, d_in, count, col_size);

    CUDA_OK(cudaGetLastError());

    CUDA_OK(cudaStreamSynchronize(stream));
  } catch (const cuda_error& e) {
    CUDA_OK(cudaStreamSynchronize(stream));
    return RustError{e.code(), e.what()};
  }

  return RustError{cudaSuccess};
}
