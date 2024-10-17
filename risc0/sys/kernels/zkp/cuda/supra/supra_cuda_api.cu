#include <util/exception.cuh>
#include <util/gpu_t.cuh>
#include <util/rusterror.h>

#ifdef FEATURE_BABY_BEAR
#include <ff/baby_bear.hpp>
#endif

#include "calc_prefix_operation.cuh"
#include "poly_divide.cuh"
#include "poseidon_baby_bear/poseidon2.cu"

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

extern "C" RustError::by_value
poly_divide(fr4_t* polynomial, size_t poly_sz, fr4_t* remainder, const fr4_t* pow) {
  const gpu_t& gpu = select_gpu();
  uint32_t sm_count = gpu.sm_count();
  uint32_t sm_ceil = round_to_next_power_of_2(sm_count);

  const uint32_t divisor_degree = DIVISOR_DEGREE;
  const uint32_t block_sz = DIV_BLOCK_SZ;
  uint32_t nwarps_red = sm_ceil < WARP_SZ ? sm_ceil : WARP_SZ;
  uint32_t nwarps_sm = sm_ceil < WARP_SZ ? 1 : sm_ceil / WARP_SZ;

  uint32_t shared_powers_size = 3 * WARP_SZ / 2 + nwarps_red + nwarps_sm / 2;

  size_t shared_sz = sizeof(fr4_t) * ((block_sz / WARP_SZ) + shared_powers_size);

  size_t nthreads = sm_count * block_sz;
  size_t nloops = (poly_sz - divisor_degree + nthreads - 1) / nthreads;

  assert(block_sz >= sm_ceil);

  try {
    event_t sync_event;

    dev_ptr_t<fr4_t> d_mem(2 * sm_ceil + 2 * divisor_degree + poly_sz + block_sz + 1, gpu[0]);
    fr4_t* d_acc = &d_mem[0];
    fr4_t* d_prev_acc = &d_mem[sm_ceil];
    fr4_t* d_polynomial = &d_prev_acc[2 * divisor_degree];
    fr4_t(*_d_z_powers)[DIV_BLOCK_SZ] =
        reinterpret_cast<decltype(_d_z_powers)>(&d_polynomial[poly_sz]);

    sync_event.record(gpu[0]);

    generate_z_powers<<<1, block_sz, 0, gpu[0]>>>(_d_z_powers, pow[0], sm_ceil);

    sync_event.wait(gpu);
    sync_event.record(gpu[0]);

    gpu.HtoD(d_polynomial, polynomial, poly_sz);
    gpu.bzero(d_acc, sm_ceil + 2 * divisor_degree);

    sync_event.wait(gpu);

    const fr4_t(*d_z_powers)[DIV_BLOCK_SZ] = _d_z_powers;
    gpu.launch_coop(div_by_x_minus_z,
                    {sm_count, block_sz, shared_sz},
                    d_polynomial,
                    d_acc,
                    d_prev_acc,
                    poly_sz,
                    nloops,
                    d_z_powers);

    gpu.DtoH(remainder, &d_polynomial[0], 1);
    gpu.DtoH(polynomial, &d_polynomial[1], poly_sz - 1);

    gpu.sync();
  } catch (const cuda_error& e) {
    gpu.sync();
    return RustError{e.code(), e.what()};
  }

  return RustError{cudaSuccess};
}
