#include "poseidon2_constants.cuh"
#include "stdio.h"

#define CELLS 24
#define ROUNDS_FULL 8
#define ROUNDS_HALF_FULL (ROUNDS_FULL / 2)
#define ROUNDS_PARTIAL 21
#define ROW_SIZE (CELLS + ROUNDS_PARTIAL)
#define CELLS_RATE 16
#define CELLS_OUT 8

struct __align__(CELLS_OUT % 4 == 0 ? 16 : 4) poseidon_out_t {
  fr_t data[CELLS_OUT];
};

struct __align__(CELLS_RATE % 4 == 0 ? 16 : 4) poseidon_in_t {
  fr_t data[CELLS_RATE];
};

namespace poseidon2 {

__device__ __forceinline__ void pow7_cells_full(fr_t cells[CELLS]) {
#pragma unroll
  for (uint32_t i = 0; i < CELLS; i++) {
    cells[i] ^= 7;
  }
}

__device__ __forceinline__ void multiply_by_m_int(fr_t cells[CELLS]) {
  fr_t sum = 0;
#pragma unroll
  for (uint32_t i = 0; i < CELLS; i++) {
    sum += cells[i];
  }

#pragma unroll
  for (uint32_t i = 0; i < CELLS; i++) {
    cells[i] = sum + M_INT_DIAG_HZN[i] * cells[i];
  }
}

__device__ __forceinline__ void multiply_by_4x4_circulant(fr_t x[4]) {
  // See appendix B of Poseidon2 paper.
  fr_t t0 = x[0] + x[1];
  fr_t t1 = x[2] + x[3];
  fr_t t2 = x[1] + x[1] + t1;
  fr_t t3 = x[3] + x[3] + t0;
  fr_t t4 = fr_t(4) * t1 + t3;
  fr_t t5 = fr_t(4) * t0 + t2;
  fr_t t6 = t3 + t5;
  fr_t t7 = t2 + t4;
  x[0] = t6;
  x[1] = t5;
  x[2] = t7;
  x[3] = t4;
}

__device__ __forceinline__ void multiply_by_m_ext(fr_t cells[CELLS]) {
  // Optimized method for multiplication by M_EXT.
  // See appendix B of Poseidon2 paper for additional details.
  fr_t tmp_sums[4] = {0};

  for (uint32_t i = 0; i < CELLS / 4; i++) {
    fr_t* tmp = cells + i * 4;
    multiply_by_4x4_circulant(tmp);

    for (uint32_t j = 0; j < 4; j++) {
      tmp_sums[j] += tmp[j];
    }
  }

  for (uint32_t i = 0; i < CELLS; i++) {
    cells[i] += tmp_sums[i % 4];
  }
}

__device__ __forceinline__ void full_round(fr_t cells[CELLS], uint32_t round_constants_off) {
#pragma unroll
  for (uint32_t i = 0; i < CELLS; i++) {
    cells[i] += ROUND_CONSTANTS[round_constants_off + i];
  }
  pow7_cells_full(cells);
  multiply_by_m_ext(cells);
}

__device__ __forceinline__ void partial_round(fr_t cells[CELLS], uint32_t round_constants_off) {
  cells[0] += ROUND_CONSTANTS[round_constants_off];
  cells[0] ^= 7;
  multiply_by_m_int(cells);
}

__device__ __forceinline__ void poseidon2_mix(fr_t cells[CELLS]) {
  uint32_t round_constants_off = 0;

  // First linear layer.
  multiply_by_m_ext(cells);

#pragma unroll 1
  for (uint32_t i = 0; i < ROUNDS_HALF_FULL * 2 + ROUNDS_PARTIAL; i++) {
    if (i < ROUNDS_HALF_FULL || i >= ROUNDS_HALF_FULL + ROUNDS_PARTIAL) {
      full_round(cells, round_constants_off);
      round_constants_off += CELLS;
    } else {
      partial_round(cells, round_constants_off);
      round_constants_off++;
    }
  }
}

} // namespace poseidon2

__launch_bounds__(256, 4) __global__
    void _poseidon2_fold(poseidon_out_t* output, const poseidon_in_t* input, uint32_t output_size) {
  uint32_t gid = blockDim.x * blockIdx.x + threadIdx.x;
  fr_t cells[CELLS];
#pragma unroll
  for (uint32_t i = 0; i < CELLS; i++) {
    cells[i] = 0;
  }

  poseidon_in_t in = input[gid];
#pragma unroll
  for (size_t i = 0; i < CELLS_RATE; i++) {
    cells[i] = in.data[i];
  }

  poseidon2::poseidon2_mix(cells);
  poseidon_out_t tmp;

#pragma unroll
  for (uint32_t i = 0; i < CELLS_OUT; i++) {
    tmp.data[i] = cells[i];
  }
  output[gid] = tmp;
}

__launch_bounds__(256, 4) __global__
    void _poseidon2_rows(poseidon_out_t* out, const fr_t* matrix, uint32_t dim_x, uint32_t dim_y) {
  uint32_t gid = blockDim.x * blockIdx.x + threadIdx.x;
  if (gid >= dim_x)
    return;

  fr_t cells[CELLS] = {0};

  matrix += gid;
  uint32_t i = 0;

  do {
#pragma unroll
    for (uint32_t j = 0; j < CELLS_RATE; j++, i++)
      cells[j] = i < dim_y ? matrix[i * dim_x] : fr_t{0};

    poseidon2::poseidon2_mix(cells);
  } while (i < dim_y);

  poseidon_out_t tmp;
#pragma unroll
  for (uint32_t i = 0; i < CELLS_OUT; i++) {
    tmp.data[i] = cells[i];
  }

  out[gid] = tmp;
}
