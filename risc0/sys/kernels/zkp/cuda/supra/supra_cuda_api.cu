#include <util/exception.cuh>
#include <util/gpu_t.cuh>
#include <util/rusterror.h>

#ifdef FEATURE_BABY_BEAR
#include <ff/baby_bear.hpp>
#endif

#include "calc_prefix_operation.cuh"
#include "poseidon_baby_bear/poseidon.cu"
#include "poseidon_baby_bear/poseidon2.cu"

extern "C" RustError::by_value sppark_poseidon_fold(fr_t* d_out, fr_t* d_in, size_t num_hashes) {
  const gpu_t& gpu = select_gpu();

  size_t block_size = num_hashes < 256 ? num_hashes : 256;
  size_t num_blocks = num_hashes < 256 ? 1 : num_hashes / 256;
  size_t shared_size = std::max(block_size, (size_t)32) * CELLS * sizeof(fr_t);

  try {
    CUDA_OK(cudaDeviceSynchronize());

    _poseidon_fold<<<num_blocks, block_size, shared_size, gpu>>>(d_out, d_in);

    CUDA_OK(cudaGetLastError());

    gpu.sync();
  } catch (const cuda_error& e) {
    gpu.sync();
    return RustError{e.code(), e.what()};
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value
sppark_poseidon_rows(fr_t* d_out, fr_t* d_in, uint32_t count, uint32_t col_size) {
  const gpu_t& gpu = select_gpu();

  size_t block_size = count < 256 ? count : 256;
  size_t num_blocks = count < 256 ? 1 : count / 256;
  size_t shared_size = std::max(block_size, (size_t)32) * CELLS * sizeof(fr_t);

  try {
    CUDA_OK(cudaDeviceSynchronize());

    _poseidon_rows<<<num_blocks, block_size, shared_size, gpu>>>(d_out, d_in, count, col_size);

    CUDA_OK(cudaGetLastError());

    gpu.sync();
  } catch (const cuda_error& e) {
    gpu.sync();
    return RustError{e.code(), e.what()};
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value
sppark_poseidon2_fold(poseidon_out_t* d_out, const poseidon_in_t* d_in, size_t num_hashes) {
  const gpu_t& gpu = select_gpu();

  size_t block_size = num_hashes < 256 ? num_hashes : 256;
  size_t num_blocks = num_hashes < 256 ? 1 : num_hashes / 256;

  try {
    CUDA_OK(cudaDeviceSynchronize());

    _poseidon2_fold<<<num_blocks, block_size, 0, gpu>>>(d_out, d_in, num_hashes);

    CUDA_OK(cudaGetLastError());

    gpu.sync();
  } catch (const cuda_error& e) {
    gpu.sync();
    return RustError{e.code(), e.what()};
  }

  return RustError{cudaSuccess};
}

extern "C" RustError::by_value
sppark_poseidon2_rows(poseidon_out_t* d_out, const fr_t* d_in, uint32_t count, uint32_t col_size) {
  const gpu_t& gpu = select_gpu();

  size_t block_size = count < 256 ? count : 256;
  size_t num_blocks = (count + block_size - 1) / block_size;

  try {
    CUDA_OK(cudaDeviceSynchronize());

    _poseidon2_rows<<<num_blocks, block_size, 0, gpu>>>(d_out, d_in, count, col_size);

    CUDA_OK(cudaGetLastError());

    gpu.sync();
  } catch (const cuda_error& e) {
    gpu.sync();
    return RustError{e.code(), e.what()};
  }

  return RustError{cudaSuccess};
}

enum Operation { OpAdd, OpMultiply };

extern "C" RustError::by_value
sppark_calc_prefix_operation(Fp4* in_elems, uint32_t count, Operation op) {
  const gpu_t& gpu = select_gpu();

  auto device_props = gpu_props(gpu.id());
  int major = device_props.major;
  const uint32_t CHUNK_MULT_80 = 44;
  const uint32_t CHUNK_MULT_70 = 45;

  uint32_t block_size = 256;
  const uint32_t CHUNK_ADD = 48;
  uint32_t CHUNK_MULT = major >= 8 ? CHUNK_MULT_80 : CHUNK_MULT_70;
  uint32_t tmp_num_block_add = (count + (block_size * CHUNK_ADD) - 1) / (block_size * CHUNK_ADD);
  uint32_t tmp_num_block_mult = (count + (block_size * CHUNK_MULT) - 1) / (block_size * CHUNK_MULT);
  uint32_t sm_count = gpu.sm_count();
  uint32_t num_blocks_add = std::min(tmp_num_block_add, sm_count);
  uint32_t num_blocks_mult = std::min(tmp_num_block_mult, sm_count);
  size_t sharedMemorySize = block_size * sizeof(Fp4);

  try {
    dev_ptr_t<Fp4> d_mem(count, gpu);
    Fp4* d_elems = &d_mem[0];

    gpu.HtoD(d_elems, in_elems, count);

    if (op == Operation::OpAdd)
      gpu.launch_coop(calc_prefix_op_kernel<Add<Fp4>, Fp4, CHUNK_ADD>,
                      {num_blocks_add, block_size, sharedMemorySize},
                      d_elems,
                      (size_t)count);
    else if (major >= 8)
      gpu.launch_coop(calc_prefix_op_kernel<Multiply<Fp4>, Fp4, CHUNK_MULT_80>,
                      {num_blocks_mult, block_size, sharedMemorySize},
                      d_elems,
                      (size_t)count);
    else
      gpu.launch_coop(calc_prefix_op_kernel<Multiply<Fp4>, Fp4, CHUNK_MULT_70>,
                      {num_blocks_mult, block_size, sharedMemorySize},
                      d_elems,
                      (size_t)count);

    gpu.DtoH(in_elems, d_elems, count);

    gpu.sync();
  } catch (const cuda_error& e) {
    gpu.sync();
    return RustError{e.code(), e.what()};
  }

  return RustError{cudaSuccess};
}
