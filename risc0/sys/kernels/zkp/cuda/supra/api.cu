#include <ff/alt_bn128.hpp>
#include <ff/baby_bear.hpp>
#include <util/gpu_t.cuh>
#include <util/rusterror.h>

#include <polynomial/div_by_x_minus_z.cuh>
#include <polynomial/prefix_op.cuh>

#include "poseidon254.cuh"

static void compute_grid_block_size(size_t total_count, size_t& block_size, size_t& num_blocks) {
  size_t min_block_size = 4 * WARP_SZ;

  if (total_count < (block_size * num_blocks)) {
    size_t count_per_block = total_count / num_blocks;

    if (count_per_block > min_block_size) {
      block_size = ((count_per_block + min_block_size - 1) / min_block_size) * min_block_size;
      num_blocks = (total_count + block_size - 1) / block_size;
    } else {
      block_size = min_block_size;
      num_blocks = (total_count + min_block_size - 1) / min_block_size;
    }
  } else {
    size_t base_iter = (total_count + (num_blocks * block_size) - 1) / (num_blocks * block_size);
    size_t out_block_size = block_size;

    for (size_t cur_block_size = block_size - min_block_size; cur_block_size >= min_block_size;
         cur_block_size -= min_block_size) {
      size_t cur_iter =
          (total_count + (num_blocks * cur_block_size) - 1) / (num_blocks * cur_block_size);

      if (cur_iter != base_iter)
        break;
      out_block_size = cur_block_size;
    }

    block_size = out_block_size;
  }
}

extern "C" RustError::by_value
sppark_poseidon254_fold(cudaStream_t stream, alt_bn128::fr_t* d_out, const alt_bn128::fr_t* d_in, size_t num_hashes) {
  stream_t sppark_stream(stream, 0);

  size_t block_size = 512;
  size_t num_blocks = sppark_stream.sm_count();

  compute_grid_block_size(num_hashes, block_size, num_blocks);

  try {
    _poseidon254_fold<<<num_blocks, block_size, 0, sppark_stream>>>(d_out, d_in, num_hashes);

    CUDA_OK(cudaGetLastError());

    sppark_stream.sync();
  } catch (const cuda_error& e) {
    sppark_stream.sync();
    return RustError{e.code(), e.what()};
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value
sppark_poseidon254_rows(cudaStream_t stream, alt_bn128::fr_t* d_out, const fr_t* d_in, size_t count, uint32_t col_size) {
  stream_t sppark_stream(stream, 0);

  size_t block_size = 512;
  size_t num_blocks = sppark_stream.sm_count();

  compute_grid_block_size(count, block_size, num_blocks);

  try {
    _poseidon254_rows<<<num_blocks, block_size, 0, sppark_stream>>>(d_out, d_in, count, col_size);

    CUDA_OK(cudaGetLastError());

    sppark_stream.sync();
  } catch (const cuda_error& e) {
    sppark_stream.sync();
    return RustError{e.code(), e.what()};
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value sppark_prefix_product(cudaStream_t stream, fr4_t d_inout[/*count*/], uint32_t count) {
  stream_t sppark_stream(stream, 0);

  try {
    prefix_op<Multiply<fr4_t>>(d_inout, count, sppark_stream);
    sppark_stream.sync();
  } catch (const cuda_error& e) {
    sppark_stream.sync();
    return RustError{e.code(), e.what()};
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value
supra_poly_divide(cudaStream_t stream, fr4_t d_inout[/*len*/], size_t len, fr4_t* remainder, const fr4_t& pow) {

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
